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
<<<<<<< HEAD

    GLfloat base_element_speed;    
   
=======
    
    std::vector<Platform*> platforms;
>>>>>>> a553dac1df9531293d8c747fc2cc0a6d92c2e261
};

extern Global global;