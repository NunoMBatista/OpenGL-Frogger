﻿#pragma once

// #include "ofMain.h"
// #include "cg_extras.h"
#include "ofApp.h"
#include "materials.h"

//desenha ponto 3D na origem
inline void drawPoint() {
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();
}

//desenha axis 3D
inline void axis3d() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

//função que desenha quadrado unitário 
//centrado na origem e preenchido
inline void rectFill_unit() {
	glBegin(GL_QUADS);
	glVertex3d(-0.5, -0.5, 0.);
	glVertex3d(-0.5, 0.5, 0.);
	glVertex3d(0.5, 0.5, 0.);
	glVertex3d(0.5, -0.5, 0.);
	glEnd();
}

inline void cube_unit_outline() {
	GLfloat p = 0.5;
    glColor3f(0, 0, 0);
	load_material(PUPIL); // Black
	// Draw filled cube
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
		// Front
		glNormal3f(0, 0, 1);
		glVertex3f(-p, -p, p);
		glVertex3f(-p, p, p);
		glVertex3f(p, p, p);
		glVertex3f(p, -p, p);

		// Back
		glNormal3f(0, 0, -1);	
		glVertex3f(-p, -p, -p);
		glVertex3f(p, -p, -p);
		glVertex3f(p, p, -p);
		glVertex3f(-p, p, -p);

		// Top
		glNormal3f(0, 1, 0);
		glVertex3f(-p, -p, -p);
		glVertex3f(-p, -p, p);
		glVertex3f(p, -p, p);
		glVertex3f(p, -p, -p);

		// Bottom
		glNormal3f(0, -1, 0);
		glVertex3f(-p, p, p);
		glVertex3f(-p, p, -p);
		glVertex3f(p, p, -p);
		glVertex3f(p, p, p);

		// Left
		glNormal3f(-1, 0, 0);
		glVertex3f(-p, -p, p);
		glVertex3f(-p, -p, -p);
		glVertex3f(-p, p, -p);
		glVertex3f(-p, p, p);

		// Right
		glNormal3f(1, 0, 0);
		glVertex3f(p, -p, p);
		glVertex3f(p, p, p);
		glVertex3f(p, p, -p);
		glVertex3f(p, -p, -p);
	glEnd();

}

inline void cube_unit(GLfloat R = 0, GLfloat G = 1, GLfloat B = 0) {
	GLfloat p = 0.5;
	//glColor3f(R, G, B);
	//glColor3f(1, 1, 1);


	// Draw filled cube
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
		// Front
		glNormal3f(0, 0, 1);
		glVertex3f(-p, -p, p);
		glVertex3f(-p, p, p);
		glVertex3f(p, p, p);
		glVertex3f(p, -p, p);

		// Back
		glNormal3f(0, 0, -1);
		glVertex3f(-p, -p, -p);
		glVertex3f(p, -p, -p);
		glVertex3f(p, p, -p);
		glVertex3f(-p, p, -p);

		// Top
		glNormal3f(0, 1, 0);
		glVertex3f(-p, -p, -p);
		glVertex3f(-p, -p, p);
		glVertex3f(p, -p, p);
		glVertex3f(p, -p, -p);

		// Bottom
		glNormal3f(0, -1, 0);
		glVertex3f(-p, p, p);
		glVertex3f(-p, p, -p);
		glVertex3f(p, p, -p);
		glVertex3f(p, p, p);

		// Left
		glNormal3f(-1, 0, 0);
		glVertex3f(-p, -p, p);
		glVertex3f(-p, -p, -p);
		glVertex3f(-p, p, -p);
		glVertex3f(-p, p, p);

		// Right
		glNormal3f(1, 0, 0);
		glVertex3f(p, -p, p);
		glVertex3f(p, p, p);
		glVertex3f(p, p, -p);
		glVertex3f(p, -p, -p);
	glEnd();

	cube_unit_outline();
}

