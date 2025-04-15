#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <ESP32Servo.h>
 // Certifique-se de incluir a biblioteca VarServo conforme instruído

// --- Configuração do LCD ---
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço 0x27, 16 colunas e 2 linhas

// --- Configuração do Teclado Matricial ---
const byte ROWS = 4; // 4 linhas
const byte COLS = 4; // 4 colunas

// Definição dos caracteres do teclado
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Observe: Usaremos '*' como confirmar e '#' como apagar (backspace).
// Os outros botões (A, B, C e D) podem ser ignorados ou customizados, mas no nosso projeto apenas os numéricos, '*' e '#' serão utilizados.
byte rowPins[ROWS] = {15, 2, 4, 16};   // Pinos das linhas
byte colPins[COLS] = {17, 5, 18, 19};    // Pinos das colunas

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// --- Configuração do Servo Motor ---
Servo servo;  // Objeto servo usando a biblioteca VarServo
const int servoPin = 14;  // Pino definido para o servo

// --- Configuração dos LEDs ---
const int ledVerde = 12;
const int ledVermelho = 13;

// --- Parâmetros do Sistema ---
const String senhaCorreta = "12345678";  // Senha padrão
String senhaDigitada = "";  // Armazena os dígitos digitados

// Tempos de delay
const unsigned long tempoPortaAberta = 5000; // 5 segundos para porta aberta
const unsigned long tempoAcessoNegado = 2000;  // 2 segundos para mensagem de acesso negado

// Função para limpar o estado e voltar à tela inicial
void resetSistema() {
  senhaDigitada = "";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Inicializacao");
  
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);
  // Garante a porta fechada (posição 0°)
  servo.write(0);
}

void setup() {
  // Inicialização dos componentes
  Serial.begin(115200);
  
  // Inicia o LCD e exibe a mensagem inicial
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Inicializacao");
  
  // Configuração dos LEDs como saída
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);
  
  // Configuração do servo
  servo.attach(servoPin);
  servo.write(0);  // Inicia com a porta fechada
  
  // Mensagem inicial no Serial (opcional)
  Serial.println("Sistema Iniciado!");
}

void loop() {
  char tecla = keypad.getKey();
  
  if (tecla) {  // Se uma tecla foi pressionada
    // Se for número, adiciona até 8 dígitos
    if (tecla >= '0' && tecla <= '9') {
      if (senhaDigitada.length() < 8) {
        senhaDigitada += tecla;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Senha: ");
        lcd.print(senhaDigitada);
        Serial.print("Digitado: ");
        Serial.println(senhaDigitada);
      }
    }
    // Se for '#' -> apaga o último dígito (backspace)
    else if (tecla == '#') {
      if (senhaDigitada.length() > 0) {
        senhaDigitada.remove(senhaDigitada.length()-1);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Senha: ");
        lcd.print(senhaDigitada);
        Serial.print("Backspace: ");
        Serial.println(senhaDigitada);
      }
    }
    // Se for '*' -> confirma a senha digitada
    else if (tecla == '*') {
      lcd.clear();
      // Comparação da senha
      if (senhaDigitada == senhaCorreta) {
        // Senha correta
        lcd.setCursor(0,0);
        lcd.print("Acesso Permitido");
        digitalWrite(ledVerde, HIGH);
        Serial.println("Acesso Permitido");
        // Abre a porta (servo para 90°)
        servo.write(90);
        delay(tempoPortaAberta);
        // Fecha a porta após tempo estipulado
        servo.write(0);
        digitalWrite(ledVerde, LOW);
      } else {
        // Senha incorreta
        lcd.setCursor(0,0);
        lcd.print("Acesso Negado");
        digitalWrite(ledVermelho, HIGH);
        Serial.println("Acesso Negado");
        delay(tempoAcessoNegado);
        digitalWrite(ledVermelho, LOW);
      }
      // Reseta o sistema para nova tentativa
      resetSistema();
    }
  }
}