#pragma once
#include <vector>

// 테트리스의 기반이 되는 Board 클래스
class Board
{
public:
	enum class CellState {
		Empty = 0,
		Border,
		Block
	};
	
	Board(int width, int height);
	
	void SetState(int x, int y, const CellState& state);
	CellState GetState(int x, int y) const;

	// board에서 Block으로 꽉 찬 줄의 개수 파악 및 꽉 찬 줄은 삭제
	int CheckFullLines();
private:
	// 한 줄이 꽉찼는지 확인
	bool isFullLine(int y);
	// 한 줄 삭제
	void removeLine(int y);
	// y번째 줄 위의 모든 Block을 아래로 한칸씩 이동
	void moveBlockDown(int y);


private:
	int _width = 0;
	int _height = 0;
	std::vector<CellState> _board;
};

