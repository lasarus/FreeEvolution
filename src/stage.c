#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <math.h>

#include "error_codes.h"
#include "font.h"
#include "state_information.h"
#include "stage.h"

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

	  if(world->objects[i].x < 0)
	    {
	      world->objects[i].x = 0;
	      world->objects[i].xv = -world->objects[i].xv;
	    }
	  else if(world->objects[i].x > status->screen_width)
	    {
	      world->objects[i].x = status->screen_width;
	      world->objects[i].xv = -world->objects[i].xv;
	    }
	  if(world->objects[i].y < 0)
	    {
	      world->objects[i].y = 0;
	      world->objects[i].yv = -world->objects[i].yv;
	    }
	  else if(world->objects[i].y > status->screen_height)
	    {
	      world->objects[i].y = status->screen_height;
	      world->objects[i].yv = -world->objects[i].yv;
	    }

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
