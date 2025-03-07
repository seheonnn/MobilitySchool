/**
 * \file IfxCpu.c
 * \brief CPU  basic functionality
 *
 * \version iLLD_1_0_1_12_0
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxCpu.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

boolean IfxCpu_acquireMutex(IfxCpu_mutexLock *lock)
{
    boolean         retVal;
    volatile uint32 spinLockVal;

    retVal      = FALSE;

    spinLockVal = 1UL;
    spinLockVal =
        (uint32)__cmpAndSwap(((unsigned int *)lock), spinLockVal, 0);

    /* Check if the SpinLock WAS set before the attempt to acquire spinlock */
    if (spinLockVal == 0)
    {
        retVal = TRUE;
    }

    return retVal;
}


IfxCpu_CoreMode IfxCpu_getCoreMode(Ifx_CPU *cpu)
{
    IfxCpu_CoreMode    cpuMode;
    Ifx_CPU_DBGSR      dbgsr;
    IfxCpu_ResourceCpu index = IfxCpu_getIndex(cpu);

    cpuMode = IfxCpu_CoreMode_unknown;

    /*get the DBGSR.HALT status */
    /*Check if the request is done for same cpu as the host for this call */
    if (IfxCpu_getCoreIndex() != index)
    {                           /*status request is for other cpu than the host */
        dbgsr = cpu->DBGSR;
    }
    else
    {                           /*status request is for same cpu as the host */
        dbgsr.U = __mfcr(CPU_DBGSR);
    }

    /*Check if the requested CPU is in DBG HALT mode */
    if (dbgsr.B.HALT == (uint32)IfxCpu_DBGST_HALT_halt)
    {                           /*CPU is in DBG HALT mode */
        cpuMode = IfxCpu_CoreMode_halt;
    }
    else
    {
        if (dbgsr.B.HALT == (uint32)IfxCpu_DBGST_HALT_run)
        {                       /*CPU is in DBG RUNNING mode now check PMCSR status */
            volatile Ifx_SCU_PMCSR *pmcsr_val;

            pmcsr_val = &MODULE_SCU.PMCSR[index];

            if (pmcsr_val->B.PMST == (uint32)IfxCpu_PMCSR_PMST_normalMode)
            {                   /*Cpu is in normal run mode */
                cpuMode = IfxCpu_CoreMode_run;
            }
            else
            {                   /*Cpu is not in run mode */
                if (pmcsr_val->B.PMST == (uint32)IfxCpu_PMCSR_PMST_idleMode)
                {               /*Cpu is in idle mode */
                    cpuMode = IfxCpu_CoreMode_idle;
                }
            }
        }
        else
        {
            cpuMode = IfxCpu_CoreMode_unknown;
        }
    }

    return cpuMode;
}


IfxCpu_ResourceCpu IfxCpu_getIndex(Ifx_CPU *cpu)
{
    IfxCpu_ResourceCpu result;
    uint32             index;
    result = IfxCpu_ResourceCpu_none;

    for (index = 0; index < IFXCPU_NUM_MODULES; index++)
    {
        if (IfxCpu_cfg_indexMap[index].module == cpu)
        {
            result = (IfxCpu_ResourceCpu)IfxCpu_cfg_indexMap[index].index;
            break;
        }
    }

    return result;
}


uint32 IfxCpu_getRandomValue(uint32 *seed)
{
    /*************************************************************************
     * the choice of a and m is important for a long period of the LCG
     * with a =  279470273 and
     *       m = 4294967291
     * a maximum period of 2^32-5 is given
     * values for a:
     * 0x5EB0A82F = 1588635695
     * 0x48E7211F = 1223106847
     * 0x10a860c1 =  279470273
     ***************************************************************************/
    uint32 x = *seed;

    /* a seed of 0 is not allowed, and therefore will be changed to a valid value */
    if (x == 0)
    {
        x = 42;
    }

    uint32 a = 0x10a860c1;  // 279470273
    uint32 m = 0xfffffffb;  // 4294967291
    uint32 result;

    //__asm(a,m,x,tmp1,tmp2              );
    //EhEl = a * x;
    //result = e14 %  m;
    // %0 result
    // %1 a
    // %2 x
    // %3 m
    result = IfxCpu_getRandomVal(a, x, m);

    *seed  = result; // to simplify seed passing

    return result;
}


uint32 IfxCpu_getRandomValueWithinRange(uint32 *seed, uint32 min, uint32 max)
{
    uint32 new_value = IfxCpu_getRandomValue(seed);

    /* swap min/max if required */
    if (min > max)
    {
        unsigned swap = max;
        max = min;
        min = swap;
    }

    /* special case */
    if ((min == 0) && (max == 0xffffffff))
    {
        return new_value;
    }

    /* return value within range */
    return (new_value % (max - min + 1)) + min;
}


void IfxCpu_releaseMutex(IfxCpu_mutexLock *lock)
{
    /*Reset the SpinLock*/
    *lock = 0;
}


void IfxCpu_resetSpinLock(IfxCpu_spinLock *lock)
{
    /*Reset the SpinLock*/
    *lock = 0;
}


