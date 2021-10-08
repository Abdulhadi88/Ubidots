#include <DHT.h>
#include <UbidotsMicroESP8266.h>

#define DHTPIN 4 // mendefriniskan in dhtr di node mcu ada 4 D2 = 4
#define DHTTYPE DHT11//medefinisikan tipe dht yang kita gunakan

char auth[] = "BBFF-IWcTUrmoHaqRfpDz2xfM9bJ5GYIK5L";
char ssid[] = "IDN Boarding School";
char pass[] = "12rpl";

DHT dht(DHTPIN, DHTTYPE);
Ubidots client(auth); // setting token dari ubidots
unsigned long last = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); //sensor mulai membaca suhu dan kelembapan
  delay(20); // delay 0,2 detik
  client.wifiConnection(ssid,pass); //waktu untuk mengirimkan data setiap 1 detik sekali

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-last>10000){ // jika sudah 10 detik
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis(); // 11 millis
    client.add("kelembapan",hum); //ubidots baca lembap
    client.add("temperature",temp); // ubidots baca suhu
    client.sendAll(true); //ubisoft mengirim semua data
  }
}

 
