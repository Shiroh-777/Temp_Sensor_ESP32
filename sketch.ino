#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4       // GPIO conectado ao DATA
#define DHTTYPE DHT22  // Tipo do sensor

DHT dht(DHTPIN, DHTTYPE);

// Endereço comum: 0x27 ou 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();          // Inicializa o LCD
  lcd.backlight();     // Liga o backlight

  lcd.setCursor(0, 0); // Coluna 0, linha 0

Serial.begin(115200);
  dht.begin();

}

void loop() {

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    lcd.print("Erro ao ler o DHT22!");
    return;
  }

  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print(" °C  |  Umidade: ");
  lcd.print(umidade);
  lcd.print(" %");

  delay(2000);
}
