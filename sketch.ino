#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ===== OrbitWatch - Estacao Terrestre de Rastreamento =====
// Simula deteccao de detritos espaciais e calculo de risco de colisao

// Pinos
const int PINO_LDR = A0;          // Telescopio (deteccao de objeto)
const int PINO_POT = A1;          // Sensibilidade do operador
const int LED_VERDE = 8;          // Risco baixo
const int LED_AMARELO = 9;        // Risco medio
const int LED_VERMELHO = 10;      // Risco alto
const int BUZZER = 11;            // Alarme critico

// LCD I2C no endereco 0x27, 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  OrbitWatch");
  lcd.setCursor(0, 1);
  lcd.print(" Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Le o telescopio (LDR) e a sensibilidade (potenciometro)
  int leituraLDR = analogRead(PINO_LDR);
  int sensibilidade = analogRead(PINO_POT);

  // Calcula o risco combinando luz captada e sensibilidade ajustada
  // Quanto mais luz e maior sensibilidade, maior o risco percebido
  int risco = map(leituraLDR, 0, 1023, 0, 100);
  int ajuste = map(sensibilidade, 0, 1023, 0, 50);
  int riscoFinal = risco + ajuste;
  if (riscoFinal > 100) riscoFinal = 100;

  // Imprime no monitor serial pra debug
  Serial.print("LDR: ");
  Serial.print(leituraLDR);
  Serial.print(" | Pot: ");
  Serial.print(sensibilidade);
  Serial.print(" | Risco: ");
  Serial.print(riscoFinal);
  Serial.println("%");

  // Atualiza o LCD
  lcd.setCursor(0, 0);
  lcd.print("Objeto detectado");
  lcd.setCursor(0, 1);
  lcd.print("Risco: ");
  lcd.print(riscoFinal);
  lcd.print("%   ");  // espacos limpam caracteres antigos

  // Decide o nivel de alerta
  if (riscoFinal < 40) {
    // Risco baixo - so verde
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
  }
  else if (riscoFinal < 75) {
    // Risco medio - amarelo
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
  }
  else {
    // Risco alto - vermelho + buzzer
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    tone(BUZZER, 1000);  // som de 1000 Hz
  }

  delay(500);
}