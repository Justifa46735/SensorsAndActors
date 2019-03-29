PubSubClient client(espClient);

void connectMqtt() {
  Serial.println("Connecting to MQTT...");
  client.setServer(MQTT_HOST, MQTT_PORT);

  while (!client.connected()) {
    if (!client.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.print("MQTT connection failed:");
      Serial.print(client.state());
      Serial.println("Retrying...");
      delay(MQTT_RETRY_WAIT);
    }
  }

  Serial.println("MQTT connected");
  Serial.println("");
}

void disconnectMqtt() {
  client.disconnect();
  Serial.println("MQTT disconnected");
}


void mqttMyCallback (char *topic, byte *payload, unsigned int length)
{
  String subscribeTopic = MQTT_BASE_TOPIC + "/" + MQTT_SUBSCRIBE_TOPIC_LEVEL_1 + "/" + MQTT_SUBSCRIBE_TOPIC_LEVEL_2;
  payload[length] = '\0';
  int waterTime = atoi((char *)payload);
  Serial.print("Watering Time ");
  Serial.println(waterTime);
}


void subscribeTopics()
{
  String subscribeTopic = MQTT_BASE_TOPIC + "/" + MQTT_SUBSCRIBE_TOPIC_LEVEL_1 + "/" + MQTT_SUBSCRIBE_TOPIC_LEVEL_2;
  client.subscribe(subscribeTopic.c_str(), 1);
  client.setCallback(&mqttMyCallback);
}

void publishData(const char* DataType, double _msg)
{
  char msg[64];
  snprintf(msg, 64, "%.2f", _msg);
  Serial.println("publish data");
  Serial.println(DataType);
  Serial.println(msg);
  String publishTopic = MQTT_BASE_TOPIC + "/" + MQTT_SUBSCRIBE_TOPIC_LEVEL_1 + "/" + DataType;

  client.publish(publishTopic.c_str(), msg);
}
