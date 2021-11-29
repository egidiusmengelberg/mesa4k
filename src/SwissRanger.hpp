#ifndef SWISSRANGER_H
#define SWISSRANGER_H

#include <stdio.h>
#include <string>

// OpenCV
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"

// LibMesaSr
#include "libMesaSR.h"
#include "definesSR.h"

#define SR_ROWS 144
#define SR_COLS 176
#define USE_FILTER 1
#define SR_IMG_DISTANCE 0
#define SR_IMG_AMPLITUDE 1
#define SR_IMG_CONFIDENCE 2
#define SR_MODE (AM_CONF_MAP | AM_CONV_GRAY | AM_COR_FIX_PTRN | AM_DENOISE_ANF)

using namespace std;
using namespace cv;

int connect(string addr);
int disconnect();
int setMode(int mode);
int setAutoExposure(bool val);
int setIntegrationTime(int val);
int setModulationFrequency(ModulationFrq freq);
int setAmplitudeThreshold(int val);

int viewImage();

#endif