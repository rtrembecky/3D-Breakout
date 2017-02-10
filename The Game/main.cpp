#include "TGround.h"
#include "TBall.h"
#include "TBat.h"
#include "TBounds.h"
#include "TRay.h"
#include "TWell.h"
#include "Colors.h"
#include <iostream>
#include <ctime>
#include <string>
#ifndef _UNICODE
#define _UNICODE
#endif
#define IL_USE_PRAGMA_LIBS
#include "IL/devil_cpp_wrapper.hpp"

//int win_width = 1920;
//int win_height = 1080;
int win_width = 1280;
int win_height = 720;

const int mouseStartX = (win_width / 2);
const int mouseStartY = (win_height / 2);
int mouseX = mouseStartX, mouseY = mouseStartY;

unsigned int t = 0;

bool w, s, a, d = w = s = a = false;
bool up, down, lft, rgt = up = down = lft = false;
bool m, n = m = false;

const double ballMoveSpeed = 1.0f;
const int fpsCap = 60;

float rot = 0.0f;

TBall ball;
TGround ground(70);
TBounds bounds;
TBat bats[3];
TWell well;

TVector afterCollisionVelocity;

GLuint wood;

bool above = true;
bool front = true;
bool top = false;
bool side = false;
bool right = true;

bool started = false;
bool pause = false;
bool moving = false;

const float l0_pos[] = { 0, 50, 0, 1 };
const float l1_pos[] = { 0, 50, 10, 1 };
const float l1_dir[] = { 0, -1, -0.2f };

unsigned int start = 0;
unsigned int score = 0;
unsigned int lowscore = 0;

void RenderString(GLdouble x, GLdouble y, const std::string &string)
{
	glRasterPos2d(x, y);
	for (unsigned int n = 0; n < string.size(); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[n]);
	}
}

void NewGame() {
	ball.SetPosition(TVector(0, 0, 25));
	ball.CalculateVelocity(TVector(0, 0, 0), ballMoveSpeed);
	well.ReactivateAll();
	well.ResetColors();
	started = false;
}

void Start() {
	ball.CalculateVelocity(TVector(rand() % 100 - 50, 0, rand() % 100 - 50).Unit(), ballMoveSpeed);
	started = true;
	score = 0;
}

void EndGame() {
	if (score < lowscore)
		lowscore = score;
	else if (lowscore == 0)
		lowscore = score;
	NewGame();
}

// Function that creates a menu used from a mouse
void mouseMenu(int value)
{
	if (value == 1)
		NewGame();
	if (value == 2) {
		pause = !pause;
		if (!started) {
			pause = false;
			Start();
		}
	}
	if (value == 4)
		exit(0);
}

// Function that creates a menu used from a mouse
void subMenu(int value)
{
	if (value == 1) {
		top = false;
		side = false;
		front = !front;
	}
	if (value == 2) {
		top = false;
		side = true;
		right = !right;
	}
	if (value == 3)
		top = true;
}

void key_pressed(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 27: //VK_ESCAPE
		exit(0);
		break;
	case VK_RETURN:
		exit(0);
		break;
	case VK_SPACE:
		mouseMenu(2);
		break;
	case 't':
		glutFullScreenToggle();
		glutWarpPointer(mouseX, mouseY);
		break;
	case 'p':
		GLint pMode[2];
		glGetIntegerv(GL_POLYGON_MODE, pMode);
		if (pMode[0] == GL_LINE)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'w':
		w = true;
		break;
	case 's':
		s = true;
		break;
	case 'a':
		a = true;
		break;
	case 'd':
		d = true;
		break;
	case 'm':
		m = true;
		break;
	case 'n':
		n = true;
		mouseMenu(1);
		break;
	case '1':
		/*if (glIsEnabled(GL_LIGHT0))
			glDisable(GL_LIGHT0);
		else
			glEnable(GL_LIGHT0);*/
		subMenu(1);
		break;
	case '2':
		/*if (glIsEnabled(GL_LIGHT1))
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);*/
		subMenu(2);
		break;
	case '3':
		/*if (glIsEnabled(GL_LIGHT2))
			glDisable(GL_LIGHT2);
		else
			glEnable(GL_LIGHT2);*/
		subMenu(3);
		break;
	};
}

void key_released(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 'w':
		w = false;
		break;
	case 's':
		s = false;
		break;
	case 'a':
		a = false;
		break;
	case 'd':
		d = false;
		break;
	case 'm':
		m = false;
		break;
	case 'n':
		n = false;
		break;
	};
}

void special_pressed(int key, int mouseX, int mouseY)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		up = true;
		break;
	case GLUT_KEY_DOWN:
		down = true;
		break;
	case GLUT_KEY_LEFT:
		lft = true;
		break;
	case GLUT_KEY_RIGHT:
		rgt = true;
		break;
	}
}

