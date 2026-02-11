/** Basic. */

#pragma once

#include <stdint.h>

/**
 * All Qardia pixels are in XBGR format.
 */
typedef struct
{
  uint8_t r, g, b, x;
} VID_Color;

typedef struct
{
  VID_Color* p;
  union
  {
    struct
    {
      int w, h;
    };
    int size[2];
  };
} VID_Image;
