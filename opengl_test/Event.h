#pragma once

#include <memory>
#include "Vector3.h"
#include "Ray.h"
#include "Manager.h"
#include "Camera.h"

class Event
{
public:
	Event();
	void idle();
	void clickFunction(int button, int state, int x, int y);
	void motionFunction(int x, int y);
	void passiveMotionFunction(int x, int y);
	void keyUp(unsigned char key, int xmouse, int ymouse);
	void keyDown(unsigned char key, int xmouse, int ymouse);
	void addShader(Shader const& shader);
	void addObject(std::shared_ptr<Object> const& object, Shape const& shape);
	void draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
		Shape const& screenData, Shader const& screenShader);
	bool isNight();
	Manager getManager();
	Camera getCamera();
	bool isTorchOn();
	bool isFlashing();
	void addIntersection(std::shared_ptr<Object> const& object, Plane const& plane);
	void addFrameBuffer(std::string const& name, FrameBuffer const& frameBuffer);
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
	bool torchOn;
	float m_grass_height;
	bool m_isFlashing;
	bool m_show_normals;
	std::unique_ptr<bool[]> m_keys;
};