#include "D:\PIC_PROJECT\tsag_zahirgaa.h"

#byte port_a   =  0x0f80
#byte port_e   =  0x0f84
#byte port_d   =  0x0f83
#byte port_b   =  0x0f81
#bit digit3  =  0x0f82.0
#bit digit2  =  0x0f82.1
#bit digit1  =  0x0f82.2
#bit digit0  =  0x0f82.5
#bit led  =  0x0f82.7

int16 tsagmin=0,sarudur=0,tsagmin_2=0;
int8 uldegdel=0, uld_0=0, uld_1=0,buhel=0,b0=0,b1=0;
int8 shfr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int8 r0,a0=10,mode=0,sec0,sec1=0,min0,min1=0,tsag0,tsag1=0;
int8 sec=0,min=0,hour=0,weekDay=0,date=0,month=0,year=0,day0,day1,sar0,sar1=0;
int1 setbit=0,hassan_sec=0;


void set_time0(int8 tsag, int8 minute, int8 sar, int8 udur)
{
    I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x00);                   // Request sec RAM address at 00H
 
    I2C_Write(0x30);                    // Write sec from RAM address 00H
    I2C_Write(0x30);                    // Write min from RAM address 01H
    I2C_Write(0x10);                    // Write hour from RAM address 02H
    I2C_Write(0x01);                   // Write weekDay on RAM address 03H
    I2C_Write(0x01);                    // Write date on RAM address 04H
    I2C_Write(0x01);                    // Write month on RAM address 05H
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
 
  int8 read_port_a(){
      port_a=port_a & 0x3f;
      a0=port_a;
      a0=set_bcd(a0);
      return a0;
  }
 
 void set_sec(){
 if(hassan_sec==1){
 delay_ms(20000);
 rtc_getdate();
  I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x00);                   // Request sec RAM address at 00H
    if(hour==0x10){
      sec=sec-0x02;
    }else{
    sec=sec-0x03;
    }
    if(sec>=0x60){sec=0x00;}
    I2C_Write(sec);                    // Write min from RAM address 01H
    I2C_STOP();
    hassan_sec=0;
 }
 }
 void set_min(){
 r0=read_port_a();
 min=r0;
 if(min>=0x60){min=0x59;}
     I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x01);                   // Request minute RAM address at 01H
 
    I2C_Write(min);                    // Write min from RAM address 01H
    I2C_STOP();
 }
 void set_tsag(){
 r0=read_port_a();
 hour=r0;
 if(hour>=0x24){hour=0x23;}
     I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x02);                   // Request hour RAM address at 02H
 
    I2C_Write(hour);                    // Write hour from RAM address 02H
    I2C_STOP();
 }
 
 
 void set_sar(){
 r0=read_port_a();
 month=r0;
 if(month>=0x13){month=0x12;}
 I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x05);                   // Request hour RAM address at 02H
 
    I2C_Write(month);                    // Write hour from RAM address 02H
    I2C_STOP();
 }
 void set_udur(){
 r0=read_port_a();
 date=r0;
 if(date>=0x32){date=0x31;}
 I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x04);                   // Request udur RAM address at 04H
 
    I2C_Write(date);                    // Write udur from RAM address 04H
    I2C_STOP();
    
 }
 
 int16 bcd_tsagmin(int16 massive_tsag){
   buhel=massive_tsag/100;
   uldegdel=massive_tsag%100;
   if(uldegdel>=60){
      buhel++;
      uldegdel=uldegdel-60;
   }
   
      uld_0=uldegdel%10;
      uld_1=uldegdel/10;
      uld_1=uld_1<<4;
      uld_1=uld_1 & 0xf0;
      uld_0=uld_0 | uld_1;
   
   b0=buhel%10;
   b1=buhel/10;
   b1=b1<<4;
   b1=b1 & 0xf0;
   b0= b0 | b1;
   tsagmin_2=make16(b0,uld_0);
 return tsagmin_2;
 }
 
#int_EXT
void  EXT_isr(void) 
{
output_a(0x00);
output_e(0x00);

setbit=bit_test(port_e,2);
if(setbit==1){
switch (port_e){
   case 4: mode=4;break;
   case 5: mode=5;break;
   case 6: mode=6;break;
   case 7: mode=7;break;
}
}
else{
//secund noilloj bga heseg
if(port_a==0x20){
I2C_Start();                          // Start I2C communication
I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
I2C_Write(0x00);                   // Request sec RAM address at 02H
I2C_Write(1);                    // Write sec from RAM address 00H
I2C_STOP();
}
}
}
 void set_year(){
   I2C_Start();                          // Start I2C communication
 
    I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(0x06);                   // Request year RAM address at 06H
 
    I2C_Write(0x20);                    // Write udur from RAM address 04H
    I2C_STOP();
 }

void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
set_tris_a(0xff);
set_tris_e(0xff);
set_tris_d(0x00);
set_tris_b(0x03);
set_tris_c(0x00);
output_a(0x00);
output_b(0x00);
output_d(0x00);
output_e(0x00);


led=1;
delay_ms(800);
led=0;
delay_ms(800);
set_year();
//set_time0(0x09,0x15,0x01,0x01);

