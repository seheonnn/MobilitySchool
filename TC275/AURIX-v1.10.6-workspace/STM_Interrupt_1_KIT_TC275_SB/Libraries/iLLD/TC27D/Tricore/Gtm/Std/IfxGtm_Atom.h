/**
 * \file IfxGtm_Atom.h
 * \brief GTM  basic functionality
 * \ingroup IfxLld_Gtm
 *
 * \version iLLD_1_0_1_12_0
 * \copyright Copyright (c) 2020 Infineon Technologies AG. All rights reserved.
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
 *
 * \defgroup IfxLld_Gtm_Std_Atom Atom Basic Functionality
 * \ingroup IfxLld_Gtm_Std
 * \defgroup IfxLld_Gtm_Std_Atom_Enumerations ATOM Enumerations
 * \ingroup IfxLld_Gtm_Std_Atom
 * \defgroup IfxLld_Gtm_Std_Atom_Channel_Functions ATOM Channel Functions
 * \ingroup IfxLld_Gtm_Std_Atom
 * \defgroup IfxLld_Gtm_Std_Atom_AGC_Functions ATOM AGC Functions
 * \ingroup IfxLld_Gtm_Std_Atom
 */

#ifndef IFXGTM_ATOM_H
#define IFXGTM_ATOM_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxGtm_cfg.h"
#include "IfxGtm.h"
#include "IfxGtm_Tbu.h"
#include "Src/Std/IfxSrc.h"
#include "IfxGtm_Cmu.h"
#include "stddef.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Gtm_Std_Atom_Enumerations
 * \{ */
/** \brief Reset source for channel counter CN0
 */
typedef enum
{
    IfxGtm_Atom_Ch_OutputTrigger_forward  = 0, /**< \brief Forward the trigger from the previous channel */
    IfxGtm_Atom_Ch_OutputTrigger_generate = 1  /**< \brief Generate the trigger from the current channel */
} IfxGtm_Atom_Ch_OutputTrigger;

/** \brief Reset event for channel counter CN0
 */
typedef enum
{
    IfxGtm_Atom_Ch_ResetEvent_onCm0     = 0,
    IfxGtm_Atom_Ch_ResetEvent_onTrigger = 1
} IfxGtm_Atom_Ch_ResetEvent;

/** \brief Enum for ATOM mode
 */
typedef enum
{
    IfxGtm_Atom_Mode_outputImmediate,
    IfxGtm_Atom_Mode_outputCompare,
    IfxGtm_Atom_Mode_outputPwm,
    IfxGtm_Atom_Mode_outputSerial
} IfxGtm_Atom_Mode;

/** \} */

/** \brief Enable/disable of Aru Input to ATOM channel
 */
typedef enum
{
    IfxGtm_Atom_AruInput_disabled = 0,  /**< \brief ARU input disabled */
    IfxGtm_Atom_AruInput_enabled  = 1   /**< \brief ARU input enabled */
} IfxGtm_Atom_AruInput;

/** \brief Match Compare control modes
 */
typedef enum
{
    IfxGtm_Atom_SomcControl_compareBoth     = 0,  /**< \brief compare CCU0 and CCU1 in parallel */
    IfxGtm_Atom_SomcControl_compareBoth1    = 1,  /**< \brief compare CCU0 and CCU1 in parallel */
    IfxGtm_Atom_SomcControl_ccu0Ts0         = 2,  /**< \brief compare CCU0 against TS0 */
    IfxGtm_Atom_SomcControl_ccu1Ts12        = 3,  /**< \brief compare only CCU1 against TS1 or TS2 */
    IfxGtm_Atom_SomcControl_ccu0ccu1Ts0     = 4,  /**< \brief compare CCU0 then CCU1, use TS0 */
    IfxGtm_Atom_SomcControl_ccu0ccu1Ts12    = 5,  /**< \brief compare CCU0 then CCU1. Use TS1 or TS2 */
    IfxGtm_Atom_SomcControl_ccu0Ts0ccu1Ts12 = 6,  /**< \brief compare CCU0 with TS0 then CCU1 with TS1 or TS2 */
    IfxGtm_Atom_SomcControl_cancelCompare   = 7   /**< \brief Cancel pending compare events */
} IfxGtm_Atom_SomcControl;

/** \brief SOMC signal level Control
 */
typedef enum
{
    IfxGtm_Atom_SomcSignalLevelControl_noChange = 0,  /**< \brief no signal level change at output */
    IfxGtm_Atom_SomcSignalLevelControl_sl0out1  = 1,  /**< \brief SL= 0 -> Out=1; SL=1->Out=0 */
    IfxGtm_Atom_SomcSignalLevelControl_sl0out0  = 2,  /**< \brief SL=0->Out=0; SL=1->Out=1 */
    IfxGtm_Atom_SomcSignalLevelControl_toggle   = 3   /**< \brief toggle the output signal level */
} IfxGtm_Atom_SomcSignalLevelControl;

/** \addtogroup IfxLld_Gtm_Std_Atom_Channel_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the base addredd of selected Atom channel
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return Pointer to channel base address
 */
IFX_INLINE Ifx_GTM_ATOM_CH *IfxGtm_Atom_Ch_getChannelPointer(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Sets the compare 0 and 1 shadow values
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param shadowZero Compare zero shadow value
 * \param shadowOne Compare one shadow value
 * \return None
 */
IFX_INLINE void IfxGtm_Atom_Ch_setCompareShadow(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 shadowZero, uint32 shadowOne);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Clears the channel One notification
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_clearOneNotification(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Clears the channel Zero notification
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_clearZeroNotification(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param clock Clock source
 * \param activeState Active State
 * \param resetEvent Channel reset event
 * \param trigger Channel trigger output mode
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_configurePwmMode(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, IfxGtm_Cmu_Clk clock, Ifx_ActiveState activeState, IfxGtm_Atom_Ch_ResetEvent resetEvent, IfxGtm_Atom_Ch_OutputTrigger trigger);

/** \brief Returns the ATOM channel input clock frequency in Hz
 * \param gtm Pointer to GTM module
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return ATOM channel input clock frequency in Hz
 */
IFX_EXTERN float32 IfxGtm_Atom_Ch_getClockFrequency(Ifx_GTM *gtm, Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the channel clock source
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return The clock source
 */
IFX_EXTERN IfxGtm_Cmu_Clk IfxGtm_Atom_Ch_getClockSource(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the compare one value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return compare one value
 */
IFX_EXTERN uint32 IfxGtm_Atom_Ch_getCompareOne(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the compare one pointer
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return compare one pointer
 */
IFX_EXTERN volatile uint32 *IfxGtm_Atom_Ch_getCompareOnePointer(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the compare zero value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return compare zero value
 */
IFX_EXTERN uint32 IfxGtm_Atom_Ch_getCompareZero(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the compare zero pointer
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return compare zero pointer
 */
IFX_EXTERN volatile uint32 *IfxGtm_Atom_Ch_getCompareZeroPointer(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Gets the ATOM output level
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return TRUE the output is high, FALSE the output is low
 */
IFX_EXTERN boolean IfxGtm_Atom_Ch_getOutputLevel(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns a pointer to the ATOM channel SRC
 * \param gtm Pointer to GTM module
 * \param atom Specifies the atom object
 * \param channel Channel index
 * \return Pointer to the TOM channel SRC
 */
IFX_EXTERN volatile Ifx_SRC_SRCR *IfxGtm_Atom_Ch_getSrcPointer(Ifx_GTM *gtm, IfxGtm_Atom atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the Timer pointer
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return Timer pointer
 */
IFX_EXTERN volatile uint32 *IfxGtm_Atom_Ch_getTimerPointer(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the status of channel One notification
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return Status of channel One notification
 */
IFX_EXTERN boolean IfxGtm_Atom_Ch_isOneNotification(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the status of channel Zero notification
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return Status of channel Zero notification
 */
IFX_EXTERN boolean IfxGtm_Atom_Ch_isZeroNotification(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Raises the interrupt for Compare 1
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_raiseInterruptOne(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Raises the interrupt for Compare 0
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_raiseInterruptZero(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Sets the channel clock source
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param clock Channel clock source
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setClockSource(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, IfxGtm_Cmu_Clk clock);

/** \brief Sets the compare 0 and 1 values
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param compareZero Compare zero value
 * \param compareOne Compare one value
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setCompare(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 compareZero, uint32 compareOne);

/** \brief Sets the compare 1 value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param compareOne Compare one value
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setCompareOne(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 compareOne);

/** \brief Sets the compare 1 shadow value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param shadowOne Compare one shadow value
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setCompareOneShadow(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 shadowOne);

/** \brief Sets the compare 0 value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param compareZero Compare zero value
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setCompareZero(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 compareZero);

/** \brief Sets the compare 0 shadow value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param shadowZero Compare zero shadow value
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setCompareZeroShadow(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 shadowZero);

/** \brief Sets the counter value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param value Counter value
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setCounterValue(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 value);

/** \brief set the Atom operating mode
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param mode Atom operating mode
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setMode(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, IfxGtm_Atom_Mode mode);

/** \brief Sets the channel notification
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param mode Interrupt mode
 * \param interruptOnCompareZero If TRUE, an interrupt is generated on compare 0, else no interrupt is generated
 * \param interruptOnCompareOne If TRUE, an interrupt is generated on compare 1, else no interrupt is generated
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setNotification(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, IfxGtm_IrqMode mode, boolean interruptOnCompareZero, boolean interruptOnCompareOne);

/** \brief Enable/disable the one shot mode
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param enabled If TRUE, the feature is enabled, else disabled
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setOneShotMode(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, boolean enabled);

/** \brief Sets the channel clock source either from local or from previous channel
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param event Channel reset event
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setResetSource(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, IfxGtm_Atom_Ch_ResetEvent event);

/** \brief Sets the signal level
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param activeState Signal level active state. In case the channel is reset, the output is set to not active. The signal is active between 0 and the leading edge (CM1) and inactive between the leading edge and the trailing edge (CM0).
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setSignalLevel(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, Ifx_ActiveState activeState);

/** \brief Sets the channel trigger output
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \param trigger Channel trigger output mode
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setTriggerOutput(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, IfxGtm_Atom_Ch_OutputTrigger trigger);

/** \brief Get the counter value
 * \param atom pointer to the ATOM instance
 * \param channel channel index of the ATOM
 * \return counter value
 */
IFX_EXTERN uint32 IfxGtm_Atom_Ch_getCounterValue(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \} */

/** \addtogroup IfxLld_Gtm_Std_Atom_AGC_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Sets the channels for update (UPEN)
 * \param agc Pointer to the AGC object
 * \param value value for the channel enable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \return None
 */
IFX_INLINE void IfxGtm_Atom_Agc_setChannelsUpdate(Ifx_GTM_ATOM_AGC *agc, uint32 value);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Builds the register value for the feature enable/disable
 * \param enableMask Mask for the channel feature enable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param disableMask Mask for the channel feature disable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param bitfieldOffset Offset of the channel 0 bitfield in the register
 * \return The register value
 */
IFX_EXTERN uint32 IfxGtm_Atom_Agc_buildFeature(uint16 enableMask, uint16 disableMask, uint8 bitfieldOffset);

/** \brief Builds the register value for the feature enable/disable for a single channel
 * \param channel Channel index
 * \param enabled Enable/ Disable choise of the feature
 * \param bitfieldOffset Offset of the channel 0 bitfield in the register
 * \return The register value
 */
IFX_EXTERN uint32 IfxGtm_Atom_Agc_buildFeatureForChannel(IfxGtm_Atom_Ch channel, boolean enabled, uint8 bitfieldOffset);

/** \brief Enable/disable one channel (ENDIS)
 * \param agc Pointer to the AGC object
 * \param channel Channel index
 * \param enabled Enable/ Disable choise of the feature
 * \param immediate If TRUE, the action is done immediately else, the action is done on AGC trigger (CTRL_TRIG)
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_enableChannel(Ifx_GTM_ATOM_AGC *agc, IfxGtm_Atom_Ch channel, boolean enabled, boolean immediate);

/** \brief Enable/disable one channel output (OUTEN)
 * \param agc Pointer to the AGC object
 * \param channel Channel index
 * \param enabled Enable/ Disable choise of the feature
 * \param immediate If TRUE, the action is done immediately else, the action is done on TGC trigger (CTRL_TRIG)
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_enableChannelOutput(Ifx_GTM_ATOM_AGC *agc, IfxGtm_Atom_Ch channel, boolean enabled, boolean immediate);

/** \brief Enable/disable one channel for update (UPEN)
 * \param agc Pointer to the AGC object
 * \param channel Channel index
 * \param enabled Enable/ Disable choise of the feature
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_enableChannelUpdate(Ifx_GTM_ATOM_AGC *agc, IfxGtm_Atom_Ch channel, boolean enabled);

/** \brief Enable/disable one or more channels (ENDIS)
 * \param agc Pointer to the AGC object
 * \param enableMask Mask for the channel feature enable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param disableMask Mask for the channel feature disable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param immediate If TRUE, the action is done immediately else, the action is done on TGC trigger (CTRL_TRIG)
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_enableChannels(Ifx_GTM_ATOM_AGC *agc, uint16 enableMask, uint16 disableMask, boolean immediate);

/** \brief Enable/disable one or more channels output (OUTEN)
 * \param agc Pointer to the TGC object
 * \param enableMask Mask for the channel feature enable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param disableMask Mask for the channel feature disable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param immediate If TRUE, the action is done immediately else, the action is done on TGC trigger (CTRL_TRIG)
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_enableChannelsOutput(Ifx_GTM_ATOM_AGC *agc, uint16 enableMask, uint16 disableMask, boolean immediate);

/** \brief Enable/disable the TGC channels trigger
 * \param agc Pointer to the AGC object
 * \param enableMask Mask for the channel feature enable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param disableMask Mask for the channel feature disable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_enableChannelsTrigger(Ifx_GTM_ATOM_AGC *agc, uint16 enableMask, uint16 disableMask);

/** \brief Enable/disable one or more channels for update (UPEN)
 * \param agc Pointer to the AGC object
 * \param enableMask Mask for the channel feature enable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param disableMask Mask for the channel feature disable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_enableChannelsUpdate(Ifx_GTM_ATOM_AGC *agc, uint16 enableMask, uint16 disableMask);

/** \brief Enable/disable the time base trigger
 * \param agc Pointer to the AGC object
 * \param enabled If TRUE, the trigger is enabled else disabled
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_enableTimeTrigger(Ifx_GTM_ATOM_AGC *agc, boolean enabled);

/** \brief Reset one or more channels
 * \param agc Pointer to the AGC object
 * \param resetMask Mask for the channel reset (bit 0: Channel 0, bit 1: channel 1, ...)
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_resetChannels(Ifx_GTM_ATOM_AGC *agc, uint32 resetMask);

/** \brief Enable/disable one channel for update (FUPD)
 * \param agc Pointer to the AGC object
 * \param channel Channel index
 * \param enabled Enable/ Disable choise of the feature
 * \param resetEnabled Enable/ Disable reset choise of the feature
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_setChannelForceUpdate(Ifx_GTM_ATOM_AGC *agc, IfxGtm_Atom_Ch channel, boolean enabled, boolean resetEnabled);

/** \brief Enable/disable one or more channels for the force update feature (FUPD)
 * \param agc Pointer to the AGC object
 * \param enableMask Mask for the channel feature enable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param disableMask Mask for the channel feature disable (bit 0: Channel 0, bit 1: channel 1, ...)
 * \param resetEnableMask Mask for the enabled channels counter reset on force update (bit 0: Channel 0, bit 1: channel 1, ...) Channel 0, bit 1: channel 1, ...)
 * \param resetDisableMask Mask for the disabled channels with no counter reset on force update (bit 0: Channel 0, bit 1: channel 1, ...)
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_setChannelsForceUpdate(Ifx_GTM_ATOM_AGC *agc, uint16 enableMask, uint16 disableMask, uint16 resetEnableMask, uint16 resetDisableMask);

/** \brief Sets the trigger time base and time base value
 * \param agc Pointer to the AGC object
 * \param base Time base used for comparison
 * \param value Compare value that raise the trigger
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_setTimeTrigger(Ifx_GTM_ATOM_AGC *agc, IfxGtm_Tbu_Ts base, uint32 value);

/** \brief Raise the trigger for the channel enable/disable settings,  output enable settings, and force update event (CTRL_TRIG)
 * \param agc Pointer to the AGC object
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Agc_trigger(Ifx_GTM_ATOM_AGC *agc);

/** \} */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief enable/disable ARU input for the ATOM channel specified.
 * \param atom pointer to the ATOM instance
 * \param channel index of ATOM channel
 * \param enabled ARU enable status
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setAruInput(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, boolean enabled);

/** \brief sets the SOMC control bits for the specified ATOM channel
 * \param atom pointer to ATOM instance
 * \param channel ATOM channel index
 * \param control SOMC control mode enum
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setSomcControl(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, IfxGtm_Atom_SomcControl control);

/** \brief sets the SL control for SOMC mode.
 * \param atom pointer to the ATOM instance
 * \param channel index of ATOM channel
 * \param ctrl SIgnal level control
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setSomcSignalLevelControl(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, IfxGtm_Atom_SomcSignalLevelControl ctrl);

/** \brief set the ARU read address 0
 * \param atom pointer to ATOM instance
 * \param channel ATOM channel index
 * \param address ARU read address 0
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setAruReadAddress0(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 address);

/** \brief set the ARU read address 1
 * \param atom pointer to ATOM instance
 * \param channel ATOM channel index
 * \param address ARU read address 1
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Ch_setAruReadAddress1(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 address);

/** \brief Returns the shadow zero value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return shadow zero value
 */
IFX_EXTERN uint32 IfxGtm_Atom_getShadowZero(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the shadow zero pointer
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return shadow zero value
 */
IFX_EXTERN volatile uint32 *IfxGtm_Atom_getShadowZeroPointer(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the shadow one value
 * \param atom Pointer to the ATOM object
 * \param channel Channel index
 * \return shadow one value
 */
IFX_EXTERN uint32 IfxGtm_Atom_getShadowOne(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/** \brief Returns the shadow One pointer
 * \param atom Pointer to the ATOM object
 * \param channel channel index
 * \return shadow One pointer
 */
IFX_EXTERN volatile uint32 *IfxGtm_Atom_getShadowOnePointer(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel);

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE Ifx_GTM_ATOM_CH *IfxGtm_Atom_Ch_getChannelPointer(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel)
{
    return (Ifx_GTM_ATOM_CH *)((uint32)&atom->CH0.RDADDR.U + 0x80 * channel);
}


IFX_INLINE void IfxGtm_Atom_Ch_setCompareShadow(Ifx_GTM_ATOM *atom, IfxGtm_Atom_Ch channel, uint32 shadowZero, uint32 shadowOne)
{
    Ifx_GTM_ATOM_CH *atomCh = IfxGtm_Atom_Ch_getChannelPointer(atom, channel);

    atomCh->SR0.U = shadowZero; // TK: replaced .B access to optimize runtime
    atomCh->SR1.U = shadowOne;
}


IFX_INLINE void IfxGtm_Atom_Agc_setChannelsUpdate(Ifx_GTM_ATOM_AGC *agc, uint32 value)
{
    agc->GLB_CTRL.U = value;
}


#endif /* IFXGTM_ATOM_H */
