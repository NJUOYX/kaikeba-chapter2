#include "common.h"
#include "timer.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include"lib.h"
uint8_t buffer[STR_BUFFER_SIZE];

int get_check_code(int code);

int clockin_machine_start(int s2m, int workhours)
{
    int emp_id = 0;
    int check_code = 0;
    int res = 0;
    if (data_lib_init(workhours) != 0)
    {
        log_error("data lib init failed");
        return -1;
    }
    init_timer(s2m);
    start_timer();
    while (check_timer() < TOTAL_MINUTES) //命令模式循环
    {
        printf("sys$:");
        scanf("%s", buffer);
        if (strcmp((const char*)buffer, WORK_COMMAND) == 0)
        {
            do
            {
                printf("your id:");
                scanf("%d", &emp_id);
                res = check_id(emp_id);
                if (res != 0)
                    log_error("id wrong");
            } while (res != 0);
            res = in_work(emp_id,check_timer());
            if (res == 0)
            {
                printf("请输入验证码：%d\nyour input:", get_check_code(emp_id));
                scanf("%d", &check_code);
                if(get_check_code(emp_id) != check_code)
                {
                    log_error("check code wrong");
                    continue;
                }
                res = on_duty(check_timer(), emp_id);
                if(res == 0)
                    log_info("check success");
                else
                    log_info("you are late");
            }
            else
            {
                res = off_duty(check_timer(),emp_id);
                if(res == 0)
                    log_info("check success");
                else
                {
                    printf("off duty too early,for %d\n",res);
                }
            }
        }
        else if (strcmp((const char*)buffer, TIME_COMMAND) == 0)
        {
            printf("%s\n", time_show());
        }
        else
            continue;
    }

    return 0;
}

int get_check_code(int code)
{
    int res = code;
    int e = 10000;
    while(code!=1)
    {
        res+=(code%10)*e;
        code/=10;
        e/=10;
    }
    return res;
}