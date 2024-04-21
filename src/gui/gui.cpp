#include "gui.h"

using namespace GUI;

static void adjustCurPosition(const int padding, Direction direction, Transform tf, Position& position) {
  if(direction == VERTICAL) {
    position.y += tf.dimension.height;
    position.y += padding;
  } else {
    position.x += tf.dimension.width;
    position.x += padding;
  }
}

void Widgeter::translateCurXPosition(const int width) {
  this->cur_position.x += width;
}

void Widgeter::translateCurYPosition(const int height) {
  this->cur_position.y += height;
}

void Widgeter::setDrawColor(const SDL_Color color) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void Widgeter::box(const Dimension dimension) {
  Transform result_tf = this->drawRect(Transform{dimension, this->cur_position});
  adjustCurPosition(this->padding, this->cur_direction, result_tf, this->cur_position);
}

void Widgeter::textBox(const bool draw_border, const std::string text) {
  Transform result_tf = this->drawText(draw_border, this->cur_position, this->font_size, text);
  adjustCurPosition(this->padding, this->cur_direction, result_tf, this->cur_position);
}

bool Widgeter::button(const Position mouse_position, std::string text) {
  std::cout << mouse_position.x << std::endl;
  std::cout << mouse_position.y << std::endl;

  Transform result_tf = this->drawText(true, this->cur_position, this->font_size, text);
  adjustCurPosition(this->padding, this->cur_direction, result_tf, this->cur_position);

  return false;
}

Transform Widgeter::drawRect(const Transform tf) {
  // set draw color
  this->setDrawColor(this->cur_color);

  SDL_Rect rect{tf.position.x, tf.position.y, tf.dimension.width, tf.dimension.height};
  SDL_RenderDrawRect(this->renderer, &rect); 

  return tf;
}

Transform Widgeter::drawText(const bool draw_border, const Position position, const int font_size, const std::string text) {
  // set draw color
  this->setDrawColor(this->cur_color);

  int width, height;
  unsigned char cur_r, cur_g, cur_b, cur_a;
  
  TTF_SizeText(font, text.c_str(), &width, &height);
  SDL_GetRenderDrawColor(renderer, &cur_r, &cur_g, &cur_b, &cur_a);
  SDL_Rect rect{position.x, position.y, width, height}; 

  // creating surface 
  SDL_Surface* text_surface = TTF_RenderText_Solid(this->font, text.c_str(), cur_color);

  if(!text_surface) {
    throw std::runtime_error("failed to create surface from texture");
  }
  
  // convvert surface to texture
  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(this->renderer, text_surface);

  if(!text_texture) {
    throw std::runtime_error("failed to create texture");
  }

  if(draw_border) {
    SDL_RenderDrawRect(renderer, &rect); 
  }
  
  // render texture
  SDL_RenderCopy(renderer, text_texture, NULL, &rect); 
  
  // free resources
  SDL_FreeSurface(text_surface);
  SDL_DestroyTexture(text_texture);

  return Transform{Dimension{width, height}, position};
}

