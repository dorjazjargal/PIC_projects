#include "D:\PIC_PROJECT\tungaah.h"
#byte port_a   =  0x0f80
#byte port_b   =  0x0f81
#byte port_d   =  0x0f83
#byte port_e   =  0x0f84

int8 umnuh_a=0, umnuh_b=0, umnuh_d=0, umnuh_e=0, porta=0;
int8 ascii_number[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};

int8 temp,n1,n2,n3=0;

#int_RDA
void  RDA_isr(void) 
{
temp=getc();
}


void convert_ascii(int8 port){
   if(port>=100){
      n3=port/100;
      n2=port%100;
      n2=n2/10;
      n1=port%10;
      putc(ascii_number[n3]);
      putc(ascii_number[n2]);
      putc(ascii_number[n1]);
      putc(0x0d);
   }
   else{
      n2=port/10;
      n1=port%10;
      putc(ascii_number[n2]);
      putc(ascii_number[n1]);
      putc(0x0d);
   }
   
}

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
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
set_tris_a(0x3f);
set_tris_b(0xff);
set_tris_c(0x80);
set_tris_d(0xff);
set_tris_e(0xff);

for(;;){


   if(umnuh_a!=~port_a){
      putc('a');
     // porta=port_a&0x3f;
      convert_ascii(~port_a);
     
   }
   umnuh_a=~port_a;
   umnuh_a=0;
   
   if(umnuh_b!=~port_b){
      putc('b');
      convert_ascii(~port_b);
     
   }
   umnuh_b=~port_b;
   
    if(umnuh_d!=port_d){
      putc('d');
      convert_ascii(port_d);
      
   }
   umnuh_d=port_d;
   umnuh_d=0;
   
   if(umnuh_e!=~port_e){
      putc('e');
      convert_ascii(~port_e);
      
   }
   umnuh_e=~port_e;
   
}
}
