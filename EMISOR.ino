#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);

int value=0;

void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Establece tu propia dirección (dirección del EMISOR) usando 5 caracteres, en el ejemplo ABCDE
  Mirf.setRADDR((byte *)"ABCDE");
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;              //canal utilizado
  Mirf.config();
}

void loop()
{
  Mirf.setTADDR((byte *)"FGHIJ");           //direccion del emisor FGHIJ, esto depende del RECEPTOR
  
  if(value>50){
    value=0;
  }
  
  Mirf.send((byte *)&value);                //enviar valor numerico (cuenta del 0 al 50)
  Serial.print("Wait for sending.....");
  while (Mirf.isSending()) delay(1);        //Se queda en el bucle hasta que se envie el dato correctamente, no importa si lo recibe o no el RECEPTOR
  Serial.print("Send success:");
  Serial.println(value);
  delay(1000);
  value=value+1;                            //incrementa la cuenta de 1 en 1
}
