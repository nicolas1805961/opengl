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
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Error.h"
#include "Sphere.h"
#include "Cube.h"
#include "Objects.h"
#include "Plane.h"
#include "Vector4.h"
#include "Ray.h"
#include "Fog.h"
#include "FrameBuffer.h"

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

Objects objects;
std::unique_ptr<bool[]> keys = std::make_unique<bool[]>(256);
std::unique_ptr<bool[]> keysSpecial = std::make_unique<bool[]>(256);
Camera camera(Vector3(0.0f, 0.0f, 3.0f));
GLfloat dt = 0.0f;
GLfloat lastTime = 0.0f;
bool firstMouse = true;
GLfloat lastX = 1920.0f / 2.0f;
GLfloat lastY = 1080.0f / 2.0f;
bool doesIntersect = false;
bool isFirstHit = false;
bool night = false;

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
		camera.ProcessKeyboard(Camera_movement::FORWARD, dt);
	else if (keys['s'])
		camera.ProcessKeyboard(Camera_movement::BACKWARD, dt);
	else if (keys['q'])
		camera.ProcessKeyboard(Camera_movement::LEFT, dt);
	else if (keys['d'])
		camera.ProcessKeyboard(Camera_movement::RIGHT, dt);
	else if (keys[27])
		exit(0);
}

void keyOperationSpecial(void)
{
	if (keysSpecial[GLUT_KEY_UP])
		camera.ProcessKeyboard(Camera_movement::FORWARD, dt);
	else if (keysSpecial[GLUT_KEY_DOWN])
		camera.ProcessKeyboard(Camera_movement::BACKWARD, dt);
	else if (keysSpecial[GLUT_KEY_LEFT])
		camera.ProcessKeyboard(Camera_movement::LEFT, dt);
	else if (keysSpecial[GLUT_KEY_RIGHT])
		camera.ProcessKeyboard(Camera_movement::RIGHT, dt);
	
}

void look(int x, int y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	GLfloat deltaX = x - lastX;
	GLfloat deltaY = lastY - y;
	lastX = x;
	lastY = y;
	camera.ProcessMouseMovement(deltaX, deltaY);
}

void processIntersection(Vector3 const& currentMousePosition, Vector3 const& lastMousePosition, Ray& ray)
{
	doesIntersect = true;
	Vector3 distanceMousePositions = (currentMousePosition - lastMousePosition).normalize();
	if (isnan(distanceMousePositions.get_x()))
	{
		std::cout << "ok\n";
	}
	ray.get_hit()->setTranslation(ray.get_hit()->getTranslation() + distanceMousePositions);
	glutPostRedisplay();
}

void motionFunction(int x, int y)
{
	static Ray lastRay;
	Vector3 mousePosition = camera.get3dMousePosition(x, y);
	static Vector3 lastMousePosition = mousePosition;
	Ray ray(camera.GetPosition(), (mousePosition - camera.GetPosition()).normalize());
	if (objects.trace(ray) && isFirstHit)
	{
		if (doesIntersect && lastRay.get_hit() != ray.get_hit())
		{
			look(x, y);
			lastMousePosition = mousePosition;
			return;
		}
		processIntersection(mousePosition, lastMousePosition, ray);
		lastRay = ray;
	}
	else if (doesIntersect && isFirstHit)
		processIntersection(mousePosition, lastMousePosition, lastRay);
	else
		doesIntersect = false;
	look(x, y);
	lastMousePosition = mousePosition;
}

void idle()
{
	// Set frame time
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);
	dt = currentTime - lastTime;
	lastTime = currentTime;
	/*for (auto const& it : objects.getObjects())
		it.second->updateVelocityAndPosition(dt / 10000.0f);*/
	keyOperation();
	keyOperationSpecial();
	glutPostRedisplay();
}

void click(int button, int state, int x, int y)
{
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
		doesIntersect = false;
	else if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		Vector3 mousePosition = camera.get3dMousePosition(x, y);
		Ray ray(camera.GetPosition(), (mousePosition - camera.GetPosition()).normalize());
		if (objects.trace(ray))
			isFirstHit = true;
		else
			isFirstHit = false;
	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
		night = !night;
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	camera.ProcessMouseScroll(direction);
}



