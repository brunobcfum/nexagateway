//      haabnexa.c
//
//      Copyright 2016 Bruno Chianca Ferreira <brunobcf@gmail.com>
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


#include "haabnexa.h"

//Let's set some default options
#define def_speed 9600
#define def_sockport 5697
#define def_opt "8N1"
#define def_port "/dev/ttyUSB0"
#define BACKLOG 10     // how many pending connections queue will hold
#define MAXDATASIZE 100 // max number of bytes we can get at once

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

void logger(char *topic, char *message){
  openlog(topic, LOG_PID|LOG_CONS, LOG_USER);
  syslog(LOG_MAKEPRI(LOG_USER, LOG_INFO), message);
  closelog();
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sockfd, new_fd, numbytes;  // listen on sock_fd, new connection on new_fd
	int fd,iBytesSent,index=1,speed;
	char *opt,*port,*data,*sockport;
  char buf[MAXDATASIZE];
  char templog[128];
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	//Start with defaults
	opt=def_opt;
	port=def_port;
	speed=def_speed;
	sockport=def_sockport;


  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // use my IP
	if (argc>1)
	{
		do
		{
			switch(argv[index++][1])
			{
				case('s'):
				speed=atoi(argv[index++]);
				break;

				case('o'):
				port=argv[index++];
				break;

				case('p'):
				opt=argv[index++];
				break;

				case('n'):
				sockport=argv[index++];
				break;

				default:
				help();
				exit(22);
			}
		}
		while (argv[index]!=0);
	}
	else if (argc==1)
	{
		help();
		exit(22);
	}
  logger("haabnexa", "Starting server");
	if ((rv = getaddrinfo(NULL, sockport, &hints, &servinfo)) != 0) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			return 1;
	}
	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
			if ((sockfd = socket(p->ai_family, p->ai_socktype,
							p->ai_protocol)) == -1) {
					perror("server: socket");
					continue;
			}

			if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
							sizeof(int)) == -1) {
					perror("setsockopt");
					exit(1);
			}

			if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
					close(sockfd);
					perror("server: bind");
					continue;
			}

			break;
	}

	freeaddrinfo(servinfo); // all done with this structure


	fd=openserial(port); //Get serial port to the programm as a file descriptor
	setserial(fd,speed,opt); //Setup the serial port
	printf("Serial port open with file descriptor number: %i\n",fd);
  sprintf(templog,"Serial port open at: %s\n",port);
  logger("haabnexa", templog);
	/*while(1)
	{

		iBytesSent = writeserial(fd,data); //Send string to serial port
		printf("%i bytes were sent to the open serial port!\n",iBytesSent);
		printf("%s was sent\n", data);

	}*/

	if (p == NULL)  {
			fprintf(stderr, "server: failed to bind\n");
			exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
			perror("listen");
			exit(1);
	}

	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
			perror("sigaction");
			exit(1);
	}
  logger("haabnexa", "Server started. waiting for connections");
  printf("server: waiting for connections...\n");


	while(1) {  // main accept() loop
			sin_size = sizeof their_addr;
			new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
			if (new_fd == -1) {
					perror("accept");
					continue;
			}

			inet_ntop(their_addr.ss_family,
					get_in_addr((struct sockaddr *)&their_addr),
					s, sizeof s);
			printf("server: got connection from %s\n", s);
		    sprintf(templog,"server: got connection from %s\n", s);
		    logger("haabnexa", templog);

			if (!fork()) { // this is the child process
					close(sockfd); // child doesn't need the listener
					/*if (send(new_fd, "Hello, world!", 13, 0) == -1)
							perror("send");*/
          if ((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
          }
          buf[numbytes] = '\0';
    			iBytesSent = writeserial(fd,buf); //Send string to serial port
    			printf("%i bytes were sent to the open serial port!\n",iBytesSent);
    			printf("%s was sent\n", buf);
			    sprintf(templog,"command %s received and forwarded to nexa gateway!\n", buf);
			    logger("haabnexa", templog);
    			close(new_fd);
    			exit(0);
			}
			close(new_fd);  // parent doesn't need this
	}

	close(fd); //Close the fd and free the port
	return 0;
}

void help()
{
	// This function simply display help message, if running as module or service does not need this
	printf("\n");
	printf("Invalid use. See below how it should be done...\n");
	printf("./haabnexa [OPT]\n");
	printf("HAAB Nexa Gateway\n");
	printf("Possible options:\n");
	printf("-o [PORT] should be something like /dev/ttyUSB0 (linux)\n");
	printf("-p [PARITY] setup parity and data bits as XYZ\n");
	printf("\n");
	printf("	[XYZ]\n");
	printf("	X - Data bits can be 5,6,7 or 8\n");
	printf("	Y - Parity can O,E or N\n");
	printf("	Z - Stop bits can be 1 or 2\n");
  printf("\n");
	printf("-s [SPEED] as a integer like 9600, 14400 etc... you know...\n");
	printf("-n [PORT] as a integer network port number, being 5697 the dedault\n");
	printf("Now try again.\n");
	printf("\n");
}
