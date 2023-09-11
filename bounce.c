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
    init(SCREEN_WIDTH, SCREEN_HEIGHT);

    int x = 0;
    int y = 0;

    while (1)
    {
        clearScreen();
        drawBox(x, y, BOX_WIDTH, BOX_HEIGHT);
        present();
    }

    return 0;
}
