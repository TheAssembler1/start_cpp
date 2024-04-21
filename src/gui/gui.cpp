#include "gui.h"

using namespace GUI;

void Widgeter::adjustCurPosition(const Transform tf) {
  if(this->cur_direction == VERTICAL) {
    this->cur_position.y += tf.dimension.height;
    this->cur_position.y += this->padding;
  } else {
    this->cur_position.x += tf.dimension.width;
    this->cur_position.x += this->padding;
  }
}

void Widgeter::setDrawColor(const SDL_Color color) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void Widgeter::box(const Dimension dimension) {
  this->setDrawColor(this->foreground_color);

  const Transform final_tf{dimension, this->cur_position};
  this->drawRect(Transform{dimension, this->cur_position});

  if(in_menu) {
    this->after_menu_y = this->cur_position.y + final_tf.dimension.height + padding;
  }

  adjustCurPosition(final_tf);
}

void Widgeter::textBox(const bool draw_border, const bool fill_border, const std::string text) {
  Dimension text_dimension{};

  TTF_SizeText(this->font, text.c_str(), &text_dimension.width, &text_dimension.height);

  Position text_position{this->cur_position.x + this->margin, this->cur_position.y + this->margin};
  Position text_box_position{this->cur_position.x, this->cur_position.y};
  Dimension text_box_dimesion{text_dimension.width + (2 * this->margin), text_dimension.height + (2 * this->margin)};
 
  const Transform text_box_tf{text_box_dimesion, text_box_position};
  const Transform text_tf{text_dimension, text_position};

  if(fill_border) {
    this->setDrawColor(this->background_color);
    this->drawFillRect(text_box_tf);
  }

  if(draw_border) {
    this->setDrawColor(this->border_color);
    this->drawRect(text_box_tf);
  }
  
  if(in_menu) {
    this->after_menu_y = this->cur_position.y + text_box_tf.dimension.height;
  }
  // dont't set render color as the ttf lib takes it as a param in func 
  this->drawText(text_tf, text);
  this->adjustCurPosition(text_box_tf);
}

static bool is_mouse_colliding(Position mouse, Transform tf) {
  if(mouse.x > tf.position.x && mouse.x < tf.position.x + tf.dimension.width) {
    if(mouse.y > tf.position.y && mouse.y < tf.position.y + tf.dimension.height) {
      return true; 
    }
  }

  return false;
}

bool Widgeter::button(const Position mouse_position, std::string text, const bool cur_pressed, const bool just_released) {
  Dimension text_dimension{};

  TTF_SizeText(this->font, text.c_str(), &text_dimension.width, &text_dimension.height);

  Position text_position{this->cur_position.x + this->margin, this->cur_position.y + this->margin};
  Position text_box_position{this->cur_position.x, this->cur_position.y};
  Dimension text_box_dimesion{text_dimension.width + (2 * this->margin), text_dimension.height + (2 * this->margin)};
 
  const Transform text_box_tf{text_box_dimesion, text_box_position};
  const Transform text_tf{text_dimension, text_position};
  bool colliding = is_mouse_colliding(mouse_position, Transform{text_box_dimesion, this->cur_position});
  
  if(colliding && cur_pressed) {
    this->setDrawColor(this->pressed_color);
  } else if(colliding) {
    this->setDrawColor(this->hovered_color);
  } else {
    this->setDrawColor(this->background_color);
  }
  this->drawFillRect(text_box_tf);

  this->setDrawColor(this->border_color);
  this->drawRect(text_box_tf);
  
  if(in_menu) {
    this->after_menu_y = this->cur_position.y + text_box_dimesion.height + this->padding;
  }

  // dont't set render color as the ttf lib takes it as a param in func 
  this->drawText(text_tf, text);
  this->adjustCurPosition(text_box_tf);
  
  if(just_released && colliding) {
    return true;
  }

  return false;
}

void Widgeter::drawRect(const Transform tf) {
  SDL_Rect rect{tf.position.x, tf.position.y, tf.dimension.width, tf.dimension.height};
  SDL_RenderDrawRect(this->renderer, &rect); 
}

void Widgeter::drawFillRect(const Transform tf) {
  SDL_Rect rect{tf.position.x, tf.position.y, tf.dimension.width, tf.dimension.height};
  SDL_RenderFillRect(this->renderer, &rect); 
}

void Widgeter::drawText(const Transform tf, const std::string text) {
  SDL_Rect rect{tf.position.x, tf.position.y, tf.dimension.width, tf.dimension.height}; 
  SDL_Surface* text_surface = TTF_RenderText_Solid(this->font, text.c_str(), this->text_color);

  if(!text_surface) {
    throw std::runtime_error("failed to create surface from texture");
  }
  
  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(this->renderer, text_surface);

  if(!text_texture) {
    throw std::runtime_error("failed to create texture");
  }

  SDL_RenderCopy(renderer, text_texture, NULL, &rect); 
  
  SDL_FreeSurface(text_surface);
  SDL_DestroyTexture(text_texture);
}

