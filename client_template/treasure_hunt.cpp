#include <duels/treasure_hunt/game.h>

using namespace duels::treasure_hunt;

int main(int argc, char** argv)
{
  Game game(argc, argv, "your name here");

  inputMsg input;
  feedbackMsg feedback;
  const auto timeout = game.timeout;

  while(game.get(feedback))
  {
    // write input in less than timeout



    game.send(input);
  }
}
