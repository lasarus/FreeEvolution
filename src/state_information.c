#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "error_codes.h"
#include "font/font.h"
#include "state_information.h"

stage_draw_info_t new_draw_info(int debug, font_t font, int screen_width, int screen_height)
{
  stage_draw_info_t draw_info;

  draw_info.debug = debug;
  draw_info.font = font;

  draw_info.screen_width = screen_width;
  draw_info.screen_height = screen_height;

  return draw_info;
}

stage_update_info_t new_update_info(int screen_width, int screen_height)
{
  stage_update_info_t update_info;

  update_info.screen_width = screen_width;
  update_info.screen_height = screen_height;

  return update_info;
}
