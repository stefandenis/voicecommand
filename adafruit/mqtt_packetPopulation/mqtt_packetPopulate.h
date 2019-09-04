/*
 * IncFile1.h
 *
 * Created: 9/3/2019 4:15:50 PM
 *  Author: M51763
 */ 


#ifndef MQTT_PACKET_POPULATE_H_
#define MQTT_PACKET_POPULATE_H_


#include <stdbool.h>
#include <stdint.h>

extern char mqttPassword[];
extern char cid[];
extern char mqttTopic[];
extern char mqttHostName[];

void MQTT_CLIENT_publish(uint8_t *data, uint16_t len);
void MQTT_CLIENT_receive(uint8_t *data, uint8_t len);
void MQTT_CLIENT_connect(void);

#endif /* MQTT_PACKET_POPULATE_H */