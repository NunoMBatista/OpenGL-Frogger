
#include "global.h"

Global global; 

Global::Global() {
    grid_rows = 15;
    grid_columns = 15;
    grid_size = 50.0f;

    grid = new Grid(grid_rows, grid_columns, grid_size);

    left_out_of_bounds = grid->get_grid_position(0, -2).x;
    right_out_of_bounds = grid->get_grid_position(1, grid_columns+2).x;

    base_element_speed = 50.0f;
    platform_offset_y = 10.0f;
}