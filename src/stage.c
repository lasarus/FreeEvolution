#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <math.h>

#include "error_codes.h"
#include "stage.h"

error_code_t init_creature_model(creature_model_t ** model)
{
  *model = malloc(sizeof(creature_model_t));

  return ERROR_NONE;
}

void draw_creature_model(creature_model_t * model, double x, double y, double rot)
{
  int i;

  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  
  for(i = 0; i < SKELETON_LEN; i++)
    {
      glTranslatef(8, 0, 0);

      glBegin(GL_QUADS);

      glColor3f(0.015625, 0.359375, 0.015625);

      glVertex3f(-16.f * model->skeleton[i], -16.f * model->skeleton[i], 0);
      glVertex3f(-16.f * model->skeleton[i], 16.f * model->skeleton[i], 0);
      glVertex3f(16.f * model->skeleton[i], 16.f * model->skeleton[i], 0);
      glVertex3f(16.f * model->skeleton[i], -16.f * model->skeleton[i], 0);

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

object_base_t new_object(object_type_t type, double x, double y, double xv, double yv)
{
  object_base_t object;
  object.type = type;
  object.x = x;
  object.y = y;
  object.xv = xv;
  object.yv = yv;

  return object;
}

double dist_from_player(double x, double y, player_base_t * player)
{
  return sqrt(pow(x - player->x, 2) + pow(y - player->y, 2));
}

error_code_t update_world(world_base_t * world, player_base_t * player, stage_update_info_t * status)
{
  int i;

  for(i = 0; i < world->object_count; i++)
    {
      switch(world->objects[i].type)
	{
	case OBJECT_FOOD:
	  world->objects[i].x += world->objects[i].xv * status->delta;
	  world->objects[i].y += world->objects[i].yv * status->delta;

	  if(dist_from_player(world->objects[i].x, world->objects[i].y, player) > 2000 ||
	     dist_from_player(world->objects[i].x, world->objects[i].y, player) < 32)
	    {
	      world->objects[i].type = OBJECT_NULL;
	    }
	  break;

	default:
	  break;
	}
    }

  return ERROR_NONE;
}

void draw_world(world_base_t * world)
{
  int i;

  for(i = 0; i < world->object_count; i++)
    {
      switch(world->objects[i].type)
	{
	case OBJECT_FOOD:
	  draw_object(&(world->objects[i]));
	  break;

	default:
	  break;
	}
    }
}

void add_object_to_world(world_base_t * world, object_base_t object)
{
  int i;

  for(i = 0; i < world->object_count; i++)
    {
      if(world->objects[i].type == OBJECT_NULL)
	{
	  world->objects[i] = object;
	  break;
	}
    }
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
