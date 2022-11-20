// Present a "Will be back soon web page", as stand-in webserver.
// 2011-01-30 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php
 
#include <EtherCard.h>
//
//#define STATIC 0  // set to 1 to disable DHCP (adjust myip/gwip values below)
//
//#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,121 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
static byte dnsip[] = { 192,168,1,1 };
//#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

const char page[] PROGMEM = "www.iotgecko.com";
//"HTTP/1.0 503 Service Unavailable\r\n"
//"Content-Type: text/html\r\n"
//"Retry-After: 600\r\n"
//"\r\n"
//"<html>"
//  "<head><title>"
//    "Service Temporarily Unavailable"
//  "</title></head>"
//  "<body>"
//    "<h3>finally done</h3>"
//    "<p><em>"
//      "nevon has been awesome .<br />"
//      "Please try again later."
//    "</em></p>"
//  "</body>"
//"</html>"
//;

void setup(){
  Serial.begin(115200);
  Serial.println("\n[backSoon]");
  
  if (ether.begin(sizeof Ethernet::buffer, mymac, 15) == 0) 
    Serial.println( "Failed to access Ethernet controller");
    
  Serial.println(F("Setting up DHCP"));
  ether.staticSetup(myip, gwip, dnsip);
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
}

void loop(){
  // wait for an incoming TCP packet, but ignore its contents
  if (ether.packetLoop(ether.packetReceive())) {
    memcpy_P(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
  }
}
