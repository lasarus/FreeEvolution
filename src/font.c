#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

#include "error_codes.h"
#include "font.h"
#include "image.h"

error_code_t font_create(font_t * font, char * path)
{
  error_code_t error;
  SDL_Surface * tmp = load_image(path);

  if(tmp == NULL)
    return ERROR_IMAGE_LOADING_ERROR;
  
  error = surface_to_GLtexture(tmp, &(font->texture));

  font->tw = tmp->w;
  font->th = tmp->h;

  font->cw = tmp->w / 16;
  font->ch = tmp->h / 16;

  SDL_FreeSurface(tmp);

  if(error != ERROR_NONE)
      return error;

  return ERROR_NONE;
}

error_code_t font_write(font_t font, double x, double y, double size, char * text)
{
  int i = 0;
  int j = 0;

  if(text == NULL)
    return ERROR_NULL_POINTER;

  for(i = 0; *text != 0; text++)
    {
      double xtex, ytex;

      xtex = (*text % 16) * font.cw;
      ytex = (*text / 16) * font.ch;

      glLoadIdentity();
      glTranslatef(x + (i * size), y + (j * size), 0);

      glColor3f(.5, .5, .5);

      glBindTexture(GL_TEXTURE_2D, font.texture);

      glBegin(GL_QUADS);
      
      glTexCoord2f((1. / font.tw) * xtex, (1. / font.th) * ytex); glVertex3f(0, 0, 0);
      glTexCoord2f((1. / font.tw) * (xtex + font.cw), (1. / font.th) * ytex); glVertex3f(16, 0, 0);
      glTexCoord2f((1. / font.tw) * (xtex + font.cw), (1. / font.th) * (ytex + font.ch)); glVertex3f(16, 16, 0);
      glTexCoord2f((1. / font.tw) * xtex, (1. / font.th) * (ytex + font.ch)); glVertex3f(0, 16, 0);

      glEnd();

      glBindTexture(GL_TEXTURE_2D, 0);

      i++;
    }
  return ERROR_NONE;
}
