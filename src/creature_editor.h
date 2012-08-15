#ifndef CREATURE_EDITOR_H
#define CREATURE_EDITOR_H

typedef struct editor_data
{
  creature_model_t * creature;
} editor_data_t;

editor_data_t init_creature_editor(creature_model_t * creature);
void update_creature_editor(editor_data_t * data, stage_update_info_t * state);
void draw_creature_editor(editor_data_t * data, stage_draw_info_t * info);

#endif
