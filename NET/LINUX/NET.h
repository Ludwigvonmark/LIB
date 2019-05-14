#ifndef NET_H_INCLUDED
#define NET_H_INCLUDED

//C++ NETWORK  linux protocols object lib 
//JLMF 2016

//OpenSSL required, for install on ubuntu: sudo apt-get install libssl-dev  
//for compile: g++ xxx.cpp -std=c++11 -lssl -lcrypto -o xxx

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

#include <iostream>
#include <fstream> //for perror()
#include <string> // string for c++
#include <string.h> // for memset()/bzero() For C
#include <sys/socket.h> 
#include <netinet/in.h> // for sockaddr_in, hotons
#include <arpa/inet.h> // for inet_addr
#include <netdb.h> //for gethostbyname(), gethostbyaddr()
#include <netinet/tcp.h> // for TCP_NODELAY
#include <time.h> // time.h
// for https


#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define MAXDATASIZE 205410
#define BACKLOG 10


#define STDIN 0  // file descriptor for standard input

enum NET_TYPE {
    TCP_SRV_SSL,
    TCP_CLT_SSL,
    TCP_SRV,
    TCP_CLT,
    UDP,
    UDP_SSL
};


class NET{//Simple NET lib
public:

    int sockfd, new_fd, numbytes, rv, yes=1;  
    char buf[MAXDATASIZE];
    std::string RCVD;//String con los datos recibidos
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];    
    socklen_t sin_size;
    NET_TYPE CT;
    
    int sockfdD;
    struct addrinfo hintsD, *servinfoD, *pD;
    int rvD;
    int numbytesD;
    
    struct sockaddr_in ServAddr;
    struct hostent *ServInf;
    static const int iMessage = 5048576; //~ MB for the buff storage
    char message[iMessage];
    std::string request = "GET ";
    std::ofstream fid;
    int iStart, iEnd, iLength;
                    
    SSL_CTX *ctx;
    SSL *ssl;                 
                    
    std::string PORT="3590";
    
    bool CON_ERR;//Conetcion error
    
    // get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
    
//public:
   // std::string PORT="3490"; 
    std::string DR;//Last data recived
    std::string DS;//Last data to send, or sended
    
    NET(){}
    
    NET(NET_TYPE NT, std::string port="3590"){
        PORT=port;
        CT=NT;
        
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();
        SSL_load_error_strings();
        
        if((CT==NET_TYPE::TCP_SRV)){
            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_flags = AI_PASSIVE; // use my IP
        
            if ((rv = getaddrinfo(NULL, PORT.c_str(), &hints, &servinfo)) != 0) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        //return 1;
            }

    // loop through all the results and bind to the first we can
            for(p = servinfo; p != NULL; p = p->ai_next) {
                if ((sockfd = socket(p->ai_family, p->ai_socktype,
                    p->ai_protocol)) == -1) {
                    perror("server: socket");
                    continue;
                }

                if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
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

            if (p == NULL)  {
                fprintf(stderr, "server: failed to bind\n");
                exit(1);
            }
            
        
        }
        else if(CT==NET_TYPE::TCP_CLT){
            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC/*PF_INET*//*AF_INET*/;
            hints.ai_socktype = SOCK_STREAM/* | SOCK_NONBLOCK*/;
            hints.ai_flags = 0;
            

        }
        else if(CT==UDP){
                memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    
     memset(&hintsD, 0, sizeof hintsD);
    hintsD.ai_family = AF_UNSPEC;
    hintsD.ai_socktype = SOCK_DGRAM;
        }
        
    }
    
    
    /*~NET(){
        close(sockfd);
        close(new_fd);
        close(rv);
        close(sockfd);
        freeaddrinfo(servinfoD);
        close(sockfdD);
    }*/
    
        
    
    void TCP_SRV_LS(){//Server waits for conection 

        if (listen(sockfd, BACKLOG) == -1) {
            perror("listen");
            exit(1);
        }
        //std::cout<<"TCP_SRV WAITING CONNECTIONS"<<std::endl;
        //printf("server: waiting for connections...\n");
        // while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            //continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr),s, sizeof s);
        std::cout<<"TCP_SRV CONNECTED TO:"<<s<<std::endl;
    }

    void TCP_SRV_SND(std::string DTS){//Server sends data
        if (send(new_fd, DTS.c_str(), DTS.length(), 0) == -1){
            perror("send");
        }
    }
    
    void TCP_SRV_RCV(){
        if ((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);        
    }
    
    //printf("server: received '%s'\n",buf);
    //std::cout<<"TCP_SRV DATA AQUISITON FROM CLIEN AT:"<<s<<std::endl;
    DR.clear();
    DR=buf;
    memset(&buf[0], 0, sizeof(buf));
    }
    
    void TCP_SRV_CLS(){//Server close conecction
        close(new_fd);  // parent doesn't need this
    }
    
    void TCP_SRV(std::string DTS){//Servidor espera por conexión envia y recive info

        if (listen(sockfd, BACKLOG) == -1) {
            perror("listen");
            exit(1);
        }
        //std::cout<<"TCP_SRV WAITING CONNECTIONS"<<std::endl;
        //printf("server: waiting for connections...\n");
        // while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            //continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr),s, sizeof s);
        std::cout<<"TCP_SRV CONNECTED TO:"<<s<<std::endl;
        
        if (send(new_fd, DTS.c_str(), DTS.length(), 0) == -1){
            perror("send");
        }
       

        if ((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);        
    }
    
    //printf("server: received '%s'\n",buf);
    //std::cout<<"TCP_SRV DATA AQUISITON FROM CLIEN AT:"<<s<<std::endl;
    DR.clear();
    DR=buf;
    memset(&buf[0], 0, sizeof(buf));
    close(new_fd);  // parent doesn't need this
    }

    void TCP_CLT_CN(std::string dir){//Client conects to server

     
     
        if ((rv = getaddrinfo(dir.c_str(), PORT.c_str(), &hints, &servinfo)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        //return 1;
            exit(EXIT_FAILURE);
        }
        //std::cout<<"INFO: "<<rv<<std::endl;
    // loop through all the results and connect to the first we can
        for(p = servinfo; p != NULL; p = p->ai_next) {
            sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol);
            //std::cout<<"SOC: "<<sockfd<<std::endl;
            if (sockfd== -1) {
                //perror("client: socket");
                continue;
            }

            
        //Manages the time out op
        struct timeval timeout;      
        timeout.tv_sec = 0;
        timeout.tv_usec = 100;
        if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0){
           // perror("setsockopt failed\n");
        }

        if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0){
           // perror("setsockopt failed\n");
        }
        //Manages the time out op

            int con =connect(sockfd, p->ai_addr, p->ai_addrlen);

            
           // std::cout<<"CON: "<<con<<std::endl;
            if (con != -1) {
                break;//Succes
            }    
            close(sockfd);
            
        }
        
    if (p == NULL) {
        //fprintf(stderr, "client: failed to connect\n");
        CON_ERR=true;
        //exit(EXIT_FAILURE);
        //return 2;
    }
    else{//Si el cliente encuentra y conecta con el servidor
        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
        CON_ERR=false;
    //printf("client: connecting to %s\n", s);
    //std::cout<<"CONNECTED TO:"<<s<<std::endl;

    freeaddrinfo(servinfo); // all done with this structure
    }
    
    
    
        //Manages the time out op
        struct timeval timeout; 
            timeout.tv_sec = 50;
        timeout.tv_usec = 0;
        if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0){
            //perror("setsockopt failed\n");
        }

        if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0){
            //perror("setsockopt failed\n");
        }
        //Manages the time out op
    
    

}

