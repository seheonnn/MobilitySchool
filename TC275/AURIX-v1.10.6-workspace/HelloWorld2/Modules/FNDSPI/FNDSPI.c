///*
// * FNDSPI.c
// *
// *  Created on: 2025. 2. 17.
// *      Author: USER
// */
//#include "FNDSPI.h"
//unsigned char Led_0f[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
//extern void initFND(){
//    IfxPort_setPinModeOutput(SCLK.port, SCLK.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
//    IfxPort_setPinModeOutput(RCLK.port, RCLK.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
//    IfxPort_setPinModeOutput(DIO.port, DIO.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
//}
//
//void send(unsigned char X){
//    for(int i = 8; i>=1; i--){
//        X & 0x80 ? IfxPort_setPinHigh(DIO.port, DIO.pinIndex) : IfxPort_setPinLow(DIO.port, DIO.pinIndex);
//        X <<= 1;
//        IfxPort_setPinLow(SCLK.port, SCLK.pinIndex);
//        IfxPort_setPinHigh(SCLK.port, SCLK.pinIndex);
//    }
//}
//
//void sendPort(unsigned char data,unsigned char port){
//    send(data);
//    send(port);
//    IfxPort_setPinLow(RCLK.port, RCLK.pinIndex);
//    IfxPort_setPinHigh(RCLK.port, RCLK.pinIndex);
//}
//
//volatile void setFNDNumber(volatile int c){
//    int i = 0;
//    while(c!=0){
//        sendPort(Led_0f[c % 10],(1<<i++));
//        c/=10;
//    }
//    while(i<4) sendPort(Led_0f[0],(1<<i++));
//}
