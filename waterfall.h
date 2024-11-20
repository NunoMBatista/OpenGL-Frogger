
#pragma once

#include "ofMain.h"
#include "particle.h"
#include <vector>

class Waterfall {
public:
    Waterfall(ofVec3f position, int start_row, int end_row);
    void update();
    void draw();

private:
    void spawn_particle();
    
    ofVec3f position;
    std::vector<Particle*> particles;
    int start_row;
    int end_row;
    float spawn_timer;
    float spawn_rate;
};