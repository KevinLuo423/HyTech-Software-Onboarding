#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // Required for sockaddr_in
#include <unistd.h>     // Required for write()
#include <stdio.h>      /* for fprintf */
#include <string.h>     /* for memcpy */
#include <netdb.h>      /* for gethostbyname */
#include <string>
#include "simpleMessage.pb.h"
#include <random>

/* paddr: prints the IP address in a standard decimal dotted format */
void paddr(unsigned char *a) {
    printf("%d.%d.%d.%d\n", a[0], a[1], a[2], a[3]);
}

int main(int argc, char **argv) {

    int port = 8080;	/* port number */
    int nbytes;
    const char* host = "localhost";
    int fd;
    struct hostent* hp;     /* host information */
    struct sockaddr_in servaddr;    /* server address */
    
    // Creating a Socket
    // fd "file descriptor" or the id that the OS assigns to the socket
    // AF_INET is specifying to use the IPv4 address family
    // SOCK_DGRAM is the type of service which in this case is virtual circuit service (UDP)
    // 0 is the specific protocol to run and there is no protocols for SOCK_DGRAM so we use 0
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket");
        return 0;
    }

    // Connecting the socket
    //int connect(int socket, const struct sockaddr *address, socklen_t address_len);

    // struct  hostent {
    // 	char    *h_name;        /* official name of host */
    // 	char    **h_aliases;    /* alias list */
    // 	int     h_addrtype;     /* host address type */
    // 	int     h_length;       /* length of address */
    // 	char    **h_addr_list;  /* list of addresses from name server */
    // };



    /* fill in the server's address and data */
    memset((char*)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // host to network short : convert a number into a 16-bit network representation
    servaddr.sin_port = htons(port);
    
    /* look up the address of the server given its name */
    // accepts a host name and returns a hostent structure
    hp = gethostbyname(host);
    if (!hp) {
        fprintf(stderr, "could not obtain address of %s\n", host);
        return 0;
    } else if (hp->h_addrtype != AF_INET) {
        fprintf(stderr, "%s returned incorrect address type\n", host);
        return 0;
    } else if (hp->h_length != 4) {
        fprintf(stderr, "%s did not return 32-bit IPv4 address\n", host);
        return 0;
    }

    memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);
    paddr((unsigned char*)hp->h_addr_list[0]);

    /* connect to the server */
    if (connect(fd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        perror("connection failed");
        return 0;
    }


    // send 20 bytes to server
    std::string out_buffer;
    socklen_t alen = sizeof(servaddr);
    std::srand(std::time(nullptr));
    simple::SimpleMessage message;
    message.set_sender_name("the client");
    message.set_data(std::rand() % 100000 + 1);
    if (message.SerializeToString(&out_buffer) != true) {
        printf("couldnt serialize\n");
    };
    nbytes = sendto(fd, out_buffer.data(), out_buffer.size(), 0, 
                        (struct sockaddr *)&servaddr, alen);

    simple::SimpleMessage messageBack;
    char msg_buffer[1024];
    nbytes = recvfrom(fd, msg_buffer, sizeof(msg_buffer), 0, 
                          (struct sockaddr *)&servaddr, &alen);
    messageBack.ParseFromString(msg_buffer);
    printf("Client: sender=%s data=%d\n", messageBack.sender_name().c_str(), messageBack.data());
}