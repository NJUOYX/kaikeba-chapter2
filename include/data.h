#ifndef __DATA_H__
#define __DATA_H__
#include "common.h"

#define WORK_DAYS 5//工作天数

#define EMP_ID_MAX 199999//id值上限
#define EMP_ID_MIN 100000//id值下限
#define EMP_NUM EMP_ID_MAX - EMP_ID_MIN + 1//id数目


struct Work_time
{
    uint16_t on_duty; //上班时间记录高8位作为时，低八位作为分
    uint16_t off_duty;//下班时间记录
    uint8_t on_v; //显示上班时间记录有效
    uint8_t off_v;//显示下班记录有效
};
typedef struct Work_time Work_time;

/*
宏解释：
HM 指Work_time 中的时间记录方式
下列的宏都是时间记录方式的转换
DAY 记录从周一（0）到周五（4）
HOUR 指小时单位时间
MIN 值分钟单位时间
*/
#define HOUR_MIN_TO_HM(hour,min) ((((uint8_t)(hour << 8))) | ((uint8_t)(min)))
#define MIN_TO_HM_TRANSFER(min) HOUR_MIN_TO_HM(GET_HOUR(min),GET_MIN(min))
#define GET_HM_HOUR(hm) (hm>>8)
#define GET_HM_MIN(hm) (hm&0xff)
#define HM_TO_MIN_TRANSFER(hm) GET_HM_HOUR(hm)*MIN_NUM+GET_HM_MIN(hm)
#define SUB_HM(hm1,hm2) (((hm2&0xff00)-(hm1&0xff00))|((hm2&0xff)-(hm1&0xff)))//work_time 结构的相减计算

#define GET_IDX(id) (id - EMP_ID_MIN)

#define OVER_TIME 3 //弹性打卡中的超时工作时间底线
#define AVAILABLE_TIME 2 //弹性打卡可容忍迟到时间


struct Emp_table
{
    Work_time recs[WORK_DAYS];//5天的工作记录
};
typedef struct Emp_table Emp_table;

extern Emp_table emp_data_libs[EMP_NUM];
int in_work(int id, int ntime);//是否正在工作，ntime指当前时间（min）
int check_id(int id);//检查id是否正常
int data_lib_init(int wh);//数据库初始化
int on_duty(int minutes, int emp_id);//上班打卡
int off_duty(int minutes, int emp_id);//下班打卡
uint16_t get_work_hm(int idx,int day);//获得相关工作时间记录
void write_report();//输出工作周报
#endif //__DATA_H__