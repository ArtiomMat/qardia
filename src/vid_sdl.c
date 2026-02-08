#include "vid.h"
#include "con.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

#include <stdlib.h>

struct VID_OsWindow
{
  SDL_Window* w;
  SDL_Renderer* r;
  SDL_Surface* ws;
  SDL_Surface* s;
};

bool VID_Init(void)
{
  return SDL_Init(SDL_INIT_VIDEO);
}

void VID_Free(void)
{
  SDL_Quit();
}

bool VID_InitWindow(VID_Window *window, const char *title, int width, int height)
{
  window->os = malloc(sizeof (VID_OsWindow));
  *window->os = (VID_OsWindow){0};

  if (!SDL_CreateWindowAndRenderer(title, width, height, 0, &window->os->w, &window->os->r))
  {
    CON_ERROR("VID_InitWindow(): Failed to create SDL window+renderer for '%s'", title);
    goto FAIL_;
  }

  window->os->ws = SDL_GetWindowSurface(window->os->w);
  if (!window->os->ws)
  {
    CON_ERROR("VID_InitWindow(): Failed to get SDL surface of '%s'", title);
    goto FAIL_;
  }
  
  window->os->s = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_XBGR8888);
  if (!window->os->s)
  {
    CON_ERROR("VID_InitWindow(): Failed to get SDL surface of '%s'", title);
    goto FAIL_;
  }

  return true;
FAIL_:
  VID_FreeWindow(window);
  return false;
}

void VID_FreeWindow(VID_Window *window)
{
  if (window->os)
  {
    if (window->os->w)
    {
      SDL_DestroyWindow(window->os->w);
    }
    if (window->os->r)
    {
      SDL_DestroyRenderer(window->os->r);
    }
    if (window->os->s)
    {
      SDL_DestroySurface(window->os->s);
    }
    free(window->os);
  }
}

VID_Color* VID_GetPixels(VID_Window *window)
{
  return window->os->s->pixels;
}

bool VID_PutPixels(VID_Window *window)
{
  return SDL_BlitSurface(window->os->s, NULL, window->os->ws, NULL);
}

void VID_Refresh(VID_Window *window)
{
  SDL_UpdateWindowSurface(window->os->w);
}

