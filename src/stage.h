#ifndef STAGE_H
#define STAGE_H

#ifndef PI
#define PI 3.14159265358979
#endif 

/* Type of stage (not yet used) */
typedef enum stage_type
  {
    STAGE_NULL = 0,
    STAGE_CELL
  } stage_type_t;

/* Type of object */
typedef enum object_type
  {
    OBJECT_NULL = 0,
    OBJECT_FOOD,
    OBJECT_AI
  } object_type_t;

typedef struct object_base
{
  object_type_t type;
  double x, xv;
  double y, yv;
} object_base_t;

/* player position and speed */
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

  error_code_t (*update)(struct stage_base * self, stage_update_info_t * state);
  error_code_t (*draw)(struct stage_base * self, stage_draw_info_t * info);
  error_code_t (*free)(struct stage_base * self);
} stage_base_t;

error_code_t init_player(player_base_t ** player, double x, double y);

object_base_t new_object(object_type_t type, double x, double y, double xv, double yv);

error_code_t update_world(world_base_t * world, player_base_t * player, stage_update_info_t * status);
void draw_world(world_base_t * world, stage_draw_info_t * info);
void add_object_to_world(world_base_t * world, object_base_t object);

void draw_player(player_base_t * player);
void draw_object(object_base_t * object);

#endif
