#include <OneWire.h>
#include <DallasTemperature.h>

// Declarando objetos dos sensores
OneWire temperatura(2);
DallasTemperature sensors(&temperatura);

// Esta função calcula o NTU da água através de uma função de segundo grau,
// limitando os valores de NTU quando o nível de tensão na porta analógica
// for estiver fora do intervalo estabelecido
double readNTU(float voltage) {
  if (voltage < 2.5)
    return 3000;
  else if (voltage > 4.2)
    return 0;
  else
  {
    double NTU =  -1120.4 * voltage * voltage + 5742.3 * voltage - 4353.8;
    return NTU;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {

  float voltage = ((float)analogRead(A0) / 1023) * 5;
  double NTU = readNTU(voltage);
  float temp = 0;

  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);

  // exibição dos valores no monitor serial
  Serial.print("Valor temperatura: ");
  Serial.print(temp);
  Serial.print("  Valor NTU: ");
  Serial.print(NTU);
  Serial.print("  tensão: ");
  Serial.println(voltage);
  delay(700);
}
