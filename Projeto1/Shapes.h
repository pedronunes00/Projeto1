#ifndef SHAPES_H
#define SHAPES_H

class Position {
public:
    int row, col;
};

class Shapes {
public:
    int getValue(Position pos);
    int type, rotation;
};


#endif