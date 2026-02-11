#include "d2.h"

#include <stdlib.h>

void D2_Fill(VID_Image* img, VID_Color color)
{
    #pragma omp simd
    for (int i = 0; i < img->w * img->h; ++i)
    {
        img->p[i] = color;
    }
}

void D2_DrawLine(VID_Image* img, int fromX, int fromY, int toX, int toY)
{
    // Finding longer and shorter dimensions
    int ldim = abs(toY - fromY) > abs(toX - fromX) ? 1 : 0;
    int sdim = !ldim;

    float now[2] = {fromX, fromY};
    float to[2] = {toX, toY};

    // int slope = (now[sdim])

}
