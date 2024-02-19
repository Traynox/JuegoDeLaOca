#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include "../models/Estructuras.h"

class Archivos {
    private:
        std::string nombreArchivo;

    public:
        Archivos(const std::string& nombreArchivo) : nombreArchivo(nombreArchivo) {}

    bool existeFile(){
        std::ifstream archivo(nombreArchivo);
        return archivo.is_open();
    }

    void guardarPuntuaciones(const std::vector<std::tuple<std::string, std::string, int>> &puntuaciones) {
        std::ofstream archivo(nombreArchivo, std::ios::app);
        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ". Creando nuevo archivo..." << std::endl;
            archivo.open(nombreArchivo);
            if (!archivo.is_open()) {
                std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
                return;
            }
        }

        for (const auto& punt : puntuaciones) {
            archivo << std::get<0>(punt) << "," << std::get<1>(punt) << "," << std::get<2>(punt)<< std::endl;
        }
        std::cout << "Datos guardados correctamente en " << nombreArchivo << std::endl;
    }

    bool jugadorExiste(const std::string& nombre) {
        
        std::ifstream archivo(nombreArchivo);
        std::string linea;

        if (!archivo.is_open()) {
           
            return false;
        }

        while (std::getline(archivo,linea)) {
            // Si se encuentra el correo en el archivo, el jugador existe
            std::istringstream iss(linea);
         
            std::string correo,nombreEnArchivo;
            int puntos;
            std::getline(iss, correo, ',');
            std::getline(iss, nombreEnArchivo, ',');

            iss >> puntos;
          

            if (nombreEnArchivo == nombre) {
                archivo.close();
                return true;
            }

           
        }
        archivo.close();
        return false;
    }

    std::string getJugadorCorreo(const std::string& nombre) {
        std::ifstream archivo(nombreArchivo);
        std::string CorreoLeido;

        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo " << nombreArchivo << " para leer" << std::endl;
            return "";
        }

        while (archivo >> CorreoLeido) {
            // Si se encuentra el correo en el archivo, el jugador existe
            if (CorreoLeido == nombre) {
                archivo.close();
                return CorreoLeido;
            }

            // Descartar el correo y la puntuación
            std::string nombre;
            int puntuacion;
            archivo >> nombre >> puntuacion;
        }
        archivo.close();
        return "";
    }

    bool actualizarPuntos(const std::string& nombre, int puntos_nuevos) {
        std::ifstream archivo_lectura(nombreArchivo);
        std::ofstream archivo_escritura("temp.txt"); // Archivo temporal para escribir los cambios
        
        if (!archivo_lectura.is_open() || !archivo_escritura.is_open()) {
            std::cerr << "Error al abrir el archivo." << std::endl;
            return false;
        }
        
        std::string linea;
        bool jugador_encontrado = false;

        while (std::getline(archivo_lectura, linea)) {
            std::istringstream iss(linea);
            std::string correo, nombreEnArchivo;
            int puntos;
            std::getline(iss, correo, ',');
            std::getline(iss, nombreEnArchivo, ',');
            iss >> puntos;
            
            if (nombreEnArchivo == nombre) {
                // Actualizar los puntos para este jugador
                archivo_escritura << correo << ',' << nombreEnArchivo << ',' << (puntos_nuevos+=puntos)<<"\n";
                jugador_encontrado = true;
            } else {
                // Mantener la línea sin cambios
                archivo_escritura << linea << '\n';
            }
        }

        archivo_lectura.close();
        archivo_escritura.close();

        // Eliminar el archivo original y renombrar el temporal
        if (remove(nombreArchivo.c_str()) != 0) {
            std::cerr << "Error al eliminar el archivo original." << std::endl;
            return false;
        }
        if (rename("temp.txt", nombreArchivo.c_str()) != 0) {
            std::cerr << "Error al renombrar el archivo temporal." << std::endl;
            return false;
        }

        if (!jugador_encontrado) {
            std::cerr << "El jugador no fue encontrado." << std::endl;
            return false;
        }

    return true;
}

    // Función de comparación para ordenar las puntuaciones en orden descendente
    bool static compararPuntuaciones(const Puntuacion& a, const Puntuacion& b) {
        return a.puntuacion > b.puntuacion; // Orden descendente
    }

    // Función para mostrar las puntuaciones en orden descendente
    void mostrarPuntuaciones() {
        
    // Cargar las puntuaciones
        std::vector<Puntuacion> puntuaciones = cargarPuntuaciones();
    // Ordenar las puntuaciones en orden descendente
        std::sort(puntuaciones.begin(), puntuaciones.end(), compararPuntuaciones);

    // Mostrar las puntuaciones en orden descendente
        std::cout << "Puntuaciones:" << std::endl;
        for (const auto& punt : puntuaciones) {
           
            std::cout <<"Nombre: " << punt.nombre << ", Puntuacion: " << punt.puntuacion << std::endl;
        }
    }

    // Función para cargar las puntuaciones desde un archivo
    std::vector<Puntuacion> cargarPuntuaciones() {
        
        std::vector<Puntuacion> puntuaciones;
        std::ifstream archivo_lectura(nombreArchivo);
        
        std::string correo, nombre, linea;
        int puntuacion;

        while (std::getline(archivo_lectura, linea)) {
            
            std::istringstream iss(linea);
            std::string correo, nombreEnArchivo;
         
            std::getline(iss, correo, ',');
            std::getline(iss, nombre, ',');
            iss >> puntuacion;   
            puntuaciones.push_back({correo, nombre, puntuacion});
        }

        return puntuaciones;
    }



};
