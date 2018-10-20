//      setserial.c
//      
//      Copyright 2011 Bruno Chianca Ferreira <brunobcf@gmail.com>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      

#include <setserial.h>
#include <termios.h>

struct termios options; //Get options struct

int setserial(int fd, int speed, char *opt)
{
	tcgetattr(fd, &options); // Get options
	
	/*From now on setting speed....*/
	if (speed==50)
	{
		cfsetispeed(&options, B50);
		cfsetospeed(&options, B50);
	}
	if (speed==75)
	{
		cfsetispeed(&options, B75);
		cfsetospeed(&options, B75);
	}
	if (speed==110)
	{
		cfsetispeed(&options, B110);
		cfsetospeed(&options, B110);
	}
	if (speed==134)
	{
		cfsetispeed(&options, B134);
		cfsetospeed(&options, B134);
	}
	if (speed==150)
	{
		cfsetispeed(&options, B150);
		cfsetospeed(&options, B150);
	}
	if (speed==200)
	{
		cfsetispeed(&options, B200);
		cfsetospeed(&options, B200);
	}
	if (speed==300)
	{
		cfsetispeed(&options, B300);
		cfsetospeed(&options, B300);
	}
	if (speed==600)
	{
		cfsetispeed(&options, B600);
		cfsetospeed(&options, B600);
	}
	if (speed==1200)
	{
		cfsetispeed(&options, B1200);
		cfsetospeed(&options, B1200);
	}
	if (speed==1800)
	{
		cfsetispeed(&options, B1800);
		cfsetospeed(&options, B1800);
	}
	if (speed==2400)
	{
		cfsetispeed(&options, B2400);
		cfsetospeed(&options, B2400);
	}
	if (speed==4800)
	{
		cfsetispeed(&options, B4800);
		cfsetospeed(&options, B4800);
	}
	if (speed==9600)
	{
		cfsetispeed(&options, B9600);
		cfsetospeed(&options, B9600);
	}
	if (speed==19200)
	{
		cfsetispeed(&options, B19200);
		cfsetospeed(&options, B19200);
	}
	if (speed==38400)
	{
		cfsetispeed(&options, B38400);
		cfsetospeed(&options, B38400);
	}
	if (speed==57600)
	{
		cfsetispeed(&options, B57600);
		cfsetospeed(&options, B57600);
	}
	if (speed==115200)
	{
		cfsetispeed(&options, B115200);
		cfsetospeed(&options, B115200);
	}

	/*Finished setting speed.*/
	
	
	switch (opt[1]) 
	{
		case('8'):	//8N1
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		break;
		
		case('7'):
		switch (opt[2])
		{
			case('E'): //7E1
			options.c_cflag |= PARENB;
			options.c_cflag &= ~PARODD;
			options.c_cflag &= ~CSTOPB;
			options.c_cflag &= ~CSIZE;
			options.c_cflag |= CS7;
			break;
		
			case('O'): //7O1
			options.c_cflag |= PARENB;
			options.c_cflag |= PARODD;
			options.c_cflag &= ~CSTOPB;
			options.c_cflag &= ~CSIZE;
			options.c_cflag |= CS7;
			break;
			
			case('S'): //7S1
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~CSTOPB;
			options.c_cflag &= ~CSIZE;
			options.c_cflag |= CS8;
			break;
			
			default:
			break;
		}
		
		default:
		break;
	}
	tcsetattr(fd, TCSANOW, &options);
	return 0;
}

