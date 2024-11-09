#include <vector>
#include "game_manager.h"
#include "cg_cam_extras.h"
#include "frog.h"
#include "car.h"

Game::Game() {
    glEnable(GL_DEPTH_TEST); // Make it possible to see the depth of the objects

    cam = new Camera(60.0f, global.grid->get_grid_position(global.grid_rows / 2, global.grid_columns / 2)); 
    camera_mode = ORTHO_TOP_DOWN;

    // Player position
    player_position = global.grid->get_grid_position(0, global.grid_columns / 2); // Start at middle of first row
    player_dimensions = ofVec3f(40, 80, 50);

    // Create the frog
    frog = new Frog(player_dimensions, player_position);

    // Initialize player grid position
    player_row = 0;
    player_column = global.grid_columns / 2;
    player_position = global.grid->get_grid_position(player_row, player_column);
    target_position = player_position;

    // Setup the camera
    cam->setup(player_position, global.grid_columns);

    cars.push_back(new Car(ofVec3f(global.grid_size / 2, global.grid_size / 2, global.grid_size / 2), global.grid->get_grid_position(1, 1), ofVec3f(-1, 0, 0)));
    cars.push_back(new Car(ofVec3f(global.grid_size / 2, global.grid_size / 2, global.grid_size / 2), global.grid->get_grid_position(1, 5), ofVec3f(-1, 0, 0)));
    cars.push_back(new Car(ofVec3f(global.grid_size / 2, global.grid_size / 2, global.grid_size / 2), global.grid->get_grid_position(1, 9), ofVec3f(-1, 0, 0)));

}

Game::~Game() {
    delete cam;
    delete frog;
    for(auto car: cars){
        delete car;
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
    frog->update(delta_time);
    cam->update(delta_time, player_position);

    for(auto dead_frog: dead_frogs){
        if(dead_frog->is_alive){
            dead_frog->update(delta_time);
        }
        else{
            // Remove the frog from the dead_frogs vector
            dead_frogs.erase(std::find(dead_frogs.begin(), dead_frogs.end(), dead_frog), dead_frogs.end());
            // Free memory
            delete dead_frog;
        }
    }

    for(auto car : cars) {
        car->update();
    }

    for(auto car: cars){
        if(check_collision(frog->position, frog->dimensions, car->position, car->dimensions)){
            // Copy the frog to the dead_frogs vector
            Frog* dead_frog = new Frog(*frog);
            dead_frog->explosion();
            dead_frogs.push_back(dead_frog);

            // Reset the player frog
            player_position = global.grid->get_grid_position(0, global.grid_columns / 2);
            frog = new Frog(player_dimensions, player_position);
            player_row = 0;
            player_column = global.grid_columns / 2;
        }
    }

}

// Draw the main game scene
void Game::draw(){
    apply_camera(); 
    frog->draw();

    for(auto dead_frog: dead_frogs){
        if(dead_frog->is_alive){
            dead_frog->draw();
        }
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
    if(global.grid->is_valid(new_row, new_column) && !frog->is_moving) {
        ofVec3f new_position = global.grid->get_grid_position(new_row, new_column);
        frog->start_move(player_position, new_position);
        player_row = new_row;
        player_column = new_column;
        player_position = new_position;
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
            case 'w': case 'W': move_forward(); break;
            case 's': case 'S': move_backward(); break;
            case 'a': case 'A': turn_left(); break;
            case 'd': case 'D': turn_right(); break;
        }
    } else {
        switch(key) {
            case 'w': case 'W': try_move(player_row + 1, player_column); frog->turn(UP); break;
            case 's': case 'S': try_move(player_row - 1, player_column); frog->turn(DOWN); break;
            case 'a': case 'A': try_move(player_row, player_column - 1); frog->turn(LEFT); break;
            case 'd': case 'D': try_move(player_row, player_column + 1); frog->turn(RIGHT); break;
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

// Get the position of a grid cell in world coordinates 
ofVec3f Game::get_grid_position(int row, int column){
    // Adjusted to make bottom left corner (0, 0)
    GLfloat x = column * global.grid_size;
    GLfloat z = row * global.grid_size;
    return ofVec3f(x, 0, z);
}

// Check if a grid cell is valid
bool Game::is_valid(int row, int column){
    return row >= 0 && row < global.grid_rows && column >= 0 && column < global.grid_columns;
}

// Check if the frog has collided
bool Game::check_collision(ofVec3f &pos1, ofVec3f &dim1, ofVec3f &pos2, ofVec3f &dim2) {


    bool collision = pos1.x < pos2.x + dim2.x &&
                     pos1.x + dim1.x > pos2.x &&
                     pos1.z < pos2.z + dim2.z &&
                     pos1.z + dim1.z > pos2.z;

    return collision;
}