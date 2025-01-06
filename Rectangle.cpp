#include "Rectangle.h"

const std::array<char,3> Rectangle::_val = {' ','#','B'};

Rectangle::Rectangle(int width,int height) :
    _x(0),_y(0), _width(width),_height(height)
{
    _rect.resize(_width * _height, Cell::Empty);
}

Rectangle::Rectangle(int width,int height,std::vector<Cell> rect): 
    _x(0),_y(0),_width(width),_height(height), _rect(rect)
{}

void Rectangle::Clear()
{
    std::fill(_rect.begin(),_rect.end(),Cell::Empty);
}

void Rectangle::SetCell(int x,int y,const Cell & cell)
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        return;
    _rect[y * _width + x] = cell;
}

Cell Rectangle::GetCell(int x,int y) const
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        return Cell::None;
    return _rect[y * _width + x];
}

void Rectangle::Render(CHAR_INFO* consoleBuffer,int consoleWidth,int consoleHeight)  // consoleHeight 매개변수 추가
{
    int startX = _x - _width * 0.5f;
    int startY = _y - _height * 0.5f;

    for(int i = 0; i < _height; ++i) {
        for(int j = 0; j < _width; ++j) {
            int currentY = startY + i;
            int currentX = startX + j;

            // 콘솔 범위 체크
            if(currentY < 0 || currentY >= consoleHeight || currentX < 0 || currentX >= consoleWidth)
                continue;

            CellType cellType = GetCell(j,i).Type;
            if(cellType == CellType::None)
                continue;

            int bufferIndex = currentY * consoleWidth + currentX;
            consoleBuffer[bufferIndex].Char.AsciiChar = _val[static_cast<int>(cellType)];
        }
    }
}

bool Rectangle::CheckCellCollision(const Rectangle& other) const
{
    // 두 사각형의 실제 위치 계산
    int thisStartX = _x - _width / 2;
    int thisStartY = _y - _height / 2;

    int otherStartX = other._x - other._width / 2;
    int otherStartY = other._y - other._height / 2;

    // 각 셀에 대해 충돌 검사
    for(int y1 = 0; y1 < _height; ++y1) {
        for(int x1 = 0; x1 < _width; ++x1) {
            // 현재 객체의 실제 위치
            int worldX1 = thisStartX + x1;
            int worldY1 = thisStartY + y1;

            // 현재 셀이 비어있으면 건너뛰기
            if(GetCell(x1,y1).Type == CellType::Empty)
                continue;

            // other의 로컬 좌표로 변환
            int localX = worldX1 - otherStartX;
            int localY = worldY1 - otherStartY;

            // other의 범위 안에 있고, 해당 위치의 셀이 비어있지 않다면 충돌
            if(localX >= 0 && localX < other._width &&
               localY >= 0 && localY < other._height) {
                if(other.GetCell(localX,localY).Type != CellType::Empty) {
                    return true;
                }
            }
        }
    }

    return false;

}