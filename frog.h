#pragma once 

//#include "ofApp.h"
#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"
#include "cg_cam_extras.h"

class Frog{
    public:
        Frog(
            ofVec3f dimensions,  // New parameter for dimensions
            ofVec3f position     // New parameter for position
        );
        
        // Main draw function, it calls all of the other draw functions
        void draw();

        // Main frame
        void draw_body();

        // Above body
        void draw_neck();
        void draw_head();
        void draw_eye(GLfloat x);
        void draw_eyes();
        void draw_tongue();
        
        // Below body
        void draw_leg(GLfloat x, GLfloat y, GLfloat z);
        void draw_legs();
        
        
        ofVec3f dimensions;  // New member variable for dimensions
        ofVec3f position;    // New member variable for position

        GLfloat body_w;
        GLfloat body_h;
        GLfloat body_l;

        GLfloat leg_w;
        GLfloat leg_h;
        GLfloat leg_l;

        GLfloat neck_w;
        GLfloat neck_h;
        GLfloat neck_l;

        GLfloat head_w;
        GLfloat head_h;
        GLfloat head_l;

        GLfloat eye_w;
        GLfloat eye_h;
        GLfloat eye_l;
};