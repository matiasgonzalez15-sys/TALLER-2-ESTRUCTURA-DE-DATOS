#include <string>
using namespace std;
class Paciente {
private:
    string id;
    string nombre;
    int edad;
    float temperatura;
    float presionArterial;
    float dolor;
    string tipoDolor;
    bool trauma;
    bool sintomasNeurologicos;
    bool requiereCirugia;
    int cantDiasHospitalizacion;
    ;
public:
    bool determinar(string num) {
        if (num == "1") {
            return true;
        }
        return false;
    }

    Paciente(string id, string nombre, int edad, float temperatura,
        float presionArterial, float dolor, string tipoDolor, string trauma,
        string sintomasNeurologicos, string requiereCirugia, int cantDiasHospitalizacion) {

        this->id = id;
        this->nombre = nombre;
        this->edad = edad;
        this->temperatura = temperatura;
        this->presionArterial = presionArterial;
        this->dolor = dolor;
        this -> trauma = determinar(trauma);
        this -> sintomasNeurologicos = determinar(sintomasNeurologicos);
        this-> requiereCirugia = determinar(requiereCirugia);
        this -> cantDiasHospitalizacion = cantDiasHospitalizacion;

    }
    string getId() {
        return this->id;
    }
    string getNombre() {
        return this->nombre;
    }
    int getEdad() {
        return this->edad;
    }
    float getTemperatura() {
        return this->temperatura;
    }
    float getPresionArterial() {
        return this->presionArterial;
    }
    float getDolor() {
        return this->dolor;
    }
    string getTipoDolor() {
        return this->tipoDolor;
    }
    bool getTrauma() {
        return this->trauma;
    }
    bool getSintomasNeurologicos() {
        return this->sintomasNeurologicos;
    }
    bool getRequiereCirugia() {
        return this->requiereCirugia;
    }
    int getCantDiasHospitalizacion() {
        return this -> cantDiasHospitalizacion;
    }
    ~Paciente() {}
};
