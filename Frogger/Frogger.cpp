#include "Frogger.h"

// level one initiailization has already been done
Frogger::Frogger(Frog *frog, int grid, int w, int h)
{
    this->frog = frog; // one frog object per run
    
    current_level = 1;
    initializeParams(w, h, grid); // initialize the software parameters
    initializeEmbeddedSystem(); // initialize the hardware paramaters
    setupLevelOne();

    intro.selection = 0;
    intro.tutorial_screens = 0;

    introScreen = true;
    nextLevel = false;
    play_game = false;
    tutorial = false;
    settings = false;
}

GraphicEngine graphics;

void Frogger::initializeParams(int w, int h, int grid)
{
    // screen sizes
    lcd_w = w; // width
    lcd_h = h; // height
    state_frog = 0;
    end_post = false;
    turtle_state = 0;
    
    water_level = 48- 4*6; // row 7 and up is the water level
    frogDie = false;
    frogOnLog = false;
    goal_post_xpos = (36); // generate random position for end post
    next_goal = false;
    
    // grid values
    grid = 4; // size of game grid system
    grid_width = 22; // size of screen width in grid units
}

void Frogger::initializeLevelTwo()
{
    setupLevelTwo();
}

void Frogger::initializeEmbeddedSystem()
{
    //game setup
    graphics.init(); // initialize the LCD object
    graphics.contrast(); // set the contrast to 0.4
    graphics.backLightOn(); // turn on the backlight

    gamepad.init();  // initialize the actual embedded system 
}

void Frogger::setupLevelOne()
{
    // vehicle objects
    setupLevelOneRow();
    setupLevelOneXPos();
    setupLevelOneSprites();    
    setupLevelOneDir();
   
    // log objects
    setupLogsLevelOne();
}

// called by frogger engine
void Frogger::setupLevelTwo()
{
    // setup vehicles
    setupLevelTwoRows();
    setupLevelTwoXPos();
    setupLevelTwoSprites();  
    setupLevelTwoDir();

    //log objects    
    setupLogLevelTwo();
}

void Frogger::setupBonusRound()
{
    setupBonusRows();
    setupBonusXpos();
    setupBonusTwoDir();
    setupBonusSprites();
}

/* SETUP CALLS */
void Frogger::setupLogsLevelOne()
{
    setLogLevelOneXPos();
    setLogLevelOneRow();
    setLogLevelOneDir();
    setLogLevelOneSprites();
}

void Frogger::setupLogLevelTwo()
{
    setLogLevelTwoXPos();
    setLogLevelTwoRow();
    setLogLevelTwoSprite();
    setLogLevelTwoDir();
}
/* SETUP CALLS */

//main function that starts the game
void Frogger::start()
{     
    //keep reading and processing user input
    while(1) {
        graphics.clear(); // clear the lcd screen 
        if(introScreen) { // shows tutorial, setting
            graphics.getPointerPos(intro.selection); // draw the initial pointer pos
            home(); // draw menu selections
        } else if (play_game) { // shows actual gameplay
            run();
            //printf("show turtle state %d" turtle_state);
        } else if(tutorial) {
            gotoPage();
        } else if(bonus_round) {
            run_bonus();
        }   
        graphics.refresh(); // refresh the lcd screen
        wait_ms(85); // fpms
    } 
}

void Frogger::displayIntro()
{
    graphics.introOne();
    wait_ms(10);
    graphics.refresh(); // refresh the lcd screen

    graphics.refresh(); // refresh the lcd screen
    graphics.clear();
    graphics.introTwo();
    wait_ms(3000);
    graphics.refresh(); // refresh the lcd screen

    graphics.refresh(); // refresh the lcd screen
    graphics.clear();
    wait_ms(5000);
    graphics.refresh(); // refresh the lcd screen 
}

