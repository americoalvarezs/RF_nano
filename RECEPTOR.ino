#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);

int value;
int operation;

void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setRADDR((byte *)"FGHIJ"); //configura la direccion del RECEPTOR (direccion propia) en el ejemplo FGHIJ
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;             //canal utilizado
  Mirf.config();
  Serial.println("Listening...");  //empieza a escuchar datos si es que llega alguno...
}

void loop()
{
  if (Mirf.dataReady()) { // si hay datos en la pila de entrada entra al IF
    Mirf.getData((byte *) &value);
    
    Serial.print("Got data: "); //Cuando se recibe dato, este se imprimen en el monitor serial por ejemplo
    Serial.println(value);
    
    operacion=(value+7)*2;  //el valor en este caso es numerico y se puede realizar operaciones matematicas
    Serial.println(operacion);
  }
}
