#ifndef FROGGER_H
#define FROGGER_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#include "Frog.h"
#include "GraphicEngine.h"
#include "WaterSprites.h"
#include "Vehicle.h"
#include "Background.h"
#include "IntroScreen.h"

#include <vector>
#include <stdio.h> 
#include <cstddef>
#include <vector>

/** Frogger Class
 *
 * @brief Frogger class that runs the entire game, in charge of lcd calls
 * @brief moving objects, checking for collision etc.
 * @author Tarek Bessalah
 * @date May, 2020
 */
class Frogger
{
    public: 
    
        /** @param frog object that frogger class keeps track of 
         */
        Frog *frog; // one frog object

        /** Constructor */
        Frogger();
        
        /** Constructor
         * @brief This constructor is the main engine of the frogger class
         * @param frog - actual frog object that user controls
         * @param w - the size of the lcd width
         * @param h - the size of the lcd height
         */ 
        Frogger(Frog *frog, int grid, int w, int h); // constructor
        
    public:
    
        /** @brief current level of the game (starts from 1)
         */
        int current_level;
        
        /** @brief current state of the frog, used to draw the animation of the frog
         */
        int state_frog;
        
        /** @brief if the frog is in the water level, it can die now if it is
         * not on the log
         */
        bool frogDie;
        
        /** @brief store the x position of the goal post
         */
        int goal_post_xpos;
        
        /** @brief user is playing the game right now
         */
        bool play_game;
        
        /** @brief user is currently in the main menu
         */
        bool introScreen;
        
        /** @brief user is currently reading the tutorial manual
         */
        bool tutorial;
        
        /** @brief user is currently reading the settings
         */
        bool settings;
        
        /** @brief if this on, then there exists an end post 
         */
        bool end_post;
        
        /** @brief frog is successful in current level
         */
        bool nextLevel;
        
        /** @brief informs if the frog reached end post
         */
        bool next_goal;
        
        /** @brief this means that bonus round is screen is on
         */
        bool bonus_round;
        
        /** @brief y coord (in rows) value of the water level
         */
        float water_level;
         
        /** @brief if the frog collides with log object and is above second
         * safety lane, it is attached to the object (going same speed)
         */
        bool frogOnLog; 
        
        /** @brief current state of the turtles, this is used to draw the animation
         * of the turtle in level 2
         */
        int turtle_state;
        
    public:
    
        /** @brief local hardware object, used for sounds, LED, and button controls etc.
         */
        Gamepad gamepad;
        
        /** @brief class object that keeps track of the current pointer position, current page
         */
        IntroScreen intro;
        
        /** @brief size of the game grid
         */
        int grid; 
        
        /** @brief size of the game grid
         */
        int row_number;
        
        /** @brief size of the lcd width in grid units
         */
        int grid_width;
        
        /** @brief size of the lcd width
         */
        int lcd_w;
        
        /** @brief size of the lcd height
         */
        int lcd_h;

    public:

        /** @brief level one row 1 vehicle objects
         */        
        Object car_row_one_one[3]; 
        
        /** @brief level one row 2 vehicle objects
         */  
        Object car_row_two_one[2];
        
        /** @brief level one row 3 vehicle objects
         */  
        Object car_row_three_one[3];
        
        /** @brief level one row 4 vehicle objects
         */  
        Object car_row_four_one[4];

        /** @brief level one row 7 log objects
         */
        Object row_one_log[3];
         
        /** @brief level one row 8 log objects
         */
        Object row_two_log[2]; 
        
        /** @brief level one row 9 log objects
         */
        Object row_three_log[3]; 


        /** @brief level two row 1 vehicle objects
         */      
        Object car_row_one_two[4];
        
        /** @brief level two row 2 vehicle objects
         */ 
        Object car_row_two_two[3];
        
        /** @brief level two row 3 vehicle objects
         */ 
        Object car_row_three_two[4];
        
        /** @brief level two row 4 vehicle objects
         */ 
        Object car_row_four_two[3];

        /** @brief level 2 row 7 log objects
         */
        Object level_row_one[2];
        
        /** @brief level 2 row 7 log objects
         */
        Object level_row_two[2];
        
        /** @brief level 2 row 7 log objects
         */
        Object level_row_three[3];


        /** @brief bonus level row 1 vehicle objects
         */
        Object bonus_row_one[4];
        
        /** @brief bonus level row 2 vehicle objects
         */
        Object bonus_row_two[3];
        
        /** @brief bonus level row 3 vehicle objects
         */
        Object bonus_row_three[4];
        
        /** @brief bonus level row 4 vehicle objects
         */
        Object bonus_row_four[3];
        
