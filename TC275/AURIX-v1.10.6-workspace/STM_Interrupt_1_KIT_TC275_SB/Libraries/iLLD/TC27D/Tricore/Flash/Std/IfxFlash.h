/**
 * \file IfxFlash.h
 * \brief FLASH  basic functionality
 * \ingroup IfxLld_Flash
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
 * \defgroup IfxLld_Flash_Std_Enumerations Enumerations
 * \ingroup IfxLld_Flash_Std
 * \defgroup IfxLld_Flash_Std_CommandSequence CommandSequence Functions
 * \ingroup IfxLld_Flash_Std
 * \defgroup IfxLld_Flash_Std_ErrorTracking Error Tracking Functions
 * \ingroup IfxLld_Flash_Std
 */

#ifndef IFXFLAS_H
#define IFXFLAS_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxFlash_cfg.h"
#include "_Utilities/Ifx_Assert.h"
#include "IfxFlash_reg.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Flash_Std_Enumerations
 * \{ */
/** \brief enumeration for Flash Error tracking
 */
typedef enum
{
    IfxFlash_ErrorTracking_none                            = 0,  /**< \brief Error tracking disabled */
    IfxFlash_ErrorTracking_correctedSingleBitError         = 1,  /**< \brief corrected single bit errors */
    IfxFlash_ErrorTracking_correctedDoubleBitError         = 2,  /**< \brief Corrected double-bit errors */
    IfxFlash_ErrorTracking_correctedSingleOrDoubleBitError = 3,  /**< \brief Corrected single-bit and double-bit errors */
    IfxFlash_ErrorTracking_uncorrectableMultiBitError      = 4   /**< \brief Detected uncorrectable errors */
} IfxFlash_ErrorTracking;

/** \brief Corrected/UnCorrected Bits Address Buffer Port Id
 */
typedef enum
{
    IfxFlash_PortId_PortId_0 = 0,  /**< \brief Port Id 0 */
    IfxFlash_PortId_PortId_1 = 1   /**< \brief Port Id 1 */
} IfxFlash_PortId;

/** \} */

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Flash_Std_Enumerations
 * \{ */
/** \brief Error tracking address structure
 */
typedef struct
{
    uint32                 address;         /**< \brief Flash address for error tracking */
    IfxFlash_ErrorTracking errorType;       /**< \brief Error type */
} IfxFlash_ErrorTracking_Address;

/** \} */

/** \addtogroup IfxLld_Flash_Std_CommandSequence
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Performs the "Clear Status" sequence. Operation and error flags are cleared.
 * \param flash selects the flash (PMU) module
 * \return None
 */
IFX_INLINE void IfxFlash_clearStatus(uint32 flash);

/** \brief Performs the sequence for entering program page mode
 * \param pageAddr pageAddr specifies the page being written - the command sequence will be varied accordingly
 * \return 0 on success, != 0 if invalid or not available page is selected
 *
 * Usage Example:
 * \code
 *
 * unsigned int pageAddr = IFXFLASH_DFLASH_START + page*IFXFLASH_DFLASH_PAGE_LENGTH;
 *
 * // enter page mode
 * IfxFlash_enterPageMode(pageAddr);
 *
 * \endcode
 *
 */
IFX_INLINE uint8 IfxFlash_enterPageMode(uint32 pageAddr);

/** \brief Performs the erase sequence for n  sectors in program or data flash
 * \param sectorAddr sector address
 * \param numSector the no.of sectors to be erased
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // erase the first and second data flash
 * IfxFlash_eraseMultiplePhysicalSectors(IFXFLASH_DFLASH_START,2);
 *
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_eraseMultiplePhysicalSectors(uint32 sectorAddr, uint32 numSector);

/** \brief Performs the erase sequence for n  sectors in program or data flash
 * \param sectorAddr sector address
 * \param numSector the no.of sectors to be erased
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // erase logical sectors of program flash
 *  IfxFlash_eraseMultipleSectors(pFlashTableLog[sector].start,2);
 *
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_eraseMultipleSectors(uint32 sectorAddr, uint32 numSector);

/** \brief Performs the erase sequence for a physical sector in program or data flash
 * \param sectorAddr sector address
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // erase the first data flash
 *  IfxFlash_erasePhysicalSector(IFXFLASH_DFLASH_START);
 *
 *
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_erasePhysicalSector(uint32 sectorAddr);

/** \brief Performs the erase sequence for a sector in program or data flash.
 * \param sectorAddr sector address
 * \return None
 *
 * Usage Example:
 * \code
 *
 *
 * // erase all sectors of program flash
 * for(sector=0; sector<IFXFLASH_PFLASH_NO_OF_LOG_SECTORS; ++sector) {
 *   // get address from predefined table
 *   unsigned int sector_addr = pFlashTableLog[sector].start;
 *   // erase sector
 *  IfxFlash_eraseSector(sector_addr);
 * }
 *
 *
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_eraseSector(uint32 sectorAddr);

/** \brief Performs the "Erase Verify" sequence for multiple sectors
 * \param sectorAddr sector address which should be verified
 * \param numSector no.of sectors to be operated on
 * \return None
 */
IFX_INLINE void IfxFlash_eraseVerifyMultipleSectors(uint32 sectorAddr, uint32 numSector);

/** \brief Performs the "Erase Verify" sequence
 * \param sectorAddr sector address which should be verified
 * \return None
 */
IFX_INLINE void IfxFlash_eraseVerifySector(uint32 sectorAddr);

/** \brief performs a load page sequence with a single 64bit access
 * \param pageAddr pageAddr start address of page which should be programmed
 * \param wordL Lower Address word
 * \param wordU Upper address word
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // load 64bit into assembly buffer of program flash
 * IfxFlash_loadPage(IFXFLASH_PFLASH_START, 0x55555555, 0xaaaaaaaa);
 *
 * // load 64bit into assembly buffer of data flash
 * IfxFlash_loadPage(0XAF000000, 0x55555555, 0xaaaaaaaa);
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_loadPage(uint32 pageAddr, uint32 wordL, uint32 wordU);

/** \brief performs a load page sequence with two 32bit accesses
 * \param pageAddr pageAddr start address of page which should be programmed
 * \param wordL Lower Address word
 * \param wordU Upper Address word
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // load 2*32bit into assembly buffer of program flash
 * IfxFlash_loadPage2X32(IFXFLASH_PFLASH_START, 0x55555555, 0xaaaaaaaa);
 *
 * // load 2*32bit into assembly buffer of data flash
 * IfxFlash_loadPage2X32(0XAF000000, 0x55555555, 0xaaaaaaaa);
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_loadPage2X32(uint32 pageAddr, uint32 wordL, uint32 wordU);

/** \brief reset to read mode
 * \param flash flash selects the flash (PMU) module
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // reset to read mode
 *  IfxFlash_resetToRead(0);
 *
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_resetToRead(uint32 flash);

/** \brief Performs the "Resume Protection" sequence
 * \param flash selects the flash (PMU) module
 * \return None
 */
IFX_INLINE void IfxFlash_resumeProtection(uint32 flash);

/** \brief Performs the "Suspend Resume" sequence for multiple sectors
 * \param sectorAddr sector address
 * \param numSector the no.of sectors  to be operated on
 * \return None
 */
IFX_INLINE void IfxFlash_suspendResumeMultipleSectors(uint32 sectorAddr, uint32 numSector);

/** \brief Performs the "Suspend Resume" sequence
 * \param sectorAddr sector address which should be resumed
 * \return None
 */
IFX_INLINE void IfxFlash_suspendResumeSector(uint32 sectorAddr);

/** \brief Polls the selected status flag in flash status register until it turns to 0
 * \param flash selects the flash (PMU) module
 * \param flashType selects the flash type
 * \return 0 on success, != 0 if invalid or not available page is selected
 *
 * Usage Example:
 * \code
 *
 * // wait until data flash 0 is unbusy
 *  IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
 *
 * \endcode
 *
 */
IFX_INLINE uint8 IfxFlash_waitUnbusy(uint32 flash, IfxFlash_FlashType flashType);

/** \brief Performs the "Write Burst" sequence, similar to write page but performs a burst transfer instead of page.Make sure the appropriate amount of data is loaded using load page command
 * \param pageAddr start address of page which should be programmed
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // program the second page of the first sector of the Program Flash
 * IfxFlash_writeBurst(0xa0000100);
 *
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_writeBurst(uint32 pageAddr);

/** \brief Performs the "Write Page" sequence
 * \param pageAddr start address of page which should be programmed
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // program the second page of the first sector of the Program Flash
 * IfxFlash_writePage(0xa0000100);
 *
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_writePage(uint32 pageAddr);

/** \brief Performs the "Write Page Once" sequence, similar to write page but performs a program verify after writing.
 * \param pageAddr start address of page which should be programmed
 * \return None
 *
 * Usage Example:
 * \code
 *
 * // program the second page of the first sector of the Program Flash
 * IfxFlash_writePageOnce(0xa0000100);
 *
 * \endcode
 *
 */
IFX_INLINE void IfxFlash_writePageOnce(uint32 pageAddr);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief The password protection of the selected UCB (if this UCB offers this feature) is temporarily disabled. The command fails by setting PROER when any of the supplied PWs does not match. In this case until the next application reset all further calls of "Disable Protection" fail with PROER independent of the supplied password.
 * \param flash selects the flash (PMU) module
 * \param ucb selects the user configuration block (0 for UCB0, 1 for UCB1, 5 for UCB_HSMC)
 * \param password password pointer to an array of 8 words
 * \return None
 */
IFX_EXTERN void IfxFlash_disableWriteProtection(uint32 flash, IfxFlash_UcbType ucb, uint32 *password);

/** \} */

/** \addtogroup IfxLld_Flash_Std_ErrorTracking
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Clear the Correctable errors in Corrected Bits Address Buffer Configuration Port x (CBABCFGx) register
 * \param portId Corrected Bits Address Buffer Port Id
 * \return None
 */
IFX_EXTERN void IfxFlash_clearCorrectableErrorTracking(IfxFlash_PortId portId);

/** \brief Select the uncorrectable errors in UnCorrectable Bits Address Buffer Configuration Port x (UBABCFGx) register
 * \param portId UnCorrected Bits Address Buffer Port Id
 * \return None
 */
IFX_EXTERN void IfxFlash_clearUncorrectableErrorTracking(IfxFlash_PortId portId);

/** \brief Disable the Correctable errors in Corrected Bits Address Buffer Configuration Port x (CBABCFGx) register
 * \param portId Corrected Bits Address Buffer Port Id
 * \param disable Disable/enable the error tracking
 * \return None
 */
IFX_EXTERN void IfxFlash_disableCorrectableErrorTracking(IfxFlash_PortId portId, boolean disable);

/** \brief Clear the uncorrectable errors in UnCorrectable Bits Address Buffer Configuration Port x (UBABCFGx) register
 * \param portId UnCorrected Bits Address Buffer Port Id
 * \param disable Disable/enable the error tracking
 * \return None
 */
IFX_EXTERN void IfxFlash_disableUncorrectableErrorTracking(IfxFlash_PortId portId, boolean disable);

/** \brief Returns the tracked correctable error addresses,  error types and number of errors which are stored in the CBAB registers.
 * \param portId Corrected Bits Address Buffer Port Id
 * \param trackedFlashAdresses tracked flash addresses for correctable errors
 * \return numErrors
 *
 * Example usage to print out tracked errors :
 *
 * \code
 *     {
 *         IfxFlash_ErrorTracking_Address trackedAddresses[IFX_FLASH_ERROR_TRACKING_MAX_CORRECTABLE_ERRORS];
 *         IfxFlash_portId portId = 0;
 *         uint8  numTrackedAddresses = IfxFlash_getTrackedCorrectableErrors(portId, trackedAddresses);
 *
 *         for(int i=0; i<numTrackedAddresses; ++i) {
 *             printf("%d: A:0x%04x Error Type:%d \n",
 *                    i,
 *                    trackedAddresses[i].address,
 *                    trackedAddresses[i].errorType);
 *         }
 *     }
 * \endcode
 *
 */
IFX_EXTERN uint32 IfxFlash_getTrackedCorrectableErrors(IfxFlash_PortId portId, IfxFlash_ErrorTracking_Address *trackedFlashAdresses);

/** \brief Returns the tracked uncorrectable error addresses,  error types and number of errors which are stored in the UBAB registers.
 * \param portId UnCorrected Bits Address Buffer Port Id
 * \param trackedFlashAdresses tracked flash addresses for uncorrectable errors
 * \return numErrors
 *
 * Example usage to print out tracked errors :
 *
 * \code
 *     {
 *         IfxFlash_ErrorTracking_Address trackedAddresses[IFX_FLASH_ERROR_TRACKING_MAX_UNCORRECTABLE_ERRORS];
 *         IfxFlash_portId portId = 0;
 *         uint8  numTrackedAddresses = IfxFlash_getTrackedUnCorrectableErrors(portId, trackedAddresses);
 *
 *         for(int i=0; i<numTrackedAddresses; ++i) {
 *             printf("%d: A:0x%04x Error Type:%d \n",
 *                    i,
 *                    trackedAddresses[i].address,
 *                    trackedAddresses[i].errorType);
 *         }
 *     }
 * \endcode
 *
 */
IFX_EXTERN uint32 IfxFlash_getTrackedUncorrectableErrors(IfxFlash_PortId portId, IfxFlash_ErrorTracking_Address *trackedFlashAdresses);

/** \brief Enables error tracking for correctable flash errors
 * \param portId Corrected Bits Address Buffer Port Id
 * \param errorTracking Error Tracking to be selected
 * \return None
 *
 * Usage example: how to enable error tracking for two flash ports:
 * \code
 *     // enable error tracking
 *     {
 *         uint16 password = IfxScuWdt_getCpuWatchdogPassword();
 *         IfxScuWdt_clearCpuEndinit(password);
 *
 *         // PFlash0
 *         IfxFlash_selectCorrectableErrorTracking(IfxFlash_PortId_PortId_0, IfxFlash_ErrorTracking_correctedSingleOrDoubleBitError);
 *         IfxFlash_selectUncorrectableErrorTracking(IfxFlash_PortId_PortId_0, IfxFlash_ErrorTracking_uncorrectableMultiBitError);
 *
 *         // PFlash1
 *         IfxFlash_selectCorrectableErrorTracking(IfxFlash_PortId_PortId_1, IfxFlash_ErrorTracking_correctedSingleOrDoubleBitError);
 *         IfxFlash_selectUncorrectableErrorTracking(IfxFlash_PortId_PortId_1, IfxFlash_ErrorTracking_uncorrectableMultiBitError);
 *
 *         IfxScuWdt_setCpuEndinit(password);
 *     }
 * \endcode
 *
 */
IFX_EXTERN void IfxFlash_selectCorrectableErrorTracking(IfxFlash_PortId portId, IfxFlash_ErrorTracking errorTracking);

/** \brief Enables error tracking for uncorrectable flash errors
 * \param portId UnCorrected Bits Address Buffer Port Id
 * \param errorTracking Error Tracking to be selected
 * \return None
 *
 * Usage example: see \ref IfxFlash_selectCorrectableErrorTracking
 *
 */
IFX_EXTERN void IfxFlash_selectUncorrectableErrorTracking(IfxFlash_PortId portId, IfxFlash_ErrorTracking errorTracking);

/** \} */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief This function will wait till all the flash banks are out of busy state
 * \return Return 0 on success.Success means none of the flash banks are in busy state.
 */
IFX_INLINE boolean IfxFlash_waitUnbusyAll(void);

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE void IfxFlash_clearStatus(uint32 flash)
{
    IFX_UNUSED_PARAMETER(flash);
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0x5554);

    *addr1 = 0xFA;

    __dsync();
}


IFX_INLINE uint8 IfxFlash_enterPageMode(uint32 pageAddr)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0x5554);

    if ((pageAddr & 0xff000000) == 0xa0000000)    // program flash
    {
        *addr1 = 0x50;
        return 0;
    }
    else if ((pageAddr & 0xff000000) == 0xaf000000)       // data flash
    {
        *addr1 = 0x5D;
        return 0;
    }

    __dsync();
    return 1; // invalid flash address
}


