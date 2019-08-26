#define F_CPU 10000000


#include <atmel_start.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#include <string.h>
#include "winc_init.h"
#include <stdio.h>
#include "winc/driver/source/nmasic.h"
#include "winc/socket/include/socket.h"
#include "winc/socket/include/m2m_socket_host_if.h"

int usart_putchar_printf(char var, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);


int usart_putchar_printf(char var, FILE *stream){
	
	USART_1_write(var);
}

/*  Packet size */
#define MAIN_WIFI_M2M_BUFFER_SIZE 1460



//#define MAIN_WLAN_SSID "MCHP.IOT"
#define MAIN_WLAN_SSID "MCHP.IOT"
#define MAIN_WLAN_AUTH M2M_WIFI_SEC_WPA_PSK
//#define MAIN_WLAN_AUTH M2M_WIFI_SEC_OPEN
#define MAIN_WLAN_PSK "microchip"
#define MAIN_WLAN_CHANNEL (6) /* < Channel number */


#define MAIN_WIFI_M2M_SERVER_PORT (6666)
//#define MAIN_WIFI_M2M_SERVER_IP 0xC0A8FFFF /* 192.168.255.255 */atmega4809
#define MAIN_WIFI_M2M_SERVER_IP 0xFFFFFFFF


#define MAX_LENGTH 100


/* Sockets for tcp communication */
static SOCKET tcp_server_socket = -1;
static SOCKET tcp_client_socket = -1;


char msg_wifi_product[40]="Message from server ";

/* Wi-Fi status */
static int8_t wifi_connected;

/* Socket buffer */
static uint8_t gau8SocketTestBuffer[MAIN_WIFI_M2M_BUFFER_SIZE];


volatile char command = 0;
int c;
char buffer[MAX_LENGTH];
int index;
volatile char data_response;


