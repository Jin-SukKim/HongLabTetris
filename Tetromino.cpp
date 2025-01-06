#include "Tetromino.h"

const std::array<char, 7> Tetromino::_symbols = {
    'I',
    'J',
    'L',
    'O',
    'S',
    'Y',
    'Z'
};

Tetromino::Tetromino(BlockType type) : Rectangle(), _type(type)
{
    const auto& template_data = BlockTemplates::Blocks[static_cast<int>(type)];

    _width = template_data.width;
    _height = template_data.height;
    _rect = template_data.shape;
}

void Tetromino::Tick(float DeltaTime)
{
	_timer += DeltaTime;
	if (_timer > 0.5f) {
		_timer = 0.f;

		// 아래로
		_y += 1;
	}
}

void Tetromino::RotateRight()
{
    // 임시 벡터에 회전된 결과 저장
    std::vector<Cell> rotated(_width * _height);

    // 90도 시계방향 회전
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            // (x,y) -> (y, width-1-x) 변환
            int newX = y;
            int newY = _width - 1 - x;
            rotated[newY * _height + newX] = GetCell(x, y);
        }
    }

    // width와 height 교환
    std::swap(_width, _height);

    // 회전된 데이터로 교체
    _rect = rotated;
}

void Tetromino::RotateLeft()
{
    // 임시 벡터에 회전된 결과 저장
    std::vector<Cell> rotated(_width * _height);

    // 90도 반시계방향 회전
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            // (x,y) -> (height-1-y, x) 변환
            int newX = _height - 1 - y;
            int newY = x;
            rotated[newY * _height + newX] = GetCell(x, y);
        }
    }

    // width와 height 교환
    std::swap(_width, _height);

    // 회전된 데이터로 교체
    _rect = rotated;
}

void Tetromino::Render(CHAR_INFO* consoleBuffer, int consoleWidth, int consoleHeight)
{
    int startX = _x - _width / 2;
    int startY = _y - _height / 2;

    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            int currentY = startY + i;
            int currentX = startX + j;

            // 콘솔 범위 체크
            if (currentY < 0 || currentY >= consoleHeight || currentX < 0 || currentX >= consoleWidth)
                continue;

            if (GetCell(j, i).Type != CellType::Block)
                continue;

            int bufferIndex = currentY * consoleWidth + currentX;
            consoleBuffer[bufferIndex].Char.AsciiChar = _symbols[static_cast<int>(_type)];
            // TODO: Cell struct에 Color를 추가한 뒤 Rendering해도 될 듯
        }
    }
}

bool Tetromino::Collision(const Rectangle& other)
{

    // 기본적인 셀 대 셀 충돌 검사 사용
    return CheckCellCollision(other);
}
