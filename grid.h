
#pragma once

#include "ofMain.h"


class Grid {
    public:
        Grid(int rows, int columns, float size);

        void draw();

        ofVec3f get_grid_position(int row, int column);
        bool is_valid(int row, int column);

        int get_rows();
        int get_columns();
        float get_size();

    private:
        int grid_rows;
        int grid_columns;
        float grid_size;
};