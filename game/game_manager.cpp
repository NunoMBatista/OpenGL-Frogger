#include <vector>
#include "game_manager.h"
#include "../utils/cg_cam_extras.h"
#include "frog.h"
#include "car.h"
#include "platform.h"
#include <cmath>
#include "stages.h"
#include "ofImage.h"
#include "ofUtils.h"  


Game::Game() {
    glEnable(GL_DEPTH_TEST);
    ofSetBackgroundColor(0, 0, 0);

    // Initialize the lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    ambient_light = ofVec4f(1, 1, 1, 1);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light.getPtr());

    // Initialize the game state
    state = WELCOME_SCREEN;
    cur_stage = 1;
    course_setup(cur_stage);
    finished_frogs_count = 0;
    lives = 3;

    // Create the player 
    player_position = global.grid->get_grid_position(0, global.grid_columns / 2); // Start at middle of first row
    player_dimensions = ofVec3f(40, 80, 45) * 0.7;
    frog = new Frog(player_dimensions, player_position);

    // Initialize player grid position
    player_row = 0;
    player_column = global.grid_columns / 2;
    player_position = global.grid->get_grid_position(player_row, player_column);
    target_position = player_position;

    // Setup the camera
    cam = new Camera(
            60, // Default FOV
            global.grid->get_grid_position(global.grid_rows / 2, global.grid_columns / 2) // The ortho center is the center of the grid
        );
    camera_mode = PERSPECTIVE_PLAYER; // Default camera mode
    cam->setup(player_position, global.grid_columns);
    draw_frog = true;

    // Load the fonts
    font_size = 20;
    font.load("RetroFont.ttf", font_size);
    font_big.load("RetroFont.ttf", font_size * 5);
    font_small.load("RetroFont.ttf", font_size * 0.5);
}


Game::~Game() {
    delete cam;
    delete frog;
    for(auto finished_frog: finished_frogs){
        delete finished_frog;
    }
    for(auto car: cars){
        delete car;
    }
    for(auto platform: platforms){
        delete platform;
    }
    for(auto dead_frog: dead_frogs){
        delete dead_frog;
    }
}


void Game::apply_camera() { 
    cam->apply(camera_mode, player_position, frog); 
}


// Update the game state
void Game::update() {
    if (state != PLAYING) {
        frog->position = global.grid->get_grid_position(0, global.grid_columns / 2);
        frog->position.y = 0;
    }

    float delta_time = ofGetLastFrameTime();

    player_position = frog->position;
    frog->update(delta_time);
    cam->update(delta_time, player_position);

    for(auto it = dead_frogs.begin(); it != dead_frogs.end();){
        if((*it)->is_alive){
            (*it)->update(delta_time);
            it++;
        }
        else{
            delete *it;
            it = dead_frogs.erase(it);
        }
    }

    for(auto finished_frog: finished_frogs){
        finished_frog->update(delta_time);
    }   

    for(auto platform: platforms){
        platform->update(delta_time);
    }

    for(auto car : cars) {
        car->update(delta_time);
    }

    // Check for collisions
    for(auto car: cars){
        if(check_collision(frog->position, frog->dimensions, car->position, car->dimensions)){
            // Copy the frog to the dead_frogs vector
            Frog* dead_frog = new Frog(*frog);
            dead_frog->explosion();
            dead_frogs.push_back(dead_frog);

            // Reset the player frog
            reset_player();
        }
    }
    
    // If the frog goes out of bounds
    if((player_position.x < -global.grid_size) || (player_position.x > (global.grid_columns * global.grid_size))){
        Frog* dead_frog = new Frog(*frog);
        dead_frog->explosion();
        dead_frogs.push_back(dead_frog);
        
        reset_player();
    }

    bool on_plat = false;
    frog->on_plat = false;
    // Check if the frog has reached a goal
    if((player_row >= global.grid->top_river_row + 1) && (!frog->is_moving)){
        // Copy the frog to the finished_frogs vector
        
        filled_slots[player_column] = 1;
        finished_frogs_count++;

        Frog* finished_frog = new Frog(*frog);
        finished_frog->turn(DOWN);
        finished_frog->winning_effect();
        
        finished_frogs.push_back(finished_frog);

        // Add a new life to compensate for the reset_player call
        lives++;
        // Reset the player frog
        reset_player();

        if(finished_frogs_count >= 5){
            finished_frogs_count = 0; 
            state = STAGE_CLEARED;
        }
    }

    ofVec3f cur_plat_velocity = ofVec3f(0, 0, 0);
    for(auto platform: platforms){
        ofVec3f acceptable_dimensions = frog->dimensions * 0.5; // The frog can be on the edge of the platform
        if(check_collision(frog->position, acceptable_dimensions, platform->position, platform->dimensions)){
            on_plat = true;
            cur_plat_velocity = platform->velocity;
        }
    }
    if(on_plat){
        frog->on_plat = true;
        frog->plat_velocity = cur_plat_velocity;

        frog->position += cur_plat_velocity * delta_time;
        player_position = frog->position;
        player_position.y += global.platform_offset_y;
    }
    // Check if the frog is in the river
    if((player_row >= global.grid->bottom_river_row) && (player_row <= global.grid->top_river_row)){
        // Check if the frog is on a platform (log or turtle)
        if(!on_plat && !frog->is_drowning && !frog->is_splashing && !frog->is_jumping && !frog->is_moving){
            // Copy the frog to the dead_frogs vector
            Frog* dead_frog = new Frog(*frog);
            dead_frog->drown();
            dead_frogs.push_back(dead_frog);
            // Reset the player frog
            reset_player();
        }
    }
}


