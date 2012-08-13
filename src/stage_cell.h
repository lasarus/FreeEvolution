#ifndef STAGE_CELL_H
#define STAGE_CELL_H

typedef struct stage_cell
{
  struct stage_base base;

  player_base_t player;
  creature_model_t skeleton;
} stage_cell_t;

error_code_t stage_cell_init(stage_base_t ** stage);

#endif
