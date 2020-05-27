#ifndef FROG_H
#define FROG_H

#include "Gamepad.h"
#include "mbed.h"
#include "N5110.h"

/** Frog Class
 *
 * @brief Frog object used by the user to move around
 * @author Tarek Bessalah
 * @date May, 2020
 */
class Frog
{
    public:
        /** Constructor */
        Frog();
        
        /** Constructor
         * @brief This constructor is the main object of the frog
         * @param x - gets the x position of the frog (initial)
         * @param y - gets the y position of the frog (initial)
         * @param width - gets the width of the frog
         */ 
        Frog(int x, int y, int width);
   
    public:
        
        /** 
         * @brief value of the left side of the rectangle of the frog 
         */
        float left_side;
        
        /** 
         * @brief value of the right side of the rectangle of the frog
         */
        float right_side;
        
        /** 
         * @brief value of the upside of the rectangle of the frog, 
         * used for collision detection
         */
        float up;
        
        /** 
         * @brief value of the downside of the rectangle of the frog
         * used for collision determination
         */
        float down;
       
        /** 
         * @brief value of the x of the rectangle of the frog
         * used for collision determination, 
         * is a float value becuase speed can change it
         */
        float x;
        
        /** 
         * @brief value of the y of the frog
         * used for collision determination 
         */
        int y;
        
        /** 
         * @brief value of the width of the frog
         * used for collision determination 
         */
        int width;
        
        /** 
         * @brief value of the height of the rectangle of the frog
         * used for collision determination 
         */
        int height;
    
    public:
         
        /** 
         * @brief This function resets the frog back to its original position
         * it updates the x, y coordinates when called
         */ 
        void reset();
        
        /**
         * @brief this test function prints the rectangle 
         * paramaters to the compiler
         */
        void test_frog();
        
};

#endif