#pragma once
#include "cocos2d.h"
using namespace cocos2d;



struct ObbData
{
	Vec2 leftBottom;
	Vec2 rightBottom;
	Vec2 rightTop;
	Vec2 leftTop;
};


class Projection
{
public:
	Projection(float min, float max);
	~Projection();

public:
	bool overlap(Projection* proj);

public:
	float getMin() const;
	float getMax() const ;

private:
	float min ;
	float max ;
};

class OBBEX
{
public:
	OBBEX();
	~OBBEX();
	OBBEX(ObbData data);
	OBBEX(Vec2 axie[4]);
	OBBEX(Vec2 leftBottom, Vec2 rightBottom, Vec2 rightTop, Vec2 leftTop);
public:
	void getAxies(Vec2 * axie);
	Projection getProjection(Vec2 axie);
	void draw(Node* parents);
public:
	Vec2 getVertex(int index) const;
	void setVertex(int index, float x, float y);
	void setVertex(int index, Vec2 v);

public:
	bool isCollidWithOBB(OBBEX obb);
	bool isCollidWithPoint(Vec2 pos);
private:
	Vec2 vertex[4];
};