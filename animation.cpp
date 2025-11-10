/*
 * animation.cpp
 *
 * This is the "implementation" file. It only contains code related to the torus animation. It has no main() and no while loop!
 */

#include "animation.h"
#include <cstdio>
#include <cmath>
#include <cstring>

static float A = 0;
static float B = 0;
static float z[1760];
static char b[1760];

void updateAnimation()
{
    A += 0.04;
    B += 0.02;
}

void renderAnimation()
{
    // --- 1. Calculate the frame ---
    memset(b, 32, 1760);
    memset(z, 0, 7040);
    for (float j = 0; j < 6.28; j += 0.07)
    {
        for (float i = 0; i < 6.28; i += 0.02)
        {
            float c = sin(i);
            float d = cos(j);
            float e = sin(A);
            float f = sin(j);
            float g = cos(A);
            float h = d + 4;
            float D = 1 / (c * h * e + f * g + 5);
            float l = cos(i);
            float m = cos(B);
            float n = sin(B);
            float t = c * h * g - f * e;
            int x = 40 + 30 * D * (l * h * m - t * n);
            int y = 12 + 15 * D * (l * h * n + t * m);
            int o = x + 80 * y;
            int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
            if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
            {
                z[o] = D;
                b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
            }
        }
    }

    // --- 2. Print the frame to screen ---
    printf("\x1b[H");
    printf("\x1b[38;5;8m"); // Set color

    for (int k = 0; k < 1760; k++)
    {
        if (k % 80 == 0)
            putchar('\n');
        if (k == 40 + 80 * 12)
        {
            printf("\x1b[1;33mNAA NI?\x1b[38;5;8m");
            k += 5;
        }
        else
        {
            putchar(b[k]);
        }
    }

    printf("\x1b[0m");

    // --- 3. Print the instructions (as you requested) ---
    printf("\x1b[23;1H");
    printf("Press Q to play\x1b[K\n");
    printf("Press X to exit.\x1b[K");
}