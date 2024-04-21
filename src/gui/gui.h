#pragma once

#include "SDL_render.h"

#include <stdexcept>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

namespace GUI {

  enum Direction {
    VERTICAL,
    HORIZONTAL,
  };

  struct Dimension {
    int width;
    int height;
  };

  struct Position {
    int x;
    int y;
  };

  class Transform {
    public:
      Transform(Dimension dimension, Position position)
        : dimension(dimension), position(position)  {}
      
      const Dimension dimension;
      const Position position;
  };

  class Widgeter {
    public:
      Widgeter(SDL_Renderer* renderer, Position start_widget_position, int padding, int font_size) 
        : renderer(renderer), padding(padding), font_size(font_size) {
        font = TTF_OpenFont("assets/fonts/raleway/Raleway-Regular.ttf", font_size);
        
        if(!font) {
          throw std::runtime_error("failed to initialize font");
        } else {
          std::cout << "succesfully created font" << std::endl;
        }

        cur_position = start_widget_position;
        start_position = cur_position;

        cur_color = SDL_Color{255, 255, 255, 255};
        start_color = cur_color;

        cur_direction = VERTICAL;
        start_direction = cur_direction;
      }
   
      void startWidgeter() {
        this->cur_color = this->start_color;
        this->cur_position = this->start_position;
        this->cur_direction = this->start_direction;

        // adjust for initial padding
        this->cur_position.x += this->padding;
        this->cur_position.y += this->padding;
      }

      void box(const Dimension dimension);
      void textBox(const bool draw_border, const std::string text);
      bool button(const Position mouse_position, const std::string text);
      
      void setDrawColor(SDL_Color color);
      void translateCurXPosition(const int width); 
      void translateCurYPosition(const int height); 

      Transform drawRect(const Transform tf);
      Transform drawText(const bool draw_border, const Position position, const int font_size, const std::string text);

    private:
      SDL_Renderer* renderer;
      TTF_Font* font;

      const int padding;
      const int font_size;
      
      SDL_Color cur_color;
      SDL_Color start_color;

      Position cur_position;
      Position start_position;

      Direction cur_direction;
      Direction start_direction;
  };

}
