#pragma once

typedef union
{
  struct
  {
    float x, y, z;
  };
  float a[3];
} float3;

typedef struct
{
  struct
  {
    float x, y, z, w;
  };
  float a[4];
} float4;

