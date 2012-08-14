#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "error_codes.h"
#include "stage.h"
#include "stage_cell.h"

#define PLAYER_SPEED .05
#define OBJECT_SPEED .05

error_code_t stage_cell_update(stage_base_t * self, stage_update_info_t * status)
{
  Uint8 * keystate = status->keystate;
  stage_cell_t * cell_stage = (stage_cell_t *)self;
  
  cell_stage->player.x += cell_stage->player.xv * status->delta;
  cell_stage->player.y += cell_stage->player.yv * status->delta;

  cell_stage->player.xv /= 1.1;
  cell_stage->player.yv /= 1.1;

  if(keystate[SDLK_w])
    {
      cell_stage->player.yv += -1 * PLAYER_SPEED;
    }
  if(keystate[SDLK_s])
    {
      cell_stage->player.yv += 1 * PLAYER_SPEED;
    }
  if(keystate[SDLK_a])
    {
      cell_stage->player.xv += -1 * PLAYER_SPEED;
    }
  if(keystate[SDLK_d])
    {
      cell_stage->player.xv += 1 * PLAYER_SPEED;
    }
  
  if(rand() % 128 == 0)
    add_object_to_world(&(cell_stage->world),
			new_object(OBJECT_FOOD,
				   rand() % status->screen_width, rand() % status->screen_height,
				   ((rand() % 128) / 128.) * OBJECT_SPEED - OBJECT_SPEED * .5, ((rand() % 128) / 128.) * OBJECT_SPEED - OBJECT_SPEED * .5));

  update_world(&(cell_stage->world), status);
  
  return ERROR_NONE;
}

error_code_t stage_cell_draw(stage_base_t * self)
{
  stage_cell_t * cell_stage = (stage_cell_t *)self;
  /*draw_player(&(cell_stage->player));*/

  draw_creature_model(&(cell_stage->skeleton), cell_stage->player.x, cell_stage->player.y, atan2(-cell_stage->player.yv, -cell_stage->player.xv));
  draw_world(&(cell_stage->world));
  
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

  printf("time: %ui\n", (unsigned int)time(NULL));

  cell_stage->player.x = 64;
  cell_stage->player.y = 64;

  cell_stage->skeleton.skeleton[0] = 1;
  for(i = 1; i < SKELETON_LEN; i++)
    cell_stage->skeleton.skeleton[i] = cell_stage->skeleton.skeleton[i - 1] - (1. / SKELETON_LEN);

  cell_stage->base.update = &stage_cell_update;
  cell_stage->base.draw = &stage_cell_draw;
  cell_stage->base.free = &stage_cell_free;

  cell_stage->world.object_count = 64;
  cell_stage->world.objects = malloc(sizeof(object_base_t) * cell_stage->world.object_count);
  memset(cell_stage->world.objects, 0, sizeof(object_base_t) * cell_stage->world.object_count);

  *stage = (stage_base_t *)cell_stage;

  return ERROR_NONE;
}
