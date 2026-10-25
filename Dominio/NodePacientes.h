#pragma once
#include "Paciente.h"

class NodePacientes {
private:
    NodePacientes* next;
    Paciente* paciente;
public:
    NodePacientes(Paciente* p) {
        this->paciente = p;
        this-> next = nullptr;
    }
    Paciente* getPaciente() {
        return this->paciente;
    }
    void setNext(NodePacientes* siguiente) {
        this->next = siguiente;
    }
    NodePacientes* getNext() {
        return this->next;
    }

    ~NodePacientes() {
        this-> next = nullptr;
    }
};
