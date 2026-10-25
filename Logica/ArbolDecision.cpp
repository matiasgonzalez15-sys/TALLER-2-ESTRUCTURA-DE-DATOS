#include "../Dominio/ArbolDecision.h"
#include <string>
using namespace std;

void ArbolDecision::liberarArbol(NodeDecision* nodo) {
    if (!nodo) return;
    liberarArbol(nodo -> izq);
    liberarArbol(nodo -> der);
    delete nodo;
}


ArbolDecision::ArbolDecision() {
    this -> raiz = new NodeDecision("esPediatrico");
    raiz -> izq = new NodeDecision("Hospitalizacion");
    raiz -> izq -> izq = new NodeDecision("Hospitalizacion", true);
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


void ArbolDecision::agregarPaso(string& ruta, const string& paso) {
    if (!ruta.empty()) ruta += " -> ";
    ruta += paso;
}

string ArbolDecision::evaluar(NodeDecision* nodo, Paciente* p, string& ruta) {
    if (!nodo) return "MedicinaGeneral";
    if (nodo->esHoja) return nodo->preguntaOServicio;

    bool cumple = false;
    string textoSi, textoNo;
    const string& q = nodo->preguntaOServicio;

    if (q == "esPediatrico") {
        cumple = p->getEdad() < 15;
        textoSi = "Edad < 15";
        textoNo = "Edad >= 15";
    }
    else if (q == "Hospitalizacion") {
        cumple = p->getCantDiasHospitalizacion() > 0;
        textoSi = "DiasHospitalizacion > 0";
        textoNo = "DiasHospitalizacion == 0";
    }
    else if (q == "Urgencia") {
        cumple = p->getDolor() >= 9 || p->getTemperatura() >= 39.5;
        textoSi = "Dolor >= 9 o Temperatura >= 39.5";
        textoNo = "Dolor < 9 y Temperatura < 39.5";
    }
    else if (q == "Cirugia") {
        cumple = p->getRequiereCirugia();
        textoSi = "RequiereCirugia == 1";
        textoNo = "RequiereCirugia == 0";
    }
    else if (q == "Cardiologico") {
        cumple = p->getTipoDolor() == "pecho" || p->getPresionArterial() > 140;
        textoSi = "TipoDolor == pecho o Presion > 140";
        textoNo = "TipoDolor != pecho y Presion <= 140";
    }
    else if (q == "Trauma") {
        cumple = p->getTrauma();
        textoSi = "Trauma == 1";
        textoNo = "Trauma == 0";
    }
    else if (q == "Neurologico") {
        cumple = p->getSintomasNeurologicos();
        textoSi = "SintomasNeurologicos == 1";
        textoNo = "SintomasNeurologicos == 0";
    }
    else {
        agregarPaso(ruta, "Nodo desconocido (" + q + ")");
        return "MedicinaGeneral";
    }
    if(cumple){
        agregarPaso(ruta,textoSi);
    }
    else{
        agregarPaso(ruta,textoNo);
    }

    return evaluar(cumple ? nodo->izq : nodo->der, p, ruta);
}

string ArbolDecision::determinarServicio(Paciente* p, string& ruta) {
    ruta.clear();
    if(p == nullptr){
        ruta = "Datos insuficientes";
        return "MedicinaGeneral";
    }
    return evaluar(raiz, p, ruta);
}
void ArbolDecision::inordenRec(NodeDecision* n) {
    if (!n) return;
    inordenRec(n->izq);
    if(n->esHoja){
          cout << "Servicio: "<< n->preguntaOServicio << endl;
    }
    else{
          cout <<  "Pregunta: " << n->preguntaOServicio << endl;
    }
    inordenRec(n->der);
}
void ArbolDecision::preordenRec(NodeDecision* n) {
    if (!n) return;
    if(n->esHoja){
          cout << "Servicio: "<< n->preguntaOServicio << endl;
    }
    else{
          cout <<  "Pregunta: " << n->preguntaOServicio << endl;
    }
    inordenRec(n->izq);
    inordenRec(n->der);
}
void ArbolDecision::postordenRec(NodeDecision* n) {
    if (!n) return;
    inordenRec(n->izq);
    inordenRec(n->der);
    if(n->esHoja){
          cout << "Servicio: "<< n->preguntaOServicio << endl;
    }
    else{
          cout <<  "Pregunta: " << n->preguntaOServicio << endl;
    }
}
void ArbolDecision::mostrarPreorden()  { cout << "\n--- Arbol de decision: PREORDEN ---" << endl;  preordenRec(raiz); }
void ArbolDecision::mostrarInorden()   { cout << "\n--- Arbol de decision: INORDEN ---" << endl;   inordenRec(raiz); }
void ArbolDecision::mostrarPostorden() { cout << "\n--- Arbol de decision: POSTORDEN ---" << endl; postordenRec(raiz); }


ArbolDecision::~ArbolDecision() {
    liberarArbol(raiz);
}
