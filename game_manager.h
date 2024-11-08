#pragma once

#include "ofMain.h"

class Frog;

class Game{
    public: 
        Game();

        void draw();

        void update();

        void camera();

        void key_pressed(int key);

        void key_released(int key);



    private: 
        /*
        ******* Camera definitions ******* 
        */
        enum CameraMode{
            PERSPECTIVE_TOP_DOWN
        };

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
        int grid_rows = 10;
        int grid_columns = 10;

        ofVec3f get_grid_postion(int row, int column);
        bool is_valid(int row, int column);

        GLfloat grid_size = 50; // Size of each grid cell
        bool is_moving = false; // Is the player moving?
        ofVec3f target_position; // Where the player is moving to
};
