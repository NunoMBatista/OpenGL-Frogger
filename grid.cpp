
#include "grid.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

Grid::Grid(int rows, int columns, float size) {
    grid_rows = rows;
    grid_columns = columns;
    grid_size = size;
}

void Grid::draw(){
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0, -grid_size/2, 0);
    for(int i = 0; i < grid_rows; i++){
        for(int j = 0; j < grid_columns; j++){
            ofVec3f position = get_grid_position(i, j);
            glPushMatrix();
                glTranslatef(position.x, position.y, position.z);
                glScalef(grid_size, 1, grid_size);
                cube_unit_outline();
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