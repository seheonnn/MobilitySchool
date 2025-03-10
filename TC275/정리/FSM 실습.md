```
// 실습3 FSM
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#define PCn_2_IDX 19
#define P2_IDX 2
#define PCn_1_IDX 11
#define P1_IDX 1

#define PCn_3_IDX 3
#define P3_IDX 2

#define EXIS0_IDX 4
#define FEN0_IDX 8 // Falling Edge
#define EIEN0_IDX 11
#define INP0_IDX 12
#define IGP0_IDX 14

#define SRE_IDX 10;
#define TOS_IDX 11

#define REN0_IDX 9 // Rising Edge

IfxCpu_syncEvent g_cpuSyncEvent = 0;

void initGPIO(void);
void initERU(void);

IFX_INTERRUPT(ISR0, 0, 0x10); // 0x10 priority의 인터럽트 발생하면 ISR0 실행
IFX_INTERRUPT(ISR1, 0, 0x20);

volatile int blinking = 1;
void ISR0(void) {
//    P10_OUT.U = 0x1 << P2_IDX;
//    P10_OMR.U = 0x40004; // toggle
    blinking = !blinking;
}

void ISR1(void) {
    P10_OMR.U = 0x20002; // toggle
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

    P10_OMR.U = 0x40002; 
    while(1) {
        if (blinking) {
            P10_OMR.U |= 0x40004; 
            P10_OMR.U |= 0x20002; 
            for (volatile int i = 0; i < 10000000; i++); // Delay
        }
    }
    
    // 답안
//    P10_OMR.U = 0x1 << 1;
//    while(1) {
//        if (blinking) {
//            P10_OMR.U = 0x60006;
//            for (volatile int i = 0; i < 10000000; i++); // Delay
//        }
//    }

		// 답안 2
//    while(1) {
//        P10_OMR.U = 0x60006 * state;
//        for (volatile int i = 0; i < 10000000; i++); // Delay
//    }
    return(1);
}

void initGPIO(void){
    P02_IOCR0.U &= ~(0x1F << PCn_1_IDX); // 스위치3 초기화
    P02_IOCR0.U |= 0x02 << PCn_1_IDX;

    P02_IOCR0.U &= ~(0x1F << PCn_3_IDX); // 스위치2 초기화
    P02_IOCR0.U |= 0x02 << PCn_3_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_2_IDX); // BLUE LED 초기화
    P10_IOCR0.U |= 0x10 << PCn_2_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_1_IDX); // RED LED 초기화
    P10_IOCR0.U |= 0x10 << PCn_1_IDX;
}

void initERU (void) {
    // set EICR
    SCU_EICR1.U &= ~(0x7 << EXIS0_IDX);
    SCU_EICR1.U |= 0x1 << EXIS0_IDX;

    SCU_EICR1.U |= 1 << FEN0_IDX;
    SCU_EICR1.U |= 1 << EIEN0_IDX;

    SCU_EICR1.U &= ~(0x7 << INP0_IDX);

    // set IGCR
    SCU_IGCR0.U &= ~(0x3 << IGP0_IDX);
    SCU_IGCR0.U |= 0x1 << IGP0_IDX;

    // set ERU
    SRC_SCU_SCU_ERU0.U &= ~0xFF;
    SRC_SCU_SCU_ERU0.U |= 0x10;

    SRC_SCU_SCU_ERU0.U |= 1 << SRE_IDX;
    SRC_SCU_SCU_ERU0.U &= ~(0x3 << TOS_IDX);

    // -----

    // set EICR
    SCU_EICR1.U &= ~(0x7 << 20); // EXIS1_IDX
    SCU_EICR1.U |= 0x2 << 20; // EXIS1_IDX

    SCU_EICR1.U |= 1 << 24; // FEN1_IDX
    SCU_EICR1.U |= 1 << 27; // EIEN1_IDX

    SCU_EICR1.U &= ~(0x7 << 28); // INP1_IDX
    SCU_EICR1.U |= 1 << 28; // INP1_IDX, OGU 1 채널

    // set IGCR
    SCU_IGCR0.U &= ~(0x3 << 30); // IGP1_IDX
    SCU_IGCR0.U |= 0x1 << 30; // IGP1_IDX

    // set ERU
    SRC_SCU_SCU_ERU1.U &= ~0xFF;
    SRC_SCU_SCU_ERU1.U |= 0x20; // 우선 순위

    SRC_SCU_SCU_ERU1.U |= 1 << SRE_IDX;
    SRC_SCU_SCU_ERU1.U &= ~(0x3 << TOS_IDX);
}

```

```
// 답안
#define STOP 0
#define BLINK 1

volatile int state = 0;

void ISR0(void) {
    // State Transition
    switch (state) {
        case STOP:
            state = BLINK;
            break;
        case BLINK:
            state = STOP;
        default:
            state = STOP;
    }
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

    P10_OMR.U = 0x1 << 1;
    while(1) {

        // State에 따른 동작
        switch (state) {
            case BLINK:
                P10_OMR.U = 0x60006 * state;
                for (volatile int i = 0; i < 10000000; i++); // Delay
                break;
            case STOP:
                break;
            default:
                break;
        }
    }
    return(1);
}
```