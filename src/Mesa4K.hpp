#ifndef MESA4K_H
#define MESA4K_H

#include <stdio.h>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include "SwissRanger.hpp"

using namespace std;

volatile sig_atomic_t stop;
string mode;
string ip_addr;
int res;

void intHandler(int signum);

#endif