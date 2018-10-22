#include <iostream>
#include <string>
#include <cstdlib>
#include <syslog.h>
#include <SerialPort.h>
#include <NexaSocket.h>
#include <Logger.h>

using namespace std;

void parse_args(int _argc, char** _argv);
void help();

SerialPort serialPort;
NexaSocket nexaSocket;
Logger logger;

string port {"/dev/ttyUSB0"};
string opt {"8N1"};
int speed  {9600};
char *received_buf;
string sockport {"5697"};

int main(int argc, char** argv){
       
    parse_args(argc, argv);
    
	cout<< "Starting HAAB Nexa 2.0"<< endl;
    logger.log("HAAB_NEXA","Starting server");
    
    
    if (serialPort.open_port(port.c_str())<0) {
        //cout<< "open_port: Unable to open serial port"<< endl;
        logger.log("HAAB_NEXA","open_port: Unable to open serial port");
    } else {
        //cout<< "Port open with fd: "<< serialPort.get_portfd() << endl;
    }
    
    if (nexaSocket.open_socket(sockport.c_str())<0) {
        //cout<< "open_socket: Unable to open socket"<< endl;
        logger.log("HAAB_NEXA","socket: Unable to open socket");
    } else {
        //cout<< "Socket open with fd: "<< nexaSocket.get_socketid() << endl;
    }
    
    while (1){
        received_buf = nexaSocket.listener(nexaSocket.get_socketid());
        serialPort.write_serial(received_buf);
    }

    
/*    
    for (int i = 0;i<sizeof(received_buf);i++)
        cout <<received_buf[i];
    cout << endl;*/
    
    nexaSocket.close_socket(nexaSocket.get_socketid());
	return 0;
}



void parse_args(int _argc, char** _argv){
    int index  {1};
    if (_argc>1)
	{
		do
		{
			switch(_argv[index++][1])
			{
				case('s'):
				speed=atoi(_argv[index++]);
				break;

				case('p'):
				port=_argv[index++];
				break;

				case('o'):
				opt=_argv[index++];
				break;

				case('n'):
				sockport=_argv[index++];
				break;

				default:
				help();
				exit(22);
			}
		}
		while (_argv[index]!=0);
	}
	else if (_argc==1)
	{
		help();
		exit(22);
	}
    
}

void help(){
	// This function simply display help message, if running as module or service does not need this
	printf("\n");
	printf("Invalid use. See below how it should be done...\n");
	printf("./haabnexa [OPT]\n");
	printf("HAAB Nexa Gateway\n");
	printf("Possible options:\n");
	printf("-o [PORT] should be something like /dev/ttyUSB0 (linux)\n");
	printf("-o [PORT_OPTIONS] setup parity and data bits as XYZ\n");
	printf("\n");
	printf("	[XYZ]\n");
	printf("	X - Data bits can be 5,6,7 or 8\n");
	printf("	Y - Parity can O,E or N\n");
	printf("	Z - Stop bits can be 1 or 2\n");
    printf("\n");
	printf("-s [SPEED] as a integer like 9600, 14400 etc... you know...\n");
	printf("-n [SOCKET PORT] as a integer network port number, being 5697 the dedault\n");
	printf("Now try again.\n");
	printf("\n");
}
