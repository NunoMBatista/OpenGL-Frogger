#pragma once

#include "ofMain.h"
#include "../utils/cg_extras.h"
#include "../camera/camera.h"
#include "../grid/grid.h" 
#include "../global/global.h"
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
    GAME_OVER,
    FINISHED
};

class Game{
    public: 
        Game();
        ~Game();


        /*
        ******** Core game definitions *******
        */
        std::bitset<20> filled_slots;
        int finished_frogs_count; 
        GameState state;
        int cur_stage;
        int lives;
        void update();
        void draw();
        void key_pressed(int key);
        void restart_game();
        void clean_stage();
        void course_setup(int stage);
        bool check_collision(ofVec3f &pos1, ofVec3f &dim1, ofVec3f &pos2, ofVec3f &dim2);
        void reset_player();


        /*
        ******* Camera definitions ******* 
        */
        Camera* cam;
        CameraMode camera_mode;
        void apply_camera(); 


        /*
        ******* Player definitions ******* 
        */
        ofVec3f player_position;
        ofVec3f player_dimensions;
        ofVec3f target_position; // Where the player is moving to
        int player_row;
        int player_column;
        void try_move(int new_row, int new_column); // Call is_valid and move the player
        // bool is_valid(int row, int column); // Check if a grid cell is valid


        /*
        ******* Frog definitions ******* 
        */
        Frog* frog;
        std::vector<Frog*> dead_frogs; // Stores the frogs that are currently in a dying animation
        std::vector<Frog*> finished_frogs; // Stores the frogs that have reached the end
        bool draw_frog; // Whether to draw the frog or not


        /*
        ******* Grid and scene definitions ******* 
        */
        std::vector<Car*> cars; 
        std::vector<Platform*> platforms;
        void draw_scene();
       

        /*
        ******* First person camera definitions ******* 
        */
        void move_forward();
        void move_backward();
        void turn_left();
        void turn_right(); 
        ofVec3f direction_to_vector(Direction dir); 


        /*
        ******* HUD definitions *******
        */
        int font_size;
        ofTrueTypeFont font;
        ofTrueTypeFont font_big;
        ofTrueTypeFont font_small;
        void draw_hud();
        void draw_game_over();
        void draw_welcome_screen();
        void draw_win_screen();
        void draw_stage_cleared();
};
