#include "ui.h"
#include "ui_local.h"
#include "vid_base.h"

static void DrawBox(
    VID_Image* img,
    int fromX, int fromY,
    int toX, int toY,
    int baseShadeI,
    bool light
)
{
  int shadeSign = light ? 1 : -1;
  VID_Color* baseShade = UI_shades + baseShadeI;
  VID_Color* topShade = UI_shades + MIN(UI_SHADES_N - 1, baseShadeI + shadeSign);
  VID_Color* botShade = UI_shades + MAX(0, baseShadeI - shadeSign);

  // Prevent negative index
  if (toY < 1 || toX < 1 || fromX >= img->w - 1 || fromY >= img->h - 1)
  {
    return;
  }

  if (toY <= fromY || toX <= fromX)
  {
    return;
  }

  fromX = MIN(MAX(0, fromX), img->w);
  toX = MIN(MAX(0, toX), img->w);
  fromY = MIN(MAX(0, fromY), img->h);
  toY = MIN(MAX(0, toY), img->h);

  #pragma omp simd
  for (int y = fromY + 1; y < toY - 1; ++y)
  {
    #pragma omp simd
    for (int i = fromX; i < toX; ++i)
      img->p[i + y * img->w] = *baseShade;

    img->p[fromX + y * img->w] = *topShade;
    img->p[toX + y * img->w] = *botShade;
  }

  #pragma omp simd
  for (int i = fromX + 0; i < toX - 0; ++i)
  {
    // TODO: Add BORDER_WIDTH constant
    img->p[i + fromY * img->w] = *topShade;
    img->p[i + (toY - 1) * img->w] = *botShade;
  }
}

static void DrawWindow(VID_Image* img, UI_Thing* thing, int fromX, int fromY, int toX, int toY)
{
  UI_WindowThing* wnd = &thing->window;
  DrawBox(fromX, fromY, toX, toY, true);

  DrawBox(fromX + WINDOW_BORDER_SIZE, fromY + WINDOW_TITLE_SIZE, toX + WINDOW_BORDER_SIZE, toY + WINDOW_BORDER_SIZE, true);
}


void UI_DrawThing(UI_App* app, UI_Thing* thing, int fromX, int fromY, int toX, int toY)
{
  if (!thing)
  {
    return;
  }
  
  VID_Image* img = app->img;
  switch (thing->type)
  {
  case UI_THING_WINDOW:
    DrawWindow(img, thing, fromX, fromY, toX, toY);
    break;

  default:
    break;
  }
}

void UI_DrawApp(UI_App* app)
{
}
