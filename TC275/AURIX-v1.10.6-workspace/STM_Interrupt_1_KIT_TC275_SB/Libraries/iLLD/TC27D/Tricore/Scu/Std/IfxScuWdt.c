/**
 * \file IfxScuWdt.c
 * \brief SCU  basic functionality
 *
 * \version iLLD_1_0_1_12_0
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
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

#include "IfxScuWdt.h"
#include "Cpu/Std/IfxCpu.h"

/******************************************************************************/
/*----------------------------------Macros------------------------------------*/
/******************************************************************************/

/** \brief Reset password of watchdog module.
 */
#define IFXSCUWDT_RESET_PASSWORD (0x3CU)

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxScuWdt_changeCpuWatchdogPassword(uint16 password, uint16 newPassword)
{
    Ifx_SCU_WDTCPU     *watchdog = &MODULE_SCU.WDTCPU[IfxCpu_getCoreIndex()];

    /* Read Config_0 register */
    Ifx_SCU_WDTCPU_CON0 wdt_con0;
    wdt_con0.U = watchdog->CON0.U;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK     = 0;
        wdt_con0.B.PW      = password;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        watchdog->CON0.U = wdt_con0.U;
    }

    /* Set new Password, ENDINT and LCK bit in Config_0 register */
    wdt_con0.B.ENDINIT = 1;
    wdt_con0.B.LCK     = 1;
    wdt_con0.B.PW      = newPassword;
    watchdog->CON0.U   = wdt_con0.U;

    /* read back ENDINIT and wait until it has been set */
    while (watchdog->CON0.B.ENDINIT == 0)
    {}
}


void IfxScuWdt_changeCpuWatchdogReload(uint16 password, uint16 reload)
{
    /* Select CPU Watchdog based on Core Id */
    uint32              coreId = IfxCpu_getCoreIndex();
    Ifx_SCU_WDTCPU     *wdt    = &MODULE_SCU.WDTCPU[coreId];

    /* Read Config_0 register */
    Ifx_SCU_WDTCPU_CON0 wdt_con0;
    wdt_con0.U = wdt->CON0.U;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK     = 0;
        wdt_con0.B.PW      = password;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        wdt->CON0.U = wdt_con0.U;
    }

    /* Set new Reload value, set ENDINT and LCK bit in Config_0 register */
    wdt_con0.B.ENDINIT = 1;
    wdt_con0.B.LCK     = 1;
    wdt_con0.B.REL     = reload;
    wdt->CON0.U        = wdt_con0.U;

    /* read back ENDINIT and wait until it has been set */
    while (wdt->CON0.B.ENDINIT == 0)
    {}
}


void IfxScuWdt_changeSafetyWatchdogPassword(uint16 password, uint16 newPassword)
{
    Ifx_SCU_WDTS     *watchdog = &MODULE_SCU.WDTS;

    /* Read Config_0 register */
    Ifx_SCU_WDTS_CON0 wdt_con0;
    wdt_con0.U = watchdog->CON0.U;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK     = 0;
        wdt_con0.B.PW      = password;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        watchdog->CON0.U = wdt_con0.U;
    }

    /* Set new Password, ENDINT and LCK bit in Config_0 register */
    wdt_con0.B.ENDINIT = 1;
    wdt_con0.B.LCK     = 1;
    wdt_con0.B.PW      = newPassword;
    watchdog->CON0.U   = wdt_con0.U;

    /* read back ENDINIT and wait until it has been set */
    while (watchdog->CON0.B.ENDINIT == 0)
    {}
}


void IfxScuWdt_changeSafetyWatchdogReload(uint16 password, uint16 reload)
{
    /* Initialize pointer to Safety Watchdog */
    Ifx_SCU_WDTS     *wdt = &MODULE_SCU.WDTS;

    /* Read Config_0 register */
    Ifx_SCU_WDTS_CON0 wdt_con0;
    wdt_con0.U = wdt->CON0.U;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK     = 0;
        wdt_con0.B.PW      = password;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        wdt->CON0.U = wdt_con0.U;
    }

    /* Set new Reload value, set ENDINT and LCK bit in Config_0 register */
    wdt_con0.B.ENDINIT = 1;
    wdt_con0.B.LCK     = 1;
    wdt_con0.B.REL     = reload;
    wdt->CON0.U        = wdt_con0.U;

    /* read back ENDINIT and wait until it has been set */
    while (wdt->CON0.B.ENDINIT == 0)
    {}
}


void IfxScuWdt_clearCpuEndinit(uint16 password)
{
    IfxScuWdt_clearCpuEndinitInline(&MODULE_SCU.WDTCPU[IfxCpu_getCoreIndex()], password);
}


void IfxScuWdt_clearSafetyEndinit(uint16 password)
{
    IfxScuWdt_clearSafetyEndinitInline(password);
}


