#ifndef STATE_INFORMATION_H
#define STATE_INFORMATION_H

typedef struct stage_update_info
{
  Uint32 delta;
  Uint32 time;
  Uint8 * keystate;

  SDLKey keydown;

  int screen_width;
  int screen_height;

  struct
  {
    int x;
    int y;
    Uint8 button;
  } mouse_state;
} stage_update_info_t;

typedef struct stage_draw_info
{
  int debug;
  font_t font;

  Uint32 time;

  int screen_width;
  int screen_height;
} stage_draw_info_t;

stage_draw_info_t new_draw_info(int debug, font_t font, int screen_width, int screen_height);
stage_update_info_t new_update_info(int screen_width, int screen_height);

#endif
