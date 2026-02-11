#if defined(__x86_64__) && !defined(VORC_NAIVE)

#include "vorc.h"

#include <math.h>

// TODO: This is the naive implementation.

/**
 * `x` and `y` are normalized ranges from `-1` to `1` where `0` is the center.
 *
 * Writes to the 
 */
static void GetRayStepSlope(float3* stepSlope, float fov, float stepSize, float x, float y)
{
  // fov * x or y gets us a respective finalized angle from -fov to +fov.
  // Applying the right trigonometic function yields slope for stepSize=1.
  // Multiplying the result by stepSize yields slope for real stepSize.

  stepSlope->z = stepSize * sinf(fov * x);
  stepSlope->x = stepSize * cosf(fov * x);
  stepSlope->y = stepSize * cosf(fov * y);
}

void VORC_Render(VORC_Context* ctx)
{
}

#endif // if defined(__x86_64__) && !defined(VORC_NAIVE)

