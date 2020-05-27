#include "Frog.h"
 
//every chicken object will accept x, y, and width (square)
Frog::Frog(int x, int y, int width){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = 4;
    
    left_side = x;
    right_side = width + x;
    up = y;
    down = width + y;
}

// reset back to start position
void Frog::reset()
{
    x = (84/2)-4/2;
    y = 48-4;
    width = 4;

    left_side = x;
    right_side = width + x;
    up = y;
    down = width + y;
    
    //test_frog();
}

void Frog::test_frog()
{
    // printf("FROG RECTANGLE PARAMS: %d, %d, %d, %d", this->left_side, 
    // this->right_side, this->up, this->down);   
}