// Draw the main game scene
void Game::draw() {
    // Reset the viewport
    glViewport(0, 0, gw(), gh());
    // Draw the main scene
    draw_frog = camera_mode == FIRST_PERSON ? false : true;
    apply_camera();
    draw_scene();

    // Draw HUD and overlays based on state
    switch(state) {
        case WELCOME_SCREEN:
            draw_welcome_screen();
            break;
        case STAGE_CLEARED:
            draw_stage_cleared();
            break;
        case GAME_OVER:
            draw_game_over();
            break;
        case PLAYING:
            draw_hud();
            break;
        case FINISHED:
            draw_win_screen();
            return;
    }

    // Draw mini-map in first person mode
    if (camera_mode == FIRST_PERSON) {
        glViewport(gw()*0.75, gh()*0.75, gw()*0.25, gh()*0.25);
        camera_mode = ORTHO_TOP_DOWN;
        apply_camera();
        draw_frog = true;
        draw_scene();
        camera_mode = FIRST_PERSON;
    }
}


void Game::draw_scene(){
    if(draw_frog && state == PLAYING){
        frog->draw();
    }
    
    for(auto finished_frog: finished_frogs){
        finished_frog->draw();
    }

    for(auto dead_frog: dead_frogs){
        if(dead_frog->is_alive){
            dead_frog->draw();
        }
    }

    for(auto platform: platforms){
        platform->draw();
    }

    for(auto car: cars){
        car->draw();
    }

    global.grid->draw();
}


void Game::move_forward() {
    switch(frog->direction) {
        case UP:    try_move(player_row + 1, player_column); break;
        case DOWN:  try_move(player_row - 1, player_column); break;
        case LEFT:  try_move(player_row, player_column - 1); break;
        case RIGHT: try_move(player_row, player_column + 1); break;
    }
}


void Game::move_backward() {
    switch(frog->direction) {
        case UP:    try_move(player_row - 1, player_column); break;
        case DOWN:  try_move(player_row + 1, player_column); break;
        case LEFT:  try_move(player_row, player_column + 1); break;
        case RIGHT: try_move(player_row, player_column - 1); break;
    }
}


// Turn left in first person mode
void Game::turn_left() {
    Direction new_direction = UP;
    switch(frog->direction) {
        case UP:    new_direction = LEFT;   break;
        case DOWN:  new_direction = RIGHT;  break;
        case LEFT:  new_direction = DOWN;   break;
        case RIGHT: new_direction = UP;     break;
    }
    frog->turn(new_direction);
}


