//
// Created by josek on 2/28/18.
//


#include "nodobb.cpp"
class ArbolBB{
private:
public:
    NodoBB *getRaiz() const {
        return raiz;
    }

    void setRaiz(NodoBB *raiz) {
        ArbolBB::raiz = raiz;
    }

private:
    NodoBB *raiz;
    int size =0;

public:
    ArbolBB(){
        raiz=NULL;
    }
    bool vacio(){
        return raiz==NULL;
    }

    void mostrarLista() {                    //Orden____

    }

    void insertar(int d){
        NodoBB *nodoNew = new NodoBB(d);

        if(vacio()){
            raiz=nodoNew;
        }
        else{
            NodoBB *nodoBB =raiz;
            NodoBB *padre;
/*
            while (1==1){
                padre=nodoBB;
                if (d)
            }   */
        }
    }


    void eliminar(int key){     //FALTA________REVISAR
    }


    void buscar(int key) { // Accion por medio del Indice (0.1.2.3---)

    }

    void editarKey(int newValue,int key) {
    }
};
