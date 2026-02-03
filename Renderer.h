#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "LinkedList.h"

class Renderer {
private:
    SDL_Renderer* renderer;
    int windowWidth;
    int windowHeight;
    
    void drawCircle(int centerX, int centerY, int radius);
    void drawArrow(int startX, int startY, int endX, int endY);
    void drawText(const char* text, int x, int y);

public:
    Renderer(SDL_Renderer* sdlRenderer, int width, int height);
    ~Renderer() = default;
    
    void renderLinkedList(const LinkedList& list);
    void renderInstructions();
};

#endif
