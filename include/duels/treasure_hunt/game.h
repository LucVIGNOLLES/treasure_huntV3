#ifndef TREASURE_HUNT_GAME_H
#define TREASURE_HUNT_GAME_H
#include <duels/client.h>
#include <duels/treasure_hunt/msg.h>
#include <sstream>
namespace duels {
namespace treasure_hunt {
class Game: public duels::Client<inputMsg, feedbackMsg>
{
public:
  Game(int argc, char** argv, std::string name, int difficulty = 1)
    : Game(argc, argv, name, difficulty, "local_game") {}
  Game(int argc, char** argv, std::string name, std::string ip, int difficulty = 1)
      : Game(argc, argv, name, difficulty, ip) {}
private:
  Game(int argc, char** argv, std::string name, int difficulty, std::string ip)
      : duels::Client<inputMsg, feedbackMsg>(
      argc, argv, 500, name, difficulty, ip, "treasure_hunt") {}
};
}
}
#endif