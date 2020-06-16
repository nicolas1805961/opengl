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
#include "Texture.h"
#include "Matrix4f.h"
#include "DirectionalLight.h"
#include "Lamp.h"
#include "Torch.h"
#include "Error.h"
#include "Sphere.h"
#include "Cube.h"
#include "Manager.h"
#include "Plane.h"
#include "Vector4.h"
#include "Ray.h"
#include "Fog.h"
#include "FrameBuffer.h"
#include "Camera.h"
#include "Event.h"
#include "Screen.h"

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

Event input;
void idle()
{
	input.idle();
}
void clickFunction(int button, int state, int x, int y)
{
	input.clickFunction(button, state, x, y);
}
void motionFunction(int x, int y)
{
	input.motionFunction(x, y);
}
void passiveMotionFunction(int x, int y)
{
	input.passiveMotionFunction(x, y);
}
void keyUp(unsigned char key, int xmouse, int ymouse)
{
	input.keyUp(key, xmouse, ymouse);
}
void keyDown(unsigned char key, int xmouse, int ymouse)
{
	input.keyDown(key, xmouse, ymouse);
}

void display() {
	if (input.isNight())
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	else
		glClearColor(0.37f, 0.65f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static unsigned int callNumber = 0;
	callNumber++;
	static Shape sphereData(Sphere::initializeLayout());
	static Shape cubeData(Cube::initializeLayout());
	static Shape planeData(Plane::initializeLayout());
	static Shape screenData(Screen::initializeLayout());
	glEnable(GL_DEPTH_TEST);

	Vector3 pointLightPositions[] = {
		Vector3(0.7f,  0.2f,  2.0f),
		Vector3(2.3f, -3.3f, -4.0f),
		Vector3(-4.0f,  2.0f, -12.0f),
		Vector3(0.0f,  0.0f, -3.0f)
	};
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	static Texture textureShadows(Texture::TextureType::DEPTH);
	static Texture textureScene(Texture::TextureType::FULL);
	static FrameBuffer shadowFrameBuffer(textureShadows);
	static FrameBuffer sceneFrameBuffer(textureScene);

	input.addFrameBuffer("shadowFrameBuffer", shadowFrameBuffer);
	input.addFrameBuffer("sceneFrameBuffer", sceneFrameBuffer);

	static Shader lightingShader("lightingVertex.glsl", "lightingFragment.glsl", Shader::ShaderType::LIGHTING);
	static Shader depthShader("shadowVertex.glsl", "shadowFragment.glsl", Shader::ShaderType::DEPTH);
	static Shader screenShader("renderVertex.glsl", "renderFragment.glsl", Shader::ShaderType::SCREEN);

	input.addShader(lightingShader);
	input.addShader(depthShader);
    
	//Fog fog(dayShader, 0.05f, 1.5f, Vector3(0.3f), Vector3(0.0f), night);
	DirectionalLight directionalLight(lightingShader, Vector3(0.3f, 0.3f, 0.3f), Vector3(2.0f, 2.0f, 2.0f), Vector3(2.0f, 2.0f, 2.0f),
		"dirLight", Vector3(0.0f, -1.0f, 0.0f));
	//point light
	Lamp lamp1(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"lamps[0]", 1.0f, 0.1f, 0.03f, std::make_shared<Sphere>("Lamp1", Vector3(1.0f, 4.0f, -7.0f), true, 0.05f));
	/*PointLight pointLight2(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"pointLights[1]", 1.0f, 0.1f, 0.03f, std::make_shared<Sphere>("PointLight2", Vector3(2.3f, 3.3f, -4.0f), true, 0.05f));
	PointLight pointLight3(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"pointLights[2]", 1.0f, 0.1f, 0.03f, std::make_shared<Sphere>("PointLight3", Vector3(-4.0f, 4.0f, -12.0f), true, 0.05f));
	PointLight pointLight4(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"pointLights[3]", 1.0f, 0.1f, 0.03f, std::make_shared<Sphere>("PointLight4", Vector3(0.0f, 3.0f, -3.0f), true, 0.05f));
	PointLight pointLight5(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"pointLights[4]", 1.0f, 0.1f, 0.03f, std::make_shared<Sphere>("PointLight5", Vector3(2.0f, 3.0f, -3.0f), true, 0.05f));*/

	Torch torch(lightingShader, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), "torch",
		Vector3(input.getCamera().GetPosition().get_x(), input.getCamera().GetPosition().get_y(), input.getCamera().GetPosition().get_z()),
		Vector3(input.getCamera().getDirection().get_x(), input.getCamera().getDirection().get_y(), input.getCamera().getDirection().get_z()),
		cosf(input.getCamera().toRadian(10.0f)), cosf(input.getCamera().toRadian(20.0f)), 1.0f, 0.01f, 0.003f);

	//Cube cube1("cube1", Vector3(0.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(5.0, 1.0, -10.0));
	//Plane plane1("plane1", Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 20.0f);
	auto sphere1 = std::make_shared<Sphere>("sphere1", Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(-2.0f, 20.0f, -10.0f));
	auto plane1 = std::make_shared<Plane>("plane1", Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 20.0f);
	auto cube1 = std::make_shared<Cube>("cube1", Vector3(0.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(5.0, 20.0, -10.0));
	//Sphere sphere1("sphere1", Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(-2.0f, 10.0f, -10.0f));
	//Sphere sphere2("sphere2", Vector3(0.0f, 0.0f, 1.0f), Vector3(0.3f, 0.3f, 0.3f), Vector3(2.0f, 1.0f, -10.0f));

	auto view = input.getCamera().getViewMatrix();
	auto projection = input.getCamera().getProjectionMatrix();
	auto viewProjPair = std::make_pair(view, projection);

    lightingShader.bind();
	lightingShader.set_uniform_1i("night", input.isNight());
	lightingShader.set_uniform_1i("torchOn", input.isTorchOn());
	lightingShader.set_uniform_1i("flashOn", input.isFlashing());
	lightingShader.set_uniform_3f("viewPosition", input.getCamera().GetPosition().get_x(), input.getCamera().GetPosition().get_y(), input.getCamera().GetPosition().get_z());

	input.addIntersection(cube1, *plane1);
	input.addIntersection(sphere1, *plane1);
	//input.addObject(std::make_shared<Cube>(cube1), cubeData);
	input.addObject(cube1, cubeData);
	input.addObject(sphere1, sphereData);
	//input.addObject(std::make_shared<Sphere>(sphere2), sphereData);
	input.addObject(plane1, planeData);
	input.addObject(lamp1.getShape(), sphereData);
	/*input.addObject(pointLight2.getShape(), sphereData);
	input.addObject(pointLight3.getShape(), sphereData);
	input.addObject(pointLight4.getShape(), sphereData);
	input.addObject(pointLight5.getShape(), sphereData);*/

	static Matrix4f shadowProjection = Matrix4f::gl_ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 10.0f);
	static Matrix4f shadowView = Matrix4f::gl_look_at(Vector3(1.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	static auto shadowMatrices = std::make_pair(shadowView, shadowProjection);

	input.draw(viewProjPair, shadowMatrices, screenData, screenShader);


	//dayShader.unbind();
	/*Matrix4f projection = camera.getProjectionMatrix();
	Matrix4f view = camera.get_view_matrix();
    dayShader.set_uniform_mat_4f("view", view);
    dayShader.set_uniform_mat_4f("projection", projection);*/

	/*Cube cube2(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(2.0f, 5.0f, -15.0f), 0.5f, 40.0f,
		Vector3(1.0f, 0.3f, 0.5f));
	Cube cube3(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(-1.5f, -2.2f, -2.5f), 0.75f, 60.0f,
		Vector3(1.0f, 0.3f, 0.5f));
	Cube cube4(Vector3(0.3f, 0.2f, 0.75f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(-3.8f, -2.0f, -12.3f), 1.2f, 80.0f,
		Vector3(1.0f, 0.3f, 0.5f));
	Cube cube5(Vector3(0.4f, 0.75f, 0.85f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(2.4f, -0.4f, -3.5f), 0.25f, 100.0f,
		Vector3(1.0f, 0.3f, 0.5f));*/

	//Vector3(-1.7f, 3.0f, -7.5f)

	/*Sphere sphere3(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(1.5f, 2.0f, -2.5f), 0.5f);
	Sphere sphere4(Vector3(0.3f, 0.2f, 0.75f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(1.5f, 0.2f, -1.5f), 1.2f);
	Sphere sphere5(Vector3(0.4f, 0.75f, 0.85f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(-1.3f, 1.0f, -1.5f), 0.25f);*/

	/*Manager.addObject("cube1", std::make_shared<Cube>(cube1));
	Manager.addObject("cube2", std::make_shared<Cube>(cube2));
	Manager.addObject("cube3", std::make_shared<Cube>(cube3));
	Manager.addObject("cube4", std::make_shared<Cube>(cube4));
	Manager.addObject("cube5", std::make_shared<Cube>(cube5));*/
	/*Manager.addObject(sphereData, std::make_shared<Sphere>(sphere1));
	Manager.addObject(sphereData, std::make_shared<Sphere>(sphere2));
	Manager.addObject(planeData, std::make_shared<Plane>(plane1));
	Manager.addObject(sphereData, pointLight1.getShape());
	Manager.addObject(sphereData, pointLight2.getShape());
	Manager.addObject(sphereData, pointLight3.getShape());
	Manager.addObject(sphereData, pointLight4.getShape());*/
	/*Manager.addObject("sphere3", std::make_shared<Sphere>(sphere3));
	Manager.addObject("sphere4", std::make_shared<Sphere>(sphere4));
	Manager.addObject("sphere5", std::make_shared<Sphere>(sphere5));*/

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugCallback, NULL);

    glFinish();
    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glewExperimental = GL_TRUE;
	glutInit(&argc, argv);
	glutInitContextVersion(4, 4);
	glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_DEBUG);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	/*glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Test");*/
	glutGameModeString("1920x1080");
	glutEnterGameMode();
	glutReshapeWindow(1920, 1080);
	//glutFullScreen();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	//glutSpecialFunc(KeySpecial);
	//glutSpecialUpFunc(KeySpecialUp);
	glutMouseFunc(clickFunction);
	glutPassiveMotionFunc(passiveMotionFunction);
	glutMotionFunc(motionFunction);
	//glutMouseWheelFunc(mouseWheel);
	glewInit();
    glutMainLoop();
    return 0;
}