#pragma once
#include "NodePacientes.h"
#include <string>
using namespace std;
class ColaPacientes {
private:
    NodePacientes* cabeza;
    NodePacientes* cola;
    int tamano;

    public:
    ColaPacientes();
    void push(Paciente* p);
    Paciente* front();
    void pop();
    void clear();
    int size();
    bool empty();
    bool existe(const string& id);
    NodePacientes* getPacientes();

    ~ColaPacientes();
};
