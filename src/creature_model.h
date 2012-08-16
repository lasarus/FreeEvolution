#ifndef CREATURE_MODEL_H
#define CREATURE_MODEL_H

#define SKELETON_LEN 15
#define ADDITION_COUNT 20 

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

void draw_creature_model(creature_model_t * model, double x, double y, double rot);
void draw_editor_creature_model(creature_model_t * model, double x, double y, double rot, int selected);

void creature_add_addition(creature_model_t * model, addition_type_t type, int pos);
void creature_remove_addition(creature_model_t * model, int pos);

#endif
