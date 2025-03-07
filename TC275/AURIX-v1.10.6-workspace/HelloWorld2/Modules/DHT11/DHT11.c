/**********************************************************************************************************************
 * \file DHT11.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 *
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include <stdio.h>
#include "IfxPort_PinMap.h"
#include "IfxPort.h"
#include "Bsp.h"
#include "DHT11.h"

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
uint16 duration_signal_level(boolean state);
void data_valid(uint8 data_0, uint8 data_2);
void data_not_valid(void);

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
/* DHT11 sensor data pin */
#define DHT11_PIN   IfxPort_P10_4
//&MODULE_P10, 4
/* DHT11 sensor stabilization time: 2 s */
#define DHT11_STABILIZATION_TIME            200000000
/* DHT11 sensor start time: 18 ms - notify the sensor to prepare the data */
#define DHT11_START_TIME                    1800000

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
/* DHT11 data visualized using OneEye
    - humidity
    - temperature
    - measurement number
    - data valid */
extern DHT11_one_eye_data g_dht11_one_eye_data = {0, 0, 0, 0};

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Function to initialize DHT11 communication */
void DHT11_init_comm(void)
{
    /* Initialize the DTH11 sensor data pin as input */
    IfxPort_setPinModeInput(DHT11_PIN.port, DHT11_PIN.pinIndex, IfxPort_InputMode_noPullDevice);
    /* Wait to stabilize the sensor */
    waitTime(DHT11_STABILIZATION_TIME);
}

/* Function to use DHT11
   - check if the connection is established
   - read the raw data from the sensor
   - decode and check the received data */
void DHT11_read_sensor(void)
{
    /* Start signal */


    IfxPort_setPinModeOutput(DHT11_PIN.port,DHT11_PIN.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinState(DHT11_PIN.port, DHT11_PIN.pinIndex,  IfxPort_State_low);

    /* Execute the start time */
    waitTime(DHT11_START_TIME);
    IfxPort_setPinState(DHT11_PIN.port, DHT11_PIN.pinIndex,  IfxPort_State_high);

    /* Wait for 5 us */
    waitTime(500);
    IfxPort_setPinModeInput(DHT11_PIN.port, DHT11_PIN.pinIndex, IfxPort_InputMode_noPullDevice);

    /* Check the Acknowledgement signal from sensor */
    duration_signal_level(TRUE);

    if (duration_signal_level(FALSE) != 0)
    {
        if (duration_signal_level(TRUE) != 0)
        {
            /* Read 40 bits (5 Bytes) */
            uint16 signals[80] = {0};

            for (uint8 i = 0; i < 80; i += 2)
            {
                /* LOW state of bit */
                signals[i] = duration_signal_level(FALSE);
                /* HIGH state of bit */
                signals[i+1] = duration_signal_level(TRUE);
            }

            /* Decode 5 Bytes */
            uint8 data[5] = {0, 0, 0, 0, 0};

            for (uint8 j = 0; j < 5; j ++)
            {
                /* 8 bits (2 states per bit) */
                for (uint8 k = 0; k < 16; k += 2)
                {
                    data[j] <<= 1;

                    if (signals[(16 * j) + k] < signals[(16 * j) + k + 1])
                    {
                        data[j] |= 1;
                    }
                }
            }

            /* Calculate the checksum */
            uint8 checksum = 0;

            checksum = data[0] + data[1] + data[2] + data[3];

            if (checksum == data[4])
            {
                /* Data is valid */
                data_valid(data[0], data[2]);
            }
            else
            {
                /* Checksum is wrong */
                data_not_valid();
            }
        }
        else
        {
            /* DHT11 sensor is not responding */
            data_not_valid();
        }
    }
    else
    {
        /* DHT11 sensor is not connected */
        data_not_valid();
    }
    g_dht11_one_eye_data.measurement_number++;
}

/* Function to measure the duration of the provided digital level */
uint16 duration_signal_level(boolean state)
{
    uint16 count = 0;

    while(IfxPort_getPinState(DHT11_PIN.port, DHT11_PIN.pinIndex) == state)
    {
        count ++;

        /* Overflow */
        if (count >= 0xFFFF)
        {
          return 0;
        }
    }

    return count;
}

/* Function to validate the sensor data */
void data_valid(uint8 data_0, uint8 data_2)
{
    g_dht11_one_eye_data.humidity = data_0;
    g_dht11_one_eye_data.temperature = data_2;
    g_dht11_one_eye_data.data_valid = TRUE;
}

/* Function to invalidate the sensor data */
void data_not_valid(void)
{
    g_dht11_one_eye_data.humidity = 0;
    g_dht11_one_eye_data.temperature = 0;
    g_dht11_one_eye_data.data_valid = FALSE;
}
