#pragma once

#include "ofMain.h"

enum material{
    FROG_SKIN,
    FROG_TONGUE,
    EYE,
    PUPIL,

    CAR_BODY_1,
    CAR_BODY_2,
    CAR_BODY_3,
    CAR_BODY_4,
    CAR_BODY_5,
    HEAD_LIGHT,
    WINDOW,
    TIRE,
    RIM,
    RADIATOR,
    
    LOG,
    
    TURTLE_SHELL,
    TURTLE_SKIN,
    
    WATER,
    ROAD,
    PURPLE_GRASS,
    TUNNEL,

    GOLD_PARTICLE,
    WATER_PARTICLE,

    GREEN_GRASS
};  

inline void load_material(enum material mat){
    GLfloat frog_skin_amb[] = {0.0, 0.5, 0.0, 1.0};
    GLfloat frog_skin_diff[] = {0.0, 0.7, 0.0, 1.0};
    GLfloat frog_skin_spec[] = {0.0, 0.5, 0.0, 1.0};
    GLfloat frog_skin_coef = 0.5;

    GLfloat frog_tongue_amb[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat frog_tongue_diff[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat frog_tongue_spec[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat frog_tongue_coef = 0.5;

    GLfloat eye_amb[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat eye_diff[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat eye_spec[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat eye_coef = 0.5;

    GLfloat pupil_amb[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat pupil_diff[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat pupil_spec[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat pupil_coef = 0.5;

    // Car 1 red
    GLfloat car_body_1_amb[] = {0.5, 0.0, 0.0, 1.0};
    GLfloat car_body_1_diff[] = {0.7, 0.0, 0.0, 1.0};
    GLfloat car_body_1_spec[] = {0.5, 0.0, 0.0, 1.0};
    GLfloat car_body_1_coef = 0.5;

    // Car 2 grey
    GLfloat car_body_2_amb[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat car_body_2_diff[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat car_body_2_spec[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat car_body_2_coef = 0.5;

    // Car 3 blue
    GLfloat car_body_3_amb[] = {0.0, 0.0, 0.5, 1.0};
    GLfloat car_body_3_diff[] = {0.0, 0.0, 0.7, 1.0};
    GLfloat car_body_3_spec[] = {0.0, 0.0, 0.5, 1.0};
    GLfloat car_body_3_coef = 0.5;

    // Car 4 purple
    GLfloat car_body_4_amb[] = {0.5, 0.0, 0.5, 1.0};
    GLfloat car_body_4_diff[] = {0.7, 0.0, 0.7, 1.0};
    GLfloat car_body_4_spec[] = {0.5, 0.0, 0.5, 1.0};
    GLfloat car_body_4_coef = 0.5;

    // Car 5 yellow
    GLfloat car_body_5_amb[] = {0.5, 0.5, 0.0, 1.0};
    GLfloat car_body_5_diff[] = {0.7, 0.7, 0.0, 1.0};
    GLfloat car_body_5_spec[] = {0.5, 0.5, 0.0, 1.0};
    GLfloat car_body_5_coef = 0.5;

    GLfloat head_light_amb[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat head_light_diff[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat head_light_spec[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat head_light_coef = 0.5;

    GLfloat window_amb[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat window_diff[] = {0.0, 0.0, 0.7, 1.0};
    GLfloat window_spec[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat window_coef = 0.5;

    GLfloat tire_amb[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat tire_diff[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat tire_spec[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat tire_coef = 0.5;

    GLfloat rim_amb[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat rim_diff[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat rim_spec[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat rim_coef = 0.5;

    GLfloat radiator_amb[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat radiator_diff[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat radiator_spec[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat radiator_coef = 0.5;

    GLfloat log_amb[] = {0.5, 0.3, 0.0, 1.0};
    GLfloat log_diff[] = {0.7, 0.5, 0.0, 1.0};
    GLfloat log_spec[] = {0.5, 0.3, 0.0, 1.0};
    GLfloat log_coef = 0.5;

    GLfloat turtle_shell_amb[] = {0.7, 0.0, 0.0, 1.0};
    GLfloat turtle_shell_diff[] = {0.7, 0.0, 0.0, 1.0};
    GLfloat turtle_shell_spec[] = {0.7, 0.0, 0.0, 1.0};
    GLfloat turtle_shell_coef = 0.5;

    GLfloat turtle_skin_amb[] = {0.0, 0.5, 0.0, 1.0};
    GLfloat turtle_skin_diff[] = {0.0, 0.7, 0.0, 1.0};
    GLfloat turtle_skin_spec[] = {0.0, 0.5, 0.0, 1.0};
    GLfloat turtle_skin_coef = 0.5;

    GLfloat water_amb[] = {0.0, 0.0, 0.5, 1.0};
    GLfloat water_diff[] = {0.0, 0.0, 0.7, 1.0};
    GLfloat water_spec[] = {0.0, 0.0, 0.5, 1.0};
    GLfloat water_coef = 0.5;

    GLfloat road_amb[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat road_diff[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat road_spec[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat road_coef = 0.5;

    GLfloat purple_grass_amb[] = {0.7, 0.0, 0.7, 1.0};
    GLfloat purple_grass_diff[] = {0.7, 0.0, 0.7, 1.0};
    GLfloat purple_grass_spec[] = {0.5, 0.0, 0.5, 1.0};
    GLfloat purple_grass_coef = 0.5;

    // Grey tunnel
    GLfloat tunnel_amb[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat tunnel_diff[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat tunnel_spec[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat tunnel_coef = 0.5;

    GLfloat gold_particle_amb[] = {0.8, 0.8, 0.0, 1.0};
    GLfloat gold_particle_diff[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat gold_particle_spec[] = {0.8, 0.8, 0.0, 1.0};
    GLfloat gold_particle_coef = 0.5;

    // Water particle can have multiple shades of blue
    GLfloat blue_shade = ofRandom(0.5, 1);
    GLfloat water_particle_amb[] = {0.0, 0.0, blue_shade*0.1f, 1.0};
    GLfloat water_particle_diff[] = {0.0, 0.0, blue_shade, 1.0};
    GLfloat water_particle_spec[] = {0.0, 0.0, blue_shade, 1.0};
    GLfloat water_particle_coef = 0.5;

    GLfloat green_grass_amb[] = {0, 0.5, 0, 1.0};
    GLfloat green_grass_diff[] = {0, 0.7, 0, 1.0};  
    GLfloat green_grass_spec[] = {0, 0.5, 0, 1.0};
    GLfloat green_grass_coef = 0.5;


    switch(mat){
        case (FROG_SKIN):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, frog_skin_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, frog_skin_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, frog_skin_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, frog_skin_coef);
            break;
        case (FROG_TONGUE):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, frog_tongue_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, frog_tongue_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, frog_tongue_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, frog_tongue_coef);
            break;
        case (EYE):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, eye_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, eye_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, eye_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, eye_coef);
            break;
        case (PUPIL):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pupil_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pupil_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pupil_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pupil_coef);
            break;
        case (CAR_BODY_1):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, car_body_1_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, car_body_1_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, car_body_1_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, car_body_1_coef);
            break;
        case (CAR_BODY_2):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, car_body_2_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, car_body_2_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, car_body_2_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, car_body_2_coef);
            break;
        case (CAR_BODY_3):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, car_body_3_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, car_body_3_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, car_body_3_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, car_body_3_coef);
            break;
        case (CAR_BODY_4):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, car_body_4_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, car_body_4_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, car_body_4_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, car_body_4_coef);
            break;
        case (CAR_BODY_5):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, car_body_5_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, car_body_5_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, car_body_5_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, car_body_5_coef);
            break;
        case (HEAD_LIGHT):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, head_light_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, head_light_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, head_light_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, head_light_coef);
            break;
        case (WINDOW):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, window_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, window_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, window_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, window_coef);
            break;
        case (TIRE):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tire_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tire_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tire_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, tire_coef);
            break;
        case (RIM):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, rim_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rim_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rim_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, rim_coef);
            break;
        case (RADIATOR):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, radiator_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, radiator_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, radiator_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, radiator_coef);
            break;
        case (LOG):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, log_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, log_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, log_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, log_coef);
            break;        
        case (TURTLE_SHELL):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, turtle_shell_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, turtle_shell_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, turtle_shell_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, turtle_shell_coef);
            break;
        case (TURTLE_SKIN):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, turtle_skin_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, turtle_skin_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, turtle_skin_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, turtle_skin_coef);
            break;
        case (WATER):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, water_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, water_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, water_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, water_coef);
            break;
        case (ROAD):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, road_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, road_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, road_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, road_coef);
            break;
        case (PURPLE_GRASS):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, purple_grass_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, purple_grass_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, purple_grass_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, purple_grass_coef);
            break;
        case (TUNNEL):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tunnel_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tunnel_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tunnel_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, tunnel_coef);
            break;
        case (GOLD_PARTICLE):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_particle_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_particle_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_particle_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_particle_coef);
            break;
        case (WATER_PARTICLE):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, water_particle_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, water_particle_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, water_particle_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, water_particle_coef);
            break;
        case (GREEN_GRASS):
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green_grass_amb);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green_grass_diff);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, green_grass_spec);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, green_grass_coef);
            break;
        default:
            break;
    }
}