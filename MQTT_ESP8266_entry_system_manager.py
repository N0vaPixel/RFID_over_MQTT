import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT server with result code "+str(rc))
    client.subscribe("es/+/+/+/rfid-reader")
    print("Subscribed to MQTT topic [es/+/+/+/rfid-reader]")
    client.subscribe("es/+/+/+/smartphone-app")
    #print("Subscribed to MQTT topic [es/+/+/+/smartphone-app]")
    print("")

def on_message(client, userdata, msg):
    print("From subscribed MQTT topic [" + msg.topic + "] - Received badge footprint : " + str(msg.payload))
    if (msg.payload == b'29e82f1d4d73fe3e8357876e7aff6719f97383fd' ):
        client.publish("es/b/4/1/lock", payload="1", qos=0, retain=False)
        print("Granted access for badge with footprint : " + str(msg.payload))
        print("Publishing to MQTT topic [" + "es/b/4/1/lock" + "] payload : 1")
    else:
        client.publish("es/b/4/1/lock", payload="0", qos=0, retain=False)
        print("Denied access for badge with footprint : " + str(msg.payload))
        print("Publishing to MQTT topic [" + "es/b/4/1/lock" + "] payload : 0")
    print("\n")
    print("\n")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set("es-manager", "es-manager")
client.connect("192.168.0.1", 1883, 60)

client.loop_forever()
