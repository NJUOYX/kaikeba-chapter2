#ifndef __DATA_H__
#define __DATA_H__
#include "common.h"

#define WORK_DAYS 5

#define EMP_ID_MAX 199999
#define EMP_ID_MIN 100000
#define EMP_NUM EMP_ID_MAX - EMP_ID_MIN + 1


struct Work_time
{
    uint16_t on_duty; //高8位作为时，低八位作为分
    uint16_t off_duty;
    uint8_t on_v; //有效位
    uint8_t off_v;
};

#define HOUR_MIN_TO_HM(hour,min) ((((uint8_t)(hour << 8))) | ((uint8_t)(min)))
#define MIN_TO_HM_TRANSFER(min) HOUR_MIN_TO_HM(GET_HOUR(min),GET_MIN(min))
#define GET_HM_HOUR(hm) (hm>>8)
#define GET_HM_MIN(hm) (hm&0xff)
#define HM_TO_MIN_TRANSFER(hm) GET_HM_HOUR(hm)*MIN_NUM+GET_HM_MIN(hm)
#define SUB_HM(hm1,hm2) (((hm2&0xff00)-(hm1&0xff00))|((hm2&0xff)-(hm1&0xff)))

#define GET_IDX(id) (id - EMP_ID_MIN)

#define OVER_TIME 3
#define AVAILABLE_TIME 2 

typedef struct Work_time Work_time;

struct Emp_table
{
    //uint32_t emp_id;
    Work_time recs[WORK_DAYS];
};

typedef struct Emp_table Emp_table;

extern Emp_table emp_data_libs[EMP_NUM];
int in_work(int id, int ntime);
int check_id(int id);
int data_lib_init(int wh);
int on_duty(int minutes, int emp_id);
int off_duty(int minutes, int emp_id);
uint16_t get_work_hm(int idx,int day);
void write_report();
#endif //__DATA_H__