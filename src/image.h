#ifndef IMAGE_H
#define IMAGE_H

SDL_Surface * load_image(char * filename);
error_code_t surface_to_GLtexture(SDL_Surface * surface, GLuint * tex2);

#endif
