#include "../Dominio/ArbolAVL.h"
#include <iostream>
#include <cctype>
using namespace std;

namespace {
bool soloDigitos(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

string sinCerosIzquierda(const string& s) {
    size_t i = 0;
    while (i + 1 < s.size() && s[i] == '0') i++;
    return s.substr(i);
}

string aMinusculas(string s) {
    for (char& c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

// [EXP] Agrega el ID del nodo visitado a la ruta de busqueda, separado por " -> ".
void agregarARuta(string* ruta, NodoAVL* n) {
    if (ruta == nullptr) return;
    if (!ruta->empty()) *ruta += " -> ";
    *ruta += n->paciente->getId();
}

void imprimirPaciente(NodoAVL* n, bool& primero) {
    if (!primero) cout << ", ";
    cout << n->paciente->getNombre() << " (" << n->paciente->getId() << ")";
    primero = false;
}
}

ArbolAVL::ArbolAVL() : raiz(nullptr), cantidad(0) {}

ArbolAVL::~ArbolAVL() {
    liberar(raiz);
}

// [EXP] Postorden: primero se liberan los hijos y despues el nodo y su paciente.
void ArbolAVL::liberar(NodoAVL* n) {
    if (n == nullptr) return;
    liberar(n->izq);
    liberar(n->der);
    delete n->paciente;
    delete n;
}

int ArbolAVL::compararId(const string& a, const string& b) {
    if (soloDigitos(a) && soloDigitos(b)) {
        string x = sinCerosIzquierda(a);
        string y = sinCerosIzquierda(b);
        if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
        int c = x.compare(y);
        return c < 0 ? -1 : (c > 0 ? 1 : 0);
    }
    int c = a.compare(b);
    return c < 0 ? -1 : (c > 0 ? 1 : 0);
}

int ArbolAVL::alturaNodo(NodoAVL* n) {
    return n == nullptr ? 0 : n->altura;
}

int ArbolAVL::balanceNodo(NodoAVL* n) {
    return n == nullptr ? 0 : alturaNodo(n->izq) - alturaNodo(n->der);
}

void ArbolAVL::actualizarAltura(NodoAVL* n) {
    int hi = alturaNodo(n->izq);
    int hd = alturaNodo(n->der);
    n->altura = 1 + (hi > hd ? hi : hd);
}

// [EXP] Rotacion simple a la derecha (caso izquierda-izquierda).
// [EXP] Antes: y es la raiz, x su hijo izquierdo, B el hijo derecho de x.
// [EXP] Despues: x pasa a ser la raiz, y queda como su hijo derecho y B pasa a ser el hijo izquierdo de y.
NodoAVL* ArbolAVL::rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->izq;
    NodoAVL* b = x->der;
    x->der = y;
    y->izq = b;
    // [EXP] Se actualiza primero y (quedo abajo) y despues x (quedo arriba).
    actualizarAltura(y);
    actualizarAltura(x);
    return x;
}

// [EXP] Rotacion simple a la izquierda (caso derecha-derecha), espejo de la anterior.
NodoAVL* ArbolAVL::rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->der;
    NodoAVL* b = y->izq;
    y->izq = x;
    x->der = b;
    actualizarAltura(x);
    actualizarAltura(y);
    return y;
}

// [EXP] Rotacion doble izquierda-derecha (caso izquierda-derecha):
// [EXP] primero se rota a la izquierda el hijo izquierdo y luego a la derecha el nodo.
NodoAVL* ArbolAVL::rotarIzquierdaDerecha(NodoAVL* n) {
    n->izq = rotarIzquierda(n->izq);
    return rotarDerecha(n);
}

// [EXP] Rotacion doble derecha-izquierda (caso derecha-izquierda):
// [EXP] primero se rota a la derecha el hijo derecho y luego a la izquierda el nodo.
NodoAVL* ArbolAVL::rotarDerechaIzquierda(NodoAVL* n) {
    n->der = rotarDerecha(n->der);
    return rotarIzquierda(n);
}

NodoAVL* ArbolAVL::balancear(NodoAVL* n) {
    actualizarAltura(n);
    int balance = balanceNodo(n);

    // [EXP] Cargado a la izquierda.
    if (balance > 1) {
        // [EXP] Si el hijo izquierdo esta cargado a la derecha es LR (doble); si no, LL (simple).
        if (balanceNodo(n->izq) < 0) return rotarIzquierdaDerecha(n);
        return rotarDerecha(n);
    }
    // [EXP] Cargado a la derecha.
    if (balance < -1) {
        // [EXP] Si el hijo derecho esta cargado a la izquierda es RL (doble); si no, RR (simple).
        if (balanceNodo(n->der) > 0) return rotarDerechaIzquierda(n);
        return rotarIzquierda(n);
    }
    return n;
}

NodoAVL* ArbolAVL::insertarRec(NodoAVL* n, Paciente* p, bool& insertado) {
    if (n == nullptr) {
        insertado = true;
        return new NodoAVL(p);
    }
    int c = compararId(p->getId(), n->paciente->getId());
    if (c < 0) {
        n->izq = insertarRec(n->izq, p, insertado);
    } else if (c > 0) {
        n->der = insertarRec(n->der, p, insertado);
    } else {
        // [EXP] ID repetido: no se inserta.
        insertado = false;
        return n;
    }
    // [EXP] Al volver de la recursion se rebalancea cada nodo del camino de insercion.
    return balancear(n);
}

bool ArbolAVL::insertar(Paciente* p) {
    if (p == nullptr) return false;
    bool insertado = false;
    raiz = insertarRec(raiz, p, insertado);
    if (insertado) cantidad++;
    return insertado;
}

// [EXP] Quita el nodo minimo de un subarbol SIN borrar al paciente: lo entrega por
// [EXP] 'extraido' para que el llamador lo reubique. Rebalancea al volver.
NodoAVL* ArbolAVL::extraerMinimo(NodoAVL* n, Paciente*& extraido) {
    if (n->izq == nullptr) {
        extraido = n->paciente;
        NodoAVL* der = n->der;
        delete n;
        return der;
    }
    n->izq = extraerMinimo(n->izq, extraido);
    return balancear(n);
}

NodoAVL* ArbolAVL::eliminarRec(NodoAVL* n, const string& id, bool& eliminado) {
    if (n == nullptr) return nullptr;
    int c = compararId(id, n->paciente->getId());
    if (c < 0) {
        n->izq = eliminarRec(n->izq, id, eliminado);
    } else if (c > 0) {
        n->der = eliminarRec(n->der, id, eliminado);
    } else {
        eliminado = true;
        // [EXP] Caso 1 y 2: sin hijos o con un solo hijo. El hijo (o null) ocupa su lugar.
        if (n->izq == nullptr || n->der == nullptr) {
            NodoAVL* hijo = (n->izq != nullptr) ? n->izq : n->der;
            delete n->paciente;
            delete n;
            return hijo;
        }
        // [EXP] Caso 3: dos hijos. Se reemplaza por su sucesor inorden (el minimo del
        // [EXP] subarbol derecho), que se extrae de su posicion original.
        Paciente* sucesor = nullptr;
        n->der = extraerMinimo(n->der, sucesor);
        delete n->paciente;
        n->paciente = sucesor;
    }
    return balancear(n);
}

bool ArbolAVL::eliminar(const string& id) {
    bool eliminado = false;
    raiz = eliminarRec(raiz, id, eliminado);
    if (eliminado) cantidad--;
    return eliminado;
}

Paciente* ArbolAVL::buscarPorId(const string& id, string* ruta) const {
    NodoAVL* actual = raiz;
    while (actual != nullptr) {
        agregarARuta(ruta, actual);
        int c = compararId(id, actual->paciente->getId());
        if (c == 0) return actual->paciente;
        actual = (c < 0) ? actual->izq : actual->der;
    }
    return nullptr;
}

Paciente* ArbolAVL::buscarNombreRec(NodoAVL* n, const string& nombreMin, string* ruta) const {
    if (n == nullptr) return nullptr;
    agregarARuta(ruta, n);
    if (aMinusculas(n->paciente->getNombre()) == nombreMin) return n->paciente;
    Paciente* r = buscarNombreRec(n->izq, nombreMin, ruta);
    if (r != nullptr) return r;
    return buscarNombreRec(n->der, nombreMin, ruta);
}

Paciente* ArbolAVL::buscarPorNombre(const string& nombre, string* ruta) const {
    return buscarNombreRec(raiz, aMinusculas(nombre), ruta);
}

bool ArbolAVL::existe(const string& id) const {
    return buscarPorId(id) != nullptr;
}

int ArbolAVL::altura() const {
    return alturaNodo(raiz);
}

int ArbolAVL::total() const {
    return cantidad;
}

bool ArbolAVL::vacio() const {
    return raiz == nullptr;
}

// [EXP] Inorden: izquierdo, nodo, derecho. En un ABB sale ordenado por ID.
void ArbolAVL::inordenRec(NodoAVL* n, bool& primero) {
    if (n == nullptr) return;
    inordenRec(n->izq, primero);
    imprimirPaciente(n, primero);
    inordenRec(n->der, primero);
}

// [EXP] Preorden: nodo, izquierdo, derecho. Muestra la forma del arbol (la raiz sale primero).
void ArbolAVL::preordenRec(NodoAVL* n, bool& primero) {
    if (n == nullptr) return;
    imprimirPaciente(n, primero);
    preordenRec(n->izq, primero);
    preordenRec(n->der, primero);
}

// [EXP] Postorden: izquierdo, derecho, nodo.
void ArbolAVL::postordenRec(NodoAVL* n, bool& primero) {
    if (n == nullptr) return;
    postordenRec(n->izq, primero);
    postordenRec(n->der, primero);
    imprimirPaciente(n, primero);
}

void ArbolAVL::mostrarInorden() const {
    if (raiz == nullptr) { cout << "Sin pacientes" << endl; return; }
    bool primero = true;
    inordenRec(raiz, primero);
    cout << endl;
}

void ArbolAVL::mostrarPreorden() const {
    if (raiz == nullptr) { cout << "Sin pacientes" << endl; return; }
    bool primero = true;
    preordenRec(raiz, primero);
    cout << endl;
}

void ArbolAVL::mostrarPostorden() const {
    if (raiz == nullptr) { cout << "Sin pacientes" << endl; return; }
    bool primero = true;
    postordenRec(raiz, primero);
    cout << endl;
}

void ArbolAVL::balancesRec(NodoAVL* n) {
    if (n == nullptr) return;
    balancesRec(n->izq);
    cout << "  " << n->paciente->getId() << " (" << n->paciente->getNombre() << ")"
         << " | altura del nodo: " << n->altura
         << " | factor de balance: " << balanceNodo(n) << endl;
    balancesRec(n->der);
}

void ArbolAVL::mostrarBalances() const {
    cout << "Altura del arbol: " << altura() << endl;
    balancesRec(raiz);
}
