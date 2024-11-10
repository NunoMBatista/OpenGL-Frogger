
#include "grid.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

Grid::Grid(int rows, int columns, float size) {
    grid_rows = rows;
    grid_columns = columns;
    grid_size = size;

    top_river_row = grid_rows;
    bottom_river_row = grid_rows - 6;

    top_road_row = 7;
    bottom_road_row = 1;
}

void Grid::draw(){
    glPushMatrix();
        glTranslatef(0, -grid_size/2, 0);
        for(int i = 0; i < grid_rows; i++){
            for(int j = 0; j < grid_columns; j++){
                ofVec3f position = get_grid_position(i, j);

                glPushMatrix();
                    glTranslatef(position.x, position.y, position.z);
                    glScalef(grid_size, 1, grid_size);
                    // Draw the road
                    if((i <= top_road_row) && (i >= bottom_road_row)){
                        cube_unit(0, 0, 0);
                    }
                    // Draw the river
                    else if((i <= top_river_row) && (i >= bottom_river_row)){
                        cube_unit(0, 0, 0.5);
                    }
                    // Draw the grass (purple)
                    else{
                        cube_unit(0.5, 0, 0.5);
                    }
                glPopMatrix();
            }
        }
    glPopMatrix();
}

ofVec3f Grid::get_grid_position(int row, int column) {
    GLfloat x = column * grid_size;
    GLfloat z = row * grid_size;
    return ofVec3f(x, 0, z);
}

// Get the grid row and column from a world position
ofVec2f Grid::get_grid_row_column(ofVec3f position){
    int row = ceil(position.z / global.grid_size);
    int column = ceil(position.x / global.grid_size);
    return ofVec2f(row, column);
}

bool Grid::is_valid(int row, int column) {
    return row >= 0 && row < grid_rows && column >= 0 && column < grid_columns;
}

int Grid::get_rows() {
    return grid_rows;
}

int Grid::get_columns() {
    return grid_columns;
}

float Grid::get_size() {
    return grid_size;
}