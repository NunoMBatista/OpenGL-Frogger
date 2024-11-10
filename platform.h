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

        void draw();

        void update();

        void draw_log();
        void draw_turtle();

        ofVec3f velocity;
        ofVec3f dimensions;
        ofVec3f position;

        int platform_type;
};
