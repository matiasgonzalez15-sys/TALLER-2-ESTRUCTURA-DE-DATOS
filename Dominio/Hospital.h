#include "NodeServicios.h"
#include "ServicioMedico.h"
#include "ColaPacientes.h"
#include "PilaHistorial.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
class Hospital {
private:
    NodeServicios* servicios;
    ColaPacientes* filaEspera;
    PilaHistorial* historial;
    ServicioMedico* crearServicioMedico(const string& nombre);
public:
    Hospital();

    void agregarPaciente(Paciente* p);
    bool existePaciente(const string& id);
    void crearPaciente(string linea);

    void añadirServicioMedico(ServicioMedico * servicio);

    void crearServicioMedico();

    void mostrarPacientes(); // ESTA FUNCION ES PARA MOSTRAR LOS PACIENTES Y SELECCIONAR CUANTOS QUIERE ATENDER
    ServicioMedico * buscarServicioMedico(const string & string);

    void atenderPacientes(int opcion); // AQUI YA LOS ATENDEMOS
    void mostrarHistorial();
    ~Hospital();
};