#include "particle.h"

Particle::Particle(ofVec3f position, ofVec3f velocity, ofVec3f color, float lifespan){
    this->position = position;
    this->velocity = velocity;
    this->lifespan = lifespan;
    this->color = color;

}

void Particle::update(float delta_time) {
    int gravity = -0.5;
    velocity.y += gravity * delta_time; // Apply gravity over time
    position += velocity * delta_time * 600; // Scale velocity to units/second
    lifespan -= delta_time;

    if(lifespan < 0){
        lifespan = 0;
    }
}

void Particle::draw(){
    position += velocity;

    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(ofRandom(0, 360), 1, 1, 1);
        glScalef(2*lifespan, 2*lifespan, 2*lifespan);
        //cube_unit(ofRandom(0, 1), ofRandom(0, 1), ofRandom(0, 1));
        cube_unit(color.x, color.y, color.z);
    glPopMatrix();
}

bool Particle::is_dead(){
    return false;
}