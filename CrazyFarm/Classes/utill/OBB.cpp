#include"OBB.h"
#include<assert.h>

Projection::Projection(float _min, float _max)
	:min(_min),
	max(_max)
{

}

Projection::~Projection()
{

}

float Projection::getMax() const
{
	return max ;
}

float Projection::getMin() const
{
	return min ;
}

bool Projection::overlap(Projection* proj)
{
	if(min > proj->getMax()) return false ;
	if(max < proj->getMin()) return false ;

	return true ;
}

OBBEX::OBBEX()
{

}

OBBEX::~OBBEX()
{

}
OBBEX::OBBEX(ObbData data)
{
	vertex[0] = data.leftBottom;
	vertex[1] = data.rightBottom;
	vertex[2] = data.rightTop;
	vertex[3] = data.leftTop;
}
OBBEX::OBBEX(Vec2 axie[4])
{
	for (int i = 0; i < 4;i++)
	{
		vertex[i] = axie[i];
	}
}

OBBEX::OBBEX(Vec2 leftBottom, Vec2 rightBottom, Vec2 rightTop, Vec2 leftTop)
{
	vertex[0] = leftBottom;
	vertex[1] = rightBottom;
	vertex[2] = rightTop;
	vertex[3] = leftTop;
}

Vec2 OBBEX::getVertex(int index) const
{
	assert(0 <= index && index <=3 && "The index must be from 0 to 3");
	return vertex[index] ;
}

void OBBEX::setVertex(int index, float x, float y)
{
	assert(0 <= index && index <=3 && "The index must be from 0 to 3");
	vertex[index].x = x ;
	vertex[index].y = y ;
}

void OBBEX::setVertex(int index, Vec2 v)
{
	assert(0 <= index && index <=3 && "The index must be from 0 to 3");
	vertex[index].x = v.x ;
	vertex[index].y = v.y ;
}

void OBBEX::getAxies(Vec2* axie)
{
	for(int i = 0 ; i < 4 ; i ++)
	{
		Vec2 s ;
		s = vertex[i] - vertex[(i + 1) % 4];
		s = s.getNormalized();
		axie[i].x = -s.y ;
		axie[i].y = s.x ;
	}
}

Projection OBBEX::getProjection(Vec2 axie)
{
	float min = vertex[0].dot(axie) ;
	float max = min ;

	for(int i = 1 ; i < 4 ; i ++)
	{
		float temp = vertex[i].dot(axie);
		if(temp > max)
			max = temp ;
		else if(temp < min)
			min = temp ;
	}// end for

	return Projection(min, max);
}

bool OBBEX::isCollidWithOBB(OBBEX obb)
{

	Vec2 * axie1 = new Vec2[4];
	Vec2 * axie2 = new Vec2[4];

	//Get the seperat axie
	getAxies(axie1);
	obb.getAxies(axie2);

	//Check for overlap for all of the axies
	for(int i = 0 ; i < 4 ; i ++)
	{
		Projection p1 = getProjection(axie1[i]);
		Projection p2 = obb.getProjection(axie1[i]);
		
		if(!p1.overlap(&p2))
		
			return false ;
	}
	for(int i = 0 ; i < 4 ; i ++)
	{
		Projection p1 = getProjection(axie2[i]);
		Projection p2 = obb.getProjection(axie2[i]);
		
		if(!p1.overlap(&p2))
			return false ;
	}

	delete[]axie1 ;
	delete[]axie2 ;
return true ;
	
}

bool OBBEX::isCollidWithPoint(Vec2 pos)
{
	bool isCollision = false;
	OBBEX ob = OBBEX(Vec2(pos.x - 1, pos.y - 1), Vec2(pos.x + 1, pos.y - 1), Vec2(pos.x + 1, pos.y + 1), Vec2(pos.x - 1, pos.y + 1));
	if (isCollidWithOBB(ob))
	{
		isCollision = true;
	}
	return isCollision;
}


void OBBEX::draw(Node* parents)
{
	auto node = DrawNode::create();
	node->drawLine(getVertex(0), getVertex(1),Color4F::RED);
	node->drawLine(getVertex(1), getVertex(2), Color4F::RED);
	node->drawLine(getVertex(2), getVertex(3), Color4F::RED);
	node->drawLine(getVertex(3), getVertex(0), Color4F::RED);
	parents->addChild(node, 100);
}