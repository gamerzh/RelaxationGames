#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <string.h>
#include "stdlib.h"
#include "cocos2d.h"
#include "Cell.h"


using namespace std;
class Matrix{
public:
	enum CellType
	{
		TYPE_1=1,
		TYPE_2=2,
		TYPE_3=3,
		TYPE_4=4
	};

	Matrix();
	~Matrix();
	
	static Matrix*getInstance();
	int ROW_NUM;//����
	int COL_NUM;//����
	int MAX_TYPE_NUM;//������������ֵ�����Ԫ������
	void initMatrix();
	bool canRemoveElement(int pos1, int pos2);
	std::vector<Cell*> getMartixCells();//��������
	int getXByCellPosition(int pos);//���ݱ������ȡ�������ϵ�Xֵ
	int getYByCellPosition(int pos);//���ݱ������ȡ�������ϵ�Yֵ
	int getPositionByXAndY(int x, int y);//����������X,��Y��ȷ�����

	bool hasRemoveElement();//���ص�ǰ�������Ƿ��п�����Ԫ��
	void resetMap();//����
	std::vector<int> getRoadChangePos();

	std::vector<int> getTipPOsition();//���������ʾ��Ԫ��
	bool boardLine = false;
private:
	std::vector<int> roadChangePos;//��¼ת�۵�

	static Matrix* instance;
	std::vector<Cell*> myCells;
	bool canReMove(std::vector<Cell*>, int pos1, int pos2);//����Ƿ���Ա���ȥ
	bool canConnectLevel1(std::vector<Cell*>, int x1, int y1, int x2, int y2);//1�����
	bool canConnectLevel2(std::vector<Cell*>, int x1, int y1, int x2, int y2);//2�����
	bool canConnectLevel3(std::vector<Cell*>, int x1, int y1, int x2, int y2);//3�����
	bool canConnectLevel3X(std::vector<Cell*>, int x1, int y1, int x2, int y2);//3��X��
	bool canConnectLevel3Y(std::vector<Cell*>, int x1, int y1, int x2, int y2);//3��Y��
	
};
#endif