void display() {
	if (night)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	else
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static unsigned int callNumber = 0;
	callNumber++;
	static auto sphereData = Sphere::initializeLayout();
	static auto cubeData = Cube::initializeLayout();
	static auto planeData = Plane::initializeLayout();
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
	
	static Texture texture(Texture::TextureType::DEPTH);
	static FrameBuffer frameBuffer(texture);

	static Shader lampShader("lampVertex.glsl", "lampFragment.glsl", Shader::ShaderType::LAMP);
	static Shader lightingShader("colorVertex.glsl", "colorFragment.glsl", Shader::ShaderType::LIGHTING);
	static Shader depthShader("shadowVertex.glsl", "shadowFragment.glsl", Shader::ShaderType::DEPTH);

	static auto dayTexture = std::make_pair(lightingShader, depthShader);
	static auto nightTexture = std::make_pair(lightingShader, lampShader);
    
	//directional light
    lightingShader.bind();
	Fog fog(lightingShader, 0.05f, 1.5f, Vector3(0.3f), Vector3(0.0f), night);
	DirectionalLight directionalLight(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(2.0f, 2.0f, 2.0f), Vector3(0.5f, 0.5f, 0.5f),
		"dirLight", Vector3(0.0f, -10.0f, 0.0f), night);
	//point light
	PointLight pointLight1(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"pointLights[0]", 1.0f, 0.09f, 0.032f, std::make_shared<Sphere>(Vector3(0.7f, 0.2f, 2.0f), true, 0.05f), night);
	PointLight pointLight2(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"pointLights[1]", 1.0f, 0.09f, 0.032f, std::make_shared<Sphere>(Vector3(2.3f, -3.3f, -4.0f), true, 0.05f), night);
	PointLight pointLight3(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"pointLights[2]", 1.0f, 0.09f, 0.032f, std::make_shared<Sphere>(Vector3(-4.0f, 2.0f, -12.0f), true, 0.05f), night);
	PointLight pointLight4(lightingShader, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f),
		"pointLights[3]", 1.0f, 0.09f, 0.032f, std::make_shared<Sphere>(Vector3(0.0f, 0.0f, -3.0f), true, 0.05f), night);
	//spotlight
	SpotLight spotLight(lightingShader, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), "spotLight",
		Vector3(camera.GetPosition().get_x(), camera.GetPosition().get_y(), camera.GetPosition().get_z()),
		Vector3(camera.getFront().get_x(), camera.getFront().get_y(), camera.getFront().get_z()), cosf(camera.get_radians(12.5f)),
		cosf(camera.get_radians(15.0f)), 1.0f, 0.09f, 0.032f, night);

	Plane plane1(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(0.0f, -10.0f, 0.0f), 20.0f);
	Sphere sphere1(Vector3(0.0f, 0.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(-1.7f, 3.0f, -7.5f));
	Sphere sphere2(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(1.3f, -2.0f, -2.5f));

	auto view = camera.get_view_matrix();
	auto projection = camera.getProjectionMatrix();
	auto viewProjPair = std::make_pair(view, projection);

    lightingShader.set_uniform_3f("viewPos", camera.GetPosition().get_x(), camera.GetPosition().get_y(), camera.GetPosition().get_z());

	objects.addObject(lightingShader, sphereData, std::make_shared<Sphere>(sphere1), "sphere1", night);
	objects.addObject(lightingShader, sphereData, std::make_shared<Sphere>(sphere2), "sphere2", night);
	objects.addObject(lightingShader, planeData, std::make_shared<Plane>(plane1), "plane1", night);
	objects.addObject(lampShader, sphereData, pointLight1.getShape(), "pointLight1", night);
	objects.addObject(lampShader, sphereData, pointLight2.getShape(), "pointLight2", night);
	objects.addObject(lampShader, sphereData, pointLight3.getShape(), "pointLight3", night);
	objects.addObject(lampShader, sphereData, pointLight4.getShape(), "pointLight4", night);

	static Matrix4f shadowProjection = Matrix4f::gl_ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	static Matrix4f shadowView = Matrix4f::gl_look_at(Vector3(-2.0f, 4.0f, -1.0f), Vector3(0.0f, -10.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	static auto shadowMatrices = std::make_pair(shadowView, shadowProjection);

	if (!night)
		objects.drawDay(viewProjPair, shadowMatrices, lightingShader, depthShader, frameBuffer);
	else
		objects.drawNight(viewProjPair, lightingShader, lampShader);


	//lightingShader.unbind();
	/*Matrix4f projection = camera.getProjectionMatrix();
	Matrix4f view = camera.get_view_matrix();
    lightingShader.set_uniform_mat_4f("view", view);
    lightingShader.set_uniform_mat_4f("projection", projection);*/

	/*Cube cube1(Vector3(0.0f, 0.0f, 1.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(0.0f, 0.0f, 0.0f), 1.0f, 20.0f,
		Vector3(1.0f, 0.3f, 0.5f));
	Cube cube2(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.2f, 0.2f, 0.2f), 32.0f, Vector3(2.0f, 5.0f, -15.0f), 0.5f, 40.0f,
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

	/*objects.addObject("cube1", std::make_shared<Cube>(cube1));
	objects.addObject("cube2", std::make_shared<Cube>(cube2));
	objects.addObject("cube3", std::make_shared<Cube>(cube3));
	objects.addObject("cube4", std::make_shared<Cube>(cube4));
	objects.addObject("cube5", std::make_shared<Cube>(cube5));*/
	/*objects.addObject(sphereData, std::make_shared<Sphere>(sphere1));
	objects.addObject(sphereData, std::make_shared<Sphere>(sphere2));
	objects.addObject(planeData, std::make_shared<Plane>(plane1));
	objects.addObject(sphereData, pointLight1.getShape());
	objects.addObject(sphereData, pointLight2.getShape());
	objects.addObject(sphereData, pointLight3.getShape());
	objects.addObject(sphereData, pointLight4.getShape());*/
	/*objects.addObject("sphere3", std::make_shared<Sphere>(sphere3));
	objects.addObject("sphere4", std::make_shared<Sphere>(sphere4));
	objects.addObject("sphere5", std::make_shared<Sphere>(sphere5));*/

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
	glutMouseFunc(click);
	glutPassiveMotionFunc(look);
	glutMotionFunc(motionFunction);
	glutMouseWheelFunc(mouseWheel);
}

void initGlew() {
    if (glewInit()) {
        std::cerr << " Error while initializing glew";
    }
}

void initGL() {
    //glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
    glViewport(0, 0, 1920, 1080);
	/*if (night)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	else
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);*/

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