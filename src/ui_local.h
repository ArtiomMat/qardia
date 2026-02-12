#pragma once

#include "ui.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define WINDOW_BORDER_SIZE 5
#define WINDOW_TITLE_SIZE 12

typedef struct UI_ThingList_
{
  struct UI_ThingList_* next;
  struct UI_ThingList_* prev;
  UI_Thing thing;
} UI_ThingList_;
