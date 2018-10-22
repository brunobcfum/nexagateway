#include "NexaSocket.h"


#define BACKLOG 10 


Logger socket_logger;

NexaSocket::NexaSocket()
{
}

NexaSocket::~NexaSocket()
{
}

void *NexaSocket::get_in_addr(struct sockaddr *sa) //gets internet address
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

char *NexaSocket::listener(int sockid){
    struct sockaddr_storage their_addr;
    socklen_t addr_len;
    size_t numbytes;
    char * buf;
    int new_fd;
    const int MAXBUFLEN {64};
    char s[INET6_ADDRSTRLEN];
    std::vector <char> received_buf;
    string log;
     
    listen(sockfd, BACKLOG); //starts listening on socket
    buf = new char[MAXBUFLEN];
    addr_len = sizeof their_addr;

    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_len);
    if (new_fd == -1) {
        perror("error in accept");
        exit(1);
    }

    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr),s, sizeof s);
    log = "Server: got connection from: ";
    log = log + s;
    socket_logger.log("HAAB_NEXA",log);

    send(new_fd, "Hello, world!", 13, 0);
    if ((numbytes = recv(new_fd, buf, MAXBUFLEN-1, 0)) == -1) {
        exit(1);
    }

    for (unsigned int i = 0; i <numbytes;i++){
        received_buf.push_back(buf[i]);
    }
    received_buf.push_back('\0');

    close(new_fd); 
    return (buf);
}

int NexaSocket::open_socket(const char *sock_port){
    struct addrinfo hints;
    struct addrinfo *servinfo, *p;
    int rv, yes=1;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    
    rv = getaddrinfo(NULL, sock_port, &hints, &servinfo);
    
    if ( rv != 0) {
        //fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    
    for(p = servinfo; p != NULL; p = p->ai_next) {
            if ((sockfd = socket(p->ai_family, p->ai_socktype, //gets file descriptor for the socket
                    p->ai_protocol)) == -1) {
                continue;
            }
            setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
            
            
            if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) { //binds the socket to our address
                close(sockfd);
                continue;
            }
            break;
    }
    if (p == NULL) {
            return 2;
    }
    freeaddrinfo(servinfo);
    return (sockfd);
}

int NexaSocket::get_socketid(){
    return(sockfd);
}

int NexaSocket::close_socket(int sockfd){
    close(sockfd);
}