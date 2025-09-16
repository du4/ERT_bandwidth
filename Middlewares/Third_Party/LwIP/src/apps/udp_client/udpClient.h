/**
  ******************************************************************************
  * @file    LwIP/LwIP_UDP_Echo_Client/Inc/udp_echoclient.h
  * @author  MCD Application Team
  * @brief   Header file for udp_echoclient.c
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

/* Define to prevent recursive inclusion -------------------------------------*/  
#ifndef __UDPCLIENT_H__
#define __UDPCLIENT_H__

/* Includes ------------------------------------------------------------------*/
#include "ip_addr.h"
/* Exported types ------------------------------------------------------------*/
#define UDP_PACKET_CUT_SIZE			600
#define UDP_PACKET_IDENTIFIER_SIZE	4

#define	PRESSURE_PACKET_TYPE			13
#define	TOMOGRAPH_ERT_PACKET_TYPE		12
#define	TOMOGRAPH_ECT_PACKET_TYPE		11

#define LOGGER_PACKET_SIZE 	128
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void udpClientConnect(ip_addr_t destIPaddr, int port);
void udpClientLoggerConnect(ip_addr_t destIPaddr, int port);
void udpClientDisconnect();
void udpClientSend(void* pinter, uint16_t size);
void udpClientLoggerSend(void* pinter);

#endif /* __UDPCLIENT_H__ */



