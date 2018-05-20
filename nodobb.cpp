//
// Created by josek on 2/28/18.
//
#include "iostream"
using namespace std;

class NodoBB{
private:
    int dato;

public:
    NodoBB *HijoIzq;
    NodoBB *HijoDer;

    NodoBB(int dato){
        this->dato=dato;
        this->HijoIzq=NULL;
        this->HijoDer=NULL;
    }

    int getDato() const {
        return dato;
    }

    void setDato(int dato) {
        NodoBB::dato = dato;
    }

    NodoBB *getHijoIzq() const {
        return HijoIzq;
    }

    void setHijoIzq(NodoBB *HijoIzq) {
        NodoBB::HijoIzq = HijoIzq;
    }

    NodoBB *getHijoDer() const {
        return HijoDer;
    }

    void setHijoDer(NodoBB *HijoDer) {
        NodoBB::HijoDer = HijoDer;
    }
};
