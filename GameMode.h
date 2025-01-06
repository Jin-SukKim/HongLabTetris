#pragma once

// 기본 게임모드
class GameMode
{
public:
    GameMode();
    ~GameMode();

    void clearScreen();

    void initializeBoard();

    void drawBoard();

    // Draw block and clear previous position
    void drawBlock(int oldX,int oldY,
        int newX,int newY);

    const int GetWidth() const;
    const int GetHeight() const;

protected:
    const int width;
    const int height;
    char* board = nullptr;
};

