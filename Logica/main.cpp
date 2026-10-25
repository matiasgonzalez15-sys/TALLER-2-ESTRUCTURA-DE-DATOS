#include <iostream>
#include <fstream>
#include <string>
#include "../Dominio/Hospital.h"
using namespace std;
void leerPacientes(Hospital* h) {
    ifstream arch("pacientes.txt");
    if (!arch.is_open()) {
        cerr<<"Error al abrir el archivo"<<endl;
        return;
    }
    string linea;
    while (getline(arch,linea)) {
        h->crearPaciente(linea);
    }
}


void menu(Hospital* h) {
    int opcion = 0;
    string id;
    while (opcion != 4) {
        cout<<"=== HOSPITAL MARMAJA ===" << endl;
        cout<<"1. Atender pacientes"<<endl;
        cout<<"2. Ver departamento"<<endl;
        cout<<"3. Buscar paciente por su ID"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"Ingresar opcion: " << endl;
        cin>>opcion;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        switch (opcion) {
            case 1:
                int opcion;
                
                cout << "Cuantos pacientes quiere atender: ";
                cin >> opcion;
                if (cin.fail()) {
                    cout<<"Opcion incorrecta"<<endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                h->atenderPacientes(opcion);
                break;
            case 2:
                cin.ignore(1000, '\n');
                h->menuAVL();
                break;
            case 3:
                h->buscarPaciente(id);
                break;
            case 4:
                cout << "Adios... :D" << endl;
                break;
            default:
                cout << "Opcion no valida!" << endl;
                break;
        }
    }
}

int main() {
    Hospital* hospital = new Hospital();
    leerPacientes(hospital);
    menu(hospital);


    delete hospital;
    return 0;
}
