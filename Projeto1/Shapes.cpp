#include "Shapes.h"

int shapes[7][4][4][4] = {
    {//O Tetromino
        {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}

        },
        {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    {//T Tetromino 
        {
            {0, 2, 0, 0},
            {2, 2, 2, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {2, 0, 0, 0},
            {2, 2, 0, 0},
            {2, 0, 0, 0},
            {0, 0, 0, 0}

        },
        {
            {2, 2, 2, 0},
            {0, 2, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 2, 0, 0},
            {2, 2, 0, 0},
            {0, 2, 0, 0},
            {0, 0, 0, 0}
        }
    },
    {//S Tetromino
        {
            {0, 3, 3, 0},
            {3, 3, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {3, 0, 0, 0},
            {3, 3, 0, 0},
            {0, 3, 0, 0},
            {0, 0, 0, 0}

        },
        {
            {0, 3, 3, 0},
            {3, 3, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {3, 0, 0, 0},
            {3, 3, 0, 0},
            {0, 3, 0, 0},
            {0, 0, 0, 0}
        }
    },
    {//Z Tetromino
        {
            {4, 4, 0, 0},
            {0, 4, 4, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 4, 0, 0},
            {4, 4, 0, 0},
            {4, 0, 0, 0},
            {0, 0, 0, 0}

        },
        {
            {4, 4, 0, 0},
            {0, 4, 4, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 4, 0, 0},
            {4, 4, 0, 0},
            {4, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    {//L Tetromino
        {
            {5, 0, 0, 0},
            {5, 5, 5, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {5, 5, 0, 0},
            {5, 0, 0, 0},
            {5, 0, 0, 0},
            {0, 0, 0, 0}

        },
        {
            {5, 5, 5, 0},
            {0, 0, 5, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 5, 0, 0},
            {0, 5, 0, 0},
            {5, 5, 0, 0},
            {0, 0, 0, 0}
        }
    },
    {//J Tetromino 
        {
            {0, 0, 6, 0},
            {6, 6, 6, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {   {6, 0, 0, 0},
            {6, 0, 0, 0},
            {6, 6, 0, 0},
            {0, 0, 0, 0}

        },
        {
            {6, 6, 6, 0},
            {6, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {6, 6, 0, 0},
            {0, 6, 0, 0},
            {0, 6, 0, 0},
            {0, 0, 0, 0}
        }
    },
    {//I Tetromino
        {
            {7, 7, 7, 7},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {7, 0, 0, 0},
            {7, 0, 0, 0},
            {7, 0, 0, 0},
            {7, 0, 0, 0}
        },
        {
            {7, 7, 7, 7},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {7, 0, 0, 0},
            {7, 0, 0, 0},
            {7, 0, 0, 0},
            {7, 0, 0, 0}
        }
    }
};


int Shapes::getValue(Position pos) {
    return shapes[type][rotation][pos.row][pos.col];
}