IFX_INLINE void IfxFlash_eraseMultiplePhysicalSectors(uint32 sectorAddr, uint32 numSector)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = sectorAddr;
    *addr2 = numSector;
    *addr3 = 0x80;
    *addr4 = 0x5a;

    __dsync();
}


IFX_INLINE void IfxFlash_eraseMultipleSectors(uint32 sectorAddr, uint32 numSector)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = sectorAddr;
    *addr2 = numSector;
    *addr3 = 0x80;
    *addr4 = 0x50;

    __dsync();
}


IFX_INLINE void IfxFlash_erasePhysicalSector(uint32 sectorAddr)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = sectorAddr;
    *addr2 = 1;
    *addr3 = 0x80;
    *addr4 = 0x5a;

    __dsync();
}


IFX_INLINE void IfxFlash_eraseSector(uint32 sectorAddr)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = sectorAddr;
    *addr2 = 1;
    *addr3 = 0x80;
    *addr4 = 0x50;

    __dsync();
}


IFX_INLINE void IfxFlash_eraseVerifyMultipleSectors(uint32 sectorAddr, uint32 numSector)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = sectorAddr;
    *addr2 = numSector;
    *addr3 = 0x80;
    *addr4 = 0x5F;

    __dsync();
}


IFX_INLINE void IfxFlash_eraseVerifySector(uint32 sectorAddr)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = sectorAddr;
    *addr2 = 1;
    *addr3 = 0x80;
    *addr4 = 0x5F;

    __dsync();
}


