#ifndef __TIMER_H__
#define __TIMER_H__
#include"pthread.h"

#define TIME_STR_BUFFER_SIZE 20
#define DAY_NUM 5
#define HOUR_NUM 24
#define MIN_NUM 60
#define START_HOUR 7
#define START_MIN START_HOUR*MIN_NUM
#define TOTAL_MINUTES DAY_NUM*HOUR_NUM*MIN_NUM - START_HOUR*MIN_NUM

#define GET_DAY(min) min/HOUR_NUM/MIN_NUM
#define GET_HOUR(min) (min/MIN_NUM)%HOUR_NUM
#define GET_MIN(min) (min)%MIN_NUM

extern int timer;
extern char str_time[TIME_STR_BUFFER_SIZE];
extern int mins_per_sec;

int init_timer(int seconds_per_hour);
int start_timer();
int check_timer();
int stop_timer();
char*time_show();



#endif//__TIMER_H__