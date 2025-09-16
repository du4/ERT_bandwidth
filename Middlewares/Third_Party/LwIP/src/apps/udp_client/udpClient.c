/**
  ******************************************************************************
  * @file    LwIP/LwIP_UDP_Echo_Client/Src/udp_echoclient.c
  * @author  MCD Application Team
  * @brief   UDP echo client
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "udpClient.h"

#include "main.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void udpReceiveCallback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
struct udp_pcb *upcb;
struct udp_pcb *upcbLogger;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Connect to UDP server
  * @param  None
  * @retval None
  */
void udpClientConnect(ip_addr_t destIPaddr, int port){
  err_t err;
  /* Create a new UDP control block  */
  upcb = udp_new();
  if (upcb!=NULL)  {
    /* configure destination IP address and port */
    err= udp_connect(upcb, &destIPaddr, port);
    if (err == ERR_OK) {
      /* Set a receive callback for the upcb */
      udp_recv(upcb, udpReceiveCallback, NULL);
    }
  }
}

void udpClientLoggerConnect(ip_addr_t destIPaddr, int port){
  err_t err;
  /* Create a new UDP control block  */
  upcbLogger = udp_new();
  if (upcbLogger!=NULL)  {
    /* configure destination IP address and port */
    err= udp_connect(upcbLogger, &destIPaddr, port);
    if (err == ERR_OK) {
      /* Set a receive callback for the upcb */
      udp_recv(upcbLogger, udpReceiveCallback, NULL);
    }
  }
}

/**
  * @brief  Disconnect to UDP server
  * @param  None
  * @retval None
  */
void udpClientDisconnect(){
   	udp_disconnect(upcb);
   	udp_remove(upcb);
}

/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
void udpClientSend(void* pinter, uint16_t size){
  struct pbuf *p;
  /* allocate pbuf from pool*/
  p = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_RAM);
  if (p != NULL)  {
    /* copy data to pbuf */
    pbuf_take(p, (char*)pinter, size);
    /* send udp data */
    udp_send(upcb, p);
    /* free pbuf */
    pbuf_free(p);
  }
}

void udpClientLoggerSend(void* pinter){
  struct pbuf *p;
  /* allocate pbuf from pool*/
  p = pbuf_alloc(PBUF_TRANSPORT, LOGGER_PACKET_SIZE, PBUF_RAM);
  if (p != NULL)  {
    /* copy data to pbuf */
    pbuf_take(p, (char*)pinter, LOGGER_PACKET_SIZE);
    /* send udp data */
    udp_send(upcbLogger, p);
    /* free pbuf */
    pbuf_free(p);
  }
}

/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
void udpReceiveCallback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port){
  /* Free receive pbuf */
  pbuf_free(p);
}


