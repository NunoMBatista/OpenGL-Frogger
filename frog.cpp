#include "frog.h"


// Frog constructor
Frog::Frog(ofVec3f dimensions, ofVec3f position)
    : dimensions(dimensions), position(position) {
    // Body proportions
    body_w = dimensions.x * 0.5;
    body_h = dimensions.y * 0.20;
    body_l = dimensions.z * 0.5;

    // Leg proportions
    leg_w = body_w * 0.2;
    leg_h = body_h * 0.4;
    leg_l = body_l * 0.1;

    // Neck proportions
    neck_w = body_w * 0.25;
    neck_h = body_h * 0.25;
    neck_l = body_l * 0.25;

    // Head proportions
    head_w = dimensions.x * 0.6;
    head_h = dimensions.y * 0.2;
    head_l = dimensions.z * 0.6;

    // Eye proportions
    eye_w = head_w * 0.3;
    eye_h = dimensions.y * 0.2;
    eye_l = head_l * 0.3;

    rotation = 0;
    target_rotation = 0;
    rotation_speed = 360.0f; // Degrees per second
    is_rotating = false;

    // Initialize jump variables
    is_jumping = false;
    jump_progress = 0.0f;  // Progress of the jump in seconds (0 to jump_duration)
    jump_duration = 0.2f;  // Duration of the jump in seconds
    jump_height = dimensions.y * 0.5f; // Height of the jump

    // Initialize movement variables
    is_moving = false;
    movement_timer = 0;
    movement_duration = 0.2f;

    // Initialize explosion variables
    is_exploding = false;
    explosion_timer = 0;
    explosion_duration = 0.7f;
    explosion_rotation_speed = 720.0f; // Degrees per second
    explosion_jump_height = dimensions.y * 1.5;

    is_alive = true;
    is_bursting = false;

    is_drowning = false;
    is_splashing = false;
    is_winning = false;

    drowning_jump_height = dimensions.y * 1;
    drowning_duration = 0.7f;

    f_scale = 1.0f;

    on_plat = false;
    plat_velocity = ofVec3f(0, 0, 0); 

    is_scaling = false;
    scale_progress = 0.0f;
    scale_duration = 0.3f;

    this->direction = UP;
}

// Destructor
Frog::~Frog() {
    for(auto particle : particles){
        delete particle;
    }
    particles.clear();
}

void Frog::update(float delta_time) {
    // Exploding animation
    if(is_exploding) update_explosion(delta_time);

    // Drowning animation
    if(is_drowning) update_drowning(delta_time);

    // Update the particles
    if(is_bursting || is_splashing){
        // Iterate throgh the particles and remove the ones with lifespan 0
        for(auto it = particles.begin(); it != particles.end();){
            if((*it)->lifespan <= 0){
                delete *it;
                it = particles.erase(it);
            }
            else{
                it++;
            }
        }

        for(auto particle : particles){
            particle->update(delta_time);
        }
    }

    // Movement animation
    if(is_moving) update_movement(delta_time);

    // Jump animation
    if(is_jumping) update_jump(delta_time);

    // Rotation animation
    if (is_rotating) update_rotation(delta_time);

    // Update scaling animation
    if(is_scaling) {
        scale_progress += delta_time;
        if(scale_progress >= scale_duration) {
            scale_progress = scale_duration;
            is_scaling = false;
        }
    }
}

void Frog::update_drowning(float delta_time){
    if(is_moving) return;
    // If it's not moving, it's already in the water
    jump_height = drowning_jump_height;


    drowning_timer += delta_time;
    if(drowning_timer >= drowning_duration){
        // Stop drowning and start splashing 
        is_drowning = false;
        splash_effect();
    }
    else{
        jump_progress += delta_time;
    }
}

void Frog::update_explosion(float delta_time) {
    explosion_timer += delta_time;

    float progress = explosion_timer / explosion_duration;
    // Shrinking effect
    f_scale = 1 - progress;

    if(explosion_timer >= explosion_duration) {
        is_exploding = false;
        // Delete the frog
        f_scale = 0;
        burst_effect();
    } 
    else {
        rotation += explosion_rotation_speed * delta_time;
        jump_progress += delta_time;
    }
}

void Frog::update_movement(float delta_time) {
    movement_timer += delta_time;
    float progress = movement_timer / movement_duration;

    if(progress >= 1.0f) {
        position = target_position;
        is_moving = false;
        movement_timer = 0;
    } 
    else {
        position = start_position.getInterpolated(target_position, progress);
    }
}

