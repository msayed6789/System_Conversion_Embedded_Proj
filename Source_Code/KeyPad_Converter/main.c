/*
 * KeyPad_Converter.c
 *
 * Created: 12/12/2022 6:32:47 PM
 * Author : M.Sayed
 */ 



#include "DIO_Interface.h"
#include "LCD.h"
#include "KeyPad.h"

u32 Binary_toDecimal(u32 num);
u32 Hexadecimal_toDecimal (u8* hex_arr,u8 index);

int main(void)
{
	DIO_init();
	LCD_init();
	u8 hex_arr[10]={0};
	u8 index =1;
    u8 k,process_f,process_t,flag=0;
	u8 u8_End_Flag=0;
    u32 num=0;
    LCD_GoTo(0,0);
    LCD_WriteString("Hello:- Mohamed Sayed");
    _delay_ms(1000);
    LCD_Clear();
    LCD_WriteString("Convert from");
    LCD_GoTo(1,0);
    LCD_WriteString("1-D 2-Hex 3-B");
    while (1)
    {
	    k=KEYPAD_GetKey();
	    if (k!=NO_KEY&&flag==0)
	    {
		    LCD_Clear();
		    LCD_WriteString("Convert   to");
		    switch(k)
		    {
			    case '1':
			    process_f ='D';
			    LCD_GoTo(0,8);
			    LCD_WriteChar(process_f);
			    LCD_GoTo(1,0);
			    LCD_WriteString(" 2-Hex 3-B");
			    break;
			    case '2':
			    process_f ='H';
			    LCD_GoTo(0,8);
			    LCD_WriteChar(process_f);
			    LCD_GoTo(1,0);
			    LCD_WriteString("1-D 3-B");
			    break;
			    case '3':
			    process_f ='B';
			    LCD_GoTo(0,8);
			    LCD_WriteChar(process_f);
			    LCD_GoTo(1,0);
			    LCD_WriteString("1-D 2-Hex");
			    break;
		    }
		    while(1)
		    {
			    k=KEYPAD_GetKey();
			    if (k!=NO_KEY)
			    {
				    break;
			    }
		    }
		    switch(k)
		    {
			    case'1':
			    process_t='D';
			    LCD_Clear();
			    LCD_GoTo(0,0);
			    LCD_WriteChar(process_f);
			    LCD_GoTo(1,0);
			    LCD_WriteChar(process_t);
			    LCD_GoTo(0,2);
			    break;
			    case'2':
			    process_t='H';
			    LCD_Clear();
			    LCD_GoTo(0,0);
			    LCD_WriteChar(process_f);
			    LCD_GoTo(1,0);
			    LCD_WriteChar(process_t);
			    LCD_GoTo(0,2);
			    break;
			    case'3':
			    process_t='B';
			    LCD_Clear();
			    LCD_GoTo(0,0);
			    LCD_WriteChar(process_f);
			    LCD_GoTo(1,0);
			    LCD_WriteChar(process_t);
			    LCD_GoTo(0,2);
			    break;
		    }
		    flag=1;
		    k=NO_KEY;
	    }
	    
	    if (k!=NO_KEY&&flag==1)
	    {
		    LCD_WriteChar(k);
		    if (k>='0' && k<='9')
		    {
				if (process_f=='H')
				{
					hex_arr[index]=k-'0';
					index++;
				}
				else 
				{
				  num=num*10+(k-'0');
				}
		    }
			
			else 
			{
				switch (k)
				{
					case 'A':
					hex_arr[index]=10;
					index++;
					break;
					case 'B':
					hex_arr[index]=11;
					index++;
					break;
					case 'C':
					hex_arr[index]=12;
					index++;
					break;
					case 'D':
					hex_arr[index]=13;
					index++;
					break;
					case 'E':
					hex_arr[index]=14;
					index++;
					break;
					case 'F':
					hex_arr[index]=15;
					index++;
					break;
				}
			}
			
		    
		    if (k=='=')
		    {
			    
			    if (process_f=='D'&& process_t =='B')
			    {
				    LCD_GoTo (1,2);
				    LCD_WriteBinary(num);
			    }
			    
			    
			    else if (process_f=='D'&& process_t =='H')
			    {
				    LCD_GoTo (1,2);
				    LCD_WeiteHex(num);
			    }
			    
			    else if (process_f=='B'&& process_t =='D')
			    {
				    u32 result=Binary_toDecimal(num);
					if (result==-1)
					{
						LCD_Clear();
						LCD_WriteString("Binary Number should be 0 or 1");
						_delay_ms(1000);
						k='c';
					}
				    LCD_GoTo (1,2);
				    LCD_WriteNumber (result);
			    }
			    
			    else if (process_f=='B'&& process_t =='H')
			    {
				    u32 result=Binary_toDecimal(num);
					if (result==-1)
					{
						LCD_Clear();
						LCD_WriteString("Binary Number should be 0 or 1");
						_delay_ms(1000);
						k='c';
					}
				    LCD_GoTo (1,2);
				    LCD_WeiteHex(result);
			    }
			 else if (process_f=='H'&& process_t =='D')
			 {
				 u32 result=Hexadecimal_toDecimal(hex_arr,index);
				 LCD_GoTo (1,2);
				 LCD_WriteNumber(result);
				 
			 }
			 else if (process_f=='H'&& process_t =='B')
			 {
				 u32 result=Hexadecimal_toDecimal(hex_arr,index);
				 LCD_GoTo (1,2);
				 LCD_WriteBinary(result); 
			 }   
			 u8_End_Flag=1;
		   }
		   while (u8_End_Flag==1)
		   {
			 k=KEYPAD_GetKey();
		    if (k=='c')
		    {
			    LCD_Clear();
			    LCD_WriteString("Convert from");
			    LCD_GoTo(1,0);
			    LCD_WriteString("1-D 2-Hex 3-B");
			    num=0;
			    flag=0;
				u8_End_Flag=0;
		    }
		   }
		    
	    }   
    }
 }


    u32 Binary_toDecimal(u32 num)
    {
	    u8 i,j=1,rem=0;
	    u32 a=num,k=1,count=0;
	    rem=a%10;
	    a=a/10;
		if (rem>1)
		{
			return -1;
		}
	    count=count+rem;
	    while (a!=0)
	    {
		    rem=a%10;
			if (rem>1)
			{
				return -1;
			}
		    for (i=0;i<j;i++)
		    {
			    k=k*2;
		    }
		    count=count+rem*k;
		    k=1;
		    a=a/10;
		    j++;
	    }
	    return count; 
    }
	
	u32 Hexadecimal_toDecimal (u8* hex_arr,u8 index)
	{
	  u8 i,j=0,k=0;
	  u32 count=0,base=1;
	  for (i=index-1;i>=1;i--)
	  { 
		for (k=0;k<j;k++)
		{
			base=base*16;
		}
		count=count+hex_arr[i]*base;
		j++;
		base=1;
	  }
	  for (i=0;i<10;i++)
	  {
		  hex_arr[i]=0;
	  }
	  index=1;
	  	return count;
	}
    