/**
 * \brief Callback to get the Data from socket.
 *
 * \param[in] sock socket handler.
 * \param[in] u8Msg socket event type. Possible values are:
 *  - SOCKET_MSG_BIND
 *  - SOCKET_MSG_LISTEN
 *  - SOCKET_MSG_ACCEPT
 *  - SOCKET_MSG_CONNECT
 *  - SOCKET_MSG_RECV
 *  - SOCKET_MSG_SEND
 *  - SOCKET_MSG_SENDTO
 *  - SOCKET_MSG_RECVFROM
 * \param[in] pvMsg is a pointer to message structure. Existing types are:
 *  - tstrSocketBindMsg
 *  - tstrSocketListenMsg
 *  - tstrSocketAcceptMsg
 *  - tstrSocketConnectMsg
 *  - tstrSocketRecvMsg
 */
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	switch (u8Msg) {
	/* Socket bind */
	case SOCKET_MSG_BIND: {
		tstrSocketBindMsg *pstrBind = (tstrSocketBindMsg *)pvMsg;
		if (pstrBind && pstrBind->status == 0) {
			printf("socket_cb: bind success!\r\n");
			listen(tcp_server_socket, 0);
		} else {
			printf("socket_cb: bind error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	} break;

	/* Socket listen */
	case SOCKET_MSG_LISTEN: {
		tstrSocketListenMsg *pstrListen = (tstrSocketListenMsg *)pvMsg;
		if (pstrListen && pstrListen->status == 0) {
			printf("socket_cb: listen success!\r\n");
			accept(tcp_server_socket, NULL, NULL);
		} else {
			printf("socket_cb: listen error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	} break;

	/* Connect accept */
	case SOCKET_MSG_ACCEPT: {
		tstrSocketAcceptMsg *pstrAccept = (tstrSocketAcceptMsg *)pvMsg;
		if (pstrAccept) {
			printf("socket_cb: accept success!\r\n");
			accept(tcp_server_socket, NULL, NULL);
			tcp_client_socket = pstrAccept->sock;
			recv(tcp_client_socket, gau8SocketTestBuffer, sizeof(gau8SocketTestBuffer), 0);
		} else {
			printf("socket_cb: accept error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	} break;

	/* Message send */
	case SOCKET_MSG_SEND: {
		printf("socket_cb: send success!\r\n");
		printf("TCP Server Test Complete!\r\n");
		printf("close socket\n");
		close(tcp_client_socket);
		close(tcp_server_socket);
	} break;

	/* Message receive */
	case SOCKET_MSG_RECV: {
		tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
		if (pstrRecv && pstrRecv->s16BufferSize > 0) {
			printf("socket_cb: recv success!\r\n");
			char c;
			c=*(pstrRecv->pu8Buffer);
			printf("%c \r\n",*(pstrRecv->pu8Buffer));
			send(tcp_client_socket, &msg_wifi_product, sizeof(msg_wifi_product), 0);
		} else {
			printf("socket_cb: recv error!\r\n");
			close(tcp_server_socket);
			tcp_server_socket = -1;
		}
	}

	break;

	default:
		break;
	}
}

/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] u8MsgType type of Wi-Fi notification. Possible types are:
 *  - [M2M_WIFI_RESP_CON_STATE_CHANGED](@ref M2M_WIFI_RESP_CON_STATE_CHANGED)
 *  - [M2M_WIFI_REQ_DHCP_CONF](@ref M2M_WIFI_REQ_DHCP_CONF)
 * \param[in] pvMsg A pointer to a buffer containing the notification parameters
 * (if any). It should be casted to the correct data type corresponding to the
 * notification type.
 */
static void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED: {
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			wifi_connected = 1;
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			wifi_connected = 0;
			printf("Station disconnected\r\n");
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF: {
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		wifi_connected = 1; 
		printf("Station connected\r\n");
		printf("Station IP is %u.%u.%u.%u\r\n",pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]); //pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		
		break;
	}

	default: {
		break;
	}
	}
}









int main(void){
	
	tstrWifiInitParam param;
	tstrM2MAPConfig   strM2MAPConfig;
	int8_t            ret = 0;
	struct sockaddr_in addr;
	
	// Redirect stream to Tera Term
	stdout = &mystdout;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	sei();

	/* Initialize BSP */
	nm_bsp_init();


	/* Initialize socket address structure */
	addr.sin_family = AF_INET;
	addr.sin_port = _htons(MAIN_WIFI_M2M_SERVER_PORT);
	addr.sin_addr.s_addr = _htonl(MAIN_WIFI_M2M_SERVER_IP);




	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));

	/* Initialize Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = wifi_cb;
	wifi_init(&param);



	/* Initialize socket module */
	socketInit();
	registerSocketCallback(socket_cb, NULL);


	/* Initialize AP mode parameters structure with SSID, channel and OPEN security type. */
	memset(&strM2MAPConfig, 0x00, sizeof(tstrM2MAPConfig));
	strcpy((char *)&strM2MAPConfig.au8SSID, MAIN_WLAN_SSID);
	strM2MAPConfig.u8ListenChannel = MAIN_WLAN_CHANNEL;
	strM2MAPConfig.u8SecType       = MAIN_WLAN_AUTH;

	strM2MAPConfig.au8DHCPServerIP[0] = 192;
	strM2MAPConfig.au8DHCPServerIP[1] = 168;
	strM2MAPConfig.au8DHCPServerIP[2] = 0;
	strM2MAPConfig.au8DHCPServerIP[3] = 1;


/* Bring up AP mode with parameters structure. */
// ret = m2m_wifi_enable_ap(&strM2MAPConfig);
// if (M2M_SUCCESS != ret) {
// 	uprintf("main: m2m_wifi_enable_ap call error!\r\n");
// 	while (1) {
// 	}
// }

// 	printf("AP mode started. You can connect to %s.\r\n", (char *)MAIN_WLAN_SSID);


/* Connect to router. */
	m2m_wifi_connect(
	(char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID), MAIN_WLAN_AUTH, (char *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);

	PORTB.DIR |= PIN5_bm;
	
while (1) {
	
	
	
	
	/* Handle pending events from network controller. */
	
	
	while (m2m_wifi_handle_events(NULL) == M2M_SUCCESS) {
		
		if (wifi_connected == M2M_WIFI_CONNECTED) {
			
			if (tcp_server_socket < 0) {
				/* Open TCP server socket */
				if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
					printf("main: failed to create TCP server socket error!\r\n");
					
					continue;
				}

				/* Bind service*/
				bind(tcp_server_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
				
				
			}
		}



	}

}
}