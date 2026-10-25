#pragma once
#include <iostream>
#include <string>
using namespace std;

class NodeDecision {
    public:
    string preguntaOServicio;
    bool esHoja;
    NodeDecision* izq;
    NodeDecision* der;

    NodeDecision(string txt) {
        preguntaOServicio = txt;
        esHoja = false;
        izq = nullptr;
        der = nullptr;
    }
    NodeDecision(string txt, bool esHoja) {
        preguntaOServicio = txt;
        this -> esHoja = esHoja;
        izq = nullptr;
        der = nullptr;
    }
    ~NodeDecision() {

    }
};
