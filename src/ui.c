#include "ui.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

VID_Color UI_shades[UI_SHADES_N] = {
  {60, 61, 20, 0},
  {105, 107, 30, 0},
  {166, 168, 49, 0},
  {225, 228, 120, 0},
  {255, 255, 200, 0}
};

void UI_DrawBox(VID_Image* img, int fromX, int fromY, int toX, int toY, int baseShadeI, bool light)
{
  int shadeSign = light ? 1 : -1;
  VID_Color* baseShade = UI_shades + baseShadeI;
  VID_Color* topShade = UI_shades + MIN(UI_SHADES_N - 1, baseShadeI + shadeSign);
  VID_Color* botShade = UI_shades + MAX(0, baseShadeI - shadeSign);

  if (toY < 1 || toX < 1)
  {
    return;
  }

  #pragma omp simd
  for (int i = fromX + 1; i < toX - 1; ++i)
  {
    img->p[i + fromY * img->w] = *topShade;
    img->p[i + (toY - 1) * img->w] = *botShade;
  }

  #pragma omp simd
  for (int y = fromY + 1; y < toY - 1; ++y)
  {
    #pragma omp simd
    for (int i = fromX; i < toX; ++i)
      img->p[i + y * img->w] = *baseShade;

    img->p[fromX + y * img->w] = *topShade;
    img->p[toX + y * img->w] = *botShade;
  } 
}

bool UI_InitApp(UI_App* app, VID_Image* img)
{
  app->img = img; 

  

  return true;
}

