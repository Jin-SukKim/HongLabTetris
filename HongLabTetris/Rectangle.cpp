const std::array<char, 4> Rectangle::_val = {' ', ' ', '#', 'O'};  // None, Empty, Border, Block

void Rectangle::Render(CHAR_INFO* consoleBuffer, int consoleWidth, int consoleHeight)
{
    int startX = _x - _width * 0.5f;
    int startY = _y - _height * 0.5f;

    for(int i = 0; i < _height; ++i) {
        for(int j = 0; j < _width; ++j) {
            int currentY = startY + i;
            int currentX = startX + j;

            if(currentY < 0 || currentY >= consoleHeight || 
               currentX < 0 || currentX >= consoleWidth)
                continue;

            Cell cell = GetCell(j, i);
            if(cell.Type == CellType::None)
                continue;

            int bufferIndex = currentY * consoleWidth + currentX;
            consoleBuffer[bufferIndex].Char.AsciiChar = _val[static_cast<int>(cell.Type)];
            consoleBuffer[bufferIndex].Attributes = cell.Color != 0 ? cell.Color : _defaultColor;
        }
    }
}

void Rectangle::Fill(const Cell& cell)
{
    std::fill(_rect.begin(), _rect.end(), cell);
}

void Rectangle::DrawBorder(const Cell& cell)
{
    // 위쪽과 아래쪽 테두리
    for(int x = 0; x < _width; ++x) {
        SetCell(x, 0, cell);
        SetCell(x, _height - 1, cell);
    }
    
    // 왼쪽과 오른쪽 테두리
    for(int y = 0; y < _height; ++y) {
        SetCell(0, y, cell);
        SetCell(_width - 1, y, cell);
    }
}

bool Rectangle::IsAreaEmpty(int startX, int startY, int width, int height) const
{
    for(int y = startY; y < startY + height; ++y) {
        for(int x = startX; x < startX + width; ++x) {
            if(GetCell(x, y).Type != CellType::Empty)
                return false;
        }
    }
    return true;
}

bool Rectangle::Collides(const Rectangle& other) const
{
    int thisLeft = _x - _width / 2;
    int thisRight = _x + _width / 2;
    int thisTop = _y - _height / 2;
    int thisBottom = _y + _height / 2;
    
    int otherLeft = other._x - other._width / 2;
    int otherRight = other._x + other._width / 2;
    int otherTop = other._y - other._height / 2;
    int otherBottom = other._y + other._height / 2;
    
    return !(thisRight < otherLeft || 
             thisLeft > otherRight || 
             thisBottom < otherTop || 
             thisTop > otherBottom);
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
            if(GetCell(x1, y1).Type == CellType::Empty)
                continue;

            // other의 로컬 좌표로 변환
            int localX = worldX1 - otherStartX;
            int localY = worldY1 - otherStartY;

            // other의 범위 안에 있고, 해당 위치의 셀이 비어있지 않다면 충돌
            if(localX >= 0 && localX < other._width && 
               localY >= 0 && localY < other._height) {
                if(other.GetCell(localX, localY).Type != CellType::Empty) {
                    return true;
                }
            }
        }
    }
    return false;
} 