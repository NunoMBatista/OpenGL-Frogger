#include "game_manager.h"
#include "cg_cam_extras.h"

#include "frog.h"

Game::Game(){
    glEnable(GL_DEPTH_TEST); // Make it possible to see the depth of the objects
    
    theta_fov = 60;

    // Distance to scene center
    cam_dist = (gh()/2)/tan((theta_fov/2)*(PI/180));

    // Default camera mode
    camera_mode = PERSPECTIVE_TOP_DOWN;

    // Player position
    player_position = ofVec3f(0, 0, 0);
    player_dimensions = ofVec3f(46, 80, 56);

    // Player velocity
    player_movement = ofVec3f(0, 0, 0);

    // Create the frog
    frog = new Frog(player_dimensions, player_position);
}

void Game::camera(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    /*
        Perspective top down axis
        X: Right
        Z: Up
    */
    if(camera_mode == PERSPECTIVE_TOP_DOWN){
        perspective(theta_fov, 10, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
        lookat(
            0,   cam_dist,    player_position.z - 300, 
            0,          0,          player_position.z,
            0,          0,                          1
        );
    }

}

// Update the game state
void Game::update(){
    // Update the player position
    // player_position += player_movement;
    // frog->position = player_position;

    
    if(is_moving) {
        ofVec3f direction = target_position - player_position;
        if(direction.length() < 5){
            // Reached target - Snap to grid
            player_position = target_position;
            is_moving = false;
        }
        else{
            // Move towards target
            player_position += direction.getNormalized() * 5;
        }
    }
    frog->position = player_position;
}

// Draw the main game scene
void Game::draw(){
    camera();

    frog->draw();

    // Draw the floor
    ofSetColor(0, 0, 0);
    ofDrawBox(0, 0, 0, 1000, 1, 1000);

}

// Key pressed event
void Game::key_pressed(int key){
    if(is_moving) return; // Ignore input while moving

    ofVec3f new_target = target_position;

    switch(key){
        case 'w':
            new_target.z += grid_size;
            break;
        case 's':
            new_target.z -= grid_size;
            break;
        case 'a':
            new_target.x -= grid_size;
            break;
        case 'd':
            new_target.x += grid_size;
            break;
    }

    // Only start moving if the target is different
    if(new_target != target_position){
        target_position = new_target;
        is_moving = true;
    }

}

// Key released event
void Game::key_released(int key){
}

ofVec3f Game::get_grid_postion(int row, int column){
    GLfloat x = (column - grid_columns/2) * grid_size;
    GLfloat z = (row - grid_rows/2) * grid_size;
    return ofVec3f(x, 0, z); 
}

bool Game::is_valid(int row, int column){
    return row >= 0 && row < grid_rows && column >= 0 && column < grid_columns;
}