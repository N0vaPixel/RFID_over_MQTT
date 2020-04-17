 
/* WiFi client library from ESP8266 arduino core */
#include <ESP8266WiFi.h>
/* TCP/UDP client library from ESP8266 arduino core */
#include <WiFiClient.h>

/* MQTT client library */
#include <PubSubClient.h>

/* RFID Reader library */
#include <SPI.h>
#include <MFRC522.h>
#include "Desfire.h"

/* Crypto hashing library from ESP8266 arduino core */
#include "Hash.h"

#include "security.h"

#ifdef SSL_SECURE
  #include <WiFiClientSecure.h>
#else
  #include <WiFiClient.h>
#endif

/* Entry location */
/* MQTT credentials must have access to this location */
#define MQTT_ROOT_TOPIC           "es"
#define MQTT_TOPIC_BAT            "b"
#define MQTT_TOPIC_FLOOR          "4"
#define MQTT_TOPIC_ENTRY          "1"
#define MQTT_TOPIC_PUB            "rfid-reader"
#define MQTT_TOPIC_SUB            "lock"

/*
Pin   Code        Arduino alias   Pin   Code        Arduino alias
A0    A0          A0              D6    GPIO 12     12
D0    GPIO 16     16              D7    GPIO 13     13
D1    GPIO 5      5               D8    GPIO 15     15
D2    GPIO 4      4               SD2   GPIO 9      9
D3    GPIO 0      0               SD3   GPIO 10     10
D4    GPIO 2      2               RX    GPIO 3      3
D5    GPIO 14     14              TX    GPIO 1      1
*/

#define GPIO_DENIED               0   // SD2
#define GPIO_GRANTED              10  // SD3
#define GPIO_HEARTBEAT            16  // D0
#define GPIO_BUZZER               2   // D4

/* Routine execution rate definition */
/* Better use RTOS... But i'm lazy */

#define WIFI_CLI_HIGH_RATE        100
#define WIFI_CLI_SLOW_RATE        2000
#define MQTT_CLI_HIGH_RATE        50
#define MQTT_CLI_SLOW_RATE        5000
#define RFID_CLI_RATE             100
#define HEARTBEAT_RATE            250

bool Heartbeat_State = false;
bool RFID_State_Previous = false;

unsigned long WiFi_cli_last_epoch = 0;
unsigned long WiFi_cli_rate = 0;

unsigned long MQTT_cli_last_epoch = 0;
unsigned long MQTT_cli_rate = 0;

unsigned long RFID_last_epoch = 0;
unsigned long RFID_rate = 0;

unsigned long Heartbeat_last_epoch = 0;
unsigned long Heartbeat_rate = 0;

time_t now;

#ifdef SSL_SECURE
  BearSSL::WiFiClientSecure wifiCli;
  //BearSSL::WiFiClientSecureFix wifiCli;
  BearSSL::X509List cert;
#else
  WiFiClient wifiCli;
#endif
PubSubClient mqttCli(wifiCli);

DESFire rfid(4, 5);

int wifiCliStatus = 0xff;
int wifiCliStatusPrevious = 0xff;
bool mqttCliStatus = false;
bool mqttCliStatusPrevious = false;

char mqttCliPubTopic[100];
char mqttCliSubTopic[100];

void mqttConnectionHandler();
void wifiConnectionHandler();
void mqttSubCallback(char*, byte*, unsigned int);
void rfidHandler();

void setup()
{
  Serial.begin(74880);
  Serial.println();
  Serial.println("[SETUP] INFO : Serial UART init.");

  pinMode(GPIO_DENIED, OUTPUT);
  pinMode(GPIO_GRANTED, OUTPUT);
  pinMode(GPIO_HEARTBEAT, OUTPUT);
  pinMode(A0, OUTPUT);
  digitalWrite(GPIO_DENIED, HIGH);
  digitalWrite(GPIO_GRANTED, HIGH);
  digitalWrite(GPIO_HEARTBEAT, HIGH);
  Serial.println("[SETUP] INFO : GPIO init.");

  SPI.begin();
  Serial.println("[SETUP] INFO : SPI init.");
  
  WiFi.disconnect();
  WiFi.begin(WIFI_CLI_SSID, WIFI_CLI_PASSWORD);
  Serial.println("[SETUP] INFO : WiFi reset.");
  
  rfid.PCD_Init();
  Serial.println("[SETUP] INFO : RFID_cli (RC522 Desfire) init.");
  
  strcpy(mqttCliPubTopic, "");
  strcpy(mqttCliSubTopic, "");
  strcat(mqttCliPubTopic, MQTT_ROOT_TOPIC);
  strcat(mqttCliPubTopic, "/");
  strcat(mqttCliPubTopic, MQTT_TOPIC_BAT);
  strcat(mqttCliPubTopic, "/");
  strcat(mqttCliPubTopic, MQTT_TOPIC_FLOOR);
  strcat(mqttCliPubTopic, "/");
  strcat(mqttCliPubTopic, MQTT_TOPIC_ENTRY);
  strcat(mqttCliPubTopic, "/");
  
  strcpy(mqttCliSubTopic, mqttCliPubTopic);
  
  strcat(mqttCliPubTopic, MQTT_TOPIC_PUB);
  strcat(mqttCliSubTopic, MQTT_TOPIC_SUB);
  Serial.println("[SETUP] INFO : Env variable init.");

  mqttCli.setServer(MQTT_CLI_HOST, MQTT_CLI_PORT);
  mqttCli.setCallback(mqttSubCallback);
  Serial.println("[SETUP] INFO : MQTT_cli init.");

  #ifdef SSL_SECURE
    /* Server verification with fingerprint */
    wifiCli.setFingerprint(server_fingerprint);
    //BearSSL::X509List cert(ca_cert);
    //wifiCli.setTrustAnchors(&cert);
    
    /* Client verification */
    /*
    BearSSL::X509List client_crt(client_cert);
    BearSSL::PrivateKey key(client_key);
    wifiCli.setClientRSACert(&client_crt, &key);
    */
    
    /* Time hack */
    wifiCli.setX509Time((time_t) 1583867183);
    
    Serial.println("[SETUP] INFO : BearSSL CA cert init.");
  #endif

  WiFi_cli_rate = WIFI_CLI_HIGH_RATE;
  MQTT_cli_rate = MQTT_CLI_HIGH_RATE;
  RFID_rate = RFID_CLI_RATE;
  Heartbeat_rate = HEARTBEAT_RATE;
  Serial.println("[SETUP] INFO : Routine rates init.");

  Serial.println("[SETUP] INFO : Setup routine success.");
  Serial.println();
}


