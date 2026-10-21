#pragma once
#include <string>
#include "NodoAVL.h"
using namespace std;

class ArbolAVL {
private:
    NodoAVL* raiz;
    int cantidad;

   
    static int compararId(const string& a, const string& b);
  
    static int alturaNodo(NodoAVL* n);
    static int balanceNodo(NodoAVL* n);
    static void actualizarAltura(NodoAVL* n);

    static NodoAVL* rotarDerecha(NodoAVL* y);
    static NodoAVL* rotarIzquierda(NodoAVL* x);
    static NodoAVL* rotarIzquierdaDerecha(NodoAVL* n);
    static NodoAVL* rotarDerechaIzquierda(NodoAVL* n);

   
    static NodoAVL* balancear(NodoAVL* n);

    NodoAVL* insertarRec(NodoAVL* n, Paciente* p, bool& insertado);
    NodoAVL* eliminarRec(NodoAVL* n, const string& id, bool& eliminado);
    static NodoAVL* extraerMinimo(NodoAVL* n, Paciente*& extraido);
    Paciente* buscarNombreRec(NodoAVL* n, const string& nombreMin, string* ruta) const;
    static void liberar(NodoAVL* n);

    static void inordenRec(NodoAVL* n, bool& primero);
    static void preordenRec(NodoAVL* n, bool& primero);
    static void postordenRec(NodoAVL* n, bool& primero);
    static void balancesRec(NodoAVL* n);

public:
    ArbolAVL();
    ArbolAVL(const ArbolAVL&) = delete;
    ArbolAVL& operator=(const ArbolAVL&) = delete;
    ~ArbolAVL();

    bool insertar(Paciente* p);
    bool eliminar(const string& id);

    Paciente* buscarPorId(const string& id, string* ruta = nullptr) const;
   
    Paciente* buscarPorNombre(const string& nombre, string* ruta = nullptr) const;
    bool existe(const string& id) const;

    int altura() const;
    int total() const;
    bool vacio() const;

    void mostrarInorden() const;
    void mostrarPreorden() const;
    void mostrarPostorden() const;

    void mostrarBalances() const;
};
