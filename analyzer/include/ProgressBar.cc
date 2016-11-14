#include "ProgressBar.h"

void display_progress_bar(char* disp, const unsigned long whereami, const unsigned long tot, const double init_time, double& average, double& speed, bool batch)
{
  int progress=int(100*double(whereami)/double(tot));
  char* p = disp;
  struct timeval tv;
  static double previous_time=0;
  static double previous = 0;
  gettimeofday(&tv,0);
  speed = ( double(whereami) - previous * double(tot) ) / double(tv.tv_sec + 1.0e-6*tv.tv_usec - previous_time);
  average = double(whereami) / double(tv.tv_sec + 1.0e-6*tv.tv_usec - init_time);

  if (!batch) {
    sprintf(disp,"processed: %2d%%   ",progress);
    move_to_end(p,disp);
    *p++ = '[';
    for ( int k = 0 ; k < 20 ; k++) {
      if ( k < progress/5)
	*p++='=';
      else if (k == progress/5)
	*p++='>';
      else
	*p++=' ';
    }
    *p++=']';
    *p++='\0';
    char buffer[40];
    sprintf(buffer,"  %.1f evts/s -> %.1f evts/s",speed,average);
    strncat(disp,buffer,40);
    std::cout << "\r";
    std::cout << disp;
    std::cout.flush();
  }
  else{
    if (whereami%100 == 1 && whereami != 1)
      std::cout << " processed " << whereami-1 << " entries >> " << (whereami-1)*100/tot << "%\n";
  }
  previous = double(whereami)/double(tot);
  previous_time=double(tv.tv_sec+1.0e-6*tv.tv_usec);
}

void display_end_bar(char* disp)
{
  sprintf(disp," processed: 100%% [====================]");
  std::cout << "\r";
  std::cout << disp;
  std::cout.flush();
  std::cout << "\n";
}