void Frog::update_jump(float delta_time) {
    jump_progress += delta_time;
    if(jump_progress >= jump_duration) {
        jump_progress = jump_duration;
        is_jumping = false;
    }
}

void Frog::update_rotation(float delta_time) {
    // Amount of rotation needed to reach target
    float diff = target_rotation - rotation; 
    // Step size            
    float step = rotation_speed * delta_time;
    
    // If the step is larger than the remaining rotation, set rotation to target and finish
    if (abs(diff) < step) {
        rotation = target_rotation;
        is_rotating = false;
    } 
    else {
        // Determine rotation direction
        GLfloat dir = 0;
        if(diff > 0) {
            dir = 1;
        } else {
            dir = -1;
        }
    
        // If the rotation is larger than 180, take the shortest path
        if (abs(diff) > 180) {
            dir *= -1;
        }
        rotation += dir * step;
        
        // Keep rotation in [-180, 180] range
        if (rotation > 180) rotation -= 360;
        if (rotation < -180) rotation += 360;
    }
}

// Draw frog
void Frog::draw(){
    // Draw the particles
    if(is_bursting || is_splashing || is_winning){
        // Draw the particles
        if(particles.size() == 0){
            is_bursting = false;
            is_splashing = false;
            is_winning = false; 
            if(!is_winning)
                is_alive = false;
        }
        for(auto particle : particles){
            if(particle->lifespan > 0){
                particle->draw();
            }
        }
    }

    // Draw the frog
    glPushMatrix();
        glTranslatef(position.x, position.y - leg_h*3, position.z);

        // Apply scaling animation
        if(is_scaling) {
            float scale_factor = scale_progress / scale_duration;
            glScalef(scale_factor, scale_factor, scale_factor);
        }

        // Apply vertical offset for jump
        float y_offset = 0.0f;

        if(on_plat){
            y_offset += global.platform_offset_y;
        }

        if(is_jumping) {
            float t = jump_progress / jump_duration;
            y_offset = jump_height * sin(PI * t);
        }
        if(is_exploding) {
            // The frog does not come back down when exploding
            y_offset = jump_height * jump_progress / explosion_duration;
        }
        if(is_drowning || is_splashing){
            y_offset = -(jump_height * jump_progress / drowning_duration);
        }
        glTranslatef(0, y_offset, 0);

        glRotatef(rotation, 0, 1, 0); // Rotate the frog in the Y axis
        
        // Explosion shrinking effect
        glScalef(f_scale, f_scale, f_scale);
        
        
        draw_body();
        draw_legs();
        draw_neck();
        draw_head();
        draw_tongue();
        draw_eyes();
    glPopMatrix();
}

void Frog::draw_body() {
    glPushMatrix();
        glScalef(body_w, body_h, body_l);
        cube_unit();
    glPopMatrix();
}

void Frog::draw_legs() {
    glPushMatrix();
        glTranslatef(0, -body_h*0.5, 0);
        glPushMatrix();
            glTranslatef(0, -leg_h*0.5, 0);
            // Front legs
            glPushMatrix();
                glTranslatef(0, 0, body_l*0.25);    
                draw_leg(-body_w*0.75, 0, 0); // Left front leg
                draw_leg(body_w*0.75, 0, 0);  // Right front leg
            glPopMatrix(); // End front legs
            // Back legs
            glPushMatrix();
                // The back legs are double the size of the front legs and are placed further back
                glTranslatef(0, 0, -body_l*0.25 - leg_l*2);   
                glScalef(1, 1, 2);
                draw_leg(-body_w*0.75, 0, 0); // Left back leg
                draw_leg(body_w*0.75, 0, 0);  // Right back leg
            glPopMatrix(); // End back legs
        glPopMatrix(); // End legs
    glPopMatrix(); // End below body
}

void Frog::draw_leg(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
        glTranslatef(x, y+leg_h, z);
        glScalef(leg_w*2, leg_h*2, leg_l*2);
        cube_unit();
    glPopMatrix();
}

void Frog::draw_neck() {
    glPushMatrix();
        glTranslatef(0, body_h*0.5, 0);
        glTranslatef(0, neck_h*0.5, 0);
        glScalef(neck_w, neck_h, neck_l);
        cube_unit();
    glPopMatrix();
}

