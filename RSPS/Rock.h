#pragma once
#include "RSP.h"

class Paper;
class Scissors;

class Rock :public RSP {

public:
	Rock();
	Rock(const Rock&);
	bool hitby(Paper& paper);
	Vector2f nearest(vector<Scissors>&);//��ġ�� �ƴ� �� ��ü ���� ���̸�ŭ.
	Vector2f nearest(vector<Paper>&);//��ġ�� �ƴ� �� ��ü ���� ���̸�ŭ.
};