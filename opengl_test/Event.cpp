#include "Event.h"

Event::Event(Manager const& manager, Camera const& camera)
	: m_camera(camera), m_manager(manager), m_lastTime(0.0f), m_night(false), m_isFirstHit(false), m_dt(0.0f), m_doesIntersect(false)
{
	m_keys = std::make_unique<bool[]>(256);
}

void Event::idle()
{
	// Set frame time
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);
	m_dt = currentTime - m_lastTime;
	m_lastTime = currentTime;
	/*for (auto const& it : Manager.getObjects())
		it.second->updateVelocityAndPosition(dt / 10000.0f);*/
	keyOperation();
	glutPostRedisplay();
}

void Event::clickFunction(int button, int state, int x, int y)
{
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
		m_doesIntersect = false;
	else if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		Vector3 mousePosition = m_camera.get3dMousePosition(x, y);
		Ray ray(m_camera.GetPosition(), (mousePosition - m_camera.GetPosition()).normalize());
		if (m_manager.trace(ray))
			m_isFirstHit = true;
		else
			m_isFirstHit = false;
	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
		m_night = !m_night;
}

void Event::motionFunction(int x, int y)
{
	static Ray lastRay;
	Vector3 mousePosition = m_camera.get3dMousePosition(x, y);
	static Vector3 lastMousePosition = mousePosition;
	Ray ray(m_camera.GetPosition(), (mousePosition - m_camera.GetPosition()).normalize());
	if (m_manager.trace(ray) && m_isFirstHit)
	{
		if (m_doesIntersect && lastRay.get_hit() != ray.get_hit())
		{
			passiveMotionFunction(x, y);
			lastMousePosition = mousePosition;
			return;
		}
		processIntersection(mousePosition, lastMousePosition, ray);
		lastRay = ray;
	}
	else if (m_doesIntersect && m_isFirstHit)
		processIntersection(mousePosition, lastMousePosition, lastRay);
	else
		m_doesIntersect = false;
	passiveMotionFunction(x, y);
	lastMousePosition = mousePosition;
}

void Event::processIntersection(Vector3 const& currentMousePosition, Vector3 const& lastMousePosition, Ray& ray)
{
	m_doesIntersect = true;
	Vector3 distanceMousePositions = (currentMousePosition - lastMousePosition).normalize();
	ray.get_hit()->setTranslation(ray.get_hit()->getTranslation() + distanceMousePositions);
	ray.get_hit()->keepTrack();
	glutPostRedisplay();
}

void Event::passiveMotionFunction(int x, int y)
{
	static float lastX = x;
	static float lastY = y;
	GLfloat deltaX = x - lastX;
	GLfloat deltaY = lastY - y;
	lastX = x;
	lastY = y;
	m_camera.updateDirection(deltaX, deltaY);
}

void Event::keyOperation(void)
{
	if (m_keys['z'])
		m_camera.updatePosition(Camera::Mouvement::FORWARD);
	else if (m_keys['s'])
		m_camera.updatePosition(Camera::Mouvement::BACKWARD);
	else if (m_keys['q'])
		m_camera.updatePosition(Camera::Mouvement::LEFT);
	else if (m_keys['d'])
		m_camera.updatePosition(Camera::Mouvement::RIGHT);
	else if (m_keys[27])
		exit(0);
}

void Event::keyUp(unsigned char key, int xmouse, int ymouse)
{
	m_keys[key] = false;
}

void Event::keyDown(unsigned char key, int xmouse, int ymouse)
{
	m_keys[key] = true;
}

void Event::addShader(Shader const& shader)
{
	m_manager.addShader(shader);
}

void Event::addObject(std::shared_ptr<Object> const& object, Shape const& shape)
{
	m_manager.addObject(object, shape);
}

void Event::draw(FrameBuffer const& frameBuffer, std::pair<Matrix4f, Matrix4f> const& viewProjMatrices,
	std::pair<Matrix4f, Matrix4f> const& shadowMatrices)
{
	m_manager.draw(frameBuffer, viewProjMatrices, shadowMatrices, m_night);
}

bool Event::isNight()
{
	return m_night;
}

Manager Event::getManager()
{
	return m_manager;
}

Camera Event::getCamera()
{
	return m_camera;
}

void Event::keepTrack()
{
	static unsigned int callNumber = 0;
	callNumber++;
	if (callNumber <= 1)
		m_manager.keepTrack();
}
