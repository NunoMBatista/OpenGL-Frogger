#pragma once

#include "ofMain.h"

class Frog;

enum CameraMode{
    ORTHO_TOP_DOWN,
    PERSPECTIVE_PLAYER
};

class Game{
    public: 
        Game();

        void draw();

        void update();

        void camera();

        void key_pressed(int key);

        void key_released(int key);

        ofVec3f get_grid_position(int row, int column);
        float get_movement_progress();
        bool is_valid(int row, int column);

    private: 
        /*
        ******* Camera definitions ******* 
        */


        // Distance to scene center
        GLfloat cam_dist;

        // Field of view angle
    	GLfloat theta_fov = 60;
        
        // Camera mode
        CameraMode camera_mode;
        /*
        ******* End of camera definitions ******* 
        */


        /*
        ******* Player definitions ******* 
        */
        ofVec3f player_position;
        ofVec3f player_dimensions;

        ofVec3f player_movement;

        // Player grid position
        int player_row;
        int player_column;

        // Movement interpolation variables
        ofVec3f start_position; // Position of the player before movement
        float movement_timer; // Timer for movement interpolation
        float movement_duration; // Duration of the movement
        /*
        ******* End of player definitions ******* 
        */


        /*
        ******* Frog definitions ******* 
        */
        Frog* frog;
        /*
        ******* End of frog definitions ******* 
        */

        /*
        ******* Grid definitions ******* 
        */
        int grid_rows = 15;
        int grid_columns = 15;


        GLfloat grid_size = 50; // Size of each grid cell
        bool is_moving = false; // Is the player moving?
        ofVec3f target_position; // Where the player is moving to
};