void IfxScuWdt_disableCpuWatchdog(uint16 password)
{
    /* Select CPU Watchdog based on Core Id */
    uint32          coreId = (uint32)IfxCpu_getCoreIndex();
    Ifx_SCU_WDTCPU *wdt    = &MODULE_SCU.WDTCPU[coreId];

    IfxScuWdt_clearCpuEndinitInline(wdt, password);
    wdt->CON1.B.DR = 1;         //Set DR bit in Config_1 register
    IfxScuWdt_setCpuEndinitInline(wdt, password);
}


void IfxScuWdt_disableSafetyWatchdog(uint16 password)
{
    IfxScuWdt_clearSafetyEndinitInline(password);
    SCU_WDTS_CON1.B.DR = 1;     //Set DR bit in Config_1 register
    IfxScuWdt_setSafetyEndinitInline(password);
}


void IfxScuWdt_enableCpuWatchdog(uint16 password)
{
    /* Select CPU Watchdog based on Core Id */
    uint32          coreId = (uint32)IfxCpu_getCoreIndex();
    Ifx_SCU_WDTCPU *wdt    = &MODULE_SCU.WDTCPU[coreId];

    IfxScuWdt_clearCpuEndinitInline(wdt, password);
    wdt->CON1.B.DR = 0;         //Clear DR bit in Config_1 register
    IfxScuWdt_setCpuEndinitInline(wdt, password);
}


void IfxScuWdt_enableSafetyWatchdog(uint16 password)
{
    IfxScuWdt_clearSafetyEndinitInline(password);
    SCU_WDTS_CON1.B.DR = 0;     //Clear DR bit in Config_1 register
    IfxScuWdt_setSafetyEndinitInline(password);
}


uint16 IfxScuWdt_getCpuWatchdogPassword(void)
{
    return IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[IfxCpu_getCoreIndex()]);
}


boolean IfxScuWdt_getCpuWatchdogEndInit(void)
{
    return (boolean)IfxScuWdt_getCpuWatchdogEndInitInline(&MODULE_SCU.WDTCPU[IfxCpu_getCoreIndex()]);
}


uint16 IfxScuWdt_getSafetyWatchdogPassword(void)
{
    return IfxScuWdt_getSafetyWatchdogPasswordInline();
}


void IfxScuWdt_initConfig(IfxScuWdt_Config *config)
{
    config->password                      = IFXSCUWDT_RESET_PASSWORD;
    config->reload                        = 0xFFFC;
    config->inputFrequency                = IfxScu_WDTCON1_IR_divBy16384;
    config->disableWatchdog               = FALSE;
    config->enableSmuRestriction          = FALSE;
    config->enableAutomaticPasswordChange = FALSE;
    config->enableTimerCheck              = FALSE;
    config->enableTimerCheckTolerance     = FALSE;
    config->clrInternalResetFlag          = FALSE;
}


void IfxScuWdt_initCpuWatchdog(Ifx_SCU_WDTCPU *wdt, const IfxScuWdt_Config *config)
{
    Ifx_SCU_WDTCPU_CON0 wdt_con0;
    Ifx_SCU_WDTCPU_CON1 wdt_con1;

    /* Read Config_0 register and clear wdt_con1 variable */
    wdt_con0.U = wdt->CON0.U;
    wdt_con1.U = 0;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK     = 0;
        wdt_con0.B.PW     ^= 0x003F;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        wdt->CON0.U = wdt_con0.U;
    }

    /* Initialize CON0 register, with modify access, with user defined parameters
     * Clear ENDINT bit to unprotect CON1 register for initialization
     * see Table 3 (Modify Access Bit Pattern Requirements) */
    wdt_con0.B.ENDINIT = 0;
    wdt_con0.B.LCK     = 1;
    wdt_con0.B.PW      = config->password; //user defined password
    wdt_con0.B.REL     = config->reload;   //user defined reload value

    /* Modify access ready - write WDT_CON0 register */
    wdt->CON0.U = wdt_con0.U;

    /* read back ENDINIT and wait until it has been cleared */
    while (wdt->CON0.B.ENDINIT == 1)
    {}

    /* Initialize CON1 register */
    switch (config->inputFrequency)
    {
    case IfxScu_WDTCON1_IR_divBy16384:
        wdt_con1.B.IR0 = 0;
        wdt_con1.B.IR1 = 0;
        break;
    case IfxScu_WDTCON1_IR_divBy256:
        wdt_con1.B.IR0 = 1;
        wdt_con1.B.IR1 = 0;
        break;
    case IfxScu_WDTCON1_IR_divBy64:
        wdt_con1.B.IR0 = 0;
        wdt_con1.B.IR1 = 1;
        break;
    }

    wdt_con1.B.DR   = config->disableWatchdog ? 1 : 0;
    wdt_con1.B.UR   = config->enableSmuRestriction ? 1 : 0;
    wdt_con1.B.PAR  = config->enableAutomaticPasswordChange ? 1 : 0;
    wdt_con1.B.TCR  = config->enableTimerCheck ? 1 : 0;
    wdt_con1.B.TCTR = config->enableTimerCheckTolerance ? 1 : 0;

    /* Finally write CON1 with user defined configuration */
    wdt->CON1.U = wdt_con1.U;

    /* Initialization finished - set CPU ENDINIT protection */
    IfxScuWdt_setCpuEndinit(config->password);
}


