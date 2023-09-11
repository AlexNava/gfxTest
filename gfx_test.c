#include "gfx.h" // all drawing functions are here
// screen coordinates are as follows:
//
// (0,0) -------> positive x
//   |
//   |
//   |
//   V
//
// positive y

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 200;

const int BOX_WIDTH = 10;
const int BOX_HEIGHT = 10;

int main(int argc, char **argv)
{
    init(SCREEN_WIDTH, SCREEN_HEIGHT); // This needs to be called only once to create a window to draw to

    int x = 0;
    int y = 0;

    while (1)
    {
        clearScreen(BLACK); // Clears the screen with the specified color
        drawBox(x, y, BOX_WIDTH, BOX_HEIGHT, ORANGE); // Draws a rectangle with top left corner in (x, y)
        present(); // Makes the image appear on the screen
    }

    return 0;
}
