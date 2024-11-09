#pragma once 

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

class Car{
    public: 
        Car(ofVec3f dimensions, ofVec3f position, ofVec3f velocity);

        void draw();

        void update();

        ofVec3f velocity;
        ofVec3f dimensions;
        ofVec3f position;

};