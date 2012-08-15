#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <math.h>

#include "error_codes.h"
#include "font.h"
#include "stage.h"

error_code_t init_creature_model(creature_model_t ** model)
{
  *model = malloc(sizeof(creature_model_t));

  return ERROR_NONE;
}

void draw_creature_eyes(creature_model_t * model, double x, double y, double rot)
{
  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  glTranslatef(model->eyes * 8, model->skeleton[model->eyes] * 16, 0);

  glBegin(GL_QUADS);
  
  glColor4f(1, 1, 1, 1);
      
  glVertex3f(-8., -8., 0);
  glVertex3f(8., -8., 0);
  glVertex3f(8., 8., 0);
  glVertex3f(-8., 8., 0);

  glColor4f(0, 0, 0, 1);
  glVertex3f(-2., -2., 0);
  glVertex3f(2., -2., 0);
  glVertex3f(2., 2., 0);
  glVertex3f(-2., 2., 0);
      
  glEnd();

  glTranslatef(0, -(model->skeleton[model->eyes] * 32), 0);

  glBegin(GL_QUADS);
  
  glColor4f(1, 1, 1, 1);
      
  glVertex3f(-8., -8., 0);
  glVertex3f(8., -8., 0);
  glVertex3f(8., 8., 0);
  glVertex3f(-8., 8., 0);

  glColor4f(0, 0, 0, 1);
  glVertex3f(-2., -2., 0);
  glVertex3f(2., -2., 0);
  glVertex3f(2., 2., 0);
  glVertex3f(-2., 2., 0);
      
  glEnd();
}

void draw_creature_model(creature_model_t * model, double x, double y, double rot)
{
  int i;

  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  
  for(i = 1; i < SKELETON_LEN; i++)
    {
      glTranslatef(8, 0, 0);

      glBegin(GL_QUADS);

      glColor4f(0.000000, 0.535156, 0.488281, 1);

      glVertex3f(-8, -16.f * model->skeleton[i - 1], 0);
      glVertex3f(-8, 16.f * model->skeleton[i - 1], 0);
      glVertex3f(0, 16.f * model->skeleton[i], 0);
      glVertex3f(0, -16.f * model->skeleton[i], 0);

      glEnd();
    }

  draw_creature_eyes(model, x, y, rot);
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
	     dist_from_player(world->objects[i].x, world->objects[i].y, player) < 16)
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

void draw_world(world_base_t * world, stage_draw_info_t * info)
{
  int i;

  for(i = 0; i < world->object_count; i++)
    {
      switch(world->objects[i].type)
	{
	case OBJECT_FOOD:
	  draw_object(&(world->objects[i]));

	  if(info->debug)
	    font_write_color(info->font, world->objects[i].x, world->objects[i].y, 16, 16, "Food", 0, 0, 0);
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

  glColor3f(0.000000, 0.535156, 0.000000);

  glVertex3f(-16, -16, 0);
  glVertex3f(-16, 16, 0);
  glVertex3f(16, 16, 0);
  glVertex3f(16, -16, 0);

  glEnd();
}
