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

  return data;
}

void update_creature_editor(editor_data_t * data, stage_update_info_t * state)
{
}

void draw_creature_editor(editor_data_t * data, stage_draw_info_t * info)
{
}
