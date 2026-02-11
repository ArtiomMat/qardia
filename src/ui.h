#pragma once

#include "vid_base.h"

#include <stdbool.h>

#define UI_SHADES_N 5

typedef enum
{
  /** Simply a linked list of things. Used internally. */
  UI_THING_LINKED_LIST_,

  UI_THING_WINDOW,
  
  UI_THING_BUTTON,
  UI_THING_TICKBOX,
  UI_THING_DROPDOWN,
  UI_THING_SLIDER,

  UI_THING_IMAGE,
  
  UI_THING_TEXT,
  UI_THING_INPUT,
  
  UI_THING_GRID,
  UI_THING_YGRID,
  UI_THING_XGRID,
} UI_ThingType;

typedef enum
{
  UI_INPUT_PASSWORD = 1 << 0,
  UI_INPUT_LOCKED = 1 << 1,

  UI_WINDOW_NO_EXIT_BUTTON = 1 << 0,
  UI_WINDOW_NO_HIDE_BUTTON = 1 << 1,
  UI_WINDOW_NO_RESIZE = 1 << 2,
} UI_Flags;

typedef struct UI_Thing
{
  UI_ThingType type;
  
  /** If freed, should clear itself out of its parent */
  struct UI_Thing* parent;
  const char* name;
  int flags;
  
  union
  {
    struct
    {
      struct UI_Thing* child;
      const char* title;
      int size[2];
    } window;
    
    struct
    {
      char* data;
      const char* hint;
      int maxSize;
    } input;
    
    struct
    {
      const char* data;
    } text;

    struct
    {
      /** E.g. a text thing. */
      struct UI_Thing* child;
      bool bTicked;
    } tickbox;
  };
} UI_Thing;

typedef struct
{
  UI_Thing* things;
  VID_Image* img;
} UI_App;

extern VID_Color UI_shades[UI_SHADES_N];

/** `img` is not freed by the app. */
bool UI_InitApp(UI_App* app, VID_Image* img);
void UI_FreeApp(UI_App* app);

void UI_DrawBox(VID_Image* img, int fromX, int fromY, int toX, int toY, int baseShadeI, bool light);

