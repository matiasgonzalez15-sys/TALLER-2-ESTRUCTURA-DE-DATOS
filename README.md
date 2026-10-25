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
## Criterios de clasificación
El árbol de decisión utiliza los datos de cada paciente para determinar su derivación. Las reglas se evalúan según el orden definido en la implementación:
1. Los pacientes menores de 14 años se derivan a Pediatría.
2. Los pacientes con traumatismos se derivan a Cirugía si requieren una operación; de lo contrario, a Traumatología.
3. Los pacientes con síntomas neurológicos se derivan a Neurología.
4. Los pacientes con dolor de pecho se derivan a Cardiología.
5. Los pacientes con temperatura igual o superior a 38,5 °C o nivel de dolor igual o superior a 8 se derivan a Urgencias.
6. Los pacientes que requieren dos o más días de hospitalización se derivan a Hospitalización.
7. Si no se cumple ninguna de las condiciones anteriores, el paciente se deriva a Medicina General.
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

### Archivo de entrada
El programa utiliza `pacientes.txt` para cargar los pacientes. Asegurarse de que el archivo se encuentre en la ruta desde la cual el programa espera leerlo antes de ejecutar el sistema.
### Compilar con CMake
Desde la carpeta principal del proyecto, ejecutar:
```bash
cmake -S . -B build
cmake --build build
```
Una vez terminada la compilación, ejecutar el programa generado dentro de la carpeta `build`. La ubicación del ejecutable depende del sistema operativo y de la configuración de CMake.
## Integrantes

| Nombre completo | RUT | Usuario de GitHub | Carrera | Paralelo |
|---|---|---|---|---|
| Maximiliano Edhin Abd-El-Kader Góngora | 22.128.215-9 | [@YovngKxder](https://github.com/YovngKxder) | Ingeniería Civil en Computación e Informática | C2 |
| Fernando Antonio Herrera Castillo | 22.057.550-0 | [@Feersito123](https://github.com/Feersito123) | Ingeniería Civil en Computación e Informática | C1 |
| Matías Ignacio González Gómez | 22.350.340-3 | [@matiasgonzalez15-sys](https://github.com/matiasgonzalez15-sys) | Ingeniería Civil en Computación e Informática | C2 |
