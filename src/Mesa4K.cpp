#include "Mesa4K.hpp"

void intHandler(int signum)
{
  stop = 1;
}

int main(int argc, char *argv[])
{

  printf("Starting Mesa4K\n");

  // add ctrl-c interupt handler
  signal(SIGINT, intHandler);

  if (argc < 3)
  {
    printf("Please specify the mode and ip address; check docs for help\n");
    exit(EXIT_FAILURE);
    return 0;
  }

  mode = argv[1];
  ip_addr = argv[2];

  // connect to camera and set options
  connect(ip_addr);
  setMode(SR_MODE);
  setAutoExposure(true);
  setIntegrationTime(100);
  setModulationFrequency(MF_15_5MHz);
  setAmplitudeThreshold(20);

  printf("Device has type: %s\n", getDeviceString().c_str());

  if (mode == "gui")
  {
    printf("Running gui mode\n");
    // Main Loop
    while (!stop)
    {
      // render Frame
      res = renderFrame();
      if (res < 1)
      {
        printf("Error during image acquisition\n");
        disconnect();
        exit(EXIT_FAILURE);
        break;
      }
    }
  }

  if (mode == "pcl")
  {
    printf("Running pcl mode\n");
    if (argc < 4)
    {
      printf("Please specify the mode and ip address and filename; check docs for help\n");
      exit(EXIT_FAILURE);
      return 0;
    }

    string filename = argv[3];

    savePoints(filename);
  }

  //disconnect from camera
  disconnect();

  return 0;
}