#include "Mesa4K.hpp"

void intHandler(int signum)
{
  stop = 1;
}

int main(int argc, char *argv[])
{

  printf("Starting Mesa4K\n");

  signal(SIGINT, intHandler);

  if (argc < 2)
  {
    printf("Please specify the ip address of the camera\n");
    exit(EXIT_FAILURE);
    return 0;
  }

  ip_addr = argv[1];

  connect(ip_addr);
  setMode(SR_MODE);
  setAutoExposure(true);
  setIntegrationTime(100);
  setModulationFrequency(MF_15_5MHz);
  setAmplitudeThreshold(20);

  printf("Device has type: %s\n", getDeviceString().c_str());

  while (!stop)
  {
    res = viewImage();
    if (res < 1)
    {
      printf("Error during image acquisition\n");
      disconnect();
      exit(EXIT_FAILURE);
      break;
    }
  }

  disconnect();

  return 0;
}