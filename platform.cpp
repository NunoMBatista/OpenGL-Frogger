#include "platform.h"
#include "global.h"

Platform::Platform(int platform_type, ofVec3f dimensions, ofVec3f position, ofVec3f velocity){
    this->dimensions = dimensions;
    
    // Adjust position to center of the platform
    position.x += (dimensions.x / 2.0f) - (global.grid_size / 2.0f);
    this->position = position;

    this->velocity = velocity;
    this->platform_type = platform_type;

    turtle_shell_dimensions = dimensions * 0.6;
    turtle_head_dimensions = dimensions * 0.4;
    turtle_leg_dimensions = dimensions * 0.1;

}

void Platform::draw(){
    if(platform_type == 1){
        draw_log();
    }
    if(platform_type == 2){
        draw_turtle();
    }
}

void Platform::update(GLfloat delta_time){
    //position += velocity;
    position += velocity * delta_time;

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
    // Red shell
    glPushMatrix();
        glTranslatef(position.x, -global.grid_size/2, position.z);
        draw_shell();

        // Legs and tail
        glPushMatrix();
            glTranslatef(0, turtle_shell_dimensions.y * 0.2, 0);
            draw_legs();
        glPopMatrix();

        // In front of the shell
        glPushMatrix();
            glTranslatef(-turtle_shell_dimensions.x * 0.5, 0, 0);
            draw_head();
        glPopMatrix();
        
    glPopMatrix();


}

void Platform::draw_shell(){
    glPushMatrix();
        glScalef(turtle_shell_dimensions.x*0.9, turtle_shell_dimensions.y*0.9, turtle_shell_dimensions.z);
        cube_unit(0.7, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glScalef(turtle_shell_dimensions.x, turtle_shell_dimensions.y*0.9, turtle_shell_dimensions.z*0.9);
        cube_unit(0.7, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glScalef(turtle_shell_dimensions.x*0.8, turtle_shell_dimensions.y*0.9, turtle_shell_dimensions.z*0.8);
        cube_unit(0.7, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glScalef(turtle_shell_dimensions.x*0.6, turtle_shell_dimensions.y, turtle_shell_dimensions.z*0.6);
        cube_unit(0.7, 0, 0);
    glPopMatrix();
}

void Platform::draw_head(){
    glPushMatrix();
        glScalef(turtle_head_dimensions.x, turtle_head_dimensions.y, turtle_head_dimensions.z);
        cube_unit(0, 0.7, 0);
    glPopMatrix();

    // Eyes
    glPushMatrix();
        glTranslatef(-turtle_head_dimensions.x * 0.5, turtle_head_dimensions.y * 0.5, turtle_head_dimensions.z * 0.3);
        glScalef(turtle_head_dimensions.x * 0.3, turtle_head_dimensions.y * 0.6, turtle_head_dimensions.z * 0.35);
        cube_unit(1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-turtle_head_dimensions.x * 0.5, turtle_head_dimensions.y * 0.5, -turtle_head_dimensions.z * 0.3);
        glScalef(turtle_head_dimensions.x * 0.3, turtle_head_dimensions.y * 0.6, turtle_head_dimensions.z * 0.35);
        cube_unit(1, 1, 1);
    glPopMatrix();

    // Pupils
    glPushMatrix();
        glTranslatef(-turtle_head_dimensions.x * 0.6, turtle_head_dimensions.y * 0.3, turtle_head_dimensions.z * 0.3);
        glScalef(turtle_head_dimensions.x * 0.3, turtle_head_dimensions.y * 0.3, turtle_head_dimensions.z * 0.3);
        //glScalef(turtle_head_dimensions.x, turtle_head_dimensions.y, turtle_head_dimensions.z);
        cube_unit(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-turtle_head_dimensions.x * 0.6, turtle_head_dimensions.y * 0.3, -turtle_head_dimensions.z * 0.3);
        glScalef(turtle_head_dimensions.x * 0.3, turtle_head_dimensions.y * 0.3, turtle_head_dimensions.z * 0.3);
        cube_unit(0, 0, 0);
    glPopMatrix();

}

void Platform::draw_legs(){
    glPushMatrix();
        glTranslatef(-turtle_shell_dimensions.x * 0.5, 0, turtle_shell_dimensions.z * 0.5);
        draw_leg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-turtle_shell_dimensions.x * 0.5, 0, -turtle_shell_dimensions.z * 0.5);
        draw_leg();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(turtle_shell_dimensions.x * 0.5, 0, turtle_shell_dimensions.z * 0.5);
        draw_leg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(turtle_shell_dimensions.x * 0.5, 0, -turtle_shell_dimensions.z * 0.5);
        draw_leg();
    glPopMatrix();

    // Tail
    glPushMatrix();
        glTranslatef(turtle_shell_dimensions.x * 0.5, 0, 0);
        glScalef(1.5, 1, 1.5);
        draw_leg();
    glPopMatrix();


}

void Platform::draw_leg(){
    glPushMatrix();
        glScalef(turtle_leg_dimensions.x, turtle_leg_dimensions.y, turtle_leg_dimensions.z);
        cube_unit(0, 0.7, 0);
    glPopMatrix();

}