void Frogger::displayLevelIntro()
{
    graphics.clear();
    graphics.newLevel1();
    wait_ms(1000);
    graphics.refresh(); // refresh the lcd screen

    graphics.refresh(); // refresh the lcd screen
    graphics.clear();
    graphics.newLevel2();
    wait_ms(1000);
    graphics.refresh(); // refresh the lcd screen

    graphics.refresh(); // refresh the lcd screen
    graphics.clear();
    wait_ms(1000);
    graphics.refresh(); // refresh the lcd screen
}

void Frogger::run()
{
    checkProgression();
    
    //printf("FROG y position, %d", frog->y);
    //printf("Display the current level, %d", current_level);   

    drawBackGround();
        
    generateLevelOneGoalPost();
            
    process_input(); // user controls the frog object
       
    actOnFrogPos();
        
    graphics.showFrog(frog->x, frog->y, frog->width, frog->height, state_frog); // display current position of frog 
}

void Frogger::run_bonus()
{
    current_level = 0;
    checkBonusProgress(); 
      
    //printf("FROG y position, %d", frog->y);
    //printf("Display the current level, %d", current_level); 
    
    drawBackGround();    
    generateLevelOneGoalPost();     
    process_input(); // user controls the frog object
    actOnFrogBonus();
    checkFrogInDeathZone();

    graphics.showFrog(frog->x, frog->y, frog->width, frog->height, state_frog); // display current position of frog 
    graphics.drawVoidBackGround();
}

void Frogger::checkFrogInDeathZone()
{
    if(frog->x < 35 || frog->x > 55)
    {
        frog->reset();
    }
}

void Frogger::checkProgression()
{ 
    if((frog->y == 48 - 4*11 || frog->y == 48 - 4*10)){
        displayLevelIntro();
        frog->reset();
        setupLevelTwo();
        current_level++;
    }
}

void Frogger::checkBonusProgress()
{ 
    if((frog->y == 48 - 4*11 || frog->y == 48 - 4*10)){
        frog->reset();
        setupLevelOne();
        current_level++;
        bonus_round = false;
        introScreen = true;
    }
}

void Frogger::actOnFrogPos()
{
    if(frog->y >= water_level)
    {
        frogDie = false;
        runCurrentLevel(); // add velocity to level vehicles and logs

    } else {
        frogDie = true;
        runCurrentLevel(); // add velocity to level vehicles and logs
            
        if((!frogOnLog) && (frog->y != 48 - 4*11 && frog->y != 48 - 4*10) && frog->x != 42){
            frog->reset();
        }
    }
}

void Frogger::actOnFrogBonus()
{
    if(frog->y != 48 - 4*11 && (frog->y != 48 - 4*10)) {     
        runCurrentLevel();
        graphics.drawVoidBackGround();
    } 
}

void Frogger::home()
{
    determineSelection();
    graphics.drawMenu();   
}

void Frogger::determineSelection()
{
   if(intro.selection < 2 && gamepad.B_pressed()){
        graphics.getPointerPos(intro.selection++);

    } else if(intro.selection > 0 && gamepad.X_pressed()){
        graphics.getPointerPos(intro.selection--);
    }
    
    //printf("Current user selection,%d", intro.selection);
    
    wait_ms(10);

    if(gamepad.A_pressed())
    {
        gotoPage();
    }
}

void Frogger::gotoPage()
{
    switch(intro.selection)
    {
        case 0:
            play_game = true;
            introScreen = false;
            tutorial = false;
            settings = false;
            break;
        case 1:
            displayTutorial();
            play_game = false;  
            introScreen = false;
            tutorial = true;
            settings = false;
            break;
        case 2: // bonus round
            setupBonusRound();
            bonus_round = true;
            play_game = false;
            introScreen = false;
            tutorial = false;
            settings = false;
            break;
    }
}

