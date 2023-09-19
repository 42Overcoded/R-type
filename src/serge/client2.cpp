// Client side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <boost/asio.hpp>

#include <boost/lexical_cast.hpp>

#include <iostream>

#define PORT     8080
#define MAXLINE 1024
   
// Driver code
int main() {

    // boost::asio::io_service io_service;
    // boost::asio::ip::tcp::resolver resolver(io_service);
    // boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    // boost::asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

    // boost::asio::ip::tcp::endpoint endpoint = *endpoints;
    // boost::asio::ip::address ip_address = endpoint.address();

    // std::string ip = "";
    // std::stringstream strsstr;
    // std::string strIP = boost::lexical_cast<std::string>(ip_address);
    // std::cout << strIP << std::endl;
    std::string ip = "fe80::f8ca:d2ea:1d2c:b2a8%wlp0s20f3";
    const char *ptrIP = ip.c_str();


    int sockfd;
    char buffer[MAXLINE];
    const char *hello = "Hello from client";
    struct sockaddr_in     servaddr;
   
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    //servaddr.sin_addr.s_addr = INADDR_ANY;
       
    inet_pton(AF_INET, ptrIP, &servaddr.sin_addr);

    int n;
    socklen_t len;
       
    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    std::cout<<"Hello message sent."<<std::endl;
           
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    std::cout<<"Server :"<<buffer<<std::endl;
   
    close(sockfd);
    return 0;
}