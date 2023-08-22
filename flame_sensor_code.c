#include<lpc21xx.h>
#define bit(x) (1<<x)
#define delay for(i=0;i<35000;i++);
 
#define FLAME (IO1PIN & (1<<24)) // reads the pin
 
unsigned int i;
 
void lcd_int();	               // initializes lcd
void dat(unsigned char);	   // passes data
void cmd(unsigned char);	   // passes commands
void string(unsigned char *);  // sends char

void main()
{
    IO0DIR =0XFFF;		//initializes pin 0 as output pins
    IO1DIR = 0x0;		  // initializes pin 1 as inputpins
    lcd_int();
    cmd(0x80);			  // forces cursor beging of 1st line

    string("MIT FLAME SENSOR");
    while(1) {
            if(FLAME) {
                    string("Flame Detected");
            }
            delay;delay;
            cmd(0x01);	  // clear screen
        }
}

void lcd_int()
{
    cmd(0x38);		  // 2 lines 5 X 7 matrix 
    cmd(0x0c);		  // display on cursor off
    cmd(0x06);		  //  increase cursor to right
    cmd(0x01);		  // clear display screen
    cmd(0x80);		  // forces cursor to the begining of 1st line
}
 
void cmd(unsigned char a)
{
    IO0PIN&=0x00;
    IO0PIN|=(a<<0);
    IO0CLR|=bit(8);                //rs=0	   to treat data as command instruction
    IO0CLR|=bit(9);                //rw=0	   to write characters on lcd
    IO0SET|=bit(10);               //en=1
    delay;
    IO0CLR|=bit(10);               //en=0	   to send data in lcd EN should be 0 
}
 
void dat(unsigned char b)
{
    IO0PIN&=0x00;
    IO0PIN|=(b<<0);
    IO0SET|=bit(8);                //rs=1
    IO0CLR|=bit(9);                //rw=0
    IO0SET|=bit(10);               //en=1
    delay;
    IO0CLR|=bit(10);               //en=0
}
 
void string(unsigned char *p)
{
    while(*p!='\0') {
        dat(*p++);
    }
}