IFX_INLINE void IfxFlash_loadPage(uint32 pageAddr, uint32 wordL, uint32 wordU)
{
    IFX_UNUSED_PARAMETER(pageAddr);
    uint64 *addr1 = (uint64 *)(IFXFLASH_CMD_BASE_ADDRESS | 0x55f0);

    __st64_lu(addr1, wordL, wordU);

    __dsync();
}


IFX_INLINE void IfxFlash_loadPage2X32(uint32 pageAddr, uint32 wordL, uint32 wordU)
{
    IFX_UNUSED_PARAMETER(pageAddr);

    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0x55f0);

    *addr1 = wordL;
    addr1++;
    *addr1 = wordU;

    __dsync();
}


IFX_INLINE void IfxFlash_resetToRead(uint32 flash)
{
    IFX_UNUSED_PARAMETER(flash);
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0x5554);
    *addr1 = 0xf0;

    __dsync();
}


IFX_INLINE void IfxFlash_resumeProtection(uint32 flash)
{
    IFX_UNUSED_PARAMETER(flash);

    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0x5554);

    *addr1 = 0xF5;

    __dsync();
}


IFX_INLINE void IfxFlash_suspendResumeMultipleSectors(uint32 sectorAddr, uint32 numSector)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = sectorAddr;
    *addr2 = numSector;
    *addr3 = 0x70;
    *addr4 = 0xCC;

    __dsync();
}