boolean IfxCpu_setCoreMode(Ifx_CPU *cpu, IfxCpu_CoreMode mode)
{
    uint8              reqslp;
    boolean            retValue;
    IfxCpu_ResourceCpu index = IfxCpu_getIndex(cpu);

    /*Modes such as HALT, SLEEP and STBY are not handled at CPU level */
    retValue = ((mode == IfxCpu_CoreMode_halt) || (mode == IfxCpu_CoreMode_sleep)
                || (mode == IfxCpu_CoreMode_stby)) ? FALSE : TRUE;

    reqslp = (mode == IfxCpu_CoreMode_idle) ? IfxScu_PMCSR_REQSLP_Idle : IfxScu_PMCSR_REQSLP_Run;

    if (retValue == TRUE)
    {
        /*Check if the same core is requesting to change the core run mode */
        if (IfxCpu_getCoreIndex() != index)
        {                       /*Request is for the other core */
            /*To access PMCSR of other CPUs handle the safety EndInit protection */
            uint16 safetyWdtPw = IfxScuWdt_getSafetyWatchdogPassword();
            IfxScuWdt_clearSafetyEndinit(safetyWdtPw);
            MODULE_SCU.PMCSR[(uint32)IfxCpu_getIndex(cpu)].B.REQSLP = reqslp;
            IfxScuWdt_setSafetyEndinit(safetyWdtPw);

            cpu->DBGSR.B.HALT = 2; /*reset the HALT bit, if it is already done it is no harm in writing again */
        }
        else
        {                          /*Request is for self, this request normally only for halt, otherwise the core is already running anyway! */
            /*To access PMCSR of self handle the cpu EndInit protection */
            uint16 cpuWdtPw = IfxScuWdt_getCpuWatchdogPassword();
            IfxScuWdt_clearCpuEndinit(cpuWdtPw);
            MODULE_SCU.PMCSR[(uint32)index].B.REQSLP = reqslp;
            IfxScuWdt_setCpuEndinit(cpuWdtPw);
        }
    }

    return retValue;
}


boolean IfxCpu_setProgramCounter(Ifx_CPU *cpu, uint32 programCounter)
{
    boolean retVal = TRUE;

    if (cpu == IfxCpu_getAddress(IfxCpu_getCoreIndex()))
    {
        retVal = FALSE;
    }
    else
    {
        cpu->PC.B.PC = programCounter >> 1;
    }

    return retVal;
}


boolean IfxCpu_setSpinLock(IfxCpu_spinLock *lock, uint32 timeoutCount)
{
    boolean         retVal;
    volatile uint32 spinLockVal;

    retVal = FALSE;

    do
    {
        spinLockVal = 1UL;
        spinLockVal =
            (uint32)__cmpAndSwap(((unsigned int *)lock), spinLockVal, 0);

        /* Check if the SpinLock WAS set before the attempt to acquire spinlock */
        if (spinLockVal == 0)
        {
            retVal = TRUE;
        }
        else
        {
            timeoutCount--;
        }
    } while ((retVal == FALSE) && (timeoutCount > 0));

    return retVal;
}


boolean IfxCpu_startCore(Ifx_CPU *cpu, uint32 programCounter)
{
    boolean retVal = TRUE;

    /* Set the PC for Core 1 */
    retVal &= IfxCpu_setProgramCounter(cpu, programCounter);
    /* Get the mode for Core 1 and set it to RUNNING */

    /* Core not running already */
    if (IfxCpu_getCoreMode(cpu) == IfxCpu_CoreMode_halt)
    {
        retVal &= IfxCpu_setCoreMode(cpu, IfxCpu_CoreMode_run);
    }

    return retVal;
}


boolean IfxCpu_waitEvent(IfxCpu_syncEvent *event, uint32 timeoutMilliSec)
{
    volatile uint32 *sync          = (volatile uint32 *)IFXCPU_GLB_ADDR_DSPR(__mfcr(CPU_CORE_ID), event);

    boolean          errorcnt      = 0U;
    /* Divide with 1000, gives the count value equivalent to milliseconds */
    uint32           stmCount      = (uint32)((IfxScuCcu_getStmFrequency() / 1000) * timeoutMilliSec);
    uint32           stmCountBegin = STM0_TIM0.U;

    while ((*sync & IFXCPU_CFG_ALLCORE_DONE) != IFXCPU_CFG_ALLCORE_DONE)
    {
        __nop();

        if ((uint32)(STM0_TIM0.U - stmCountBegin) >= stmCount)
        {
            errorcnt = 1;
            break;
        }

        /* There is no need to check overflow of the STM timer.
         * When counter after overflow subtracted with counter before overflow,
         * the subtraction result will be as expected, as long as both are unsigned 32 bits
         * eg: stmCountBegin= 0xFFFFFFFE (before overflow)
         *     stmCountNow = 0x00000002 (before overflow)
         *     diff= stmCountNow - stmCountBegin = 4 as expected.*/
    }

    return errorcnt;
}


void IfxCpu_emitEvent(IfxCpu_syncEvent *event)
{
    Ifx__imaskldmst(event, 1, __mfcr(CPU_CORE_ID), 1);
}
