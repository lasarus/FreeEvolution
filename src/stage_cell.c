#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <math.h>

#include "error_codes.h"
#include "stage.h"
#include "stage_cell.h"

#define PLAYER_SPEED .1

error_code_t stage_cell_update(stage_base_t * self, Uint32 delta)
{
  stage_cell_t * cell_stage = (stage_cell_t *)self;
  
  cell_stage->player.x += PLAYER_SPEED * delta;
  cell_stage->player.y += PLAYER_SPEED * delta;
  
  return ERROR_NONE;
}

error_code_t stage_cell_draw(stage_base_t * self)
{
  stage_cell_t * cell_stage = (stage_cell_t *)self;
  /*draw_player(&(cell_stage->player));*/

  draw_creature_model(&(cell_stage->skeleton), cell_stage->player.x, cell_stage->player.y, PI / 3);
  
  return ERROR_NONE;
}

error_code_t stage_cell_free(stage_base_t * self)
{
  free(self);

  return ERROR_NONE;
}

error_code_t stage_cell_init(stage_base_t ** stage)
{
  int i;
  stage_cell_t * cell_stage = malloc(sizeof(stage_cell_t));

  cell_stage->player.x = 0;
  cell_stage->player.y = 0;
  
  for(i = 0; i < SKELETON_LEN; i++)
    cell_stage->skeleton.skeleton[i] = (SKELETON_LEN - i) * .1;

  cell_stage->base.update = &stage_cell_update;
  cell_stage->base.draw = &stage_cell_draw;
  cell_stage->base.free = &stage_cell_free;

  *stage = (stage_base_t *)cell_stage;

  return ERROR_NONE;
}
