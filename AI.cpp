#include <iostream>
#include <string>
#include <vector>
#include <duels/treasure_hunt/msg.h>
#include <duels/local.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include"AI.h"

using namespace std;
using duels::Player;
using namespace duels::treasure_hunt;

void level1_IA::update_map_from_sonar(feedbackMsg fb)
{
    vector<int> xs = fb.Xs;
    vector<int> ys = fb.Ys;
    vector<bool> is_obs = fb.Os;

    for (int i = 0; i<xs.size(); i++)
    {
        if (is_obs[i])
        {
            map[xs[i]][ys[i]] = 2;
        }
        else
        {
            map[xs[i]][ys[i]] = 1;
        }
    }
}


void level1_IA::get_closest_obs(feedbackMsg fb)
{
    int i = 0;
    switch (fb.t)
    {
    case 0:
        while (map[fb.x+i][fb.y]==1)
        {
            i++;
        }
        d_obs = i;
        break;

    case 1:
        while (map[fb.x][fb.y-i]==1)
        {
            i++;
        }
        d_obs = i;
        break;

    case 2:
        while (map[fb.x-i][fb.y]==1)
        {
            i++;
        }
        d_obs = i;
        break;

    case 3:
        while (map[fb.x][fb.y+i]==1)
        {
            i++;
        }
        d_obs = i;
        break;
    }
}


std::string level1_IA::send_input(feedbackMsg fb)
{
    std::string input;

    switch (state) {

    case 0:
        input = "sonar";
        state = 1;
        d_mem = 100;
        break;

    case 1:
        update_map_from_sonar(fb);
        get_closest_obs(fb);

        if (fb.dist-d_mem<0 && d_obs>=2)
        {
            input = "move";
            state = 1;
            d_mem = fb.dist;
        }
        else
        {
            if (d_obs<2)
            {
                input = "turn_l";
                state = 0;
            }
            else
                input = "turn_l";
                state = 2;
        }
        break;

    case 2:
        input = "turn_l";
        state = 3;
        break;

    case 3:
        input = "move";
        state = 4;
    break;

    case 4:
        input = "turn_l";
        state = 0;
        break;


    }
    cout<<d_mem<<" ; "<<fb.dist<<endl;
    //d_mem = fb.dist;
    return input;


}
