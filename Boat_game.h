#ifndef BOAT_GAME_H
#define BOAT_GAME_H
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

bool Is_free(int x,int y, int X[NB_OBS], int Y[NB_OBS]);
bool Is_In(int x, int y, vector<int> X, vector<int> Y);

struct MsgSonar
{
    vector<int> xs;
    vector<int> ys;
    vector<bool> obstacle;
};


class Boat{
public:
    int x;
    int y;
    int t;
    bool treasure_found=false;
    bool hit_obstacle=false;
    MsgSonar Sonar_coordinates;
    Boat(){};
    Boat(int width, int height, int Xo[NB_OBS], int Yo[NB_OBS], int seed){
        srand (time(NULL) + seed);
        t=rand()%4;
        x=rand()%width;
        y=rand()%height;
        while (!Is_free(x, y, Xo, Yo)){
            x=rand()%width;
            y=rand()%height;
        }
        Sonar_coordinates.xs.push_back(-5);
        Sonar_coordinates.ys.push_back(-5);
        Sonar_coordinates.obstacle.push_back(false);
    };

    void Update_game(inputMsg input, int Xo[NB_OBS], int Yo[NB_OBS], int xt, int yt);
    void Move(int Xo[NB_OBS], int Yo[NB_OBS]);
    void Turn_l();
    void Turn_r();
    void Get_Sonar(int Xo[NB_OBS], int Yo[NB_OBS]);
    bool On_treasure(int xt, int yt);

};

class Grid
{
public:
    int height, width;
    int x_treasure, y_treasure;
    int Xo[NB_OBS];
    int Yo[NB_OBS];
    Boat b1;
    Boat b2;


    Grid(){
        srand (time(NULL));
        height=20;
        width=30;

        x_treasure=rand()%width;
        y_treasure=rand()%height;

        Create_Obstacles();

        while (!Is_free(x_treasure, y_treasure, Xo, Yo))
        {
            x_treasure=rand()%width;
            y_treasure=rand()%height;
        }

        b1=Boat(width, height, Xo, Yo, 0);
        b2=Boat(width, height, Xo, Yo, 1);
    };
    void Create_Obstacles();
    feedbackMsg Create_feedback(Boat b);
};



#endif
