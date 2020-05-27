#include "GraphicEngine.h"

GraphicEngine::GraphicEngine(){}

/** Draw the pointer next to the menu texts */
void GraphicEngine::getPointerPos(int sel)
{    
    switch(sel)
    {
       case 0:
            lcd.drawSprite(30, 48 - 4*12, 8, 12, (int *)frog);
            break;
        case 1: 
            lcd.drawSprite(55, 44 - 4*7, 8, 12, (int *)frog);            
            break;
        case 2: 
            lcd.drawSprite(50, 48 - 4*4, 8, 12, (int *)frog);            
            break;
    }  
    
    wait_ms(10);
}

void GraphicEngine::drawMenu()
{
    lcd.printString("Play",3, 0);
    lcd.drawRect(-1, 48 - 4*12, 30, 11, FILL_TRANSPARENT);
    
    lcd.printString("Tutorial",3,2);
    lcd.drawRect(-1, 50 - 4*9, 55, 10, FILL_TRANSPARENT);
    
    lcd.printString("Bonus",3,4);
    lcd.drawRect(-1, 50 - 4*5, 50, 10, FILL_TRANSPARENT);  
}

void GraphicEngine::drawTutor1()
{
    lcd.printString("Tutorial: (A) ", 0,0);
    lcd.printString("To move frog  ", 0,1);
    lcd.printString("press X(UP),  ", 0,2);
    lcd.printString("B(DOWN)       ", 0,3);
    lcd.printString("A(LEFT),      ", 0,4);
    lcd.printString("Y(right)      ", 0,5);
    wait_ms(20); 
}

void GraphicEngine::drawTutor2()
{
    lcd.printString("Tutorial: (A) ", 0,0);
    lcd.printString("Avoid, water, ", 0,1);
    lcd.printString("vehicles,     ", 0,2);
    lcd.printString("snakes        ", 0,3);
    lcd.printString("jump on logs, ", 0,4);
    lcd.printString("reach the goal", 0,5);  
    wait_ms(20); 
}

void GraphicEngine::drawTutor3()
{
    lcd.printString("Tutorial: (A) ", 0,0);
    lcd.printString("Most          ", 0,1);
    lcd.printString("importantly   ", 0,2);
    lcd.printString("Have fun :)   ", 0,3);
    lcd.printString("Press A       ", 0,4);
    lcd.printString("to play!      ", 0,5); 
    wait_ms(20); 
}

void GraphicEngine::newLevel1()
{
    lcd.printString("|------------|", 0,0);
    lcd.printString("|Congrats!   |", 0,1);
    lcd.printString("|            |", 0,2);
    lcd.printString("|            |", 0,3);
    lcd.printString("|            |", 0,4);
    lcd.printString("|------------|", 0,5);
}


void GraphicEngine::newLevel2()
{
    lcd.printString("|------------|", 0,0);
    lcd.printString("|  Loading   |", 0,1);
    lcd.printString("|            |", 0,2);
    lcd.printString("|  Level 2   |", 0,3);
    lcd.printString("|            |", 0,4);
    lcd.printString("|------------|", 0,5);
}

void GraphicEngine::introOne()
{
    lcd.printString("|Project     |", 0,0);
    lcd.printString("|  by        |", 0,1);
    lcd.printString("|   Tarek    |", 0,2);
    lcd.printString("| Bessalah   |", 0,3);
    lcd.printString("|            |", 0,4);
    lcd.printString("|201344887   |", 0,5);
}

void GraphicEngine::introTwo()
{
    lcd.drawSprite(20, 48-4*12, 36, 43,(int *)frogger_intro);  
    lcd.printString("|  FROGGER!  |", 0,5);
}

void GraphicEngine::init()
{
    lcd.init();
}

void GraphicEngine::contrast()
{
    lcd.setContrast(0.45);  
}

void GraphicEngine::clear()
{
    lcd.clear();
}

void GraphicEngine::refresh()
{
    lcd.refresh();
}

void GraphicEngine::backLightOn()
{
    lcd.backLightOn();
}

