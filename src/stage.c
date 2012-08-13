#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "error_codes.h"
#include "stage.h"

error_code_t init_creature_model(creature_model_t ** model)
{
  *model = malloc(sizeof(creature_model_t));

  return ERROR_NONE;
}

void draw_creature_model(creature_model_t * model, double x, double y)
{
  int i;

  for(i = 0; i < SKELETON_LEN; i++)
    {
      glLoadIdentity();

      glTranslatef(x, y, 0);

      glBegin(GL_QUADS);

      glColor3f(1.f, 1.f, 1.f);

      glVertex3f(-16.0 * model->skeleton[i], -16.0 * model->skeleton[i], 0);
      glVertex3f(-16.0 * model->skeleton[i], 16.0 * model->skeleton[i], 0);
      glVertex3f(16.0 * model->skeleton[i], 16.0 * model->skeleton[i], 0);
      glVertex3f(16.0 * model->skeleton[i], -16.0 * model->skeleton[i], 0);

      glEnd();
    }
}

void free_creature_model(creature_model_t * model)
{
  free(model);
}

error_code_t init_player(player_base_t ** player, double x, double y)
{
  *player = malloc(sizeof(player_base_t));

  (*player)->x = x;
  (*player)->y = y;

  return ERROR_NONE;
}

void draw_player(player_base_t * player)
{
  glLoadIdentity();

  glTranslatef(player->x, player->y, 0);

  glBegin(GL_QUADS);

  glColor3f(1.f, 1.f, 1.f);

  glVertex3f(-16, -16, 0);
  glVertex3f(-16, 16, 0);
  glVertex3f(16, 16, 0);
  glVertex3f(16, -16, 0);

  glEnd();
}

void draw_object(object_base_t * object)
{
  glLoadIdentity();

  glTranslatef(object->x, object->y, 0);

  glBegin(GL_QUADS);

  glColor3f(1.f, 1.f, 1.f);

  glVertex3f(-16, -16, 0);
  glVertex3f(-16, 16, 0);
  glVertex3f(16, 16, 0);
  glVertex3f(16, -16, 0);

  glEnd();
}
