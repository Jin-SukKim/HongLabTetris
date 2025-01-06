#include "Board.h"

Board::Board(int width, int height) : Rectangle(width, height)
{
}

void Board::Init()
{
    // 왼쪽, 오른쪽 벽 설정
    for (int y = 0; y < _height; ++y) {
        SetCell(0, y, Cell::Border);  // 왼쪽 벽
        SetCell(_width - 1, y, Cell::Border);  // 오른쪽 벽
    }

    // 바닥 설정
    for (int x = 0; x < _width; ++x)
        SetCell(x, _height - 1, Cell::Border);
}

void Board::Clear()
{
    Rectangle::Clear();
    Init();
}

int Board::CheckFullLines()
{
    int count = 0;
    for (int y = _height - 2; y >= 0; --y) {
        // 한 줄이 Block으로 꽉찼다면 Count + 1
        if (isFullLine(y)) {
            count++;
            removeLine(y); // 한 줄을 지우고
            moveBlockDown(y); // y줄 위의 block을 한 칸씩 내리기
        }
    }

    return count;
}

bool Board::Collision(const Rectangle& other)
{
    // Board는 Border와 Block에 대해서만 충돌 검사
    int otherWidth = other.GetWidth();
    int otherHeight = other.GetHeight();
    int otherStartX = other.GetPosX() - otherWidth / 2;
    int otherStartY = other.GetPosY() - otherHeight / 2;

    // other의 각 셀에 대해
    for(int y = 0; y < otherHeight; ++y) {
        for(int x = 0; x < otherWidth; ++x) {
            // other의 빈 셀은 무시
            if(other.GetCell(x,y).Type == CellType::Empty)
                continue;

            // Board에서의 위치 계산
            int boardX = otherStartX + x;
            int boardY = otherStartY + y;

            // Board 범위 밖이면 충돌
            if(boardX < 0 || boardX >= _width ||
               boardY < 0 || boardY >= _height)
                return true;

            // Board의 해당 위치에 Border나 Block이 있으면 충돌
            Cell boardCell = GetCell(boardX,boardY);
            if(boardCell.Type == CellType::Border ||
               boardCell.Type == CellType::Block)
                return true;
        }
    }
    return false;
}

bool Board::isFullLine(int y)
{
    int x = 1;
    for (; x < _width - 1; ++x) {
        if (GetCell(x, y).Type != CellType::Block)
            return false;
    }
    return true;
}

void Board::removeLine(int y)
{
    for (int x = 1; x < _width - 1; ++x)
        SetCell(x, y, Cell::Empty);
}

void Board::moveBlockDown(int y)
{
    // y번째 줄 위로 모두 한 칸씩 내리기
    for (int ty = y; ty > 0; --ty) {
        for (int x = 1; x < _width - 1; ++x) {
            // 윗줄의 상태를 현재 줄로 복사
            SetCell(x, ty, GetCell(x, ty - 1));
        }
    }

    // 최상단 줄은 비움
    for (int x = 1; x < _width - 1; ++x) {
        SetCell(x, 0, Cell::Empty);
    }
}
