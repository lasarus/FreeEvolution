#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>
#include "error_codes.h"

SDL_Surface * load_image(char * filename);

error_code_t OGConvertS(SDL_Surface * surface, GLuint * tex2);

#endif
