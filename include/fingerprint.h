/*
 * IncFile1.h
 *
 * Created: 6/29/2018 2:34:08 PM
 *  Author: M50673
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <stdint.h>
#include <stdbool.h>

#define HANDSHAKE_BUFF_SIZE			13
#define ACK_HANDSHAKE_BUFF_SIZE		12

#define GETIMG_BUFF_SIZE			12
#define ACK_GETIMG_BUFF_SIZE		12

#define IMG2TZ_BUFF_SIZE			13
#define ACK_IMG2TZ_BUFF_SIZE		12

#define SEARCH_BUFF_SIZE			17
#define ACK_SEARCH_BUFF_SIZE		16

#define CHIP_ADDRESS				0xFFFFFFFF

typedef struct search_return {
	uint8_t confirmation_code;
	uint16_t page_id;
	uint16_t match_score;
} search_return;

typedef struct search {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	instruction_code;
	uint8_t		buffer_id;
	uint16_t	start_page;
	uint16_t	page_id;
	uint16_t	check_sum;
} search;

typedef struct  search_ack {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	confirmation_code;
	uint16_t	page_id;
	uint16_t	match_score;
	uint16_t	check_sum;
} search_ack;

/* handshake format */
typedef struct handshake {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	instruction_code;
	uint8_t		control_code;
	uint16_t	check_sum;
} handshake;

typedef struct handshake_ack {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	confirmation_code;
	uint16_t	check_sum;
} handshake_ack;

/* set adder format */
typedef struct set_adder {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	instruction_code;
	uint8_t		new_module_address;
	uint16_t	check_sum;
} set_adder;

typedef struct set_adder_ack {
	uint16_t	header;
	uint32_t	new_module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	confirmation_code;
	uint16_t	check_sum;
} set_adder_ack;

/* collect finger image */

typedef struct get_img {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	instruction_code;
	uint16_t	check_sum;
} get_img;

typedef struct get_img_ack {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	confirmation_code;
	uint16_t	check_sum;
} get_img_ack;

/* img2tz */

typedef struct img2tz {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	instruction_code;
	uint8_t 	buffer_id;
	uint16_t	check_sum;
} img2tz;

typedef struct img2tz_ack {
	uint16_t	header;
	uint32_t	module_address;
	uint8_t 	package_identifier;
	uint16_t	package_length;
	uint8_t 	confirmation_code;
	uint16_t	check_sum;
} img2tz_ack;

bool send_handshake(void);
uint8_t img();
uint8_t img_to_tz(uint8_t buffer_id);
search_return search_library(uint8_t buffer_id, uint16_t start_page, uint16_t page_id);

#endif /* INCFILE1_H_ */