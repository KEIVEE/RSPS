#pragma once
#include "RSP.h"

class Rock; //��ȯ ������ ���� ���� ��ġ. �˻��ؼ� �˾���
//������ϳ��� �����ϸ� �̻��� ���� �߻��Ѵٰ� ��
class Scissors;

class Paper :public RSP {

public:
	Paper();
	Paper(const Paper&);
	Vector2f nearest(vector<Rock>&);
	Vector2f nearest(vector<Scissors>&);
};