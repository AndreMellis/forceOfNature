#include "Game.h"

int main(int argc, char *args[])
{
    Game forceOfNatureGame;

    forceOfNatureGame.init();
    forceOfNatureGame.run();
    forceOfNatureGame.close();

    return 0;
}
