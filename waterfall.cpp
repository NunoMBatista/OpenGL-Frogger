
#include "waterfall.h"
#include "global.h"

Waterfall::Waterfall(ofVec3f position, int start_row, int end_row){
    spawn_rate = 0.001f;
    spawn_timer = 0;
    this->start_row = start_row;
    this->end_row = end_row;
    this->position = position;
}

void Waterfall::update() {
    // Spawn new particles
    spawn_timer += ofGetLastFrameTime();
    if (spawn_timer >= spawn_rate) {
        spawn_particle();
        spawn_timer = 0;
    }

    // Update existing particles
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](Particle* p) {
                if (p->lifespan <= 0) {
                    delete p;
                    return true;
                }
                return false;
            }
        ),
        particles.end()
    );

    for (auto& particle : particles) {
        particle->update();
    }
}

void Waterfall::draw() {
    for (auto& particle : particles) {
        particle->draw();
    }
}

void Waterfall::spawn_particle() {
    // Random Y position between start and end rows
    float z_pos = ofRandom(
        global.grid->get_grid_position(start_row, 0).z,
        global.grid->get_grid_position(end_row, 0).z
    );
    
    ofVec3f spawn_pos = ofVec3f(position.x, position.y, z_pos);
    ofVec3f velocity = ofVec3f(ofRandom(0, 0.02), ofRandom(0, 0.05), ofRandom(-0.2, 0.2));
    
    particles.push_back(new Particle(
        spawn_pos,
        velocity,
        ofVec3f(0, 0, ofRandom(0.5, 1)), // Blue-ish color
        ofRandom(0, 2) 
    ));
}