#ifndef STAGE_H
#define STAGE_H

#ifndef PI
#define PI 3.14159265358979
#endif 

#define SKELETON_LEN 15

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

typedef struct stage_update_info
{
  Uint32 delta;
  Uint32 time;
  Uint8 * keystate;

  int screen_width;
  int screen_height;

  struct
  {
    int x;
    int y;
    Uint8 button;
  } mouse_state;
} stage_update_info_t;

typedef struct stage_draw_info
{
  int debug;
  font_t font;
} stage_draw_info_t;

typedef struct stage_base
{
  stage_type_t type;

  error_code_t (*update)(struct stage_base * self, stage_update_info_t * state);
  error_code_t (*draw)(struct stage_base * self, stage_draw_info_t * info);
  error_code_t (*free)(struct stage_base * self);
} stage_base_t;

error_code_t init_player(player_base_t ** player, double x, double y);
error_code_t init_creature_model(creature_model_t ** model);

object_base_t new_object(object_type_t type, double x, double y, double xv, double yv);

error_code_t update_world(world_base_t * world, player_base_t * player, stage_update_info_t * status);
void draw_world(world_base_t * world, stage_draw_info_t * info);
void add_object_to_world(world_base_t * world, object_base_t object);

void draw_creature_model(creature_model_t * model, double x, double y, double rot);
void draw_player(player_base_t * player);
void draw_object(object_base_t * object);

void free_creature_model(creature_model_t * model);

#endif
