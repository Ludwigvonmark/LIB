
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "AXSML.h"
#include "AXGL.h"

#define PORT "4950"
#define MAXBUFLEN 729

char data [729];
char inst [729];
char AXDip[27];


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    memset(inst, 0, sizeof inst);
memset(AXDip, 0, sizeof AXDip);


int idse= ISE ();
int idsmi=ISMI ();
int idsmd=ISMD ();
std::cout<<"AXNET V0.3 C++"<<std::endl;


strncpy(AXDip,"192.168.1.103", sizeof(AXDip));


int sockfdD;
    struct addrinfo hintsD, *servinfoD, *pD;
    int rvD;
    int numbytesD;

    memset(&hintsD, 0, sizeof hintsD);
    hintsD.ai_family = AF_UNSPEC;
    hintsD.ai_socktype = SOCK_DGRAM;



    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
       // fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }






                if ((rvD = getaddrinfo(AXDip, PORT, &hintsD, &servinfoD)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rvD));
        return 1;
    }
    // loop through all the results and make a socket
    for(pD = servinfoD; pD != NULL; pD = pD->ai_next) {
        if ((sockfdD = socket(pD->ai_family, pD->ai_socktype,
                pD->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;}
        break; }

    if (pD == NULL) {
        fprintf(stderr, "talker: failed to bind socket\n");
        return 2;
    }



struct timeval tv;
tv.tv_sec = 0;
tv.tv_usec = 500000;
if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
    perror("Error");
}
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
       // fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);

   // printf("listener: waiting to recvfrom...\n");

    addr_len = sizeof their_addr;

//printf("listener: packet contains \"%s\"\n", inst);

while(1){


 if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 ,0,
        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        //perror("recvfrom");
        //exit(1);
       // printf("no data to read\n");
    }
    else{
    buf[0]='X';
strcpy(inst,buf);
    //printf("listener: got packet from %s\n",
       // inet_ntop(their_addr.ss_family,
         //   get_in_addr((struct sockaddr *)&their_addr),
         //s, sizeof s));
   // printf("listener: packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
        WSMD(inst,idsmd, idse);
    //printf("listener: packet contains \"%s\"\n", buf);
    }



if(AXDip[0]!=0){//AXNET waiting for contact

if(inst[0]==0){
strncpy(data,"AX\0", sizeof(data));
}

else{
strncpy(data, RSMI(idsmi, idse), sizeof(data));
}
//strncpy(data,"hi AXNET", sizeof(data));

    if ((numbytesD = sendto(sockfdD,data, strlen(data), 0,
             pD->ai_addr, pD->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }

}

//ISstd::cout<<data<<"  "<<inst<<std::endl;

}

    close(sockfd);

    freeaddrinfo(servinfoD);
    close(sockfdD);



    return 0;
}
