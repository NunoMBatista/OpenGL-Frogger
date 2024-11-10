
#pragma once

#include "ofMain.h"


class Grid {
    public:
        Grid(int rows, int columns, float size);

        void draw();
        ofVec3f get_grid_position(int row, int column);
        ofVec2f get_grid_row_column(ofVec3f position);
        bool is_valid(int row, int column);

        int get_rows();
        int get_columns();
        float get_size();

        int closest_column(ofVec3f position);

        int top_river_row;
        int bottom_river_row;

        int top_road_row;
        int bottom_road_row;

    private:
        int grid_rows;
        int grid_columns;
        float grid_size;
};