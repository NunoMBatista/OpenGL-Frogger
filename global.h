#pragma once

#include "ofMain.h"
#include "grid.h"
#include "platform.h"

class Global {
public:
    Global();

    int grid_rows;
    int grid_columns;
    float grid_size;

    Grid* grid;

    GLfloat left_out_of_bounds;
    GLfloat right_out_of_bounds;
    
    std::vector<Platform*> platforms;
};

extern Global global;