void Frogger::displayTutorial()
{
    wait_ms(15);  

    switch(intro.tutorial_screens)
    {
        case 0:
            graphics.drawTutor1();
            gotoNextTutorialSlide();
            break;
        case 1:
            graphics.drawTutor2();
            gotoNextTutorialSlide();
            break;
        case 2:
            graphics.drawTutor3();
            gotoNextTutorialSlide();
            break;
        default:
            home();
            intro.selection = 0;            
    }
}

void Frogger::gotoNextTutorialSlide()
{
    if(gamepad.A_pressed()){
        intro.tutorial_screens++;
        wait_ms(25);  
    }
    
    if(intro.tutorial_screens > 2){
        intro.tutorial_screens = 7;
        tutorial = false;
    }
    
    //printf("Current tutorial screen, %d" intro.tutorial_screen);
}

void Frogger::drawBackGround()
{
    graphics.drawDangerZone();
    graphics.drawSafetyLanes(); 
}

void Frogger::generateLevelOneGoalPost()
{
    graphics.drawEndPost(goal_post_xpos);
}

int Frogger::randEndPost()
{
    return (rand() % 80) + 12;      
}



void Frogger::process_input() {
    //determine the input 
    if(gamepad.A_pressed()){
        state_frog = 1;
        moveFrog(1,0); // move frog right
        frogOnLog = false;
    } else if(gamepad.X_pressed()){
        state_frog = 0;
        moveFrog(0,-1);// move it down
        frogOnLog = false;
    } else if(gamepad.B_pressed()){
        state_frog = 3;
        moveFrog(0,1); // move the frog up
        frogOnLog = false;
    } else if(gamepad.Y_pressed()){
        state_frog = 2;
        moveFrog(-1,0); // move the frog left
        frogOnLog = false;
    } 
    wait_ms(10);
}

void Frogger::drawFrogStates()
{
    state_frog++;
    graphics.showFrog(frog->x, frog->y, frog->width, frog->height, state_frog); // display current position of frog
    state_frog--;
}

//moves the frog around the grid
void Frogger::moveFrog(int xWay, int yWay)
{
    //increment the left side of the chicken by a value of the grid size
    frog->x += xWay * 4;
    // printf("Current frog x, %d", frog->x);
    
    //increment the top side by a value of grid sizw
    frog->y += yWay * 4;
    // printf("Current frog y, %d", frog->y);

    // update rect parameters
    frog->left_side = frog->x;
    frog->right_side = 6 + frog->x;
    frog->up = frog->y;
    frog->down = 4 + frog->y;
    
    //frog->test_frog();
}

/* ENGINE CALLS */
void Frogger::runCurrentLevel()
{
    switch (current_level)
    {
        case 0:
            runBonusRound();
            break;
        case 1:
            runLevelOne();
            break;
        case 2:
            runLevelTwo();
            break;
    }
}

void Frogger::runLevelOne()
{
    moveVehiclesLevelOne(); // increment the x pos and display
    moveLogsLevelOne();  
}

void Frogger::runLevelTwo()
{
    moveVehiclesLevelTwo();
    moveLogsLevelTwo();
}

void Frogger::runBonusRound()
{
    moveBonusObjects();
}
/* ENGINE CALLS */

/* ENGINE RUN */
void Frogger::moveVehiclesLevelOne()
{
    moveVehicle(car_row_one_one, 'S', 3);
    moveVehicle(car_row_two_one, 'M', 2);
    moveVehicle(car_row_three_one, 'S', 3);
    moveVehicle(car_row_four_one, 'M', 4);    
}

void Frogger::moveVehiclesLevelTwo()
{
    moveVehicle(car_row_one_two, 'M', 4);
    moveVehicle(car_row_two_two, 'M', 3);
    moveVehicle(car_row_three_two, 'F', 4);
    moveVehicle(car_row_four_two, 'F', 3);      
}

void Frogger::moveLogsLevelOne()
{
    moveVehicle(row_one_log, 'S', 3);
    moveVehicle(row_two_log, 'M', 2);
    moveVehicle(row_three_log, 'S', 3);    
}

