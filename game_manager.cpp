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
    movement_duration = 0.2; // Duration of movement in seconds
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
            get_grid_position(0, grid_columns/2).x,   cam_dist,          player_position.z, 
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
            0,          1,                          0
        );
    }

    if(camera_mode == FIRST_PERSON){
        perspective(theta_fov*1.5, 10, 1000);


        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
        int direction = frog->rotation;
        ofVec3f offset = ofVec3f(0, 0, 0);
        if(direction == 0) offset = ofVec3f(0, 0, 100);
        if(direction == 180) offset = ofVec3f(0, 0, -100);
        if(direction == -90) offset = ofVec3f(-100, 0, 0);
        if(direction == 90) offset = ofVec3f(100, 0, 0);

        lookat(
            player_position.x,                          player_position.y + 100,                     player_position.z, 
            player_position.x + offset.x,                     player_position.y + 100,          player_position.z + offset.z,
            0,                                                                1,                                     0
        );
    }

}

// Update the game state
void Game::update() {
    float delta_time = ofGetLastFrameTime();

    if(is_moving) {
        // Update movement timer
        movement_timer += delta_time;

        float progress = get_movement_progress();

        if(progress >= 1.0f){
            // Movement complete
            player_position = target_position;
            is_moving = false;
            movement_timer = 0;
        } 
        else {
            // Interpolate position
            player_position = start_position.getInterpolated(target_position, progress);
        }
    }

    // Update the frog's position and animation
    frog->position = player_position;
    frog->update(delta_time);
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

    cout << frog->direction << endl; 
}

// Key pressed event
void Game::key_pressed(int key){
    if(is_moving) return; // Ignore input while moving

    int new_row = player_row;
    int new_column = player_column;

    switch(key){
        case '1':
            camera_mode = ORTHO_TOP_DOWN;
            return;
            break;
        case '2':
            camera_mode = PERSPECTIVE_PLAYER;
            return;
            break;
        case '3':
            camera_mode = FIRST_PERSON;
            if(frog->direction == UP) frog->eye_vector = ofVec3f(0, 0, 1);
            if(frog->direction == DOWN) frog->eye_vector = ofVec3f(0, 0, -1);
            if(frog->direction == LEFT) frog->eye_vector = ofVec3f(-1, 0, 0);
            if(frog->direction == RIGHT) frog->eye_vector = ofVec3f(1, 0, 0);
            return;
            break;
    }

    if(camera_mode == FIRST_PERSON){
        // Change the frog's direction relative to the camera
        if(key == 'w' || key == 'W'){
            if(frog->direction == UP){
                new_row += 1;
            }
            else if(frog->direction == DOWN){
                new_row -= 1;
            }
            else if(frog->direction == LEFT){
                new_column -= 1;
            }
            else if(frog->direction == RIGHT){
                new_column += 1;
            }
        }
        if(key == 'a' || key == 'A'){
            if(frog->direction == UP){
                frog->turn(LEFT);
            }
            else if(frog->direction == DOWN){
                frog->turn(RIGHT);
            }
            else if(frog->direction == LEFT){
                frog->turn(DOWN);
            }
            else if(frog->direction == RIGHT){
                frog->turn(UP);
            }
        }
        if(key == 'd' || key == 'D'){
            if(frog->direction == UP){
                frog->turn(RIGHT);
            }
            else if(frog->direction == DOWN){
                frog->turn(LEFT);
            }
            else if(frog->direction == LEFT){
                frog->turn(UP);
            }
            else if(frog->direction == RIGHT){
                frog->turn(DOWN);
            }
        }
        if(key == 's' || key == 'S'){
            if(frog->direction == UP){
                new_row -= 1;
            }
            if(frog->direction == DOWN){
                new_row += 1;
            }
            if(frog->direction == LEFT){
                new_column += 1;
            }
            if(frog->direction == RIGHT){
                new_column -= 1;
            }
        }
    }
    
    else{
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
        }
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

        // Start frog jumping animation
        frog->is_jumping = true;
        frog->jump_progress = 0.0f;
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