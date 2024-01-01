/* 
    Control de acceso - Primer prototipo
    
    Permite almacenar usuarios y datos personales mediante una estructura de datos. 
    La misma se aloja en la memoria dinámica mediante la función malloc(): 
    void *malloc(size_t size).

    https://es.wikipedia.org/wiki/Malloc
    https://en.cppreference.com/w/c/memory/malloc

    Para copiar el contenido de un array en otro se utiliza la función strncpy: 
    strncpy(destino, fuente, cantidad_a_copiar). 
    
    No esta garantizada la copia del caracter nulo de fin de cadena (\0), por lo 
    que se recomienda agregarlo manualmente.

    https://en.cppreference.com/w/cpp/string/byte/strncpy

    La función snprintf() se utilizar para almacenar un string con un tamaño 
    especificado en un determinado formato. Además retorna el número de caracteres 
    escritos (sin incluir el caracter nulo \0): 
    int snprintf(char *str, size_t size, const char *format, …) 
    donde *str es un buffer, size es el numero maximo de bytes (caracteres) que 
    seran escritos en el buffer.

    https://cplusplus.com/reference/cstdio/snprintf/


    13 de diciembre de 2023
    Lucas Martin Treser
*/

/*** Variables privadas ***/

struct usuarios {
  char user_name[20];       // Nombre de usuario
  char user_timestamp[16];  // Ultimo acceso
  char user_tag[10];        // Tag ID
  uint32_t user_dni;        // Numero de documento
  uint8_t user_home;        // Numero de departamento/casa
  bool user_access;         // Permisos de usuario
};
uint16_t _usersUsed;
uint16_t _numUsers;
bool _errorFlag;
usuarios* _usersList;

/*** Constantes privadas ***/

const int BUFFER_SIZE = 1024;

void setup() {

  Serial.begin(9600);

  // Iniciar cantidad de usuarios
  bool error = begin(13);
  if (error == false) Serial.println("ERROR: asignación de memoria");

  // Agregar usuarios
  addUser("Gabriel Batistuta", 30654321, 22, "E0A3B2C5", false, "20231215T083000");
  addUser("Diego Maradona", 30123456, 10, "A1B2C3D4", true, "20231215T093000");
  addUser("Lionel Messi", 32234567, 10, "N3O4P5Q6", true, "20231215T123000");
  addUser("Cristiano Ronaldo", 32901234, 7, "R7S8T9U0", true, "20231215T133000");
  addUser("Pele", 30876543, 10, "F5G6H7I8", true, "20231215T103000");
  addUser("Zinedine Zidane", 31567890, 5, "J9K0L1M2", true, "20231215T113000");

  delay(500);

  // Imprimir reportes
  char informe[BUFFER_SIZE];

  // Reporte minimo de usuarios
  minReport(informe);
  Serial.println(informe);

  // Reporte completo de usuarios
  fullReport(0, informe);
  Serial.println(informe);
}

void loop() {

  /*** Función principal - Nada para hacer ***/
}

/***** Metodos publicos *****/

/*** Crear una lista de usuarios ***/
bool begin(uint16_t numUsers) {
  _usersUsed = 0;
  _errorFlag = false;
  _numUsers = numUsers;
  _usersList = (usuarios*)malloc(numUsers * sizeof(usuarios));

  // Si falla malloc() se genera un error
  if ((uint8_t)_usersList == NULL) return false;
  return true;
}

/*** Agregar usuarios a la lista ***/
void addUser(const char* userName, uint32_t userDni, uint8_t userHome,
             const char* userTag, bool userAcces, const char* timeStamp) {
  addNewUser(userName, userDni, userHome, userTag, userAcces, timeStamp);
}

/*** Generar reporte completo ***/
// option = 0: todos los usuarios
// option = n: usuario en particular, donde n es el número de usuario
void fullReport(uint8_t option, char* output) {
  userReports(option, output);
}

/*** Generar reporte minimo ***/
void minReport(char* output) {
  uint8_t option = 99;
  userReports(option, output);
}

/***** Metodos privados *****/

/*** Agregar un nuevo usuario a la lista ***/
void addNewUser(const char* userName, uint32_t userDni, uint8_t userHome,
                const char* userTag, bool userAcces, const char* timeStamp) {

  if (_usersUsed < _numUsers) {

    // Copiar los datos recibidos desde la funcion a la estructura destino
    strncpy(_usersList[_usersUsed].user_name, userName, (sizeof(_usersList[_usersUsed].user_name) - 1));
    strncpy(_usersList[_usersUsed].user_tag, userTag, (sizeof(_usersList[_usersUsed].user_tag) - 1));
    strncpy(_usersList[_usersUsed].user_timestamp, timeStamp, (sizeof(_usersList[_usersUsed].user_timestamp) - 1));

    // Asegurarse de que las cadenas estén terminadas en null
    _usersList[_usersUsed].user_name[sizeof(_usersList[_usersUsed].user_name) - 1] = '\0';
    _usersList[_usersUsed].user_tag[sizeof(_usersList[_usersUsed].user_tag) - 1] = '\0';
    _usersList[_usersUsed].user_timestamp[sizeof(_usersList[_usersUsed].user_timestamp) - 1] = '\0';

    _usersList[_usersUsed].user_dni = userDni;
    _usersList[_usersUsed].user_home = userHome;
    _usersList[_usersUsed].user_access = userAcces;

    _usersUsed++;
  } else {
    _errorFlag = true;
  }
}

/*** Generar reportes de los usuarios ***/
void userReports(uint8_t option, char* output) {

  size_t pos = 0;

  // ERROR: opcion no permitida
  if (option > _numUsers && option != 99) {
    pos += snprintf(output, BUFFER_SIZE, "Error: opcion no permitida \n\n");
  }
  // Ejecución normal
  else if (_usersUsed > 0) {

    // Cabecera del reporte
    pos += snprintf(output, BUFFER_SIZE, "Cantidad de usuarios: %d\n", _numUsers);
    pos += snprintf(output + pos, BUFFER_SIZE - pos, "Errores al agregar usuarios: %d\n", _errorFlag);
    pos += snprintf(output + pos, BUFFER_SIZE - pos, "--------------------------------\n");

    uint8_t i = (option == 0 || option == 99) ? 0 : option - 1;
    
    for (i; i < _numUsers; i++) {

      pos += snprintf(output + pos, BUFFER_SIZE - pos, "Usuario #%d: %s\n", i, _usersList[i].user_name);
      
      if (option != 99) {
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "DNI: %lu\n", _usersList[i].user_dni);
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "Departamento: %d\n", _usersList[i].user_home);
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "Tag ID: %s\n", _usersList[i].user_tag);
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "Permisos: %d\n", _usersList[i].user_access);
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "Ultimo Acceso: %s\n\n", _usersList[i].user_timestamp);
      }

      if (option != 0 && option != 99) break;
    }
  }
  // ERROR: no se encuentran usuarios registrados
  else {
    pos += snprintf(output, BUFFER_SIZE, "No hay usuarios registrados \n\n");
  }

  // Agregar el carácter nulo al final del buffer de salida, aunque este lleno
  if (pos < BUFFER_SIZE) {
    output[pos] = '\0';
  } else {
    output[BUFFER_SIZE - 1] = '\0';
  }
}