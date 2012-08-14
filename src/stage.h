#ifndef STAGE_H
#define STAGE_H

#ifndef PI
#define PI 3.14159265358979
#endif 

#define SKELETON_LEN 10

/* Creature model/skeleton */
typedef struct creature_model
  {
    double skeleton[SKELETON_LEN];
  } creature_model_t;

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
    OBJECT_AI
  } object_type_t;

/* Not yet used */
typedef struct object_base
{
  object_type_t type;
  double x;
  double y;
} object_base_t;

/* player position and speed */
typedef struct player_base
{
  double x, xv;
  double y, yv;
} player_base_t;

/* Not yet used */
typedef struct world_base
{
  Uint32 object_count;
  object_base_t * objects;
} world_base_t;

typedef struct stage_update_info
{
  Uint32 delta;
  Uint8 * keystate;
} stage_update_info_t;

typedef struct stage_base
{
  stage_type_t type;

  error_code_t (*update)(struct stage_base * self, stage_update_info_t * state);
  error_code_t (*draw)(struct stage_base * self);
  error_code_t (*free)(struct stage_base * self);
} stage_base_t;

error_code_t init_player(player_base_t ** player, double x, double y);
error_code_t init_creature_model(creature_model_t ** model);

void draw_creature_model(creature_model_t * model, double x, double y, double rot);
void draw_player(player_base_t * player);
void draw_object(object_base_t * object);

void free_creature_model(creature_model_t * model);

#endif