IFX_INLINE void IfxFlash_suspendResumeSector(uint32 sectorAddr)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = sectorAddr;
    *addr2 = 1;
    *addr3 = 0x70;
    *addr4 = 0xCC;

    __dsync();
}


IFX_INLINE uint8 IfxFlash_waitUnbusy(uint32 flash, IfxFlash_FlashType flashType)
{
    if (flash == 0)
    {
        while (FLASH0_FSR.U & (1 << flashType))
        {}
    }

#if IFXFLASH_NUM_FLASH_MODULES > 1
    else if (flash == 1)
    {
        while (FLASH1_FSR.U & (1 << flashType))
        {}
    }
#endif
    else
    {
        return 1; // invalid flash selected
    }
    __dsync();
    return 0;     // finished
}


IFX_INLINE void IfxFlash_writeBurst(uint32 pageAddr)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = pageAddr;
    *addr2 = 0x00;
    *addr3 = 0xa0;
    *addr4 = 0x7a;

    __dsync();
}


IFX_INLINE void IfxFlash_writePage(uint32 pageAddr)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = pageAddr;
    *addr2 = 0x00;
    *addr3 = 0xa0;
    *addr4 = 0xaa;

    __dsync();
}


IFX_INLINE void IfxFlash_writePageOnce(uint32 pageAddr)
{
    volatile uint32 *addr1 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa50);
    volatile uint32 *addr2 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaa58);
    volatile uint32 *addr3 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);
    volatile uint32 *addr4 = (volatile uint32 *)(IFXFLASH_CMD_BASE_ADDRESS | 0xaaa8);

    *addr1 = pageAddr;
    *addr2 = 0x00;
    *addr3 = 0xa0;
    *addr4 = 0x9a;

    __dsync();
}


IFX_INLINE boolean IfxFlash_waitUnbusyAll(void)
{
    while (FLASH0_FSR.U & 0x1EU)
    {}

    __dsync();
    return 0;
}


#endif /* IFXFLAS_H */
