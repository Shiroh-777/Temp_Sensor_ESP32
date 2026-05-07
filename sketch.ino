#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4       // GPIO conectado ao DATA
#define DHTTYPE DHT22  // Tipo do sensor

#define LED_VERDE 2
#define LED_VERMELHO 15

float ultimaTemp = -1000;
float ultimaUmid = -1000;

DHT dht(DHTPIN, DHTTYPE);

// Endereço comum: 0x27 ou 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();          // Inicializa o LCD
  lcd.backlight();     // Liga o backlight

  lcd.setCursor(0, 0); // Coluna 0, linha 0

Serial.begin(115200);
  dht.begin();

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

}

void loop() {

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    lcd.print("Erro ao ler o DHT22!");

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    return;
  }

// Leitura OK
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);
  
if (temperatura != ultimaTemp || umidade != ultimaUmid) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(umidade);
    lcd.print(" %");

    // Atualiza os valores anteriores
    ultimaTemp = temperatura;
    ultimaUmid = umidade;

  delay(2000);
}
}
