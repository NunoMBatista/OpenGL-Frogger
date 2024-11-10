#pragma once

#include "ofMain.h"
#include "car.h"
#include "platform.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"
#include <vector>

inline void stage_1(std::vector<Car*> &cars, std::vector<Platform*> &platforms ){
    // First row of cars 
    cars.push_back(new Car(1, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(1, 1), ofVec3f(-global.base_element_speed, 0, 0)));
    cars.push_back(new Car(1, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(1, 5), ofVec3f(-global.base_element_speed, 0, 0)));
    cars.push_back(new Car(1, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(1, 9), ofVec3f(-global.base_element_speed, 0, 0)));

    // Second row of cars
    cars.push_back(new Car(2, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(2, 1), ofVec3f(global.base_element_speed, 0, 0)));
    cars.push_back(new Car(2, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(2, 9), ofVec3f(global.base_element_speed, 0, 0)));
    cars.push_back(new Car(2, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(2, 13), ofVec3f(global.base_element_speed, 0, 0)));

    // Third row of cars
    cars.push_back(new Car(3, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(3, 2), ofVec3f(-global.base_element_speed * 0.8, 0, 0)));
    cars.push_back(new Car(3, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(3, 6), ofVec3f(-global.base_element_speed * 0.8, 0, 0)));
    cars.push_back(new Car(3, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(3, 10), ofVec3f(-global.base_element_speed * 0.8, 0, 0)));

    // Fourth row of cars
    cars.push_back(new Car(4, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(4, 7), ofVec3f(global.base_element_speed * 2, 0, 0)));

    // Fifth row of cars
    cars.push_back(new Car(5, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(5, 3), ofVec3f(-global.base_element_speed * 1.5, 0, 0)));
    cars.push_back(new Car(5, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(5, 8), ofVec3f(-global.base_element_speed * 1.5, 0, 0)));

    cars.push_back(new Car(1, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(6, 1), ofVec3f(global.base_element_speed*1.2, 0, 0)));
    cars.push_back(new Car(1, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(6, 6), ofVec3f(global.base_element_speed*1.2, 0, 0)));
    cars.push_back(new Car(1, ofVec3f(global.grid_size * 0.75, global.grid_size * 0.75, global.grid_size * 0.75), global.grid->get_grid_position(6, 10), ofVec3f(global.base_element_speed*1.2, 0, 0)));

    // First row of platforms
    for(int i = 0; i < 16; i++){
        if(i % 4 == 0){
            continue;
        }
        platforms.push_back(new Platform(2, ofVec3f(global.grid_size * 1, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row, i), ofVec3f(-global.base_element_speed * 1, 0, 0)));

    }

    // Second row of platforms
    platforms.push_back(new Platform(1, ofVec3f(global.grid_size * 3, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 1, 3), ofVec3f(global.base_element_speed * 0.5, 0, 0)));
    platforms.push_back(new Platform(1, ofVec3f(global.grid_size * 3, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 1, 10), ofVec3f(global.base_element_speed * 0.5, 0, 0)));

    // Third row of platforms
    platforms.push_back(new Platform(1, ofVec3f(global.grid_size * 5, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 2, 1), ofVec3f(global.base_element_speed * 1.8, 0, 0)));
    platforms.push_back(new Platform(1, ofVec3f(global.grid_size * 5, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 2, 8), ofVec3f(global.base_element_speed * 1.8, 0, 0)));

    // Fourth row of platforms
    platforms.push_back(new Platform(2, ofVec3f(global.grid_size * 1, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 3, 7), ofVec3f(-global.base_element_speed * 1.5, 0, 0)));
    platforms.push_back(new Platform(2, ofVec3f(global.grid_size * 1, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 3, 8), ofVec3f(-global.base_element_speed * 1.5, 0, 0)));
    platforms.push_back(new Platform(2, ofVec3f(global.grid_size * 1, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 3, 9), ofVec3f(-global.base_element_speed * 1.5, 0, 0)));

    platforms.push_back(new Platform(2, ofVec3f(global.grid_size * 1, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 3, 12), ofVec3f(-global.base_element_speed * 1.5, 0, 0)));
    platforms.push_back(new Platform(2, ofVec3f(global.grid_size * 1, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 3, 13), ofVec3f(-global.base_element_speed * 1.5, 0, 0)));
    platforms.push_back(new Platform(2, ofVec3f(global.grid_size * 1, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 3, 14), ofVec3f(-global.base_element_speed * 1.5, 0, 0)));

    // Fifth row of platforms
    platforms.push_back(new Platform(1, ofVec3f(global.grid_size * 3, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 4, 2), ofVec3f(global.base_element_speed * 0.75, 0, 0)));
    platforms.push_back(new Platform(1, ofVec3f(global.grid_size * 3, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 4, 7), ofVec3f(global.base_element_speed * 0.75, 0, 0)));
    platforms.push_back(new Platform(1, ofVec3f(global.grid_size * 3, global.grid_size * 0.5, global.grid_size * 0.75), global.grid->get_grid_position(global.grid->bottom_river_row + 4, 13), ofVec3f(global.base_element_speed * 0.75, 0, 0)));
}