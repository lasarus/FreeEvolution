#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "error_codes.h"
#include "font.h"
#include "stage.h"
#include "creature_editor.h"

editor_data_t init_creature_editor(creature_model_t * creature)
{
  editor_data_t data;

  data.creature = creature;
  data.selected = 3;

  return data;
}

int update_creature_editor(editor_data_t * data, stage_update_info_t * state)
{
  if(state->keystate[SDLK_UP] && data->creature->skeleton[data->selected] < 10)
    {
      if(data->creature->skeleton[data->selected] < 10)
	data->creature->skeleton[data->selected] += 0.01 * state->delta;
    }
  else if(state->keystate[SDLK_DOWN])
    {
      if(data->creature->skeleton[data->selected] > 0.1)
	data->creature->skeleton[data->selected] -= 0.01 * state->delta;
    }

  if(data->creature->skeleton[data->selected] > 10)
    data->creature->skeleton[data->selected] = 10;
  else if(data->creature->skeleton[data->selected] < 0.1)
    data->creature->skeleton[data->selected] = 0.1;


  if(state->keydown == SDLK_LEFT)
    {
      if(data->selected > 0)
	data->selected--;
    }
  else if(state->keydown == SDLK_RIGHT)
    {
      if(data->selected < SKELETON_LEN - 1)
	data->selected++;
    }

  if(state->keydown == SDLK_F2)
    return 1;
  return 0;
}

void draw_creature_editor(editor_data_t * data, stage_draw_info_t * info)
{
  int i;

  glLoadIdentity();
  glTranslatef(info->screen_width / 2, info->screen_height / 2, 0);
  
  for(i = 1; i < SKELETON_LEN; i++)
    {
      glTranslatef(8, 0, 0);

      glBegin(GL_QUADS);

      if(data->selected == i - 1)
	glColor4f(1., 0., 0., 1);
      else
	glColor4f(0.000000, 0.535156, 0.488281, 1);

      glVertex3f(-8, -16.f * data->creature->skeleton[i - 1], 0);
      glVertex3f(-8, 16.f * data->creature->skeleton[i - 1], 0);

      if(data->selected == i)
	glColor4f(1., 0., 0., 1);
      else
	glColor4f(0.000000, 0.535156, 0.488281, 1);

      glVertex3f(0, 16.f * data->creature->skeleton[i], 0);
      glVertex3f(0, -16.f * data->creature->skeleton[i], 0);

      glEnd();
    }
}
