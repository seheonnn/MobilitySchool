/*
 * dht11_driver.c
 *
 *  Created on: 2025. 2. 18.
 *      Author: jijon
 */


#include "Ifx_Types.h"
#include "dht11_driver.h"
#include "Bsp.h"


void DHT11_Start (void){
    IfxPort_setPinModeOutput(DHT11.port, DHT11.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinState(DHT11.port, DHT11.pinIndex, IfxPort_State_low);
    delay(18000);   // wait for 18ms
    IfxPort_setPinModeInput(DHT11.port, DHT11.pinIndex,IfxPort_InputMode_noPullDevice);
}
uint8_t Check_Response (void){
    uint8_t Response = 0;
    delay (40);
    if (!(IfxPort_getPinState(DHT11.port, DHT11.pinIndex)))
    {
        delay (80);
        if ((IfxPort_getPinState(DHT11.port, DHT11.pinIndex))) Response = 1;
        else Response = -1;
    }
    while ((IfxPort_getPinState(DHT11.port, DHT11.pinIndex)));   // wait for the pin to go low

    return Response;
}
uint8_t DHT11_Read (void){
    uint8_t i,j;
    for (j=0;j<8;j++)
    {
        while (!(IfxPort_getPinState(DHT11.port, DHT11.pinIndex)));   // wait for the pin to go high
        delay (40);   // wait for 40 us
        if (!(IfxPort_getPinState(DHT11.port, DHT11.pinIndex)))   // if the pin is low
        {
            i&= ~(1<<(7-j));   // write 0
        }
        else i|= (1<<(7-j));  // if the pin is high, write 1
        while ((IfxPort_getPinState(DHT11.port, DHT11.pinIndex)));  // wait for the pin to go low
    }
    return i;
}

void delay(uint32_t us){
    waitTime(us*100);
}


