#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cassert>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Matrix4f.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\string_cast.hpp"
#include "Camera.h"

std::unique_ptr<bool[]> keys = std::make_unique<bool[]>(256);
std::unique_ptr<bool[]> keysSpecial = std::make_unique<bool[]>(256);
Camera camera(Vector3(0.0f, 0.0f, 3.0f));
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool firstMouse = true;
GLfloat lastX = 1920.0f / 2.0f;
GLfloat lastY = 1080.0f / 2.0f;

// Function prototypes
void KeyPressed(unsigned char key, int xmouse, int ymouse)
{
	keys[key] = true;
}

void KeyUp(unsigned char key, int xmouse, int ymouse)
{
	keys[key] = false;
}

void KeySpecial(int key, int xmouse, int ymouse)
{
	keysSpecial[key] = true;
}

void KeySpecialUp(int key, int xmouse, int ymouse)
{
	keysSpecial[key] = false;
}

void keyOperation(void)
{
	if (keys['z'])
		camera.ProcessKeyboard(Camera_movement::FORWARD, deltaTime);
	else if (keys['s'])
		camera.ProcessKeyboard(Camera_movement::BACKWARD, deltaTime);
	else if (keys['q'])
		camera.ProcessKeyboard(Camera_movement::LEFT, deltaTime);
	else if (keys['d'])
		camera.ProcessKeyboard(Camera_movement::RIGHT, deltaTime);
	else if (keys[27])
		exit(0);
}

void keyOperationSpecial(void)
{
	if (keysSpecial[GLUT_KEY_UP])
		camera.ProcessKeyboard(Camera_movement::FORWARD, deltaTime);
	else if (keysSpecial[GLUT_KEY_DOWN])
		camera.ProcessKeyboard(Camera_movement::BACKWARD, deltaTime);
	else if (keysSpecial[GLUT_KEY_LEFT])
		camera.ProcessKeyboard(Camera_movement::LEFT, deltaTime);
	else if (keysSpecial[GLUT_KEY_RIGHT])
		camera.ProcessKeyboard(Camera_movement::RIGHT, deltaTime);
}

void look(int x, int y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	GLfloat deltaX = lastX - x;
	GLfloat deltaY = y - lastY;
	lastX = x;
	lastY = y;
	camera.ProcessMouseMovement(deltaX, deltaY);
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	camera.ProcessMouseScroll(direction);
}

void test_opengl_error() {
	GLenum err = glGetError();
	switch (err) {
	case GL_NO_ERROR: return;
	case GL_INVALID_ENUM:
		std::cerr << "GL_INVALID_ENUM\n";
		break;
	case GL_INVALID_VALUE:
		std::cerr << "GL_INVALID_VALUE\n";
		break;
	case GL_INVALID_OPERATION:
		std::cerr << "GL_INVALID_OPERATION\n";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
		break;
	case GL_OUT_OF_MEMORY:
		std::cerr << "GL_OUT_OF_MEMORY\n";
		break;
	case GL_STACK_UNDERFLOW:
		std::cerr << "GL_STACK_UNDERFLOW\n";
		break;
	case GL_STACK_OVERFLOW:
		std::cerr << "GL_STACK_OVERFLOW\n";
		break;
	default:
		std::cerr << "UNKONWN ERROR\n";
		break;
	}
}