void Frogger::moveLogsLevelTwo()
{
    moveVehicle(level_row_one, 'F', 2);
    moveVehicle(level_row_two, 'M', 2);
    moveVehicle(level_row_two, 'F', 3);
}

void Frogger::moveBonusObjects()
{
    moveVehicle(bonus_row_one, 'F', 4);
    moveVehicle(bonus_row_two, 'U', 3);
    moveVehicle(bonus_row_four, 'U', 3); 
    moveVehicle(bonus_row_seven, 'U', 2);
    moveVehicle(bonus_row_eight, 'F', 3); 
}
/* ENGINE RUN */

void Frogger::checkFrogOnWater()
{
    if(frog->y < water_level) // if the frog is past the safety lane
    {
       frogDie = true; // frog will die if not on turtle/log
    } else {
        frogDie = false;   
    }
}

void Frogger::moveVehicle(Object *row, char c, int array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        moveIndividualObject(&row[i], c);
        checkCollison(row[i]); // check if the frog has crashed/on log
        checkTurtleDrown();
    }
}

void Frogger::checkTurtleDrown()
{
    // if the frog is on the row of the turtles and 
    // turtles are under water, then frog is dead
    if(frog->y == (48-(4*8)) 
    && (turtle_state >= 3001)
    && current_level == 2){
        frog->reset(); // frog is dead
    }
}

void Frogger::moveIndividualObject(Object *vehicle, char c){
    switch(c)
    {
        case 'S':
            vehicle->speedSlow(vehicle->object.dir);
            break;
        case 'M':
            vehicle->speedMedium(vehicle->object.dir);
            break;  
        case 'F':
            vehicle->speedFast(vehicle->object.dir);
            break;
        case 'U':
            vehicle->speedUltra(vehicle->object.dir);
            break;
    }
    checkOutOfBounds(vehicle);
    checkFrogOutOfBounds(); 
    graphics.showObj(vehicle, turtle_state);  // display to screen
    updateTurtleState();
}



void Frogger::updateTurtleState()
{
    switch(turtle_state)
    {
        case 0 ... 1000:
            turtle_state++;  
            break;
        case 1001 ... 2000:
            turtle_state++;  
            break;
        case 2001 ... 3000:
            turtle_state++;  
            break;
        case 3001 ... 4000:
            turtle_state++;  
            break;
        case 4001 ... 5000: turtle_state++; break;
        case 5001: turtle_state = 0; break;
    }
}
/* ENGINE RUN */

/* CHECKERS */
void Frogger::checkOutOfBounds(Object *obj)
{
    if(obj->object.x > 84 + randCars()){
        obj->object.x = -2;

    } else if(obj->object.x < -8) {
        obj->object.x = 84;
    }
}

void Frogger::checkFrogOutOfBounds(){
    if(frog->x > 84){
        frog->reset(); // set the frog back to the start
        graphics.printLoser();

    } else if(frog->x < 0) {
        frog->reset();
        graphics.printLoser();
    }
}

void Frogger::checkCollison(Object object)
{
    if(!(frog->up >= object.rectangle.bottom ||
    (frog->right_side <= object.rectangle.left_side)  ||
    (frog->down <= object.rectangle.up) ||
    (frog->left_side >= object.rectangle.right_side))) {
        moveFrogWithLog(object);
        checkFrogAction(object); // check to do what do with frog based on height    
    }
}

void Frogger::checkFrogReachedRiver()
{
    if(frog->y < water_level) {
       frogDie = true; // frog can die if it touches water
    } else {
        frogDie = false;
    }
}

void Frogger::checkFrogAction(Object log)
{
    if(frog->y < water_level) { // frog is in water zone
        frogOnLog = true; // moving same speed as log
        frogDie = false;

    } else { // frog is on the road 
        state_frog = 0; // facing upward
        
        frog->reset(); // crashed with car so reset
        
        frogOnLog = false;
        frogDie = false;
    }
    
    if(frog->y == (48 - (4*10)))
    {
        end_post = true;   
    }
}

