#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <time.h>

int screen_width = 640, screen_height = 480, screen_bpp = 32;
int quit = 0;

/* inits SDL and OpenGL */
SDL_Surface * screen = NULL;
SDL_Event event;

int init_gl()
{
  glClearColor(0.f, 0.f, 0.f, 0);
  
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
  if(init())
    return 1;

  srand(time(NULL));

  while(!quit)
    {
      if(SDL_PollEvent(&event))
	{
	  if(event.type == SDL_QUIT)
	    {
	      quit = 1;
	    }
	}
      glClear(GL_COLOR_BUFFER_BIT);
      SDL_GL_SwapBuffers();
      SDL_Delay(10);
    }

  return 0;
}
