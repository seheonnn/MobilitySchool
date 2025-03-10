```
// 실습 1
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#define PCn_2_IDX 19
#define P2_IDX 2
#define PCn_1_IDX 11
#define P1_IDX 1

#define EXISO_IDX 4
#define FENO_IDX 8
#define EIENO_IDX 11
#define INPO_IDX 12
#define IGPO_IDX 14

#define SRE_IDX 10;
#define TOS_IDX 11

#define RENO_IDX 9

IfxCpu_syncEvent g_cpuSyncEvent = 0;

void initGPIO(void);
void initERU(void);

IFX_INTERRUPT(ISR0, 0, 0x10); // 0x10 priority의 인터럽트 발생하면 ISR0 실행
void ISR0(void) {
    P10_OUT.U = 0x1 << P2_IDX;
}
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
    initERU();

    while(1) {

    }

    return(1);
}

void initGPIO(void){
    P02_IOCR0.U &= ~(0x1F << PCn_1_IDX); // 스위치 초기화
    P02_IOCR0.U |= 0x02 << PCn_1_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_2_IDX); // LED 초기화
    P10_IOCR0.U |= 0x10 << PCn_2_IDX;
}

void initERU (void) {
    // set EICR
    SCU_EICR1.U &= ~(0x7 << EXISO_IDX);
    SCU_EICR1.U |= 0x1 << EXISO_IDX;

    SCU_EICR1.U |= 1 << FENO_IDX;
    SCU_EICR1.U |= 1 << EIENO_IDX;

    SCU_EICR1.U &= ~(0x7 << INPO_IDX);

    // set IGCR
    SCU_IGCR0.U &= ~(0x3 << IGPO_IDX);
    SCU_IGCR0.U |= 0x1 << IGPO_IDX;

    // set IGCR
    SRC_SCU_SCU_ERU0.U &= ~0xFF;
    SRC_SCU_SCU_ERU0.U |= 0x10;

    SRC_SCU_SCU_ERU0.U |= 1 << SRE_IDX;
    SRC_SCU_SCU_ERU0.U &= ~(0x3 << TOS_IDX);
}

```

```
// 스위치 Interrupt 활용 toggle
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#define PCn_2_IDX 19
#define P2_IDX 2
#define PCn_1_IDX 11
#define P1_IDX 1

#define EXISO_IDX 4
#define FENO_IDX 8 // Falling Edge
#define EIENO_IDX 11
#define INPO_IDX 12
#define IGPO_IDX 14

#define SRE_IDX 10;
#define TOS_IDX 11

#define RENO_IDX 9 // Rising Edge

IfxCpu_syncEvent g_cpuSyncEvent = 0;

void initGPIO(void);
void initERU(void);

IFX_INTERRUPT(ISR0, 0, 0x10); // 0x10 priority의 인터럽트 발생하면 ISR0 실행
void ISR0(void) {
//    P10_OUT.U = 0x1 << P2_IDX;
    P10_OMR.U = 0x40004; // toggle
}
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
    initERU();

    while(1) {
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

void initERU (void) {
    // set EICR
    SCU_EICR1.U &= ~(0x7 << EXISO_IDX);
    SCU_EICR1.U |= 0x1 << EXISO_IDX;

    SCU_EICR1.U |= 1 << FENO_IDX;
    SCU_EICR1.U |= 1 << EIENO_IDX;

    SCU_EICR1.U &= ~(0x7 << INPO_IDX);

    // set IGCR
    SCU_IGCR0.U &= ~(0x3 << IGPO_IDX);
    SCU_IGCR0.U |= 0x1 << IGPO_IDX;

    // set IGCR
    SRC_SCU_SCU_ERU0.U &= ~0xFF;
    SRC_SCU_SCU_ERU0.U |= 0x10;

    SRC_SCU_SCU_ERU0.U |= 1 << SRE_IDX;
    SRC_SCU_SCU_ERU0.U &= ~(0x3 << TOS_IDX);
}
```