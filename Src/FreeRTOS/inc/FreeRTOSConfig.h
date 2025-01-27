/*
 * FreeRTOS V202011.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f4xx.h"
#include "bsp_abit_usart.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
// #ifdef __ICCARM__
#if defined(__ICCARM) || defined(__CC_ARM) || defined(__GNUC__)
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

#define vAssertCalled(char, int) 						printf("Error:%s, %d\r\n", char, int)
#define configASSERT(x) if((x) == 0) 					vAssertCalled(__FILE__, __LINE__)

/************************************************************************ 
 *               FreeRTOS 基础配置配置选项 
 *********************************************************************/ 
/* 置 1：RTOS 使用抢占式调度器；置 0：RTOS 使用协作式调度器（时间片） 
* 
* 注：在多任务管理机制上，操作系统可以分为抢占式和协作式两种。 
* 协作式操作系统是任务主动释放 CPU 后，切换到下一个任务。 
* 任务切换的时机完全取决于正在运行的任务。 
*/
#define configUSE_PREEMPTION							1

/* 1 使能时间片调度(默认是使能的) */
#define configUSE_TIME_SLICING							1

/* 某些运行 FreeRTOS 的硬件有两种方法选择下一个要执行的任务： 
* 通用方法和特定于硬件的方法（以下简称“特殊方法”）。 
* 
* 通用方法： 
*      1.configUSE_PORT_OPTIMISED_TASK_SELECTION 为 0 或者硬件不支持这种特殊方法。 
*      2.可以用于所有 FreeRTOS 支持的硬件 
*      3.完全用 C 实现，效率略低于特殊方法。 
*      4.不强制要求限制最大可用优先级数目 
* 特殊方法： 
*      1.必须将 configUSE_PORT_OPTIMISED_TASK_SELECTION 设置为 1。 
*      2.依赖一个或多个特定架构的汇编指令（一般是类似计算前导零[CLZ]指令）。 
*      3.比通用方法更高效 
*      4.一般强制限定最大可用优先级数目为 32 
*  
* 一般是硬件计算前导零指令，如果所使用的，MCU 没有这些硬件指令的话此宏应该设置为 0！ 
*/
#define configUSE_PORT_OPTIMISED_TASK_SELECTION			1

/* 置1:使能低功耗tickless模式, 置0:保持系统节拍(tick)中断一直运行 */
#define configUSE_TICKLESS_IDLE							1

/* 
* 写入实际的 CPU 内核时钟频率，也就是 CPU 指令执行频率，通常称为 Fclk 
* Fclk 为供给 CPU 内核的时钟信号，我们所说的 cpu 主频为 XX MHz， 
* 就是指的这个时钟信号，相应的，1/Fclk 即为 cpu 时钟周期； 
*/
#define configCPU_CLOCK_HZ								( SystemCoreClock )

/* RTOS系统节拍中断的频率。即一秒中断的次数，每次中断RTOS都会进行任务调度 */
#define configTICK_RATE_HZ								( ( TickType_t ) 1000 )

/* 可使用的最大优先级 */
#define configMAX_PRIORITIES							( 32 )

/* 空闲任务使用的堆栈大小 */
#define configMINIMAL_STACK_SIZE						( ( unsigned short ) 128 )

/* 任务名字字符串长度 */
#define configMAX_TASK_NAME_LEN							( 10 )
#define configUSE_TRACE_FACILITY						1

/* 系统节拍计数器变量数据类型，1表示为16位无符号整型，0表示为32位无符号整型 */
#define configUSE_16_BIT_TICKS							0

/* 空闲任务放弃CPU使用权给其他同优先级的用户任务 */
#define configIDLE_SHOULD_YIELD							1

/* 启用队列 */
#define configUSE_QUEUE_SETS							1

/* 开启任务通知功能，默认开启 */
#define configUSE_TASK_NOTIFICATIONS					1

/* 使用互斥信号量 */
#define configUSE_MUTEXES								1

/* 使用递归互斥信号量 */
#define configUSE_RECURSIVE_MUTEXES						1

/* 为1时，使用计数信号量 */
#define configUSE_COUNTING_SEMAPHORES					1

/* 设置可以注册的信号量喝消息队列个数 */
#define configQUEUE_REGISTRY_SIZE						10

#define configUSE_APPLICATION_TASK_TAG					0

/***************************************************************** 
 *              FreeRTOS 与内存申请有关配置选项 
 ****************************************************************/
/* 支持动态内存申请 */
#define configSUPPORT_DYNAMIC_ALLOCATION				1

/* 系统所有总的堆大小 */
#define configTOTAL_HEAP_SIZE							( ( size_t ) ( 75 * 1024 ) )							

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 							0
#define configMAX_CO_ROUTINE_PRIORITIES 				( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS								1
#define configTIMER_TASK_PRIORITY						( 2 )
#define configTIMER_QUEUE_LENGTH						10
#define configTIMER_TASK_STACK_DEPTH					( configMINIMAL_STACK_SIZE * 2 )

