#include "terminal.h"
#include "animation.h"
#include "game.h"

#include <thread>
#include <chrono>
#include <cstdio>

int main()
{
    setupPlatformTerminal();
    printf("\x1b[2J");

    bool isRunning = true;
    bool showTorus = true;

    while (isRunning)
    {
        char c = getNonBlockingKey();
        if (c != 0)
        {
            if (c == 'x' || c == 'X')
            {
                isRunning = false;
            }
            else if (c == 'q' || c == 'Q')
            {
                showTorus = !showTorus;
                printf("\x1b[2J");
            }
        }

        if (showTorus)
        {
            updateAnimation();
            renderAnimation();
        }
        else
        {
            runGame();
            showTorus = true;
            printf("\x1b[2J");
        }

        fflush(stdout);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    printf("\x1b[2J\x1b[H");
    printf("Exiting... Thanks for playing!\n");

    return 0;
}