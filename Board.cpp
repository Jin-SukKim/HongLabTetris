#include "Board.h"

Board::Board(int width, int height) : _width(width), _height(height)
{
    _board.resize(_width * _height, CellState::Empty);

    // 왼쪽, 오른쪽 벽 설정
    for (int y = 0; y < height; ++y) {
        SetState(0, y, CellState::Border);  // 왼쪽 벽
        SetState(_width - 1, y, CellState::Border);  // 오른쪽 벽
    }

    // 바닥 설정
    for (int x = 0; x < _width; ++x)
        SetState(x, _height - 1, CellState::Border);
}

void Board::SetState(int x, int y, const CellState& state)
{
    _board[y * _width + x] = state;
}

Board::CellState Board::GetState(int x, int y) const
{
    return _board[y * _width + x];
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

bool Board::isFullLine(int y)
{
    int x = 1;
    for (; x < _width - 1; ++x) {
        if (GetState(x, y) != CellState::Block)
            return false;
    }
    return true;
}

void Board::removeLine(int y)
{
    for (int x = 1; x < _width - 1; ++x)
        SetState(x, y, CellState::Empty);
}

void Board::moveBlockDown(int y)
{
    // y번째 줄 위로 모두 한 칸씩 내리기
    for (int ty = y; ty > 0; --ty) {
        for (int x = 1; x < _width - 1; ++x) {
            // 윗줄의 상태를 현재 줄로 복사
            SetState(x, ty, GetState(x, ty - 1));
        }
    }

    // 최상단 줄은 비움
    for (int x = 1; x < _width - 1; ++x) {
        SetState(x, 0, CellState::Empty);
    }
}