void IfxScuWdt_initSafetyWatchdog(Ifx_SCU_WDTS *wdt, const IfxScuWdt_Config *config)
{
    Ifx_SCU_WDTS_CON0 wdt_con0;
    Ifx_SCU_WDTS_CON1 wdt_con1;

    /* Read Config_0 register and clear wdt_con1 variable */
    wdt_con0.U = wdt->CON0.U;
    wdt_con1.U = 0;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK     = 0;
        wdt_con0.B.PW     ^= 0x003F;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        wdt->CON0.U = wdt_con0.U;
    }

    /* Initialize CON0 register, with modify access, with user defined parameters
     * Clear ENDINT bit to unprotect CON1 register for initialization
     * see Table 3 (Modify Access Bit Pattern Requirements) */
    wdt_con0.B.ENDINIT = 0;
    wdt_con0.B.LCK     = 1;
    wdt_con0.B.PW      = config->password; //user defined password
    wdt_con0.B.REL     = config->reload;   //user defined reload value

    /* Modify access ready - write WDT_CON0 register */
    wdt->CON0.U = wdt_con0.U;

    /* read back ENDINIT and wait until it has been cleared */
    while (wdt->CON0.B.ENDINIT == 1)
    {}

    /* Initialize CON1 register */
    switch (config->inputFrequency)
    {
    case IfxScu_WDTCON1_IR_divBy16384:
        wdt_con1.B.IR0 = 0;
        wdt_con1.B.IR1 = 0;
        break;
    case IfxScu_WDTCON1_IR_divBy256:
        wdt_con1.B.IR0 = 1;
        wdt_con1.B.IR1 = 0;
        break;
    case IfxScu_WDTCON1_IR_divBy64:
        wdt_con1.B.IR0 = 0;
        wdt_con1.B.IR1 = 1;
        break;
    }

    wdt_con1.B.DR     = config->disableWatchdog ? 1 : 0;
    wdt_con1.B.UR     = config->enableSmuRestriction ? 1 : 0;
    wdt_con1.B.PAR    = config->enableAutomaticPasswordChange ? 1 : 0;
    wdt_con1.B.TCR    = config->enableTimerCheck ? 1 : 0;
    wdt_con1.B.TCTR   = config->enableTimerCheckTolerance ? 1 : 0;
    wdt_con1.B.CLRIRF = config->clrInternalResetFlag ? 0 : 1;

    /* Finally write CON1 with user defined configuration */
    wdt->CON1.U = wdt_con1.U;

    /* Initialization finished - set Safety ENDINIT protection */
    IfxScuWdt_setSafetyEndinit(config->password);
}


void IfxScuWdt_serviceCpuWatchdog(uint16 password)
{
    IfxScuWdt_setCpuEndinit(password);
}


void IfxScuWdt_serviceSafetyWatchdog(uint16 password)
{
    IfxScuWdt_setSafetyEndinit(password);
}


void IfxScuWdt_setCpuEndinit(uint16 password)
{
    IfxScuWdt_setCpuEndinitInline(&MODULE_SCU.WDTCPU[IfxCpu_getCoreIndex()], password);
}


void IfxScuWdt_setSafetyEndinit(uint16 password)
{
    IfxScuWdt_setSafetyEndinitInline(password);
}


boolean IfxScuWdt_enableWatchdogWithDebugger(void)
{
    boolean          status = 0, oenEnabled = 0, watchdogEnabled = 0;
    uint32           ostateValue;

    volatile uint32 *oecPtr    = (volatile uint32 *)0xF0000478;
    volatile uint32 *ostatePtr = (volatile uint32 *)0xF0000480;
    volatile uint32 *ocntrlPtr = (volatile uint32 *)0xF000047C;

    /* read OSTATE.OEN */
    ostateValue = *ostatePtr;
    oenEnabled  = (ostateValue & 0x00000001);

    if (!oenEnabled)
    {
        /* enable the debug interface (OSTATE.OEN )if it is not already enabled */
        /* pattern for enabling OSTATE.OEN */
        *oecPtr = 0xA1;
        *oecPtr = 0x5E;
        *oecPtr = 0xA1;
        *oecPtr = 0x5E;

        /* read OSTATE.OEN again*/
        ostateValue = *ostatePtr;
        oenEnabled  = (ostateValue & 0x00000001);
    }

    if (oenEnabled)
    {
        /* set watchdog suspend bit in OSTATE reg, by writing OCNTRL.WDTSUS and OCNTRL.WDTSUS_P together */
        *ocntrlPtr = 0x00003000;
    }
    else
    {
        status = 1;
    }

    IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, oenEnabled == 1);

    /* read OSTATE.WDTSUS */
    ostateValue     = *ostatePtr;
    watchdogEnabled = (ostateValue & 0x00000080);

    if (!watchdogEnabled)
    {
        status = 1;
    }

    IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, watchdogEnabled == 1);

    return status;
}
