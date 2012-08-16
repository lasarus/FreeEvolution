#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "error_codes.h"
#include "font.h"
#include "state_information.h"
#include "creature_model.h"
#include "stage.h"
#include "creature_editor.h"
#include "stage_cell.h"

#define PLAYER_SPEED .002
#define OBJECT_SPEED .05

error_code_t stage_cell_update(stage_base_t * self, stage_update_info_t * status)
{
  Uint8 * keystate = status->keystate;
  stage_cell_t * cell_stage = (stage_cell_t *)self;
  
  if(cell_stage->editor)
    {
      int r = update_creature_editor(&(cell_stage->editor_data), status);
      
      if(r)
	cell_stage->editor = 0;
      return ERROR_NONE;
    }

  cell_stage->player.x += cell_stage->player.xv * status->delta;
  cell_stage->player.y += cell_stage->player.yv * status->delta;

  cell_stage->player.xv /= 1 + (.005 * status->delta);
  cell_stage->player.yv /= 1 + (.005 * status->delta);

  if(keystate[SDLK_w])
    {
      cell_stage->player.yv += -1 * PLAYER_SPEED * status->delta;
    }
  if(keystate[SDLK_s])
    {
      cell_stage->player.yv += 1 * PLAYER_SPEED * status->delta;
    }
  if(keystate[SDLK_a])
    {
      cell_stage->player.xv += -1 * PLAYER_SPEED * status->delta;
    }
  if(keystate[SDLK_d])
    {
      cell_stage->player.xv += 1 * PLAYER_SPEED * status->delta;
    }

  if(status->mouse_state.button & SDL_BUTTON(1) &&
     (pow(status->mouse_state.y - cell_stage->player.y, 2) + pow(status->mouse_state.x - cell_stage->player.x, 2) > 8 * 8))
    {
      double angl;

      angl = atan2(status->mouse_state.y - cell_stage->player.y, -(status->mouse_state.x - cell_stage->player.x));

      cell_stage->player.xv -= cos(angl) * PLAYER_SPEED * status->delta;
      cell_stage->player.yv += sin(angl) * PLAYER_SPEED * status->delta;
    }
  
  if(rand() % 64 == 0)
    add_object_to_world(&(cell_stage->world),
			new_object(OBJECT_FOOD,
				   rand() % status->screen_width, rand() % status->screen_height,
				   ((rand() % 128) / 128.) * OBJECT_SPEED - OBJECT_SPEED * .5, ((rand() % 128) / 128.) * OBJECT_SPEED - OBJECT_SPEED * .5));

  update_world(&(cell_stage->world), &(cell_stage->player), status);
  
  if(status->keydown == SDLK_F2)
    cell_stage->editor = 1;

  return ERROR_NONE;
}

error_code_t stage_cell_draw(stage_base_t * self, stage_draw_info_t * info)
{
  stage_cell_t * cell_stage = (stage_cell_t *)self;

  if(cell_stage->editor)
    {
      draw_creature_editor(&(cell_stage->editor_data), info);

      return ERROR_NONE;
    }

  draw_world(&(cell_stage->world), info);

  draw_creature_model(info, &(cell_stage->skeleton),
		      cell_stage->player.x,
		      cell_stage->player.y,
		      atan2(-cell_stage->player.yv, -cell_stage->player.xv),
		      (pow(cell_stage->player.xv, 2) + pow(cell_stage->player.yv, 2) > .25 * .25) ? ANIMATION_SWIM : 0);

  if(info->debug)
    font_write_color(info->font, cell_stage->player.x, cell_stage->player.y, 16, 16, "Player", 0, 0, 0);
  
  return ERROR_NONE;
}

error_code_t stage_cell_free(stage_base_t * self)
{
  stage_cell_t * cell_stage = (stage_cell_t *)self;

  free(cell_stage->world.objects);
  free(cell_stage);

  return ERROR_NONE;
}

error_code_t stage_cell_init(stage_base_t ** stage)
{
  int i;
  stage_cell_t * cell_stage = malloc(sizeof(stage_cell_t));

  srand(time(NULL));

  cell_stage->player.x = 64;
  cell_stage->player.y = 64;

  cell_stage->skeleton.skeleton[0] = .5;
  cell_stage->skeleton.skeleton[1] = 1;
  for(i = 2; i < SKELETON_LEN; i++)
    cell_stage->skeleton.skeleton[i] = (1. / i) * 2;

  memset(cell_stage->skeleton.additions, 0, sizeof(creature_addition_t) * ADDITION_COUNT);

  cell_stage->base.update = &stage_cell_update;
  cell_stage->base.draw = &stage_cell_draw;
  cell_stage->base.free = &stage_cell_free;

  cell_stage->editor_data = init_creature_editor(&(cell_stage->skeleton));
  cell_stage->editor = 1;

  cell_stage->world.object_count = 64;
  cell_stage->world.objects = malloc(sizeof(object_base_t) * cell_stage->world.object_count);
  memset(cell_stage->world.objects, 0, sizeof(object_base_t) * cell_stage->world.object_count);

  *stage = (stage_base_t *)cell_stage;

  return ERROR_NONE;
}
