#include "nifti.h"
#include "con.h"
#include <stdio.h>

bool NIFTI_Open(NIFTI_File* file, const char* path)
{
  FILE* f = fopen(path, "rb");

  if (!f)
  {
    CON_ERROR("NIFTI_Open(): Can't open path '%s'!", path);
    goto FAIL_;
  }

  // file->header
  size_t readCount = fread(&file->header, sizeof (file->header), 1, f);
  if (!readCount)
  {
    CON_ERROR("NIFTI_Open(): Couldn't read the header of '%s', could read %zu headers(need 1)!", path, readCount);
    goto FAIL_;
  }
  // Check that the template is there
  if (file->header.magic[0] != 'n' || (file->header.magic[1] != '+' && file->header.magic[1] != 'i'))
  {
    file->header.magic[3] = 0; // Force null terminator for logging
    CON_ERROR("NIFTI_Open(): The magic of '%s' wasn't all that magical(%s)...", path, file->header.magic);
    goto FAIL_;
  }
  // Ensure that it's a version we support and set file->version
  if (file->header.magic[2] != '1')
  {
    CON_ERROR("NIFTI_Open(): The version of '%s' is unsupported(%c)...", path, file->header.magic[2]);
    goto FAIL_;
  }
  else
  {
    file->version = file->header.magic[2] - '0';
  }
  
  file->header.descrip[NIFTI_DESCRIP_SIZE - 1] = 0; // No buffer overflows today
  CON_INFO("NIFTI_Open(): Opened '%s', description: '%s'!", path, file->header.descrip);
  file->f = f;
  return true;

FAIL_:
  if (f)
  {
    fclose(f);
  }
  return false;
}

void NIFTI_Close(NIFTI_File* file)
{
  if (file->f)
  {
    fclose(file->f);
  }
}

