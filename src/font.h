#ifndef FONT_H
#define FONT_H

typedef struct font
{
  int tw, th;
  int cw, ch;

  GLuint texture;
} font_t;

error_code_t font_create(font_t * font, char * path);
error_code_t font_write(font_t font, double x, double y, double vsize, double hsize, char * text);
error_code_t font_write_color(font_t font, double x, double y, double vsize, double hsize, char * text, float r, float g, float b);

#endif
