#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "stage.h"

void draw_player(player_base_t * player)
{
  glLoadIndentity();

  glTranslatef(player->x, player->y, 0);

  glBegin(GL_QUADS);

  glColor3f(1f, 1f, 1f);

  glVertex3f(-16, -16, 0);
  glVertex3f(-16, 16, 0);
  glVertex3f(16, 16, 0);
  glVertex3f(16, -16, 0);

  glEnd();
}

void draw_object(object_base_t * object)
{
  glLoadIndentity();

  glTranslatef(object-player->x, object->y, 0);

  glBegin(GL_QUADS);

  glColor3f(1f, 1f, 1f);

  glVertex3f(-16, -16, 0);
  glVertex3f(-16, 16, 0);
  glVertex3f(16, 16, 0);
  glVertex3f(16, -16, 0);

  glEnd();
}