VID_ScanCode TranslateSdl3ScanCode(SDL_Scancode sdlCode)
{
    switch (sdlCode)
    {
        // Letters
        case SDL_SCANCODE_A: return VID_KEY_A;
        case SDL_SCANCODE_B: return VID_KEY_B;
        case SDL_SCANCODE_C: return VID_KEY_C;
        case SDL_SCANCODE_D: return VID_KEY_D;
        case SDL_SCANCODE_E: return VID_KEY_E;
        case SDL_SCANCODE_F: return VID_KEY_F;
        case SDL_SCANCODE_G: return VID_KEY_G;
        case SDL_SCANCODE_H: return VID_KEY_H;
        case SDL_SCANCODE_I: return VID_KEY_I;
        case SDL_SCANCODE_J: return VID_KEY_J;
        case SDL_SCANCODE_K: return VID_KEY_K;
        case SDL_SCANCODE_L: return VID_KEY_L;
        case SDL_SCANCODE_M: return VID_KEY_M;
        case SDL_SCANCODE_N: return VID_KEY_N;
        case SDL_SCANCODE_O: return VID_KEY_O;
        case SDL_SCANCODE_P: return VID_KEY_P;
        case SDL_SCANCODE_Q: return VID_KEY_Q;
        case SDL_SCANCODE_R: return VID_KEY_R;
        case SDL_SCANCODE_S: return VID_KEY_S;
        case SDL_SCANCODE_T: return VID_KEY_T;
        case SDL_SCANCODE_U: return VID_KEY_U;
        case SDL_SCANCODE_V: return VID_KEY_V;
        case SDL_SCANCODE_W: return VID_KEY_W;
        case SDL_SCANCODE_X: return VID_KEY_X;
        case SDL_SCANCODE_Y: return VID_KEY_Y;
        case SDL_SCANCODE_Z: return VID_KEY_Z;

        // Numbers
        case SDL_SCANCODE_1: return VID_KEY_1;
        case SDL_SCANCODE_2: return VID_KEY_2;
        case SDL_SCANCODE_3: return VID_KEY_3;
        case SDL_SCANCODE_4: return VID_KEY_4;
        case SDL_SCANCODE_5: return VID_KEY_5;
        case SDL_SCANCODE_6: return VID_KEY_6;
        case SDL_SCANCODE_7: return VID_KEY_7;
        case SDL_SCANCODE_8: return VID_KEY_8;
        case SDL_SCANCODE_9: return VID_KEY_9;
        case SDL_SCANCODE_0: return VID_KEY_0;

        // Control Keys
        case SDL_SCANCODE_RETURN:    return VID_KEY_RETURN;
        case SDL_SCANCODE_ESCAPE:    return VID_KEY_ESCAPE;
        case SDL_SCANCODE_BACKSPACE: return VID_KEY_BACKSPACE;
        case SDL_SCANCODE_TAB:       return VID_KEY_TAB;
        case SDL_SCANCODE_SPACE:     return VID_KEY_SPACE;
        case SDL_SCANCODE_CAPSLOCK:  return VID_KEY_CAPSLOCK;

        // Function Keys
        case SDL_SCANCODE_F1:  return VID_KEY_F1;
        case SDL_SCANCODE_F2:  return VID_KEY_F2;
        case SDL_SCANCODE_F3:  return VID_KEY_F3;
        case SDL_SCANCODE_F4:  return VID_KEY_F4;
        case SDL_SCANCODE_F5:  return VID_KEY_F5;
        case SDL_SCANCODE_F6:  return VID_KEY_F6;
        case SDL_SCANCODE_F7:  return VID_KEY_F7;
        case SDL_SCANCODE_F8:  return VID_KEY_F8;
        case SDL_SCANCODE_F9:  return VID_KEY_F9;
        case SDL_SCANCODE_F10: return VID_KEY_F10;
        case SDL_SCANCODE_F11: return VID_KEY_F11;
        case SDL_SCANCODE_F12: return VID_KEY_F12;

        // Navigation & Commands
        case SDL_SCANCODE_PRINTSCREEN: return VID_KEY_PRINTSCREEN;
        case SDL_SCANCODE_SCROLLLOCK:  return VID_KEY_SCROLLLOCK;
        case SDL_SCANCODE_PAUSE:       return VID_KEY_PAUSE;
        case SDL_SCANCODE_INSERT:      return VID_KEY_INSERT;
        case SDL_SCANCODE_HOME:        return VID_KEY_HOME;
        case SDL_SCANCODE_PAGEUP:      return VID_KEY_PAGEUP;
        case SDL_SCANCODE_DELETE:      return VID_KEY_DELETE;
        case SDL_SCANCODE_END:         return VID_KEY_END;
        case SDL_SCANCODE_PAGEDOWN:    return VID_KEY_PAGEDOWN;
        case SDL_SCANCODE_RIGHT:       return VID_KEY_RIGHT;
        case SDL_SCANCODE_LEFT:        return VID_KEY_LEFT;
        case SDL_SCANCODE_DOWN:        return VID_KEY_DOWN;
        case SDL_SCANCODE_UP:          return VID_KEY_UP;

        // Punctuation
        case SDL_SCANCODE_GRAVE:      return VID_KEY_GRAVE;
        case SDL_SCANCODE_MINUS:      return VID_KEY_MINUS;
        case SDL_SCANCODE_EQUALS:     return VID_KEY_EQUALS;
        case SDL_SCANCODE_LEFTBRACKET:  return VID_KEY_LBRACKET;
        case SDL_SCANCODE_RIGHTBRACKET: return VID_KEY_RBRACKET;
        case SDL_SCANCODE_BACKSLASH:    return VID_KEY_BACKSLASH;
        case SDL_SCANCODE_SEMICOLON:    return VID_KEY_SEMICOLON;
        case SDL_SCANCODE_APOSTROPHE:   return VID_KEY_APOSTROPHE;
        case SDL_SCANCODE_COMMA:        return VID_KEY_COMMA;
        case SDL_SCANCODE_PERIOD:       return VID_KEY_PERIOD;
        case SDL_SCANCODE_SLASH:        return VID_KEY_SLASH;

        // Modifiers
        case SDL_SCANCODE_LCTRL:  return VID_KEY_LCTRL;
        case SDL_SCANCODE_LSHIFT: return VID_KEY_LSHIFT;
        case SDL_SCANCODE_LALT:   return VID_KEY_LALT;
        case SDL_SCANCODE_LGUI:   return VID_KEY_LGUI;
        case SDL_SCANCODE_RCTRL:  return VID_KEY_RCTRL;
        case SDL_SCANCODE_RSHIFT: return VID_KEY_RSHIFT;
        case SDL_SCANCODE_RALT:   return VID_KEY_RALT;
        case SDL_SCANCODE_RGUI:   return VID_KEY_RGUI;

        default: return VID_KEY_UNKNOWN;
    }
}

