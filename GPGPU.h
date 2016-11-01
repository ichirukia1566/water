#pragma once

#define GLEW_STATIC 1
#include "gl_2_1.h"
#include <GL/glut.h>
#include <string>

class GPGPU
{
public:
	GPGPU(int w, int h);

	void restart();
	void update(float t);
	void display();
	void moveCtX(int i, float x);
	void moveCtY(int i, float y);
	void changeFreq(int i, float f);
	void changeSpeed(int i, float s);
	void changeAmp(int i, float a);
	void moveIslandX(float x);
	void moveIslandY(float y);
	int loadShader(char* filename, std::string& text);

private:
    int _width;				// width of the screen
	int _height;			// height of the screen
	int _initialized;		// if the cells are initialized (=1) or not (=0)

	GLuint _initializedLoc;
    GLuint _texUnitLoc;

	GLuint _t;
	GLuint _ct; // center
	GLuint _freq; // frequency
	GLuint _speed; // speed
	GLuint _amp; // amplitude
	GLuint _island; // island
	GLuint _light; // light
    
    GLuint _textureId;		// The texture ID used to store data array
    GLuint _programId;		// the program ID

    GLuint _fragmentShader;
};

