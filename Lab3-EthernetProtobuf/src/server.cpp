#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> // Required for sockaddr_in and htons
#include <stdio.h>
#include <string.h>
#include <stdlib.h>     // Required for exit()
#include <unistd.h>     // Required for read() and close()
#include <errno.h>      // Required for errno constants
#include "simpleMessage.pb.h"

int main() {

    int port = 8080;	/* port number */
	int rqst;       /* socket accepting the request */
	socklen_t alen;       /* length of address structure */
	struct sockaddr_in my_addr;    /* address of this service */
	struct sockaddr_in client_addr;  /* client's address */
	int sockoptval = 1;
    int svr;
    int nbytes;

    // Creating a Socket
    // fd "file descriptor" or the id that the OS assigns to the socket
    // our fd is called svr
    // AF_INET is specifying to use the IPv4 address family
    // SOCK_DGRAM is the type of service which in this case is virtual circuit service (UDP)
    // 0 is the specific protocol to run and there is no protocols for SOCK_DGRAM so we use 0
    // this uses TCP/IP
    if ((svr = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket");
        exit(1);
    }

    /* allow immediate reuse of the port */
    // a special operation you can call on a port
	setsockopt(svr, SOL_SOCKET, SO_REUSEADDR, &sockoptval, sizeof(int));



    // Identifying a Socket (binding the socket to a port)
    // the function doesn't take a port number as input though, but a sockaddr structure
    // bind(int socket, const struct sockaddr *address, socklen_t address_len);
    // for IP networking, we use the struct sockaddr_in that we need to fill out before using bind
    // struct sockaddr_in {
    //     __uint8_t       sin_len;
    //     sa_family_t     sin_family;  AF_INET
    //     in_port_t       sin_port;    use 0 to specify OS to choose port for you
    //     struct  in_addr sin_addr;    IP address
    //     char            sin_zero[8];
    // };
    struct sockaddr_in myaddr;
    
    // set everything in myaddr to 0
    memset((char *)&myaddr, 0, sizeof(myaddr));

    myaddr.sin_family = AF_INET;
    // htonl is "host to network long" which converts int to a network representation due to big endian/little endian
    // INADDR_ANY means we let the OS use whatever network interface it wants (wifi or ethernet)
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(port); // using 0 would set to any port
    if (bind(svr, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        perror("bind failed");
        exit(1);
    }


    // Make the socket a listening socket
    // int listen(int socket, int backlog);
    // backlog defines the max number of pending connections that can be queued before connections are refused
    
    // the accept system call grabs the first connection request in the queue and creates a new socket for it
    // int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len)

    // if (listen(svr, 5) < 0) {
    //     perror("listen failed");
    //     exit(1);
    // }

	/* loop, accepting connection requests */
    alen = sizeof(client_addr);
	for (;;) {
		// while ((rqst = accept(svr, (struct sockaddr *)&client_addr, &alen)) < 0) {
		// 	/* we may break out of accept if the system call */
        //     /* was interrupted. In this case, loop back and */
        //     /* try again */
        //     if ((errno != ECHILD) && (errno != ERESTART) && (errno != EINTR)) {
        //             perror("accept failed");
        //             exit(1);
        //     } 
        // }

		/* the socket for this accepted connection is rqst */
		// read bytes from client here

        simple::SimpleMessage message;
        char msg_buffer[1024];
        nbytes = recvfrom(svr, msg_buffer, sizeof(msg_buffer), 0, 
                          (struct sockaddr *)&client_addr, &alen);
        message.ParseFromString(msg_buffer);
        printf("Server: sender=%s data=%d\n", message.sender_name().c_str(), message.data());

        simple::SimpleMessage messageBack;
        std::string out_buffer;
        messageBack.set_sender_name("the server");
        messageBack.set_data(123456789);
        if (messageBack.SerializeToString(&out_buffer) != true) {
            printf("couldnt serialize\n");
        };
        
        nbytes = sendto(svr, out_buffer.data(), out_buffer.size(), 0, 
                        (struct sockaddr *)&client_addr, alen);
	}

    // must use int shutdown(int socket, int how); or close() to close socket in professional projects


}