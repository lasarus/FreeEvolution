#ifndef CREATURE_MODEL_H
#define CREATURE_MODEL_H

#define SKELETON_LEN 15

/* Creature model/skeleton */
typedef struct creature_model
  {
    int eyes;
    double skeleton[SKELETON_LEN];
  } creature_model_t;

void draw_creature_model(creature_model_t * model, double x, double y, double rot);
void draw_editor_creature_model(creature_model_t * model, double x, double y, double rot, int selected);

#endif
