/*
    TreStruct - Ejemplo de aplicacion

*/

#include "TreStruct.h"

TreStruct miStruct;
const int BUFFER_SIZE = 1024;

void setup() {

  Serial.begin(9600);

  // Iniciar cantidad de usuarios
  bool error = miStruct.begin(13);

  if (error == false) Serial.println("ERROR: asignación de memoria");

  // Agregar usuarios
  miStruct.addUser("Gabriel Batistuta", 30654321, 22, "E0A3B2C5", false, "20231215T083000");
  miStruct.addUser("Diego Maradona", 30123456, 10, "A1B2C3D4", true, "20231215T093000");
  miStruct.addUser("Lionel Messi", 32234567, 10, "N3O4P5Q6", true, "20231215T123000");
  miStruct.addUser("Cristiano Ronaldo", 32901234, 7, "R7S8T9U0", true, "20231215T133000");
  miStruct.addUser("Pele", 30876543, 10, "F5G6H7I8", true, "20231215T103000");
  miStruct.addUser("Zinedine Zidane", 31567890, 5, "J9K0L1M2", true, "20231215T113000");

  delay(500);

  // Imprimir reportes
  char informe[BUFFER_SIZE];

  // Reporte minimo de usuarios
  miStruct.minReport(informe);
  Serial.println(informe);

  // Reporte completo de usuarios
  miStruct.fullReport(0, informe);
  Serial.println(informe);
}

void loop() {

  /*** Función principal - Nada para hacer ***/
}