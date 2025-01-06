#pragma once
#include "Rectangle.h"

// 테트리스의 기반이 되는 Board 클래스
class Board : public Rectangle
{
public:
	Board(int width, int height);
	
	// Board 초기화
	void Init();
	void Clear() override;

	// board에서 Block으로 꽉 찬 줄의 개수 파악 및 꽉 찬 줄은 삭제
	int CheckFullLines();
	// Board의 내부에서 Block이 Border에 부딪히는지 확인
	bool Collision(const Rectangle& other) override;
private:
	// 한 줄이 꽉찼는지 확인
	bool isFullLine(int y);
	// 한 줄 삭제
	void removeLine(int y);
	// y번째 줄 위의 모든 Block을 아래로 한칸씩 이동
	void moveBlockDown(int y);

};

