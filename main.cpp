/* 
 *   ELEC2645 Embedded Systems Project
 *   School of Electronic & Electrical Engineering
 *   University of Leeds
 *   2019/20
 *  
 *   Name: Tarek Bessalah    
 *   Username: el19tb
 *   Student ID Number: 201344887
 *   Date: May, 2020
 */

#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "Frogger.h"
#include "Test.h"

void conduct_test();

int main()
{
    int size = 4; // game grid size
    int lcd_x = 84;
    int lcd_y = 48;
    int frog_width = 6; // width of frog, slightly fatter than width
    
    //conduct_test(); // run the tests of the program
    
    Frog frog((lcd_x/2)-frog_width/2, lcd_y-size, frog_width); // start at the bottom centre
    Frog *frogptr= &frog; // user will have control over this
    
    //printf("FROG POSITION, x: %d, y: %d", frog->x, frog->y)
    
    Frogger game(frogptr, size, lcd_x, lcd_y); // accepts the frogptr and graphics classes
    game.displayIntro(); // display the intro screen on boot up
    game.start(); // start the game loop
}

void conduct_test()
{
    #ifdef LOGGER_MODE
        run_progression();
        run_collision_detection();
        run_row_func();
        run_rect_params();
        run_frog_test();
    #endif  
}
