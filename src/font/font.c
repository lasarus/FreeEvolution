#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

#include "../error_codes.h"
#include "font.h"
#include "../image.h"

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

error_code_t font_write(font_t font, double x, double y, double vsize, double hsize, char * text)
{
  return font_write_color(font, x, y, vsize, hsize, text, 0, 0, 0);
}

error_code_t font_write_color(font_t font, double x, double y, double vsize, double hsize, char * text, float r, float g, float b)
{
  return font_angled_write_color(font, x, y, vsize, hsize, text, r, g, b, 0);
}

error_code_t font_angled_write_color(font_t font, double x, double y, double vsize, double hsize, char * text, float r, float g, float b, double rot)
{
  int i = 0;
  int j = 0;

  if(text == NULL)
    return ERROR_NULL_POINTER;

  for(i = 0; *text != 0; text++)
    {
      double xtex, ytex;

      if(*text == '\n')
	{
	  i = 0;
	  j++;
	  continue;
	}
      else if(*text == '\t')
	{
	  i /= 8;
	  i++;
	  i *= 8;
	  continue;
	}

      xtex = (*text % 16) * font.cw;
      ytex = (*text / 16) * font.ch;

      glLoadIdentity();
      glTranslatef(x, y, 0);
      glRotatef(rot, 0, 0, 1);
      glTranslatef((i * vsize), (j * hsize), 0);

      glColor3f(r, g, b);

      glBindTexture(GL_TEXTURE_2D, font.texture);

      glBegin(GL_QUADS);
      
      glTexCoord2f((1. / font.tw) * xtex, (1. / font.th) * ytex); glVertex3f(0, 0, 0);
      glTexCoord2f((1. / font.tw) * (xtex + font.cw), (1. / font.th) * ytex); glVertex3f(vsize, 0, 0);
      glTexCoord2f((1. / font.tw) * (xtex + font.cw), (1. / font.th) * (ytex + font.ch)); glVertex3f(vsize, hsize, 0);
      glTexCoord2f((1. / font.tw) * xtex, (1. / font.th) * (ytex + font.ch)); glVertex3f(0, hsize, 0);

      glEnd();

      glBindTexture(GL_TEXTURE_2D, 0);

      i++;
    }
  return ERROR_NONE;
}
