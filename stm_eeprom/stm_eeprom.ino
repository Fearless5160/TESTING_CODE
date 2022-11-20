#include <EEPROM.h>

const int addressEEPROM_min = 0;              //Tentukan batasan alamat yang ingin digunakan.
const int addressEEPROM_max = 4095;           //Sebagai contoh maksimum adalah 4095, artinya kita alokasikan memori 4KB (4096 bytes) untuk EEPROM Virtual.

float latitude =   4.158919;                  //Ini adalah contoh data yang ingin disimpan ke EEPROM.
float longitude = 96.124843;                  //Data Koordinat yang terdiri dari Latitude dan Longitude.

int addressLat = 0;                           //Jumlah karakter dari nilai latitude adalah 8, jadi alamat dimulai dari 0 hingga 8.
int addressLon = 9;                           //Jumlah karakter dari nilai longitude adalah 9, jadi alamat dimulai dari 9 hingga 17.

void setup()
{
  Serial.begin(9600);
  delay(100);

  String lat = String (latitude, 6);         //Data yang akan disimpan ke EEPROM adalah String. Baris ini digunakan untuk konversi float ke String.
  String lon = String (longitude, 6);        //Nilai 6 menunjukkan berapa banyak angka dibelakang koma yang akan di konversi.

  //------------------- Perintah Tulis Data -------------------
  Serial.println(" -----------------------------------------");
  Serial.println("| Menulis Latitude  ke EEPROM | Tersimpan |");
  EEPROMwrite(addressLat, lat);
  Serial.println("| Menulis Longitude ke EEPROM | Tersimpan |");
  EEPROMwrite(addressLon, lon);
  Serial.println(" -----------------------------------------");
  Serial.println("\n");
  delay(1000);
  //----------------------------------------------------------

  //------------------- Perintah Baca Data -------------------
  Serial.println("Baca data dari EEPROM.....");
  Serial.print("Latitude  : ");
  Serial.println(EEPROMread(addressLat, 8));  //Ambil data dari alamat 0 dengan jumlah karakter sebanyak 8.
  Serial.print("Longitude : ");
  Serial.println(EEPROMread(addressLon, 9));  //Ambil data dari alamat 9 dengan jumlah karakter sebanyak 9.
  Serial.println("\n");
  delay(1000);
  //----------------------------------------------------------

  Serial.println("Sekarang, silahkan COMMENT *Perintah Tulis Data* untuk menonaktifkan perintah tulis data ke EEPROM.");
  delay(5000);
  Serial.println("Kemudian, silahkan tekan tombol reset atau cabut STM32 dari komputer, untuk melihat apakah data dari EEPROM tetap tersimpan atau tidak.");
} 

void loop()
{

}

String EEPROMread(int StartAddr, int StringLength)
{
  char buf[StringLength + 1];
  eeprom_read_string(StartAddr, buf, StringLength + 1);
  String dataStr = buf;
  return dataStr;
}

void EEPROMwrite(int StartAddr, String DataString)
{
  int val = DataString.length() + 1;
  char StringChar[val];
  char buff[val];

  DataString.toCharArray(StringChar, val);
  strcpy(buff, StringChar);
  eeprom_write_string(StartAddr, buff);
}

boolean eeprom_is_addr_ok(int addr)
{
  return ((addr >= addressEEPROM_min) && (addr <= addressEEPROM_max));
}

boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes)
{
  int i;

  if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes))
  {
    return false;
  }

  for (i = 0; i < numBytes; i++)
  {
    EEPROM.write(startAddr + i, array[i]);
  }
  return true;
}

boolean eeprom_write_string(int addr, const char* string)
{
  int numBytes;                                                    // jumlah byte aktual yang akan ditulis

  numBytes = strlen(string) + 1;                                   // Tulis konten string ditambah byte terminator string (0x00)
  return eeprom_write_bytes(addr, (const byte*)string, numBytes);
}

boolean eeprom_read_string(int addr, char* buffer, int bufSize)
{
  byte ch;                                                         // byte baca dari eeprom
  int bytesRead;                                                   // jumlah byte yang dibaca sejauh ini

  if (!eeprom_is_addr_ok(addr))                                    // periksa alamat mulai
  {
    return false;
  }

  if (bufSize == 0)                                                // bagaimana kita bisa menyimpan byte dalam buffer kosong?
  {
    return false;
  }

  if (bufSize == 1)                                                // apakah ada ruang untuk terminator string saja, tidak ada alasan untuk melangkah lebih jauh
  {
    buffer[0] = 0;
    return true;
  }

  bytesRead = 0;                                                   // inisialisasi penghitung byte
  ch = EEPROM.read(addr + bytesRead);                              // baca byte berikutnya dari eeprom
  buffer[bytesRead] = ch;                                          // simpan ke dalam buffer pengguna
  bytesRead++;

  // jika tidak ada kondisi berhenti terpenuhi, baca byte berikutnya dari eeprom
  while ( (ch != 0x00) && (bytesRead < bufSize) && ((addr + bytesRead) <= addressEEPROM_max) )
  {
    ch = EEPROM.read(addr + bytesRead);
    buffer[bytesRead] = ch;                                        // simpan ke dalam buffer pengguna
    bytesRead++;
  }

  if ((ch != 0x00) && (bytesRead >= 1))                            // pastikan buffer pengguna memiliki terminator string, (0x00) sebagai byte terakhirnya
  {
    buffer[bytesRead - 1] = 0;
  }
  return true;
