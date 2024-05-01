#pragma once

#include "EZ-Template/drive/drive.hpp"
#include <type_traits>

extern Drive chassis;

#define BIG_BOT true

#if BIG_BOT
    void big_bot_match_close();
#else
    void red_bot_match_far_6ball();
    void red_bot_match_far_5ball();
    void red_bot_match_old();
    
#endif
// void big_bot_skills();
// void small_bot_skills();
// void red_bot_match_close();
// void small_AWP();
// void turn_example();
// void drive_and_turn();
// void wait_until_change_speed();
// void swing_example();
// void combining_movements();
// void interfered_example();

void default_constants();