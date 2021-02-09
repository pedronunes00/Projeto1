#include "Board.h"
#include < C:\Users\pedro\source\repos\Projeto1\Projeto1\Shapes.h >
#include <iostream>

using namespace std;

Board::Board() {
    clearBoard();
}

void Board::clearBoard() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            board[row][col] = FREE;
        }
    }
}

bool Board::isGameOver() {
    for (int col = 0; col < COLUMNS; col++) {
        if (board[0][col] != FREE) return true;
    }
    return false;
}

bool Board::isFreePosition(int row, int col) {
    return board[row][col] == FREE;
}

void Board::storeShape(Shape shape, Position pos) {
    int ShapeRow, ShapeCol, boardRow, boardCol;
    int row = pos.row;
    int col = pos.col;

    for (boardRow = row, ShapeRow = 0; boardRow < row + BLOCK_SIZE; boardRow++, ShapeRow++) {
        for (boardCol = col, ShapeCol = 0; boardCol < col + BLOCK_SIZE; boardCol++, ShapeCol++) {
            if (Shape.getValue(ShapeRow, ShapeCol) != 0) {
                board[boardRow][boardCol] = Shape.getValue(ShapeRow, ShapeCol);
            }
        }
    }
}

bool Board::isCollision(Shape shape, Position pos) {
    int ShapeRow, ShapeCol, boardRow, boardCol;
    int row = pos.row;
    int col = pos.col;

    if (row >= ROWS || col >= COLUMNS || col < 0) return true;

    for (boardRow = row, ShapeRow = 0; boardRow < row + BLOCK_SIZE && boardRow < ROWS; boardRow++, ShapeRow++) {
        for (boardCol = col, ShapeCol = 0; boardCol < col + BLOCK_SIZE && boardCol < COLUMNS; boardCol++, ShapeCSol++) {
            //cout << "boardRow && boardCol " << boardRow << " " << boardCol << " shapeCol && shapeRow " << ShapeRow << " " << ShapeCol << endl;
            if (shape.getValue(ShapeRow, ShapeCol) != 0 && board[boardRow][boardCol] != 0) {
                return true;
            }
            else if (boardRow == ROWS - 1 && ShapeRow < BLOCK_SIZE - 1) {
                int tempRow = ShapeRow;
                int tempCol = ShapeCol;
                tempRow++;
                if (shape.getValue(tempRow, tempCol) != 0) return true;
            }
            else if (boardCol == COLUMNS - 1 && ShapeCol < BLOCK_SIZE - 1) {
                int tempRow = ShapeRow;
                int tempCol = ShapeCol;
                tempCol++;
                if (shape.getValue(tempRow, tempCol) != 0) return true;
            }
        }
    }
    return false;
}

int Board::deleteFullLines() {
    int lines = 0;
    for (int row = 0; row < ROWS; row++) {
        int col = 0;
        while (col < COLUMNS) {
            if (board[row][col] == 0) break;
            col++;
        }
        if (col == COLUMNS) {
            deleteLine(row);
            lines++;
        }
    }
    return lines;
}

void Board::deleteLine(int row) {
    for (int y = row; y > 0; y--) {
        for (int x = 0; x < COLUMNS; x++) {
            board[y][x] = board[y - 1][x];
        }
    }
}