#include <iostream>
#include <cstdlib>
class Jugador {
private:
   std::string correo;
   std::string name;
   int id;
   int posicionX;
   int posicionY;
   int castigo;
   bool carcel;
   bool derechaOrIzquierda;
   std::string color;
   
public:       
   Jugador(int posicionX, int posicionY, int castigo, bool carcel,bool derechaOrIzquierda) : 
               posicionX(posicionX), 
               posicionY(posicionY), 
               castigo(castigo),
               carcel(carcel),
               derechaOrIzquierda(derechaOrIzquierda){}
    
    void mover(int pasos, int TAM_TABLERO) {

        int nuevaPosicionY = posicionY + pasos;

        if (posicionY >= (TAM_TABLERO - 1) && 
            (posicionX == (TAM_TABLERO-1) || posicionX == 5 || posicionX == 3 || posicionX == 1)) {
           
            posicionX -= nuevaPosicionY - (TAM_TABLERO - 1);
            posicionY = TAM_TABLERO - 1;
            derechaOrIzquierda = false;

        } else if (posicionY <= 0 && (posicionX == 6 || posicionX == 4 || posicionX == 2)) {
          
            posicionX -= abs(nuevaPosicionY);
            posicionY = 0;
            derechaOrIzquierda = true;

        } else {
            if (derechaOrIzquierda) {
                posicionY = nuevaPosicionY;
               
            } else {
                posicionY = posicionY - pasos;
                
            }
        }
        // Asegurar que la posición en X permanezca dentro de los límites
        posicionX = std::max(0, std::min(posicionX, TAM_TABLERO - 1));
        // Asegurar que la posición en Y permanezca dentro de los límites
        posicionY = std::max(0, std::min(posicionY, TAM_TABLERO - 1));
}
   
    void setName(const std::string& newName) {
        name = newName;
    }
    void setCorreo(const std::string& newCorreo) {
        correo = newCorreo;
    }
    void setCastigo(int newCastigo){
        castigo = newCastigo;
    }
     void setId(const int newId){
        id = newId;
    }
    void setPosicionX(const int newPosicionX){
        posicionX = newPosicionX;
    }
    void setPosicionY(const int newPosicionY){
        posicionY = newPosicionY;
    }
    void setCarcel(const bool newCarcel){
        carcel = newCarcel;
    }
    void setDerechaOrIzquierda(const bool newDerechaOrIzquierda){
        derechaOrIzquierda = newDerechaOrIzquierda;
    }
    void setColor(const std::string& newColor) {
        color = newColor;
    }
    std::string getColor() const {
        return color;
    }
    std::string getName() const {
        return name;
    }
    std::string getCorreo() const {
        return correo;
    }
    int getId() const {
        return id;
    }
    int getPosicionX() const {
        return posicionX;
    }
    int getPosicionY() const {
        return posicionY;
    }
     int getCastigo() const {
        return castigo;
    }
    bool isCarcel(){
        return carcel;
    }
     bool isDerechaOrIzquierda(){
        return derechaOrIzquierda;
    }
};

