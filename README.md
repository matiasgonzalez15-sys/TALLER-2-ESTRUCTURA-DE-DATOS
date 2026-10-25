# Taller 2 - Estructura de Datos
## Descripción
El proyecto consiste en un sistema de gestión hospitalaria desarrollado en C++. Permite cargar pacientes desde un archivo de texto, procesarlos mediante una cola, clasificarlos utilizando un árbol de decisión y almacenarlos en el árbol AVL correspondiente al servicio médico asignado.
## Servicios médicos
El sistema considera los siguientes servicios:
- Urgencias
- Medicina General
- Cardiología
- Neurología
- Traumatología
- Cirugía
- Pediatría
- Hospitalización
## Estructuras de datos utilizadas
**Cola de pacientes:** permite procesar a los pacientes respetando el orden de llegada mediante el criterio FIFO.
**Árbol de decisión:** evalúa los atributos de cada paciente para determinar el servicio médico al que será derivado.
**Árboles AVL:** cada servicio cuenta con un árbol AVL para almacenar y administrar sus pacientes. Se consideran operaciones de inserción, búsqueda, eliminación, recorridos y balanceo.
## Árbol de decisión

El árbol de decisión es un árbol binario implementado manualmente con nodos y punteros. Cada nodo interno contiene una pregunta sobre un atributo del paciente: si la respuesta es afirmativa se continúa por el hijo izquierdo, y si es negativa por el hijo derecho. Las hojas del árbol corresponden a los ocho servicios del hospital, y la ruta seguida por cada paciente se muestra por pantalla al atenderlo.

La evaluación comienza en la raíz con la pregunta de si el paciente es pediátrico, es decir, si su edad es menor a 15 años. Elegimos este atributo como raíz porque es el filtro más general: los menores de edad se atienden en servicios distintos a los de los adultos. Si el paciente es pediátrico, se revisan los días de hospitalización estimados: si son mayores a 0 el paciente se deriva a Hospitalización, y si no, a Pediatría.

Si el paciente tiene 15 años o más, se evalúa primero si presenta una urgencia vital, que definimos como un dolor mayor o igual a 9 o una temperatura mayor o igual a 39.5. Esta pregunta va antes que cualquier especialidad porque una urgencia debe atenderse de inmediato, y en ese caso el paciente se deriva a Urgencia. Si no hay urgencia, se revisa si requiere cirugía, caso en el que se deriva a Cirugía. Luego se evalúa si es un caso cardiológico, lo que ocurre cuando el tipo de dolor es de pecho o la presión arterial es mayor a 140, y en ese caso va a Cardiología. Después se revisa si el paciente presenta trauma, y de ser así se deriva a Traumatología. Finalmente se evalúa si tiene síntomas neurológicos, que lo derivan a Neurología, y si no cumple ninguna de las condiciones anteriores se asigna a Medicina General, que cumple el rol de servicio de atención inicial.

En total el árbol utiliza nueve atributos del paciente (edad, días de hospitalización, dolor, temperatura, requiere cirugía, tipo de dolor, presión arterial, trauma y síntomas neurológicos), por lo que supera el mínimo de cuatro exigido, y existe al menos una ruta válida hacia cada uno de los ocho servicios.

Los casos límite están definidos de forma exacta. Una edad de 15 años ya se considera adulta, un dolor de 9 o una temperatura de 39.5 ya se consideran urgencia, y una presión de 140 exactos no se considera cardiológica, ya que se exige que sea mayor. Cuando un paciente cumple varias condiciones a la vez, se respeta el orden del árbol y se toma la primera que se cumple, de modo que, por ejemplo, un paciente con dolor de pecho y dolor 9 es derivado a Urgencia y no a Cardiología.

Los datos inválidos se controlan al leer el archivo. Si una línea tiene campos faltantes, valores no numéricos donde corresponde, valores fuera de rango, un tipo de dolor desconocido o un ID repetido, la línea se rechaza, se informa el error por pantalla y el programa continúa con las demás líneas. Las líneas en blanco se ignoran. Si el árbol recibe un paciente nulo, es decir, con datos insuficientes, el paciente se deriva a Medicina General por ser el servicio de evaluación inicial.

El árbol de decisión puede recorrerse en preorden, inorden y postorden desde el menú, en la opción Ver departamentos y luego la opción de recorridos del árbol de decisión.

