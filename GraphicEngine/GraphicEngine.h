#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "Frog.h"
#include "Object.h"
#include "Vehicle.h"
#include "WaterSprites.h"
#include "Background.h"
#include "Frogger.h"

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include <vector>

/** GraphicEngine Class
 * @brief displays objects to lcd, stores all the graphical objects
 * @author Tarek Bessalah
 * @date May, 2020
 */
class GraphicEngine 
{
    public:
    
        /** Constructor 
         * @param the lcd object to draw on
         */
        GraphicEngine();
            
        /** 
         * @param this is the physical lcd object, that the user is looking at
         */
        N5110 lcd;

    public:     
        
        /** 
         * @param initiailized the lcd object
         */
        void init();  

        /** 
         * @param clears the current screen
         */    
        void clear();
        
        /** 
         * @param refreshes the screen
         */
        void refresh();
        
        /** 
         * @param sets the contrast to a fixed value of 0.45
         */
        void contrast();
        
        /** 
         * @param turns on the the backlight on
         */
        void backLightOn();
        
        /** 
         * @param testing object used to print to the screen
         */
        void printTest();
        
        /** 
         * @param prints the loser text to the screen
         */
        void printLoser();
        
        /** 
         * @param prints squished message to the lcd
         */
        void print();
        
        /** 
         * @param draws the danger zone at the top
         */
        void drawDangerZone();
        
        /** 
         * @param draws the menu to the screen
         */
        void drawMenu();
        
        /** 
         *  @param based on the pointer, it uses a switch statement to draw it
         *  @param sel- the number of rows
         */
        void getPointerPos(int sel);
        
        /** 
         *  @param display the frog based on the x, y, height, and animation
         *  @param x - x pos of frog
         *  @param y - y of the frog
         *  @param width - width of frog
         *  @param height - height of frog
         *  @param state - current animation of the frog
         */
        void showFrog(float x, int y, int width, int height, int state);
        
        /** 
         * @param draws the black rectangles for bonus rounds
         */
        void drawVoidBackGround();
        
        /** 
         *  @param draws the goal post in the lcd, has the sprite object already saved
         *  @param x - x pos of the goal post
         */
        void drawEndPost(int x);
        
        /** 
         * @param prints congratulations whenever the frog succeeds
         */
        void printCongrats();
        
        /** 
         *  @param displays the vehicle objects of the bonus rounds              
         *  @param x - the x pos of the vehicle
         *  @param y - the y pos of the vehicle
         *  @param c - the sprite of the vehicle
         */
        void displayBonusObjects(int x, int y, char c);
        
        /** 
         *  @param shows the object to the screen
         *  @param obj pointer - used to access the rectangle parameters of the vehicle
         *  @param state - the state of the turtle to detemine what turtle sprite to draw
         */
        void showObj(Object *obj, int state);
        
        /** 
         * @param displays the intro of a new level part b 
         */
        void newLevel1();
        
        /** 
         *  @param displays the intro of a new level two
         *  @param
         */
        void newLevel2();
        
        /** 
         * @param first part of the intro
         */
        void introOne();
        
        /** 
         *  @param second part of the intro 
         */
        void introTwo();
        
        /** 
         *  @param displays turtle object to screen
         *  @param x - x pos of the turtle
         *  @param y - y pos of the turtle
         *  @param turtle_state - animation state of turtle
         */
        void displayTurtles(int x, int y, char c, int turtle_state);
        
        /** 
         *  @param draw safe lanes of the game
         */
        void drawSafetyLanes();
        
        /** 
         *  @param displays log object to screen
         *  @param x - x pos of the log
         *  @param y - y pos of the log
         *  @param c - sprite of the log
         */
        void displayLog(int x, int y, char c);
        
        /** 
         *  @param displays vehicle object to screen
         *  @param x - x pos of the vehicle
         *  @param y - y pos of the vehicle
         *  @param c - sprite of the vehicle
         */
        void displayVehicle(int x, int y, char c);

        /** 
         * @param draw tutorial slide part 1
         */
        void drawTutor1();
        
        /** 
         * @param draw tutorial slide part 2
         */
        void drawTutor2();
        
        /** 
         * @param draw tutorial slide part 3
         */
        void drawTutor3();
};

#endif
    
    