  cmake_minimum_required(VERSION 3.10)
   project(HospitalTaller2)

   set(CMAKE_CXX_STANDARD 17)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)

   add_executable(hospital
           Logica/main.cpp
           Logica/Hospital.cpp
           Logica/ColaPacientes.cpp
           Logica/ArbolDecision.cpp
           Logica/ArbolAVL.cpp
   )

   configure_file(${CMAKE_SOURCE_DIR}/pacientes.txt ${CMAKE_BINARY_DIR}/pacientes.txt COPYONLY)