void Frog::draw_head() {
    glPushMatrix();
        glTranslatef(0, body_h*0.5 + neck_h, 0);
        glTranslatef(0, head_h*0.5, 0);
        glScalef(head_w, head_h, head_l);
        cube_unit();
    glPopMatrix();
}

void Frog::draw_tongue() {
    glColor3f(1, 0, 0);
    glPushMatrix();
        glTranslatef(0, body_h*0.5 + neck_h, 0);
        glTranslatef(0, head_h*0.5, 0);
        glTranslatef(0, 0, head_l*0.5);
        glScalef(head_w*0.5, head_h*0.2, head_l*0.3);
        cube_unit(1, 0, 0);
    glPopMatrix();
    glColor3f(0, 1, 0);
}

void Frog::draw_eyes() {
    glPushMatrix();
        glTranslatef(0, body_h*0.5 + neck_h + head_h, 0);
        glTranslatef(0, eye_h*0.5, 0);
        draw_eye(-eye_w); // Left eye
        draw_eye(eye_w);  // Right eye
    glPopMatrix();
}

void Frog::draw_eye(GLfloat x) {
    glPushMatrix();
        glTranslatef(x, 0, 0);
        glScalef(eye_w, eye_h, eye_l);
        cube_unit(1, 1, 1);
    glPopMatrix();

    // Pupil
    glPushMatrix();
        glTranslatef(x * 0.5, 0, eye_l * 0.5);
        glScalef(eye_w * 0.5, eye_h * 0.5, eye_l * 0.5);
        cube_unit(0, 0, 0);
    glPopMatrix();
}

void Frog::turn(Direction new_direction) {
    direction = new_direction;
    
    float new_rotation = 0;
    switch(new_direction) {
        case UP:
            new_rotation = 0;
            break;
        case DOWN:
            new_rotation = 180;
            break;
        case LEFT:
            new_rotation = -90;
            break;
        case RIGHT:
            new_rotation = 90;
            break;
    }
    
    target_rotation = new_rotation;
    is_rotating = true;
}

void Frog::start_move(const ofVec3f& start_pos, const ofVec3f& target_pos) {
    start_position = start_pos;
    target_position = target_pos;
    is_moving = true;
    movement_timer = 0;
    is_jumping = true;
    jump_progress = 0.0f;
}

void Frog::explosion() {
    is_moving = false;
    is_jumping = false;
    is_exploding = true;
    jump_height = explosion_jump_height;
    explosion_timer = 0;
}

void Frog::burst_effect(){
    is_bursting = true; 
    for(int i = 0; i < 100; i++){
        ofVec3f p_position = position;
        p_position.y += jump_height/2;
        
        ofVec3f p_color;
        // Eyes explosion
        if(i > 90){
            p_color = ofVec3f(1, 1, 1);
        }
        // Tongue explosion
        else if(i < 9){
            p_color = ofVec3f(1, 0, 0);
        }
        // Body explosion
        else{
            p_color = ofVec3f(0, ofRandom(0.5, 1), 0);
        }
        
        Particle* particle = new Particle(
            p_position,
            ofVec3f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5)),
            p_color,
            ofRandom(2, 5)
        );
        particles.push_back(particle);
    }
}

void Frog::drown(){
    is_drowning = true;
    drowning_timer = 0;
}

void Frog::splash_effect(){
    is_splashing = true;
    for(int i = 0; i < 200; i++){
        ofVec3f p_position = position;
        p_position.y -= jump_height/2;
        Particle* particle = new Particle(
            p_position,
            ofVec3f(ofRandom(-0.2, 0.2), ofRandom(0.5, 1), ofRandom(-0.2, 0.2))/3,
            ofVec3f(0, 0, ofRandom(0, 1)),
            ofRandom(2, 5)
        );
        
        particles.push_back(particle);
    }
}

void Frog::winning_effect(){
    is_winning = true; 
    for(int i = 0; i < 300; i++){
        Particle* particle = new Particle(
            position,
            ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)),
            ofVec3f(ofRandom(0.8, 1), ofRandom(0.8, 1), ofRandom(0, 0.5)),
            ofRandom(2, 5)
        );
        particles.push_back(particle);
    }
}

void Frog::start_scale_animation() {
    is_scaling = true;
    scale_progress = 0.0f;
}