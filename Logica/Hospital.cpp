#include "../Dominio/Hospital.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
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


bool Hospital::crearPaciente(string linea) { // creamos pacientes y se mandan a la fila de espera
    if(linea.empty()) return false;
    stringstream ss(linea);
    string id, nombre, edadString, tempStr, presionStr, dolorStr, tipoDolor, traumaStr, sintNeuStr, cirugiaStr,
            diasHospStr;

    if (!getline(ss, id, ';') || !getline(ss, nombre, ';') || !getline(ss, edadStr, ';') ||
        !getline(ss, tempStr, ';') || !getline(ss, presionStr, ';') || !getline(ss, dolorStr, ';') ||
        !getline(ss, tipoDolor, ';') || !getline(ss, traumaStr, ';') || !getline(ss, sintNeuStr, ';') ||
        !getline(ss, cirugiaStr, ';') || !getline(ss, diasStr, ';')) {
        cerr << "Linea invalida porque faltan atributos" << linea << endl;
        return false;
    }
    try{
        if (id.empty() || nombre.empty()) throw invalid_argument("ID/nombre vacio");
        int edad = stoi(edadStr);
        float temp = stof(tempStr);
        float presion = stof(presionStr);
        float dolor = stof(dolorStr);
        int dias = stoi(diasStr);    
        if (edad < 0 || edad > 120) throw invalid_argument("Edad fuera de rango (0-120)");
        if (temp < 30 || temp > 45) throw invalid_argument("Temperatura fuera de rango (30-45)");
        if (presion <= 0 || presion > 300) throw invalid_argument("Presion fuera de rango (1-300)");
        if (dolor < 0 || dolor > 10) throw invalid_argument("Dolor fuera de rango (0-10)");
        if (dias < 0) throw invalid_argument("DiasHospitalizacion negativo");
        if (tipoDolor != "pecho" && tipoDolor != "cabeza" && tipoDolor != "abdomen" &&
            tipoDolor != "extremidad" && tipoDolor != "otro")
            throw invalid_argument("Tipo de dolor no valido");
        if ((traumaStr != "0" && traumaStr != "1") ||
            (sintNeuStr != "0" && sintNeuStr != "1") ||
            (cirugiaStr != "0" && cirugiaStr != "1"))
            throw invalid_argument("Trauma/SintomasNeuro/Cirugia deben ser 0 o 1");
 
        if (existePaciente(id)) {
            cerr << "Paciente duplicado (ID " << id << ")" << endl;
            return false;
        }
        Paciente* paciente = new Paciente(id, nombre, edad, temp, presion, dolor, tipoDolor,
                                          traumaStr, sintNeuStr, cirugiaStr, dias);
        agregarPaciente(paciente);
        return true;
    } catch (const exception& e) {
        cerr << "Linea invalida (" << e.what() << "): " << linea << endl;
        return false;
    }       
        

    
    
}





ServicioMedico* Hospital::buscarServicioMedico(const string& nombre) { 
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
                cout << ""<< endl;
                cout << "=== ATENDIENDO PACIENTE ===" << endl;
                cout << "ID: " << p->getId() << endl;
                cout << "Nombre: " << p->getNombre() << endl;
                cout << "Edad: " << p->getEdad() << endl;
                cout << "Temperatura: " << p->getTemperatura() << endl;
                cout << "Presion: " << p->getPresionArterial() << endl;
                cout << "Dolor: " << p->getDolor() << endl;
                cout << "TipoDolor: " << p->getTipoDolor() << endl;
                cout << "Trauma: " << p->getTrauma() << endl;
                cout << "SintomasNeurologicos: " << p->getSintomasNeurologicos() << endl;
                cout << "RequiereCirugia: " << p->getRequiereCirugia() << endl;
                cout << "DiasHospitalizacion: " << p->getCantDiasHospitalizacion() << endl;
                cout << "Ruta: " << ruta << endl;
                cout << "Servicio asignado: " << nombreServicio << endl;
                cout << "Paciente insertado en el AVL de " << nombreServicio << "." << endl;
 
 
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
        cout << "5. Recorridos del arbol de decision" << endl;
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
        } 
         else if (op == 5) {
            mostrarArbolDecision();
        } else if (op != 0) {
            cout << "Opcion no valida." << endl;
        }
    }
}

void Hospital::mostrarArbolDecision(){
    arbol -> mostrarPreorden();
    arbol -> mostrarInorden();
    arbol -> mostrarPostorden();
}




Hospital::~Hospital() {
    NodeServicios* actualS= this-> servicios;
    while (actualS != nullptr) {
        NodeServicios* temp = actualS;
        actualS = actualS->getNext();
        delete temp;
    }
    delete this -> filaEspera;
    delete this -> arbol;
}

