
#include <SPI.h>
#include <Ethernet.h>
#include <ICMPPing.h> //Ethernet library moet hiervoor naar 1.1.2 niet compatible met 2.0.0!!
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <w5100.h>

int changeScreen = 0;

// Enter a MAC address for your controller below.
byte mac[] = {0x12, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
//byte ip[] = {172,30,1,25};    niet nodig want gaat op basis van DHCP

//init Ping
IPAddress pingAddr(8,8,8,8); // ip address to ping "Google"
//
SOCKET pingSocket = 0;
//
char buffer [256];
ICMPPing ping(pingSocket, (uint16_t)random(0, 255));

//init LCD
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);  //


void setup() {
    //Start LCD
    lcd.begin(16, 2);
    lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
    lcd.setBacklight(HIGH);

    lcd.setCursor(0, 0);
    lcd.print("Welkom bij de");
    lcd.setCursor(0, 1);
    lcd.print("Vergeer-Sniffer");

    delay(4000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Stop de internet");
    lcd.setCursor(0, 1);
    lcd.print("kabel erin");
   // Serial.println(Ethernet.linkStatus());   deze functie is alleen beschikbaar bij 2.0.0
    delay(7000);

    // Open serial communications and wait for port to open:
    Serial.begin(9600);

    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

    // start the Ethernet connection:
    Serial.println("Initialize Ethernet with DHCP:");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Zoeken naar: ...");
    lcd.setCursor(0, 1);
    lcd.print("IP-adres");
    delay(1000);


    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Krijg geen DHCP");
        lcd.setCursor(0, 1);
        lcd.print("Onbekend Netwerk");
        delay(1000);

        while (true) {
            delay(1);
        }
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mijn IP is");

    // print your local IP address:
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());

    lcd.setCursor(0, 1);
    lcd.print(Ethernet.localIP());
    delay(5000);
}

void loop() {
    ICMPEchoReply echoReply = ping(pingAddr, 4);

    if (echoReply.status == SUCCESS)  {
        sprintf(buffer,
              "Reply[%d] from: %d.%d.%d.%d: bytes=%d time=%ldms TTL=%d",
              echoReply.data.seq,
              echoReply.addr[0],
              echoReply.addr[1],
              echoReply.addr[2],
              echoReply.addr[3],
              REQ_DATASIZE,
              millis() - echoReply.data.time,
              echoReply.ttl);
        if (changeScreen == 0) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Kan op internet!");
            lcd.setCursor(0, 1);
            lcd.print(Ethernet.localIP());
            changeScreen = 1;
            delay(4000);
        } else if (changeScreen == 1) {
            lcd.clear();
            lcd.setCursor(0, 0);
           // lcd.print(Ethernet.gatewayIP());
            lcd.print("Gateway is: ");
            lcd.setCursor(0, 1);
            lcd.print(Ethernet.gatewayIP());
            changeScreen = 2;
            delay(2000);
        } else if (changeScreen == 2) {
            lcd.clear();
            lcd.setCursor(0, 0);
           // lcd.print(Ethernet.gatewayIP());
            lcd.print("Subnetmask is ");
            lcd.setCursor(0, 1);
            lcd.print(Ethernet.subnetMask());
            changeScreen = 0;
            delay(2000);
        }
      }
      else {
        sprintf(buffer, "Echo request failed; %d", echoReply.status);
        if (changeScreen == 0) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Geen internet!");
            lcd.setCursor(0, 1);
            lcd.print(Ethernet.localIP());
            changeScreen = 1;
            delay(4000);
        } else if (changeScreen == 1) {
            lcd.clear();
            lcd.setCursor(0, 0);
           // lcd.print(Ethernet.gatewayIP());
            lcd.print("Gateway is: ");
            lcd.setCursor(0, 1);
            lcd.print(Ethernet.gatewayIP());
            changeScreen = 2;
            delay(2000);
        } else if (changeScreen == 2) {
            lcd.clear();
            lcd.setCursor(0, 0);
           // lcd.print(Ethernet.gatewayIP());
            lcd.print("Subnetmask is ");
            lcd.setCursor(0, 1);
            lcd.print(Ethernet.subnetMask());
            changeScreen = 0;
            delay(2000);
        }
   }

}
