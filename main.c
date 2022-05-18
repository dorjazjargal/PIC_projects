#include "D:\PIC_PROJECT\main.h"
#int_RDA
void  RDA_isr(void) 
{

}



void main()
{

   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_64);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
//Setup_Oscillator parameter not selected from Intr Oscillotar Config tab

   // TODO: USER CODE!!

}
