/** VOlume Ray Casting module. */

#pragma once

#include "m.h"
#include "vid.h"
#include "vid_base.h"

typedef struct
{
  float3 pos;
  float4 rot;
  float fov;
} VORC_Camera;

typedef struct
{
  int size[3];
  float data[];
} VORC_Volume;

typedef struct
{
  VID_Image img;
  VORC_Camera cam;
  VORC_Volume* vol;
} VORC_Context;

VORC_Volume* VORC_InitVolume(int width, int height, int depth);

/**
 * `image` is not freed by `VORC`.
 */
void VORC_InitContext(VORC_Context* ctx, VID_Image* image);
void VORC_BindCamera(VORC_Context* ctx, VORC_Camera* camera);
void VORC_BindVolume(VORC_Context* ctx, VORC_Volume* volume);

void VORC_Render(VORC_Context* ctx);

