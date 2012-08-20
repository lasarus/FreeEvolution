#ifndef CREATURE_MODEL_H
#define CREATURE_MODEL_H

#define SKELETON_LEN 15
#define ADDITION_COUNT 20 

enum
  {
    ANIMATION_SWIM_SLOW = 1 << 0,
    ANIMATION_SWIM_FAST = 1 << 1
  };

typedef enum addition_type
  {
    ADDITION_NONE = 0,
    ADDITION_EYE = 1,
    ADDITION_MOUTH = 2,
    ADDITION_SPIKE = 3
  } addition_type_t;

typedef struct creature_addition
{
  addition_type_t type;
  int pos;
} creature_addition_t;

/* Creature model/skeleton */
typedef struct creature_model
  {
    double skeleton[SKELETON_LEN];
    creature_addition_t additions[ADDITION_COUNT];
  } creature_model_t;

void draw_eye(double scale);
void draw_spike(double scale, int inverted);

void draw_creature_model(stage_draw_info_t * draw_info, creature_model_t * model, double x, double y, double rot, Uint32 animation);
void draw_editor_creature_model(stage_draw_info_t * draw_info, creature_model_t * model, double x, double y, double rot, int selected, Uint32 animation);

void creature_add_addition(creature_model_t * model, addition_type_t type, int pos);
void creature_remove_addition(creature_model_t * model, int pos);
int creature_addition_at_pos(creature_model_t * model, int pos);

#endif
