#pragma once

#include "vid.h"

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
  UI_THING_COLUMNS,
  UI_THING_ROWS,
} UI_ThingType;

typedef enum
{
  UI_INPUT_PASSWORD = 1 << 0,
  UI_INPUT_LOCKED = 1 << 1,

  UI_WINDOW_NO_EXIT_BUTTON = 1 << 0,
  UI_WINDOW_NO_HIDE_BUTTON = 1 << 1,
  UI_WINDOW_NO_RESIZE = 1 << 2,
} UI_Flags;

struct UI_Thing;

typedef struct
{
  /** 0 to 1. For 1D, Rows or Columns. */
  float weight;
  /** The thing encapsulated in the grid */
  struct UI_Thing* thing;
} UI_Cell;

typedef struct
{
  struct UI_Thing* child;
  const char* title;
  int size[2];
  int pos[2];
} UI_WindowThing;

typedef struct
{
  char* data;
  const char* hint;
  int maxSize;
} UI_InputThing;

typedef struct UI_Thing
{
  UI_ThingType type;
  
  /** If freed, should clear itself out of its parent */
  struct UI_Thing* parent;
  const char* name;
  int flags;
  
  union
  {
    UI_WindowThing window;
    UI_InputThing input;    

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

    struct
    {
      UI_Cell* cells;
      int size;
    } xgrid, ygrid;

    struct
    {
      UI_Cell* cells;
      int size[2];
    } grid;
  };
} UI_Thing;

/** For internal use */
struct UI_ThingList_;
typedef struct
{
  struct UI_ThingList_* things;
  VID_Image* img;
} UI_App;

extern VID_Color UI_shades[UI_SHADES_N];

/** `img` is not freed by the app. */
bool UI_InitApp(UI_App* app, VID_Image* img);
void UI_FreeApp(UI_App* app);
void UI_DrawApp(UI_App* app);
UI_Thing* UI_AddWindow(UI_App* app, UI_Thing* parent, int w, int h);

void UI_DrawThing(UI_App* app, UI_Thing* thing, int fromX, int fromY, int toX, int toY);

void UI_PipeVidEvent(UI_App* app, VID_Event* e);
