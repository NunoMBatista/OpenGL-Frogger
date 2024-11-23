#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "camera.h"
#include "grid.h" 
#include "global.h"
#include <vector>

// Forward declarations
class Frog;
class Camera;
class Car;
class Platform;

enum GameState {
    WELCOME_SCREEN,
    PLAYING,
    STAGE_CLEARED,
    GAME_OVER
};

class Game{
    public: 
        Game();
        ~Game();

        void draw();

        void update();

        void apply_camera(); 

        void key_pressed(int key);

        void key_released(int key);

        bool is_valid(int row, int column);

        bool check_collision(ofVec3f &pos1, ofVec3f &dim1, ofVec3f &pos2, ofVec3f &dim2);

        void reset_player();

        void draw_scene();

        void course_setup(int stage);

        void clean_stage();

    private: 
        /*
        ******* Camera definitions ******* 
        */
        Camera* cam;
        CameraMode camera_mode;
        /*
        ******* End of camera definitions ******* 
        */


        /*
        ******* Player definitions ******* 
        */
        ofVec3f player_position;
        ofVec3f player_dimensions;

        // Player grid position
        int player_row;
        int player_column;
        /*
        ******* End of player definitions ******* 
        */


        /*
        ******* Frog definitions ******* 
        */
        Frog* frog;
        std::vector<Frog*> dead_frogs;
        std::vector<Frog*> finished_frogs;
        int finished_frogs_count;
        bool draw_frog;

        /*
        ******* End of frog definitions ******* 
        */

        /*
        ******* Grid definitions ******* 
        */
        ofVec3f target_position; // Where the player is moving to
        /*
        ******* End of grid definitions ******* 
        */
       
        /*
        ******* First person camera definitions ******* 
        */
        void move_forward();
        void move_backward();
        void turn_left();
        void turn_right(); 
        ofVec3f direction_to_vector(Direction dir);
        /*
        ******** End of first person camera definitions ******* 
        */

        GameState state;

        void draw_welcome_screen();

        void try_move(int new_row, int new_column); // Try to move the player to a new grid cell (check if it's valid)
        const float ROTATION_SPEED = 90.0f; // Degrees per key press

        std::vector<Car*> cars; // List of cars
        std::vector<Platform*> platforms; // List of platforms
        std::bitset<20> filled_slots;
        int cur_stage;

        int lives;
        void draw_hud();
        void draw_game_over();
        void restart_game();
        void draw_stage_cleared();
};
