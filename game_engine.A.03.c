#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

// Define screen dimensions for both windows
#define GUI_WINDOW_WIDTH  300
#define GUI_WINDOW_HEIGHT 200
#define RENDER_WINDOW_WIDTH  800
#define RENDER_WINDOW_HEIGHT 600

// Function to initialize SDL and SDL_ttf
bool init(SDL_Window **window1, SDL_Renderer **renderer1, SDL_Window **window2, SDL_Renderer **renderer2) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        return false;
    }

    // Create two windows
    *window1 = SDL_CreateWindow("GUI Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GUI_WINDOW_WIDTH, GUI_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window1) {
        printf("Window 1 could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    *window2 = SDL_CreateWindow("Render Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RENDER_WINDOW_WIDTH, RENDER_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window2) {
        printf("Window 2 could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderers for both windows
    *renderer1 = SDL_CreateRenderer(*window1, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer1) {
        printf("Renderer for Window 1 could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    *renderer2 = SDL_CreateRenderer(*window2, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer2) {
        printf("Renderer for Window 2 could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// Function to close SDL resources
void close(SDL_Window *window1, SDL_Renderer *renderer1, SDL_Window *window2, SDL_Renderer *renderer2, TTF_Font *font) {
    // Destroy the font
    if (font) {
        TTF_CloseFont(font);
    }

    // Destroy renderers and windows
    SDL_DestroyRenderer(renderer1);
    SDL_DestroyRenderer(renderer2);
    SDL_DestroyWindow(window1);
    SDL_DestroyWindow(window2);

    // Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

// Function to render the FPS in the GUI window
void renderFPS(SDL_Renderer *renderer, TTF_Font *font, int fps) {
    // Set text color
    SDL_Color textColor = {255, 255, 255, 255};  // White text

    // Create text texture
    char fpsText[20];
    snprintf(fpsText, sizeof(fpsText), "FPS: %d", fps);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, fpsText, textColor);
    if (!textSurface) {
        printf("Unable to render text surface! TTF_Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Render the text
    SDL_RenderCopy(renderer, textTexture, NULL, NULL);
    SDL_DestroyTexture(textTexture);
}

int main() {
    SDL_Window *window1 = NULL, *window2 = NULL;
    SDL_Renderer *renderer1 = NULL, *renderer2 = NULL;
    TTF_Font *font = NULL;

    // Initialize SDL and create windows
    if (!init(&window1, &renderer1, &window2, &renderer2)) {
        printf("Failed to initialize SDL or create windows!\n");
        return -1;
    }

    // Load font for FPS counter (use any ttf font on your system)
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24);
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        close(window1, renderer1, window2, renderer2, font);
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    int frameCount = 0;
    Uint32 startTicks = SDL_GetTicks();
    float deltaTime = 0.0f;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Calculate FPS
        frameCount++;
        Uint32 currentTicks = SDL_GetTicks();
        deltaTime = (currentTicks - startTicks) / 1000.0f;

        if (deltaTime >= 1.0f) {
            int fps = frameCount / deltaTime;
            frameCount = 0;
            startTicks = currentTicks;

            // Clear and render FPS to GUI window
            SDL_SetRenderDrawColor(renderer1, 0, 0, 0, 255);  // Black background
            SDL_RenderClear(renderer1);
            renderFPS(renderer1, font, fps);
            SDL_RenderPresent(renderer1);
        }

        // Clear and render to the render window (currently blank)
        SDL_SetRenderDrawColor(renderer2, 0, 0, 255, 255);  // Blue background
        SDL_RenderClear(renderer2);
        SDL_RenderPresent(renderer2);
    }

    close(window1, renderer1, window2, renderer2, font);
    return 0;
}
