#pragma once
#include <iostream>
#include <string>
#include "NodeDecision.h"
#include "Paciente.h"
using namespace std;

class ArbolDecision {
private:
    NodeDecision* raiz;
    void liberarArbol(NodeDecision* nodo);
    string evaluar(NodeDecision* nodo, Paciente* p, string& ruta);
    void agregarPaso(string& ruta, const string& paso);
public:

    ArbolDecision();
    ~ArbolDecision();
    string determinarServicio(Paciente* p, string& ruta);



};
