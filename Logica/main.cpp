#include <iostream>
#include <fstream>
#include <string>
#include "../Dominio/Hospital.h"
using namespace std;
bool leerPacientes(Hospital* h) {
    ifstream arch("pacientes.txt");
    if (!arch.is_open()) {
        cerr<<"Error al abrir el archivo"<<endl;
        return false;
    }
    string linea;
    int cargados = 0;
    while (getline(arch,linea)) {
        if(h->crearPaciente(linea)) cargados++;
    }
    cout << "Cargados en total: "<< cargados << endl;
    return true;
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
                int cantidad;
                
                cout << "Cuantos pacientes quiere atender: ";
                cin >> cantidad;
                if (cin.fail()) {
                    cout<<"Opcion incorrecta"<<endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                h->atenderPacientes(cantidad);
                break;
            case 2:
                cin.ignore(1000, '\n');
                h->menuAVL();
                break;
            case 3:
                cin.ignore(1000, '\n');
                cout << "Indique el ID del paciente: ";
                getline(cin, id);
                if(!id.empty()){
                    h->buscarPaciente(id);   
                }
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
    if(leerPacientes(hospital)){
        menu(hospital);
    }
    


    delete hospital;
    return 0;
}
