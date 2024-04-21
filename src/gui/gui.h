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
      Widgeter(SDL_Renderer* renderer, Position start_widget_position, int margin, int padding, int font_size) 
        : renderer(renderer), margin(margin), padding(padding), font_size(font_size) {
        font = TTF_OpenFont("assets/fonts/raleway/Raleway-Regular.ttf", font_size);
        
        if(!font) {
          throw std::runtime_error("failed to initialize font");
        } else {
          std::cout << "succesfully created font" << std::endl;
        }

        // FIXME: set these threw the constructor and mutable methods
        text_color = SDL_Color{255, 255, 255, 255};
        border_color = SDL_Color{0, 0, 255, 255};
        foreground_color = SDL_Color{255, 255, 255, 255};
        background_color = SDL_Color{50, 50, 50, 255};
        hovered_color= SDL_Color{100, 100, 100, 255};
        pressed_color = SDL_Color{150, 150, 150, 255};


        cur_position = start_widget_position;
        start_position = cur_position;

        cur_direction = VERTICAL;
        start_direction = cur_direction;
      }
   
      void startWidgeter() {
        this->cur_position = this->start_position;
        this->cur_direction = this->start_direction;
        this->cur_position.x += this->padding;
        this->cur_position.y += this->padding;
      }

      void startMenu() {
        this->cur_direction = HORIZONTAL;
        this->in_menu = true;
        
        // have to reset the x position to value before menu creation
        this->before_menu_x = this->cur_position.x;
      }

      void endMenu() {
        this->in_menu = false;
        this->cur_direction = VERTICAL;

        this->cur_position.x = this->before_menu_x;
        this->cur_position.y = this->after_menu_y;
      }

      void box(const Dimension dimension);
      void textBox(const bool draw_border, const bool fill_border, const std::string text);
      bool button(const Position mouse_position, const std::string text, const bool cur_pressed, const bool just_released);
      void adjustCurPosition(const Transform tf);
      void setDrawColor(const SDL_Color color);
      void drawRect(const Transform tf);
      void drawFillRect(const Transform tf);
      void drawText(const Transform tf, const std::string text);

    private:
      SDL_Renderer* renderer;
      TTF_Font* font;

      const int padding;
      const int margin;
      const int font_size;
  
      bool in_menu = false;

      int before_menu_x;
      int after_menu_y;
  
      SDL_Color text_color;
      SDL_Color border_color;
      SDL_Color foreground_color;
      SDL_Color background_color;
      SDL_Color hovered_color;
      SDL_Color pressed_color;
      
      Position cur_position;
      Position start_position;

      Direction cur_direction;
      Direction start_direction;
  };

}
