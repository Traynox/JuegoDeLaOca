#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "../models/Jugador.hpp"
#include "../models/Tablero.hpp"
#include "../archivos/Archivos.hpp"
#include "../models/Estructuras.h"

class JuegoDeLaOca {
private:
    Jugador jugador1;
    Jugador jugador2;
    Tablero tablero;
    int modePlay; // modo de juego ( 2 jugadores o 1)
    std::string nombresRamdon[7];
    std::string ANSI_RESET; //color por defecto de consola
    std::string ANSI_YELLOW;
    bool gameOver;
    Archivos archivo;
    int dado;
public:
    JuegoDeLaOca() : jugador1(7,0,0,false,true),
                     jugador2(7,0,0,false,true), 
                     nombresRamdon{"Pepe(CPU)", "Pablo(CPU)", "Maria(CPU)", "Flora(CPU)", 
                                    "Max(CPU)", "Tomas(CPU)", "Stacy(CPU)"}, 
                     ANSI_RESET("\033[0m"), 
                     ANSI_YELLOW("\033[33m"), 
                     gameOver(false),
                     archivo("../archivos/puntuaciones.txt") {}

    void setGameOver(bool newGameOver){
        gameOver = newGameOver;
    }
    bool isGameOver(){
        return gameOver;
    }
    
    void verificarJugadores(){
        std::string correo;
        if(modePlay==1){
            if(!archivo.jugadorExiste(jugador1.getName())){
                std::cout << "No estas registrado, por favor, ingresa el correo del jugador 1: ";
                std::cin >> correo;
                jugador1.setCorreo(correo);
                guardar(jugador1,0);
            }else{
                correo = archivo.getJugadorCorreo(jugador1.getName());
                jugador1.setCorreo(correo);
            }
        }else if(modePlay==2){
            if(!archivo.jugadorExiste(jugador1.getName())){
                std::cout << "No estas registrado, por favor, ingresa el Correo del jugador 1: ";
                std::cin >> correo;
                jugador1.setCorreo(correo);
                guardar(jugador1,0);
            }else{
                correo = archivo.getJugadorCorreo(jugador1.getName());
                jugador1.setCorreo(correo);
            }
            if(!archivo.jugadorExiste(jugador2.getName())){
                std::cout << "No estas registrado, por favor, ingresa el Correo del jugador 2: ";
                std::cin >> correo;
                jugador2.setCorreo(correo);
                guardar(jugador2,0);
            }else{
                correo = archivo.getJugadorCorreo(jugador2.getName());
                jugador2.setCorreo(correo);
            }
        }
    }
    
    void bienvenida(){
        std::string name1;
        std::string name2;
      
        srand(time(nullptr));
        bool nextMenu= false;
        while(!nextMenu){
            
            limpiar();
            std::cout << "\n\n Bienvenido al Juego de la Oca para 2 jugadores! \n\n";
            
            std::cout << "Seleccione numero para modo de juego: \n";
            std::cout <<"1:PvE \n";
            std::cout <<"2:PvP \n" ;
            std::cout <<"3: Ver Ranking \n"; 
            std::cout <<"Ingrese su opcion: ";
            std::cin >> modePlay;
            switch (modePlay){

            case 1:
            case 2:
                    nextMenu=true;
                    limpiar();
                break;
            case 3:
                if(archivo.existeFile()){
                    archivo.mostrarPuntuaciones();
                  
                }else{
                    std::cout << "No hay puntuaciones que mostrar"<<std::endl;
                }
               
               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
               break;
            default:
               std::cout << "Ingrese una opcion valida"<<std::endl;
               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            }

            limpiar();
        }

        std::cout << "Por favor, ingresa el ID del jugador 1: ";
        std::cin >> name1;
        
        if(modePlay==1){
            int ramdon = 0 + rand() % 7;
            name2= nombresRamdon[ramdon];
            std::cout << "Se asigno un nombre aleatorio al jugador 2: "<<name2<<" \n";
         }else if(modePlay==2){
            std::cout << "Por favor, ingresa el ID del jugador 2: ";
            std::cin >> name2;
         }
       
        jugador1.setName(name1);
        jugador2.setName(name2);
        jugador1.setId(1);
        jugador2.setId(2);
        jugador1.setColor("\033[32m");
        jugador2.setColor("\033[31m");

        verificarJugadores();
        
    }

    void guardar(Jugador &jugador,int puntos){
        
        std::vector<std::tuple<std::string, std::string, int>> puntuaciones = {
            std::make_tuple(jugador.getCorreo(), jugador.getName(), puntos) };
        if(archivo.jugadorExiste(jugador.getName())){
            archivo.actualizarPuntos(jugador.getName(),1);
           
        }else{
            archivo.guardarPuntuaciones(puntuaciones);
        }
    }

