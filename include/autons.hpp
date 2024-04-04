#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

#define BIG_BOT true

#if BIG_BOT
    void big_bot_skills();
    void big_bot_match_auton();
#else
    void small_bot_skills();
    void small_bot_match_auton();
#endif
// void small_AWP();
// void turn_example();
// void drive_and_turn();
// void wait_until_change_speed();
// void swing_example();
// void combining_movements();
// void interfered_example();

void default_constants();