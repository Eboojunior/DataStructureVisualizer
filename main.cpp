#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include "LinkedList.h"
#include "Renderer.h"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Data Structure Visualizer",
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );
    
    if (!window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create renderer
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, nullptr);
    if (!sdlRenderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Create our custom renderer and linked list
    auto renderer = std::make_unique<Renderer>(sdlRenderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    auto linkedList = std::make_unique<LinkedList>();

    // Add some initial data
    linkedList->insert(10);
    linkedList->insert(20);
    linkedList->insert(30);
    linkedList->insert(40);

    bool running = true;
    SDL_Event e;
    int nodeToAdd = 50;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if (e.type == SDL_EVENT_KEY_DOWN) {
                switch (e.key.key) {
                    case SDLK_SPACE:
                        linkedList->insert(nodeToAdd);
                        nodeToAdd += 10;
                        break;
                    case SDLK_D:
                        if (!linkedList->isEmpty()) {
                            linkedList->remove();
                        }
                        break;
                    case SDLK_C:
                        linkedList->clear();
                        nodeToAdd = 10;
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(sdlRenderer, 30, 30, 50, 255);
        SDL_RenderClear(sdlRenderer);

        // Render the linked list
        renderer->renderLinkedList(*linkedList);
        
        // Render instructions
        renderer->renderInstructions();

        // Present the rendered frame
        SDL_RenderPresent(sdlRenderer);
        
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
