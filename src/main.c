#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <time.h>

#include "error_codes.h"
#include "stage.h"
#include "stage_cell.h"

int screen_width = 640, screen_height = 480, screen_bpp = 32;
int quit = 0;

/* inits SDL and OpenGL */
SDL_Surface * screen = NULL;
SDL_Event event;

int init_gl()
{
  glClearColor(0.50390625f, 0.6953125f, 0.85546875f, 0);
  
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
  Uint32 old_ticks, new_ticks;
  stage_base_t * current_stage;
  stage_update_info_t * stage_state;

  if(init())
    return 1;

  stage_cell_init(&current_stage);
  stage_state = malloc(sizeof(stage_update_info_t));
  stage_state->screen_width = screen_width;
  stage_state->screen_height = screen_height;
  srand(time(NULL));

  old_ticks = SDL_GetTicks();
  while(!quit)
    {
      if(SDL_PollEvent(&event))
	{
	  if(event.type == SDL_QUIT)
	    {
	      quit = 1;
	    }
	}
      new_ticks = SDL_GetTicks();
      stage_state->delta = new_ticks - old_ticks;
      stage_state->time = new_ticks;

      stage_state->keystate = SDL_GetKeyState(NULL);

      (*current_stage->update)(current_stage, stage_state);

      glClear(GL_COLOR_BUFFER_BIT);

      (*current_stage->draw)(current_stage);

      SDL_GL_SwapBuffers();
      SDL_Delay(10);
      
      old_ticks = new_ticks;
    }
  (*current_stage->free)(current_stage);
  return 0;
}
