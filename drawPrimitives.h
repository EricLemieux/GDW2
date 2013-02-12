#pragma once
#include "GL/glut.h"
#include <string>

void setLineWidth(float width){
	glLineWidth(width);
}

void setColor(float red, float green, float blue){
	glColor3f(red,green,blue);
}

void drawLine(float startX, float startY, float endX, float endY){
	glBegin(GL_LINES);
	glVertex3f(startX,startY,0);
	glVertex3f(endX,endY,0);
	glEnd();
}

void drawRectangle(bool filled, float cornerX, float cornerY, int width, int height, float theta){
	if(filled) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glRotatef(theta,0,0,1);
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(0,height,0);
	glVertex3f(width,height,0);
	glVertex3f(width,0,0);
	glEnd();
	glPopMatrix();
}

void drawCircle(int subdivisions, float radius, float centerX, float centerY){
	float x,y;
	float step = 2.f*M_PI/(float) subdivisions;
	glPushMatrix();
	glTranslatef(centerX,centerY,0);
	glBegin(GL_LINE_LOOP);
	for(float theta=0;theta<=2.f*M_PI;theta+=step)
	{
		x = radius*cos(theta);
		y = radius*sin(theta);
		glVertex3f(x,y,0);
	}
	glEnd();
	glPopMatrix();
}

void drawFilledCircle(int subdivisions, float radius, float centerX, float centerY)
{
	float x,y;
	float step = 2.f*M_PI/(float) subdivisions;
	glPushMatrix();
	glTranslatef(centerX,centerY,0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,0);
	for(float theta=0;theta<=2.f*M_PI;theta+=step)
	{
		x = radius*cos(theta);
		y = radius*sin(theta);
		glVertex3f(x,y,0);
	}
	glVertex3f(radius,0,0);
	glEnd();

	glPopMatrix();
}

void drawTriangle(bool filled, float p0x, float p0y, float p1x, float p1y, float p2x, float p2y)
{
	if(filled) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glBegin(GL_TRIANGLES);
	glVertex3f(p0x,p0y,0);
	glVertex3f(p1x,p1y,0);
	glVertex3f(p2x,p2y,0);
	glEnd();
}

void drawText(std::string s, float posX, float posY)
{
	glPushMatrix();
	glRasterPos2f(posX,posY);
	const char *text = s.c_str();
	for(int i=0;i<s.length();i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glPopMatrix();
}