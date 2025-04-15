Atividade proposta:

Você foi contratado para desenvolver um protótipo de  para um laboratório de IoT. O sistema deve:

1 - Ler uma senha digitada em um .
2 - Mostrar o feedback no .
3 - Controlar uma "porta" (simulada por um ) e  (verde/vermelho) para indicar acesso liberado ou negado.

  Monte o circuito no Wokwi com:
  ESP32 + Teclado Matricial + LCD I2C + Servo Motor + 2 LEDs.

Programe o ESP32 para:
  Exibir no LCD:  ao iniciar.
  Aceitar senhas de até 8 dígitos (usando teclas numéricas).
  Tecla  como  para confirmar a senha.
  Tecla  como  para apagar dígitos.
  Comparar a senha digitada com a senha padrão .
  Se correta:
  Mover o servo para 90° (porta aberta).
  Acender LED verde + LCD: .
  Manter a porta aberta por  antes de fechar.

Se incorreta:
  Acender LED vermelho + LCD:  por , depois voltar ao estado inicial.
  Use a biblioteca  (não a padrão Servo.h).
  Pinos sugeridos:
  LCD: SDA=21, SCL=23.
  Teclado: Linhas=15,2,4,16 / Colunas=17,5,18,19.
  Servo=14, LED_Verde=12, LED_Vermelho=13.
  Link do projeto no Wokwi + código (.ino).
  Vídeo ou relatório (PDF) com explicações.