for(;;){
  rtc_getdate();
if(hour==0x15 && min==0x59 && sec>=0x57){hassan_sec=1;}
if(hour==0x21 && min==0x59 && sec>=0x57){hassan_sec=1;}
if(hour==0x03 && min==0x59 && sec>=0x57){hassan_sec=1;}
if(hour==0x09 && min==0x59 && sec>=0x57){hassan_sec=1;}


set_sec();

setbit=bit_test(port_e,2);


if(mode==4){set_min(); mode=0;}
if(mode==5){set_tsag(); mode=0;}
if(mode==6){set_udur(); mode=0;}
if(mode==7){set_sar(); mode=0;}

port_e=0;

sec0=sec&0x0f;
sec1=sec&0xf0;
sec1=sec1>>4;

min0=min&0x0f;
min1=min&0xf0;
min1=min1>>4;

tsag0=hour&0x0f;
tsag1=hour&0xf0;
tsag1=tsag1>>4;

sar0=month&0x0f;
sar1=month&0xf0;
sar1=sar1>>4;

day0=date&0x0f;
day1=date&0xf0;
day1=day1>>4;

if(port_e==0){
port_d=shfr[sec0];
port_d=port_d|0x80;
digit0=1;
delay_ms(10);
digit0=0;
delay_ms(1);
port_d=shfr[sec1];
digit1=1;
delay_ms(10);
digit1=0;
delay_ms(1);

port_d=shfr[min0];
port_d=port_d|0x80;
digit2=1;
delay_ms(10);
digit2=0;
delay_ms(1);
port_d=shfr[min1];
digit3=1;
delay_ms(10);
digit3=0;
delay_ms(1);
}

if(port_e==1){
port_d=shfr[min0];
port_d=port_d|0x80;
digit0=1;
delay_ms(10);
digit0=0;
port_d=shfr[min1];
digit1=1;
delay_ms(10);
digit1=0;
delay_ms(5);

port_d=shfr[tsag0];
digit2=1;
delay_ms(10);
digit2=0;
port_d=shfr[tsag1];
digit3=1;
delay_ms(10);
digit3=0;
delay_ms(10);
}

if(port_e==0x03 || port_e==2){
port_d=shfr[day0];
digit0=1;
delay_ms(10);
digit0=0;
port_d=shfr[day1];
digit1=1;
delay_ms(10);
digit1=0;
delay_ms(10);

port_d=shfr[sar0];
digit2=1;
delay_ms(10);
digit2=0;
port_d=shfr[sar1];
digit3=1;
delay_ms(10);
digit3=0;
delay_ms(10);
}
//starts of gerel on/of
tsagmin=make16(hour,min);
sarudur=make16(month,date);
if(month==1 || month==2 || month==0x12 || month==0x11){
  if(tsagmin<=0x1650 && tsagmin>=0x0820){
      //led is off
      led=0;
  }
  else{
   //led is on
   led=1;
  }
}

if(sarudur>=0x0301 && sarudur<=0x0315){
  if(tsagmin>=0x0800 && tsagmin<=0x1836){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x0316 && sarudur<=0x0331){
  if(tsagmin>=0x0704 && tsagmin<=0x1858){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x0400 && sarudur<=0x0415){
  if(tsagmin>=0x0631 && tsagmin<=0x1921){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x0416 && sarudur<=0x0431){
  if(tsagmin>=0x0602 && tsagmin<=0x1943){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}

if(sarudur>=0x0500 && sarudur<=0x0515){
  if(tsagmin>=0x0535 && tsagmin<=0x2004){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x0516 && sarudur<=0x0531){
  if(tsagmin>=0x0513 && tsagmin<=0x2024){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}

if(sarudur>=0x0600 && sarudur<=0x0615){
  if(tsagmin>=0x0457 && tsagmin<=0x2043){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x0616 && sarudur<=0x0631){
  if(tsagmin>=0x0452 && tsagmin<=0x2053){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}

if(sarudur>=0x0700 && sarudur<=0x0715){
  if(tsagmin>=0x0505 && tsagmin<=0x2050){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x0716 && sarudur<=0x0731){
  if(tsagmin>=0x0527 && tsagmin<=0x2029){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}

if(sarudur>=0x0800 && sarudur<=0x0815){
  if(tsagmin>=0x0545 && tsagmin<=0x2007){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x0816 && sarudur<=0x0831){
  if(tsagmin>=0x0608 && tsagmin<=0x1936){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}

if(sarudur>=0x0900 && sarudur<=0x0915){
  if(tsagmin>=0x0628 && tsagmin<=0x1905){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x0916 && sarudur<=0x0931){
  if(tsagmin>=0x0649 && tsagmin<=0x1834){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}

if(sarudur>=0x1000 && sarudur<=0x1015){
  if(tsagmin>=0x0713 && tsagmin<=0x1800){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}
if(sarudur>=0x1016 && sarudur<=0x1031){
  if(tsagmin>=0x0734 && tsagmin<=0x1736){
   //off
   led=0;
  }
  else{
  //on
  led=1;
  }
}

if(sec>=0x60){
I2C_Start();                          // Start I2C communication
I2C_Write(0xd0);                   // connect to DS1307 by sending its ID on I2c Bus
I2C_Write(0x00);                   // Request sec RAM address at 02H
I2C_Write(1);                    // Write sec from RAM address 00H
I2C_STOP();
}

}
}

