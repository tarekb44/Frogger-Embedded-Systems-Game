#ifndef TEST_H
#define TEST_H

#include "Frog.h"
#include "Frogger.h"
#include "Object.h"

/** 
 * This testing schedule is based on the Testing example from
 * LAB 106 
 */

/** TEST FROG CLASS */
bool test_frog_reset(float expect_value_x, float expec_value_y);
void run_frog_test();

/** TEST OBJECT CLASS */
bool test_row_func(int row);
bool test_rec_paramaters(int x, int y, char c);
bool test_speed_funcs(int dir);
bool test_update(int x, int y);

/** TEST FROGGER FUNCTIONS */
bool test_out_of_bounds(Object *vehicle);
bool test_frog_actions();
bool test_collision();
bool test_progression();

/** CALLER FUNCTIONS */
void run_rect_params();
void run_speed();
void run_update();
void run_row_func();
void run_progression();
void run_collision_detection();

#endif