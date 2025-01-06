Tetromino::Tetromino(BlockType type) : Rectangle(), _type(type)
{
    const auto& template_data = BlockTemplates::Templates[static_cast<int>(type)];
    _width = template_data.width;
    _height = template_data.height;
    _rect = template_data.cells;
    _color = template_data.color;
}

void Tetromino::Render(CHAR_INFO* consoleBuffer, int consoleWidth, int consoleHeight)
{
    int startX = _x - _width * 0.5f;
    int startY = _y - _height * 0.5f;

    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            int currentY = startY + i;
            int currentX = startX + j;

            if (currentY < 0 || currentY >= consoleHeight || 
                currentX < 0 || currentX >= consoleWidth)
                continue;

            if (GetCell(j, i).Type != CellType::Block)
                continue;

            int bufferIndex = currentY * consoleWidth + currentX;
            consoleBuffer[bufferIndex].Char.AsciiChar = _symbols[static_cast<int>(_type)];
            consoleBuffer[bufferIndex].Attributes = _color;
        }
    }
}

bool Tetromino::Collision(const Rectangle& other)
{
    // 기본적인 셀 대 셀 충돌 검사 사용
    return CheckCellCollision(other);
} 