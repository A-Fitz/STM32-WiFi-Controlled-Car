/**
 ******************************************************************************
 * @file    wifi.h
 * @author  MCD Application Team
 * @brief   This file contains the diffrent wifi core resources definitions.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
#ifndef __WIFI_H_
#define __WIFI_H_

/* Includes ------------------------------------------------------------------*/
#include "wifi/es_wifi.h"
#include "wifi/es_wifi_io.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
	WIFI_ECN_OPEN = 0x00,
	WIFI_ECN_WEP = 0x01,
	WIFI_ECN_WPA_PSK = 0x02,
	WIFI_ECN_WPA2_PSK = 0x03,
	WIFI_ECN_WPA_WPA2_PSK = 0x04,
} WIFI_Ecn_t;

typedef enum {
	WIFI_TCP_PROTOCOL = 0, WIFI_UDP_PROTOCOL = 1,
} WIFI_Protocol_t;

typedef enum {
	WIFI_SERVER = 0, WIFI_CLIENT = 1,
} WIFI_Type_t;

typedef enum {
	WIFI_STATUS_OK = 0,
	WIFI_STATUS_ERROR = 1,
	WIFI_STATUS_NOT_SUPPORTED = 2,
	WIFI_STATUS_JOINED = 3,
	WIFI_STATUS_ASSIGNED = 4,
	WIFI_STATUS_TIMEOUT = 5,
} WIFI_Status_t;

typedef struct {
	uint8_t Number; /*!< Connection number */
	uint16_t RemotePort; /*!< Remote PORT number */
	uint16_t LocalPort;
	uint8_t RemoteIP[4]; /*!< IP address of device */
	WIFI_Protocol_t Protocol; /*!< Connection type. Parameter is valid only if connection is made as client */
	uint32_t TotalBytesReceived; /*!< Number of bytes received in entire connection lifecycle */
	uint32_t TotalBytesSent; /*!< Number of bytes sent in entire connection lifecycle */
	uint8_t Active; /*!< Status if connection is active */
	uint8_t Client; /*!< Set to 1 if connection was made as client */
} WIFI_Socket_t;

typedef struct {
	uint8_t ClientNumber; /*!< nth client attached */
	uint8_t ClientMAC[6]; /*!< MAC address of client */
	int16_t ClientRSSI; /*!< RSSI of connection with client */
} WIFI_AP_Client_t;

typedef struct {
	WIFI_AP_Client_t Clients[ES_WIFI_MAX_AP_CLIENTS];
	uint8_t count;
} WIFI_AP_Clients_t;

typedef struct {
	uint8_t SSID[ES_WIFI_MAX_SSID_NAME_SIZE + 1];
	uint8_t PSWD[ES_WIFI_MAX_PSWD_NAME_SIZE + 1];
	uint8_t channel;
	WIFI_Ecn_t Ecn;
} WIFI_APConfig_t;

typedef struct {
	uint8_t SSID[ES_WIFI_MAX_SSID_NAME_SIZE + 1]; /*!< Network public name for ESP AP mode */
	uint8_t IP_Addr[4]; /*!< IP Address */
	uint8_t MAC_Addr[6]; /*!< MAC address */
} WIFI_APSettings_t;

typedef struct {
	uint8_t IsConnected;
	uint8_t IP_Addr[4];
	uint8_t IP_Mask[4];
	uint8_t Gateway_Addr[4];
} WIFI_Conn_t;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
WIFI_Status_t WIFI_Init(void);
WIFI_Status_t WIFI_GetIP_Address(uint8_t *ipaddr);
WIFI_Status_t WIFI_GetGateway_Address(uint8_t *Gateway_addr);
WIFI_Status_t WIFI_GetMAC_Address(uint8_t *mac);

WIFI_Status_t WIFI_ConfigureAP(const char *ssid, const char *pass, WIFI_Ecn_t ecn, uint8_t channel, uint8_t max_conn);
WIFI_Status_t WIFI_TerminateAP();
WIFI_Status_t WIFI_ListAPClients(WIFI_AP_Clients_t *APClients, uint32_t Timeout);
WIFI_Status_t WIFI_Disconnect(void);

WIFI_Status_t WIFI_Ping(uint8_t *ipaddr, uint16_t count, uint16_t interval_ms);

WIFI_Status_t WIFI_StartServer(uint32_t socket, WIFI_Protocol_t type, uint16_t port);
WIFI_Status_t WIFI_WaitServerConnection(int socket, uint32_t Timeout, uint8_t *RemoteIp, uint16_t *RemotePort);
WIFI_Status_t WIFI_CloseSocket();
WIFI_Status_t WIFI_StopServer();

WIFI_Status_t WIFI_SendData(uint8_t socket, uint8_t *pdata, uint16_t Reqlen, uint16_t *SentDatalen, uint32_t Timeout);
WIFI_Status_t WIFI_ReceiveData(uint8_t socket, uint8_t *pdata, uint16_t Reqlen, uint16_t *RcvDatalen, uint32_t Timeout);

WIFI_Status_t WIFI_SetOEMProperties(const char *name, uint8_t *Mac);
WIFI_Status_t WIFI_ResetModule(void);
WIFI_Status_t WIFI_SetModuleDefault(void);
WIFI_Status_t WIFI_ModuleFirmwareUpdate(const char *url);

#endif /* __WIFI_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
