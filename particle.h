#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

class Particle{
    public:
        Particle(ofVec3f position, ofVec3f velocity, ofVec3f color, float lifespan);
        void update(float delta_time);
        void draw();
        bool is_dead();

        GLfloat time_lived;
        ofVec3f position;
        ofVec3f velocity;
        ofVec3f color;
        float lifespan;

};