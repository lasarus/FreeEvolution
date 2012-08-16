#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "error_codes.h"
#include "font.h"
#include "creature_model.h"
#include "stage.h"
#include "creature_editor.h"

editor_data_t init_creature_editor(creature_model_t * creature)
{
  editor_data_t data;

  data.creature = creature;
  data.selected = 3;

  data.current_type = ADDITION_EYE;
  data.saddition = 0;

  return data;
}

int update_creature_editor(editor_data_t * data, stage_update_info_t * state)
{
  if(!data->saddition)
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
    }
  else
    {
      if(state->keydown == SDLK_LEFT)
	{
	  if(data->selected > 1)
	    data->current_type--;
	}
      else if(state->keydown == SDLK_RIGHT)
	{
	  data->current_type++;
	}
    }

  if(data->creature->skeleton[data->selected] > 10)
    data->creature->skeleton[data->selected] = 10;
  else if(data->creature->skeleton[data->selected] < 0.1)
    data->creature->skeleton[data->selected] = 0.1;
  
  if(state->keydown == SDLK_LCTRL)
    {
      if(creature_addition_at_pos(data->creature, data->selected))
	creature_remove_addition(data->creature, data->selected);
      else
	creature_add_addition(data->creature, data->current_type, data->selected);
    }
  else if(state->keydown == SDLK_TAB)
    {
      data->saddition = !data->saddition;
    }

  if(state->keydown == SDLK_F2)
    return 1;
  return 0;
}

void draw_creature_editor(editor_data_t * data, stage_draw_info_t * info)
{
  char * str = NULL;
  draw_editor_creature_model(data->creature, info->screen_width / 2, info->screen_height / 2, 0, data->selected);

  glLoadIdentity();
  glTranslatef(info->screen_width / 2, 64, 0);

  switch(data->current_type)
    {
    case ADDITION_MOUTH:
      str = "Mouth";
      break;

    case ADDITION_EYE:
      draw_eye(4);
      str = "Eye";
      break;

    case ADDITION_SPIKE:
      draw_spike(4, 1);
      str = "Spike";
      break;

    default:
      str = "?";
      break;
    }
  font_write(info->font, info->screen_width / 2, 64, 16, 16, str);
}