/** To save function space, call different drawing functions based on the char */
void GraphicEngine::showObj(Object *obj, int turtles_state)
{
    if(obj->object.c == 'G' || obj->object.c == 'M') {
        displayLog(obj->object.x, obj->object.y, obj->object.c);
    } else if(obj->object.c == 'T') {
        displayTurtles(obj->object.x, obj->object.y, obj->object.c, turtles_state);
    } else if(obj->object.c == 'S') {
        displayBonusObjects(obj->object.x, obj->object.y, obj->object.c);
    } else {
        displayVehicle(obj->object.x, obj->object.y, obj->object.c);
    } 
}

void GraphicEngine::displayBonusObjects(int x, int y, char c)
{
    lcd.drawSprite(x, y, 4, 12, (int *)star);
}

void GraphicEngine::drawDangerZone()
{
    lcd.drawSprite(0, 48 - 4*11, 7, 83, (int *)danger_zone);
}

void GraphicEngine::drawVoidBackGround()
{
    lcd.drawRect(0, 0, 35, 48, FILL_BLACK);
    lcd.drawRect(55, 0, 35, 48, FILL_BLACK);
}

/** To increase the duration of the states, make it by a factor of 1000 */
void GraphicEngine::displayTurtles(int x, int y, char c, int turtle_sate){
    switch(turtle_sate)
    {
        case 0 ... 1000:
            lcd.drawSprite(x, y, 4, 20, (int *)turtles_state_one);  
            break;
        case 1001 ... 2000:
            lcd.drawSprite(x, y, 4, 20, (int *)turtles_state_one);  
            break;
        case 2001 ... 3000:
            lcd.drawSprite(x, y, 4, 20, (int *)turtles_state_two);  
            break;
        case 3001 ... 4000:
            lcd.drawSprite(x, y, 4, 20, (int *)turtles_state_two);  
            break;
        case 4001 ... 5000:
            lcd.drawSprite(x, y, 4, 20, (int *)turtles_state_three);  
            break;
    }
}

/** Based on the char values you can determine the sprite */
void GraphicEngine::displayVehicle(int x, int y, char c)
{
    switch(c)
    {
        case 'L': 
            lcd.drawSprite(x, y, 4, 12, (int *)left_racer);
            break;
        case 'R' : 
            lcd.drawSprite(x, y, 4, 12, (int *)right_racer);
            break;
        case 'B': 
            lcd.drawSprite(x, y, 4, 16, (int *)bus);
            break;
        case 'N': 
            lcd.drawSprite(x, y, 4, 10, (int *)right_normal);
            break;
        case 'X': 
            lcd.drawSprite(x, y, 4, 10, (int *)left_normal);
            break;
    } 
}

void GraphicEngine::displayLog(int x, int y, char c)
{
    switch(c)
    {
        case 'G':
            lcd.drawSprite(x, y, 4, 20, (int *)log_big);  
            break;

        case 'M':
            lcd.drawSprite(x, y, 4, 16, (int *)medium_log);  
            break;
    }
}

/* TO-DO: ADD SPRITES AND SPRITE STATE */
void GraphicEngine::showFrog(float x, int y, int width, int height, int state)
{
    switch(state)
    {
        case 0:
            lcd.drawSprite(x, y, 4, 6, (int *)frog_state_up);
            break;
        case 1:
            lcd.drawSprite(x, y, 4, 6, (int *)frog_state_left);
            break;
        case 2: 
            lcd.drawSprite(x, y, 4, 6, (int *)frog_state_right);
            break;
        case 3: 
            lcd.drawSprite(x, y, 4, 6, (int *)frog_state_down);
            break;
    }
}

void GraphicEngine::drawSafetyLanes()
{        
    lcd.drawSprite(0, 48 - 4, 4, 83, (int *)safety_zone); // row 0 -> bottom
    
    lcd.drawSprite(0, 48 - 4*6, 4, 83, (int *)safety_zone); // row 6 -> middle(ish)
}

void GraphicEngine::drawEndPost(int x_pos)
{
    lcd.drawSprite(x_pos, 48 - 4*11, 8, 18, (int *)goal_post);
}

void GraphicEngine::printTest()
{
    lcd.printString("SQUISHED", 1, 1);  
}

void GraphicEngine::print()
{
    lcd.printString("DROWNED",1,1);  
}

void GraphicEngine::printLoser()
{
    lcd.printString("LOSER!!!!",1,1);  
}

void GraphicEngine::printCongrats()
{
    lcd.printString("CONGTATS NEXT LEVEL!!!!",1,1);    
}