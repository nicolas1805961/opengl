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
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Error.h"
#include "Sphere.h"
#include "Cube.h"

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam)
{
	std::string msgSource;
	switch (source) {
	case GL_DEBUG_SOURCE_API:
		msgSource = "WINDOW_SYSTEM";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		msgSource = "SHADER_COMPILER";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		msgSource = "THIRD_PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		msgSource = "APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		msgSource = "OTHER";
		break;
	}

	std::string msgType;
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		msgType = "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		msgType = "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		msgType = "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		msgType = "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		msgType = "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		msgType = "OTHER";
		break;
	}

	std::string msgSeverity;
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		msgSeverity = "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		msgSeverity = "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		msgSeverity = "HIGH";
		break;
	}

	printf("glDebugMessage:\n%s \n type = %s source = %s severity = %s\n", message, msgType.c_str(), msgSource.c_str(), msgSeverity.c_str());
}

std::unique_ptr<bool[]> keys = std::make_unique<bool[]>(256);
std::unique_ptr<bool[]> keysSpecial = std::make_unique<bool[]>(256);
Camera camera(Vector3(0.0f, 0.0f, 3.0f));
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool firstMouse = true;
GLfloat lastX = 1920.0f / 2.0f;
GLfloat lastY = 1080.0f / 2.0f;

//Vector3 lightPosition(1.2f, 1.0f, 2.0f);

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

void idle()
{
	// Set frame time
	GLfloat currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	keyOperation();
	keyOperationSpecial();
	glutPostRedisplay();
}

