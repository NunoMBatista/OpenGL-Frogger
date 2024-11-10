#pragma once 

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

class Car{
    public: 
        Car(int car_type, ofVec3f dimensions, ofVec3f position, ofVec3f velocity);

        void draw();
        void draw_car_type_1();
        void draw_car_type_2();
        void draw_car_type_3();
        void draw_car_type_4();
        void draw_car_type_5();      

        void update(GLfloat delta_time);


        ofVec3f velocity;
        ofVec3f dimensions;
        ofVec3f position;

        int car_type;

};