#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

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
  draw_player(&(cell_stage->player));
  
  return ERROR_NONE;
}

error_code_t stage_cell_free(stage_base_t * self)
{
  free(self);

  return ERROR_NONE;
}

error_code_t stage_cell_init(stage_base_t ** stage)
{
  stage_cell_t * cell_stage = malloc(sizeof(stage_cell_t));

  cell_stage->player.x = 0;
  cell_stage->player.y = 0;

  cell_stage->base.update = &stage_cell_update;
  cell_stage->base.draw = &stage_cell_draw;
  cell_stage->base.free = &stage_cell_free;

  *stage = (stage_base_t *)cell_stage;

  return ERROR_NONE;
}
