#pragma once 

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

/*
    Platform types:
    1 - Log
    2 - Turtle
    
*/
class Platform{
    public: 
        Platform(int platform_type, ofVec3f dimensions, ofVec3f position, ofVec3f velocity);

        // Initialize the grid for this platform
        void initialize_grid();

        // Check if the frog is on a valid grid cell
        bool is_frog_on_grid(const ofVec3f& frog_position) const;

        void draw();

        void update();

        void draw_log();
        void draw_turtle();

        ofVec3f velocity;
        ofVec3f dimensions;
        ofVec3f position;

        int platform_type;

    private:
        std::vector<ofVec3f> grid_cells;
        float grid_size;
        ofVec3f origin;
};
