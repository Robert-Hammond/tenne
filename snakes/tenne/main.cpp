#include <battlesnake/server/server.h>

#include <iostream>

#include "snake_random.h"

int main()
{
    SnakeRandom snake;
    battlesnake::server::BattlesnakeServer server(&snake, 80);

    server.Run([](unsigned short port)
               { std::cout << "Hirejou Tenne is running on port " << port << std::endl; });

    return 0;
}
