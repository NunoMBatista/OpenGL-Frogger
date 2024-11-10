
#include "grid.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

Grid::Grid(int rows, int columns, float size) {
    grid_rows = rows;
    grid_columns = columns;
    grid_size = size;

    top_river_row = grid_rows - 3;
    bottom_river_row = top_river_row - 4;

    top_road_row = 6;
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
                    // Draw the road
                    if((i <= top_road_row) && (i >= bottom_road_row)){
                        glScalef(grid_size, 1, grid_size);
                        cube_unit(0, 0, 0);
                    }
                    // Draw the river
                    else if((i <= top_river_row) && (i >= bottom_river_row)){
                        glScalef(grid_size, 1, grid_size);
                        cube_unit(0, 0, 0.5);
                    }
                    // Draw the final row (green)
                    else if(i == grid_rows - 1){
                        glScalef(grid_size, grid_size*4, grid_size);
                        cube_unit(0, 0.6, 0);
                    }
                    // Draw the goal row (green and yellow)
                    else if(i == grid_rows - 2){
                        if((j - 1) % 3 == 0){
                            glScalef(grid_size, 1, grid_size);
                            cube_unit(0.6, 0.6, 0);
                        }
                        else{
                            glScalef(grid_size, grid_size*4, grid_size);
                            cube_unit(0, 0.9, 0);
                        }
                    }
                    // Draw the grass (purple)
                    else{
                        glScalef(grid_size, 1, grid_size);
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
    if (row == global.grid->top_river_row + 1){
        if((column - 1) % 3 == 0){
            return true;
        }
        return false;
    }


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

int Grid::closest_column(ofVec3f position){
    return round(position.x / grid_size);
}