#include "D:\PIC_PROJECT\adc_test1.h"

#byte port_d   =  0x0f83

int16 a0=0,a1=0,e0=0,e1=0,e2=0;
int8 temp=0,r0=0,r1=0,r2=0,r3=0;

int8 shifr[10]={0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};



#int_RDA

void  RDA_isr(void) 
{
   temp=getc();
  // port_d=temp;
}

void str(int16 a)
{
   r0=a%10;
   r1=a/10;
   r1=r1%10;
   r2=a/100;
   r3=r2/10;
   r2=r2%10;
   putc(shifr[r3]);
   putc(shifr[r2]);
   putc(shifr[r1]);
   putc(shifr[r0]);
   putc(' ');
   delay_ms(10);
}



void main()
{

   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   set_tris_c(0x80);
   set_tris_a(0xff);
   set_tris_d(0x00);
   port_d=0x01;
   for (;;)
   {
      set_adc_channel(0);
      delay_ms(1);
      a0=read_adc();
      
     
      putc('C');
      port_d=0xaa;
      delay_ms(1000);
      port_d=0x55;
      delay_ms(1000);
      str (a0);
     // str (a1);
     // str (e0);
     // str (e1);
    //  str (e2);
     // putc(13);
      delay_ms(700);
      
}

}
