#include "wifi/access_point.h"

/**
 * @brief Creates an access point in direct connection mode.
 * @retval Success of procedure.
 */
bool createAP(void) {
	return WIFI_Init() == WIFI_STATUS_OK
			&& WIFI_ConfigureAP(AP_SSID, AP_PASSWORD, WIFI_ECN_WPA2_PSK, AP_CHANNEL,
					AP_MAX_CONNECTIONS) == WIFI_STATUS_OK;
}

/**
 * @brief Finds all clients connected to the AP, stores in APClients variable.
 * @retval Success of procedure.
 */
bool getClients(void) {
	return WIFI_ListAPClients(&APClients) == WIFI_STATUS_OK;
}

/**
 * @brief Creates a single connection TCP server in multi accept mode (so we don't have to wait for acceptance).
 * @retval Success of procedure.
 */
bool startTCPServer(void) {
	socket = 0;

	return WIFI_StartServer(socket, WIFI_TCP_PROTOCOL, TCP_PORT) == WIFI_STATUS_OK;
}

/**
 * @brief Wait for a connection to the TCP server.
 * @retval Success of procedure.
 */
bool waitForTCPConnection(void) {
	// TODO [@fitzgeralaus] What about a timeout?
	return WIFI_WaitServerConnection(socket, TCP_WAIT_TIMEOUT, remoteIP,
			remotePort) == WIFI_STATUS_OK;
}

/**
 * @brief Receive any data that has been sent over the TCP server.
 * @retval Success of procedure.
 */
bool receiveData(void) {
	return WIFI_ReceiveData(socket, recData, REC_PAYLOAD_SIZE, &recDataLen)
			== WIFI_STATUS_OK;
}

/**
 * @brief Send some data over the TCP server when requested.
 * @retval Success of procedure.
 */
bool sendData(uint8_t *sendData, uint8_t *sendDataLen) {
	return WIFI_SendData(socket, sendData, sendDataLen, &sentDataLen)
			== WIFI_STATUS_OK;
}