    void jugar() {
        
        bienvenida();
        /*std::string name1="juan";
        std::string name2="pepe";
        jugador1.setName(name1);
        jugador2.setName(name2);
        jugador1.setId(1);
        jugador2.setId(2);
        jugador1.setColor("\033[32m");
        jugador2.setColor("\033[31m");*/
        std::cout <<"Jugador "<<jugador1.getColor()<<jugador1.getName()<<ANSI_RESET<<" y jugador "<<jugador2.getColor()<< jugador2.getName()<<ANSI_RESET<<" Listos!... \n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        limpiar();
        std::cout <<ANSI_YELLOW<< "COMIENCEN!!!\n"<<ANSI_RESET;
       
        while (!gameOver) {  
            
            if(!isCastigo(jugador1)){
                if(jugador1.isCarcel()){
                    carcelMessage(jugador1);
                }else{
                    seguirOAbandonarJuego(jugador1);
                    
                    if(gameOver){break;}
                    jugarTurno(jugador1,false);
                    
                    if(isOca(jugador1)){ oca(jugador1); }
                    if(isPuente(jugador1)){ puente(jugador1); }
                    if(isHospedaje(jugador1)){ hospedaje(jugador1); }
                    if(isMuerte(jugador1)){ muerte(jugador1); }
                    if(isCarcel(jugador1)){ carcel(jugador1,jugador2); }
                }
            }else{
                castigoMessage(jugador1);
            }

            if (isGanador(jugador1)) {
                std::cout <<"Jugador "<<jugador1.getColor() << jugador1.getName()<<ANSI_RESET<<" ha ganado!\n";

                guardar(jugador1,1);
                gameOver=true;
                std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                break;
            }
            
           if(!isCastigo(jugador2)){
                if(jugador2.isCarcel()){
                    carcelMessage(jugador2);
                }else{
                    seguirOAbandonarJuego(jugador2); 
                    
                    if(gameOver){break;}
                    jugarTurno(jugador2,false);
                    
                    if(isOca(jugador2)){ oca(jugador2); }
                    if(isPuente(jugador2)){ puente(jugador2); }
                    if(isHospedaje(jugador2)){ hospedaje(jugador2); }
                    if(isMuerte(jugador2)){ muerte(jugador2); }
                    if(isCarcel(jugador2)){ carcel(jugador1,jugador2); }
                }
           }else{
                castigoMessage(jugador2);
           }

            if (isGanador(jugador2)) {
                std::cout <<"Jugador "<<jugador2.getColor()<< jugador2.getName()<<ANSI_RESET<<" ha ganado!\n";
                
                guardar(jugador2,1);
                gameOver=true;
                std::this_thread::sleep_for(std::chrono::milliseconds(3000)); 
                break;
            }
            
        }
    }

private:
   
    void jugarTurno(Jugador &jugador,bool isOca) {

            if(isOca){//isOca(jugador)
                dado = dado; // conservar el valor anterior del dado
            }else{
                dado = 1 + rand() % 6;   
                //dado=3;
            }
            std::cout << "Has sacado un " << dado << " en el dado.\n";
            int count=1;
            
            while (count<=dado){
 
                limpiar();
                jugador.mover(1, tablero.getTAM_TABLERO());// se mueve de 1 en 1 por casilla
                imprimirTablero();
                if(isExcesoDeDadosAlFinal(jugador,count)){
                std::cout << "El jugador "<<jugador.getColor()<<jugador.getName()<<ANSI_RESET<<" ha sacado un " << dado << 
                             ", te pasaste en exceso. \n Retrocedes la cantidad faltante de casillas...\n"<<std::flush;
               
                std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // Esperar 4 segundos
                    break;
                }
                std::cout << "El jugador "<<jugador.getColor()<<jugador.getName()<<ANSI_RESET<<" ha sacado un " << dado << " en el dado.\n"<<std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Esperar 1 segundo
                count++;    
            }
         
            limpiar();
            decirFrase(jugador);
    }
    

    bool isGanador(Jugador &jugador) {
        return tablero.getCasilla(jugador.getPosicionX(), jugador.getPosicionY())->getLetra() == 'J';
    }

