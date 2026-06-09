# 🛰️ OrbitWatch — Estação Terrestre de Monitoramento de Detritos Espaciais

> Solução de Edge Computing para rastreamento de lixo orbital e alertas de colisão em tempo real.

---

## 📋 Descrição do Projeto

O **OrbitWatch** é uma plataforma de monitoramento orbital desenvolvida como parte do projeto interdisciplinar da FIAP. A solução simula uma **estação terrestre de rastreamento** que detecta a aproximação de detritos espaciais a satélites ativos, calcula o nível de risco de colisão e emite alertas visuais e sonoros para o operador.

O módulo de Edge Computing representa o hardware embarcado da estação terrestre: sensores que capturam dados do ambiente orbital simulado, processamento local do risco e interface de alerta em tempo real — sem depender de um servidor central.

---

## 🎯 Objetivo da Solução

- Simular a detecção de objetos em órbita por meio de sensores analógicos
- Calcular o risco de colisão com base na intensidade do sinal captado e na sensibilidade configurada pelo operador
- Emitir alertas visuais (LEDs) e sonoros (buzzer) de acordo com o nível de risco
- Exibir a porcentagem de risco em tempo real no display LCD
- Demonstrar a aplicação de Edge Computing em infraestrutura espacial crítica

---

## 🔧 Componentes Utilizados

| Componente | Quantidade | Função no Projeto |
|---|---|---|
| Arduino Uno | 1 | Microcontrolador principal |
| Sensor LDR (fotoresistor) | 1 | Simula o telescópio/detector de passagem de objeto |
| Potenciômetro | 1 | Ajuste de sensibilidade do operador |
| LED Verde | 1 | Indicador de risco baixo (< 40%) |
| LED Amarelo | 1 | Indicador de risco médio (40–74%) |
| LED Vermelho | 1 | Indicador de risco alto (≥ 75%) |
| Buzzer | 1 | Alarme sonoro em risco crítico |
| Display LCD 16x2 (I2C) | 1 | Exibição da porcentagem de risco |
| Resistores 1kΩ | 3 | Proteção dos LEDs |
| Protoboard | 1 | Montagem do circuito |

**Biblioteca:** `LiquidCrystal_I2C`

---

## ⚙️ Explicação do Funcionamento

O sistema opera em loop contínuo com as seguintes etapas:

1. **Leitura do LDR (A0):** O sensor fotoresistor simula um telescópio captando a passagem de um objeto em órbita. Quanto maior a intensidade luminosa captada, maior o sinal analógico (0–1023), que é mapeado para uma escala de risco de 0 a 100%.

2. **Leitura do Potenciômetro (A1):** Representa a sensibilidade configurada pelo operador da estação. Seu valor é mapeado para um ajuste de 0 a 50 pontos, somado ao risco base — simulando que um operador mais alerta eleva o nível de atenção do sistema.

3. **Cálculo do Risco Final:**
   ```
   riscoFinal = map(LDR, 0, 1023, 0, 100) + map(POT, 0, 1023, 0, 50)
   riscoFinal = min(riscoFinal, 100)
   ```

4. **Acionamento dos alertas:**
   - `riscoFinal < 40%` → LED **verde** aceso, buzzer silencioso
   - `40% ≤ riscoFinal < 75%` → LED **amarelo** aceso, buzzer silencioso
   - `riscoFinal ≥ 75%` → LED **vermelho** aceso, buzzer ativo (1000 Hz)

5. **Display LCD:** Atualizado a cada 500ms exibindo `"Objeto detectado"` na linha 1 e `"Risco: XX%"` na linha 2.

6. **Monitor Serial:** Imprime os valores brutos do LDR, potenciômetro e risco calculado para depuração.

---

## 🔌 Estrutura do Circuito

```
Arduino Uno
├── A0  ──── LDR (saída analógica do sensor fotoresistor)
├── A1  ──── Potenciômetro (sinal)
├── A4  ──── LCD SDA (I2C)
├── A5  ──── LCD SCL (I2C)
├── D8  ──── Resistor 1kΩ ──── LED Verde (ânodo)
├── D9  ──── Resistor 1kΩ ──── LED Amarelo (ânodo)
├── D10 ──── Resistor 1kΩ ──── LED Vermelho (ânodo)
├── D11 ──── Buzzer (terminal +)
├── 5V  ──── VCC (LDR, Potenciômetro, LCD)
└── GND ──── GND (todos os componentes)
```

Os cátodos dos LEDs são conectados ao GND via protoboard. O LCD utiliza comunicação I2C no endereço `0x27`.

---

## 🚀 Instruções de Execução

### Simulação no Wokwi

1. Acesse o projeto diretamente pelo link:  
   **[https://wokwi.com/projects/465170239976778753](https://wokwi.com/projects/465170239976778753)**

2. Clique em **▶ Play** para iniciar a simulação

3. Interaja com o circuito:
   - **Arraste o controle do LDR** para simular a detecção de um objeto passando pelo telescópio
   - **Gire o potenciômetro** para ajustar a sensibilidade do operador
   - Observe os LEDs, o buzzer e o display LCD respondendo em tempo real

### Execução local (hardware físico)

1. Instale a IDE Arduino: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Instale a biblioteca `LiquidCrystal_I2C` via **Sketch → Incluir Biblioteca → Gerenciar Bibliotecas**
3. Conecte o Arduino ao computador via USB
4. Abra o arquivo `sketch.ino`
5. Selecione a placa **Arduino Uno** e a porta correta em **Ferramentas**
6. Clique em **Upload**
7. Monte o circuito conforme o diagrama acima
8. Abra o **Monitor Serial** (9600 baud) para acompanhar os valores em tempo real

---

## 📁 Estrutura do Repositório

```
orbitwatch-edge/
├── sketch.ino          # Código-fonte Arduino/C++
├── diagram.json        # Diagrama do circuito (Wokwi)
├── libraries.txt       # Bibliotecas utilizadas
├── wokwi-project.txt   # Link do projeto no simulador
└── README.md           # Documentação do projeto
```

---

## 👥 Integrantes do Grupo

| Nome | RM |
|---|---|
| João Victor Pereira Gimenes | 571662 |
| Juan Duarte | 570331 |
| Julio Cesar da Silva Cocco | 569463 |
| Rafael Boletini de Oliveira | 570219 |
| Victor Rossi Sales Zanandre | 573844 |

---

## 🌍 Conexão com ODS

- **ODS 9** — Indústria, Inovação e Infraestrutura: monitoramento da infraestrutura espacial crítica
- **ODS 13** — Ação Contra a Mudança Global do Clima: satélites são essenciais para monitoramento ambiental e climático

---

## 📎 Links

- 🔗 Simulação Wokwi: [https://wokwi.com/projects/465170239976778753](https://wokwi.com/projects/465170239976778753)

---

*Projeto desenvolvido para a disciplina de Edge Computing — FIAP 2026*
