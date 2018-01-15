#include "C:\Users\huannc\Desktop\Projects\Khoa cua so\khoaso.h"

void Init_LCD();
void WrCmd_LCD(unsigned char cmd);
void WrData_LCD(unsigned char data);
void WrStr_LCD(unsigned char *s);
void button();
void button_password();
void button_check();
void check_password();

unsigned char password[4], check[4];
unsigned int i,k,j, value;
unsigned char str[20];

//LCD code
void WrCmd_LCD(unsigned char cmd)
{
    output_low(PIN_A0);
    output_high(PIN_A1);
    output_b(cmd);
    delay_ms(10);
    output_low(PIN_A1);
    delay_ms(10);
}

void WrData_LCD(unsigned char data)
{
    output_high(PIN_A0);
    output_high(PIN_A1);
    output_b(data);
    delay_ms(10);
    output_low(PIN_A1);
    delay_ms(10);
}

void WrStr_LCD(unsigned char *s)
{
   while(*s)
   {
       WrData_LCD(*s);
       s++;
   }
}

void Init_LCD(void)
{
    output_low(PIN_A0);
    output_low(PIN_A1);
    output_b(0);
    delay_ms(200);
    WrCmd_LCD(0x30);
    delay_ms(50);
    WrCmd_LCD(0x30);
    delay_ms(110);
    WrCmd_LCD(0x30);
    delay_ms(10);
    WrCmd_LCD(0x38);
    delay_ms(10);
    WrCmd_LCD(0x0C);
    delay_ms(10);
    WrCmd_LCD(0x06);
    delay_ms(10);
    WrCmd_LCD(0x01);
    delay_ms(10);
}

void SetCursor_LCD(unsigned char m,unsigned char n)
{
    if (m==1)
    {
        WrCmd_LCD(0x80+n);
        delay_ms(10);
    }
    else
    {
        WrCmd_LCD(0xC0+n);
        delay_ms(10);
    }
}

void button()
{
    while(input(PIN_C4)==0)
    {}
    while(input(PIN_C4)==1)
    {
      
      value=(input_c()<<4)>>4;
      delay_ms(10);    
      if (value>7)
         value=value-8;
      else if (value<6)
         value=value+8;
    }
}

void button_password()
{
   if (value<10)
   {
      WrData_LCD(0x2A);
      delay_ms(10);
      password[i]=value;
   }
   else if (value==10)              
   {
      WrCmd_LCD(0x10);
      delay_ms(10);
      WrData_LCD(' ');
      delay_ms(10);
      WrCmd_LCD(0x10);
      i=i-2;                      
   }
   else 
   {
      i--;
   }        
}

void check_password()
{
   for (i=0;i<4;i++)
   {
      if (check[i]==password[i])
      j++;
   }
}
   

void button_check()
{
   if (value<10)
   {
      WrData_LCD(0X2A);
      delay_ms(10);
      check[i]=value;
   }
   else if (value==10)              
   {
      WrCmd_LCD(0x10);
      delay_ms(10);
      WrData_LCD(' ');
      delay_ms(10);
      WrCmd_LCD(0x10);
      i=i-2;                      
   }
   else 
   {
      i--;
   }        
}

void open() //60 Degree
{
  for(i=0;i<50;i++)
  {
    output_high(PIN_A3);
    Delay_us(1150);
    output_low(PIN_A3);
    Delay_us(18850);
  }
}

void lock() //120 Degree
{
  
  for(i=0;i<50;i++)
  {
    output_high(PIN_A3);
    Delay_us(1850);
    output_low(PIN_A3);
    Delay_us(18150);
  }
}

//Main
void main()
{
   set_tris_b(0x00);
   set_tris_a(0x00);
   set_tris_c(0X1F);
   output_a(0);
   Init_LCD();
   SetCursor_LCD(1,0);
   sprintf(str,"Tao MK:");
   WrStr_LCD(str);
   delay_ms(10);
   for (i=0;i<4;i++)
   {
      button();
      button_password();       
   }
Loop:WrCmd_LCD(0x01);
     delay_ms(10);
     lock();
     
   while(1)
   {
      j=0;
      button();
      if (value==11)
      {
         SetCursor_LCD(1,0);
         delay_ms(10);
         sprintf(str,"Nhap MK:");
         WrStr_LCD(str);
         delay_ms(10);         
         for (i=0;i<4;i++)
         {
            button();                     
            button_check();
        }
        check_password();
        if (j!=4)
        {
            WrCmd_LCD(0x01);
            delay_ms(10);
            SetCursor_LCD(1,0);
            delay_ms(10);
            sprintf(str,"Sai MK");
            WrStr_LCD(str);
            delay_ms(2000);            
            goto Loop;            
        }
        else
        {
            WrCmd_LCD(0x01);
            delay_ms(10);
            SetCursor_LCD(1,0);
            delay_ms(10);
            sprintf(str,"MK chinh xac");
            WrStr_LCD(str);
            delay_ms(10);
            open();
      Loop2:for (k=0;k<255;k++)
            {
               for(i=0;i<255;i++)
               {
                  for (j=0;j<57;j++)
                  {
                     if (input(PIN_C4)==1)
                     goto Loop1;
                  }
               }
            }
            WrCmd_LCD(0x01);
            delay_ms(10);
            sprintf(str,"Cua chua dong");
            WrStr_LCD(str);
            delay_ms(10);
            output_high(PIN_A2);
      Loop1:button();
            if (value==12)
            {
                lock();
                output_low(PIN_A2);
                WrCmd_LCD(0x01);
                sprintf(str,"Cua dong");
                WrStr_LCD(str);
                delay_ms(2000);
                goto Loop;
            }
            else
                goto Loop2;
            
        }
     }
        else if (value==13)
        {
         SetCursor_LCD(1,0);
         sprintf(str,"Nhap MK cu :");
         WrStr_LCD(str);
         delay_ms(10);
         for (i=0;i<4;i++)
         {
            button();
            button_check();
         }
         check_password();
         if (j!=4)
         {
            WrCmd_LCD(0x01);
            delay_ms(10);
            SetCursor_LCD(1,0);
            delay_ms(10);
            sprintf(str,"Sai MK");
            WrStr_LCD(str);
            delay_ms(2000);
            j=0;
            goto Loop;
         }
         else
         {
            SetCursor_LCD(2,0);
            delay_ms(10);    
            sprintf(str,"Nhap MK moi:");
            WrStr_LCD(str);
            delay_ms(10);
            for (i=0;i<4;i++)
            {
               button();
               button_password();
            }
            WrCmd_LCD(0x01);
            delay_ms(10);
            sprintf(str,"Hoan tat cai dat");
            WrStr_LCD(str);
            delay_ms(2000);
            j=0;
            goto Loop;
         }
      }  
   }  
}
            
            
            
         
         
         
   
      
         
   
   

 