void look(int x, int y)
{
	/*if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}*/
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



void display() {
	static int x = 0;
	x++;
	Renderer renderer;
	renderer.clear();
	//lightPosition[0] -= 0.001f;
	//lightPosition[2] -= 0.001f;
	glEnable(GL_DEPTH_TEST);
	/*Vector3 cubePositions[] =
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(2.0f, 5.0f, -15.0f),
		Vector3(-1.5f, -2.2f, -2.5f),
		Vector3(-3.8f, -2.0f, -12.3f),
		Vector3(2.4f, -0.4f, -3.5f)
	};*/

	/*Vector3 spherePositions[] =
	{
		Vector3(-1.7f, 3.0f, -7.5f),
		Vector3(1.3f, -2.0f, -2.5f),
		Vector3(1.5f, 2.0f, -2.5f),
		Vector3(1.5f, 0.2f, -1.5f),
		Vector3(-1.3f, 1.0f, -1.5f)
	};*/

	// Positions of the point lights
	Vector3 pointLightPositions[] = {
		Vector3(0.7f,  0.2f,  2.0f),
		Vector3(2.3f, -3.3f, -4.0f),
		Vector3(-4.0f,  2.0f, -12.0f),
		Vector3(0.0f,  0.0f, -3.0f)
	};
    
    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

    //VertexArray vaBox;
	//VertexBuffer vb(positions, 8 * 4 * 6 * sizeof(float));
    //VertexBufferLayout layoutBox(3, 3, 2);
    /*layoutBox.push<GLfloat>(3);
    layoutBox.push<GLfloat>(3);
    layoutBox.push<GLfloat>(2);*/
    //vaBox.addBuffer(vb, layoutBox);
	//IndexBuffer ib(indices, 2 * 3 * 6);

	//VertexArray vaLight(vb, layoutBox);
	//vaLight.addBuffer(vb, layoutBox);

	/*Shader lightingShader("lightingVertex.glsl", "lightingFragment.glsl");
	Shader lampShader("lampVertex.glsl", "lampFragment.glsl");*/

	/*static Texture textureDiffuse("container2.png");
	static Texture textureSpecular("container2_specular.png");*/
	
	Shader lampShader("lampVertex.glsl", "lampFragment.glsl");
	Shader lightingShader("colorVertex.glsl", "colorFragment.glsl");
    
    lightingShader.bind();
	Sphere::initializeLayout();
	Cube::initializeLayout();
	//directional light
	DirectionalLight directionalLight(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.4f, 0.4f, 0.4f), Vector3(0.5f, 0.5f, 0.5f),
		"dirLight", Vector3(-0.2f, -1.0f, -0.3f));
	//point light 1
	PointLight pointLight1(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(4.0f, 4.0f, 4.0f), "pointLights[0]",
		Vector3(pointLightPositions[0].get_x(), pointLightPositions[0].get_y(), pointLightPositions[0].get_z()), 1.0f, 0.09f, 0.032f);
	//point light 2
	PointLight pointLight2(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(4.0f, 4.0f, 4.0f), "pointLights[1]",
		Vector3(pointLightPositions[1].get_x(), pointLightPositions[1].get_y(), pointLightPositions[1].get_z()), 1.0f, 0.09f, 0.032f);
	//point light 3
	PointLight pointLight3(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(4.0f, 4.0f, 4.0f), "pointLights[2]",
		Vector3(pointLightPositions[2].get_x(), pointLightPositions[2].get_y(), pointLightPositions[2].get_z()), 1.0f, 0.09f, 0.032f);
	//point light 4
	PointLight pointLight4(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(4.0f, 4.0f, 4.0f), "pointLights[3]",
		Vector3(pointLightPositions[3].get_x(), pointLightPositions[3].get_y(), pointLightPositions[3].get_z()), 1.0f, 0.09f, 0.032f);
	//spotlight
	SpotLight spotLight(lightingShader, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), "spotLight",
		Vector3(camera.GetPosition().get_x(), camera.GetPosition().get_y(), camera.GetPosition().get_z()),
		Vector3(camera.getFront().get_x(), camera.getFront().get_y(), camera.getFront().get_z()), cosf(camera.get_radians(12.5f)),
		cosf(camera.get_radians(15.0f)), 1.0f, 0.09f, 0.032f);

    lightingShader.set_uniform_3f("viewPos", camera.GetPosition().get_x(), camera.GetPosition().get_y(), camera.GetPosition().get_z());

	Matrix4f projection = Matrix4f::gl_perspective(camera.GetZoom(), 1920.0f / 1080.0f, 0.1f, 1000.0f);
	Matrix4f view = camera.get_view_matrix();
    lightingShader.set_uniform_mat_4f("view", view);
    lightingShader.set_uniform_mat_4f("projection", projection);

	/*textureDiffuse.bind();
	textureSpecular.bind(1);*/
	/*Cube cube1(lightingShader, "material", Vector3(0.0f, 0.0f, 1.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(0.0f, 0.0f, 0.0f),
		1.0f, 20.0f, Vector3(1.0f, 0.3f, 0.5f));
	cube1.draw();
	Cube cube2(lightingShader, "material", Vector3(0.0f, 1.0f, 0.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(2.0f, 5.0f, -15.0f),
		0.5f, 40.0f, Vector3(1.0f, 0.3f, 0.5f));
	cube2.draw();
	Cube cube3(lightingShader, "material", Vector3(1.0f, 0.0f, 0.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(1.5f, 2.0f, -2.5f),
		0.75f, 60.0f, Vector3(1.0f, 0.3f, 0.5f));
	cube3.draw();
	Cube cube4(lightingShader, "material", Vector3(0.3f, 0.2f, 0.75f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(-3.8f, -2.0f, -12.3f),
		1.2f, 80.0f, Vector3(1.0f, 0.3f, 0.5f));
	cube4.draw();
	Cube cube5(lightingShader, "material", Vector3(0.4f, 0.75f, 0.85f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(2.4f, -0.4f, -3.5f),
		0.25f, 100.0f, Vector3(1.0f, 0.3f, 0.5f));
	cube5.draw();*/
	/*for(unsigned int i = 0; i < 5; i++)
	{
		model = Matrix4f(1.0f);
		model = Matrix4f::gl_translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = Matrix4f::gl_rotate(model, camera.get_radians(angle), Vector3(1.0f, 0.3f, 0.5f));
		lightingShader.set_uniform_mat_4f("model", model);
		cube.draw();
		//renderer.draw(vaBox, ib, lightingShader);
	}*/

	Sphere sphere1(lightingShader, "material", Vector3(0.0f, 0.0f, 1.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(-1.7f, 3.0f, -7.5f),
		0.5f);
	sphere1.draw();
	Sphere sphere2(lightingShader, "material", Vector3(0.0f, 1.0f, 0.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(-1.7f, 4.2f, -7.5f),
		0.7f);
	sphere2.draw();
	/*Sphere sphere3(lightingShader, "material", Vector3(1.0f, 0.0f, 0.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(1.5f, 2.0f, -2.5f),
		0.75f);
	sphere3.draw();
	Sphere sphere4(lightingShader, "material", Vector3(0.3f, 0.2f, 0.75f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(1.5f, 0.2f, -1.5f),
		1.2f);
	sphere4.draw();
	Sphere sphere5(lightingShader, "material", Vector3(0.4f, 0.75f, 0.85f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(-1.3f, 1.0f, -1.5f),
		0.25f);
	sphere5.draw();*/
	/*for (unsigned int i = 0; i < 5; i++)
	{
		model = Matrix4f(1.0f);
		model = Matrix4f::gl_translate(model, spherePositions[i]);
		lightingShader.set_uniform_mat_4f("model", model);
		sphere.draw();
		//renderer.draw(vaBox, ib, lightingShader);
	}*/

	/*textureDiffuse.bind();
	textureSpecular.bind(1);

	renderer.draw(vaBox, ib, lightingShader);*/
	lightingShader.unbind();
	/*textureDiffuse.unbind();
	textureSpecular.unbind();*/

	/*model = Matrix4f::gl_translate(model, lightPosition);
	model = Matrix4f::gl_scale(model, Vector3(0.01f));*/
	lampShader.bind();
	lampShader.set_uniform_mat_4f("view", view);
	lampShader.set_uniform_mat_4f("projection", projection);
	//lampShader.set_uniform_mat_4f("model", model);
	Matrix4f model(1.0f);
	for (GLuint i = 0; i < 4; i++)
	{
		model = Matrix4f(1.0f);
		model = Matrix4f::gl_translate(model, pointLightPositions[i]);
		model = Matrix4f::gl_scale(model, Vector3(0.05f)); // Make it a smaller cube
		lampShader.set_uniform_mat_4f("model", model);
		sphere1.draw(lampShader);
		//renderer.draw(vaLight, ib, lampShader);
	}

	//renderer.draw(vaLight, ib, lampShader);
	lampShader.unbind();

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugCallback, NULL);

    glFinish();
    glutSwapBuffers();
}

void initGlut(int& argc, char* argv[]) {
    glewExperimental = GL_TRUE;
    glutInit(&argc, argv);
    glutInitContextVersion(4, 4);
    glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Test");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
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
    //test_opengl_error();
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