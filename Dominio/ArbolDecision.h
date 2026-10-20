#include <iostream>
#include <string>
#include "NodeDecision.h"
#include "Paciente.h"
using namespace std;

class ArbolDecision {
private:
    NodeDecision* raiz;
    void liberarArbol(NodeDecision* nodo);
    string evaluar(NodeDecision* nodo, Paciente* p);
public:

    ArbolDecision();
    string determinarServicio(Paciente* p);




};