void TCP_CLT_RCV(){
      if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
       // perror("recv");
        //exit(1);
    }
     DR=buf;
    memset(&buf[0], 0, sizeof(buf));
    //std::cout<<"DATA RECIVED FROM SERVER"<<std::endl; 
       //printf("client: received '%s'\n",buf);
}

void TCP_CLT_SND(std::string DTS){

    //std::cout<<"DATA SENDED TO SERVER"<<std::endl; 
    if (send(sockfd, DTS.c_str(), DTS.length(), 0) == -1){
   // perror("send");
    }

    buf[numbytes] = '\0';
    
}

void TCP_CLT(std::string dir,std::string DTS){

        if ((rv = getaddrinfo(dir.c_str(), PORT.c_str(), &hints, &servinfo)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        //return 1;
        }


    // loop through all the results and connect to the first we can
        for(p = servinfo; p != NULL; p = p->ai_next) {
            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
                perror("client: socket");
                continue;
            }

            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                perror("client: connect");
                continue;
            }

            break;
        }
                
    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        //return 2;
    }
    else{//Si el cliente encuentra y conecta con el servidor

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    //printf("client: connecting to %s\n", s);
    std::cout<<"CONNECTING TO:"<<s<<std::endl;

    freeaddrinfo(servinfo); // all done with this structure

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }
     DR=buf;
    memset(&buf[0], 0, sizeof(buf));
        //std::cout<<"DATA RECIVED FROM SERVER"<<std::endl; 
       //printf("client: received '%s'\n",buf);
        
       // std::cout<<"DATA SENDED BACK TO SERVER"<<std::endl; 
    if (send(sockfd, DTS.c_str(), DTS.length(), 0) == -1)
    perror("send");

    buf[numbytes] = '\0';

    }

}

void TCP_SSL_SRV(std::string DTS){

    
    
}

