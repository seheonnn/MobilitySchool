/**
 * \file IfxDsadc_Dsadc.c
 * \brief DSADC DSADC details
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
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxDsadc_Dsadc.h"

/******************************************************************************/
/*-----------------------Private Function Prototypes--------------------------*/
/******************************************************************************/

/** \brief calculate division factor
 * \param sourceFreq Source frequency
 * \param targetFreq Target frequency
 * \return division factor
 */
IFX_STATIC sint32 IfxDsadc_Dsadc_calcDIVx(float32 sourceFreq, float32 *targetFreq);

/** \brief Initialises the auxilary filter
 * \param channel Pointer to the DSADC channel handle
 * \param config pointer to the DSADC fir auxilary filter configuration
 * \return None
 */
IFX_STATIC void IfxDsadc_Dsadc_initAuxFilter(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_AuxFilterConfig *config);

/** \brief Initialises the comb filter
 * \param channel Pointer to the DSADC channel handle
 * \param config pointer to the DSADC comb filter configuration
 * \return None
 */
IFX_STATIC void IfxDsadc_Dsadc_initCombFilter(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_CombFilterConfig *config);

/** \brief Initialises the demodulator
 * \param channel Pointer to the DSADC channel handle
 * \param config pointer to the DSADC demodulator configuration
 * \return None
 */
IFX_STATIC void IfxDsadc_Dsadc_initDemodulator(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_DemodulatorConfig *config);

/** \brief Initialises the fir filter
 * \param channel Pointer to the DSADC channel handle
 * \param config pointer to the DSADC fir filter configuration
 * \return None
 */
IFX_STATIC void IfxDsadc_Dsadc_initFirFilter(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_FirFilterConfig *config);

/** \brief Initialises the integrator
 * \param channel Pointer to the DSADC channel handle
 * \param config pointer to the DSADC fir integrator configuration
 * \return None
 */
IFX_STATIC void IfxDsadc_Dsadc_initIntegrator(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_IntegratorConfig *config);

/** \brief Initialises the modulator
 * \param channel Pointer to the DSADC channel handle
 * \param config pointer to the DSADC modulator configuration
 * \return None
 */
IFX_STATIC void IfxDsadc_Dsadc_initModulator(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_ModulatorConfig *config);

/** \brief Initialises the rectifier
 * \param channel Pointer to the DSADC channel handle
 * \param config pointer to the DSADC fir rectifier configuration
 * \return None
 */
IFX_STATIC void IfxDsadc_Dsadc_initRectifier(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_RectifierConfig *config);

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

IFX_STATIC sint32 IfxDsadc_Dsadc_calcDIVx(float32 sourceFreq, float32 *targetFreq)
{
    float32 bestError = 10e6;
    sint32  bestDiv   = 2, i;

    for (i = 2; i <= 32; i += 2)
    {
        float32 freq  = sourceFreq / i;
        float32 error = __absf(freq - *targetFreq);

        if (__leqf(error, bestError))
        {
            bestError = error;
            bestDiv   = i;

            if (!__neqf(error, 0))
            {
                break;
            }
        }
    }

    *targetFreq = sourceFreq / bestDiv;

    return (bestDiv / 2) - 1;
}


sint16 IfxDsadc_Dsadc_getAuxResult(IfxDsadc_Dsadc_Channel *channel)
{
    return IfxDsadc_getAuxResult(channel->module, channel->channelId);
}


IFX_STATIC void IfxDsadc_Dsadc_initAuxFilter(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_AuxFilterConfig *config)
{
    Ifx_DSADC_CH_FCFGA fcfga;

    fcfga.U                   = 0;

    fcfga.B.CFADF             = config->decimationFactor - 1;
    fcfga.B.CFAC              = config->combFilterType;

    fcfga.B.SRGA              = config->serviceRequest;
    fcfga.B.ESEL              = config->eventSelect;
    fcfga.B.EGT               = config->eventGate;

    fcfga.B.AFSC              = config->combFilterShift;

    (channel->channel)->FCFGA = fcfga;
}