        /** @brief bonus level row 6 vehicle objects
         */
        Object bonus_row_six[2];
        
        /** @brief bonus level row 7 vehicle objects
         */
        Object bonus_row_seven[2];
        
        /** @brief bonus level row 8 vehicle objects
         */
        Object bonus_row_eight[3];
            
    public:
    
        /** @brief function that runs the logic of the game
         *  @brief can update the current level
         *  @brief gives velocity to objects at every frame
         */
        void run();
        
         /** @brief function that runs the bonus round of the game
          *   @brief draws the black background
          *   @brief a different outlook to frogger
          */
        void run_bonus();
        
         /** @brief bonus function that acts on the frog, such
          *  @brief collision detection, if the frog goes to black 
          *  @brief background
          */
        void actOnFrogBonus();
        
         /** @brief bonus level row 8 vehicle objects
          */
        void checkBonusProgress();
        
         /** main function reponsible for turtle states
          * @brief increments the state of the turtle
          * @brief based on the state, frog can drown
          */
        void updateTurtleState();
        
        /**  @brief main function that acts on the frog, such
          *  @brief collision detection, if the frog is on water 
          *  @brief level progression as well
          */
        void actOnFrogPos();
        
         /** @brief displays the main menu selections
          *  @details "USE X AND B to scroll" & "PRESS A TO SELECT"
          */
        void home();
        
         /** @brief determines the current selection of menu based on X AND B
          */
        void determineSelection();
        
         /** @brief goes to the page based on menu selection
          */
        void gotoPage();
        
         /** @brief goes to page on selection, updates the boolean values
          */
        void selectOption();
        
         /** @brief at every frame, this function checks if the frog is at the
          *  @brief the location of the goal post
          */
        void checkLevelProgression();
        
         /** @brief function that generates a random x pos for the goal post
          *  @brief main purpose is to add challenge to the game
          */
        int randEndPost();
        
         /** @brief if the frog reaches the water level (48-4*6) coordinates
          *  @bried the frog will need to be on a log to survive
          */
        void checkFrogOnWater();
        
         /** @brief based on the current pos of the frog, it can either kill
          *  @brief it or put it on top of a log, or collide with a car (if on roads)
          *  @param accepts a Object class to check if the rectangle size of the vehicle
          */
        void checkFrogAction(Object log);
        
         /** @brief sets up the y pos of all level 2 vehicles
          */
        void setupLevelTwoRows();

        /** @brief adds velocity to objects, sets up the background, and goal- 
         *  @brief post of the bonus round
         */
        void runBonusRound();
        
         /** @brief setup the y pos of all vehicles of the bonus round
          */
        void setupBonusRows();
        
         /** @brief setup the x pos of the vehicles 
          */
        void setupBonusXpos();
        
         /** @brief setup the direction of the vehicles in the bonus round
         */
        void setupBonusTwoDir();
        
         /** @brief setup the sprite objects of vehicles by giving them a 
          *  @brief specific char value, the graphic engine will detect the type of sprite
          */
        void setupBonusSprites();
        
         /** @brief give velocity to objects based on the speed defined earlier in the bonus play
          */
        void moveBonusObjects();

        /** @brief when it is detected that the frog collided with a log object
         *  @bried this function will give the frog the same speed as the log
         */
        void moveFrogWithLog(Object log);
        
         /** @brief check if the turtle is under water based on the current
          *  @brief current state of the turtle, if it is under water, the frog 
          *  @brief will die if it is on it
          */
        void checkTurtleDrown();
        
         /** @brief add safety lane sprites, add the danger zone sprites
          */
        void drawBackGround();
        
         /** @brief setup the level one goal post, give it x pos and y pos
          */
        void generateLevelOneGoalPost();
        
         /** @brief generate the goal post based on the rand() function
          */
        void setUpGoalPost();
        
         /** @brief main function that is in charge of detection system of
          *  @brief the entire engine, if the frog is on water, it would set the 
          *  @brief frogOnLog function to true so the frog moves alongised the log
          *  @param Object - reads in the object rectangle paramaters, to compare it with frog's
          */
        void checkCollison(Object object);
        
         /** @brief sets up the x pos of all the vehicles and objects
          *  @param accepts the pointer object of the object to give it y pos
          *  @param dis - actual distance between each other
          *  @param array_size - the number of vehicles that should be assigned
          */
        void setupRowDistance(Object *objects, int dis, int array_size);
        
         /** @brief sets up the x pos of all the vehicles and objects, called by
          *  @brief setupRowDistance usually
          *  @param accepts the pointer object of the object to give it y pos
          *  @param dis - actual distance between each other
          */
        void setDistance(Object *object, int dis);

