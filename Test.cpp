#include "Test.h"

/** TEST FROG CLASS */

/** Function that checks whether Frog has respawned in the right
 *  position
 */
bool test_frog_reset(float expect_value_x, float expec_value_y)
{
    Frog test_frog((84/2)-6/2, 48-4, 6); // test a frog object
    //printf("Frog reset x pos: %d,%d", x, y);
    if(test_frog.x == expect_value_x && test_frog.y == expec_value_y){
        //printf("FROG TEST PASSED");
        return true;
    } else {
        //printf("FROG TEST FAILED, %d", test_frog.x);
        return false;
    }
}

void run_frog_test()
{
    test_frog_reset((84/2)-6/2, 48-4);
    test_frog_reset((64/2)-6/2, 24-4);
    test_frog_reset((32/2)-6/2, 12-4);
}

/** TEST OBJECT CLASS */

/** Returns true if the input row will give the correct y pos */
bool test_row_func(int row, int object_y_coord)
{
    Object test_object;
    printf("Object row test: %d", row);
    if(test_object.object.y == object_y_coord){
      //  printf("OBJECT TEST PASSED");
        return true;
    } else {
       // printf("OBJECT TEST FAILED, %d", row);
        return false;
    }
}

/** function tests that the object class creates the rectangle correcly */
bool test_rec_paramaters(int x, int y, char c)
{
    Object test_object;
    if(test_object.rectangle.right_side == (x + test_object.width) &&
    test_object.rectangle.bottom == y + test_object.height
    && test_object.rectangle.up == test_object.object.y){
        //printf("OBJECT TEST PASSED");
        return true;
    } else {
        //printf("OBJECT TEST FAILED, %d, %d, object type: ", x, y, c);
        return false;
    }
}

bool test_speed_funcs(int dir)
{
    Object test_object;
    if(test_object.object.dir == dir){
        //printf("OBJECT TEST PASSED");
        return true;
    } else {
        //printf("OBJECT TEST FAILED, %d", dir);
        return false;
    }
}

void run_rect_params()
{
    test_rec_paramaters(5, 48-4*5, 'S');
    test_rec_paramaters(6, 48-4*6, 'B');
    test_rec_paramaters(7, 48-4*7, 'T');
}

void run_row_func()
{
    test_row_func(6, 48-4*6); 
    test_row_func(7, 48-4*7); 
    test_row_func(8, 48-4*8); 
    test_row_func(9, 48-4*9); 
}
