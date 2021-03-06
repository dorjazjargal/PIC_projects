#include "D:\PIC_PROJECT\photo_relay_test.h"
#byte port_b   =  0x0f81
#byte port_d   =  0x0f83
int16 a0=0,a1=0,a2=0;
int8 i=0,teden_udaa=0;
int8 temp,r0,r1,r2,r3=0;
int8 shifr[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};

#int_RDA
void  RDA_isr(void) 
{
temp=getc();
}

int16 avg_adc(int8 times){
a0=0;
if(times>=63){
times=63;
}
for(i=0;i<times;i++){
set_adc_channel(0);
delay_ms(100);
a1=read_adc();
a0+=a1;
}
a0=a0/times;
return a0;
}



void main()
{

   //setup_adc_ports(RA0_ANALOG);
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   output_a(0x00);
set_tris_c(0x80);
set_tris_a(0x01);
set_tris_d(0x00);

output_d(0x00);
port_b=0;

port_d=0xff;
delay_ms(1000);
port_d=0;
delay_ms(500);

teden_udaa=20;

for(;;){

a0=0;
a0=avg_adc(teden_udaa);


if(a0>=860){
//off
port_d=0;
}
if(a0<=859 && a0>600){
port_d=0;
}
/*
if(a0<=590 && a0>570){
//on
port_d=0xff;
delay_ms(30000);
delay_ms(30000);
}*/
if(a0<=570 && a0>5){
//on
port_d=0xff;
delay_ms(10000);
delay_ms(30000);
delay_ms(30000);
}
if(a0<=5){port_d=0;}
a2=a0;
if(a2>=1000){
a2=999;
}
r2=a2/100;
r3=a2%100;
r1=r3/10;
r0=r3%10;
putc('a');
putc('d');
putc('c');
putc('=');
putc(shifr[r2]);
putc(shifr[r1]);
putc(shifr[r0]);
putc(0x0d);
port_b=0;
delay_ms(200);
port_b=shifr[r2];
delay_ms(200);
port_b=shifr[r1];
delay_ms(200);
port_b=shifr[r0];
delay_ms(200);

}
}