         /** @brief sets up the x pos of all the vehicles and objects
          *  @param accepts the pointer object of the object to give it y pos
          *  @param row - actual distance between each other
          *  @param array_size - the number of vehicles that should be assigned
          */
        void setRowObjects(Object *objecs, int row, int array_size);
        
         /** @brief assign row to individual vehicle object
          *  @param object - pointer array of object
          *  @param row - the row of the vehicles
          */
        void createRow(Object *object, int row);
        
         /** @brief sets the sprite objects of the vehicles (each row will have one kind)
          *  @param accepts the pointer object of the object to give it a sprite
          *  @param c - the character of the sprite, the graphic class will know what type of sprite
          *  @param array_size - the number of vehicles that should be assigned
          */
        void setSpriteObjects(Object *objects, char c, int array_size);
        
         /** @brief sets the sprite objects of one vehicle(each row will have one kind)
          *  @param accepts the pointer object of the object to give it a sprite
          *  @param c - the character of the sprite, the graphic class will know what type of sprite
          */
        void setSprite(Object *object, char c);

         /** @brief gives the direction of the vehicle, based on two #s: 1(right) or 2(left)
          *  @param accepts the pointer object of the object to give it a sprite
          *  @param dir - direction of the vehicle arrays
          *  @param array_size - the number of vehicles that should be assigned
          */
        void setDirObjects(Object *objecs, int dir, int array_size);
        
         /** @brief gives direction to an individual object
          *  @param accepts the pointer object of the object to give it a direction
          *  @param dir - should be either 1 (right) or 2(left)
=         */
        void setDir(Object *objecs, int dir);
        
        /** @brief moves the log objects based on the velocity assigned before 
         */
        void moveLogsLevelOne();
        
        /** @brief checks if the frog is passed water_level, then sets frogDie 
         */
        void checkFrogReachedRiver();
        
         /** @brief increments the current tutorial slide to view the next page 
         */
        void gotoNextTutorialSlide();
        
         /** @brief showss the page of the tutorial to the user
          */
        void displayTutorial();
        
         /** @brief checks if the frog is in the x and y coordinates of the end goal 
          */
        void goalReached();
        
         /** @brief checks if the frog has reached the end goal, then if it does, it goes next level
          */
        void checkProgression();
        
         /** @brief adds velocity to the level 2 logs
          */
        void moveLogsLevelTwo();
        
         /** @brief based on the frog state, it draws the animation of the moving frog
          */
        void drawFrogStates();

         /** @brief this increments the velocity of all the objects inside by 0.4
          */
        void speedSlow();
        
         /** @brief this increments the velocity of all the objects inside by 0.6
          */
        void speedMedium();
        
         /** @brief this increments the velocity of all the objects inside by 0.8
          */
        void speedFast();
        
         /** @brief sets up the x pos, rectangle, y pos of the vehicles in bonus 
          */
        void setupBonusRound();
        
         /** @brief sets up the x pos, rectangle, y pos of the vehicles in level one 
          */
        void setupLevelOne();
        
         /** @brief sets up the rows of all lanes in the level one
          */
        void setupLevelOneRow();
        
         /** @brief sets up the x positions of all lanes in the level one
          */
        void setupLevelOneXPos();
        
         /** @brief sets up the sprites of all lanes in the level one
          */
        void setupLevelOneSprites();
        
         /** @brief sets up the directions of all lanes in the level one
         */
        void setupLevelOneDir();

        /** @brief sets up the log positons and speed, and directions
         */
         void setupLogsLevelOne();

        /** @brief sets up the x position of logs of level one
         */
        void setLogLevelOneXPos();
        
        /** @brief sets up the y position of logs of level one
         */
        void setLogLevelOneRow();
        
        /** @brief sets up the rows position of logs of level one
         */
        void setLogLevelOneDir();
        
        /** @brief sets up the sprites of logs of level one
         */
        void setLogLevelOneSprites();

        /** @brief sets up the x pos, rectangle, y pos of the vehicles in level two 
         */
        void setupLevelTwo();
        
         /** @brief generate random positions of cars when it goes out of bounds
          *  @brief this makes it appear randomly and adds challenge to it 
          */
        int randCars();

         /** @brief sets up the x positions of all lanes in the level two
          */
        void setupLevelTwoXPos();
        
        /** @brief sets up the sprites of all lanes in the level two
         */
        void setupLevelTwoSprites();
        
        /** @brief sets up the dir of all lanes in the level two
         */  
        void setupLevelTwoDir();

        /** @brief sets up the log objects, and gives them y, x, speed, and sprites
         *  @brief of the sprite
         */   
        void setupLogLevelTwo();

