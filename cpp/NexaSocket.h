#ifndef NEXASOCKET_H
#define NEXASOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <Logger.h>

class NexaSocket
{
    
private:
    void *get_in_addr(struct sockaddr *sa);
    int sockfd;
    

public:
    NexaSocket();
    ~NexaSocket();
    int open_socket(const char *sock_port);
    char *listener(int sockid);
    int get_socketid();
    int close_socket(int sockid);

};

#endif // NEXASOCKET_H
