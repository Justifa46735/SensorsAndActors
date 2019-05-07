char*   WIFI_SSID       = "MP_INTERNAL1";
//mp_dart";
char*   WIFI_PASSWORD   = "esp8266_2";
//siemens18";

// MQTT defenitions

const char*   MQTT_HOST       = "10.10.30.145";
//192.168.178.199";
const int     MQTT_PORT       = 1883;
const char*   MQTT_CLIENTID   = "airquality-client_2";
const char*   MQTT_USERNAME   = "username";
const char*   MQTT_PASSWORD   = "password";
const String  MQTT_BASE_TOPIC = "/de/methodpark/er/smart";
//mp/meetingrooms/airquality"; 
const String  MQTT_SUBSCRIBE_TOPIC_LEVEL_1 = "speakers_corner";
const String  MQTT_SUBSCRIBE_TOPIC_LEVEL_2 = "getData";
const int     MQTT_RETRY_WAIT = 5000;

// Message/Datatypes of the sensor values
// They will be also be part of the mqtt Topic

const char*  MQTT_TEMPERATURE = "temperature";
const char*  MQTT_PRESSURE = "pressure";
const char*  MQTT_HUMIDITY = "humidity";
const char*  MQTT_GAS = "gas";
const char*  MQTT_ALTITUDE = "altitude";
const char*  MQTT_PPM = "carbon_dioxide";
//const char*  MQTT_PPM = "ppm";
