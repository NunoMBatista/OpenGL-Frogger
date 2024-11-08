#include "frog.h"

// Frog constructor
Frog::Frog(ofVec3f dimensions, ofVec3f position)
    : dimensions(dimensions), position(position) {
    // Body proportions
    body_w = dimensions.x * 0.5;
    body_h = dimensions.y * 0.20;
    body_l = dimensions.z * 0.5;

    // Legs proportions
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

    // Initialize jump variables
    is_jumping = false;
    jump_progress = 0.0f;
    jump_duration = 0.2f;  // Duration of the jump in seconds
    jump_height = dimensions.y * 0.5f;  // Adjust as needed
}

void Frog::update(float delta_time) {
    if(is_jumping) {
        jump_progress += delta_time;
        if(jump_progress >= jump_duration) {
            jump_progress = jump_duration;
            is_jumping = false;
        }
    }
}

// Draw frog
void Frog::draw(){
    // Draw the frog
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);

        // Apply vertical offset for jump
        float y_offset = 0.0f;
        if(is_jumping) {
            float t = jump_progress / jump_duration;
            y_offset = jump_height * sin(PI * t);
        }
        glTranslatef(0, y_offset, 0);

        glRotatef(rotation, 0, 1, 0); // Rotate the frog in the Y axis
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
                draw_leg(-body_w*0.25, 0, 0); // Left front leg
                draw_leg(body_w*0.25, 0, 0);  // Right front leg
            glPopMatrix(); // End front legs
            // Back legs
            glPushMatrix();
                glTranslatef(0, 0, -body_l*0.25);    
                draw_leg(-body_w*0.25, 0, 0); // Left back leg
                draw_leg(body_w*0.25, 0, 0);  // Right back leg
            glPopMatrix(); // End back legs
        glPopMatrix(); // End legs
    glPopMatrix(); // End below body
}

void Frog::draw_leg(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(leg_w, leg_h, leg_l);
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

    switch(new_direction){
        case UP:
            rotation = 0;
            break;
        case DOWN:
            rotation = 180;
            break;
        case LEFT:
            rotation = -90;
            break;
        case RIGHT:
            rotation = 90;
            break;
    }
}