// Turn right in first person mode
void Game::turn_right() {
    Direction new_direction = UP;
    switch(frog->direction) {
        case UP:    new_direction = RIGHT;  break;
        case DOWN:  new_direction = LEFT;   break;
        case LEFT:  new_direction = UP;     break;
        case RIGHT: new_direction = DOWN;   break;
    }
    frog->turn(new_direction);
}


void Game::try_move(int new_row, int new_column) {
    ofVec3f new_position = player_position;
    int closest_column = global.grid->closest_column(player_position);

    // When the frog is moving into the goal row (top_river_row + 1)
    if(new_row == global.grid->top_river_row + 1){
        // Can only move to the last row if it's a goal position and it's empty
        if(((closest_column - 1) % 3 != 0) || (filled_slots[closest_column])){
            return;
        }
        else{
            // Mark the slot as filled
            filled_slots[closest_column] = true;
            // Move into the goal row
            new_position = global.grid->get_grid_position(new_row, closest_column);
            frog->start_move(player_position, new_position);
            player_row = new_row;
            player_column = closest_column;
        }
    }

    // If the frog is moving into a cell within the x limits or is on a platform (platforms do not restrict movement)
    if((global.grid->is_valid(new_row, new_column) || frog->on_plat) && !frog->is_moving) {
        // If the frog is in the river
        if((player_row >= global.grid->bottom_river_row) && (player_row <= global.grid->top_river_row + 1)){
            
            // If the frog is hopping between platforms or leaving the river (it's not moving in the same row)
            if(new_row != player_row){
                // Snap to the closest column
                new_column = closest_column;
                new_position = global.grid->get_grid_position(new_row, new_column);
            }

            // If the frog is moving in the same platform row do not snap to the closest cell
            else if(new_column != player_column){
                GLfloat move_offset = (new_column - player_column) * global.grid_size;
                
                // Compensate for the platform movement
                GLfloat platform_offset = frog->plat_velocity.x * ofGetLastFrameTime();
                new_position.x = player_position.x + move_offset + platform_offset;
                new_position.y = player_position.y - global.platform_offset_y;
            }
        }
        // If the frog is not in the river 
        else{
            // Just move in the grid
            new_position = global.grid->get_grid_position(new_row, new_column);
        }

        player_column = new_column;
        player_row = new_row;
        frog->start_move(player_position, new_position);
        frog->position = player_position;
    }
}


void Game::key_pressed(int key) {
    if(key == '+'){
        if(cam->theta_fov < 90){
            cam->theta_fov += 5;
        }
    }
    if(key == '-'){
        if(cam->theta_fov > 10){
            cam->theta_fov -= 5;
        }
    }
    if(key == 'f' || key == 'F'){
        ofToggleFullscreen();
    }

    switch(state) {
        case WELCOME_SCREEN:
            if (key == ' ') {
                state = PLAYING;
                frog->start_scale_animation();
            }
            return;
        case STAGE_CLEARED:
            if (key == ' ') {
                state = PLAYING;
                course_setup(++cur_stage);
                lives++;
                frog->start_scale_animation();
            }
            return;
        case GAME_OVER:
            if (key == ' ') restart_game();
            return;
        case FINISHED:
            if (key == ' ') restart_game();
            return;
        case PLAYING:
            if (frog->is_moving || frog->is_exploding || frog->is_scaling) return;
            switch(key) {
                case '1': 
                    camera_mode = ORTHO_TOP_DOWN; 
                    return;
                case '2': 
                    camera_mode = PERSPECTIVE_PLAYER; 
                    return;
                case '3':
                    camera_mode = FIRST_PERSON;
                    frog->eye_vector = direction_to_vector(frog->direction);
                    return;
            }

            // The movement keys are different in first person, you can only go forwards or backwards and turn left or right
            if(camera_mode == FIRST_PERSON) {
                switch(key) {
                    case 'w': case 'W': case OF_KEY_UP:     move_forward(); break;
                    case 's': case 'S': case OF_KEY_DOWN:   move_backward(); break;
                    case 'a': case 'A': case OF_KEY_LEFT:   turn_left(); break;
                    case 'd': case 'D': case OF_KEY_RIGHT:  turn_right(); break;
                }
            } 
            else {
                switch(key) {
                    case 'w': case 'W': case OF_KEY_UP:     try_move(player_row + 1, player_column); frog->turn(UP); break;
                    case 's': case 'S': case OF_KEY_DOWN:   try_move(player_row - 1, player_column); frog->turn(DOWN); break;
                    case 'a': case 'A': case OF_KEY_LEFT:   try_move(player_row, player_column - 1); frog->turn(LEFT); break;
                    case 'd': case 'D': case OF_KEY_RIGHT:  try_move(player_row, player_column + 1); frog->turn(RIGHT); break;
                }
            }
            break;
    }
}


