#ifndef TREASURE_HUNT_MSG_H
#define TREASURE_HUNT_MSG_H
#include <sstream>
#include <duels/game_state.h>
#include <vector>
namespace duels {
namespace treasure_hunt {
struct initMsg

{
  int x1; int y1; int t1; int x2; int y2; int t2; int xt; int yt; int Xo[136]; int Yo[136]; int height; int width;
  std::string toYAMLString(std::string p1, std::string p2) const 
  {
    std::stringstream ss;
    ss << "p1: " << p1;
    ss << "\np2: " << p2;
    ss << "\nx1: " << x1;
    ss << "\ny1: " << y1;
    ss << "\nt1: " << t1;
    ss << "\nx2: " << x2;
    ss << "\ny2: " << y2;
    ss << "\nt2: " << t2;
    ss << "\nxt: " << xt;
    ss << "\nyt: " << yt;
    ss << "\nXo: " << "[";
    for(size_t i=0; i < 136; ++i)
      ss << Xo[i] << (i == 135?"]":", ");
    ss << "\nYo: " << "[";
    for(size_t i=0; i < 136; ++i)
      ss << Yo[i] << (i == 135?"]":", ");
    ss << "\nheight: " << height;
    ss << "\nwidth: " << width;
    return ss.str();
  }
};

struct inputMsg
{
  std::string action;
};

struct feedbackMsg
{
  int x; int y; int t; std::vector<int> Xs; std::vector<int> Ys; std::vector<bool> Os; int dist;
  feedbackMsg() {}
  feedbackMsg(int _x, int _y, int _t, std::vector<int> _Xs, std::vector<int> _Ys, std::vector<bool> _Os, int _dist)
    : x(_x), y(_y), t(_t), Xs(_Xs), Ys(_Ys), Os(_Os), dist(_dist) {}
  State state = State::ONGOING;
};

struct displayMsg
{
  int x1; int y1; int t1; int x2; int y2; int t2; int Xs1[1001]; int Ys1[1001]; int Xs2[1001]; int Ys2[1001];
  std::string toYAMLString(int winner) const 
  {
    std::stringstream ss;
    ss << "winner: " << winner;
    ss << "\nx1: " << x1;
    ss << "\ny1: " << y1;
    ss << "\nt1: " << t1;
    ss << "\nx2: " << x2;
    ss << "\ny2: " << y2;
    ss << "\nt2: " << t2;
    ss << "\nXs1: " << "[";
    for(size_t i=0; i < 1001; ++i)
      ss << Xs1[i] << (i == 1000?"]":", ");
    ss << "\nYs1: " << "[";
    for(size_t i=0; i < 1001; ++i)
      ss << Ys1[i] << (i == 1000?"]":", ");
    ss << "\nXs2: " << "[";
    for(size_t i=0; i < 1001; ++i)
      ss << Xs2[i] << (i == 1000?"]":", ");
    ss << "\nYs2: " << "[";
    for(size_t i=0; i < 1001; ++i)
      ss << Ys2[i] << (i == 1000?"]":", ");
    return ss.str();
  }
};

}
}
#endif
