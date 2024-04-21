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

  GUI::Widgeter widgeter(renderer, GUI::Position{0, 0}, 2, 4, 13);

  bool left_mouse_is_pressed = false;
  bool left_mouse_was_pressed = false;

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
    
    left_mouse_was_pressed = false;
    if(SDL_GetMouseState(&mouse_position.x, &mouse_position.y) & SDL_BUTTON(MOUSE_BUTTON_LEFT)) {
      left_mouse_is_pressed = true;
    } else {
      if(left_mouse_is_pressed) {
        left_mouse_was_pressed = true;
      }

      left_mouse_is_pressed = false;
    }

    SDL_Color bg_color{0, 0, 0, 255};
    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);
  
    widgeter.startWidgeter();
    widgeter.textBox(true, false, "pacman emulator");
    
    for(int i = 0; i < 5; i++) {
      widgeter.box(GUI::Dimension{10, 10});
    }

    widgeter.startMenu();
    if(widgeter.button(mouse_position, "Run", left_mouse_is_pressed, left_mouse_was_pressed)) {
      std::cout << "Run" << std::endl;
    }
    if(widgeter.button(mouse_position, "Stop", left_mouse_is_pressed, left_mouse_was_pressed)) {
      std::cout << "Stop" << std::endl;
    }
    if(widgeter.button(mouse_position, "Step 1", left_mouse_is_pressed, left_mouse_was_pressed)) {
      std::cout << "Step 1" << std::endl;
    }
    if(widgeter.button(mouse_position, "Step 10", left_mouse_is_pressed, left_mouse_was_pressed)) {
      std::cout << "Step 10" << std::endl;
    }
    widgeter.endMenu();

    for(int i = 0; i < 5; i++) {
      widgeter.box(GUI::Dimension{10, 10});
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(50);
  }

exit:
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_Quit();
  return 0;
}
