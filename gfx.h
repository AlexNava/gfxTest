#ifndef GFX_H
#define GFX_H

#include <SDL2/SDL.h>

SDL_Window *win;
SDL_Renderer *sdlRenderer;
SDL_Texture *sdlTexture;
SDL_Surface *rgbSurface;
SDL_Surface *vgaSurface;
char *vgaScreen;
SDL_Color sdlPalette[256];
int screenWidth;
int screenHeight;
int screenInitialized = 0;

typedef enum colors
{
    BLACK,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA,
    WHITE
};

void setPal(uint8_t col, uint8_t r, uint8_t g, uint8_t b) {
    // sets rgb amount for a given palette entry

    sdlPalette[col].r = r;
    sdlPalette[col].g = g;
    sdlPalette[col].b = b;

    if (vgaSurface && vgaSurface->format->palette)
        SDL_SetPaletteColors(vgaSurface->format->palette, &sdlPalette[col], col, 1);

}

void init(int w, int h)
{
    if (!screenInitialized)
    {
        screenWidth = w;
        screenHeight = h;

        const int WINDOW_SCALE = 3;
        win = SDL_CreateWindow("hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               w * WINDOW_SCALE, h * WINDOW_SCALE, 0);
        sdlRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

        SDL_RenderSetLogicalSize(sdlRenderer, w, h);

        sdlTexture = SDL_CreateTexture(
            sdlRenderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            w, h);

        rgbSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        vgaSurface = SDL_CreateRGBSurface(0, w, h, 8, 0, 0, 0, 0);

        vgaScreen = (char*)(vgaSurface->pixels);

        setPal(BLACK, 0, 0, 0);
        setPal(RED, 255, 0, 0);
        setPal(ORANGE, 255, 127, 0);
        setPal(YELLOW, 255, 255, 0);
        setPal(GREEN, 0, 255, 0);
        setPal(CYAN, 0, 192, 255);
        setPal(BLUE, 0, 64, 255);
        setPal(MAGENTA, 255, 0, 128);
        setPal(WHITE, 255, 255, 255);
    }
    screenInitialized = 1;
}

void clearScreen(uint8_t color)
{
    SDL_LockSurface(vgaSurface);
    memset (vgaScreen, color, screenWidth * screenHeight);
    SDL_UnlockSurface(vgaSurface);
}

void drawBox(int x, int y, int w, int h, uint8_t color)
{
    SDL_LockSurface(vgaSurface);
    for (int px = 0; px < w; ++px)
        for (int py = 0; py < h; ++py)
        {
            if (((x + px) >= 0 && (x + px) < screenWidth)
                && ((y + py) >= 0 && (y + py) < screenHeight))
            vgaScreen[screenWidth * (y+py) + x + px] = color;
        }
    SDL_UnlockSurface(vgaSurface);
}

void present()
{
    void *texturePixels;
    int texturePitch;

    if (!vgaSurface)
        return;

    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        if (evt.type == SDL_QUIT)
        {
            exit(0);
        }
    }

    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);

    SDL_ClearError();
    SDL_BlitSurface(vgaSurface, NULL, rgbSurface, NULL); // with format conversion

    SDL_LockTexture(sdlTexture, NULL, &texturePixels, &texturePitch);
        SDL_ConvertPixels(rgbSurface->w, rgbSurface->h,
        rgbSurface->format->format,
        rgbSurface->pixels, rgbSurface->pitch,
        SDL_PIXELFORMAT_ARGB8888,
        texturePixels, texturePitch);
    SDL_UnlockTexture(sdlTexture);

    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
    SDL_RenderPresent(sdlRenderer);
}

#endif