void IfxDsadc_Dsadc_initCarrierGen(IfxDsadc_Dsadc *dsadc, const IfxDsadc_Dsadc_CarrierGenConfig *config)
{
    Ifx_DSADC_CGCFG cgcfg;

    cgcfg.U = 0;

    float32         sourceFreq = IfxDsadc_getModulatorInputClockFreq(dsadc->dsadc);
    float32         targetFreq = config->frequency;
    cgcfg.B.DIVCG       = IfxDsadc_Dsadc_calcDIVx(sourceFreq / (32 * 32), &targetFreq);
    cgcfg.B.SIGPOL      = (config->inverted == FALSE) ? 0 : 1;
    cgcfg.B.BREV        = (config->bitReversed == FALSE) ? 0 : 1;
    cgcfg.B.CGMOD       = config->carrierWaveformMode;

    dsadc->dsadc->CGCFG = cgcfg;

    const IfxDsadc_Cgpwm_Out *pinPos = config->pinPos;

    if (pinPos != NULL_PTR)
    {                           /* Initialise positive carrier pin */
        IfxDsadc_initCgPwmPin(pinPos, config->pinMode, config->pinDriver);
    }

    const IfxDsadc_Cgpwm_Out *pinNeg = config->pinNeg;

    if (pinNeg != NULL_PTR)
    {                           /* Initialise negative carrier pin */
        IfxDsadc_initCgPwmPin(pinNeg, config->pinMode, config->pinDriver);
    }
}


void IfxDsadc_Dsadc_initChannel(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_ChannelConfig *config)
{
    Ifx_DSADC *dsadc = config->module;

    channel->channelId = config->channelId;
    channel->module    = dsadc;
    channel->channel   = (Ifx_DSADC_CH *)&dsadc->CH[config->channelId];

    IfxDsadc_Dsadc_initModulator(channel, &config->modulator);
    IfxDsadc_Dsadc_initDemodulator(channel, &config->demodulator);
    IfxDsadc_Dsadc_initCombFilter(channel, &config->combFilter);
    IfxDsadc_Dsadc_initFirFilter(channel, &config->firFilter);
    IfxDsadc_Dsadc_initIntegrator(channel, &config->integrator);
    IfxDsadc_Dsadc_initAuxFilter(channel, &config->auxFilter);
    IfxDsadc_Dsadc_initRectifier(channel, &config->rectifier);

    const IfxDsadc_Dsadc_ChannelPins *pins = config->channelPins;

    if (pins != NULL_PTR)
    {
        const IfxDsadc_Dsn_In *dsn = pins->dsn;

        if (dsn != NULL_PTR)
        {
            IfxDsadc_initDsnPin(dsn, pins->dsnMode, pins->pinDriver);
        }

        const IfxDsadc_Dsp_In *dsp = pins->dsp;

        if (dsp != NULL_PTR)
        {
            IfxDsadc_initDspPin(dsp, pins->dspMode, pins->pinDriver);
        }

        const IfxDsadc_Cin_In *cin = pins->cin;

        if (cin != NULL_PTR)
        {
            IfxDsadc_initCinPin(cin, pins->cinMode, pins->pinDriver);
        }

        const IfxDsadc_Din_In *din = pins->din;

        if (din != NULL_PTR)
        {
            IfxDsadc_initDinPin(din, pins->dinMode, pins->pinDriver);
        }

        const IfxDsadc_Itr_In *itr = pins->itr;

        if (itr != NULL_PTR)
        {
            IfxDsadc_initItrPin(itr, pins->itrMode, pins->pinDriver);
        }
    }
}


