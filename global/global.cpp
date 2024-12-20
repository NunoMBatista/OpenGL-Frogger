
#include "global.h"

Global global; 

Global::Global() {
    grid_rows = 15;
    grid_columns = 15;
    grid_size = 50.0f;

    grid = new Grid(grid_rows, grid_columns, grid_size);

    left_out_of_bounds = grid->get_grid_position(0, -3).x;
    right_out_of_bounds = grid->get_grid_position(1, grid_columns+3).x;

    base_element_speed = 50.0f;
    platform_offset_y = 10.0f;

}

void Global::load_textures(){
    // Load the textures
    life.load("life.png");
    life.setImageType(OF_IMAGE_COLOR_ALPHA);

    purple_grass.load("purple_grass.png");
    purple_grass.setImageType(OF_IMAGE_COLOR_ALPHA);

    tunnel.load("tunnel.png");
    tunnel.setImageType(OF_IMAGE_COLOR_ALPHA);

    green_grass.load("green_grass.jpg");
    green_grass.setImageType(OF_IMAGE_COLOR_ALPHA);
}