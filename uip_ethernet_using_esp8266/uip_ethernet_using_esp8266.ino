#include <UIPEthernet.h>

EthernetClient client;
uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
IPAddress IP(192,168,1,121);
//EthernetServer server(80);
//byte serv[] = {192, 168, 1, 117} ;   //Enter the IPv4 address
byte serv[] = "www.vinevon.com" ;   //Enter the IPv4 address
String readString;
//EthernetClient cliente;
void setup() 
{
  Serial.begin(9600);
//  char server[] = "www.iotgecko.com";
//  Serial.println("enter");
  Ethernet.init(15);
//  Serial.println("init");
  Ethernet.begin(mac,IP);
  Serial.println(Ethernet.localIP());
  Serial.println(Ethernet.gatewayIP());
  Serial.println(Ethernet.dnsServerIP());
//  server.begin();
}

void loop()
{ 
//  EthernetClient client = serv.available();
//  Serial.println(client);
  if (client.connect(serv,80))
  {
      Serial.println("connected");
      char c = client.read();
      client.print("GET /ethernet/data.php?");
      client.print("temperature=");
      client.print(120);
      client.print("&humidity=");
      client.print(50);
      client.print("&heat_index=");
      client.println(20);
      client.println();
      delay(1);
      client.stop();        
  }
  else
  {
     Serial.println("connection failed");
  }
}
