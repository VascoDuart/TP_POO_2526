#ifndef TP_POO_2526_INTERFACEGRELHA_H
#define TP_POO_2526_INTERFACEGRELHA_H


#include "Jardim.h"
#include "Jardineiro.h"

class InterfaceGrelha {
    const Jardim& jardim;
    const Jardineiro& jd;
public:
    InterfaceGrelha(Jardim& jardim,Jardineiro& jardineiro);
    void desenharJardim() const;
};


#endif //TP_POO_2526_INTERFACEGRELHA_H
