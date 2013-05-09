
/*
 * Gokhan Kiziltepe 040080168
 * 
 *------------------------------*
 * a --> light source left		*
 * d --> light source right		*
 * q --> turn batman left		*
 * e --> turn batman right		*
 *------------------------------*
 * 
 * This project is developed under Ubuntu 13.04 (Based on Debian/Ubuntu)
 * 
 * A debian based operating system (Debian/Ubuntu/Pardus2013/Mint...) can compile 
 * and run this code with correctly installed packages.
 * 
 * OpenGL Version: 3.0 Mesa 9.1.1
 * OpenGL Extension Wrangler 1.8.0 (GLEW)
 * Assimp 3.0
 * GLSL Version 1.3.0
 * 
 * To compile the code use 'Makefile' and 
 * the executable output 'fresnel_without_bonus' will be created 
 * 
 * You can also use this line from terminal
 * #g++ -Wall main.cpp -lGLEW -lGL -lglut -lGLU -lSOIL -lassimp -lm -o fresnel_without_bonus 
 * 
 * Changed shaders are
 * 	-diffuse_per_vertex_shader.frag
 * 	-diffuse_per_vertex_shader.vert
 *  -diffuse_per_pixel_shader.frag
 *  -diffuse_per_pixel_shader.vert
*/
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>
#include "Scene.h"

#include "ScreenSpaceShaderNode.h"
#include "NormalShaderNode.h"
#include "ColorFillNode.h"
#include "DiffusePerPixelNode.h"
#include "DiffusePerVertexNode.h"
#include "SimpleEffect.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define WINDOW_TITLE_PREFIX "Ders 7"

void IdleFunction(void);
void ResizeFunction(int Width, int Height);
void setupScene();

unsigned FrameCount = 0;

int CurrentWidth = 800,
CurrentHeight = 600,
WindowHandle = 0, mouseX = 0, mouseY = 0;

SceneNode* pad1;
SceneNode* pad2;
Light* light;

Camera *camera;

Scene* scene;

float directionX = 1;
float directionY = 0.5;
float speed = 0.001;

static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    scene->draw();
    
    glutSwapBuffers();
    FrameCount++;
}

GLboolean wire = false;

static void Key(unsigned char key, int x, int y)
{
    printf("%d", key);
    switch (key) {
		case 27:
			exit(0);
            break;
        case 'q': 
			pad1->rotate(5.f, 0, 1.0f, 0);
            pad2->rotate(5.f, 0, 1.0f, 0);
            break;
        case 'e': 
			pad1->rotate(-5.f, 0, 1.0f, 0);
            pad2->rotate(-5.f, 0, 1.0f, 0);
            break;
        case 'a':
            light->translate(-100, 0, 0);
            break;
        case 'd':
            light->translate(100, 0, 0);
            break;
        case 'w': 
            if( !wire )
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
               glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
                wire=!wire;
            break;
	}
}
void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
    scene->resize();
}

static void timerCallback (int value)
{
    if (0 != value) {
		char* TempString = (char*)
        malloc(512 + strlen(WINDOW_TITLE_PREFIX));
        
		sprintf(
                TempString,
                "%s: %d Frames Per Second @ %d x %d",
                WINDOW_TITLE_PREFIX,
                FrameCount * 4,
                CurrentWidth,
                CurrentHeight
                );
        
		glutSetWindowTitle(TempString);
		free(TempString);
	}
	FrameCount = 0;
	glutTimerFunc(250, timerCallback, 1);
}

void IdleFunction(void)
{
	glutPostRedisplay();
}

void setupScene(){
    scene = new Scene();
    
    pad1 = new DiffusePerPixelNode("Batman.obj");
    
    pad2 = new DiffusePerVertexNode("Batman.obj");

    pad1->translate(-80, 0, 0);
    
    pad2->translate(80, 0, 0);
    
    scene->addNode(pad1);
    scene->addNode(pad2);
    
    camera = new Camera();
    
    camera->translate(0.f, 100.f, 300.f);

    scene->setCamera(camera);
    
    scene->addEffect(new SimpleEffect(&CurrentWidth,&CurrentHeight));
    
    light = new Light();
    light->translate(0, 300.f, 400.f);
    
    scene->addLight(light);
}

int main (int argc, char ** argv)
{
    
    GLenum type;
    
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth,CurrentHeight);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("");
    GLenum err = glewInit();
	if (GLEW_OK != err)
	{
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf("GLSL Version: %s\n",glslVersion);
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    
    printf("GL Version: %s\n",glVersion);
    
    glClearColor(0.0, 1.0, 0.0, 1.0);
    // Z-Buffer i aciyoruz
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE); 
    
       
    setupScene();
    
    timerCallback(0);
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);
    glutIdleFunc(IdleFunction);
    glutMainLoop();
    
    return 0;
}


