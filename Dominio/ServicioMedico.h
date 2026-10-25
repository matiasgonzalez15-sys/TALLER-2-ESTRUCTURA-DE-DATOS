#include "NodePacientes.h"
#include "ArbolAVL.h"
#include <iostream>
#pragma once

class ServicioMedico {
protected:
    string nombre;
     ArbolAVL* arbolPacientes;
public:

    ServicioMedico(string nombre) {
        this->nombre = nombre;
        this->arbolPacientes = new ArbolAVL();
    };
    string getNombre() const{
        return this->nombre;
    }
    virtual ~ServicioMedico() {
        delete arbolPacientes;
    }

    Paciente* buscarPorId(const string& id, string* ruta = nullptr) const {
        return arbolPacientes->buscarPorId(id, ruta);
    }

    Paciente* buscarPorNombre(const string& nombre, string* ruta = nullptr) const {
        return arbolPacientes->buscarPorNombre(nombre, ruta);
    }

    bool eliminarPaciente(const string& id) {
        return arbolPacientes->eliminar(id);
    }
    int total() const { return arbolPacientes->total(); }
    int altura() const { return arbolPacientes->altura(); }

    void mostrarTodoAVL() const {
        cout << "Total de pacientes: " << arbolPacientes->total() << endl;
        cout << "Altura del arbol: " << arbolPacientes->altura() << endl;
        cout << "Inorden:    "; arbolPacientes->mostrarInorden();
        cout << "Preorden:   "; arbolPacientes->mostrarPreorden();
        cout << "Postorden:  "; arbolPacientes->mostrarPostorden();
        cout << "\nFactores de balance:" << endl;
        arbolPacientes->mostrarBalances();
        cout << "\nForma del arbol (raiz a la izquierda):" << endl;
        arbolPacientes->mostrarArbol();
    }
    void mostrarPacientes() const {
        arbolPacientes->mostrarInorden();
    }

    virtual bool agregarPaciente(Paciente* p) {
        if (p == nullptr) {
            cout << "ERROR: paciente nulo" << endl;
            return false;
        }
        if (arbolPacientes == nullptr) {
            cout << "ERROR: el arbol de pacientes es nulo" << endl;
            return false;
        }
        bool resultado = arbolPacientes->insertar(p);
        return resultado;
    }
};
class Urgencia : public ServicioMedico {
public:
    Urgencia() : ServicioMedico("Urgencia") {};
};

class MedicinaGeneral : public ServicioMedico {
public:
    MedicinaGeneral() : ServicioMedico("MedicinaGeneral") {};
};

class Cardiologia : public ServicioMedico {
public:
    Cardiologia() : ServicioMedico("Cardiologia") {};
};

class Neurologia : public ServicioMedico {
public:
    Neurologia() : ServicioMedico("Neurologia") {};
};

class Traumatologia : public ServicioMedico {
public:
    Traumatologia() : ServicioMedico("Traumatologia") {};
};
class Cirugia : public ServicioMedico {
public:
    Cirugia() : ServicioMedico("Cirugia") {};
};
class Pediatria : public ServicioMedico {
public:
    Pediatria() : ServicioMedico("Pediatria") {};
};
class Hospitalizacion : public ServicioMedico {
public:
    Hospitalizacion() : ServicioMedico("Hospitalizacion") {};
};