void special_released(int key, int mouseX, int mouseY)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		up = false;
		break;
	case GLUT_KEY_DOWN:
		down = false;
		break;
	case GLUT_KEY_LEFT:
		lft = false;
		break;
	case GLUT_KEY_RIGHT:
		rgt = false;
		break;
	}
}

void init(){
	std::srand(std::time(NULL));
	well = TWell(2, 6, 12, 17, 6);
	ball = TBall(3, TVector(0, 0, 25));
	for (TBat& bat : bats) {
		bat = TBat(18, 0, 8, 50, 55, orange);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glLineWidth(3.0);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH); //default GL_SMOOTH
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_NORMALIZE);

	// set lights
	//glLightfv(GL_LIGHT0, GL_AMBIENT, gray3); //def 0,0,0
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, gray); // def 1,1,1, others 0,0,0
	//glLightfv(GL_LIGHT0, GL_SPECULAR, black); // def 1,1,1, others 0,0,0
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02); // def attenuations: 1,0,0
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, gray2);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, gray2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0f);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0002f);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, gray2);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, gray2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0f);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0002f);
	glEnable(GL_LIGHT2);

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black); //ambient light not from light source, def: {0.2,0.2,0.2,1.0}
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //specular from eye, or center of the scene

	glMaterialfv(GL_FRONT, GL_SPECULAR, white); //def 0,0,0
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white); def 0.2/0.8

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilImage image;
	image.Load(L"wood.jpg");
	glGenTextures(1, &wood);
	glBindTexture(GL_TEXTURE_2D, wood);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.Width(), image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

	bats[1].MoveRight(120);
	bats[2].MoveLeft(120);
}

