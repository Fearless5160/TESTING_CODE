
#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");
  delay(1000);
  if (!SD.begin(D4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("vinayak nevon");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  else 
  {
    Serial.println("error opening test.txt");
  }

//   re-open the file for reading:
  myFile = SD.open("test.csv", FILE_READ);
  if (myFile) 
  {
    Serial.println("test.txt:");

    while (myFile.available())
    {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else 
  {
    Serial.println("error opening test.txt");
  }
}

void loop()
{
  // nothing happens after setup
}