        /** @brief sets up the log objects, and gives them x position
         */
        void setLogLevelTwoXPos();
        
        /** @brief sets up the logs of level two (rows)
         */
        void setLogLevelTwoRow();
        
         /** @brief sets up the level two sprites of the logs 
         */
        void setLogLevelTwoSprite();
        
         /** @brief sets up the level two log directions 
         */
        void setLogLevelTwoDir();
        
         /** @brief initialized the x pos, the y pos, and creates the arrays for 
          *  @details Only called when the frog progresses, to next level to save memory
          */
        void initializeLevelTwo();

         /** @brief displays the object to the lcd, calls the graphics class 
          */
        void displayObject(Object &temp_object);  
       
    public:
    
         /** @brief main function that starts that checks if the 
          *  @brief user is at home or playing the game based on input
         */
        void start();
        
         /** @brief reads the input based on the current state of gampad
          *  @brief based on the user choice, the lcd changes 
          *  @param A,B,X etc. are used for the user to move around the screen
          */
        void input();  
        
         /** @brief this is the main function that changes the position of the frog
          *  @param A,B,X are used for the user to move around the screen
          */
        void process_input(); 
        
         /** @brief this function calls the graphic engine to clear the screen
         */
        void clear();
        
         /** @brief this function adds velocity to the vehicles for every frame
          *  @details use this function when you want to move level one objects
          */
        void runLevelOne();
        
         /** @brief this function adds velocity to the vehicles for every frame
          *  @details use this function when you want to move level two objects
          */
        void runLevelTwo();
        
         /** @brief based on the defined speed, all the objects move
          *  @details this is a level one call 
          */
        void moveVehiclesLevelOne();
        
         /** @brief based on the defined speed, all the objects move
          *  @details this is a level two call 
          */
        void moveVehiclesLevelTwo();
        
         /** @brief move vehicles across the lcd, this function also checks for
          *  @brief out of bound vehicles, as well as checks for collisions with 
          *  @brief frog object in the screen
          *  @param row - accepts a vehicle array object to add velocity to the x pos
          *  @param c -based on the char, this could be slow, medium, fast, ultra(really fast)
          *  @param array_size - the number of the vehicles in the particular row
          */
        void moveVehicle(Object *row, char c, int array_size);

         /** @brief moves individual object in the lcd
          *  @param vehicle - accepts a vehicle pointer to change the individual speed
          *  @param c -based on the char, this could be slow, medium, fast, ultra(really fast)
          */      
        void moveIndividualObject(Object *vehicle, char c);
        
         /** @brief this always checks for every vehicle if it is on the screen
          *  @param object pointer - based on the pointer, it updates the x pos based on the direction
         */
        void checkOutOfBounds(Object *vehicle);
        
         /** @brief displays the animation at the beginning, with the logo, and name etc.
          */
        void displayLevelIntro();
        
         /** @brief runs the current level when called
          *  @param based on the state of the current level, the level is run 
          */
        void runCurrentLevel();
        
         /** @brief initialize the paramaters that are used throughout the engine such as turtle states
          *  @param w - the lcd width 
          *  @param y - the lcd height 
          *  @param grid - size of grid on the lcd screen
          */
        void initializeParams(int w, int h, int grid);
        
         /** @brief this initialized the screen, the gamepad, and sets initial values
          */
        void initializeEmbeddedSystem();
        
         /** @brief based on the frog y position check if it has passed the water_level
          */
        void checkIfFrogIsInWater();
        
         /** @brief this function moves the frog based on the given input
          *  @param xWay - this function changes the x value of the frog based on input
          *  @param yWay - this function changes the y value of the frog 
          */
        void moveFrog(int xWay, int yWay);
        
         /** @brief runs the game
         */
        void game();
        
         /** @brief this function calls graphic engine to refresh the lcd
          */
        void refresh();
           
         /** @brief creates the safety lanes at row 1 and row 6
          */
        void drawSafety();
        
         /** @brief checks if the frog touches the black background in the bonus round
          *  @brief will reset the frog if it touches it
          */
        void checkFrogInDeathZone();
        
         /** @brief if the frog goes out of screen, then reset
          */
        void checkFrogOutOfBounds();
        
         /** @brief dipslays the intro page of the frogger game 
          */
        void displayIntro();
        
         /** @brief sets ups the parametes of the frogger object, initially,
          *  @brief sets the current level, frog position, and turtle states
          */
        void setup();
        
         /** @brief based on the x pos assigned on bootup the goal post is created
          *  @brief this function calls the graphics class
          */
        void createGoalPost();     
};

#endif




