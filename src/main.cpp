/**
 * @file main.cpp
 * @author DSC IoT Team (Anindya)
 * @brief A concept demonstration of socket.io client on node-mcu
 * @version 0.1
 * @date 2021-12-14
 *
 * @copyright Copyright (c) 2021
 *
 */
/* ======== Includes ======== */
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <Hash.h>
/* ======== Macros ======== */
#define USE_SERIAL Serial // USB port
#define PWM_MAX 500
#define LED_PIN 4 //D2

/* ======== GLobals ======== */
WiFiManager wm;
SocketIOclient io;
typedef struct data_t
{
    bool state;
    uint16_t brightness;
} data_t;

/* ======== Function prototypes ======== */
void socketIOEventHandler(socketIOmessageType_t type, uint8_t *payload, size_t length);
void payloadHandler(uint8_t *payload);
void updateLamp(int pin, data_t data);

/* ======== Driver Setup ======== */
void setup()
{
    USE_SERIAL.begin(74880);
    pinMode(LED_PIN, OUTPUT);
    analogWriteFreq(500);
    // for ease of debugging
    USE_SERIAL.setDebugOutput(true);

    // USE_SERIAL.printf("\n\n\n");
    for (uint8_t t = 4; t > 0; t--)
    {
        USE_SERIAL.printf("  [SETUP] BOOT WAIT %d...\r", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    // disable AP
    if (WiFi.getMode() & WIFI_AP)
    {
        WiFi.softAPdisconnect(true);
    }

    wm.autoConnect("IoT Socket Demo");

    String ip = WiFi.localIP().toString();
    USE_SERIAL.printf("[SETUP] WiFi Connected %s\n", ip.c_str());

    // server address, port and URL
    io.begin("iot-socket.herokuapp.com", 80, "/socket.io/?EIO=4");

    // event handler
    io.onEvent(socketIOEventHandler);
}
/* ======== Driver Loop ======== */
void loop()
{
    io.loop();
}

/* ======== Function definitions ======== */
void socketIOEventHandler(socketIOmessageType_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case sIOtype_DISCONNECT:
        USE_SERIAL.printf("[IOc] Disconnected!\n");
        break;
    case sIOtype_CONNECT:
        USE_SERIAL.printf("[IOc] Connected to url: %s\n", payload);

        // join default namespace (no auto join in Socket.IO V3)
        io.send(sIOtype_CONNECT, "/");
        break;
    case sIOtype_EVENT:
        USE_SERIAL.printf("[IOc] get event: %s\n", payload);
        payloadHandler(payload);
        break;
    case sIOtype_ACK:
        USE_SERIAL.printf("[IOc] get ack: %u\n", length);
        hexdump(payload, length);
        break;
    case sIOtype_ERROR:
        USE_SERIAL.printf("[IOc] get error: %u\n", length);
        hexdump(payload, length);
        break;
    case sIOtype_BINARY_EVENT:
        USE_SERIAL.printf("[IOc] get binary: %u\n", length);
        hexdump(payload, length);
        break;
    case sIOtype_BINARY_ACK:
        USE_SERIAL.printf("[IOc] get binary ack: %u\n", length);
        hexdump(payload, length);
        break;
    }
}

void payloadHandler(uint8_t *payload)
{
    StaticJsonDocument<80> doc;
    deserializeJson(doc, (const char *)payload);
    JsonArray array = doc.as<JsonArray>();
    data_t data;
    String topic = array[0].as<const char *>();
    if (topic == "toggle")
    {
        data.state = array[1].as<boolean>();
    }
    else if (topic == "slider")
    {
        data.brightness = String(array[1].as<const char *>()).toInt();
    }
    else
        return;
    delay(10);
    // update the lamp-state only if else block is not triggered
    updateLamp(LED_PIN, data);
}

void updateLamp(int pin, data_t data)
{
    uint16_t value = data.state?data.brightness:0;
    USE_SERIAL.println(value);
    analogWrite(LED_PIN, value);
}