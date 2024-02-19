#include <iostream>
#include <vector>
#include <algorithm> 
#include "CasillaEspecial.hpp"


class Tablero {
private:
    int TAM_TABLERO;
    std::vector<int> oca; 
    std::vector<std::vector<CasillaEspecial*>> casillasEspeciales;
    std::vector<std::vector<int>> casillasEspecialesInt;

public:

    Tablero() {
    
        // Inicialización del tablero con valores de ejemplo
       TAM_TABLERO = 8;
       oca={8, 13, 18, 23, 28, 33, 38, 43, 48, 53, 58};
       casillasEspecialesInt = {
        {8, 0, 0, 0, 0, 1, 0, 7},
        {1, 0, 0, 0, 6, 1, 0, 0},
        {0, 0, 0, 0, 1, 5, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 4, 0, 0, 0, 1},
        {0, 0, 1, 3, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 2, 0}};

       llenarTablero();
       asignarCasillasEspeciales();
    }
    ~Tablero() {
        // Limpieza de la memoria asignada dinámicamente
        for (int i = 0; i < TAM_TABLERO; ++i) {
            for (int j = 0; j < TAM_TABLERO; ++j) {
                delete casillasEspeciales[i][j];
            }
        }
    }
    int getTAM_TABLERO() {
        return TAM_TABLERO;
    }
    CasillaEspecial* getCasilla(int fila, int columna){
        return casillasEspeciales[fila][columna];
    }
    void setCasillasEspecialesInt(const std::vector<std::vector<int>>& valores) {
        casillasEspecialesInt = valores;
    }
    // Método de get para casillasEspecialesInt
    const std::vector<std::vector<int>>& getCasillasEspecialesInt() const {
        return casillasEspecialesInt;
    }
    const std::vector<int>& getOca() const {
        return oca;
    }
private:
    void llenarTablero(){
         int valor=63;
         bool bandera=false;
        for (int i = 0; i< TAM_TABLERO ; ++i) {
      
            std::vector<CasillaEspecial*> fila;
          
            for (int j = 0; j < TAM_TABLERO; ++j) {

                char valorString = std::to_string(valor)[0];
                fila.push_back(new CasillaEspecial(valor, valorString));
                
                valor--;
            }
               
            if(bandera){
                std::reverse(fila.begin(), fila.end());
            }
             bandera = !bandera;
            
            casillasEspeciales.push_back(fila);
        }
 }
  
void asignarCasillasEspeciales(){

       for (int i = 0; i< TAM_TABLERO ; ++i) {
          for (int j = 0; j < TAM_TABLERO; ++j) {

                switch (casillasEspecialesInt[i][j]) {
                        case 1:
                            getCasilla(i,j)->setLetra('O');
                            //getCasilla(i,j)->setValor(1);                          
                            break;
                        case 2:
                            getCasilla(i,j)->setLetra('P');
                            //getCasilla(i,j)->setValor(2);  
                            break;
                        case 3:
                            getCasilla(i,j)->setLetra('P');
                          //  getCasilla(i,j)->setValor(3); 
                            break;
                        case 4:
                            getCasilla(i,j)->setLetra('H');
                           // getCasilla(i,j)->setValor(4); 
                            break;
                        case 5:
                            getCasilla(i,j)->setLetra('L');
                           // getCasilla(i,j)->setValor(5); 
                            break;
                        case 6:
                            getCasilla(i,j)->setLetra('C');
                           // getCasilla(i,j)->setValor(6); 
                            break;
                        case 7:
                            getCasilla(i,j)->setLetra('M');
                           // getCasilla(i,j)->setValor(7); 
                            break;
                        case 8:
                            getCasilla(i,j)->setLetra('J');
                           // getCasilla(i,j)->setValor(8); 
                            break;
                        default:
                            break;
                }
            }
       }
}
};
