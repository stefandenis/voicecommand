/*
 * http.h
 *
 * Created: 7/18/2018 10:04:07 AM
 *  Author: M50673
 */ 

#define BUFF_SIZE 50

#ifndef HTTP_H_
#define HTTP_H_

char buffer[BUFF_SIZE];

void GET_request(char* path, char* query_string);
void POST_request(char* path, char* content_type, char* content);



#endif /* HTTP_H_ */