void IfxDsadc_Dsadc_initChannelConfig(IfxDsadc_Dsadc_ChannelConfig *config, IfxDsadc_Dsadc *dsadc)
{
    const IfxDsadc_Dsadc_ChannelConfig IfxDsadc_Dsadc_defaultChannelConfig = {
        .modulator              = {
            .positiveInput      = IfxDsadc_InputConfig_inputPin,
            .negativeInput      = IfxDsadc_InputConfig_referenceGround,
            .inputGain          = IfxDsadc_InputGain_factor1,
            .inputPin           = IfxDsadc_InputPin_a,
            .modulatorClockFreq = 10.0e6,
            .commonModeVoltage  = IfxDsadc_CommonModeVoltage_c,
        },
        .demodulator            = {
            .inputDataSource    = IfxDsadc_InputDataSource_onChipStandAlone,
            .triggerInput       = IfxDsadc_TriggerInput_a,
            .integrationTrigger = IfxDsadc_IntegratorTrigger_bypassed,
            .timestampTrigger   = IfxDsadc_TimestampTrigger_noTrigger,
            .sampleClockSource  = IfxDsadc_SampleClockSource_internal,
            .sampleStrobe       = IfxDsadc_SampleStrobe_sampleOnRisingEdge,
        },
        .combFilter             = {
            .bypassed         = FALSE,
            .combFilterType   = IfxDsadc_MainCombFilterType_comb3,
            .combFilterShift  = IfxDsadc_MainCombFilterShift_noShift,
            .serviceRequest   = IfxDsadc_MainServiceRequest_everyNewResult,
            .decimationFactor = 50,
            .startValue       = 0,
        },
        .firFilter              = {
            .fir0Enabled        = FALSE,
            .fir1Enabled        = FALSE,
            .offsetCompensation = FALSE,
            .dataShift          = IfxDsadc_FirDataShift_noShift,
            .internalShift      = IfxDsadc_FirInternalShift_noShift,
        },
        .integrator             = {
            .windowSize        = IfxDsadc_IntegrationWindowSize_internalControl,
            .discardCount      = 0,
            .integrationCount  = 20,
            .integrationCycles = 1,
        },
        .auxFilter              = {
            .bypassed         = TRUE,
            .combFilterType   = IfxDsadc_AuxCombFilterType_comb1,
            .combFilterShift  = IfxDsadc_AuxCombFilterShift_noShift,
            .serviceRequest   = IfxDsadc_AuxServiceRequest_never,
            .eventSelect      = IfxDsadc_AuxEvent_everyNewResult,
            .eventGate        = IfxDsadc_AuxGate_definedByESEL,
            .decimationFactor = 4,
        },
        .rectifier              = {
            .enabled    = FALSE,
            .signSource = IfxDsadc_RectifierSignSource_onChipGenerator,
            .signDelay  = 0,
            .signPeriod = 0,
        },

        .channelPins            = NULL_PTR
    };

    *config           = IfxDsadc_Dsadc_defaultChannelConfig;
    config->channelId = IfxDsadc_ChannelId_0;

    if (dsadc != NULL_PTR)
    {
        config->module = dsadc->dsadc;
    }
    else
    {
        config->module = NULL_PTR;
    }
}


IFX_STATIC void IfxDsadc_Dsadc_initCombFilter(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_CombFilterConfig *config)
{
    Ifx_DSADC_CH_FCFGC fcfgc;

    fcfgc.U                   = 0;

    fcfgc.B.CFMDF             = config->decimationFactor - 1;
    fcfgc.B.CFMC              = config->combFilterType;
    fcfgc.B.CFEN              = (config->bypassed == FALSE) ? 1 : 0;

    fcfgc.B.MFSC              = config->combFilterShift;

    fcfgc.B.SRGM              = config->serviceRequest;
    fcfgc.B.CFMSV             = config->startValue - 1;

    (channel->channel)->FCFGC = fcfgc;
}


IFX_STATIC void IfxDsadc_Dsadc_initDemodulator(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_DemodulatorConfig *config)
{
    Ifx_DSADC_CH_DICFG dicfg;

    dicfg.U                   = 0;

    dicfg.B.DSRC              = config->inputDataSource;
    dicfg.B.DSWC              = 1; // enable write access for this bitfield

    dicfg.B.ITRMODE           = config->integrationTrigger;
    dicfg.B.TSTRMODE          = config->timestampTrigger;
    dicfg.B.TRSEL             = config->triggerInput;
    dicfg.B.TRWC              = 1; // enable write access for these bitfields

    dicfg.B.CSRC              = config->sampleClockSource;
    dicfg.B.STROBE            = config->sampleStrobe;
    dicfg.B.SCWC              = 1; // enable write access for these bitfields

    (channel->channel)->DICFG = dicfg;
}


IFX_STATIC void IfxDsadc_Dsadc_initFirFilter(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_FirFilterConfig *config)
{
    Ifx_DSADC_CH_FCFGM fcfgm;

    fcfgm.U                   = 0;

    fcfgm.B.FIR0EN            = (config->fir0Enabled != FALSE) ? 1 : 0;
    fcfgm.B.FIR1EN            = (config->fir1Enabled != FALSE) ? 1 : 0;
    fcfgm.B.OCEN              = (config->offsetCompensation != FALSE) ? 1 : 0;
    fcfgm.B.DSH               = config->dataShift;
    fcfgm.B.FSH               = config->internalShift;

    (channel->channel)->FCFGM = fcfgm;
}


