cmake_minimum_required(VERSION 4.0)
project(TP_POO_2526)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP_POO_2526 main.cpp
        Jardim.cpp
        Jardim.h
        Jardineiro.cpp
        Jardineiro.h
        Simulador.cpp
        Simulador.h
        Ferramentas/Ferramenta.cpp
        Ferramentas/Ferramenta.h
        Settings.h
        Posicao.cpp
        Posicao.h
        Plantas/Planta.cpp
        Plantas/Planta.h
        Comando.cpp
        Comando.h
        Ferramentas/Regador.cpp
        Ferramentas/Regador.h
        Ferramentas/Adubo.cpp
        Ferramentas/Adubo.h
        Ferramentas/Tesoura.cpp
        Ferramentas/Tesoura.h
        Plantas/Cacto.cpp
        Plantas/Cacto.h
        Plantas/Roseira.cpp
        Plantas/Roseira.h
        Plantas/ErvaDaninha.cpp
        Plantas/ErvaDaninha.h
        Plantas/PlantaExotica.cpp
        Plantas/PlantaExotica.h
        InterfaceGrelha.cpp
        InterfaceGrelha.h)
