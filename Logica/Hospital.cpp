#include "../Dominio\Hospital.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Hospital::Hospital() {
    this -> servicios = nullptr;
    this-> filaEspera = new ColaPacientes();

}

void Hospital::añadirServicioMedico(ServicioMedico* s) { // se agregan al nodo de los servicios
    NodeServicios* servicio = new NodeServicios(s);

    if (this -> servicios == nullptr) {
        this -> servicios = servicio;
    }
    else {
        NodeServicios* cursor = this -> servicios;
        while (cursor -> getNext() != nullptr) {
            cursor = cursor -> getNext();
        }
        cursor -> setNext(servicio);
    }
}

void Hospital::crearServicioMedico() { // tenemos que crear aqui los servicios medicos
    ServicioMedico* u = new Urgencia();
    añadirServicioMedico(u);
    ServicioMedico* mg = new MedicinaGeneral();
    añadirServicioMedico(mg);
    ServicioMedico* c = new Cardiologia();
    añadirServicioMedico(c);
    ServicioMedico* n = new Neurologia();
    añadirServicioMedico(n);
    ServicioMedico* t = new Traumatologia();
    añadirServicioMedico(t);
    ServicioMedico* cir = new Cirugia();
    añadirServicioMedico(cir);
    ServicioMedico* p = new Pediatria();
    añadirServicioMedico(p);
    ServicioMedico* hosp = new Hospitalizacion();
    añadirServicioMedico(hosp);
}

void Hospital::agregarPaciente(Paciente *p) { // se agrega el paciente a la cola
    if (!existePaciente(p->getId())) {
        filaEspera->push(p);
    } else {
        cout << p->getId() << " ya se encuentra en la fila" << endl;
    }
}


bool Hospital::existePaciente(const string &id) { // verificamos si el paciente ya existe
    if (filaEspera->existe(id)) {
        return true;
    }
    return false;
}

void Hospital::crearPaciente(string linea) { // creamos pacientes y se mandan a la fila de espera
    stringstream ss(linea);
    string id, nombre, edadString, tempStr, presionStr, dolorStr, tipoDolor, traumaStr, sintNeuStr, cirugiaStr,
            diasHospStr;
    getline(ss, id, ';');
    getline(ss, nombre, ';');
    getline(ss, edadString, ';');
    getline(ss, tempStr, ';');
    getline(ss, presionStr, ';');
    getline(ss, dolorStr, ';');
    getline(ss, tipoDolor, ';');
    getline(ss, traumaStr, ';');
    getline(ss, sintNeuStr, ';');
    getline(ss, cirugiaStr, ';');
    getline(ss, diasHospStr, ';');

    int edad = stoi(edadString);
    float temp = stof(tempStr);
    float presion = stof(presionStr);
    float dolor = stof(dolorStr);
    int diasHosp = stoi(diasHospStr);
    bool existeP = existePaciente(id);
    if (!existeP) {
        Paciente* paciente = new Paciente(id, nombre, edad, temp, presion, dolor, tipoDolor, traumaStr,
            sintNeuStr, cirugiaStr, diasHosp);
        agregarPaciente(paciente);
    }
}
void Hospital::mostrarPacientes() {

}
ServicioMedico* Hospital::buscarServicioMedico(const string & servicio) {

}
void Hospital::atenderPacientes(int opcion) {

}


Hospital::~Hospital() {
    NodeServicios* actualS= this-> servicios;
    while (actualS != nullptr) {
        NodeServicios* temp = actualS;
        actualS = actualS->getNext();
        delete temp;
    }
    delete this -> filaEspera;
}
