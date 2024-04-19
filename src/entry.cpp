#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

int main() {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "failed to init" << std::endl;
  } else {
    std::cout << "success to init" << std::endl;
  }

  std::cout << "Hello World!" << std::endl;
}
