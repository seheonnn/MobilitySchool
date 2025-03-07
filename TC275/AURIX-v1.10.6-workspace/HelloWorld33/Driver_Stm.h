#ifndef DRIVER_STM
#define DRIVER_STM

/***********************************************************************/
/*Include*/ 
/***********************************************************************/
#include "Ifx_Types.h"
#include "IfxStm.h"
#include "IfxCpu_Irq.h"

typedef unsigned int uint8_t;
typedef unsigned int uint32_t;

/***********************************************************************/
/*Typedef*/ 
/***********************************************************************/
typedef struct
{
    uint8_t u8nuScheduling1msFlag;
    uint8_t u8nuScheduling10msFlag;
    uint8_t u8nuScheduling100msFlag;
    uint8_t u8nuScheduling1000msFlag;
}SchedulingFlag;

/***********************************************************************/
/*Define*/ 
/***********************************************************************/

/***********************************************************************/
/*External Variable*/ 
/***********************************************************************/
extern SchedulingFlag stSchedulingInfo;


/***********************************************************************/
/*Global Function Prototype*/ 
/***********************************************************************/
extern void Driver_Stm_Init(void);


#endif /* DRIVER_STM */
