#ifndef MODELS_H
#define MODELS_H

#include "ofMain.h"

inline void draw_frog(GLfloat f_width, GLfloat f_height, GLfloat f_length){
    GLfloat body_w = f_width;
    GLfloat body_h = f_height*0.20;
    GLfloat body_l = f_length;

    GLfloat leg_w = body_w*0.2;
    GLfloat leg_h = body_h*0.4;
    GLfloat leg_l = body_l*0.1;

    GLfloat neck_w = body_w*0.25;
    GLfloat neck_h = body_h*0.25;
    GLfloat neck_l = body_l*0.25;

    GLfloat head_w = f_width*0.5;
    GLfloat head_h = f_height*0.2;
    GLfloat head_l = f_length*0.5;

    GLfloat eye_w = head_w*0.3;
    GLfloat eye_h = f_height*0.2;
    GLfloat eye_l = head_l*0.3;

    // Frog
    glPushMatrix();
        // Main body
        glPushMatrix();
            glScalef(body_w, body_h, body_l);
            cube_unit();
        glPopMatrix();

        // Below body
        glPushMatrix();
            glTranslatef(0, -body_h*0.5, 0);
            
            // Legs
            glPushMatrix();
                glTranslatef(0, -leg_h*0.5, 0);
                
                // Front legs
                glPushMatrix();
                    glTranslatef(0, 0, body_l*0.25);    
                    // Left front leg
                    glPushMatrix();
                        glTranslatef(-body_w*0.25, 0, 0);
                        glScalef(leg_w, leg_h, leg_l);
                        cube_unit();
                    glPopMatrix();

                    // Right front leg
                    glPushMatrix();
                        glTranslatef(body_w*0.25, 0, 0);
                        glScalef(leg_w, leg_h, leg_l);
                        cube_unit();
                    glPopMatrix();
                glPopMatrix(); // End front legs

                // Back legs
                glPushMatrix();
                    glTranslatef(0, 0, -body_l*0.25);    
                    // Left back leg
                    glPushMatrix();
                        glTranslatef(-body_w*0.25, 0, 0);
                        glScalef(leg_w, leg_h, leg_l);
                        cube_unit();
                    glPopMatrix();

                    // Right back leg
                    glPushMatrix();
                        glTranslatef(body_w*0.25, 0, 0);
                        glScalef(leg_w, leg_h, leg_l);
                        cube_unit();
                    glPopMatrix();
                glPopMatrix(); // End front legs


            glPopMatrix(); // End legs
        glPopMatrix(); // End below body

        // Above body
        glPushMatrix();
            glTranslatef(0, body_h*0.5, 0);

            // Starts at neck
            glTranslatef(0, neck_h*0.5, 0);
            
            // Neck
            glPushMatrix();
                glScalef(neck_w, neck_h, neck_l);
                cube_unit();
            glPopMatrix();

            // Above neck
            glPushMatrix();
                glTranslatef(0, neck_h*0.5, 0);
                // Starts at head
                glTranslatef(0, head_h*0.5, 0);

                // Head
                glPushMatrix();
                    glScalef(head_w, head_h, head_l);
                    cube_unit();
                glPopMatrix();

                // Tongue
                glColor3f(1, 0, 0);
                glPushMatrix();
                    glTranslatef(0, 0, head_l*0.5);
                    glScalef(head_w*0.5, head_h*0.2, head_l*0.5);
                    cube_unit(1, 0, 0);
                glPopMatrix();

                glColor3f(0, 1, 0);
                // Above head
                glPushMatrix();
                    glTranslatef(0, head_h*0.5, 0);
                    glTranslatef(0, eye_h*0.5, 0);

                    // Eyes
                    glPushMatrix();
                        // Left eye
                        glPushMatrix();
                            glTranslatef(-eye_w, 0, 0);
                            glScalef(eye_w, eye_h, eye_l);
                            cube_unit(1, 1, 1);
                        glPopMatrix();
                        
                        // Right eye
                        glPushMatrix();
                            glTranslatef(eye_w, 0, 0);
                            glScalef(eye_w, eye_h, eye_l);
                            cube_unit(1, 1, 1);
                        glPopMatrix();

                        // Pupils
                        glPushMatrix();
                            // Left pupil
                            glPushMatrix();
                                glTranslatef(-eye_w*0.5, 0, eye_l*0.5);
                                glScalef(eye_w*0.5, eye_h*0.5, eye_l*0.5);
                                cube_unit(0, 0, 0);
                            glPopMatrix();

                            // Right pupil
                            glPushMatrix();
                                glTranslatef(eye_w*0.5, 0, eye_l*0.5);
                                glScalef(eye_w*0.5, eye_h*0.5, eye_l*0.5);
                                cube_unit(0, 0, 0);
                            glPopMatrix();
                        glPopMatrix();

                    glPopMatrix(); 
                glPopMatrix(); // End above head
            glPopMatrix(); // End above neck
        glPopMatrix();  // End above body
    glPopMatrix(); // End frog

}

#endif