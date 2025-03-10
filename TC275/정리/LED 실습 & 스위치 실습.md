Reset Value가 이미 0010이긴 하지만 가독성을 위해 동일한 값으로 세팅

```c
void initLED(void){
    // 주소기반 LED 초기화 및 설정
    P10_IOCR0.U &= ~(0x1F << PCn_2_IDX);
    P10_IOCR0.U |= 0x10 << PCn_2_IDX;
}
```

Push-Pull - 전원에 모두 연결되어 있음

Open-drain - 전원에 모두 연결되어 있지 않아 정확한 판별이 어려움

Pull-up - 높은 전압에 연결되어 있음. 초기화 1

Pull-down - 낮은 전압에 연결되어 있음. 초기화 0


```c
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#define PCn_2_IDX 19
#define P2_IDX 2
#define PCn_1_IDX 11
#define P1_IDX 1

IfxCpu_syncEvent g_cpuSyncEvent = 0;

void initGPIO(void);

int core0_main(void)
{
    IfxCpu_enableInterrupts();

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    initGPIO();

    while(1)
    {
        // & 값이 0이면 버튼이 눌린 것
//        if ((P02_IN.U & (0x1 << P1_IDX)) == 0) {
        if (!(P02_IN.U & (0x1 << P1_IDX))) {
            P10_OUT.U = 0x1 << P2_IDX; // LED On
        } else {
            P10_OUT.U = 0x0 << P2_IDX;
        }
    }
    return(1);
}

void initGPIO(void){
    P02_IOCR0.U &= ~(0x1F << PCn_1_IDX); // 스위치 초기화
    P02_IOCR0.U |= 0x02 << PCn_1_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_2_IDX); // LED 초기화
    P10_IOCR0.U |= 0x10 << PCn_2_IDX;
}

```

```c
// 실습 1

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#define PCn_2_IDX 19
#define P2_IDX 2

#define PCn_1_IDX 11
#define P1_IDX 1

IfxCpu_syncEvent g_cpuSyncEvent = 0;


void initGPIO(void);

int core0_main(void)
{
    IfxCpu_enableInterrupts();

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    initGPIO();

    while(1) // while 빠르게 돔
    {
        // & 값이 0이면 버튼이 눌린 것
//        if ((P02_IN.U) & (0x1 << P1_IDX) == 0) {
        if (!(P02_IN.U & (0x1 << P1_IDX))) { // 누른 순간은 0, 기본 1
            P10_OUT.U = 0x1 << P1_IDX; // RED LED On
        } else {
            P10_OUT.U = 0x1 << P2_IDX; // BLUE LED On
        }
    }
    return(1);
}

void initGPIO(void){
    P02_IOCR0.U &= ~(0x1F << PCn_1_IDX); // 스위치 초기화
    P02_IOCR0.U |= 0x02 << PCn_1_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_2_IDX); // BLUE LED 초기화
    P10_IOCR0.U |= 0x10 << PCn_2_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_1_IDX); // RED LED 초기화
    P10_IOCR0.U |= 0x10 << PCn_1_IDX;
}

```


```
// 실습 1

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#define PCn_2_IDX 19
#define P2_IDX 2

#define PCn_1_IDX 11
#define P1_IDX 1

IfxCpu_syncEvent g_cpuSyncEvent = 0;


void initGPIO(void);

int core0_main(void)
{
    IfxCpu_enableInterrupts();

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    initGPIO();

    while(1) // while 빠르게 돔
    {
        // & 값이 0이면 버튼이 눌린 것
//        if ((P02_IN.U) & (0x1 << P1_IDX) == 0) {
        if (!(P02_IN.U & (0x1 << P1_IDX))) { // 누른 순간은 0, 기본 1
            P10_OUT.U = 0x1 << P1_IDX; // RED LED On
        } else {
            P10_OUT.U = 0x1 << P2_IDX; // BLUE LED On
        }
    }
    return(1);
}

void initGPIO(void){
    P02_IOCR0.U &= ~(0x1F << PCn_1_IDX); // 스위치 초기화
    P02_IOCR0.U |= 0x02 << PCn_1_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_2_IDX); // BLUE LED 초기화
    P10_IOCR0.U |= 0x10 << PCn_2_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_1_IDX); // RED LED 초기화
    P10_IOCR0.U |= 0x10 << PCn_1_IDX;
}

```