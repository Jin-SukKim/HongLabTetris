#pragma once
#include <Windows.h>
#include <vector>
#include <array>
#include "Cell.h"

class Rectangle
{
public:
	Rectangle(int width = 0,int height = 0);
	Rectangle(int width,int height, std::vector<Cell> rect);

	// Board 초기화
	virtual void Clear();

	void SetPos(int x,int y) { _x = x; _y = y; }
	int GetPosX() const { return _x; }
	int GetPosY() const { return _y; }

	void SetCell(int x,int y,const Cell& cell);
	Cell GetCell (int x,int y) const;

	int GetWidth() const { return _width; }
	int GetHeight() const {	return _height;	}
	
	// ConsoleBuffer를 사용해서 Rendering할 경우 사용
	virtual void Render(CHAR_INFO* consoleBuffer,int consoleWidth,int consoleHeight);
	
	virtual bool Collision(const Rectangle& other) = 0;
	bool CheckCellCollision(const Rectangle& other) const;
protected:
	// Console에서의 위치
	int _x = 0;
	int _y = 0;
	
	// Rectangle의 정보
	int _width = 0;
	int _height = 0;
	std::vector<Cell> _rect;

	static const std::array<char,3> _val;
};

