#pragma once
class Intersect
{
public:
	Intersect(bool doesIntersect, float distance);
private:
	bool m_doesIntersect;
	float m_distance;
};