    bool isExcesoDeDadosAlFinal(Jugador &jugador, int movimientoActual){//count 

        if(isGanador(jugador) && movimientoActual>0){
            
            int posicionX= jugador.getPosicionX();
            int posicionY= jugador.getPosicionY();
            int resultadoPosicion= (tablero.getCasilla(posicionX,posicionY)->getValor() - movimientoActual);
            int size= tablero.getTAM_TABLERO();
            
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){

                    if(resultadoPosicion == tablero.getCasilla(i,j)->getValor()){
                        
                        jugador.setPosicionX(i);
                        jugador.setPosicionY(j);
                        int posicionX = jugador.getPosicionX();
                        if(posicionX == 6 || posicionX == 4 || posicionX == 2){
                            jugador.setDerechaOrIzquierda(true);
                        }else 
                        if((posicionX== (tablero.getTAM_TABLERO()-1) || 
                            posicionX == 5 || posicionX == 3 || posicionX == 1)){
                            jugador.setDerechaOrIzquierda(false);
                        }
                        return true;
                    }
                }
            }
        }
            return false;
    }

    bool isOca(Jugador &jugador){
        
        int size = tablero.getOca().size();
        int posicionX = jugador.getPosicionX();
        int posicionY = jugador.getPosicionY();
        
        for (int i = 0 ; i < size; ++i){
                
              if(tablero.getCasilla(posicionX,posicionY)->getValor() 
                 == tablero.getOca()[i]){
                    
                    return true;
                    }            
        }
        return false;
    }
    void oca(Jugador &jugador){

        bool next=false;
        
        while(!next){
            
            if(isOca(jugador)){
               
                jugarTurno(jugador,true); //is Oca 
            }else{
                next=true;
            }
        }
    }

    bool isLaberinto(Jugador &jugador){
        
        if(jugador.getPosicionX() == 3 && jugador.getPosicionY() == 5){
            jugador.setPosicionX(4);
            jugador.setPosicionY(1);
            return true;
        }
        return false;
    }

    bool isPuente(Jugador &jugador){
        
        if(jugador.getPosicionX()== 7 && jugador.getPosicionY() == 6){
            
            return true;
        
        }else if(jugador.getPosicionX()== 6 && jugador.getPosicionY() == 3){
           
            return true;
        }
        return false;
    }

    void puente(Jugador &jugador){
        
        if(isPuente(jugador)){//jugador.getPosicionX()== 7 && jugador.getPosicionY() == 6
            jugador.setPosicionX(6);
            jugador.setPosicionY(3);
            jugador.setDerechaOrIzquierda(!jugador.isDerechaOrIzquierda());
        
        }else if(isPuente(jugador)){//jugador.getPosicionX()== 6 && jugador.getPosicionY() == 3
            jugador.setPosicionX(7);
            jugador.setPosicionY(6);
            jugador.setDerechaOrIzquierda(!jugador.isDerechaOrIzquierda());
        }
    }

    bool isCastigo(Jugador &jugador){
        if(jugador.getCastigo() > 0){// castigo son los turno que le faltan de del hospedaje
            
            return true;
        }
        return false;
    }
    void carcelMessage(Jugador &jugador){
        
        imprimirTablero();
        std::cout << "No puedes jugar, "<<jugador.getColor()
                      << jugador.getName()<<ANSI_RESET<<" estas en la carcel, "
                      <<" espera a que te rescaten... \n";
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    }
    void castigoMessage(Jugador &jugador){
        
        imprimirTablero();
        std::cout << "No puedes jugar "<<jugador.getColor()
                      << jugador.getName()<<ANSI_RESET<<", faltan "
                      <<jugador.getCastigo() <<" turnos \n";
        // castigo son los turno que le faltan de del hospedaje se le quita uno
        int newCastigo = jugador.getCastigo()-1;
        jugador.setCastigo(newCastigo);
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    }

    bool isHospedaje(Jugador &jugador){

         if(jugador.getPosicionX() == 5 && jugador.getPosicionY() == 3){
           
            return true;
        }
        return false;
    }
    void hospedaje(Jugador &jugador){
        jugador.setCastigo(2);
    }
    bool isCarcel(Jugador &jugador){
       
        if((jugador.getPosicionX() == 1 && jugador.getPosicionY() == 4)){
           return true;
        }
        return false;
    }
    void carcel(Jugador &jugador1, Jugador &jugador2){
        
        if(isCarcel(jugador1)){
            jugador1.setCarcel(true);
            
        } 
        if(isCarcel(jugador2)){
            jugador2.setCarcel(true);
        }
        if(isCarcel(jugador1) && isCarcel(jugador2)){
            jugador1.setCarcel(false);
            jugador2.setCarcel(false);
        }
    }

    bool isMuerte(Jugador &jugador){
        
        if(jugador.getPosicionX()==0 && jugador.getPosicionY()==7){
            return true;
        }
        return false;
    }
    void muerte(Jugador &jugador){
        jugador.setPosicionX(7);
        jugador.setPosicionY(0);
        jugador.setDerechaOrIzquierda(true);// Variable bandera para el movimiento de las fichas
    }
  
    void imprimirTablero(){
        
        std::cout << "+----+----+----+----+----+----+----+----+" << std::endl;
        for (int i =0 ; i < tablero.getTAM_TABLERO(); ++i) {
            
            for (int j = 0 ; j < tablero.getTAM_TABLERO(); ++j) {
                
                if(jugador1.getPosicionX() == i && jugador1.getPosicionY() == j &&
                   jugador2.getPosicionX() == i && jugador2.getPosicionY() == j){
                   
                    std::cout <<"|"<<jugador1.getColor()<< "J1"<<ANSI_RESET<<jugador2.getColor()<<"J2"<<ANSI_RESET;
                   
                }else if (jugador1.getPosicionX() == i && jugador1.getPosicionY() == j) {
                    
                    std::cout << "| "<<jugador1.getColor()<<"J1 "<<ANSI_RESET;
                   
                }else if(jugador2.getPosicionX() == i && jugador2.getPosicionY() == j) {

                    std::cout << "| "<<jugador2.getColor()<<"J2 "<<ANSI_RESET;
                
                }else {
                   printCasilla(i,j);        
                }
            }
            std::cout <<"|"<< std::endl;
        }
            std::cout << "+----+----+----+----+----+----+----+----+" << std::endl;
            //std::cout <<  jugador1.getPosicionX()<<" = X / Y = "<<jugador1.getPosicionY()<<std::endl;  
    }

    void printCasilla(int i, int j){
      int valor = tablero.getCasillasEspecialesInt()[i][j];
      std::string posicionString = std::to_string(tablero.getCasilla(i,j)->getValor());
      switch (valor){
        case 0:
            if (posicionString.length() > 1) {
                std::cout <<"| "<< tablero.getCasilla(i,j)->getValor() <<" ";
            }else{
                std::cout <<"|  "<< tablero.getCasilla(i,j)->getValor() <<" ";
            }
            break;
        case 1: 
        case 2: 
        case 3: 
        case 4:
        case 5: 
        case 6: 
        case 7: 
        case 8:
             std::cout <<"|  "<< tablero.getCasilla(i,j)->getLetra() <<" ";
            break;
        default:
            break;
      }
      
    }

    void decirFrase(Jugador &jugador){

        char valor = tablero.getCasilla(jugador.getPosicionX(),
                                       jugador.getPosicionY())->getLetra();
        
            switch (valor) {
                        case 'O':
                            std::cout <<jugador.getColor()<<jugador.getName()<<": "<<ANSI_YELLOW<< 
                            "De oca a oca y tiro porque me toca!"<<ANSI_RESET<<std::endl;
                            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
                            break;
                        case 'P':
                            std::cout <<jugador.getColor()<<jugador.getName()<<": "<<ANSI_YELLOW<<
                            "De puente a puente y tiro porque me lleva la corriente!"<<ANSI_RESET<<std::endl;
                            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
                            break;
                        case 'L':
                            std::cout <<jugador.getColor()<<jugador.getName()<<": "<<ANSI_YELLOW<< 
                            "Del laberinto al 30! "<<ANSI_RESET<<std::endl;
                            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
                            break;
                        default:
                            break;
                    }
            
    }
    void limpiar(){
        
         std::cout <<"\033[2J\033[H";
    }
    void seguirOAbandonarJuego(Jugador &jugador){
           
            std::cout << "Que deseas hacer "<<jugador.getColor()<<jugador.getName()<<ANSI_RESET<<"?\n";
            std::cout << "1. Tirar dado\n";
            std::cout << "2. Empezar nuevo juego\n";
            std::cout << "3. Salir\n";
            std::cout << "Ingrese su opcion: ";

            int opcion;
            if(modePlay==1 && jugador.getId()==2){
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                opcion = 1; //siempre la cpu escojera continuar o tirar dado
                std::cout << std::endl;
            }else{
                std::cin >> opcion;
            }
            switch (opcion){

                case 1:
                    std::cout << "El jugador "<<jugador.getColor()<<jugador.getName()<<ANSI_RESET<<" tiro el dado...\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
                case 2:
                  
                    gameOver=true;
                    limpiar();
                break;
                case 3:
                  
                    std::cout << "Saliendo del juego...\n";
                    exit(EXIT_SUCCESS);
                break;
                default:
                    std::cout << "Opción inválida. El juego continuara con normalidad \n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            }
    }
};