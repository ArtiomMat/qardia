#include "ui_local.h"

#include <stdlib.h>

VID_Color UI_shades[UI_SHADES_N] = {
  {60, 61, 20, 0},
  {105, 107, 30, 0},
  {166, 168, 49, 0},
  {225, 228, 120, 0},
  {255, 255, 200, 0}
};

bool UI_InitApp(UI_App* app, VID_Image* img)
{
  app->img = img;
  app->things = NULL;

  return true;
}

void UI_FreeApp(UI_App *app)
{
  for (UI_ThingList_* node = app->things; node; /* Inside */)
  {
    UI_ThingList_* next = node->next;
    free(node);
    node = next;
  }
}

UI_Thing* UI_AddThing()
{

}

