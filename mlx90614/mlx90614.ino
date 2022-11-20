#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
String c = "";

void setup()
{
   Serial.begin(9600);
   mlx.begin();
   Serial.println("9600");
   mlx.writeEmissivityReg(64650); 
   Serial.println(mlx.readEmissivity());
   delay(1000);
}

void loop()
{
      Serial.print("Ambient: ");
      Serial.print(mlx.readObjectTempF()); 
      Serial.println(" F");
      Serial.print("Object: ");
      Serial.print(mlx.readObjectTempC()); 
      Serial.println(" C");
      delay(5000);
}
