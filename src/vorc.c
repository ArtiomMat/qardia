#include "vorc.h"

void VORC_InitContext(VORC_Context* ctx, VID_Image* image)
{
  ctx->img = *image;
}

void VORC_BindCamera(VORC_Context* ctx, VORC_Camera* camera)
{
  ctx->cam = *camera;
}

void VORC_BindVolume(VORC_Context* ctx, VORC_Volume* volume)
{
  ctx->vol = volume;
}