ofVec3f Game::direction_to_vector(Direction dir) {
    switch(dir) {
        case UP:    return ofVec3f(0, 0, 1);
        case DOWN:  return ofVec3f(0, 0, -1);
        case LEFT:  return ofVec3f(-1, 0, 0);
        case RIGHT: return ofVec3f(1, 0, 0);
        default:    return ofVec3f(0, 0, 1);
    }
}


// // Check if a grid cell is valid
// bool Game::is_valid(int row, int column){
//     return row >= 0 && row < global.grid_rows && column >= 0 && column < global.grid_columns;
// }


// Check if the frog has collided
bool Game::check_collision(ofVec3f &pos1, ofVec3f &dim1, ofVec3f &pos2, ofVec3f &dim2) {
    /*
    ofVec3f mx1 = ofVec3f(
        pos1.x - dim1.x / 2,
        pos1.y - dim1.y / 2,
        pos1.z - dim1.z / 2
    );
    ofVec3f mx2 = ofVec3f(
        pos2.x - dim2.x / 2,
        pos2.y - dim2.y / 2,
        pos2.z - dim2.z / 2
    );
    ofVec3f mn1 = ofVec3f(
        pos1.x + dim1.x / 2,
        pos1.y + dim1.y / 2,
        pos1.z + dim1.z / 2
    );
    ofVec3f mn2 = ofVec3f(
        pos2.x + dim2.x / 2,
        pos2.y + dim2.y / 2,
        pos2.z + dim2.z / 2
    );

    return (mx1.x <= mn2.x && mn1.x >= mx2.x) &&
           (mx1.y <= mn2.y && mn1.y >= mx2.y) &&
           (mx1.z <= mn2.z && mn1.z >= mx2.z);
    */

    // Simplified version
    return (
        fabs(pos1.x - pos2.x) * 2 < (dim1.x + dim2.x) &&
        fabs(pos1.y - pos2.y) * 2 < (dim1.y + dim2.y) &&
        fabs(pos1.z - pos2.z) * 2 < (dim1.z + dim2.z)
    );
}


void Game::reset_player() {
    lives--;
    if (lives <= 0) {
        frog->is_alive = false;
        frog->is_splashing = false;
        frog->is_exploding = false;
        frog->is_drowning = false;
        frog->is_winning = false;
        state = GAME_OVER;
        return;
    }
    
    // Reset position to the middle of the first row
    player_row = 0;
    player_column = global.grid_columns / 2;
    player_position = global.grid->get_grid_position(player_row, player_column);
    player_position.y = 0;

    // Create a new frog
    frog = new Frog(player_dimensions, player_position);
    frog->start_scale_animation();

    // Make it face up and reset the eye vector
    frog->direction = UP;
    if(camera_mode == FIRST_PERSON){
        frog->eye_vector = direction_to_vector(frog->direction);
    }
}


void Game::restart_game() {
    state = PLAYING;
    lives = 4;
    finished_frogs_count = 0;
    cur_stage = 1;
    course_setup(cur_stage);
    reset_player();
    frog->start_scale_animation();
}


