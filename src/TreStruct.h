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

#ifndef TreStruct_h
#define TreStruct_h

#include "Arduino.h"

class TreStruct
{

public:
  /*** Constructor ***/
  TreStruct(void);

  /*** Crear una lista de usuarios ***/
  bool begin(uint16_t numUsers);

  /*** Agregar usuarios a la lista ***/
  void addUser(const char *userName, uint32_t userDni, uint8_t userHome,
               const char *userTag, bool userAcces, const char *timeStamp);

  /*** Generar reporte completo ***/
  void fullReport(uint8_t option, char *output);

  /*** Generar reporte minimo ***/
  void minReport(char *output);

private:
  struct usuarios
  {
    char user_name[20];      // Nombre de usuario
    char user_timestamp[16]; // Ultimo acceso
    char user_tag[10];       // Tag ID
    uint32_t user_dni;       // Numero de documento
    uint8_t user_home;       // Numero de departamento/casa
    bool user_access;        // Permisos de usuario
  };

  uint16_t _usersUsed;
  uint16_t _numUsers;
  bool _errorFlag;
  usuarios *_usersList;

  const int BUFFER_SIZE = 1024;

  /*** Agregar un nuevo usuario a la lista ***/
  void addNewUser(const char *userName, uint32_t userDni, uint8_t userHome,
                  const char *userTag, bool userAcces, const char *timeStamp);

  /*** Generar reportes de los usuarios ***/
  void userReports(uint8_t option, char *output);
};

#endif