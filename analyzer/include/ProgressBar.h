#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

#define move_to_end(p,s) p = strchr (s, '\0');

void display_progress_bar(char* disp, const unsigned long whereami, const unsigned long tot, const double init_time, double& speed, double& average, bool batch=false);
void display_end_bar(char* disp);


#endif
