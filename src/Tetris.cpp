#include "Tetris.h"

Board::Board(const size_t &width, const size_t &height) : boardWidth(width), boardHeight(height)
{
    this->board = new char *[height];
    for (int i = 0; i < height; ++i)
    {
        this->board[i] = new char[width];
        for (int j = 0; j < width; ++j)
            board[i][j] = ' ';
    }
}

void Board::ClearScreen()
{
    system("cls");
}

void Board::PrintScreen() const
{
    for (int i = 0; i < this->boardHeight; ++i)
    {
        for (int j = 0; j < this->boardWidth; ++j)
            std::cout << this->board[i][j];
        std::cout << "\n";
    }
}

void Board::UpdateBoard(const Block &block)
{

    for (int i = 0; i < 4; ++i)
    {
        Coordinates coor = block.getCoordinate(i);
        this->board[coor.y][coor.x] = '#';
    }
}

size_t Board::PopContinuosLineCount() const
{
    size_t count = 0;

    for (int i = 0; i < this->boardHeight; ++i)
    {
        bool isContinuos = true;
        for (int j = 0; j < this->boardWidth; ++j)
            if (this->board[i][j] != '#')
                isContinuos = false;
        if (isContinuos)
        {
            count++;
            delete this->board[i];
            for (int j = i; j < this->boardHeight - 1; ++j)
                this->board[i] = this->board[i + 1];

            this->board[this->boardHeight] = new char[this->boardWidth];

            for (int j = 0; j < this->boardWidth; ++j)
                this->board[this->boardHeight][j] = ' ';
        }
    }

    return count;
}

bool Board::IsOverlap(const Coordinates &coor) const
{
    return this->board[coor.y][coor.x] == '#' ? true : false;
}

bool Board::IsOverflow(const Coordinates &coor) const
{
    return coor.x < this->boardWidth && coor.y < this->boardHeight ? true : false;
}

Board::~Board()
{
    for (int i = 0; i < this->boardHeight; ++i)
        delete this->board[i];
    delete board;
}

void Block::RotateBlock(ERotateDirection rotate)
{
    for (int i = 0; i < 3; ++i)
    {
        RelativeCoordinate tmp{0, 0};
        RelativeCoordinate &relativeCoor = this->other[i];
        if (rotate == ERotateDirection::ClockWise)
        {
            tmp.x = relativeCoor.y;
            tmp.y = -relativeCoor.x;
        }
        else
        {
            tmp.x = -relativeCoor.y;
            tmp.y = relativeCoor.x;
        }
        this->other[i] = tmp;
    }
}

void Block::Move(EDirection direction)
{
    int addedToXValue, addedToYValue;

    switch (direction)
    {
    case EDirection::Down:
        addedToXValue = 0;
        addedToYValue = 1;
        break;
    case EDirection::Left:
        addedToXValue = -1;
        addedToYValue = 0;
        break;
    case EDirection::Right:
        addedToXValue = 1;
        addedToYValue = 0;
        break;

    default:
        throw "undefined Direction value";
    }
    this->center.x += addedToXValue;
    this->center.y += addedToYValue;

    for (int i = 0; i < 3; ++i)
    {
        this->other[i].x += addedToXValue;
        this->other[i].y += addedToYValue;
    }
}

Coordinates Block::getCoordinate(const size_t elementIdx) const
{
    if (elementIdx > 3)
        throw "elementIdx must be 0-3";

    if (elementIdx == 0)
        return this->center;

    Coordinates tmp = this->center;
    tmp.x += this->other[elementIdx - 1].x;
    tmp.y += this->other[elementIdx - 1].y;

    return tmp;
}

SquareBlock::SquareBlock(const Coordinates centerCoor)
{
    this->center = centerCoor;
    this->other[0] = RelativeCoordinate{-1, 0};
    this->other[1] = RelativeCoordinate{-1, -1};
    this->other[2] = RelativeCoordinate{0, -1};
}

LShapeBlock::LShapeBlock(const Coordinates centerCoor)
{
    this->center = centerCoor;
    this->other[0] = RelativeCoordinate{0, -1};
    this->other[1] = RelativeCoordinate{0, 1};
    this->other[2] = RelativeCoordinate{1, 1};
}

ReverseLShapeBlock::ReverseLShapeBlock(const Coordinates centerCoor)
{
    this->center = centerCoor;
    this->other[0] = RelativeCoordinate{0, -1};
    this->other[1] = RelativeCoordinate{0, 1};
    this->other[2] = RelativeCoordinate{-1, 1};
}

SnakeBlock::SnakeBlock(const Coordinates centerCoor)
{
    this->center = centerCoor;
    this->other[0] = RelativeCoordinate{0, -1};
    this->other[1] = RelativeCoordinate{1, 0};
    this->other[2] = RelativeCoordinate{1, 1};
}

ReverseSnakeBlock::ReverseSnakeBlock(const Coordinates centerCoor)
{
    this->center = centerCoor;
    this->other[0] = RelativeCoordinate{0, -1};
    this->other[1] = RelativeCoordinate{-1, 0};
    this->other[2] = RelativeCoordinate{-1, 1};
}

StraightBlock::StraightBlock(const Coordinates centerCoor)
{
    this->center = centerCoor;
    this->other[0] = RelativeCoordinate{0, -1};
    this->other[1] = RelativeCoordinate{0, 1};
    this->other[2] = RelativeCoordinate{0, 2};
}

Block &System::PopNextBlock(const Block &nextBlock)
{
    Block &tmp = this->nextBlock;
    this->nextBlock = nextBlock;
    return tmp;
}

size_t System::GetScore()
{
    return this->score;
}

void System::AddScore(const size_t value)
{
    this->score += value;
}
