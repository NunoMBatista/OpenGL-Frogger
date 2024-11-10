#pragma once 

#include "ofMain.h"
#include "cg_drawing_extras.h"
#include "cg_cam_extras.h"
#include "particle.h"

class Frog {
    public:
        Frog(ofVec3f dimensions, ofVec3f position);
        ~Frog();
        
        void draw();
        void update(float delta_time);
        void turn(Direction direction);
        void start_move(const ofVec3f& start_pos, const ofVec3f& target_pos);
        bool is_moving;

        void update_movement(float delta_time);
        void update_jump(float delta_time);
        void update_rotation(float delta_time);
        void update_explosion(float delta_time);
        void update_drowning(float delta_time);

        void explosion();
        void burst_effect();
        
        void drown();
        void splash_effect();

        // Public variables
        ofVec3f eye_vector;        
        Direction direction;
        GLfloat rotation;
        ofVec3f dimensions;
        ofVec3f position;

        GLfloat f_scale;

        bool is_jumping;
        float jump_progress;
        float jump_duration;
        float jump_height;

        bool is_exploding;
        GLfloat explosion_timer;
        GLfloat explosion_duration;
        GLfloat explosion_rotation_speed;
        GLfloat explosion_jump_height;

        float target_rotation;
        float rotation_speed;
        bool is_rotating;

        bool is_alive;
        bool is_bursting;

        bool on_plat;

        bool is_drowning;
        bool is_splashing;
        GLfloat drowning_timer;
        GLfloat drowning_duration;
        GLfloat drowning_jump_height; 

        // Snap the frog's position to the nearest grid cell
        void snap_to_grid(const ofVec3f& grid_position);

    private:
        // Drawing methods
        void draw_body();
        void draw_neck();
        void draw_head();
        void draw_eye(GLfloat x);
        void draw_eyes();
        void draw_tongue();
        void draw_leg(GLfloat x, GLfloat y, GLfloat z);
        void draw_legs();

        // Body dimensions
        GLfloat body_w, body_h, body_l;
        GLfloat leg_w, leg_h, leg_l;
        GLfloat neck_w, neck_h, neck_l;
        GLfloat head_w, head_h, head_l;
        GLfloat eye_w, eye_h, eye_l;

        // Movement variables
        //bool moving;
        ofVec3f start_position;
        ofVec3f target_position;
        float movement_timer;
        float movement_duration;

        std::vector<Particle*> particles;

};