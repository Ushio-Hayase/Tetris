#pragma once

#include <iostream>

#include "Queue.h"

struct Coordinates
{
    size_t x;
    size_t y;
};

struct RelativeCoordinate
{
    int x;
    int y;
};

enum class EDirection
{
    Down,
    Left,
    Right
};

enum class ERotateDirection
{
    ClockWise,
    CounterClockWise
};

class Block
{
public:
    void RotateBlock(ERotateDirection rotate);
    Coordinates getCoordinate(const size_t elementIdx) const;
    void Move(EDirection direction);
    virtual ~Block() {};
protected:
    Coordinates center;
    RelativeCoordinate other[3];
};

class Board
{
public:
    Board() = delete;

    Board(const size_t &width, const size_t &height);

    void ClearScreen();

    void PrintScreen() const;

    void UpdateBoard(const Block &block);

    bool IsOverlap(const Coordinates &coor) const;

    bool IsOverflow(const Coordinates &coor) const;

    size_t PopContinuosLineCount() const;

    ~Board();
protected:
    size_t boardWidth;
    size_t boardHeight;
    char** board;

};

class System
{
public:
    System() = default;
    Block &PopNextBlock(const Block &nextBlock);
    size_t GetScore();
    void AddScore(const size_t value);
private:
    size_t score = 0;
    Block& nextBlock;
};

class SquareBlock : public Block
{
public:
    SquareBlock() = delete;
    SquareBlock(const Coordinates centerCoor);
};

class LShapeBlock : Block
{
public:
    LShapeBlock() = delete;
    LShapeBlock(const Coordinates centerCoor);
};

class ReverseLShapeBlock : Block
{
public:
    ReverseLShapeBlock() = delete;
    ReverseLShapeBlock(const Coordinates centerCoor);
};

class SnakeBlock : Block
{
public:
    SnakeBlock() = delete;
    SnakeBlock(const Coordinates centerCoor);
};

class ReverseSnakeBlock : Block
{
public:
    ReverseSnakeBlock() = delete;
    ReverseSnakeBlock(const Coordinates centerCoor);
};

class StraightBlock : Block
{
public:
    StraightBlock() = delete;
    StraightBlock(const Coordinates centerCoor);
};
