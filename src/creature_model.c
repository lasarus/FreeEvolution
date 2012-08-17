#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <math.h>

#include "error_codes.h"
#include "font.h"
#include "state_information.h"
#include "creature_model.h"

#ifndef PI
#define PI 3.14159265358979
#endif

double height_at_pos(stage_draw_info_t * draw_info, creature_model_t * model, Uint32 animation, int pos)
{
  double r = 0;
  if(animation & ANIMATION_SWIM_FAST)
    r += (sin((pos + (-draw_info->time / 10.) - 1) / 3.) + 1) * 8.;
  else if(animation & ANIMATION_SWIM_SLOW)
    r += (sin((pos + (-draw_info->time / 10.) - 1) / 3.) + 1) * 4.;
  
  if(animation & ANIMATION_TURN_LEFT)
    r += pos * pos / 8.;
  else if(animation & ANIMATION_TURN_RIGHT)
    r -= pos * pos / 8.;

  return r;
}

void draw_eye(double scale)
{
  glBegin(GL_QUADS);

  glColor4f(1, 1, 1, 1);
      
  glVertex3f(-8. * scale, -8. * scale, 0);
  glVertex3f(8. * scale, -8. * scale, 0);
  glVertex3f(8. * scale, 8. * scale, 0);
  glVertex3f(-8. * scale, 8. * scale, 0);

  glColor4f(0, 0, 0, 1);
  glVertex3f(-2. * scale, -2. * scale, 0);
  glVertex3f(2. * scale, -2. * scale, 0);
  glVertex3f(2. * scale, 2. * scale, 0);
  glVertex3f(-2. * scale, 2. * scale, 0);

  glEnd();
}

void draw_spike(double scale, int inverted)
{
  glBegin(GL_TRIANGLES);
  
  glColor4f(1, 1, 1, 1);
      
  glVertex3f(-4 * scale, 0, 0);
  glVertex3f(4 * scale, 0, 0);
  glVertex3f(0, (inverted ? -32 : 32) * scale, 0);
      
  glEnd();
}

void draw_creature_eyes(stage_draw_info_t * draw_info, creature_model_t * model, double x, double y, double rot, int pos, Uint32 animation)
{
  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  glTranslatef(pos * 8, model->skeleton[pos] * 16 - height_at_pos(draw_info, model, animation, pos), 0);

  draw_eye(1);

  glTranslatef(0, -(model->skeleton[pos] * 32), 0);

  draw_eye(1);
}

void draw_creature_spikes(stage_draw_info_t * draw_info, creature_model_t * model, double x, double y, double rot, int pos, Uint32 animation)
{
  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  glTranslatef(pos * 8, model->skeleton[pos] * 16 - height_at_pos(draw_info, model, animation, pos), 0);

  draw_spike(1, 0);

  glTranslatef(0, -(model->skeleton[pos] * 32), 0);

  draw_spike(1, 1);
}

void draw_creature_model(stage_draw_info_t * draw_info, creature_model_t * model, double x, double y, double rot, Uint32 animation)
{
  draw_editor_creature_model(draw_info, model, x, y, rot, -1, animation);
}

void draw_editor_creature_model(stage_draw_info_t * draw_info, creature_model_t * model, double x, double y, double rot, int selected, Uint32 animation)
{
  int i;
  double w1, w2;

  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  
  for(i = 1; i < SKELETON_LEN; i++)
    {
      w1 = height_at_pos(draw_info, model, animation, i - 1);
      w2 = height_at_pos(draw_info, model, animation, i);

      glTranslatef(8, 0, 0);

      glBegin(GL_QUADS);

      if(i - 1 == selected)	
	glColor4f(1, 0, 0, 1);
      else
	glColor4f(0.000000, 0.535156, 0.488281, 1);

      glVertex3f(-8, 16.f * model->skeleton[i - 1] - w1, 0);
      glVertex3f(-8, -16.f * model->skeleton[i - 1] - w1, 0);

      if(i == selected)	
	glColor4f(1, 0, 0, 1);
      else
	glColor4f(0.000000, 0.535156, 0.488281, 1);

      glVertex3f(0, -16.f * model->skeleton[i] - w2, 0);
      glVertex3f(0, 16.f * model->skeleton[i] - w2, 0);

      glEnd();
    }

  for(i = 0; i < ADDITION_COUNT; i++)
    {
      switch(model->additions[i].type)
	{
	case ADDITION_EYE:
	  draw_creature_eyes(draw_info, model, x, y, rot, model->additions[i].pos, animation);
	  break;

	case ADDITION_MOUTH:
	  draw_creature_spikes(draw_info, model, x, y, rot, model->additions[i].pos, animation);
	  break;

	case ADDITION_SPIKE:
	  draw_creature_spikes(draw_info, model, x, y, rot, model->additions[i].pos, animation);
	  break;

	default:
	  break;
	}
    }
}

void creature_add_addition(creature_model_t * model, addition_type_t type, int pos)
{
  int i;

  for(i = 0; i < ADDITION_COUNT; i++)
    {
      if(model->additions[i].type == ADDITION_NONE)
	{
	  model->additions[i].type = type;
	  model->additions[i].pos = pos;
	  break;
	}
    }
}

void creature_remove_addition(creature_model_t * model, int pos)
{
  int i;

  for(i = 0; i < ADDITION_COUNT; i++)
    {
      if(model->additions[i].type != ADDITION_NONE && model->additions[i].pos == pos)
	{
	  model->additions[i].type = ADDITION_NONE;
	}
    }
}

int creature_addition_at_pos(creature_model_t * model, int pos)
{
  int i;

  for(i = 0; i < ADDITION_COUNT; i++)
    {
      if(model->additions[i].type != ADDITION_NONE && model->additions[i].pos == pos)
	{
	  return 1;
	}
    }
  return 0;
}
