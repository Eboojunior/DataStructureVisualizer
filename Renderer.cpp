#include "Renderer.h"
#include <string>
#include <cmath>

Renderer::Renderer(SDL_Renderer* sdlRenderer, int width, int height) 
    : renderer(sdlRenderer), windowWidth(width), windowHeight(height) {}

void Renderer::drawCircle(int centerX, int centerY, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

void Renderer::drawArrow(int startX, int startY, int endX, int endY) {
    // Draw line
    SDL_RenderLine(renderer, startX, startY, endX, endY);
    
    // Calculate arrow head
    double angle = atan2(endY - startY, endX - startX);
    int arrowLength = 15;
    double arrowAngle = M_PI / 6; // 30 degrees
    
    int arrowX1 = endX - arrowLength * cos(angle - arrowAngle);
    int arrowY1 = endY - arrowLength * sin(angle - arrowAngle);
    int arrowX2 = endX - arrowLength * cos(angle + arrowAngle);
    int arrowY2 = endY - arrowLength * sin(angle + arrowAngle);
    
    SDL_RenderLine(renderer, endX, endY, arrowX1, arrowY1);
    SDL_RenderLine(renderer, endX, endY, arrowX2, arrowY2);
}

void Renderer::renderLinkedList(const LinkedList& list) {
    std::vector<int> values = list.getValues();
    
    if (values.empty()) {
        // Draw "Empty List" message
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Simple text rendering would require SDL_ttf, for now just draw a placeholder
        return;
    }
    
    int nodeRadius = 30;
    int nodeSpacing = 120;
    int startX = 100;
    int startY = windowHeight / 2;
    
    for (size_t i = 0; i < values.size(); i++) {
        int currentX = startX + i * nodeSpacing;
        int currentY = startY;
        
        // Draw node circle (outline)
        SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);
        for (int r = nodeRadius - 3; r <= nodeRadius; r++) {
            drawCircle(currentX, currentY, r);
        }
        
        // Draw node value (simplified number rendering)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        int value = values[i];
        
        // Simple digit rendering using rectangles
        int digitWidth = 8;
        int digitHeight = 12;
        int digitX = currentX - (std::to_string(value).length() * digitWidth) / 2;
        int digitY = currentY - digitHeight / 2;
        
        // Draw digits as simple rectangles (very basic)
        std::string valueStr = std::to_string(value);
        for (size_t d = 0; d < valueStr.length(); d++) {
            SDL_FRect rect = {
                static_cast<float>(digitX + d * digitWidth),
                static_cast<float>(digitY),
                static_cast<float>(digitWidth - 2),
                static_cast<float>(digitHeight)
            };
            SDL_RenderFillRect(renderer, &rect);
        }
        
        // Draw arrow to next node
        if (i < values.size() - 1) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
            int arrowStartX = currentX + nodeRadius;
            int arrowEndX = startX + (i + 1) * nodeSpacing - nodeRadius;
            drawArrow(arrowStartX, currentY, arrowEndX, currentY);
        }
    }
}

void Renderer::renderInstructions() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // Draw simple instruction rectangles (placeholder for text)
    std::vector<std::string> instructions = {
        "SPACE: Add Node",
        "D: Delete Last Node", 
        "C: Clear All",
        "ESC: Exit"
    };
    
    int y = 50;
    for (const auto& instruction : instructions) {
        SDL_FRect rect = {50, static_cast<float>(y), 200, 20};
        SDL_RenderRect(renderer, &rect);
        y += 30;
    }
}
