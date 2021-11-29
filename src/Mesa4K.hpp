#ifndef MESA4K_H
#define MESA4K_H

#include <stdio.h>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include "SwissRanger.hpp"

using namespace std;

volatile sig_atomic_t stop;
string ip_addr;
int res;

void intHandler(int signum);

#endif