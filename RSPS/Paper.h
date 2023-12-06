#pragma once
#include "RSP.h"

class Rock; //순환 참조를 막기 위한 조치. 검색해서 알았음
//헤더파일끼리 참조하면 이상한 일이 발생한다고 함
class Scissors;

class Paper :public RSP {

public:
	Paper();
	Paper(const Paper&, Texture& texturePtr);
	Paper(Vector2f& pos, Texture& texturePtr);
	bool hitby(Scissors& scissors);
	Paper(const Paper&);
	Vector2f nearest(vector<Rock>&);
	Vector2f nearest(vector<Scissors>&);
};