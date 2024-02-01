# Biblioteca TreStruct

Primer experiencia en el proceso de creación de bibliotecas para Arduino. Se trata de una biblioteca para crear y manipular una estructura que almacena datos personales.

## Descripción del código

TreStruct permite almacenar usuarios y datos personales mediante una estructura de datos. La misma se aloja en la memoria dinámica mediante la función `void *malloc(size_t size)`. Puede aprender más sobre *malloc()* leyendo en [Wikipedia](https://es.wikipedia.org/wiki/Malloc) o [aquí](https://en.cppreference.com/w/c/memory/malloc).

Para copiar el contenido de un array en otro se utiliza la función `strncpy(destino, fuente, cantidad_a_copiar)`. Como *strncpy* no garantiza la copia del caracter nulo de fin de cadena `\0`, se recomienda agregarlo manualmente. Un poco más sobre *strncpy* en este [enlace](https://en.cppreference.com/w/cpp/string/byte/strncpy).

La función *snprintf()* se utilizar para almacenar un string con un tamaño especificado en un determinado formato. Además retorna el número de caracteres escritos (sin incluir el caracter nulo `\0`): `int snprintf(char *str, size_t size, const char *format, …)`, donde `*str` es un buffer, `size` es el numero maximo de bytes (caracteres) que seran escritos en el buffer. Más sobre *snprintf()* [aquí](https://cplusplus.com/reference/cstdio/snprintf/).

La biblioteca expone de manera publica los siguientes métodos:

- `TreStruct(void)` Constructor.
- `bool begin(uint16_t numUsers)` Crea una lista de usuarios.
- `void addUser(const char *userName, uint32_t userDni, uint8_t userHome, const char *userTag, bool userAcces, const char *timeStamp)` Agrega usuarios a la lista.
- `void fullReport(uint8_t option, char *output)` Genera un reporte completo.
- `void minReport(char *output)` Genera un reporte minimo.

## Licencia

Este trabajo está protegido por la **Licencia MIT**. Puedes acceder a la versión original de la licencia (en inglés) a través del archivo [LICENSE](./LICENSE) o en línea en [The MIT License (MIT)](https://mit-license.org/). También proporcionamos una traducción no oficial desde [Wikipedia](https://es.m.wikipedia.org/wiki/Licencia_MIT#La_licencia):

Copyright (c) 2024 Lucas Martín Treser

Por la presente se concede permiso, libre de cargos, a cualquier persona que obtenga una copia de este software y de los archivos de documentación asociados (el "Software"), a utilizar el Software sin restricción, incluyendo sin limitación los derechos a usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar, y/o vender copias del Software, y a permitir a las personas a las que se les proporcione el Software a hacer lo mismo, sujeto a las siguientes condiciones:

El aviso de copyright anterior y este aviso de permiso se incluirán en todas las copias o partes sustanciales del Software.

EL SOFTWARE SE PROPORCIONA "COMO ESTÁ", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A GARANTÍAS DE COMERCIALIZACIÓN, IDONEIDAD PARA UN PROPÓSITO PARTICULAR E INCUMPLIMIENTO. EN NINGÚN CASO LOS AUTORES O PROPIETARIOS DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGUNA RECLAMACIÓN, DAÑOS U OTRAS RESPONSABILIDADES, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O CUALQUIER OTRO MOTIVO, DERIVADAS DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O SU USO U OTRO TIPO DE ACCIONES EN EL SOFTWARE.
