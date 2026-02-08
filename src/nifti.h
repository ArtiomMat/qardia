#pragma once

#include <stdbool.h>
#include <stdio.h>

#define NIFTI_DESCRIP_SIZE 80

typedef struct
{
  // Thanks to brainder my g's <3
  int   sizeof_hdr;
  char  data_type[10];
  char  db_name[18];
  int   extents;
  short session_error;
  char  regular;
  char  dim_info;
  short dim[8];
  float intent_p1;
  float intent_p2;
  float intent_p3;
  short intent_code;
  short datatype;
  short bitpix;
  short slice_start;
  float pixdim[8];
  float vox_offset;
  float scl_slope;
  float scl_inter;
  short slice_end;
  char  slice_code;
  char  xyzt_units;
  float cal_max;
  float cal_min;
  float slice_duration;
  float toffset;
  int   glmax;
  int   glmin;
  char  descrip[NIFTI_DESCRIP_SIZE];
  char  aux_file[24];
  short qform_code;
  short sform_code;
  float quatern_b;
  float quatern_c;
  float quatern_d;
  float qoffset_x;
  float qoffset_y;
  float qoffset_z;
  float srow_x[4];
  float srow_y[4];
  float srow_z[4];
  char  intent_name[16];
  char  magic[4];
} NIFTI_Header;

typedef struct
{
  FILE* f;
  int version;
  NIFTI_Header header;
} NIFTI_File;

bool NIFTI_Open(NIFTI_File* file, const char* path);
void NIFTI_Close(NIFTI_File* file);

