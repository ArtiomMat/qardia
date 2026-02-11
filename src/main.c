#include "con.h"
#include "d2.h"
#include "nifti.h"
#include "vid.h"
#include "vid_base.h"
#include "ui.h"

int main()
{
  CON_INFO("WELCOME TO QARDIA!");

  NIFTI_File nii;
  NIFTI_Open(&nii, "data/spm152.nii");

  VID_Init();

  VID_Window window;
  VID_InitWindow(&window, "INVINCIBLE", 500, 500);
  
  // D2_Fill(&window.img, (VID_Color){0, 160, 128, 32});
  UI_DrawBox(&window.img, 10, 10, 60, 40, 1, false);

  VID_BlitPixels(&window);

  VID_Event e;
  while(1)
  {
    VID_Refresh(&window);

    while (VID_PollEvent(&window, &e))
    {
      switch (e.type)
      {
      case VID_EVENT_EXIT:
        return 0;

      case VID_EVENT_DOWN:
        CON_INFO("%d", e.data.down.code);
        break;
      case VID_EVENT_UP:
        CON_INFO("UP %d", e.data.down.code);
        break;

      default:
        break;
      }
    }
  }

  VID_Free();

  NIFTI_Close(&nii);

  return 0;
}
