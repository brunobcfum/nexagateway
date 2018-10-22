#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <Logger.h>


class SerialPort
{
private:
    int port_fd {-1};
    struct termios options; //Get options struct
    
public:
    SerialPort(); // Constructor
    ~SerialPort(); // Destructor
    int open_port(const char *cPort); //Open Serial port passed as argument
    int set_serial(int speed, char *opt); //Set some options for serial port as speed and configuration
    int write_serial(char *buffer); //Writes buffer to serial port
    int get_portfd();
};

#endif // SERIALPORT_H
