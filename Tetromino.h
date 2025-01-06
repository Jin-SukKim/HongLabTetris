#pragma once
#include "Rectangle.h"
#include "BlockData.h"

// Tetris의 Block
class Tetromino : public Rectangle
{
public:
	enum class BlockType {
		I,
		J,
		L,
		O,
		S,
		T,
		Z
	};

	Tetromino(BlockType type);

	void Tick(float DeltaTime);

	// 90도 회전
	void RotateRight();
	// -90도 회전
	void RotateLeft();

	void Render(CHAR_INFO* consoleBuffer,int consoleWidth,int consoleHeight) override;
	// Block을 회전이나 이동시킬 다음 위치에 다른 Block이 없는지 확인하는 함수
	bool Collision(const Rectangle& other) override;
private:
	// 일정 시간이 지날때마다 Block이 아래로 내려가도록 타이머 설정
	float _timer = 0.f; 
	BlockType _type;
	static const std::array<char,7> _symbols;
};