void loop()
{
  if ( ( millis() - WiFi_cli_last_epoch ) >= WiFi_cli_rate )
  {
    wifiConnectionHandler();
    WiFi_cli_last_epoch = millis();
  }
  if ( ( millis() - MQTT_cli_last_epoch ) >= MQTT_cli_rate )
  {
    mqttConnectionHandler();
    MQTT_cli_last_epoch = millis();
  }
  if ( ( millis() - RFID_last_epoch ) >= RFID_rate )
  {
    rfidHandler();
    RFID_last_epoch = millis();
  }
  if ( ( millis() - Heartbeat_last_epoch ) >= Heartbeat_rate )
  {
    digitalWrite(GPIO_HEARTBEAT, Heartbeat_State = !Heartbeat_State);
    #ifdef SSL_SECURE
      wifiCli.setX509Time((time_t) 1583867183);
    #endif
    Heartbeat_last_epoch = millis();
  }
  delay(1);
}


void wifiConnectionHandler()
{
  wifiCliStatus = WiFi.status();
  if( wifiCliStatus != wifiCliStatusPrevious )
  {
    Serial.print("[WiFi_cli] DEBUG : Wi-Fi State changed : STATUS = ");
    switch(wifiCliStatus)
    {
      case WL_CONNECTED       : Serial.println("WL_CONNECTED");       break;
      case WL_IDLE_STATUS     : Serial.println("WL_IDLE_STATUS");     break;
      case WL_NO_SSID_AVAIL   : Serial.println("WL_NO_SSID_AVAIL");   break;
      case WL_DISCONNECTED    : Serial.println("WL_DISCONNECTED");    break;
      case WL_CONNECT_FAILED  : Serial.println("WL_CONNECT_FAILED");  break;
    }
  
    if (wifiCliStatus == WL_IDLE_STATUS )
    {
      Serial.printf("[WiFi_cli] INFO : Associating to WiFi SSID : %s\n", WIFI_CLI_SSID);
      WiFi.begin(WIFI_CLI_SSID, WIFI_CLI_PASSWORD);
      WiFi_cli_rate = WIFI_CLI_HIGH_RATE;
    }
    else if (wifiCliStatus == WL_CONNECT_FAILED )
    {
      Serial.println("[WiFi_cli] ERROR : Connection failed ! ");
      WiFi_cli_rate = WIFI_CLI_HIGH_RATE;
    }
    else if (wifiCliStatus == WL_NO_SSID_AVAIL )
    {
      Serial.println("[WiFi_cli] ERROR : Not in range ! ");
      WiFi_cli_rate = WIFI_CLI_HIGH_RATE;
    }
    else if (wifiCliStatus == WL_DISCONNECTED )
    {
      if ( wifiCliStatusPrevious != WL_CONNECTED )
      {
        Serial.println("[WiFi_cli] INFO : Not connected. ");
      }
      else
      {
        Serial.println("[WiFi_cli] ERROR : Disconnected. ");
      }
      WiFi_cli_rate = WIFI_CLI_HIGH_RATE;
    }
    else if ( wifiCliStatus == WL_CONNECTED )
    {
      Serial.println("[WiFi_cli] INFO : Connection success. ");
      Serial.print("[WiFi_cli] INFO : Got IP address: ");
      Serial.println(WiFi.localIP());
      Serial.print("[WiFi_cli] INFO : Gateway IP address: ");
      Serial.println(WiFi.gatewayIP());
      WiFi_cli_rate = WIFI_CLI_SLOW_RATE;
    }
    wifiCliStatusPrevious = wifiCliStatus;
  }
  return;
}

