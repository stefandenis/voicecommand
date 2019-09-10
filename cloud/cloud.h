/* 
    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

#ifndef CLOUD_H_INCLUDED
#define CLOUD_H_INCLUDED

#include <util/delay.h>
#include <stdint.h>
#include <atomic.h>
#include <stdbool.h>
#include <adc_basic.h>
#include <stdio.h>

#include "network.h"
#include "timeout.h"
#include "mqtt_client/mqtt_client.h"

#define MAIN_WLAN_SSID      "MCHP.IOT"
#define MAIN_WLAN_AUTH      M2M_WIFI_SEC_WPA_PSK
#define MAIN_WLAN_PSK       "microchip"

#define PORT                (1883)
#define AWS_HOST_ENDPOINT   "io.adafruit.com"
#define AWS_THING_ID        "90127a37-600a-40b9-a79e-203eea8e5384"
#define ADAFRUIT_USERNAME   "aphosura4ever"
#define ADAFRUIT_IO_KEY     "2d62a8a274a7453db068dc45c079b277"


typedef enum
{
    CLOUD_STATE_INIT,
    CLOUD_STATE_WIFI_CONNECT,
    CLOUD_STATE_WAIT_FOR_INTERNET,
    CLOUD_STATE_DNS_REQUEST,
    CLOUD_STATE_TLS_CONNECT,
    CLOUD_STATE_MQTT,
    CLOUD_STATE_SUBSCRIBE,
	CLOUD_STATE_SENDING
	
} cloudState_t;

typedef enum
{
    CLOUD_EVENT_SUCCESS,
    CLOUD_EVENT_FAIL,
    CLOUD_NO_EVENT
} cloudEvent_t;

typedef cloudState_t (*handlerFunc_t)(void);
typedef void (*observerFunction_t)(cloudState_t state, cloudEvent_t ev);
typedef absolutetime_t (*sendFunction_t)(void *payload);

void CLOUD_startApp(void);
void CLOUD_setSendFunction(sendFunction_t function);
void CLOUD_setObserver(observerFunction_t function);

void CLOUD_runTask(void);
void CLOUD_publish(uint8_t *value);
void CLOUD_receiveEvent(cloudEvent_t e);    
void CLOUD_subscribe();

#endif