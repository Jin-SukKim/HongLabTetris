#include <iostream>
#include <windows.h>


// Screen size settings
const int width = 10;
const int height = 20;
char board[height][width];

void clearScreen() {
    system("cls");
}

void initializeBoard() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            board[y][x] = ' ';
        }
    }
}

void drawBoard() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << board[y][x];
        }
        std::cout << std::endl;
    }
}

// Draw block and clear previous position
void drawBlock(int oldX, int oldY, int newX, int newY) {
   
    if (oldY >= 0) { // note: Prevent invalid array access by ensuring oldY is non-negative
        board[oldY][oldX] = ' ';
    }

    board[newY][newX] = '#';
}

int main() {

    initializeBoard();
    int blockX = width / 2;
    int blockY = 0;

    while (true) {
        clearScreen();
        drawBlock(blockX, blockY - 1, blockX, blockY);
        drawBoard();

        // Move the block down
        blockY++;
        if (blockY >= height) {
            blockY = 0; // Reset block position to the top
        }

        Sleep(500);
    }

    return 0;
}
