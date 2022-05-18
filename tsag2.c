#include "D:\PIC_PROJECT\tsag2.h"
#byte port_e   =  0x0f84
#byte port_d   =  0x0f83
#byte port_b   =  0x0f81

int8 r0,a0=10,r1=0,mode=0;
int8 sec=0,min=0,hour=0,weekDay=0,date=0,month=0,year=0;
int1 b=1;
int1 setbit=0,hassan_sec=0,e0_bit=0,e1_bit=0;


void set_time0(int8 tsag, int8 minute, int8 sar, int8 udur)
{
    I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x00);                   // Request sec RAM address at 00H
 
    I2C_Write(0x50);                    // Write sec from RAM address 00H
    I2C_Write(0x59);                    // Write min from RAM address 01H
    I2C_Write(0x23);                    // Write hour from RAM address 02H
    I2C_Write(0x04);                   // Write weekDay on RAM address 03H
    I2C_Write(0x31);                    // Write date on RAM address 04H
    I2C_Write(0x12);                    // Write month on RAM address 05H
    I2C_Write(0x20);                    // Write year on RAM address 06h
 
    I2C_Stop();                              // Stop I2C communication after Setting the Date
}


void rtc_getdate()
{
    I2C_Start();                            // Start I2C communication
 
    I2C_Write(0xd0);                         // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x00);                         // Request Sec RAM address at 00H
 
    I2C_Stop();                                // Stop I2C communication after selecting Sec Register
 
    I2C_Start();                            // Start I2C communication
    I2C_Write(0xd1);            // connect to DS1307(Read mode) by sending its ID
 
    sec = I2C_Read(1);                // read second and return Positive ACK
    min = I2C_Read(1);                 // read minute and return Positive ACK
    hour= I2C_Read(1);               // read hour and return Negative/No ACK
    weekDay = I2C_Read(1);           // read weekDay and return Positive ACK
    date= I2C_Read(1);              // read Date and return Positive ACK
    month=I2C_Read(1);            // read Month and return Positive ACK
    year =I2C_Read(0);             // read Year and return Negative/No ACK
 
    I2C_Stop();                              // Stop I2C communication after reading the Date
}

int8 set_bcd(int8 ival)
 {
    return ((ival / 10) << 4) | (ival % 10);
 }
 
  int8 readadc(){
       set_adc_channel(0);
       delay_us(250);
       a0=read_adc();
   
      if(a0>=3){
      a0=a0-3;
      }
      
      a0=a0/4;
      a0=set_bcd(a0);
      
      return a0;
   
  }
 
 void set_sec(){
 if(hassan_sec==1){
 hassan_sec=0;
 delay_ms(30000);
 rtc_getdate();
  I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x00);                   // Request sec RAM address at 00H
    //port_d=sec;
    sec=sec-0x15;
    
    if(sec<=0 && sec>=0x60){sec=0x00;port_d=3;}
    I2C_Write(sec);                    // Write min from RAM address 01H
    I2C_STOP();
    
 }
 }
 void set_min(){
 r0=readadc();
 min=r0;
 if(min>=0x60){min=0x59;}
     I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x01);                   // Request minute RAM address at 01H
 
    I2C_Write(min);                    // Write min from RAM address 01H
    I2C_STOP();
 }
 void set_tsag(){
 r0=readadc();
 hour=r0;
 if(hour>=0x24){hour=0x23;}
     I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x02);                   // Request hour RAM address at 02H
 
    I2C_Write(hour);                    // Write hour from RAM address 02H
    I2C_STOP();
 }
 void set_sar(){
 r0=readadc();
 month=r0;
 if(month>=0x13){month=0x12;}
 I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x05);                   // Request hour RAM address at 02H
 
    I2C_Write(month);                    // Write hour from RAM address 02H
    I2C_STOP();
 }
 void set_udur(){
 r0=readadc();
 date=r0;
 if(date>=0x32){date=0x31;}
 I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x04);                   // Request udur RAM address at 04H
 
    I2C_Write(date);                    // Write udur from RAM address 04H
    I2C_STOP();
    
 }
 
#int_EXT
void  EXT_isr(void) 
{
setbit=bit_test(port_e,2);
if(setbit==1){
switch (port_e){
   case 4: mode=4;break;
   case 5: mode=5;break;
   case 6: mode=6;break;
   case 7: mode=7;break;
}
}
}
 void segment_ruu_gargah(int8 k0){
   
 }
void main()
{

   setup_adc_ports(RA0_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_psp(PSP_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
set_tris_a(0x01);
set_tris_e(0x00);
set_tris_d(0x00);
set_tris_b(0x01);
set_tris_c(0x00);
output_c(0x00);
output_a(0x00);
output_b(0x00);
output_d(0x00);

for(;;){
  
if(b==1){
set_time0(0x09,0x15,0x10,0x01);
b=0;
delay_ms(1500);
}
delay_ms(200);

if(hour==0x23 && min>=0x59 && sec>=0x57){hassan_sec=1;}
rtc_getdate();
set_sec();

setbit=bit_test(port_e,2);

if(setbit==1){
r1=readadc();
segment_ruu_gargah(r1);
}

if(mode==4){set_sar(); mode=0;}
if(mode==5){set_udur(); mode=0;}
if(mode==6){set_tsag(); mode=0;}
if(mode==7){set_min(); mode=0;}

}
}

