bool Board::Collision(const Rectangle& other)
{
    // Board는 Border와 Block에 대해서만 충돌 검사
    int otherWidth = other.GetWidth();
    int otherHeight = other.GetHeight();
    int otherStartX = other.GetPosX() - otherWidth / 2;
    int otherStartY = other.GetPosY() - otherHeight / 2;

    // other의 각 셀에 대해
    for(int y = 0; y < other.GetHeight(); ++y) {
        for(int x = 0; x < other.GetWidth(); ++x) {
            // other의 빈 셀은 무시
            if(other.GetCell(x, y).Type == CellType::Empty)
                continue;

            // Board에서의 위치 계산
            int boardX = otherStartX + x;
            int boardY = otherStartY + y;

            // Board 범위 밖이면 충돌
            if(boardX < 0 || boardX >= _width || 
               boardY < 0 || boardY >= _height)
                return true;

            // Board의 해당 위치에 Border나 Block이 있으면 충돌
            Cell boardCell = GetCell(boardX, boardY);
            if(boardCell.Type == CellType::Border || 
               boardCell.Type == CellType::Block)
                return true;
        }
    }
    return false;
} 