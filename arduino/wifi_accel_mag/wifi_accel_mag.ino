#include <Wire.h>
#include <LSM303.h>
#include <WiFlyHQ.h>

/* Change these to match your WiFi network */
const char mySSID[] = "internetz";
const char myPassword[] = "1nt3rn3tz";

WiFly wifly;

LSM303 compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
      char buf[32];

    Serial.begin(9600);
//    Serial.println("Starting");
//    Serial.print("Free memory: ");
//    Serial.println(wifly.getFreeMemory(),DEC);

    Serial1.begin(9600);

    if (!wifly.begin(&Serial1,&Serial)) {
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
	Serial.println("Joining network");
	wifly.setSSID(mySSID);
	wifly.setPassphrase(myPassword);
	wifly.enableDHCP();

	if (wifly.join()) {
	    Serial.println("Joined wifi network");
	} else {
	    Serial.println("Failed to join wifi network");
	    //terminal();
	}
    } else {
        Serial.println("Already joined network");
    }

    /* Setup for UDP packets, sent automatically */
    wifly.setIpProtocol(WIFLY_PROTOCOL_UDP);
    wifly.setHost("192.168.1.6", 11999);	// Send UDP packet to this server and port



    wifly.setDeviceID("Wifly-UDP");

    wifly.setHost("192.168.1.6", 11999);	// Send UPD packets to this server and port

    Serial.println("WiFly ready");
}

void loop() {
  compass.read();

  //Serial.print("A ");
  //wifly.print("");
  wifly.print((int)compass.a.x);
  wifly.print("|");
  wifly.print((int)compass.a.y);
  wifly.print("|");
  wifly.print((int)compass.a.z);
  wifly.print("|");
  wifly.print((int)compass.m.x);
  wifly.print("|");
  wifly.print((int)compass.m.y);
  wifly.print("|");
  wifly.print((int)compass.m.z);
  wifly.print("[/p]");
  
  delay(100);
}
