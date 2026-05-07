#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// Definição do sensor DHT22
#define DHTPIN 2        // Pino de dados do DHT22 (DOUT)
#define DHTTYPE DHT22   // Tipo: DHT22

// Inicializar sensor DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inicializar LCD I2C (endereço 0x27, 16x2 caracteres)
// Se não funcionar, tente 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variáveis para armazenar leituras
float temperatura = 0;
float umidade = 0;

void setup() {
  // Iniciar Serial para debug
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("\n\n");
  Serial.println("Sistema de Monitoramento DHT22 + LCD I2C");
  Serial.println("=========================================");
  
  // Iniciar LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DHT22 + LCD I2C");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(2000);
  
  // Iniciar sensor DHT22
  dht.begin();
  
  // Limpar LCD
  lcd.clear();
  
  Serial.println("Sistema inicializado com sucesso!");
  Serial.println("Pinos utilizados:");
  Serial.println("  - DHT22 DOUT  → Pino 2");
  Serial.println("  - LCD SDA      → Pino A4");
  Serial.println("  - LCD SCL      → Pino A5");
  Serial.println("  - DHT22 VCC    → 5V");
  Serial.println("  - DHT22 GND    → GND");
  Serial.println("  - LCD VCC      → 5V");
  Serial.println("  - LCD GND      → GND");
}

void loop() {
  // Ler dados do sensor DHT22
  lerSensorDHT22();
  
  // Exibir no LCD
  exibirNoLCD();
  
  // Exibir no Serial Monitor
  exibirNoSerial();
  
  // Aguardar 2 segundos antes da próxima leitura
  delay(2000);
}

// Função para ler dados do DHT22
void lerSensorDHT22() {
  // DHT22 recomenda esperar ~2 segundos entre leituras
  umidade = dht.readHumidity();
  temperatura = dht.readTemperature();
  
  // Verificar se a leitura falhou
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Erro na leitura do DHT22!");
    temperatura = 0;
    umidade = 0;
    return;
  }
}

// Função para exibir no LCD
void exibirNoLCD() {
  // Limpar tela
  lcd.clear();
  
  // Primeira linha: Temperatura
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print("C");
  
  // Segunda linha: Umidade
  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(umidade);
  lcd.print("%");
}

// Função para exibir no Serial Monitor (Debug)
void exibirNoSerial() {
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C | Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");
}
