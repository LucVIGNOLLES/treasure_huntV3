#include <iostream>
#include "Boat_game.h"
#include <vector>
#include <math.h>

using namespace std;


bool Is_free(int x, int y, int X[NB_OBS], int Y[NB_OBS]){
    int i;
    bool res=true;
    if (x>=29||y>=19||x<=0||y<=0){res=false;}
    else {
        for (i=0;i<NB_OBS;i++){
            if ((X[i]==x)&&(Y[i]==y)){
                res=false;
            }
        }
    }
    return res;
};


bool Is_In(int x, int y, vector<int> X, vector<int> Y){
    bool res=false;
    for (int i=0; i<X.size(); i++){
        if ((x==X[i])&&(y==Y[i])){
                res=true;
        }
    }
    return res;
}



void Boat::Move(int Xo[NB_OBS], int Yo[NB_OBS]){
    int t=Boat::t;

    if ((t==0) /*&& Is_free(Boat::x+1, Boat::y, Xo, Yo)*/){
        Boat::x++;
    }
    if ((t==1) /*&& Is_free(Boat::x, Boat::y+1, Xo, Yo)*/){
        Boat::y--;
    }
    if ((t==2) /*&& Is_free(Boat::x-1, Boat::y, Xo, Yo)*/){
        Boat::x--;
    }
    if ((t==3) /*&& Is_free(Boat::x, Boat::y-1, Xo, Yo)*/){
        Boat::y++;
    }
};


void Boat::Turn_l(){
    if (Boat::t==3){Boat::t=0;}
    else {Boat::t=Boat::t+1;}
};

void Boat::Turn_r(){
    if (Boat::t==0){Boat::t=3;}
    else {Boat::t=Boat::t-1;}
};

void Boat::Get_Sonar(int Xo[NB_OBS], int Yo[NB_OBS]){
    Boat::Sonar_coordinates.xs.clear();
    Boat::Sonar_coordinates.ys.clear();
    Boat::Sonar_coordinates.obstacle.clear();
    float lower= -Boat::t*(3.14/2) - (3.14/3);
    float upper= -Boat::t*(3.14/2) + (3.14/3);
    float alpha=lower;
    for (int i = 0; i<100; i++){
        alpha=lower+i*(upper-lower)/100;
        float inc_a=cos(alpha);
        float inc_b=sin(alpha);

        float a = Boat::x + 0.5;
        float b = Boat::y + 0.5;
        while (Is_free(int(floor(a)), int(floor(b)), Xo, Yo)){
            if (!Is_In(int(a), int(b), Boat::Sonar_coordinates.xs, Boat::Sonar_coordinates.ys)){
                Boat::Sonar_coordinates.xs.push_back(int(floor(a)));
                Boat::Sonar_coordinates.ys.push_back(int(floor(b)));
                Boat::Sonar_coordinates.obstacle.push_back(false);

            }
            a = a+inc_a;
            b = b+inc_b;

        }
        if (!Is_In(int(a), int(b), Boat::Sonar_coordinates.xs, Boat::Sonar_coordinates.ys)){
            Boat::Sonar_coordinates.xs.push_back(int(a));
            Boat::Sonar_coordinates.ys.push_back(int(b));
            Boat::Sonar_coordinates.obstacle.push_back(true);
        }
    }
};




void Boat::Update_game(inputMsg input, int Xo[NB_OBS], int Yo[NB_OBS], int xt, int yt){
    string A=input.action;
    if (A=="move"){
        Boat::Move(Xo, Yo);
        if (Boat::On_treasure(xt, yt)){Boat::treasure_found=true;}
        if (!Is_free(Boat::x,Boat::y,Xo,Yo)){Boat::hit_obstacle=true;}
        Boat::Sonar_coordinates.xs.clear();
        Boat::Sonar_coordinates.ys.clear();
        Boat::Sonar_coordinates.obstacle.clear();
    }
    if (A=="turn_l"){
        Boat::Turn_l();
        Boat::Sonar_coordinates.xs.clear();
        Boat::Sonar_coordinates.ys.clear();
        Boat::Sonar_coordinates.obstacle.clear();
    }
    if (A=="turn_r"){
        Boat::Turn_r();
        Boat::Sonar_coordinates.xs.clear();
        Boat::Sonar_coordinates.ys.clear();
        Boat::Sonar_coordinates.obstacle.clear();
    }
    if (A=="sonar"){
        Boat::Get_Sonar(Xo, Yo);
    }
};

bool Boat::On_treasure(int xt, int yt){
    return ((Boat::x==xt)&&(Boat::y==yt));
}

void Grid::Create_Obstacles(){
    srand (time(NULL));
    int NB_RAND = NB_OBS-96;
    int t;
    for (int i=0; i<NB_RAND/2; i++){
        Xo[i]=x_treasure;
        Yo[i]=y_treasure;
        while ((Xo[i]==x_treasure)&&(Yo[i]==y_treasure)){
            Xo[i]=rand()%(width-1);
            Yo[i]=rand()%height;
            t = rand()%2;
            if (t==0){
                Xo[NB_RAND-1-i]=Xo[i]+1;
                Yo[NB_RAND-1-i]=Yo[i];
            }
            else{
                Xo[NB_RAND-1-i]=Xo[i];
                Yo[NB_RAND-1-i]=Yo[i]+1;
            }
        }
        if (i>0){
            for (int j=0;j<i;j++){
                while ((Xo[i]==Xo[j])&&(Yo[i]==Yo[j])){
                    Xo[i]=rand()%(width-1);
                    Yo[i]=rand()%height;
                    if (t==0){
                        Xo[NB_RAND-1-i]=Xo[i]+1;
                        Yo[NB_RAND-1-i]=Yo[i];
                    }
                    else{
                        Xo[NB_RAND-1-i]=Xo[i];
                        Yo[NB_RAND-1-i]=Yo[i]+1;
                    }
                }
            }
        }
    }
    int j =0;
    for (int i=NB_RAND; i<NB_RAND+30; i++)
    {
        Xo[i] = j;
        Yo[i] = 0;
        j++;
    }
    j = 0;
    for (int i=NB_RAND+30; i<NB_RAND+60; i++)
    {
        Xo[i] = j;
        Yo[i] = 19;
        j++;
    }
    j = 1;
    for (int i=NB_RAND+60; i<NB_RAND+78; i++)
    {
        Xo[i] = 0;
        Yo[i] = j;
        j++;
    }
    j = 1;
    for (int i=NB_RAND+78; i<NB_RAND+96; i++)
    {
        Xo[i] = 29;
        Yo[i] = j;
        j++;
    }
    cout<<"Obstacles created"<<endl;
};


feedbackMsg Grid::Create_feedback(Boat b){
    feedbackMsg fb;
    fb.x=b.x;
    fb.y=b.y;
    fb.t=b.t;
    fb.Xs=b.Sonar_coordinates.xs;
    fb.Ys=b.Sonar_coordinates.ys;
    fb.Os=b.Sonar_coordinates.obstacle;
    fb.dist=abs(Grid::x_treasure-b.x)+abs(Grid::y_treasure-b.y);
    return fb;
};
