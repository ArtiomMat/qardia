#pragma once

#include "m.h"
#include "vid.h"

typedef struct
{
  VID_Color* p;
  int w, h;
} VORC_Context;

typedef struct
{
  float3 pos;
  float4 rot;
  float fov;
} VORC_Camera;

typedef struct
{
  float* data;
  int size[3];
} VORC_Volume;

/**
 * `pixels` is not managed by VORC.
 */
void VORC_InitContext(VORC_Context* ctx, VID_Color* pixels, int width, int height);
void VORC_SetCamera(VORC_Context* ctx, VORC_Camera* camera);
void VORC_SetVolume(VORC_Context* ctx, VORC_Camera* camera);

