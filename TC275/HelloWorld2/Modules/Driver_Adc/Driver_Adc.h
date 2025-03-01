//Driver_Adc.h 로 저장해주세요

#ifndef DRIVER_ADC
#define DRIVER_ADC

/***********************************************************************/
/*Include*/
/***********************************************************************/
#include "Ifx_Types.h"
#include "IfxVadc.h"
#include "IfxVadc_Adc.h"
/***********************************************************************/
/*Typedef*/
/***********************************************************************/
typedef struct
{
    IfxVadc_Adc vadc; /* VADC handle */
    IfxVadc_Adc_Group adcGroup;
} App_VadcAutoScan;


/***********************************************************************/
/*Define*/
/***********************************************************************/

/***********************************************************************/
/*External Variable*/
/***********************************************************************/
IFX_EXTERN App_VadcAutoScan g_VadcAutoScan;


/***********************************************************************/
/*Global Function Prototype*/
/***********************************************************************/
extern void Driver_Adc_Init(void);
extern void Driver_Adc0_ConvStart(void);
extern uint32_t Driver_Adc0_DataObtain(void);




#endif /* DRIVER_STM */
