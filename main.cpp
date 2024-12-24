#include "tetris.h"

int main()
{
    int width, height;

    std::cout << "높이와 너비를 띄어쓰기로 분리해서 입력 >> ";
    std::cin >> height >> width;

    Board board(width, height);

    board.ClearScreen();

    int spawnX, spawnY;

    spawnX = width / 2;

    spawnY = 2;

    Coordinates spawnCoor = {spawnX, spawnY};

    Block blocks[6];

    blocks[0] = SquareBlock(spawnCoor);
}