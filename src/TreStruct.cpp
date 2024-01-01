#include "TreStruct.h"
#include "Arduino.h"

/***** Metodos publicos *****/

/*** Constructor***/
TreStruct::TreStruct(void)
{
  // nothing to do here, begin() does it all
}

/*** Crear una lista de usuarios ***/
bool TreStruct::begin(uint16_t numUsers)
{
  _usersUsed = 0;
  _errorFlag = false;
  _numUsers = numUsers;
  _usersList = (usuarios *)malloc(numUsers * sizeof(usuarios));

  // Si falla malloc() se genera un error
  if ((uint8_t)_usersList == NULL)
    return false;
  return true;
}

/*** Agregar usuarios a la lista ***/
void TreStruct::addUser(const char *userName, uint32_t userDni, uint8_t userHome,
             const char *userTag, bool userAcces, const char *timeStamp)
{
  addNewUser(userName, userDni, userHome, userTag, userAcces, timeStamp);
}

/*** Generar reporte completo ***/
// option = 0: todos los usuarios
// option = n: usuario en particular, donde n es el número de usuario
void TreStruct::fullReport(uint8_t option, char *output)
{
  userReports(option, output);
}

/*** Generar reporte minimo ***/
void TreStruct::minReport(char *output)
{
  uint8_t option = 99;
  userReports(option, output);
}

/***** Metodos privados *****/

/*** Agregar un nuevo usuario a la lista ***/
void TreStruct::addNewUser(const char *userName, uint32_t userDni, uint8_t userHome,
                const char *userTag, bool userAcces, const char *timeStamp)
{

  if (_usersUsed < _numUsers)
  {

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
  }
  else
  {
    _errorFlag = true;
  }
}

/*** Generar reportes de los usuarios ***/
void TreStruct::userReports(uint8_t option, char *output)
{

  size_t pos = 0;

  // ERROR: opcion no permitida
  if (option > _numUsers && option != 99)
  {
    pos += snprintf(output, BUFFER_SIZE, "Error: opcion no permitida \n\n");
  }
  // Ejecución normal
  else if (_usersUsed > 0)
  {

    // Cabecera del reporte
    pos += snprintf(output, BUFFER_SIZE, "Cantidad de usuarios: %d\n", _numUsers);
    pos += snprintf(output + pos, BUFFER_SIZE - pos, "Errores al agregar usuarios: %d\n", _errorFlag);
    pos += snprintf(output + pos, BUFFER_SIZE - pos, "--------------------------------\n");

    uint8_t i = (option == 0 || option == 99) ? 0 : option - 1;

    for (i; i < _numUsers; i++)
    {

      pos += snprintf(output + pos, BUFFER_SIZE - pos, "Usuario #%d: %s\n", i, _usersList[i].user_name);

      if (option != 99)
      {
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "DNI: %lu\n", _usersList[i].user_dni);
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "Departamento: %d\n", _usersList[i].user_home);
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "Tag ID: %s\n", _usersList[i].user_tag);
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "Permisos: %d\n", _usersList[i].user_access);
        pos += snprintf(output + pos, BUFFER_SIZE - pos, "Ultimo Acceso: %s\n\n", _usersList[i].user_timestamp);
      }

      if (option != 0 && option != 99)
        break;
    }
  }
  // ERROR: no se encuentran usuarios registrados
  else
  {
    pos += snprintf(output, BUFFER_SIZE, "No hay usuarios registrados \n\n");
  }

  // Agregar el carácter nulo al final del buffer de salida, aunque este lleno
  if (pos < BUFFER_SIZE)
  {
    output[pos] = '\0';
  }
  else
  {
    output[BUFFER_SIZE - 1] = '\0';
  }
}