void Game::draw_win_screen(){
    // Save current matrices
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, gw(), gh(), 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

            // Draw win screen
            glColor3f(0, 1, 0);
            font_big.drawString("YOU WIN!", gw()/2 - font_big.stringWidth("YOU WIN!")/2, gh()/2 - 100);
            font.drawString("<Press SPACE to restart>", gw()/2 - font.stringWidth("Press SPACE to restart")/2, gh()/2 + 20);

            // Restore matrices
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void Game::draw_hud() {
    // Save current matrices
    glMatrixMode(GL_PROJECTION);
    
    glPushMatrix();
    
        glLoadIdentity();
    
        glOrtho(0, gw(), gh(), 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
    
        glPushMatrix();
            glLoadIdentity();

            glColor3f(0, 1, 0);

            font_small.drawString("Lives:", 30, 30);

            // Draw lives
            for (int i = 0; i < lives; i++) {
                glPushMatrix();
                    glTranslatef(font_small.stringWidth("Lives:      ") + 30 + i * 40, 26, 0);
                    glScalef(20, 20, 1);
                    rectFill_unit();
                glPopMatrix();
            }

            // Draw stage number
            string stage_text = "Stage: " + ofToString(cur_stage);
            font_small.drawString(stage_text, 30, 60);

            // Display current field of view and FPS 
            string fov_text = "FOV: " + ofToString(cam->theta_fov);
            string fps_text = "FPS: " + ofToString(ofGetFrameRate(), 0);
            font_small.drawString(fov_text, gw() - font_small.stringWidth(fov_text) - 30, 30);
            font_small.drawString(fps_text, gw() - font_small.stringWidth(fps_text) - 30, 60);


            // Restore matrices
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void Game::draw_game_over() {
    // Save current matrices
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glPushMatrix();
        glOrtho(0, gw(), gh(), 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        
        glPushMatrix();
            glLoadIdentity();

            // Draw game over text
            glColor3f(1, 0, 0);
            font_big.drawString("GAME OVER", gw()/2 - font_big.stringWidth("GAME OVER")/2, gh()/2 - 100);
            font.drawString("<Press SPACE to restart>", gw()/2 - font.stringWidth("Press SPACE to restart")/2, gh()/2 + 20);

            // Restore matrices
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void Game::draw_welcome_screen() {
    // Save current matrices
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, gw(), gh(), 0, -1, 1);
    
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

            // Draw title and instructions
            glColor3f(0, 1, 0);
            font_big.drawString("FROGGER", gw()/2 - font_big.stringWidth("FROGGER")/2, gh()/2 - 100);
            glColor3f(1, 1, 1);

            std::string instructions = 
                "                     Controls:\n\n"
                "             1: Orthographic view\n"
                "             2: Perspective view\n"
                "             3: First-Person view\n\n"
                "Use 'WASD' or the arrow keys to move\n\n"
                "             F: Toggle fullscreen\n\n"
                "       +/-: Adjust the field of view\n\n"
                "           <Press SPACE to start>";
            font.drawString(instructions, gw()/2 - font.stringWidth("Use 'WASD' or arrow keys to move")/2, gh()/2);

            // Restore matrices
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void Game::draw_stage_cleared() {
    // Save current matrices
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, gw(), gh(), 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

            // Draw stage cleared message
            glColor3f(1, 1, 0);
            font_big.drawString("STAGE CLEARED!", gw()/2 - font_big.stringWidth("STAGE CLEARED!")/2, gh()/2 - 100);
            font.drawString("<Press SPACE to continue>", gw()/2 - font.stringWidth("Press SPACE to continue")/2, gh()/2 + 20);
            

            // Restore matrices
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void Game::course_setup(int stage){
    clean_stage();
    switch(cur_stage){
        case 1:
            stage_1(cars, platforms);
            break;
        case 2:
            stage_2(cars, platforms);
            break;
        case 3:
            stage_3(cars, platforms);
            break;
        case 4: 
            state = FINISHED;
            break;
    }
}


void Game::clean_stage(){
    cars.clear();
    platforms.clear();
    dead_frogs.clear();
    finished_frogs.clear();
    filled_slots.reset();
}