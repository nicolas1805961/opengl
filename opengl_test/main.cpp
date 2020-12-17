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
#include "Grass.h"
#include "Random.h"
#include "Particle.h"
#include "SSBO.h"

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam)
{
	std::cout << "source = " << source << ", type = " << type << ", id = " << id << ", severity = " << severity << ", length = " <<
		length << ", message = " << message << ", userParam = " << userParam << "\n";
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
	static Random rand_generator;
	static Shape sphereData(Sphere::initializeLayout());
	static Shape cubeData(Cube::initializeLayout());
	static Shape planeData(Plane::initializeLayout());
	static Shape screenData(Screen::initializeLayout());
	static Shape grassData(Grass::initializeLayout(rand_generator));
	static SSBO particleData = initializeLayout();
	glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	static Texture textureShadows(Texture::TextureType::DEPTH);
	static Texture textureScene(Texture::TextureType::FULL);
	static FrameBuffer shadowFrameBuffer(textureShadows);
	static FrameBuffer sceneFrameBuffer(textureScene);

	input.addFrameBuffer("shadowFrameBuffer", shadowFrameBuffer);
	input.addFrameBuffer("sceneFrameBuffer", sceneFrameBuffer);


	static Shader lightingShader("lightingVertex.glsl", "lightingFragment.glsl", Shader::ShaderType::LIGHTING);
	static Shader particlesShader("particleVertex.glsl", "particleFragment.glsl", Shader::ShaderType::PARTICLE);
	static Shader computeShader("compute.glsl", Shader::ShaderType::COMPUTE);
	static Shader depthShader("shadowVertex.glsl", "shadowFragment.glsl", Shader::ShaderType::DEPTH);
	static Shader screenShader("renderVertex.glsl", "renderFragment.glsl", Shader::ShaderType::SCREEN);
	static Shader grassShader("grass_vertex.glsl", "geometry_grass.glsl", "lightingFragment.glsl", Shader::ShaderType::GRASS);
	static Shader normalShader("grass_vertex.glsl", "geometry_normal.glsl", "normal_Fragment.glsl", Shader::ShaderType::NORMAL);

	input.addShader(lightingShader);
	input.addShader(computeShader);
	input.addShader(particlesShader);
	input.addShader(grassShader);
	input.addShader(normalShader);
	input.addShader(depthShader);
    
	//Fog fog(dayShader, 0.05f, 1.5f, Vector3(0.3f), Vector3(0.0f), night);
	/*DirectionalLight directionalLight(lightingShader, grassShader, Vector3(0.3f, 0.3f, 0.3f), Vector3(2.0f, 2.0f, 2.0f), Vector3(2.0f, 2.0f, 2.0f),
		"dirLight", Vector3(0.0f, -1.0f, 0.0f));*/
	Lamp lamp1(lightingShader, grassShader, Vector3(100, 100, 100), Vector3(100, 100, 100), Vector3(100, 100, 100),
		"lamps[0]", std::make_shared<Sphere>("Lamp1", Vector3(-10.0f, 0.3f, -1.0f), true, 0.05f));

	Torch torch(lightingShader, Vector3(40.0, 40.0, 40.0), Vector3(40.0, 40.0, 40.0), Vector3(40.0, 40.0, 40.0), "torch",
		Vector3(input.getCamera().getDirection().get_x(), input.getCamera().getDirection().get_y(),
			input.getCamera().getDirection().get_z()), cosf(input.getCamera().toRadian(10.0f)), cosf(input.getCamera().toRadian(20.0f)),
		std::make_shared<Sphere>("Torch", Vector3(input.getCamera().GetPosition().get_x(), input.getCamera().GetPosition().get_y(),
			input.getCamera().GetPosition().get_z()), true, 0.05));

	//auto sphere1 = std::make_shared<Sphere>("sphere1", Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(-2.0f, 20.0f, -10.0f));
	auto plane1 = std::make_shared<Plane>("plane1", Vector3(0.110f, 0.078f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 1.0f);
	auto grass1 = std::make_shared<Grass>("grass1", Vector3(0.0f, 0.3f, 0.0f), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 0.0f), 1.0f);
	//auto cube1 = std::make_shared<Cube>("cube1", Vector3(0.0f, 1.0f, 1.0f), Vector3(3.0, 3.0, 3.0), Vector3(5.0, 20.0, -10.0));

	auto view = input.getCamera().getViewMatrix();
	auto projection = input.getCamera().getProjectionMatrix();
	auto viewProjPair = std::make_pair(view, projection);

	lightingShader.bind();
	lightingShader.set_uniform_1i("night", input.isNight());
	lightingShader.set_uniform_1i("torchOn", input.isTorchOn());
	lightingShader.set_uniform_1i("flashOn", input.isFlashing());
	lightingShader.set_uniform_3f("viewPosition", input.getCamera().GetPosition().get_x(), input.getCamera().GetPosition().get_y(), input.getCamera().GetPosition().get_z());

	grassShader.bind();
	grassShader.set_uniform_1i("night", input.isNight());
	grassShader.set_uniform_1i("torchOn", input.isTorchOn());
	grassShader.set_uniform_1i("flashOn", input.isFlashing());
	grassShader.set_uniform_3f("viewPosition", input.getCamera().GetPosition().get_x(), input.getCamera().GetPosition().get_y(), input.getCamera().GetPosition().get_z());
	
	//input.addIntersection(cube1, *plane1);
	//input.addIntersection(sphere1, *plane1);
	//input.addObject(cube1, cubeData);
	//input.addObject(sphere1, sphereData);
	input.addObject(plane1, planeData);
	input.addObject(grass1, grassData);
	//input.addObject(lamp1.getShape(), sphereData);

	static Matrix4f shadowProjection = Matrix4f::gl_ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 10.0f);
	static Matrix4f shadowView = Matrix4f::gl_look_at(Vector3(1.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	static auto shadowMatrices = std::make_pair(shadowView, shadowProjection);

	input.draw(viewProjPair, shadowMatrices, screenData, screenShader, particleData);

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
	glutInitWindowSize(1024, 1024);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Shader Programming");
	/*glutGameModeString("1920x1080");
	glutEnterGameMode();
	glutReshapeWindow(1920, 1080);*/
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(clickFunction);
	glutPassiveMotionFunc(passiveMotionFunction);
	glutMotionFunc(motionFunction);
	glewInit();
    glutMainLoop();
    return 0;
}