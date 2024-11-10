#include "car.h"
#include "grid.h"
#include "global.h"

Car::Car(int car_type, ofVec3f dimensions, ofVec3f position, ofVec3f velocity){
    this->dimensions = dimensions;
    this->position = position;
    this->velocity = velocity;
    this->car_type = car_type;
}

void Car::update(){
    position += velocity;

    if(position.x < global.left_out_of_bounds){
        position.x = global.right_out_of_bounds;
    }
    else if(position.x > global.right_out_of_bounds){
        position.x = global.left_out_of_bounds;
    }

} 

void Car::draw(){
    if(car_type == 1){
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glScalef(dimensions.x, dimensions.y, dimensions.z);
            cube_unit(1, 0, 0);
        glPopMatrix();
    }
    if(car_type == 2){
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glScalef(dimensions.x, dimensions.y, dimensions.z);
            cube_unit(0, 1, 0);
        glPopMatrix();
    }
    if(car_type == 3){
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glScalef(dimensions.x, dimensions.y, dimensions.z);
            cube_unit(0, 0, 1);
        glPopMatrix();
    }
    if(car_type == 4){
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glScalef(dimensions.x, dimensions.y, dimensions.z);
            cube_unit(1, 1, 1);
        glPopMatrix();
    }
    if(car_type == 5){
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glScalef(dimensions.x*2, dimensions.y, dimensions.z);
            cube_unit(1, 1, 0);
        glPopMatrix();
    }

}

