#include "../Dominio/ArbolDecision.h"
#include <string>
using namespace std;

void ArbolDecision::liberarArbol(NodeDecision* nodo) {
    if (!nodo) return;
    liberarArbol(nodo -> izq);
    liberarArbol(nodo -> der);
    delete nodo;
}
string ArbolDecision::evaluar(NodeDecision* nodo, Paciente* p) {
    if (!nodo) return "MedicinaGeneral";
    if (nodo -> esHoja) return nodo -> preguntaOServicio;

    if (nodo->preguntaOServicio == "esPediatrico") {
        if (p->getEdad() < 15) {
            return evaluar(nodo -> izq, p);
        }
        else {
            return evaluar(nodo -> der, p);
        }
    }
    else if (nodo -> preguntaOServicio == "Hospitalizacion") {
        if (p -> getCantDiasHospitalizacion() > 0) {
            return evaluar(nodo -> izq, p);
        }
        else {
            return evaluar(nodo -> der, p);
        }
    }
    else if (nodo -> preguntaOServicio == "Urgencia") {
        if (p-> getDolor() >= 9 || p -> getDolor() > 39.5) {
            return evaluar(nodo -> izq, p);
        }
        else {
            return evaluar(nodo -> der, p);
        }
    }
    else if (nodo -> preguntaOServicio == "Cirugia") {
        if (p -> getRequiereCirugia()) {
            return evaluar(nodo -> izq, p);
        }
        else {
            return evaluar(nodo -> der, p);
        }
    }
    else if (nodo -> preguntaOServicio == "Cardiologico") {
        if (p -> getTipoDolor() == "pecho" || p -> getPresionArterial() > 140) {
            return evaluar(nodo -> izq, p);
        }
        else {
            return evaluar(nodo -> der, p);
        }
    }
    else if (nodo -> preguntaOServicio == "Trauma") {
        if (p->getTrauma()) {
            return evaluar(nodo -> izq, p);
        }
        else {
            return evaluar(nodo -> der, p);
        }
    }
    else if (nodo -> preguntaOServicio == "Neurologico") {
        if (p -> getSintomasNeurologicos()) {
            return evaluar(nodo -> izq, p);
        }
        else {
            return evaluar(nodo -> der, p);
        }
    }
    return "MedicinaGeneral";
}

ArbolDecision::ArbolDecision() {
    this -> raiz = new NodeDecision("esPediatrico");
    raiz -> izq = new NodeDecision("Hospitalizacion");
    raiz -> izq -> izq = new NodeDecision("Hospitalacion", true);
    raiz -> izq -> der = new NodeDecision("Pediatria", true);

    raiz -> der = new NodeDecision("Urgencia");
    raiz -> der -> izq = new NodeDecision("Urgencia", true);
    raiz -> der -> der = new NodeDecision("Cirugia");
    raiz -> der -> der -> izq = new NodeDecision("Cirugia", true);
    raiz -> der -> der -> der = new NodeDecision("Cardiologico");
    raiz -> der -> der -> der -> izq = new NodeDecision("Cardiologia", true);
    raiz -> der -> der -> der -> der = new NodeDecision("Trauma");
    raiz -> der -> der -> der -> der -> izq = new NodeDecision("Traumatologia", true);
    raiz -> der -> der -> der -> der -> der = new NodeDecision("Neurologico");
    raiz -> der -> der -> der -> der -> der -> izq = new NodeDecision("Neurologia", true);
    raiz -> der -> der -> der -> der -> der -> der = new NodeDecision("MedicinaGeneral", true);
}
string ArbolDecision::determinarServicio(Paciente *p) {
    return evaluar(raiz, p);
}

