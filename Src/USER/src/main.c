#include "main.h"

static TaskHandle_t AppTaskCreate_Handle;
static TaskHandle_t LED1_Task_Handle;
static TaskHandle_t LED2_Task_Handle;

void LED2_Task(void *paramerter)
{
    while(1)
    {
        ABIT_LED2_ON;
        vTaskDelay(500);
        printf("led2_task running, LED2_ON\r\n");
        ABIT_LED2_OFF;
        vTaskDelay(500);
        printf("led2_task running, LED2_OFF\r\n");
    }
}

void LED1_Task(void *paramerter)
{
    while(1)
    {
        ABIT_LED1_ON;
        vTaskDelay(1000);
        printf("led1_task running, LED1_ON\r\n");
        ABIT_LED1_OFF;
        vTaskDelay(1000);
        printf("led1_task running, LED1_OFF\r\n");
    }
}

void AppTaskCreate(void *parameter)
{
    BaseType_t xReturn = pdPASS;

    taskENTER_CRITICAL();
    xReturn = xTaskCreate((TaskFunction_t)LED1_Task,
                          (const char *)"LED1_Task",
                          (uint16_t)128,
                          (void *)NULL,
                          (UBaseType_t)2,
                          (TaskHandle_t *)&LED1_Task_Handle);
    if(xReturn == pdPASS)
        printf("create LED1 Task success!\r\n");

    xReturn = xTaskCreate((TaskFunction_t)LED2_Task,
                          (const char *)"LED2_Task",
                          (uint16_t)128,
                          (void *)NULL,
                          (UBaseType_t)3,
                          (TaskHandle_t *)&LED2_Task_Handle);
    if(xReturn == pdPASS)
        printf("create LED2 Task success!\r\n");
    
    vTaskDelete(AppTaskCreate_Handle);

    portEXIT_CRITICAL();
}

int main()
{
    BaseType_t xReturn = pdPASS;

    bsp_abit_sys_init();

    xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
                          (const char *)"AppTaskCreate",
                          (uint16_t)512,
                          (void *)NULL,
                          (UBaseType_t)1,
                          (TaskHandle_t *)&AppTaskCreate_Handle);
    if(xReturn == pdPASS)
        vTaskStartScheduler();
    else
        return -1;
    
    return 0;
}