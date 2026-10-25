#pragma once
#include "ArbolDecision.h"
#include "Paciente.h"
#include "NodeServicios.h"
#include "ServicioMedico.h"
#include "ColaPacientes.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
class Hospital {
private:
    NodeServicios* servicios;
    ColaPacientes* filaEspera;
    ArbolDecision* arbol;
public:
    Hospital();
    ServicioMedico* buscarServicioMedico(const string& nombre);
    void agregarPaciente(Paciente* p);
    bool existePaciente(const string& id);
    bool crearPaciente(string linea);
    void añadirServicioMedico(ServicioMedico * servicio);
    void crearServicioMedico();
    void verDepartamento();
    void BuscarPorId(const string& id);


    void menuAVL();
    void mostrarArbolDecision();
    void buscarPaciente(const string& entrada);
    ServicioMedico* elegirServicio();



    void atenderPacientes(int opcion); // AQUI YA LOS ATENDEMOS
    ~Hospital();
};