void Frogger::moveFrogWithLog(Object log)
{
    switch (log.object.dir)
    {
        case 1:
            frog->x += log.speed; // move it right
            break;
                
        case 2:
            frog->x = frog->x - log.speed; // move it left
            break;
    }
    
    //printf("Log speed: %d", log.speed);
}

/* CHECKERS */

/* X POS */
void Frogger::setupLevelOneXPos()
{
    setupRowDistance(car_row_one_one, 20 , 3);
    setupRowDistance(car_row_two_one, 25, 2);
    setupRowDistance(car_row_three_one, 30, 3);
    setupRowDistance(car_row_four_one, 25, 4);  
}

void Frogger::setLogLevelOneXPos()
{
    setupRowDistance(row_one_log, 20, 3);
    setupRowDistance(row_two_log, 30, 2);
    setupRowDistance(row_three_log, 25, 3);
}

void Frogger::setLogLevelTwoXPos()
{
    setupRowDistance(level_row_one, 20, 2);
    setupRowDistance(level_row_two, 30, 2);
    setupRowDistance(level_row_three, 25, 3);
}

void Frogger::setupLevelTwoXPos()
{
    setupRowDistance(car_row_one_two, 15, 4);
    setupRowDistance(car_row_two_two, 20, 3);
    setupRowDistance(car_row_three_two, 25, 4);
    setupRowDistance(car_row_four_two, 25, 3);  
}

void Frogger::setupBonusXpos()
{
    setupRowDistance(bonus_row_one, 15, 4);
    setupRowDistance(bonus_row_two, 20, 3);
    setupRowDistance(bonus_row_four, 25, 3);

    setupRowDistance(bonus_row_seven, 20, 2);
    setupRowDistance(bonus_row_eight, 25, 3);
}

void Frogger::setupRowDistance(Object *objects, int dis, int array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        setDistance(&objects[i], dis);
        dis += dis; // ensure that each object has appropriate seperation        
    }  
}

void Frogger::setDistance(Object *object, int dis)
{
    object->setSeperation(dis);
    
    //printf("Seperation set &d", object->object.dir);
}
/* X POS */

/* ROW */

void Frogger::setupLevelOneRow()
{
    setRowObjects(car_row_one_one, 2, 3);
    setRowObjects(car_row_two_one, 3, 2);
    setRowObjects(car_row_three_one, 4, 3);
    setRowObjects(car_row_four_one, 5, 4);
}

void Frogger::setupLevelTwoRows()
{
    setRowObjects(car_row_one_two, 2, 4);
    setRowObjects(car_row_two_two, 3, 3);
    setRowObjects(car_row_three_two, 4, 4);
    setRowObjects(car_row_four_two, 5, 3);
}

void Frogger::setLogLevelOneRow()
{
    setRowObjects(row_one_log, 7, 3);
    setRowObjects(row_two_log, 8, 2);
    setRowObjects(row_three_log, 9, 3);
}

void Frogger::setLogLevelTwoRow()
{
    setRowObjects(level_row_one, 7, 2);
    setRowObjects(level_row_two, 8, 2);
    setRowObjects(level_row_three, 9, 3);
}

void Frogger::setupBonusRows()
{
    setRowObjects(bonus_row_one, 2, 4);
    setRowObjects(bonus_row_two, 3, 3);
    setRowObjects(bonus_row_four, 4, 3);

    setRowObjects(bonus_row_seven, 7, 2);
    setRowObjects(bonus_row_eight, 9, 3);
}

void Frogger::setRowObjects(Object *objects, int row, int array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        createRow(&objects[i], row);   
        //printf("row number set &d", objects[i]->object.row); 
    }  
}

