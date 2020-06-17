//Termocirculador SousVide simples com arduino uno e DS18B20

//Bibliotecas para utilização do sensor de temperatura, já incluidas na IDE do arduino 
//(Ferramentas/Gerenciar bibliotecas)
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Porta do sensor DS18B20
#define ONE_WIRE_BUS 3

//Porta do rele
#define RELAY_PIN 4

 
// Define uma instancia do oneWire para comunicacao com o sensor:
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

float tempMin=0;

 
void setup(void)
{
  //inicializando o rele, desligado quando porta está no estado HIGH
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  //inicializando comunicação serial
  Serial.begin(115200);
  
  //inicializando sensores
  sensors.begin();
  // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensor DS18B20...");
  Serial.print("Quantidade de sensores encontrados: ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensor(es).");
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Não foi encontrado um sensor !"); 
    // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();
  
  //lcd.begin(16, 2);

  
  //Realizando a leitura da temperatura desejada pelo usuario:
  Serial.println("Informe a temperatura desejada para iniciar: ");
  while(tempMin==0){
    if (Serial.available()>0){
    //recebendo temperatura informada pelo usuario, convertendo leitura do teclado para o tipo float
      tempMin=Serial.parseFloat();
    
    }
    
  }
  Serial.print("Temperatura configurada: ");
  Serial.println(tempMin);


  //Fim do setup
   
}
 
 
void loop()
{ 
  float temp = sensors.getTempC(sensor1);
  
  

  
  // Le a informacao do sensor
  sensors.requestTemperatures();
  
  // Verifica se a temperatura está abaixo da temperatura definida pelo usuario, aciona o aquecedor caso esteja abaixo do limite
  if (temp < tempMin)
  {
    aciona_aquecedor();
  }
  Serial.print("Temperatura atual: ");
  Serial.println(temp);
  Serial.print("Temperatura desejada: ");
  Serial.println(tempMin); 

  // Mostra dados no serial monitor
  //Serial.print("Temp C: ");
  //Serial.print(tempC);
  //Serial.print(" Min : ");
  //Serial.print(tempMin);
  //Serial.print(" Max : ");
  //Serial.println(tempMax);
   
  // Mostra dados no LCD  
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("Temp.:       ");
  //Simbolo grau
  //lcd.write(223);
  //lcd.print("C");
  //lcd.setCursor(7,0);
  //lcd.print(tempC);
  //lcd.setCursor(0,1);
 // lcd.print("L: ");
  //lcd.setCursor(3,1);
  //lcd.print(tempMin,1);
  //lcd.setCursor(8,1);
  //lcd.print("H: ");
  //lcd.setCursor(11,1);
  //lcd.print(tempMax,1);
  delay(1000);
}

void aciona_aquecedor(){
 
 //Acionando o aquecedor - ligado quando estado de RELAY_PIN=LOW 
 digitalWrite(RELAY_PIN, LOW);
 Serial.println("Aquecedor ligado");
 //Mantem o aquecedor ligado por 10s
 delay(5000);
 //Desligando o aquecedor - desligado quando estado de RELAY_PIN=HIGH
 digitalWrite(RELAY_PIN, HIGH);
 Serial.println("Aquecedor desligado");
 delay(5000);
 
}

void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