void display() {
	// Set frame time
	GLfloat currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	keyOperation();
	keyOperationSpecial();
    Renderer renderer;
    renderer.clear();
	GLfloat positions[] =
	{
		-0.5f, 0.5f, -0.5f, /*0.0f, 1.0f,*/
		-0.5f, -0.5f, -0.5f, /*0.0f, 0.0f,*/
		0.5f, -0.5f, -0.5f, /*1.0f, 0.0f,*/
		0.5f, 0.5f, -0.5f, /*1.0f, 1.0f,*/

		0.5f, 0.5f, -0.5f, /*0.0f, 1.0f,*/
		0.5f, -0.5f, -0.5f, /*0.0f, 0.0f,*/
		0.5f, -0.5f, 0.5f, /*1.0f, 0.0f,*/
		0.5f, 0.5f, 0.5f, /*1.0f, 1.0f,*/

		0.5f, 0.5f, 0.5f, /*0.0f, 1.0f,*/
		0.5f, -0.5f, 0.5f, /*0.0f, 0.0f,*/
		-0.5f, -0.5f, 0.5f, /*1.0f, 0.0f,*/
		-0.5f, 0.5f, 0.5f, /*1.0f, 1.0f,*/

		-0.5f, 0.5f, 0.5f, /*0.0f, 1.0f,*/
		-0.5f, -0.5f, 0.5f, /*0.0f, 0.0f,*/
		-0.5f, -0.5f, -0.5f, /*1.0f, 0.0f,*/
		-0.5f, 0.5f, -0.5f, /*1.0f, 1.0f,*/

		-0.5f, -0.5f, 0.5f, /*0.0f, 1.0f,*/
		0.5f, -0.5f, 0.5f, /*0.0f, 0.0f,*/
		0.5f, -0.5f, -0.5f, /*1.0f, 0.0f,*/
		-0.5f, -0.5f, -0.5f, /*1.0f, 1.0f,*/

		-0.5f, 0.5f, -0.5f, /*0.0f, 1.0f,*/
		0.5f, 0.5f, -0.5f, /*0.0f, 0.0f,*/
		0.5f, 0.5f, 0.5f, /*1.0f, 0.0f,*/
		-0.5f, 0.5f, 0.5f, /*1.0f, 1.0f*/

	};
	GLuint indices[] =
	{
		// front
		0, 1, 3,
		3, 1, 2,
		// right
		4, 5, 7,
		7, 5, 6,
		// back
		8, 9, 11,
		11, 9, 10,
		// left
		12, 13, 15,
		15, 13, 14,
		// bottom
		16, 17, 19,
		19, 17, 18,
		// top
		20, 21, 23,
		23, 21, 22
	};
	/*Vector3 cubePositions[] =
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(2.0f, 5.0f, -15.0f),
		Vector3(-1.5f, -2.2f, -2.5f),
		Vector3(-3.8f, -2.0f, -12.3f),
		Vector3(2.4f, -0.4f, -3.5f),
		Vector3(-1.7f, 3.0f, -7.5f),
		Vector3(1.3f, -2.0f, -2.5f),
		Vector3(1.5f, 2.0f, -2.5f),
		Vector3(1.5f, 0.2f, -1.5f),
		Vector3(-1.3f, 1.0f, -1.5f)
	};*/
    glEnable(GL_DEPTH_TEST);
    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/



    VertexArray vaBox;
	VertexBuffer vb(positions, 6 * 6 * 3 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<GLfloat>(3);
    //layout.push<GLfloat>(2);
    vaBox.addBuffer(vb, layout);
	IndexBuffer ib(indices, 2 * 3 * 6);

	VertexArray vaLight;
	vaLight.addBuffer(vb, layout);

	Shader lightingShader("lightingVertex.glsl", "lightingFragment.glsl");
	Shader lampShader("lampVertex.glsl", "lampFragment.glsl");


	Matrix4f model(1.0f);
	Matrix4f view(1.0f);
	Matrix4f projection = Matrix4f::gl_perspective(camera.GetZoom(), 1920.0f / 1080.0f, 0.1f, 1000.0f);
	view = camera.get_view_matrix();
    //Texture texture("Mauritius_beach.png");
    //texture.bind();
    lightingShader.bind();
    lightingShader.set_uniform_3f("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader.set_uniform_3f("lightColor", 1.0f, 0.5f, 1.0f);
    lightingShader.set_uniform_mat_4f("view", view);
    lightingShader.set_uniform_mat_4f("projection", projection);
	lightingShader.set_uniform_mat_4f("model", model);
	renderer.draw(vaBox, ib, lightingShader);
	lightingShader.unbind();

	model = Matrix4f::gl_translate(model, Vector3(1.2f, 1.0f, 2.0f));
	model = Matrix4f::gl_scale(model, Vector3(0.2f));
	//Texture texture("Mauritius_beach.png");
	//texture.bind();
	lampShader.bind();
	lampShader.set_uniform_mat_4f("view", view);
	lampShader.set_uniform_mat_4f("projection", projection);
	lampShader.set_uniform_mat_4f("model", model);
	renderer.draw(vaLight, ib, lampShader);
	lampShader.unbind();
    //shader.set_uniform_1i("u_Texture", 0);
    //renderer.draw(va, ib, shader);


    glFinish();
    glutSwapBuffers();
    test_opengl_error();
}

void initGlut(int& argc, char* argv[]) {
    //glewExperimental = GL_TRUE;
    glutInit(&argc, argv);
    glutInitContextVersion(4, 4);
    glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Test");
    glutDisplayFunc(display);
    glutIdleFunc(display);
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(KeySpecial);
	glutSpecialUpFunc(KeySpecialUp);
	//glutMotionFunc(look);
	glutPassiveMotionFunc(look);
	glutMouseWheelFunc(mouseWheel);
}

void initGlew() {
    if (glewInit()) {
        std::cerr << " Error while initializing glew";
    }
}

void initGL() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, 1920, 1080);
    glClearColor(0.0, 0, 0, 1.0);
    test_opengl_error();
}

int main(int argc, char* argv[]) {
    std::cerr << "Glut init\n";
    initGlut(argc, argv);
    std::cerr << "Glut init Ok\n";
    std::cerr << "Glew init\n";
    initGlew();
    std::cerr << "Glew init Ok\n";
    std::cerr << "GL init\n";
    initGL();
    std::cerr << "GL init Ok\n";
    std::cerr << "Start\n";
    glutMainLoop();
    return 0;
}