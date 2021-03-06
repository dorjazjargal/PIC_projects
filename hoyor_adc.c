#include "D:\PIC_PROJECT\hoyor_adc.h"
#byte port_d   =  0x0f83

int8 temp=0,i=0;
int16 a0=0,a1=0,a2=0,limit=0,a4=0;
int8 r0,r1,r2,r3=0;
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
a2=read_adc();
a0+=a2;
}
a0=a0/times;
return a0;
}

void main()
{

   setup_adc_ports(AN0_AN1_AN3);
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
set_tris_a(0x0f);
set_tris_c(0x80);
set_tris_d(0x00);
port_d=0xff;
delay_ms(1500);
port_d=0;
delay_ms(800);
for(;;){

delay_ms(1000);
   avg_adc(20);
   
   set_adc_channel(1);
   delay_ms(1);
   a1=read_adc();
   a1=a1/5;
   
   a4=a0;
   a0=a0+a1;
   
   limit=550; 
   
   if(a0>=limit){
      port_d=0;
      delay_ms(10000);
   }
   if(a0<limit && a0>450){
      port_d=0xff;
      delay_ms(30000);
   }
   if(a0<=450 && a0>5){
      port_d=0xff;
   }
   
   if(a4<5){// photo resistoriin hul tasarchihsan ued untarah tul
      port_d=0;
   }
   
r2=a0/100;
r3=a0%100;
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
}
}
