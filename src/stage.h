#ifndef STAGE_H
#define STAGE_H

typedef enum stage_type
  {
    STAGE_NULL = 0,
    STAGE_CELL
  } stage_type_t;

typedef enum object_type
  {
    OBJECT_NULL = 0,
    OBJECT_AI
  } object_type_t;

typedef struct object_base
{
  object_type_t type;
  double x;
  double y;
} object_base_t;

typedef struct player_base
{
  double x, xv;
  double y, yv;
} player_base_t;

typedef struct world_base
{
  Uint32 object_count;
  object_base_t * objects;
} world_base_t;

typedef struct stage_base
{
  stage_type_t type;

  error_code_t (*update)(stage_base_t * self, Uint32 delta);
  error_code_t (*draw)(stage_base_t * self);
  error_code_t (*free)(stage_base_t * self);
} stage_base_t;

void draw_player(player_base_t * player);
void draw_object(object_base_t * object);

#endif
