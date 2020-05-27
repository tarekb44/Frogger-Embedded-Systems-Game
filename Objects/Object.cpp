#include "Object.h"
#include "Frogger.h"

Object::Object()
{  
    initializeLogParameters();
    initializeScreenParameters();
}

void Object::initializeScreenParameters()
{
    screenHeight = 48;
    screenWidth = 84;
    grid = 4;
}

void Object::initializeLogParameters()
{
    size = 3;  
    seperation = 0;  
   
    //different speeds of vehicles
    slow = 0.4;
    medium = 0.6;
    fast = 0.8;
}

void Object::setDir(int dir)
{
    this->object.dir = dir; 
    
    //printf("print current object direction %d", this->object.dir);
}

void Object::setRow(int row)
{
    this->row = row;
   
    // y position of all vehicles
    object.y = screenHeight - grid * row;
    //printf("print current object y %d", this->object.y);

}

void Object::setSeperation(int seperate)
{
    this->seperation = seperate;
   
    // intialize the vehicle size and position in lcd
    // x position of all vehicles
    object.x = seperation;
}

void Object::speedSlow(int dir)
{
    this->speed = 0.4;

    switch(dir)
    {
        case 1:
            object.x += 0.4;
            updateRect(object.x, object.y);
            break;
        case 2:
            object.x -= 0.4;
            updateRect(object.x, object.y);
            break;
    }
    
    //printf("check if rect is updated %d", this->rectangle.left_side, 
    //this->rectangle.right_side);
}

void Object::speedMedium(int dir)
{ 
    this->speed = 0.6;
    
    switch(dir)
    {
        case 1:
            object.x += 0.6;
            updateRect(object.x, object.y);
            break;
        case 2:
            object.x -= 0.6;
            updateRect(object.x, object.y);
            break;
    }
}

void Object::speedFast(int dir)
{   
    this->speed = 0.9;
    
    switch(dir)
    {
        case 1:
            object.x += 0.9;
            updateRect(object.x, object.y);
            break;
        case 2:
            object.x -= 0.9;
            updateRect(object.x, object.y);
            break;
    }
}

void Object::speedUltra(int dir)
{   
    this->speed = 1.3;

    switch(dir)
    {
        case 1:
            object.x += 1.3;
            updateRect(object.x, object.y);
            break;
        case 2:
            object.x -= 1.3;
            updateRect(object.x, object.y);
            break;
    }
}

void Object::setSprite(char c)
{
    this->object.c = c;  // used to determine the sprite 

    if(c == 'T' || c == 'M' || c == 'G') {
        determineLogRecParamaters(c); // create a rectangle for logs
    } else if(c == 'S') {
        determineBonusVehiclesRec(c);
    } else {
        determineVehicleRecParamaters(c); // create a rectangle for vehicles
    }
}

void Object::determineVehicleRecParamaters(char c)
{
    switch(c)
    {
        case 'R':
            createRect(12, 4);
            break;
        case 'L':
            createRect(12, 4);
            break;
        case 'N':
            createRect(10, 4);
            break;
        case 'X':
            createRect(10, 4);
            break;
        case 'B':
            createRect(16, 4);
            break;
    }
}

void Object::determineLogRecParamaters(char c)
{
    switch(c)
    {
        case 'M':
            createRect(16, 4);
            break;
        case 'T':  
            createRect(12, 4);
            break;
        case 'G':
            createRect(20, 4);
            break;
    }  
}

void Object::determineBonusVehiclesRec(char c)
{
    createRect(4, 12);
}

void Object::createRect(int width, int height)
{
    this->width = width;
    this->height = height;
    this->rectangle.left_side = object.x;
    this->rectangle.right_side = object.x + width;
    this->rectangle.bottom = height + object.y;
    this->rectangle.up = object.y;
}

void Object::updateRect(int x, int y)
{
    this->rectangle.left_side = object.x;
    this->rectangle.right_side = object.x + this->width;
    this->rectangle.bottom = this->height + object.y;
    this->rectangle.up = object.y;
}