## Archivo de pacientes
Los pacientes se cargan desde `pacientes.txt`, que contiene los datos necesarios para realizar la clasificación. Cada registro incluye ID, nombre, edad, temperatura, presión arterial, nivel de dolor, tipo de dolor, traumatismo, síntomas neurológicos, requerimiento de cirugía y días de hospitalización. Los campos están separados por el delimitador utilizado por el programa, por lo que se debe respetar el formato establecido para la lectura de los datos.
## Compilación y ejecución

### Requisitos
- Compilador de C++ compatible con el estándar utilizado por el proyecto.
- CMake.
- Git (opcional, para clonar el repositorio).

### Windows (VS Code)
1. Instalar un compilador de C++, por ejemplo GCC mediante MSYS2.
2. Instalar CMake y agregarlo al `PATH` si es necesario.
3. Abrir una terminal en la carpeta principal del proyecto, donde se encuentra `CMakeLists.txt`.
4. Ejecutar los siguientes comandos:

```bash
cmake -S . -B build
cmake --build build
```

5. Ejecutar el archivo `.exe` generado dentro de la carpeta `build`. Su ubicación depende de la configuración de CMake.

### Linux
Desde la carpeta principal del proyecto, ejecutar:

```bash
cmake -S . -B build
cmake --build build
```

Después, ejecutar el archivo generado dentro de la carpeta `build`.

También se puede compilar directamente con g++, desde la carpeta principal del proyecto:

```bash
g++ -std=c++17 -Wall -o hospital Logica/*.cpp
./hospital
```

Después, ejecutar el archivo generado dentro de la carpeta `build`.

### Archivo de entrada
El programa utiliza `pacientes.txt` para cargar los pacientes. Asegurarse de que el archivo se encuentre en la ruta desde la cual el programa espera leerlo antes de ejecutar el sistema.
### Compilar con CMake
Desde la carpeta principal del proyecto, ejecutar:
```bash
cmake -S . -B build
cmake --build build
```
Una vez terminada la compilación, ejecutar el programa generado dentro de la carpeta `build`. La ubicación del ejecutable depende del sistema operativo y de la configuración de CMake.
## Funcionamiento del programa

Al iniciar, el programa lee `pacientes.txt` y encola a los pacientes en orden de llegada. Menú principal:

1. **Atender pacientes:** se indica cuántos atender. Por cada uno se retira de la cola, se evalúa en el árbol de decisión, se muestra la ruta seguida y se inserta en el AVL del servicio asignado.
2. **Ver departamento:** abre una consola con el estado de todos los departamentos, el detalle de un departamento (recorridos inorden, preorden y postorden, altura, factor de balance y forma del árbol), búsqueda de pacientes, eliminación por ID y recorridos del árbol de decisión.
3. **Buscar paciente:** busca por ID o nombre en los AVL de todos los servicios y muestra la ruta de búsqueda.
4. **Salir.**

Cada AVL usa el ID como clave y mantiene el balance con rotaciones simples (izquierda y derecha) y dobles (izquierda-derecha y derecha-izquierda).

## Casos de prueba

Con el `pacientes.txt` incluido, la clasificación esperada es:

| ID | Paciente | Servicio |
|----|----------|----------|
| 001 | Juan Perez | Medicina General |
| 002 | Maria Gomez | Pediatría |
| 003 | Carlos Ruiz | Urgencia |
| 004 | Ana Torres | Traumatología |
| 005 | Pedro Soto | Cirugía |
| 006 | Sofia Morales | Traumatología |
| 007 | Luis Rojas | Medicina General |
| 008 | Rosa Diaz | Hospitalización |
| 009 | Mario Vega | Cardiología |
| 010 | Elena Paz | Neurología |
| 011 | Paula Mena | Medicina General |
| 012 | Jorge Silva | Medicina General |

Los IDs 001, 007, 011 y 012 llegan en orden creciente a Medicina General, lo que obliga al AVL a rotar.
## Integrantes

| Nombre completo | RUT | Usuario de GitHub | Carrera | Paralelo |
|---|---|---|---|---|
| Maximiliano Edhin Abd-El-Kader Góngora | 22.128.215-9 | [@YovngKxder](https://github.com/YovngKxder) | Ingeniería Civil en Computación e Informática | C2 |
| Fernando Antonio Herrera Castillo | 22.057.550-0 | [@Feersito123](https://github.com/Feersito123) | Ingeniería Civil en Computación e Informática | C1 |
| Matías Ignacio González Gómez | 22.350.340-3 | [@matiasgonzalez15-sys](https://github.com/matiasgonzalez15-sys) | Ingeniería Civil en Computación e Informática | C2 |
