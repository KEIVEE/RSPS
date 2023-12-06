#pragma once
#include "RSP.h"

class Rock; //��ȯ ������ ���� ���� ��ġ. �˻��ؼ� �˾���
//������ϳ��� �����ϸ� �̻��� ���� �߻��Ѵٰ� ��
class Scissors;

class Paper :public RSP {
public:
	Paper();
	Paper(const Paper&, Texture& texturePtr);
	Paper(Vector2f& pos, Texture& texturePtr);
	bool hitby(Scissors& scissors);
	Vector2f nearest(vector<Rock>&);
	Vector2f nearest(vector<Scissors>&);
};