#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

#include "error_codes.h"
#include "image.h"

SDL_Surface * load_image(char * filename)
{
  SDL_Surface * loadedImage = NULL;
  SDL_Surface * optimizedImage = NULL;
  loadedImage = IMG_Load(filename);
  if(loadedImage != NULL)
    {
      optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
      SDL_FreeSurface(loadedImage);
    }
  return optimizedImage;
}

error_code_t surface_to_GLtexture(SDL_Surface * surface, GLuint * tex2)
{
  GLuint texture;
  GLenum texture_format;
  GLint  nOfColors;

  if ( (surface->w & (surface->w - 1)) != 0 ) {
    return ERROR_IMAGE_NOT_POWER_OF_TWO;
  }

  if ( (surface->h & (surface->h - 1)) != 0 ) {
    return ERROR_IMAGE_NOT_POWER_OF_TWO;
  }

  nOfColors = surface->format->BytesPerPixel;
  if (nOfColors == 4)
    {
      if (surface->format->Rmask == 0x000000ff)
	texture_format = GL_RGBA;
      else
	texture_format = GL_BGRA;
    } else if (nOfColors == 3)
    {
      if (surface->format->Rmask == 0x000000ff)
	texture_format = GL_RGB;
      else
	texture_format = GL_BGR;
    } else {
    return ERROR_IMAGE_INVALID_PIXELS_PER_BYTES;
  }

  glGenTextures( 1, &texture );

  glBindTexture( GL_TEXTURE_2D, texture );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

  glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
		texture_format, GL_UNSIGNED_BYTE, surface->pixels );

  *tex2 = texture;

  return ERROR_NONE;
}