/*************************************************************** 
             FreeRTOS 与钩子函数有关的配置选项 
**************************************************************/
/* 置 1：使用空闲钩子（Idle Hook 类似于回调函数）；置 0：忽略空闲钩子 
 * 
 * 空闲任务钩子是一个函数，这个函数由用户来实现， 
 * FreeRTOS 规定了函数的名字和参数：void vApplicationIdleHook(void )， 
 * 这个函数在每个空闲任务周期都会被调用 
 * 对于已经删除的 RTOS 任务，空闲任务可以释放分配给它们的堆栈内存。 
 * 因此必须保证空闲任务可以被 CPU 执行 
 * 使用空闲钩子函数设置 CPU 进入省电模式是很常见的 
 * 不可以调用会引起空闲任务阻塞的 API 函数 
 */
#define configUSE_IDLE_HOOK								0

/* 置 1：使用时间片钩子（Tick Hook）；置 0：忽略时间片钩子 
 * 
 * 
 * 时间片钩子是一个函数，这个函数由用户来实现， 
 * FreeRTOS 规定了函数的名字和参数：void vApplicationTickHook(void ) 
 * 时间片中断可以周期性的调用 
 * 函数必须非常短小，不能大量使用堆栈， 
 * 不能调用以”FromISR" 或 "FROM_ISR”结尾的 API 函数 
 */
/* xTaskIncrementTick 函数是在 xPortSysTickHandler 中断函数中被调用的。因此，  
 * vApplicationTickHook()函数执的时间必须很短才行                                                                               
 */
#define configUSE_TICK_HOOK								0

/* 使用内存申请失败钩子函数  */
#define configUSE_MALLOC_FAILED_HOOK					0

/* 
 * 大于 0 时启用堆栈溢出检测功能，如果使用此功能 
 * 用户必须提供一个栈溢出钩子函数，如果使用的话 
 * 此值可以为 1 或者 2，因为有两种栈溢出检测方法 */
#define configCHECK_FOR_STACK_OVERFLOW					0

/******************************************************************** 
          FreeRTOS 与运行时间和任务状态收集有关的配置选项 
**********************************************************************/
/* 启用运行时间统计功能 */
#define configGENERATE_RUN_TIME_STATS					0

/* 启用可视化跟踪调试 */
#define configUSE_TRACE_FACILITY						0

/* 与宏 configUSE_TRACE_FACILITY 同时为 1 时会编译下面 3 个函数 
 * prvWriteNameToBuffer() 
 * vTaskList(), 
 * vTaskGetRunTimeStats() 
*/
#define configUSE_STATS_FORMATTING_FUNCTIONS			1

/******************************************************************** 
                FreeRTOS 与协程有关的配置选项 
*********************************************************************/
/* 启用协程，启用协程以后必须添加文件 croutine.c */ 
#define configUSE_CO_ROUTINES     						0 
/* 协程的有效优先级数目 */
#define configMAX_CO_ROUTINE_PRIORITIES       			( 2 ) 

/*********************************************************************** 
                FreeRTOS 与软件定时器有关的配置选项 
**********************************************************************/
/* 启用软件定时器 */
#define configUSE_TIMERS								1

/* 软件定时器优先级 */
#define configTIMER_TASK_PRIORITY						( configMAX_PRIORITIES - 1 )

/* 软件定时器队列长度 */
#define configTIMER_QUEUE_LENGTH						10

/* 软件定时器任务堆栈大小 */
#define configTIMER_TASK_STACK_DEPTH					( configMINIMAL_STACK_SIZE * 2 )

/************************************************************ 
            FreeRTOS 可选函数配置选项 
************************************************************/
#define INCLUDE_vTaskGetSchedulerState					1
#define INCLUDE_vTaskPrioritySet						1
#define INCLUDE_uxTaskPriorityGet						1
#define INCLUDE_vTaskDelete								1
#define INCLUDE_vTaskCleanUpResources					1
#define INCLUDE_vTaskSuspend							1
#define INCLUDE_vTaskDelayUntil							1
#define INCLUDE_vTaskDelay								1
#define INCLUDE_eTaskGetState							1
#define INCLUDE_xTimerPendFunctionCall					1

/****************************************************************** 
            FreeRTOS 与中断有关的配置选项 
******************************************************************/
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       						__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       						4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
/* 中断最低优先级 */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
/* 系统可管理的最高中断优先级 */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY					( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY			( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
// #define configASSERT( x ) if( ( x ) == 0 ) 				{ taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
/**************************************************************** 
            FreeRTOS 与中断服务函数有关的配置选项 
****************************************************************/ 
#define vPortSVCHandler 								SVC_Handler
#define xPortPendSVHandler 								PendSV_Handler

#endif /* FREERTOS_CONFIG_H */