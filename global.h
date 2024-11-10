
#pragma once

#include "ofMain.h"
#include "grid.h"

class Global {
public:
    Global();

    int grid_rows;
    int grid_columns;
    float grid_size;

    Grid* grid;

    GLfloat left_out_of_bounds;
    GLfloat right_out_of_bounds;

    GLfloat base_element_speed;    
   
};

extern Global global;