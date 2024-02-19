#include "../controllers/JuegoDeLaOca.hpp"
class View{

private:
    JuegoDeLaOca juego;
public:
    View(){}

    void start(){
        while(true){
         
          juego.jugar();
          
          if(juego.isGameOver()){
             juego = JuegoDeLaOca();
           
            }
        }
    }

   
};


