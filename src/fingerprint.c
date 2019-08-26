/*
 * fingerprint.c
 *
 * Created: 6/29/2018 2:35:17 PM
 *  Author: M50673
 */ 


#include "fingerprint.h"
#include "usart_basic.h"
#include <string.h>

#define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))
#define NTOHS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))

#define NTOHL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))

#define htons(n) HTONS(n)
#define ntohs(n) NTOHS(n)

#define htonl(n) HTONL(n)
#define ntohl(n) NTOHL(n)

void write_buffer(uint8_t *buffer, uint8_t size) {
	
	int i = 0;
	
	while(size > 0) {
		USART_0_write(buffer[i++]);
		size--;
	}
}

void read_buffer(uint8_t *buffer, uint8_t size) {
	int i = 0;
	
	while(size > 0){
		buffer[i++] = USART_0_read();
		asm("nop");
		size--;
	}
}

void copy_buffer(uint8_t *dest, uint8_t *src, uint8_t size) {
	
	for(int i = 0; i < size; ++i) {
		dest[i] = src[i];
	}
}

bool send_handshake() {
	handshake h;
	handshake_ack ack;
	
	uint8_t recv_buffer[ACK_HANDSHAKE_BUFF_SIZE];
	
	/* Set data into the handshake structure in network format */
	h.header = htons(0xEF01);
	h.module_address = htonl(CHIP_ADDRESS);
	h.package_identifier = 0x01;
	h.package_length = htons(0x0004);
	h.instruction_code = 0x17;
	h.control_code = 0;
	h.check_sum = htons(0x001C);
	
	uint8_t send_buffer[HANDSHAKE_BUFF_SIZE];
	memcpy(send_buffer, &h, HANDSHAKE_BUFF_SIZE);
	
	/* Send the handshake until checksum is correct */
	do {
	/* write buffer */
	write_buffer(send_buffer, (HANDSHAKE_BUFF_SIZE) );
	
	/* read buffer (ack) */
	read_buffer(recv_buffer, ACK_HANDSHAKE_BUFF_SIZE);
	
	/* making the structure from recv_buffer */
	copy_buffer(&ack, recv_buffer, ACK_HANDSHAKE_BUFF_SIZE);
	
	/* Convert from network to host */
	ack.header = ntohs(ack.header);
	ack.module_address = ntohl(ack.module_address);
	ack.package_length = ntohs(ack.package_length);
	ack.check_sum = ntohs(ack.check_sum);
	
	} while (ack.package_identifier + ack.package_length + ack.confirmation_code != ack.check_sum);

	if(ack.confirmation_code != 0x00)
		return false;
		
	return true;
}

uint8_t img() {
	get_img im;
	get_img_ack ack;
	
	uint8_t recv_buffer[ACK_GETIMG_BUFF_SIZE];
	
	im.header = htons(0xEF01);
	im.module_address = htonl(CHIP_ADDRESS);
	im.package_identifier = 0x01;
	im.package_length = htons(0x0003);
	im.instruction_code = 0x01;
	im.check_sum = htons(0x005);
	
	uint8_t send_buffer[GETIMG_BUFF_SIZE];
	memcpy(send_buffer, &im, GETIMG_BUFF_SIZE);
	
	/* Send the handshake until checksum is correct */
	do {
		/* write buffer */
		write_buffer(send_buffer, GETIMG_BUFF_SIZE);
		
		/* read buffer (ack) */
		read_buffer(recv_buffer, ACK_GETIMG_BUFF_SIZE);
		
		/* making the structure from recv_buffer */
		copy_buffer(&ack, recv_buffer, ACK_GETIMG_BUFF_SIZE);
		
		/* Convert from network to host */
		ack.header = ntohs(ack.header);
		ack.module_address = ntohl(ack.module_address);
		ack.package_length = ntohs(ack.package_length);
		ack.check_sum = ntohs(ack.check_sum);
		
	} while (ack.package_identifier + ack.package_length + ack.confirmation_code != ack.check_sum);

	return ack.confirmation_code;
}

uint8_t img_to_tz(uint8_t buffer_id) {
	img2tz im;
	img2tz_ack ack;
	
	uint8_t recv_buffer[ACK_IMG2TZ_BUFF_SIZE];
	
	im.header = htons(0xEF01);
	im.module_address = htonl(CHIP_ADDRESS);
	im.package_identifier = 0x01;
	im.package_length = htons(0x0004);
	im.instruction_code = 0x02;
	im.buffer_id = buffer_id;
	im.check_sum = htons(0x01 + 0x0004 + 0x02 + buffer_id);
	
	uint8_t send_buffer[IMG2TZ_BUFF_SIZE];
	memcpy(send_buffer, &im, IMG2TZ_BUFF_SIZE);
	
	/* Send the handshake until checksum is correct */
	do {
		/* write buffer */
		write_buffer(send_buffer, IMG2TZ_BUFF_SIZE);
		
		/* read buffer (ack) */
		read_buffer(recv_buffer, ACK_IMG2TZ_BUFF_SIZE);
		
		/* making the structure from recv_buffer */
		copy_buffer(&ack, recv_buffer, ACK_IMG2TZ_BUFF_SIZE);
		
		/* Convert from network to host */
		ack.header = ntohs(ack.header);
		ack.module_address = ntohl(ack.module_address);
		ack.package_length = ntohs(ack.package_length);
		ack.check_sum = ntohs(ack.check_sum);
		
	} while (ack.package_identifier + ack.package_length + ack.confirmation_code != ack.check_sum);

	return ack.confirmation_code;
}

search_return search_library(uint8_t buffer_id, uint16_t start_page, uint16_t page_id) {
	volatile search s;
	volatile search_ack ack;
	
	volatile uint8_t recv_buffer[ACK_SEARCH_BUFF_SIZE];
	
	s.header = htons(0xEF01);
	s.module_address = htonl(CHIP_ADDRESS);
	s.package_identifier = 0x01;
	s.package_length = htons(0x0008);
	s.instruction_code = 0x04;
	s.buffer_id = buffer_id;
	s.start_page = htons(start_page);
	s.page_id = htons(page_id);
	volatile value = 0x01 + 0x0008 + 0x04 + buffer_id + start_page + page_id;
	s.check_sum = htons(0x01 + 0x0008 + 0x04 + buffer_id + start_page + page_id);
	
	volatile uint8_t send_buffer[SEARCH_BUFF_SIZE];
	memcpy(send_buffer, &s, SEARCH_BUFF_SIZE);
	
	/* Send the handshake until checksum is correct */
	do {
		/* write buffer */
		write_buffer(send_buffer, SEARCH_BUFF_SIZE);
		
		/* read buffer (ack) */
		read_buffer(recv_buffer, ACK_SEARCH_BUFF_SIZE);
		
		/* making the structure from recv_buffer */
		copy_buffer(&ack, recv_buffer, ACK_SEARCH_BUFF_SIZE);
		
		/* Convert from network to host */
		ack.header = ntohs(ack.header);
		ack.module_address = ntohl(ack.module_address);
		ack.package_length = ntohs(ack.package_length);
		ack.page_id = ntohs(ack.page_id);
		ack.match_score = ntohs(ack.match_score);
		ack.check_sum = ntohs(ack.check_sum);
		
	} while (ack.package_identifier + ack.package_length + ack.confirmation_code + ack.page_id + ack.match_score != ack.check_sum);


	search_return return_value;
	return_value.confirmation_code = ack.confirmation_code;
	return_value.page_id = ack.page_id;
	return_value.match_score = ack.match_score;
	
	return return_value;
	
}