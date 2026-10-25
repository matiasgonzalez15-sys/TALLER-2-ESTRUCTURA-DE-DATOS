
#include "../Dominio/ColaPacientes.h"
#include <string>
using namespace std;
ColaPacientes::ColaPacientes() {
    this-> cabeza = nullptr;
    this-> cola = nullptr;
    this-> tamano = 0;
}

int ColaPacientes::size() {
    return this-> tamano;
}
bool ColaPacientes::empty() {
    return this-> tamano == 0;
}
void ColaPacientes::push(Paciente* p){
    NodePacientes* nuevo = new NodePacientes(p);
    if (empty()) {
        this-> cabeza = nuevo;
        this-> cola = nuevo;
    }
    else {
        this-> cola ->setNext(nuevo);
        this-> cola = nuevo;
    }
    this->tamano++;
}
void ColaPacientes::pop() {
    if (empty()) return;
    NodePacientes* temp = this->cabeza;
    this-> cabeza = this-> cabeza -> getNext();
    if (cabeza == nullptr) {
        this-> cola = nullptr;
    }
    temp->setNext(nullptr);
    delete temp;
    this->tamano--;
}

Paciente *ColaPacientes::front() {
    if (empty()) return nullptr;
    return this-> cabeza->getPaciente();
}

void ColaPacientes::clear() {
    while (!empty()) {
        pop();
    }
}
bool ColaPacientes::existe(const string &id) {
    NodePacientes* cursor = this-> cabeza;
    while (cursor != nullptr) {
        if (cursor->getPaciente()->getId() == id) {
            return true;
        }
        cursor = cursor->getNext();
    }
    return false;
}

ColaPacientes::~ColaPacientes() {
    while(!empty()){
        delete front();
        pop();
    }
}