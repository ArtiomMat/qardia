#include "con.h"
#include "nifti.h"
#include "vid.h"
#include <string.h>

int main()
{
  CON_INFO("WELCOME TO QARDIA!");

  NIFTI_File nii;
  NIFTI_Open(&nii, "data/spm152.nii");

  VID_Init();

  VID_Window window;
  VID_InitWindow(&window, "INVINCIBLE", 500, 500);
  VID_Color pixels[500 * 500] = {0, 0, 0, 0, 0, 255};

  memcpy(VID_GetPixels(&window), pixels, 500 * 500 * 4);
  VID_PutPixels(&window);

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
      }
    }
  }

  VID_Free();

  NIFTI_Close(&nii);

  return 0;
}
