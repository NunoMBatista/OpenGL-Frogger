#include "platform.h"
#include "global.h"

Platform::Platform(int platform_type, ofVec3f dimensions, ofVec3f position, ofVec3f velocity){
    this->dimensions = dimensions;
    this->position = position;
    this->velocity = velocity;
    this->platform_type = platform_type;
}

void Platform::draw(){
    if(platform_type == 1){
        draw_log();
    }
    if(platform_type == 2){
        draw_turtle();
    }
}

void Platform::update(){
    position += velocity;

    if(position.x < global.left_out_of_bounds){
        position.x = global.right_out_of_bounds;
    }
    else if(position.x > global.right_out_of_bounds){
        position.x = global.left_out_of_bounds;
    }
}

void Platform::draw_log(){
    glPushMatrix();
        glTranslatef(position.x, -global.grid_size/2, position.z);
        glScalef(dimensions.x, dimensions.y, dimensions.z);
        cube_unit(0.5, 0.35, 0.05);
    glPopMatrix();
}

void Platform::draw_turtle(){
}