IFX_STATIC void IfxDsadc_Dsadc_initIntegrator(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_IntegratorConfig *config)
{
    Ifx_DSADC_CH_IWCTR iwctr;

    iwctr.U                   = 0;

    iwctr.B.REPVAL            = config->integrationCycles - 1;
    iwctr.B.NVALDIS           = config->discardCount;
    iwctr.B.IWS               = config->windowSize;
    iwctr.B.NVALINT           = config->integrationCount - 1;

    (channel->channel)->IWCTR = iwctr;
}


IFX_STATIC void IfxDsadc_Dsadc_initModulator(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_ModulatorConfig *config)
{
    Ifx_DSADC_CH_MODCFG modcfg;

    modcfg.U         = 0;

    modcfg.B.INCFGP  = config->positiveInput;
    modcfg.B.INCFGN  = config->negativeInput;
    modcfg.B.GAINSEL = config->inputGain;
    modcfg.B.INSEL   = config->inputPin;
    modcfg.B.INCWC   = 1;       // enable write access for these bitfields

    float32 targetFreq = config->modulatorClockFreq;
    float32 sourceFreq = IfxDsadc_getModulatorInputClockFreq(channel->module);
    modcfg.B.DIVM              = IfxDsadc_Dsadc_calcDIVx(sourceFreq, &targetFreq);
    modcfg.B.DWC               = 1; // enable write access for this bitfield

    modcfg.B.CMVS              = config->commonModeVoltage;
    modcfg.B.GCEN              = 0; // normal operation (calibration mode disabled)
    modcfg.B.MWC               = 1; // enable write access for these bitfields

    (channel->channel)->MODCFG = modcfg;
}


void IfxDsadc_Dsadc_initModule(IfxDsadc_Dsadc *dsadc, const IfxDsadc_Dsadc_Config *config)
{
    Ifx_DSADC *dsadcSFR = config->dsadc;

    dsadc->dsadc = dsadcSFR;

    {
        uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
        IfxScuWdt_clearCpuEndinit(passwd);
        dsadcSFR->CLC.U = 0x00000000;

        if (dsadcSFR->CLC.U)
        {}                       // sync access

        IfxScuWdt_setCpuEndinit(passwd);

        {
            Ifx_DSADC_GLOBCFG globcfg;
            globcfg.U           = dsadcSFR->GLOBCFG.U;

            globcfg.B.MCSEL     = config->modulatorClockSelect;
            globcfg.B.LOSUP     = config->lowPowerSupply;
            globcfg.B.PSWC      = 1;

            dsadcSFR->GLOBCFG.U = globcfg.U;
        }
    }
}


void IfxDsadc_Dsadc_initModuleConfig(IfxDsadc_Dsadc_Config *config, Ifx_DSADC *dsadc)
{
    const IfxDsadc_Dsadc_Config IfxDsadc_Dsadc_defaultConfig = {
        .modulatorClockSelect = IfxDsadc_ModulatorClock_fDSD,
        .lowPowerSupply       = IfxDsadc_LowPowerSupply_5V
    };

    *config       = IfxDsadc_Dsadc_defaultConfig;
    config->dsadc = dsadc;
}


IFX_STATIC void IfxDsadc_Dsadc_initRectifier(IfxDsadc_Dsadc_Channel *channel, const IfxDsadc_Dsadc_RectifierConfig *config)
{
    Ifx_DSADC_CH_RECTCFG rect;

    rect.U                              = 0;
    rect.B.RFEN                         = config->enabled;
    rect.B.SSRC                         = config->signSource;
    (channel->channel)->RECTCFG         = rect;
    (channel->channel)->CGSYNC.B.SDPOS  = config->signDelay;
    (channel->channel)->CGSYNC.B.SDNEG  = config->signDelay + (config->signPeriod / 2);
    (channel->channel)->IWCTR.B.NVALDIS = config->signDelay + 1;
}


void IfxDsadc_Dsadc_initCarrierGenConfig(IfxDsadc_Dsadc_CarrierGenConfig *config)
{
    config->bitReversed         = FALSE;
    config->carrierWaveformMode = IfxDsadc_CarrierWaveformMode_sine;
    config->frequency           = 10000;
    config->inverted            = FALSE;
    config->pinDriver           = IfxPort_PadDriver_cmosAutomotiveSpeed1;
    config->pinMode             = IfxPort_OutputMode_pushPull;
    config->pinNeg              = NULL_PTR;
    config->pinPos              = NULL_PTR;
}
