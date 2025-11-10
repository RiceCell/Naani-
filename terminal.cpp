/*
 * terminal.cpp
 *
 * Implementation for all cross-platform terminal controls.
 */

#include "terminal.h"
#include <cstdlib> // For atexit
#include <cstdio>  // For printf

// --- Platform-Specific Headers ---
#ifdef _WIN32
// Windows-specific headers
#include <windows.h> // For console functions
#include <conio.h>   // For _kbhit(), _getch()
#else
// POSIX-specific (Linux, macOS) headers
#include <unistd.h>  // For read, STDIN_FILENO
#include <termios.h> // For terminal settings
#include <fcntl.h>   // For fcntl, O_NONBLOCK
#endif

// --- Global variable to store original terminal settings (POSIX only) ---
#ifndef _WIN32
static struct termios g_old_termios;
#endif

/**
 * @brief Restores the terminal to its original (blocking, cursor-visible) mode.
 */
void restoreTerminal()
{
#ifdef _WIN32
    // Show cursor on Windows
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hConsole, &info);
    info.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &info);
#else
    // Restore terminal settings on POSIX
    tcsetattr(STDIN_FILENO, TCSANOW, &g_old_termios);
    printf("\x1b[?25h"); // Show the cursor again
#endif
}

/**
 * @brief Sets up the terminal for non-blocking, non-echoing input.
 */
void setupPlatformTerminal()
{
    atexit(restoreTerminal); // Register restore to be called on exit

#ifdef _WIN32
                             // Hide cursor on Windows
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hConsole, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
#else
                             // Get the current terminal settings (POSIX)
    tcgetattr(STDIN_FILENO, &g_old_termios);
    struct termios new_termios = g_old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    printf("\x1b[?25l"); // Hide the cursor (ANSI escape)
#endif
}

/**
 * @brief Checks for a key press in a non-blocking way.
 * @return The character pressed (e.g., 'q') or 0 if no key was pressed.
 */
char getNonBlockingKey()
{
    char c = 0;
#ifdef _WIN32
    if (_kbhit())
    {
        c = _getch();
    }
#else
    if (read(STDIN_FILENO, &c, 1) > 0)
    {
        // c is set
    }
#endif
    return c;
}