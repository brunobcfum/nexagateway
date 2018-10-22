#include "SerialPort.h"


Logger serial_logger;

SerialPort::SerialPort()
{
}

SerialPort::~SerialPort()
{
}

int SerialPort::open_port(const char *cPort){
    string log {"Serial: port open "};
    /*
     * O_NOCTTY
    If set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process. 
     * O_RDWR
    Open for reading and writing. The result is undefined if this flag is applied to a FIFO.
     * O_NDELAY or O_NONBLOCK
    The open will return without waiting for the device to be ready or available; subsequent behavior of the device is device specific. 
     * */
    port_fd = open(cPort, O_NOCTTY | O_NDELAY | O_RDWR); // Open the serial port file descriptor with some options 
	if (port_fd == -1){
		//Error opening port
        return (-1);
	}
	else
		fcntl(port_fd, F_SETFL, 0); //Apply options to file descriptor
    log = log + cPort;
    serial_logger.log("HAAB_NEXA",log);
	return (port_fd);
}

int SerialPort::write_serial(char *buffer)
{
    string log;
    log = "Serial: ";
	int iBytes=0,iIndex=0;
	while(buffer[iIndex]!=0){
		iBytes += write(port_fd,&buffer[iIndex++],1); //write data to serial port byte per byte until buffer is empty
	}
    log = log + std::to_string(iBytes);
    log = log + " bytes sent to serial port." ;
    serial_logger.log("HAAB_NEXA",log);
	return(iBytes); //return the number of bytes written
}

int SerialPort::set_serial(int speed, char *opt)
{
	tcgetattr(port_fd, &options); // Get options
	
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
	
	
	switch (opt[1]) //This needs to  be fixed.
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
	tcsetattr(port_fd, TCSANOW, &options);
	return 0;
}

int SerialPort::get_portfd(){
    return port_fd;
}

