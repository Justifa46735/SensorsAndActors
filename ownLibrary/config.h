char*   WIFI_SSID       = "YourSSID";
char*   WIFI_PASSWORD   = "YourPassword";

// MQTT defenitions

const char*   MQTT_HOST       = "192.168.178.36";
const int     MQTT_PORT       = 1883;
const char*   MQTT_CLIENTID   = "airquality-client";
const char*   MQTT_CLIENTID_2   = "airquality-client_2";
const char*   MQTT_CLIENTID_3   = "airquality-client_3";
const char*   MQTT_CLIENTID_4   = "airquality-client_4";
const char*   MQTT_CLIENTID_5   = "airquality-client_5";
const char*   MQTT_CLIENTID_6   = "airquality-client_6";
const char*   MQTT_USERNAME   = "username";
const char*   MQTT_PASSWORD   = "password";
const String  MQTT_BASE_TOPIC = "mp/meetingrooms/airquality"; 
const String  MQTT_SUBSCRIBE_TOPIC_LEVEL_1 = "mpRoom";
const String  MQTT_SUBSCRIBE_TOPIC_LEVEL_2 = "getData";

const int     MQTT_RETRY_WAIT = 5000;

// Message/Datatypes of the sensor values
// They will be also be part of the mqtt Topic

const char*  MQTT_TEMPERATURE = "temperature";
const char*  MQTT_PRESSURE = "pressure";
const char*  MQTT_HUMIDITY = "humidity";
const char*  MQTT_GAS = "gas";
const char*  MQTT_ALTITUDE = "altitude";
const char*  MQTT_PPM = "ppm";
const char*  MQTT_PM2DOT5 = "pm2dot5";
const char*  MQTT_PM10 = "pm10";

// Module name of the sensors
// They will be also be part of the mqtt Topic
const char*  MQTT_BME680_TOPIC_LEVEL_1 = "BME680";
const char*  MQTT_DHT22_TOPIC_LEVEL_1 = "DHT22";
const char*  MQTT_DHT22_2_TOPIC_LEVEL_1 = "DHT22_2";
const char*  MQTT_BMP180_TOPIC_LEVEL_1 = "BMP180";
const char*  MQTT_BMP180_2_TOPIC_LEVEL_1 = "BMP180_2";
const char*  MQTT_SDS011_TOPIC_LEVEL_1 = "SDS011";
