#pragma once

#include "vid_base.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct VID_OsWindow VID_OsWindow;

typedef struct
{
  VID_OsWindow* os;
  VID_Image img;
} VID_Window;

typedef enum
{
  VID_EVENT_DOWN,
  VID_EVENT_UP,
  VID_EVENT_MOVE,
  VID_EVENT_WHEEL,
  VID_EVENT_EXIT,
} VID_EventType;

typedef enum
{
  VID_KEY_UNKNOWN = 0,

  // --- Letters ---
  VID_KEY_A, VID_KEY_B, VID_KEY_C, VID_KEY_D,
  VID_KEY_E, VID_KEY_F, VID_KEY_G, VID_KEY_H,
  VID_KEY_I, VID_KEY_J, VID_KEY_K, VID_KEY_L,
  VID_KEY_M, VID_KEY_N, VID_KEY_O, VID_KEY_P,
  VID_KEY_Q, VID_KEY_R, VID_KEY_S, VID_KEY_T,
  VID_KEY_U, VID_KEY_V, VID_KEY_W, VID_KEY_X,
  VID_KEY_Y, VID_KEY_Z,

  // --- Numbers ---
  VID_KEY_1, VID_KEY_2, VID_KEY_3, VID_KEY_4,
  VID_KEY_5, VID_KEY_6, VID_KEY_7, VID_KEY_8,
  VID_KEY_9, VID_KEY_0,

  // --- Control Keys ---
  VID_KEY_RETURN,
  VID_KEY_ESCAPE,
  VID_KEY_BACKSPACE,
  VID_KEY_TAB,
  VID_KEY_SPACE,
  VID_KEY_CAPSLOCK,

  // --- Function Keys ---
  VID_KEY_F1, VID_KEY_F2, VID_KEY_F3, VID_KEY_F4,
  VID_KEY_F5, VID_KEY_F6, VID_KEY_F7, VID_KEY_F8,
  VID_KEY_F9, VID_KEY_F10, VID_KEY_F11, VID_KEY_F12,

  // --- Navigation & Commands ---
  VID_KEY_PRINTSCREEN,
  VID_KEY_SCROLLLOCK,
  VID_KEY_PAUSE,
  VID_KEY_INSERT,
  VID_KEY_HOME,
  VID_KEY_PAGEUP,
  VID_KEY_DELETE,
  VID_KEY_END,
  VID_KEY_PAGEDOWN,
  VID_KEY_RIGHT,
  VID_KEY_LEFT,
  VID_KEY_DOWN,
  VID_KEY_UP,

  // --- Punctuation ---
  VID_KEY_GRAVE,          // `
  VID_KEY_MINUS,          // -
  VID_KEY_EQUALS,         // =
  VID_KEY_LBRACKET,       // [
  VID_KEY_RBRACKET,       // ]
  VID_KEY_BACKSLASH,      // back-slash 
  VID_KEY_SEMICOLON,      // ;
  VID_KEY_APOSTROPHE,     // '
  VID_KEY_COMMA,          // ,
  VID_KEY_PERIOD,         // .
  VID_KEY_SLASH,          // /

  // --- Modifiers ---
  VID_KEY_LCTRL,
  VID_KEY_LSHIFT,
  VID_KEY_LALT,
  VID_KEY_LGUI,           // Windows/Command key
  VID_KEY_RCTRL,
  VID_KEY_RSHIFT,
  VID_KEY_RALT,
  VID_KEY_RGUI,

  // --- Mouse Buttons ---
  VID_MOUSE_LEFT,
  VID_MOUSE_RIGHT,
  VID_MOUSE_MIDDLE,
  VID_MOUSE_X1,
  VID_MOUSE_X2,

  VID_KEY_NUM
} VID_ScanCode;

typedef struct
{
  VID_EventType type;
  union 
  {
    struct {
      VID_ScanCode code;
    } up, down;
    
    struct {
      int x, y;
      /**
       * Delta relative to previous event.
       */
      int dx, dy;
    } move;

    struct {
      /**
       * Scroll amount (float handles precision wheels)
       */
      float delta;
    } wheel;
  } data;
} VID_Event;

bool VID_Init(void);
void VID_Free(void);

bool VID_InitWindow(VID_Window* window, const char* title, int width, int height);
void VID_FreeWindow(VID_Window* window);
bool VID_BlitPixels(VID_Window* window);
void VID_Refresh(VID_Window* window);

bool VID_PollEvent(VID_Window* window, VID_Event* e);

