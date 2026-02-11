/** Basic 2D ops. */

#pragma once

#include "vid_base.h"

void D2_DrawLine(VID_Image* img, int fromX, int fromY, int toX, int toY);
void D2_Fill(VID_Image* img, VID_Color color);

static inline void D2_Set(VID_Image* img, int x, int y, VID_Color color)
{
    img->p[x + y * img->w] = color;
}

void D2_DrawLineOnY(VID_Image* img, int x, int length);
void D2_DrawLineOnX(VID_Image* img, int y, int length);

