/*
 * udp_server.cpp
 *
 *  Created on: Apr 19, 2017
 *      Author: paco
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

#include "config.h"

int udp_server_run(int portNumber){
//---- create UDP socket ----

int udpReceiveSocket=socket(PF_INET,SOCK_DGRAM,0);
int udpSendSocket=socket(PF_INET,SOCK_DGRAM,0);

struct sockaddr_in myAddr;
myAddr.sin_family=AF_INET;
myAddr.sin_port=htons(portNumber);
myAddr.sin_addr.s_addr=htonl(INADDR_ANY);
bind(udpReceiveSocket, (struct sockaddr *)&myAddr, sizeof(myAddr));

printf("UDP Server started on port: %d\n", portNumber);

for(;;)
  {
  //---- receive a 32-bit integer in network format ----
//  int32_t tmp;

  int8_t tmp[122];
  struct sockaddr_in fromAddr;
  socklen_t len = sizeof(fromAddr);

  // Read 122 bytes
  recvfrom(udpReceiveSocket, &tmp, 122, 0, (struct sockaddr *)&fromAddr, &len);

  //---- convert to host format 32-bit integer ----
//  int32_t request=0;
//  request = ntohl(tmp);

//  printf("T=%d N=%d", tmp[0], tmp[1]);

  //---- display request and source address/port ----

  printf("from %s:%d : T=%d N=%d | x=%d y=%d \n", inet_ntoa(fromAddr.sin_addr), ntohs(fromAddr.sin_port), tmp[0], tmp[1], tmp[2]|tmp[3]<<8|tmp[4]<<16);

  //---- prepare reply ----
  int32_t reply=2;

  //---- convert to network format 32-bit integer ----

  reply = htonl(reply);

  struct sockaddr_in toAddr;
  toAddr.sin_family = AF_INET;
  toAddr.sin_port = htons(portNumber);
  toAddr.sin_addr = fromAddr.sin_addr;




  //---- send converted reply to client ----

  //send(udpSocket, &reply, sizeof(reply), 0);
  sendto(udpSendSocket, &reply, sizeof(reply), 0, (struct sockaddr *)&toAddr, sizeof(toAddr));

  printf("Replied to client: %s:%d : %d\n", inet_ntoa(toAddr.sin_addr), toAddr.sin_port, ntohl(reply));
  }

//---- close UDP socket ----

close(udpReceiveSocket);
close(udpSendSocket);

return 0;
}
