cmake_minimum_required(VERSION 4.3)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1
        Dominio/Paciente.h
        Dominio/Hospital.h
        Dominio/NodeServicios.h
        Dominio/ServicioMedico.h
        Dominio/NodePacientes.h
        Logica/main.cpp
        Logica/Hospital.cpp
        Dominio/ColaPacientes.h
        Logica/ColaPacientes.cpp
        Dominio/ArbolDecision.h
        Dominio/NodeDecision.h
        Logica/ArbolDecision.cpp
)
