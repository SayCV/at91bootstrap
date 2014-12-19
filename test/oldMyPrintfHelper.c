
#include "div.h"

#include "test.h"

#include <stdarg.h>

/* lib/string.c */
unsigned int strlen(const char *str);

void usart_puts(const char *ptr);

/* Copyright (C) 1989, 1990, 1991, 1992 Free Software Foundation, Inc.
     Written by James Clark (jjc@jclark.com)

This file is part of groff.

groff is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

groff is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with groff; see the file COPYING.  If not, write to the Free Software
Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

#define INT_DIGITS 19		/* enough for 64 bit integer */

char *itoaLess(i)
     int i;
{
  /* Room for INT_DIGITS digits, - and '\0' */
  static char buf[INT_DIGITS + 2];
  char *p = buf + INT_DIGITS + 1;	/* points to terminating '\0' */
  if (i >= 0) {
    do {
      *--p = '0' + (i % 10);
      i /= 10;
    } while (i != 0);
    return p;
  }
  else {			/* i < 0 */
    do {
      *--p = '0' - (i % 10);
      i /= 10;
    } while (i != 0);
    *--p = '-';
  }
  return p;
}

char *itoa(int val, char *buf, unsigned radix)
{
        char *p;
        char *firstdig;
        char temp;
        unsigned digval;
        p = buf;
        if(val<0)
        { 
                *p++ = '-';
                val = (unsigned long)(-(long)val);
        }
        firstdig = p;
        do
        {
                digval = (unsigned)(mod(val, radix)); 
                val = div(val, radix);
                if(digval>9)
                {
                        *p++ = (char)(digval-10+'a');
                }
                else
                {
                        *p++=(char)(digval+'0');
                }
        }while(val>0); 
        *p--='\0';
        do
        {
                temp=*p;
                *p=*firstdig;
                *firstdig=temp;
                --p;
                ++firstdig;
        }while(firstdig<p);
        return buf; 
}

void usart_putint( int num )
{
  unsigned char buffer[10];

  itoa( num, buffer, 16 );
  usart_puts( buffer );
}

void usart_printf (char *p_fmt, ...) {
    char    str[80u + 1u];
    uint8_t  len;
    //uint8_t  err;
    va_list vArgs;

    va_start(vArgs, p_fmt);
  
    vsprintf((char *)str, (char const *)p_fmt, vArgs);
   
    va_end(vArgs);

    len = strlen(str);
		if(len>=80) len=80;
		
    str[len] = '\0';
    usart_puts(str);
}

extern void udelay(unsigned int usec);
//udelay(33000); /* 33 ms: the maximum delay of udelay() */
void mdelay(unsigned int msec) {
	uint32_t i = 0;
	for(i = 0; i<msec; i++)
		udelay(1000); /* 1 ms */
}
