#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

class Particle{
    public:
        Particle(ofVec3f position, ofVec3f velocity, ofVec3f color, float lifespan);
        void update();
        void draw();
        bool is_dead();

        ofVec3f position;
        ofVec3f velocity;
        ofVec3f color;
        float lifespan;

};