void Frogger::createRow(Object *object, int row)
{
    object->setRow(row);  
}
/* ROW */

/* SPRITES */
void Frogger::setupLevelOneSprites()
{
    setSpriteObjects(car_row_one_one, 'X', 3);
    setSpriteObjects(car_row_two_one, 'N', 2);
    setSpriteObjects(car_row_three_one, 'B', 3);
    setSpriteObjects(car_row_four_one, 'R', 4);  
}

void Frogger::setupLevelTwoSprites()
{
    setSpriteObjects(car_row_one_two, 'R', 4);
    setSpriteObjects(car_row_two_two, 'L', 3);
    setSpriteObjects(car_row_three_two, 'N', 4);
    setSpriteObjects(car_row_four_two, 'X', 3);  
}

void Frogger::setLogLevelOneSprites()
{
    setSpriteObjects(row_one_log, 'G',3);
    setSpriteObjects(row_two_log, 'M', 2);
    setSpriteObjects(row_three_log, 'G', 3);
}

void Frogger::setLogLevelTwoSprite()
{
    setSpriteObjects(level_row_one, 'M', 2);
    setSpriteObjects(level_row_two, 'T', 2);
    setSpriteObjects(level_row_three, 'G', 3);
}

void Frogger::setupBonusSprites()
{
    setSpriteObjects(bonus_row_one, 'S', 4);
    setSpriteObjects(bonus_row_two, 'S', 3);
    setSpriteObjects(bonus_row_four, 'S', 3);

    setSpriteObjects(bonus_row_seven, 'S', 2);
    setSpriteObjects(bonus_row_eight, 'S', 3);
}

void Frogger::setSpriteObjects(Object *objects, char c, int array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        setSprite(&objects[i], c);
        //printf("sprite set &d", objects[i]->c);
    }    
}

void Frogger::setSprite(Object *object, char c)
{
   object->setSprite(c);  
}
/* SPRITES */

/* DIR */
void Frogger::setupLevelOneDir()
{
    setDirObjects(car_row_one_one, 2, 3);
    setDirObjects(car_row_two_one, 1, 2);
    setDirObjects(car_row_three_one, 2, 3);
    setDirObjects(car_row_four_one, 1, 4);  
}

void Frogger::setupLevelTwoDir()
{
    setDirObjects(car_row_one_two, 1, 4);
    setDirObjects(car_row_two_two, 2, 3);
    setDirObjects(car_row_three_two, 1, 4);
    setDirObjects(car_row_four_two, 2, 3);  
}

void Frogger::setLogLevelOneDir()
{
    setDirObjects(row_one_log, 1, 3);
    setDirObjects(row_two_log, 2, 2);
    setDirObjects(row_three_log, 1, 3);
}

void Frogger::setLogLevelTwoDir()
{
    setDirObjects(level_row_one, 1, 2);
    setDirObjects(level_row_two, 2, 2);
    setDirObjects(level_row_three, 1, 3);
}

void Frogger::setupBonusTwoDir()
{
    setDirObjects(bonus_row_one, 2, 4);
    setDirObjects(bonus_row_two, 1, 3);
    setDirObjects(bonus_row_three, 2, 4);
    setDirObjects(bonus_row_four, 1, 3);

    setDirObjects(bonus_row_six, 1, 2);
    setDirObjects(bonus_row_seven, 2, 2);
    setDirObjects(bonus_row_eight, 1, 3); 
}

void Frogger::setDirObjects(Object *objects, int dir, int array_size)
{
   for(int i = 0; i < array_size; i++)
    {
        setDir(&objects[i], dir);
        //printf("direction set &d", objects[i]->object.dir);
    }    
}

void Frogger::setDir(Object *object, int dir)
{
    object->setDir(dir);  
}
/* DIR */

// so the user does not predict when the next car is coming
int Frogger::randCars()
{
    return (rand() % 4) + 1;
}
