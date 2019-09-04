#include "mqtt/mqtt_core/mqtt_core.h"
#include "mqtt_comm_layer.h"
#include "adafruit_service.h"


publishReceptionHandler_t imqtt_publishReceiveCallBackTable[NUM_TOPICS_SUBSCRIBE];

//uint32_t mqttGoogleApisComIP;

packetReceptionHandler_t adafruit_packetReceiveCallBackTable[ADAFRUIT_PACKET_RECV_TABLE_SIZE];


char Feed_Key[FEED_KEY_LENGTH];
char Adafruit_IO_Username[ADAFRUIT_USERNAME_LENGTH];
char mqttSubscribeTopic[TOPIC_SIZE];



void ADAFRUIT_subscribe(void)
{
	mqttSubscribePacket adafruitSubscribePacket;
	uint8_t             topicCount = 0;

	// Variable header
	adafruitSubscribePacket.packetIdentifierLSB = 1;
	adafruitSubscribePacket.packetIdentifierMSB = 0;

	// Payload
	for (topicCount = 0; topicCount < NUM_TOPICS_SUBSCRIBE; topicCount++) {
		sprintf(mqttSubscribeTopic, "%s/feeds/%s", Adafruit_IO_Username, Feed_Key );
		adafruitSubscribePacket.subscribePayload[topicCount].topic        = (uint8_t *)mqttSubscribeTopic;
		adafruitSubscribePacket.subscribePayload[topicCount].topicLength  = strlen(mqttSubscribeTopic);
		adafruitSubscribePacket.subscribePayload[topicCount].requestedQoS = 0;

		imqtt_publishReceiveCallBackTable[0].topic                         = mqttSubscribeTopic;
		imqtt_publishReceiveCallBackTable[0].mqttHandlePublishDataCallBack = received_from_adafruit;
		MQTT_SetPublishReceptionHandlerTable(imqtt_publishReceiveCallBackTable);
	}

	if (MQTT_CreateSubscribePacket(&adafruitSubscribePacket) == true) {
		debug_printInfo("ADAFRUIT: SUBSCRIBE packet created");
		sendSubscribe = false;
	}
}


void ADAFRUIT_publishData(uint8_t *data, unsigned int len){
	
	MQTT_CLIENT_publish(data,len);
	
}