void TCP_SSL_CLT(std::string website, std::string DTS){//DTS=data to send
    DR.clear();
     if(SSL_library_init() < 0){
                        std::cerr<<"OpenSSL error"<<std::endl;
                        return;
                    }
                    
                    ctx = SSL_CTX_new (SSLv23_client_method ());
                    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);

                    //To define the server's address.
                    memset(&ServAddr, 0, sizeof(ServAddr));
                    std::string host;
                    iLength = website.length();
                    iStart = 0; iEnd = iLength - 1;
                    if(website.substr(0,8) == "https://") iStart = 8;
                    else if(website.substr(0,7) == "http://") iStart = 7;
                    for(int i = iStart; i<iLength; i++){
                        if(website.substr(i, 1)=="/"){
                            iEnd = i - 1;
                            break;
                        }
                    }
                    host = website.substr(iStart, iEnd - iStart + 1);

                    ServInf = gethostbyname(host.c_str());
                    if(ServInf == NULL){
                        std::cerr<<"HostName error"<<std::endl;
                        return;
                    }
                    
                    //Get a socket
                    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
                        std::cerr<<"Socket error"<<std::endl;
                        return;
                    }
                    
                    memset(&ServAddr, 0, sizeof(ServAddr));
                    ServAddr.sin_family = AF_INET;
                    ServAddr.sin_port = htons(443);
                    ServAddr.sin_addr.s_addr = *(long*)(ServInf->h_addr);

                    if ( connect(sockfd, (struct sockaddr*)&ServAddr, sizeof(ServAddr)) == -1 ) {
                       std::cerr<<"Conection error"<<std::endl;
                       return;
                    }

                    ssl = SSL_new(ctx); 
                    SSL_set_fd(ssl, sockfd);
    
                    SSL_connect(ssl);

                    // To send the request.
                    request += website + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";                    
                    SSL_write(ssl, request.c_str(), request.length());

                    // To initiate the file.
                 /*   fid.open((FileName + "." + FileType).c_str());
                    if(fid.fail()){
                        std::cerr << "OpeningFile error" << std::endl;
                        return;
                    }*/

                    // To read dataflow for the file.
                    int iRecv = 1;                    
                    std::string RcvDt;
                    
                    while (iRecv != 0 && iRecv != -1){
                        memset(message, '\0', sizeof(message));
                       iRecv= SSL_read(ssl, message, iMessage);
                        RcvDt+=std::string(message);

                    }
                    std::string initS="\r\n\r\n";
                    std::string servR="\r\n";
                    
                    std::size_t found = RcvDt.find(initS);
                    if (found!=std::string::npos){
                        RcvDt.erase(0,found+10);
                    }
                    while((found!=std::string::npos)&&(found<(RcvDt.size()-8))){
                        found = RcvDt.find(servR);
                        if(found<(RcvDt.size()-8)){
                            RcvDt.erase(found,8);//
                        }
                    }
                    DR+=RcvDt.c_str();
                    //fid.write(RcvDt.c_str(), RcvDt.size());
                                       

                    // To close the downloaded file
                    //fid.close();
                    if(iRecv == -1){
                        std::cerr<<"SSL_read error"<<std::endl;
                        return;
                    }


                    SSL_free(ssl);
                    close(sockfd);
                    SSL_CTX_free(ctx);
    
}

void UDP_RCV(){
    if ((rv = getaddrinfo(NULL, PORT.c_str(), &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
       // return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
       // return 2;
    }

    freeaddrinfo(servinfo);

    printf("listener: waiting to recvfrom...\n");

    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, buf, MAXDATASIZE-1 , 0,
        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
       // exit(1);
    }
    
    else{

    printf("listener: got packet from %s\n",
        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s));
    printf("listener: packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("listener: packet contains \"%s\"\n", buf);

    //buf[0]='X';
    DR.clear();
    DR=buf;
    memset(&buf[0], 0, sizeof(buf));
    //printf("listener: got packet from %s\n",
       // inet_ntop(their_addr.ss_family,
         //   get_in_addr((struct sockaddr *)&their_addr),
         //s, sizeof s));
   // printf("listener: packet is %d bytes long\n", numbytes);
    //printf("listener: packet contains \"%s\"\n", buf);
    
     close(sockfd);
    }
}

void UDP_SND(std::string dir, std::string DTS ){
 if ((rvD = getaddrinfo(dir.c_str(), PORT.c_str(), &hintsD, &servinfoD)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rvD));
        //return 1;
    }

    // loop through all the results and make a socket
    for(pD = servinfoD; pD != NULL; pD = pD->ai_next) {
        if ((sockfdD = socket(pD->ai_family, pD->ai_socktype,
                pD->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if (pD == NULL) {
        fprintf(stderr, "talker: failed to create socket\n");
       // return 2;
    }

    if ((numbytes = sendto(sockfdD,DTS.c_str(), DTS.length(), 0,
             pD->ai_addr, pD->ai_addrlen)) == -1) {
        perror("talker: sendto");
        //exit(1);
    }

    freeaddrinfo(servinfoD);

    close(sockfdD);
 
}


};



#endif // NET_H_INCLUDED
