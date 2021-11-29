#include "SwissRanger.hpp"
#include <iostream>

CMesaDevice *cam;

float *buffer_, *xp_, *yp_, *zp_;

// connect to camera with specified ip address
int connect(string addr)
{
  int res;
  res = SR_OpenETH(&cam, addr.c_str());

  if (res < 1)
  {
    printf("Could not connect to camera with ip: %s\n", addr.c_str());
    return 0;
  }

  printf("Connected to camera with ip: %s succesfully\n", addr.c_str());
  return 1;
}

// disconnect from camera
int disconnect()
{
  int res;
  res = SR_Close(cam);

  if (res < 0)
  {
    printf("Error while disconnecting from camera\n");
    return 0;
  }

  printf("Disconnected from camera succesfully\n");
  return 1;
}

// set camera mode
int setMode(int mode)
{
  int res;
  res = SR_SetMode(cam, mode);

  if (res < 0)
  {
    printf("Error while setting mode of camera\n");
    return 0;
  }

  printf("Set mode of camera succesfully\n");
  return 1;
}

// set auto exposure
int setAutoExposure(bool val)
{
  int res;
  int timemin, timemax, percOverPos, desiredPos;
  if (val == true)
  {
    timemin = 1;
    timemax = 150;
    percOverPos = 5;
    desiredPos = 70;
  }
  else
  {
    timemin = 10;
    timemax = 20;
    percOverPos = 0;
    desiredPos = 0;
  }

  res = SR_SetAutoExposure(cam, timemin, timemax, percOverPos, desiredPos);

  if (res < 0)
  {
    printf("Error while setting auto exposure of camera\n");
    return 0;
  }

  printf("Set auto exposure of camera succesfully\n");
  return 1;
}

// set integration time
int setIntegrationTime(int time)
{
  int res;
  res = SR_SetIntegrationTime(cam, time);

  if (res < 0)
  {
    printf("Error while setting integration time of camera\n");
    return 0;
  }

  printf("Set integration time of camera succesfully\n");
  return 1;
}

// set amplitude threshold
int setAmplitudeThreshold(int val)
{
  int res;
  res = SR_SetAmplitudeThreshold(cam, val);

  if (res < 0)
  {
    printf("Error while setting amplitude threshold of camera\n");
    return 0;
  }

  printf("Set amplitude threshold of camera succesfully\n");
  return 1;
}

// set modulation frequency
int setModulationFrequency(ModulationFrq freq)
{
  int res;
  res = res = SR_SetModulationFrequency(cam, freq);

  if (res < 0)
  {
    printf("Error while setting modulation frequency of camera\n");
    return 0;
  }

  printf("Set modulation frequency of camera succesfully\n");
  return 1;
}

//render camera frame
int renderFrame()
{
  SR_SetMode(cam, AM_COR_FIX_PTRN | AM_CONV_GRAY | AM_DENOISE_ANF | AM_CONF_MAP);
  int res = SR_Acquire(cam);
  if (res < 0)
  {
    printf("Error acquiring image\n");
    return 0;
  }

  Mat depth(SR_ROWS, SR_COLS, CV_16U, SR_GetImage(cam, SR_IMG_DISTANCE));
  Mat visual(SR_ROWS, SR_COLS, CV_16U, SR_GetImage(cam, SR_IMG_AMPLITUDE));
  Mat confidence(SR_ROWS, SR_COLS, CV_16U, SR_GetImage(cam, SR_IMG_CONFIDENCE));

  Size newSize(640, 480);
  resize(depth, depth, newSize);
  resize(visual, visual, newSize);
  resize(confidence, confidence, newSize);

  normalize(depth, depth, 0, 255, NORM_MINMAX, CV_8UC1);
  equalizeHist(depth, depth);

  normalize(visual, visual, 0, 255, NORM_MINMAX, CV_8UC1);
  equalizeHist(visual, visual);

  normalize(confidence, confidence, 0, 255, NORM_MINMAX, CV_8UC1);
  equalizeHist(confidence, confidence);

  imshow("Depth", depth);
  imshow("Visual", visual);
  imshow("Confidence", confidence);

  cvWaitKey(15);

  return 1;
}

// get device string
string getDeviceString()
{
  char buf[100];
  SR_GetDeviceString(cam, buf, 100);
  string deviceString(buf);
  return deviceString;
}

//save points to file
int savePoints(string filename)
{
  int res;

  res = SR_Acquire(cam);

  if (res < 0)
  {
    printf("Error acquiring image\n");
    return 0;
  }

  size_t buffer_size = SR_ROWS * SR_COLS * 3 * sizeof(float);
  buffer_ = (float *)malloc(buffer_size);
  memset(buffer_, 0xaf, buffer_size);

  xp_ = buffer_;
  yp_ = &xp_[SR_ROWS * SR_COLS];
  zp_ = &yp_[SR_ROWS * SR_COLS];

  res = SR_CoordTrfFlt(cam, xp_, yp_, zp_, sizeof(float), sizeof(float), sizeof(float));
  if (res < 0)
  {
    printf("Error calculating points\n");
    return 0;
  }

  std::ofstream file(filename);

  for (int i = 0; i < SR_COLS * SR_ROWS; i++)
  {
    char buff[50];
    sprintf(buff, "%.6f %.6f %.6f\n", xp_[i], yp_[i], zp_[i]);
    file << buff;
  }

  file.close();

  if (buffer_)
    free(buffer_);

  buffer_ = NULL;

  return 1;
}