#pragma once
#include "RSP.h"
#include "Paper.h"
class Rock :public RSP {

public:
	Rock();
	Rock(const Rock&);
	bool hitby(Paper& paper);
	Vector2f nearest(vector<Paper>&);//��ġ�� �ƴ� �� ��ü ���� ���̸�ŭ.
};