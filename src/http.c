/*
 * http.c
 *
 * Created: 7/18/2018 10:07:53 AM
 *  Author: M50673
 */ 

#include "include/http.h"
#include <string.h>
#include <stdio.h>

void GET_request(char* path, char* query_string) {
	
	
	
	/* Prepare the buffer */
	memset(buffer, 0, BUFF_SIZE);
	sprintf(buffer, "GET %s?%s HTTP/1.1\r\nHost: z\r\n\r\n", path, query_string);
	
	/* Send buffer */
	//send(tcp_client_socket, buffer, strlen(buffer), 0);
}

void POST_request(char* path, char* content_type, char* content) {
	char buffer[BUFF_SIZE];
	
	/* Prepare the buffer */
	memset(buffer, 0, BUFF_SIZE);
	sprintf(buffer, "POST %s HTTP/1.1\r\nContent-Type: %s\r\nHost: z\r\ncontent-length: %i\r\n\r\n&s", 
			path, content_type, sizeof(content), content);
	
	/* Send buffer */
	//send(tcp_client_socket, buffer, strlen(buffer), 0);
}