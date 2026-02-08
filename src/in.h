#pragma once

typedef enum {
  IN_EVENT_DOWN,
  IN_EVENT_UP,
} IN_EventType;

typedef struct
{
  int type;
} IN_Event;
