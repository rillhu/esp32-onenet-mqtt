#ifndef _LED_TASK_
#define _LED_TASK_

extern bool led_task_run;
extern unsigned int led_blink_freq; //second

void led_task(void *pv);

#endif
