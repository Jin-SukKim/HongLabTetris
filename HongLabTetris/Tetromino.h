#pragma once
#include "Rectangle.h"
#include "BlockData.h"

class Tetromino : public Rectangle
{
public:
    enum class BlockType {
        I, J, L, O, S, T, Z
    };

    explicit Tetromino(BlockType type);
    void Tick(float DeltaTime);
    void RotateRight();
    void RotateLeft();
    void Render(CHAR_INFO* consoleBuffer, int consoleWidth, int consoleHeight) override;

private:
    float _timer = 0.f;
    BlockType _type;
    WORD _color;
    static const std::array<char, 7> _symbols;
}; 