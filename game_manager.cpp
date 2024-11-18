#include <vector>
#include "game_manager.h"
#include "cg_cam_extras.h"
#include "frog.h"
#include "car.h"
#include "platform.h"
#include <cmath>
#include "stages.h"

Game::Game() {
    glEnable(GL_DEPTH_TEST); // Make it possible to see the depth of the objects
    ofSetBackgroundColor(0, 0, 0); // Set the background color to black

    cam = new Camera(60.0f, global.grid->get_grid_position(global.grid_rows / 2, global.grid_columns / 2)); 
    camera_mode = PERSPECTIVE_PLAYER; // Default camera mode

    // Player position
    player_position = global.grid->get_grid_position(0, global.grid_columns / 2); // Start at middle of first row
    player_dimensions = ofVec3f(40, 80, 45);
    player_dimensions *= 0.7;

    // Create the frog
    frog = new Frog(player_dimensions, player_position);

    // Initialize player grid position
    player_row = 0;
    player_column = global.grid_columns / 2;
    player_position = global.grid->get_grid_position(player_row, player_column);
    target_position = player_position;

    // Setup the camera
    cam->setup(player_position, global.grid_columns);

    // Setup the course
    cur_stage = 1;
    course_setup(cur_stage);
    finished_frogs_count = 0;

    draw_frog = true;
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
    float delta_time = ofGetLastFrameTime();

    player_position = frog->position;
    frog->update(delta_time);
    cam->update(delta_time, player_position);

    for(auto dead_frog: dead_frogs){
        if(dead_frog->is_alive){
            dead_frog->update(delta_time);
        }
        else{
            // Remove the frog from the dead_frogs vector
            dead_frogs.erase(std::find(dead_frogs.begin(), dead_frogs.end(), dead_frog), dead_frogs.end());
        }
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
        finished_frog->rotation = 180;
        finished_frog->winning_effect();
        finished_frogs.push_back(finished_frog);
        // Reset the player frog
        reset_player();

        if(finished_frogs_count >= 5){
            finished_frogs_count = 0; 
            course_setup(++cur_stage);
        }
    }

    ofVec3f cur_plat_velocity = ofVec3f(0, 0, 0);
    for(auto platform: platforms){
        ofVec3f acceptable_dimensions = frog->dimensions * 0.5;
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
void Game::draw(){
    draw_frog = camera_mode == FIRST_PERSON ? false : true;
    apply_camera(); 
    draw_scene();

    draw_frog = true;
    // Draw a minimap in the top left corner in case of top down view
    if(camera_mode == FIRST_PERSON){
        glViewport(gw()*0.5, gh()*0.5, gw()*0.5, gh()*0.5);
        cam->apply_ortho_top_down(player_position);
        draw_scene();
    }
}

void Game::draw_scene(){
    if(draw_frog){
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
        case UP:    new_direction = LEFT; break;
        case DOWN:  new_direction = RIGHT; break;
        case LEFT:  new_direction = DOWN; break;
        case RIGHT: new_direction = UP; break;
    }
    frog->turn(new_direction);
}

// Turn right in first person mode
void Game::turn_right() {
    Direction new_direction = UP;
    switch(frog->direction) {
        case UP:    new_direction = RIGHT; break;
        case DOWN:  new_direction = LEFT; break;
        case LEFT:  new_direction = UP; break;
        case RIGHT: new_direction = DOWN; break;
    }
    frog->turn(new_direction);
}

void Game::try_move(int new_row, int new_column) {
    ofVec3f new_position = player_position;
    int closest_column = global.grid->closest_column(player_position);

    // When the frog is on the last row, it can only move to a goal position
    if(new_row == global.grid->top_river_row + 1){
        // Can only move to the last row if it's a goal position and it's empty
        if(((closest_column - 1) % 3 != 0) || (filled_slots[closest_column])){
            return;
        }
        else{
            filled_slots[closest_column] = true;
            new_position = global.grid->get_grid_position(new_row, closest_column);
            frog->start_move(player_position, new_position);
            player_row = new_row;
            player_column = closest_column;
        }
    }

    if((global.grid->is_valid(new_row, new_column) || frog->on_plat) && !frog->is_moving) {
        // If the frog is in the river
        if(player_row >= global.grid->bottom_river_row && player_row <= global.grid->top_river_row + 1){
            // If the frog is hopping platforms or leaving the river
            if(new_row != player_row){
                // Snap to the closest column
                new_column = closest_column;
                
                new_position = global.grid->get_grid_position(new_row, new_column);

                if(new_row < global.grid->bottom_river_row){
                    new_column = global.grid->closest_column(new_position);
                }
            }

            
            // If the frog is moving in the same platform row do not snap to the closest cell
            else if(new_column != player_column){
                GLfloat move_offset = (new_column - player_column) * global.grid_size;
                GLfloat platform_offset = frog->plat_velocity.x * ofGetLastFrameTime();
                new_position.x = player_position.x + move_offset + platform_offset;
                new_position.y = player_position.y - global.platform_offset_y;
                new_position.z = player_position.z;
            }
        }
        // If the frog is not in the river 
        else{
            new_position = global.grid->get_grid_position(new_row, new_column);
        }

        player_column = new_column;
        player_row = new_row;
        frog->start_move(player_position, new_position);

        //player_position = new_position;
        frog->position = player_position;

    }
}

void Game::key_pressed(int key) {
    if(frog->is_moving || frog->is_exploding) return;
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
    } else {
        switch(key) {
            case 'w': case 'W': case OF_KEY_UP:     try_move(player_row + 1, player_column); frog->turn(UP); break;
            case 's': case 'S': case OF_KEY_DOWN:   try_move(player_row - 1, player_column); frog->turn(DOWN); break;
            case 'a': case 'A': case OF_KEY_LEFT:   try_move(player_row, player_column - 1); frog->turn(LEFT); break;
            case 'd': case 'D': case OF_KEY_RIGHT:  try_move(player_row, player_column + 1); frog->turn(RIGHT); break;
        }
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

// Key released event
void Game::key_released(int key){
}

// Check if a grid cell is valid
bool Game::is_valid(int row, int column){
    return row >= 0 && row < global.grid_rows && column >= 0 && column < global.grid_columns;
}

// Check if the frog has collided
bool Game::check_collision(ofVec3f &pos1, ofVec3f &dim1, ofVec3f &pos2, ofVec3f &dim2) {
    return (
        fabs(pos1.x - pos2.x) * 2 < (dim1.x + dim2.x) &&
        fabs(pos1.y - pos2.y) * 2 < (dim1.y + dim2.y) &&
        fabs(pos1.z - pos2.z) * 2 < (dim1.z + dim2.z)
    );
}

void Game::reset_player() {
    player_position = global.grid->get_grid_position(0, global.grid_columns / 2);
    frog = new Frog(player_dimensions, player_position);
    player_row = 0;
    player_column = global.grid_columns / 2;
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
    }

}

void Game::clean_stage(){
    cars.clear();
    platforms.clear();
    dead_frogs.clear();
    finished_frogs.clear();
    filled_slots.reset();
}