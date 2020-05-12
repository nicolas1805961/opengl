#pragma once

#include <memory>
#include "Vector3.h"
#include "Ray.h"
#include "Manager.h"

class Event
{
public:
	Event(Manager const& manager, Camera const& camera);
	void idle();
	void clickFunction(int button, int state, int x, int y);
	void motionFunction(int x, int y);
	void passiveMotionFunction(int x, int y);
	void keyUp(unsigned char key, int xmouse, int ymouse);
	void keyDown(unsigned char key, int xmouse, int ymouse);
	void addShader(Shader const& shader);
	void addObject(std::shared_ptr<Object> const& object, Shape const& shape);
	void draw(FrameBuffer const& frameBuffer, std::pair<Matrix4f, Matrix4f> const& viewProjMatrices,
		std::pair<Matrix4f, Matrix4f> const& shadowMatrices);
	bool isNight();
	Manager getManager();
	Camera getCamera();
	bool isTorchOn();
	void addIntersection(std::shared_ptr<Object> const& object, Plane const& plane);
	void keepTrack();

private:
	void processIntersection(Vector3 const& currentMousePosition, Vector3 const& lastMousePosition, Ray& ray);
	void keyOperation(void);
	Manager m_manager;
	Camera m_camera;
	float m_dt;
	float m_lastTime;
	bool m_doesIntersect;
	bool m_isRunning;
	bool m_isFirstHit;
	bool m_night;
	bool torchOn;
	std::unique_ptr<bool[]> m_keys;
};