#include "car.h"
#include "grid.h"
#include "global.h"

Car::Car(ofVec3f dimensions, ofVec3f position, ofVec3f velocity){
    this->dimensions = dimensions;
    this->position = position;
    this->velocity = velocity;
}

void Car::update(){
    position += velocity;

    if(position.x < global.left_out_of_bounds){
        position.x = global.right_out_of_bounds;
    }
    // else if(position.x > global.right_out_of_bounds){
    //     position.x = global.left_out_of_bounds;
    // }

} 

void Car::draw(){
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(dimensions.x, dimensions.y, dimensions.z);
        cube_unit(1, 0, 0);
    glPopMatrix();
}

