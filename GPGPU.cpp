#include "GPGPU.h"
#include <iostream>
#include <fstream>

float ct[] = { 0.3, 0.3, 0.8, 0.7, 0.4, 0.9 };
float freq[] = { 50.0, 40.0, 30.0 };
float speed[] = { 0.01, 0.015, 0.01 };
float amp[] = { 0.4, 0.6, 0.45 };
float light[] = { 0.0, 0.0, 1.0 };
float island[] = { 0.5, 0.5 };
float tempT = 0;
GPGPU::GPGPU(int w, int h) : _initialized(0), _width(w), _height(h)
{
    // Create a texture to store the framebuffer
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGB, GL_FLOAT, 0);

    _programId = glCreateProgram();

	// Load fragment shader which will be used as computational kernel
	std::string edgeFragSource2;
	loadShader("fragment.glsl", edgeFragSource2);

    // Create the fragment program
    _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* source = edgeFragSource2.c_str();
    glShaderSource(_fragmentShader, 1, &source, NULL);
    glCompileShader(_fragmentShader);
    glAttachShader(_programId, _fragmentShader);

    // Link the shader into a complete GLSL program.
    glLinkProgram(_programId);

	// Check program
	{
		int infologLength = 0;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &infologLength);
		if (infologLength > 0) {
			char *infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(_programId, infologLength, NULL, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

    // Get location of the uniform variables
    _texUnitLoc = glGetUniformLocation(_programId, "texUnit");
	_initializedLoc = glGetUniformLocation(_programId, "initialized");
	_t = glGetUniformLocation(_programId, "t");
	_ct = glGetUniformLocation(_programId, "ct");
	_freq = glGetUniformLocation(_programId, "freq");
	_speed = glGetUniformLocation(_programId, "speed");
	_amp = glGetUniformLocation(_programId, "amp");
	_island = glGetUniformLocation(_programId, "island");
	_light = glGetUniformLocation(_programId, "light");
}

void GPGPU::restart()
{
	_initialized = 0;
}

void GPGPU::update(float t)
{
	tempT = t;
    // Backup the viewport dimensions
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    glViewport(0, 0, _width, _height);
        
    // Copy the results to the texture
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glUseProgram(_programId);
            
    // Set the uniform variables
    glUniform1i(_texUnitLoc, 0);
	glUniform1i(_initializedLoc, _initialized);
	_initialized = 1;
	
	glUniform1f(_t, t); // void glUniform1f(GLint location, GLfloat v0);
	glUniform2fv(_ct, 3, ct); // void glUniform2fv(GLint location, GLsizei count, const GLfloat *value);
	glUniform1fv(_freq, 3, freq);
	glUniform1fv(_speed, 3, speed);
	glUniform1fv(_amp, 3, amp);
	glUniform3fv(_light, 1, light);
	glUniform2fv(_island, 1, island);
	
            
	// By drawing a quad, the fragment shader will be called for each pixel.
    glBegin(GL_QUADS);
    {            
        glTexCoord2f(0, 0); glVertex3f(-1, -1, -0.5f);
        glTexCoord2f(1, 0); glVertex3f( 1, -1, -0.5f);
        glTexCoord2f(1, 1); glVertex3f( 1,  1, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1,  1, -0.5f);
    }
    glEnd();

    glUseProgram(0);
        
    // Copy the rendered image to the texture so that we can start from the current state in the next iteration
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, _width, _height);
        
    // Restore the stored viewport dimensions
	glViewport(vp[0], vp[1], vp[2], vp[3]);
}

void GPGPU::display()
{
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glEnable(GL_TEXTURE_2D);

    // Render the result image.
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0); glVertex3f(-1, -1, -0.5f);
        glTexCoord2f(1, 0); glVertex3f( 1, -1, -0.5f);
        glTexCoord2f(1, 1); glVertex3f( 1,  1, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1,  1, -0.5f);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

int GPGPU::loadShader(char* filename, std::string& text)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::in);

	std::string line;
	while (ifs.good()) {
        getline(ifs, line);

		text += line + "\n";
    }

	return 0;
}

void GPGPU::moveCtX(int i, float x)
{
	if((ct[i * 2] + x) <= 1.0f && (ct[i * 2] + x) >= 0.0f)
		ct[i * 2] += x;
	update(tempT);
}

void GPGPU::moveCtY(int i, float y)
{
	if ((ct[i * 2 + 1] + y) <= 1.0f && (ct[i * 2 + 1] + y) >= 0.0f)
		ct[i * 2 + 1] += y;
	update(tempT);
}

void GPGPU::changeFreq(int i, float f)
{
	if ((freq[i] + f) >= 0.0f)
		freq[i] += f;
	update(tempT);
}

void GPGPU::changeSpeed(int i, float s)
{
	if ((speed[i] + s) >= 0.0f)
		speed[i] += s;
	update(tempT);
}

void GPGPU::changeAmp(int i, float a)
{
	if ((amp[i] + a) >= 0.0f)
		amp[i] += a;
	update(tempT);
}

void GPGPU::moveIslandX(float x)
{
	if ((island[0] + x) >= 0.0f && (island[0] + x) <= 1.0f)
		island[0] += x;
	update(tempT);
}

void GPGPU::moveIslandY(float y)
{
	if ((island[0] + y) >= 0.0f && (island[0] + y) <= 1.0f)
		island[1] += y;
	update(tempT);
}