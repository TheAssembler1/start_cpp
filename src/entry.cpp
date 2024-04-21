#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "gui/gui.h"

int main() {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "sdl2 failed to init" << std::endl;
  } else {
    std::cout << "sdl2 successfully initialized" << std::endl;
  }

  if(TTF_Init() < 0) {
    std::cout << "sdl_ttf failed to init" << std::endl;
  } else {
    std::cout << "sdl2_ttf successfully initialized" << std::endl;
  }

  SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  GUI::Widgeter widgeter(renderer, GUI::Position{0, 0}, 2, 12);

  for(;;) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        goto exit;
      } 
      
    }

    GUI::Position mouse_position;

    #define MOUSE_BUTTON_LEFT 1
    unsigned int button_mask;
    if(SDL_GetMouseState(&mouse_position.x, &mouse_position.y) & SDL_BUTTON(MOUSE_BUTTON_LEFT)) {
      std::cout << "mouse clicked" << std::endl;
    }
    
    SDL_Color bg_color{0, 0, 0, 255};
    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);
  
    widgeter.startWidgeter();
    
    widgeter.textBox(true, "pacman emulator");

    if(widgeter.button(mouse_position, "test button")) {
      std::cout << "button pressed" << std::endl;
    }

    for(int i = 0; i < 5; i++) {
      widgeter.box(GUI::Dimension{10, 10});
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(500);
  }

exit:
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_Quit();
  return 0;
}
