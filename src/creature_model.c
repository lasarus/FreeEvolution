#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <math.h>

#include "error_codes.h"
#include "creature_model.h"

#ifndef PI
#define PI 3.14159265358979
#endif 

void draw_creature_eyes(creature_model_t * model, double x, double y, double rot, int pos)
{
  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  glTranslatef(pos * 8, model->skeleton[pos] * 16, 0);

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

  glTranslatef(0, -(model->skeleton[pos] * 32), 0);

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

void draw_creature_spikes(creature_model_t * model, double x, double y, double rot, int pos)
{
  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  glTranslatef(pos * 8, model->skeleton[pos] * 16, 0);

  glBegin(GL_TRIANGLES);
  
  glColor4f(1, 1, 1, 1);
      
  glVertex3f(-4, 0, 0);
  glVertex3f(4, 0, 0);
  glVertex3f(0, 32, 0);
      
  glEnd();

  glTranslatef(0, -(model->skeleton[pos] * 32), 0);

  glBegin(GL_TRIANGLES);
  
  glColor4f(1, 1, 1, 1);
      
  glVertex3f(-4, 0, 0);
  glVertex3f(4, 0, 0);
  glVertex3f(0, -32, 0);
      
  glEnd();
}

void draw_creature_model(creature_model_t * model, double x, double y, double rot)
{
  draw_editor_creature_model(model, x, y, rot, -1);
}

void draw_editor_creature_model(creature_model_t * model, double x, double y, double rot, int selected)
{
  int i;

  glLoadIdentity();
  glTranslatef(x, y, 0);
  glRotatef(rot / PI * 180, 0.f, 0.f, 1.f);
  
  for(i = 1; i < SKELETON_LEN; i++)
    {
      glTranslatef(8, 0, 0);

      glBegin(GL_QUADS);

      if(i - 1 == selected)	
	glColor4f(1, 0, 0, 1);
      else
	glColor4f(0.000000, 0.535156, 0.488281, 1);

      glVertex3f(-8, -16.f * model->skeleton[i - 1], 0);
      glVertex3f(-8, 16.f * model->skeleton[i - 1], 0);

      if(i == selected)	
	glColor4f(1, 0, 0, 1);
      else
	glColor4f(0.000000, 0.535156, 0.488281, 1);

      glVertex3f(0, 16.f * model->skeleton[i], 0);
      glVertex3f(0, -16.f * model->skeleton[i], 0);

      glEnd();
    }

  for(i = 0; i < ADDITION_COUNT; i++)
    {
      switch(model->additions[i].type)
	{
	case ADDITION_EYE:
	  draw_creature_eyes(model, x, y, rot, model->additions[i].pos);
	  break;

	case ADDITION_MOUTH:
	  draw_creature_spikes(model, x, y, rot, model->additions[i].pos);
	  break;

	case ADDITION_SPIKE:
	  draw_creature_spikes(model, x, y, rot, model->additions[i].pos);
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
