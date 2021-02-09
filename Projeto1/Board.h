#ifndef BOARD_H
#define BOARD_H

#include "Shapes.h"

#define ROWS 20
#define COLUMNS 10
#define FREE 0
#define BLOCK_SIZE 4

class Board {
public:
    Board();
    bool isGameOver();
    bool isFreePosition(Position pos);
    bool isCollision(Shapes tetromino, Position boardPos);
    void storeTetromino(Shapes tetromino, Position boardPos);
    int deleteFullLines();
    void clearBoard();
    int board[ROWS][COLUMNS];
private:
    void deleteLine(int row);
};

#endif