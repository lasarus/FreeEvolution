#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <time.h>

#include "error_codes.h"
#include "font.h"
#include "stage.h"
#include "creature_editor.h"
#include "stage_cell.h"

int screen_width = 1280, screen_height = 720, screen_bpp = 32;
int quit = 0;

/* inits SDL and OpenGL */
SDL_Surface * screen = NULL;
SDL_Event event;

int init_gl()
{
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);

  glClearColor(0.50390625f, 0.6953125f, 0.85546875f, 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screen_width, screen_height, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);

  if(glGetError() != GL_NO_ERROR)
    return 1;
  
  return 0;
}

int init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return 1;
  
  screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp, SDL_OPENGL);
  
  if(screen == NULL)
    return 1;
  
  if(init_gl())
    return 0;
  
  SDL_WM_SetCaption("Free Evolution", NULL);
  return 0;
}

/* main loop */
int main(int argc, char ** argv)
{
  char buffer[256];
  Uint32 frame, frame_count_s, frame_count_c, fps;
  Uint32 old_ticks, new_ticks;
  stage_base_t * current_stage;
  stage_update_info_t * stage_state;
  stage_draw_info_t * stage_draw_info;
  font_t font;

  if(init())
    return 1;

  stage_cell_init(&current_stage);
  stage_state = malloc(sizeof(stage_update_info_t));
  stage_state->screen_width = screen_width;
  stage_state->screen_height = screen_height;
  stage_state->keydown = SDLK_UNKNOWN;

  font_create(&font, "default.png");

  stage_draw_info = malloc(sizeof(stage_draw_info_t));
  stage_draw_info->font = font;
  stage_draw_info->debug = 1;
  stage_draw_info->screen_width = screen_width;
  stage_draw_info->screen_height = screen_height;

  srand(time(NULL));

  old_ticks = SDL_GetTicks();
  frame_count_s = old_ticks;
  fps = -1;
  while(!quit)
    {
      if(SDL_PollEvent(&event))
	{
	  if(event.type == SDL_QUIT)
	    {
	      quit = 1;
	    }
	  else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F1)
	    {
	      stage_draw_info->debug = !stage_draw_info->debug;
	    }

	  if(event.type == SDL_KEYDOWN)
	    stage_state->keydown = event.key.keysym.sym;
	}

      new_ticks = SDL_GetTicks();
      frame_count_c = new_ticks;
      stage_state->delta = new_ticks - old_ticks;
      stage_state->time = new_ticks;

      stage_state->mouse_state.button = SDL_GetMouseState(&stage_state->mouse_state.x, &stage_state->mouse_state.y);

      stage_state->keystate = SDL_GetKeyState(NULL);

      (*current_stage->update)(current_stage, stage_state);

      stage_state->keydown = SDLK_UNKNOWN;

      /*DRAWING*/

      glClear(GL_COLOR_BUFFER_BIT);

      (*current_stage->draw)(current_stage, stage_draw_info);

      if(frame_count_c - frame_count_s > 1000)
	{
	  fps = frame;
	  frame = 0;
	  frame_count_s = frame_count_c;
	}
      
      sprintf(buffer, "time:\t%u:%u.%u\nframe:\t%u\nfps:\t%u", (new_ticks / 1000) / 60, (new_ticks / 1000) % 60, new_ticks % 1000, frame, fps);

      if(stage_draw_info->debug)
	font_write_color(font, 0, 0, 32, 32, buffer, 0, 0, 0);

      SDL_GL_SwapBuffers();
      
      old_ticks = new_ticks;
      frame++;
    }
  (*current_stage->free)(current_stage);
  return 0;
}