void reshape(int width, int height)
{
	win_width = width;
	win_height = height;
	glViewport(0, 0, win_width, win_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, double(win_width) / double(win_height), 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
	t++;

	if (pause) {
		glutPostRedisplay();
		glutTimerFunc(1000 / fpsCap, timer, 0);
		return;
	}

	if (w) {
		ball.CalculateVelocity(ball.GetVelocity() + TVector(0, 0, -0.2), 1);
	}
	if (s) {
		ball.CalculateVelocity(ball.GetVelocity() + TVector(0, 0, 0.2), 1);
	}
	if (a) {
		ball.CalculateVelocity(ball.GetVelocity() + TVector(-0.2, 0, 0), 1);
	}
	if (d) {
		ball.CalculateVelocity(ball.GetVelocity() + TVector(0.2, 0, 0), 1);
	}
	if (rgt) {
		for (TBat& bat : bats)
			bat.MoveRight(1);
		moving = true;
	}
	else if (lft) {
		for (TBat& bat : bats)
			bat.MoveLeft(1);
		moving = true;
	}
	else
		moving = false;

	bool collision = false;
	double collision_time;
	int col;

	if (moving) {
		col = bats[0].CollisionsNow(ball, ballMoveSpeed);
		if (col > 0);
			//collision = true;
		if (bats[1].CollisionsNow(ball, ballMoveSpeed) > 0);
			//collision = true;
		if (bats[2].CollisionsNow(ball, ballMoveSpeed) > 0);
			//collision = true;
	}
	col = bats[0].Collisions(ball, ballMoveSpeed);
	if (col > 0) {
		bats[0].Reflections(ball, ballMoveSpeed, afterCollisionVelocity, collision_time, col, moving);
		collision = true;
	}
	else {
		col = bats[1].Collisions(ball, ballMoveSpeed);
		if (col > 0) {
			bats[1].Reflections(ball, ballMoveSpeed, afterCollisionVelocity, collision_time, col, moving);
			collision = true;
		}
		else {
			col = bats[2].Collisions(ball, ballMoveSpeed);
			if (col > 0) {
				bats[2].Reflections(ball, ballMoveSpeed, afterCollisionVelocity, collision_time, col, moving);
				collision = true;
			}
		}
	}

	if (!collision)
		if (bounds.Wall_Reflection(ball, ground, ballMoveSpeed, afterCollisionVelocity, collision_time)) {
			// collision with wall detected next step
			collision = true;
	}
	if (!collision) {
		std::pair<int, int> index = well.Collisions(ball, ballMoveSpeed, col);
		if (index.first != -1) {
			well.Reflections(ball, ballMoveSpeed, afterCollisionVelocity, collision_time, col, index);
			collision = true;
			well.DeativateBrick(index);
		}
	}

	if (collision) {
		ball.Move(collision_time);
		ball.CalculateVelocity(afterCollisionVelocity, 1);
		ball.Move(ballMoveSpeed - collision_time);
	}
	else {
		ball.Move(ballMoveSpeed);
	}

	if (!well.State())
		EndGame();
	else
		if (started)
			score++;

	glutPostRedisplay();
	glutTimerFunc(1000 / fpsCap, timer, 0);
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (top) {
		gluLookAt(0, 190, 1, 0, 0, 0, 0, 1, 0);
		glDisable(GL_LIGHT2);
	}
	else {
		glEnable(GL_LIGHT2);
		if (side)
			gluLookAt(right ? 120 : -120, 90, 0, right ? 20 : -20, 0, 0, 0, 1, 0);
		else
			gluLookAt(0, 90, front ? 120 : -120, 0, 0, front ? 20 : -20, 0, 1, 0);
	}
	glRotatef(rot, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1_dir);

	float l2_pos[] = { 0, 40, 80, 1 };
	float l2_dir[] = { 0, -40, -80 };
	if (side) {
		l2_pos[0] = right ? 80.0f : -80.0f;
		l2_pos[2] = 0;
		l2_dir[0] = -l2_pos[0];
		l2_dir[2] = 0;
	}
	else {
		l2_pos[0] = 0;
		l2_pos[2] = front ? 80.0f : -80.0f;
		l2_dir[0] = 0;
		l2_dir[2] = -l2_pos[2];
	}
	glLightfv(GL_LIGHT2, GL_POSITION, l2_pos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l2_dir);

	//draw ground
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 30.0f);
	glColor3fv(white);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood);
	ground.Draw();
	glDisable(GL_TEXTURE_2D);

	//draw ball
	glColor3fv(red2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
	ball.Draw();

	//draw bats
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
	for (TBat& bat : bats)
		bat.Draw();

	glMaterialfv(GL_FRONT, GL_SPECULAR, gray3);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	well.Draw();

	// 2D HUD over 3D scene
	// disable depth buffer and lighting
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);

	// push current projection matrix, set 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, win_width, win_height, 0.0);

	// write score, highscore and help on the screen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3d(1.0, 1.0, 1.0);
	if (lowscore == 0)
		RenderString(win_width * 0.75, win_height * 0.1, "Highscore: -");
	else
		RenderString(win_width * 0.75, win_height * 0.1, "Highscore: " + std::to_string(lowscore / 60) + "," + std::to_string(lowscore / 6 - (lowscore / 60) * 10));
	RenderString(win_width * 0.75, win_height * 0.1 + 30, "Score (time): " + std::to_string(score / 60) + "," + std::to_string(score / 6 - (score / 60) * 10));
	RenderString(win_width * 0.75, win_height * 0.8, "N:");
	RenderString(win_width * 0.75 + 145, win_height * 0.8, "New (reset) game");
	RenderString(win_width * 0.75, win_height * 0.8 + 30, "Space:");
	RenderString(win_width * 0.75 + 145, win_height * 0.8 + 30, "Start/Pause game");
	RenderString(win_width * 0.75, win_height * 0.8 + 60, "Arrow keys:");
	RenderString(win_width * 0.75 + 145, win_height * 0.8 + 60, "Move the bats");
	RenderString(win_width * 0.75, win_height * 0.8 + 90, "Enter/Escape:");
	RenderString(win_width * 0.75 + 145, win_height * 0.8 + 90, "Quit");
	RenderString(win_width * 0.75, win_height * 0.8 + 120, "Right click:");
	RenderString(win_width * 0.75 + 145, win_height * 0.8 + 120, "Menu");
	RenderString(win_width * 0.1, win_height * 0.8, "Change view:");
	RenderString(win_width * 0.11, win_height * 0.8 + 30, "1: Front/Back");
	RenderString(win_width * 0.11, win_height * 0.8 + 60, "2: Right/Left");
	RenderString(win_width * 0.11, win_height * 0.8 + 90, "3: Top");
	RenderString(win_width * 0.11, win_height * 0.8 + 120, "T: Toggle fullcreen");


	// pop perspective projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// enable depth buffer and lighting
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - win_width) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - win_height) / 2);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow("Game");

	// Create sub-menu
	int sub = glutCreateMenu(subMenu);
	glutAddMenuEntry("Front|Back", 1);
	glutAddMenuEntry("Right|Left", 2);
	glutAddMenuEntry("Top", 3);
	
	// Create a mouse menu
	int main = glutCreateMenu(mouseMenu);
	// Add menu entries
	glutAddMenuEntry("New Game", 1);
	glutAddMenuEntry("Start - release the ball!", 2);
	glutAddSubMenu("View", sub);
	glutAddMenuEntry("Quit", 4);
	// Attach menu to mouse right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(render);
	//glutIdleFunc(render);
	glutKeyboardFunc(key_pressed);
	glutKeyboardUpFunc(key_released);
	//glutPassiveMotionFunc(mouse_moved);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special_pressed);
	glutSpecialUpFunc(special_released);
	glutTimerFunc(1000 / fpsCap, timer, 0);

	glutWarpPointer(mouseStartX, mouseStartY);
	//glutSetCursor(GLUT_CURSOR_NONE);

	init();

	//preload_objects();

	glutMainLoop();

	return 0;
}