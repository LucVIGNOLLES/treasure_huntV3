#ifndef AI_H
#define AI_H
#include <iostream>
#include <string>
#include <vector>
#include <duels/treasure_hunt/msg.h>
#include <duels/local.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
using duels::Player;
using namespace duels::treasure_hunt;

class level1_IA{
public:
    std::string send_input(feedbackMsg fb);
private:

    int map[30][20];
    int d_mem = 100;
    int d_obs;
    int state;

    void update_map_from_sonar(feedbackMsg fb);
    void get_closest_obs(feedbackMsg fb);
};


#endif
