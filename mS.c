#include "D:\PIC_PROJECT\mS.h"
#byte port_d   =  0x0f83
#byte port_b   =  0x0f81


void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
set_tris_d(0x00);
set_tris_b(0x00);
port_d=0xff;
port_b=0xff;

for(;;){
delay_ms(15000);
port_b=0x00;
port_d=0xff;
delay_ms(1);
port_b=255;
port_d=0;

}
}
