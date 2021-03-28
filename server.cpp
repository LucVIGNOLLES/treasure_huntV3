#define LOCAL_GAME  // to test the game AI with a dumb player AI

#include <duels/treasure_hunt/msg.h>
#ifdef LOCAL_GAME
#include <duels/local.h>
#else
#include <duels/server.h>
#endif
#include "Boat_game.h"
#include"AI.h"

using duels::Player;
using namespace duels::treasure_hunt;
#ifdef LOCAL_GAME
using GameIO = duels::LocalGame<initMsg, inputMsg, feedbackMsg, displayMsg, 500, 500>;
#else
using GameIO = duels::Server<initMsg, inputMsg, feedbackMsg, displayMsg, 500, 500>;
#endif


int main(int argc, char** argv)
{
  feedbackMsg feedback1, feedback2;
  initMsg init;
  inputMsg input1, input2;
  displayMsg display;
  GameIO game_io;
  // simulation time
  const double dt(game_io.samplingTime());

  // build initial game state

  Grid G = Grid();
  level1_IA thiery;
  level1_IA roger;


  // build init message for display
  init.x1=G.b1.x;
  init.y1=G.b1.y;
  init.t1=G.b1.t;
  init.x2=G.b2.x;
  init.y2=G.b2.y;
  init.t2=G.b2.t;
  init.xt=G.x_treasure;
  init.yt=G.y_treasure;
  init.height=G.height;
  init.width=G.width;
  for (int i=0;i<NB_OBS;i++){
      init.Xo[i]=G.Xo[i];
      init.Yo[i]=G.Yo[i];
  }




#ifdef LOCAL_GAME
  game_io.initDisplay(init, "treasure_hunt");  // add false at the end if you run the display in another terminal
  game_io.setLevel(1);
#else
  game_io.initDisplay(argc, argv, init);
  const bool two_players = game_io.hasTwoPlayers();
#endif


  while(true)
  {
    // check if any regular winner
    if(G.b1.treasure_found||G.b2.treasure_found||G.b1.hit_obstacle||G.b2.hit_obstacle)
    {
      if(G.b1.treasure_found||G.b2.hit_obstacle)
      game_io.registerVictory(Player::One, feedback1, feedback2);
      else
      game_io.registerVictory(Player::Two, feedback1, feedback2);
      break;
    }


    // build display information
    display.x1=G.b1.x;
    display.y1=G.b1.y;
    display.t1=G.b1.t;
    display.x2=G.b2.x;
    display.y2=G.b2.y;
    display.t2=G.b2.t;
    for (int i=0;i<1001;i++){
        if (i<G.b1.Sonar_coordinates.xs.size()){
            display.Xs1[i]=G.b1.Sonar_coordinates.xs[i];
            display.Ys1[i]=G.b1.Sonar_coordinates.ys[i];
        }
        else{
            display.Xs1[i]=-5;
            display.Ys1[i]=-5;
        }
        if (i<G.b2.Sonar_coordinates.xs.size()){
            display.Xs2[i]=G.b2.Sonar_coordinates.xs[i];
            display.Ys2[i]=G.b2.Sonar_coordinates.ys[i];
        }
        else {
            display.Xs2[i]=-5;
            display.Ys2[i]=-5;
        }
    };


    game_io.sendDisplay(display);
    
    // build player 1 feedback
    feedback1=G.Create_feedback(G.b1);

    // build player 2 feedback
    feedback2=G.Create_feedback(G.b2);



#ifndef LOCAL_GAME
    if(two_players)
    {
      if(!game_io.sync(feedback1, input1, feedback2, input2))
        break;
    }
    else
    {
      // sync with player 1, exits if needed
      if(!game_io.sync(feedback1, input1))
        break;


#else
      // write dumb player AI from feedback1 to input1
//    srand (time(NULL)+G.b2.t+G.b2.x+50);
//          int r=rand()%4;
//          r = 1;
//          if (r==0){
//              input1.action="sonar";
//          }
//          if (r==1){
//              input1.action="turn_l";
//          }
//          if (r==2){
//              input1.action="move";
//          }
//          if (r==3){
//              input1.action="turn_r";
//          }
    input1.action = thiery.send_input(feedback1);


#endif

      // artificial opponent: put your AI here      
//          srand (time(NULL)+G.b1.t+G.b1.x);
//               r=rand()%4;
//               if (r==0){
//                   input2.action="sonar";
//               }
//               if (r==1){
//                   input2.action="turn_l";
//               }
//               if (r==2){
//                   input2.action="move";
//               }
//               if (r==3){
//                   input2.action="turn_r";
//               }
        input2.action = roger.send_input(feedback2);

               

#ifndef LOCAL_GAME
    }
#endif

    // update game state from input1 and input2
    G.b1.Update_game(input1, G.Xo, G.Yo, G.x_treasure, G.y_treasure);
    G.b2.Update_game(input2, G.Xo, G.Yo, G.x_treasure, G.y_treasure);
    
    
  }

  // final results
  game_io.sendResult(display, feedback1, feedback2);

  return 0;
}
