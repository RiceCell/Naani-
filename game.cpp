/*
 * game.cpp
 *
 * Implementation for game screen. INSTRUCTIONS RANI WILL ADD A BUTTON FOR THE ACTUAL SEPARATE GAME
 */

#include "game.h"
#include <cstdio>

// Platform-specific headers for key press
#ifdef _WIN32
#include <conio.h> // For _getch()
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

void runGame()
{

    printf("\x1b[2J\x1b[H");
    printf("\x1b[1;36m");
    printf("==========================================================\n");
    printf("     Welcome to Naa Ni, a virtual-verbal memory game!     \n");
    printf("==========================================================\n\n");
    printf("\x1b[0m");
    printf("This is the new function you wanted to call.\n\n");
    printf("Press any key to return to the torus...\n");

// 2. Wait for a single key press (blocking)
#ifdef _WIN32
    printf("\x1b[?25h");
    _getch();
    printf("\x1b[?25l");
#else
    printf("\x1b[?25h");

    struct termios old_settings, new_settings;
    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    char temp;
    read(STDIN_FILENO, &temp, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    printf("\x1b[?25l");
#endif
}