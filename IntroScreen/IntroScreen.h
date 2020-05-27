#ifndef INTROSCREEN_H
#define INTROSCREEN_H

/** IntroScreen Class
 * @brief used to keep track of the current position of the menu
 * @author Tarek Bessalah
 * @date May, 2020
 */
class IntroScreen
{  
    public:
        /** Gets the value of selection
         * @return the current pointer selection number
         */
        int selection;
        
        /** Gets the page of tutorial screen
         * @return the current pointer tutorial screen
         */
        int tutorial_screens;
};

#endif