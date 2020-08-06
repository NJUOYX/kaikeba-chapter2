#include "data.h"
#include"timer.h"
#include <stdio.h>
Emp_table emp_data_libs[EMP_NUM];
int work_hours;

int check_id(int id)
{
    if (id >= EMP_ID_MIN && id <= EMP_ID_MAX)
        return 0;
    return -1;
}

int in_work(int id, int ntime)
{
    return emp_data_libs[GET_IDX(id)].recs[GET_DAY(ntime)].on_v;
}

int on_duty(int minutes, int emp_id)
{
    int late = 0;
    int over_time = 0;
    late = GET_HOUR(minutes) - START_HOUR;
    emp_data_libs[GET_IDX(emp_id)].recs[GET_DAY(minutes)].on_duty = MIN_TO_HM_TRANSFER(minutes);
    emp_data_libs[GET_IDX(emp_id)].recs[GET_DAY(minutes)].on_v = 1;
    if (GET_DAY(minutes) > 0)
    {
        over_time = GET_HM_HOUR(get_work_hm(GET_IDX(emp_id), GET_DAY(minutes) - 1));
    }
    if (late < 0)
        return 0;
    if (over_time > OVER_TIME && late < AVAILABLE_TIME)
        return 0;
    else
        return (int)(MIN_TO_HM_TRANSFER(minutes));
}

int off_duty(int minutes, int emp_id)
{
    int early = 0;
    early = GET_HOUR(minutes) - GET_HM_HOUR(emp_data_libs[GET_IDX(emp_id)].recs[GET_DAY(minutes)].on_duty);
    emp_data_libs[GET_IDX(emp_id)].recs[GET_DAY(minutes)].off_duty = MIN_TO_HM_TRANSFER(minutes);
    emp_data_libs[GET_IDX(emp_id)].recs[GET_DAY(minutes)].off_v = 1;
    if (early < 0)
        return 0;
    else
        return (int)(MIN_TO_HM_TRANSFER(minutes));
}

int data_lib_init(int wh)
{
    int i = 0;
    int j = 0;
    work_hours = wh;
    for (i = 0; i < EMP_NUM; ++i)
    {
        for (j = 0; j < WORK_DAYS; ++j)
            emp_data_libs[i].recs[j].on_v = emp_data_libs[i].recs[j].off_v = 0;
    }
    return 0;
}

uint16_t get_work_hm(int idx, int day)
{
    if (emp_data_libs[idx].recs[day].on_v == 1 && emp_data_libs[idx].recs[day].off_v == 1)
    {
        return SUB_HM(emp_data_libs[idx].recs[day].off_duty, emp_data_libs[idx].recs[day].on_duty);
    }
    return 0;
}

//周平均上班时长，周迟到，早退，缺卡次数
uint16_t get_avarange(int idx)
{
    int i = 0;
    uint16_t total = 0;
    int res = 0;
    for(i = 0;i<DAY_NUM;++i)
    {
        total+=get_work_hm(idx,i);
    }
    res = HM_TO_MIN_TRANSFER(total);
    return MIN_TO_HM_TRANSFER(res/DAY_NUM);
}

int get_late(int idx)
{
    int i = 0;
    int res = 0;
    for(i = 0;i<DAY_NUM;++i)
    {
        if(emp_data_libs[idx].recs[i].on_v == 0||GET_HM_HOUR(emp_data_libs[idx].recs[i].on_duty)<START_HOUR)
            res++;
    }
    return res;
}

int get_early(int idx)
{
    int i = 0;
    int res = 0;
    for(i = 0;i<DAY_NUM;++i)
    {
        if(GET_HM_HOUR(get_work_hm(idx,i))<work_hours)
            res++;
    }
    return res;
}

int get_lack(int idx)
{
    int i = 0;
    int res = 0;
    for(i = 0;i<DAY_NUM;++i)
    {
        if(emp_data_libs[idx].recs[i].off_v == 0)
            res++;
    }
    return res;
}

void write_report()
{
    int i = 0;
    int avar_min = 0;
    int late = 0;
    int early = 0;
    int lack = 0;
    for (i = 0; i < EMP_NUM; ++i)
    {
        avar_min = get_avarange(i);
        printf("avarange: %d hours,%d minutes\n", GET_HOUR(avar_min), GET_MIN(avar_min));
        late = get_late(i);
        printf("late: %d times\n", late);
        early = get_early(i);
        printf("early: %d times\n", early);
        lack = get_lack(i);
        printf("lack of duty: %d times\n", lack);
    }
}