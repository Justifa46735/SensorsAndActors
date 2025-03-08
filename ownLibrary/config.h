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
const char*   MQTT_CLIENTID_7   = "airquality-client_7";
const char*   MQTT_CLIENTID_8   = "airquality-client_8";
const char*   MQTT_CLIENTID_9   = "airquality-client_9";
const char*   MQTT_USERNAME   = "username";
const char*   MQTT_PASSWORD   = "password";
const String  MQTT_SUBSCRIBE_TOPIC_LEVEL_2 = "getData";

const int     MQTT_RETRY_WAIT = 500;

// Message/Datatypes of the sensor values
// They will be also be part of the mqtt Topic

const char*  MQTT_TEMPERATURE = "temperature";
const char*  MQTT_HEATINDEX = "heatindex";
const char*  MQTT_PRESSURE = "pressure";
const char*  MQTT_HUMIDITY = "humidity";
const char*  MQTT_GAS = "gas";
const char*  MQTT_ALTITUDE = "altitude";
const char*  MQTT_PPM = "ppm";
const char*  MQTT_PPM_UART = "ppm_uart";
const char*  MQTT_PPM_PWM = "ppm_pwm";
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
const char*  MQTT_MHZ19B_TOPIC_LEVEL_1 = "MHZ19B";
const char*  MQTT_MHZ14A_TOPIC_LEVEL_1 = "MHZ14A";
const char*  MQTT_PMS7003_TOPIC_LEVEL_1 = "PMS7003";
