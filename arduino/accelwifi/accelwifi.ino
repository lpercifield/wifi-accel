/*
 * WiFlyHQ Example udpclient.ino
 *
 * This sketch implements a simple UDP client that sends a UDP packet
 * to a UDP server every second.
 *
 * This sketch is released to the public domain.
 *
 */


#include <WiFlyHQ.h>

/* Change these to match your WiFi network */
const char mySSID[] = "nws-parsons";
const char myPassword[] = "nws-parsons";

WiFly wifly;

int x,y,z;

void setup()
{
    char buf[32];

    Serial.begin(9600);
//    Serial.println("Starting");
//    Serial.print("Free memory: ");
//    Serial.println(wifly.getFreeMemory(),DEC);

//    wifiSerial.begin(9600);
    pinMode(A5,OUTPUT);
    digitalWrite(A5,LOW);

    if (!wifly.begin(&Serial)) {
        Serial.println("Failed to start wifly");
	//terminal();
    }

    if (wifly.getFlushTimeout() != 10) {
        //Serial.println("Restoring flush timeout to 10msecs");
        wifly.setFlushTimeout(10);
	wifly.save();
	wifly.reboot();
    }

    /* Join wifi network if not already associated */
    if (!wifly.isAssociated()) {
	/* Setup the WiFly to connect to a wifi network */
	//Serial.println("Joining network");
	wifly.setSSID(mySSID);
	wifly.setPassphrase(myPassword);
	wifly.enableDHCP();

	if (wifly.join()) {
	    //Serial.println("Joined wifi network");
	} else {
	    //Serial.println("Failed to join wifi network");
	    //terminal();
	}
    } else {
        //Serial.println("Already joined network");
    }

    /* Setup for UDP packets, sent automatically */
    wifly.setIpProtocol(WIFLY_PROTOCOL_UDP);
    wifly.setHost("10.0.1.20", 11999);	// Send UDP packet to this server and port



    wifly.setDeviceID("Wifly-UDP");

    wifly.setHost("10.0.1.20", 11999);	// Send UPD packets to this server and port

    //Serial.println("WiFly ready");
}

uint32_t lastSend = 0;
uint32_t count=0;

void loop()
{
    x = analogRead(A2);
    y = analogRead(A3);
    z = analogRead(A4);
    wifly.print(x);
    wifly.print("|");
    wifly.print(y);
   wifly.print("|");
   wifly.print(z);
    wifly.print("[/p]");
    delay(50);                // found i need a short delay before second TX

}

