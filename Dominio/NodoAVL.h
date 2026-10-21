#pragma once
#include "Paciente.h"


class NodoAVL {
public:
    Paciente* paciente;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;

    explicit NodoAVL(Paciente* p) : paciente(p), izq(nullptr), der(nullptr), altura(1) {}
};
