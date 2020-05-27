#ifndef OBJECT_H
#define OBJECT_H

/** stores the object position */
struct ObjectInfo
{
    float x; /**< float for x value */
    int y; /**< int for y value */
    int dir; /**< int for direction value */
    char c; /**< sprite */
};

/** stores the rectangle of object */
struct Rect
{
    float right_side; /**< right side */
    float left_side; /**< left side */
    float up; /**< up */
    float bottom; /**< bottom */
}; 

/** Object Class
 *
 * @brief builds the vehicles and logs and the end posts
 * @author Tarek Bessalah
 * @date May, 2020
 */
class Object
{
    public:
    
        /** Constructor */
        Object();
        
        /** @brief holds the speed of a slow object (0.4)
         */        
        int slow;
        
        /** @brief holds the speed of a medium pace object (0.6)
         */
        int medium;
        
        /** @brief holds the speed of a fast pace object (0.8)
         */
        int fast;
        
        /** @brief holds the current row number og object
         */
        int row;
        
        /** @brief holds the value of seperation
         */
        int seperation;
        
        /** @brief size of grid
         */
        int grid;
        
        /** @brief size of lcd width
         */
        int size;
        
        /** @brief current speed
         */
        float speed;
        
        /** @brief width of the screen
         */
        float width;
        
        /** @brief height of the screen
         */
        float height;
        
        /** @brief screen width in grid units
         */
        int screenWidth;
        
        /** @brief screen height in grid units
         */
        int screenHeight;
        
        /** @brief objectinfo struct object
         */ 
        ObjectInfo object;
        
        /** @brief rectangle struct object
         */
        Rect rectangle;
            
    public:
    
        /** @brief screen width in grid units
         *  @param row - sets the row of the object
         */
        void setRow(int row);
        
        /** @brief sets the y values
         *  @param seperation - sets distance between objects in row
         */
        void setSeperation(int seperation);
        
        /**
         *  @param type - sets the sprite object
         */
        void setSprite(char type);
        
        /** @brief update the rect parameters after change of speed
         *  @param c - set the sprite
         */
        void determineVehicleRecParamaters(char c);
        
        /** @brief update the rect parameters after change of speed
         *  @param x - set the x pos
         *  @param y - set the y pos 
         */
        void updateRect(int x, int y);
        
        /** @brief create the rectangle of object
         *  @param x - set the x pos
         *  @param y - set the y pos 
         */
        void createRect(int x, int y);
        
        /** @brief creates a rectangle
         *  @param c - sets the sprite objects
         */
        void determineLogRecParamaters(char c);
        
        /** @brief ssets the rectangle parameters for collision detection
         *  @param c - sets the sprites
         */
        void determineBonusVehiclesRec(char c);
        
        /** @brief sets the direction of the vehicle
         *  @param dir - should be either 1 or 2 
         */
        void setDir(int dir);

        /** @brief increases the x pos by 0.4 
         *  @param dir - sets the direction of the object
         */
        void speedSlow(int dir);
        
        /** @brief increases the x pos by 0.6 
         *  @param dir - sets the direction of the object
         */
        void speedMedium(int dir);
        
        /** @brief increases the x pos by 0.8 
         *  @param dir - sets the direction of the object
         */
        void speedFast(int dir);
        
        /** @brief increases the x pos by 1.3 (ultra speed)
         *  @param dir - sets the direction of the object
         */
        void speedUltra(int dir);

        /** @brief set the log values
         */
        void initializeLogParameters();
        
        /** @brief set the screen width, height to a value
         */
        void initializeScreenParameters();
};

#endif