void mqttConnectionHandler()
{
  if( /* WiFi.status() == WL_CONNECTED */ wifiCliStatus == WL_CONNECTED )
  {
    mqttCliStatus = mqttCli.connected();
    if( mqttCliStatus != mqttCliStatusPrevious )
    {
      if( !mqttCliStatus )
      {
        Serial.println("[MQTT_cli] ERROR : Disconnected !");
      }
    }
    
    if( mqttCliStatus )
    {
      mqttCli.loop();
    }
    else
    {
      Serial.print("[MQTT_cli] INFO : Attempting MQTT connection..");

      if (mqttCli.connect("", MQTT_CLI_USERNAME, MQTT_CLI_PASSWORD)) {
        Serial.println("connected");
        mqttCli.subscribe(mqttCliSubTopic);
        Serial.print("[MQTT_cli] INFO : Subscribed to MQTT topic [");
        Serial.print(mqttCliSubTopic);
        Serial.println("]");
        MQTT_cli_rate = MQTT_CLI_HIGH_RATE;
      } else {
        Serial.print("failed, rc=");
        Serial.println(mqttCli.state());
        MQTT_cli_rate = MQTT_CLI_SLOW_RATE;
      }
    }
    mqttCliStatusPrevious = mqttCliStatus;
  }
}

void rfidHandler()
{
  if( WiFi.status() == WL_CONNECTED && mqttCli.connected() )
  {
    if ( rfid.PICC_IsNewCardPresent() /*&& !RFID_State_Previous*/ )
    {
      if ( rfid.PICC_ReadCardSerial() )
      { 
          /*RFID_State_Previous = 10;*/
          char uid[100];
          char temp[100];
          char hash[100];
          strcpy(hash, SHA1_SALT_BEFORE);
          Serial.println("[RFID] INFO : Detected new rfid badge");
          sprintf(temp, "%02x", rfid.uid.sak);
          strcat(hash, temp);
          
          Serial.print("   *   SAK = ");
          Serial.print("0x");
          Serial.println(temp);
          Serial.print("   *   UID length : ");
          Serial.println(rfid.uid.size);
          
          strcpy(uid, "   *   UID : {");
          for (byte i = 0; i < rfid.uid.size; i++)
          {
            sprintf(temp, "%02x", rfid.uid.uidByte[i]);
            strcat(hash, temp);
            strcat(uid, "0x");
            strcat(uid, temp);
            if (i < rfid.uid.size - 1)
            {
              strcat(uid, ", ");
            }
            else
            {
              strcat(uid, "}");
            }
          }
          Serial.println(uid);
          strcat(hash, SHA1_SALT_AFTER);
          sha1(hash).toCharArray(hash, 100);
          Serial.print("   *   SHA1 hash footprint : ");
          Serial.println(hash);
          Serial.print("[MQTT_cli] INFO : Publishing to MQTT topic [");
          Serial.print(mqttCliPubTopic);
          Serial.print("] payload : ");
          Serial.println(hash);
          mqttCli.publish(mqttCliPubTopic, hash);
      }   
    }
  }
  /*
  else if ( rfid.PICC_IsNewCardPresent() ) 
  {
    return;
  }
  else
  {
    if ( RFID_State_Previous )
      RFID_State_Previous = false;
  }
  */
}

void mqttSubCallback(char* topic, byte* payload, unsigned int length) {
  if ( !strcmp( topic, mqttCliSubTopic ) )
  {
    Serial.print("[MQTT_cli] INFO : Message arrived from subscribed MQTT topic [");
    Serial.print(topic);
    Serial.print("] payload : ");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    digitalWrite(GPIO_HEARTBEAT, Heartbeat_State = true);
    if ( length == 1 && (char)payload[0] == '1') {
      Serial.println("[MQTT_cli] INFO : Door access : GRANTED");

      digitalWrite(GPIO_GRANTED, LOW);
      Serial.println("[HW_ctrl] INFO : Door state : UNLOCK");
      
      tone(GPIO_BUZZER, 2850);
      delay(100);
      noTone(GPIO_BUZZER);
      delay(100);
      tone(GPIO_BUZZER, 2850);
      delay(100);
      noTone(GPIO_BUZZER);
      
      delay(4000);
      digitalWrite(GPIO_GRANTED, HIGH);
      Serial.println("[HW_ctrl] INFO : Door state : LOCK");
      
    } else if ( length == 1 && (char)payload[0] == '0') {
      Serial.println("[MQTT_cli] INFO : Door access : DENIED");
      digitalWrite(GPIO_DENIED, LOW);
      tone(GPIO_BUZZER, 800);
      delay(500);
      noTone(GPIO_BUZZER);
      delay(500);
      tone(GPIO_BUZZER, 800);
      delay(500);
      noTone(GPIO_BUZZER);
      digitalWrite(GPIO_DENIED, HIGH);
    }
  }
}