VID_ScanCode TranslateSdl3MouseButton(uint8_t button)
{
    switch (button)
    {
        case SDL_BUTTON_LEFT:   return VID_MOUSE_LEFT;
        case SDL_BUTTON_RIGHT:  return VID_MOUSE_RIGHT;
        case SDL_BUTTON_MIDDLE: return VID_MOUSE_MIDDLE;
        case SDL_BUTTON_X1:     return VID_MOUSE_X1;
        case SDL_BUTTON_X2:     return VID_MOUSE_X2;
        default:                return VID_KEY_UNKNOWN;
    }
}

bool VID_PollEvent(VID_Window *window, VID_Event *e)
{
  SDL_Event sdlEvent;
  if (!SDL_PollEvent(&sdlEvent))
  {
    return false;
  }

  switch (sdlEvent.type)
  {
  case SDL_EVENT_QUIT:
    e->type = VID_EVENT_EXIT;
    break;

  case SDL_EVENT_KEY_DOWN:
  case SDL_EVENT_KEY_UP:
    e->type = sdlEvent.type == SDL_EVENT_KEY_DOWN ? VID_EVENT_DOWN : VID_EVENT_UP;
    // Up and down are both the same so don't care
    e->data.down.code = TranslateSdl3ScanCode(sdlEvent.key.scancode);
    break;

  case SDL_EVENT_MOUSE_BUTTON_DOWN:
  case SDL_EVENT_MOUSE_BUTTON_UP:
    e->type = (sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) ? VID_EVENT_DOWN : VID_EVENT_UP;
    // Up and down are both the same so don't care
    e->data.down.code = TranslateSdl3MouseButton(sdlEvent.button.button);
    break;

  case SDL_EVENT_MOUSE_MOTION:
    e->type = VID_EVENT_MOVE;
    e->data.move.x  = (int)sdlEvent.motion.x;
    e->data.move.y  = (int)sdlEvent.motion.y;
    e->data.move.dx = (int)sdlEvent.motion.xrel;
    e->data.move.dy = (int)sdlEvent.motion.yrel;
    break;
  
  case SDL_EVENT_MOUSE_WHEEL:
    e->type = VID_EVENT_WHEEL;
    // SDL3 uses 'y' for vertical scroll with a weird ahh flag for sign. 
    if (sdlEvent.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
    {
      e->data.wheel.delta = -sdlEvent.wheel.y;
    }
    else
    {
      e->data.wheel.delta = sdlEvent.wheel.y;
    }
    break;

  default:
    break;
  }

  return true;
}

