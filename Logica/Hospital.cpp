#include "../Dominio\Hospital.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Hospital::Hospital() {
    this -> servicios = nullptr;
    this-> filaEspera = new ColaPacientes();
    this->arbol = new ArbolDecision();
    crearServicioMedico();
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





ServicioMedico* Hospital::buscarServicioMedico(const string& nombre) { //gepeteado
    NodeServicios* cursor = servicios;

    while (cursor != nullptr) {
        ServicioMedico* servicio = cursor->getServicio();

        if (servicio != nullptr &&
            servicio->getNombre() == nombre) {
            return servicio;
            }

        cursor = cursor->getNext();
    }

    return nullptr;
}


void Hospital::atenderPacientes(int opcion) {
    int atendidos = 0;

    while (atendidos < opcion && !filaEspera->empty()) {
        Paciente* p = filaEspera->front();
        if (p == nullptr) { return; }
        filaEspera->pop();
        string ruta;
        string nombreServicio = arbol->determinarServicio(p,ruta);

        ServicioMedico* servicioDestino = buscarServicioMedico(nombreServicio);
        if (servicioDestino != nullptr) {
            if (servicioDestino->agregarPaciente(p)) {
                cout << "ID: " << p->getId() << endl;
                cout << "Nombre: " << p->getNombre() << endl;
                cout << "Edad: " << p->getEdad() << endl;
                cout << "Ruta: " << ruta << endl;
                cout << "Servicio asignado: " << nombreServicio << endl;


                atendidos++;
            } else {

                delete p;
                cout << "No se pudo registrar al paciente." << endl;
            }
        } else {
            cout << "Error interno: Servicio '" << nombreServicio << "' no encontrado." << endl;
            delete p;
        }
    }

    cout << "\nSe atendieron " << atendidos << " pacientes de la fila." << endl;
}



ServicioMedico* Hospital::elegirServicio() {
    NodeServicios* cursor = servicios;
    int n = 1;
    while (cursor != nullptr) {
        cout << n << ". " << cursor->getServicio()->getNombre()
             << " (" << cursor->getServicio()->total() << " pacientes)" << endl;
        cursor = cursor->getNext();
        n++;
    }
    cout << "Seleccione el departamento: ";
    string linea;
    getline(cin, linea);
    int opcion;
    try { opcion = stoi(linea); }
    catch (...) { cout << "Entrada invalida." << endl; return nullptr; }
    if (opcion < 1 || opcion >= n) { cout << "Opcion invalida." << endl; return nullptr; }

    cursor = servicios;
    for (int i = 1; i < opcion; i++) cursor = cursor->getNext();
    return cursor->getServicio();
}

void Hospital::buscarPaciente(const string& entrada) {
    cout << "Buscando en los AVL..." << endl;
    for (NodeServicios* c = servicios; c != nullptr; c = c->getNext()) {
        ServicioMedico* s = c->getServicio();
        string ruta;
        Paciente* p = s->buscarPorId(entrada, &ruta);
        if (p == nullptr) {
            ruta.clear();
            p = s->buscarPorNombre(entrada, &ruta);
        }
        if (p != nullptr) {
            cout << "\nPaciente encontrado:\n-------" << endl;
            cout << "ID: " << p->getId() << endl;
            cout << "Nombre: " << p->getNombre() << endl;
            cout << "Edad: " << p->getEdad() << endl;
            cout << "Departamento: " << s->getNombre() << endl;
            cout << "T: " << p->getTemperatura() << " | D: " << p->getDolor()
                 << " | TD: " << p->getTipoDolor()
                 << " | Trauma: " << (p->getTrauma() ? "Si" : "No")
                 << " | SN: " << (p->getSintomasNeurologicos() ? "Si" : "No")
                 << " | RC: " << (p->getRequiereCirugia() ? "Si" : "No")
                 << " | DH: " << p->getCantDiasHospitalizacion() << endl;
            cout << "-------\nRuta de busqueda: " << ruta << endl;
            return;
        }
    }
    cout << "Paciente no encontrado." << endl;
}

void Hospital::menuAVL() {
    string linea;
    int op = -1;
    while (op != 0) {
        cout << "\n=== CONSOLA AVL ===" << endl;
        cout << "1. Estado general de todos los departamentos" << endl;
        cout << "2. Ver un departamento en detalle (recorridos, altura, balances, arbol)" << endl;
        cout << "3. Buscar paciente por ID o nombre" << endl;
        cout << "4. Eliminar paciente por ID" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione: ";
        getline(cin, linea);
        try { op = stoi(linea); } catch (...) { op = -1; }

        if (op == 1) {
            cout << "\n=== ESTADO DE LOS DEPARTAMENTOS ===" << endl;
            for (NodeServicios* c = servicios; c != nullptr; c = c->getNext()) {
                ServicioMedico* s = c->getServicio();
                cout << "\n" << s->getNombre() << " | altura: " << s->altura()
                     << " | total: " << s->total() << endl;
                cout << "  Pacientes: ";
                s->mostrarPacientes();
            }
        } else if (op == 2) {
            ServicioMedico* s = elegirServicio();
            if (s != nullptr) {
                cout << "\n--- " << s->getNombre() << " ---" << endl;
                s->mostrarTodoAVL();
            }
        } else if (op == 3) {
            cout << "Indique el ID o Nombre del paciente: ";
            getline(cin, linea);
            if (!linea.empty()) buscarPaciente(linea);
        } else if (op == 4) {
            ServicioMedico* s = elegirServicio();
            if (s != nullptr) {
                cout << "ID a eliminar: ";
                getline(cin, linea);
                if (s->eliminarPaciente(linea))
                    cout << "Paciente eliminado. Arbol rebalanceado." << endl;
                else
                    cout << "No existe ese ID en el departamento." << endl;
            }
        } else if (op != 0) {
            cout << "Opcion no valida." << endl;
        }
    }
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

