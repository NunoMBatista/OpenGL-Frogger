#include "game_manager.h"
#include "cg_cam_extras.h"

#include "frog.h"

Game::Game(){
    glEnable(GL_DEPTH_TEST); // Make it possible to see the depth of the objects
    
    theta_fov = 60;

    // Distance to scene center
    cam_dist = (gh()/2)/tan((theta_fov/2)*(PI/180));

    // Default camera mode
    camera_mode = ORTHO_TOP_DOWN;

    // Player position
    player_position = ofVec3f(0, 0, 0);
    player_dimensions = ofVec3f(46, 80, 56);

    // Player velocity
    player_movement = ofVec3f(0, 0, 0);

    // Create the frog
    frog = new Frog(player_dimensions, player_position);

    grid_size = 50; // Each grid cell is 50 units

    // Initialize player at grid cell (0, 0)
    player_row = 0;
    player_column = grid_columns/2;
    player_position = get_grid_position(player_row, player_column);
    target_position = player_position;
    is_moving = false;
    movement_timer = 0;
    movement_duration = 0.05; // Duration of movement in seconds
}

void Game::camera(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    /*
        Perspective top down axis
        X: Right
        Z: Up
    */
    if(camera_mode == ORTHO_TOP_DOWN){
        
        glOrtho(gw()/2, -gw()/2, -gh()/2, gh()/2, 10, 1000);
        //perspective(theta_fov, 10, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
        lookat(
            get_grid_position(0, grid_columns/2).x,   cam_dist,    player_position.z, 
            get_grid_position(0, grid_columns/2).x,          0,          player_position.z,
            0,          0,                          1
        );
    }
    if(camera_mode == PERSPECTIVE_PLAYER){
        perspective(theta_fov, 10, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
        lookat(
            player_position.x,   player_position.y + 200,    player_position.z - 300, 
            player_position.x,          player_position.y,          player_position.z,
            0,          0,                          1
        );
    }

}

// Update the game state
void Game::update(){
    if(is_moving) {
        // Update movement timer with the time since the last frame in order to get frame rate independent movement
        movement_timer += ofGetLastFrameTime();

        // The movement progress goes from 0 to 1
        float progress = get_movement_progress();
        
        if(progress >= 1.0f){
            // Movement complete
            player_position = target_position;
            is_moving = false;
            movement_timer = 0;
        } 
        else {
            // Linear interpolation
            player_position = start_position.getInterpolated(target_position, progress);
        }
    }
    frog->position = player_position;
}

float Game::get_movement_progress(){
    // Linear interpolation
    return movement_timer / movement_duration;
}

// Draw the main game scene
void Game::draw(){
    camera();
    frog->draw();

    // Draw the floor
    ofSetColor(0, 0, 0);

    // Draw grid
    for(int i = 0; i < grid_rows; i++){
        for(int j = 0; j < grid_columns; j++){
            ofVec3f position = get_grid_position(i, j);
            glPushMatrix();
                glTranslatef(position.x, position.y, position.z);
                glScalef(grid_size, 1, grid_size);
                cube_unit_outline();
            glPopMatrix();
        }
    }
}

// Key pressed event
void Game::key_pressed(int key){
    if(is_moving) return; // Ignore input while moving

    int new_row = player_row;
    int new_column = player_column;

    switch(key){
        case 'w':
        case 'W':
            new_row += 1;
            frog->turn(UP);
            break;
        case 's':
        case 'S':
            if(new_row > 0) new_row -= 1;
            frog->turn(DOWN);
            break;
        case 'a':
        case 'A':
            if(new_column > 0) new_column -= 1;
            frog->turn(LEFT);
            break;
        case 'd':
        case 'D':
            new_column += 1;
            frog->turn(RIGHT);
            break;
        case '1':
            camera_mode = ORTHO_TOP_DOWN;
            break;
        case '2':
            camera_mode = PERSPECTIVE_PLAYER;
            break;
    }

    // Check if the new position is valid
    if(is_valid(new_row, new_column)){
        // Save the start and target positions
        start_position = player_position;
        target_position = get_grid_position(new_row, new_column);
        
        // Update player grid position
        player_row = new_row;
        player_column = new_column;
        
        // Start movement
        is_moving = true;
        movement_timer = 0;
    }
}

// Key released event
void Game::key_released(int key){
}
// Get the position of a grid cell in world coordinates
ofVec3f Game::get_grid_position(int row, int column){
    // Adjusted to make bottom left corner (0, 0)
    GLfloat x = column * grid_size;
    GLfloat z = row * grid_size;
    return ofVec3f(x, 0, z);
}

// Check if a grid cell is valid
bool Game::is_valid(int row, int column){
    return row >= 0 && row < grid_rows && column >= 0 && column < grid_columns;
}