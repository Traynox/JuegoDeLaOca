class CasillaEspecial {
private:
    int valor;
    char letra;
public:
    CasillaEspecial(int valor, char letra) : valor(valor), letra(letra) {}

    void setValor( int newValor){
        valor = newValor;
    }
    int getValor(){
        return valor;
    }
    void setLetra( char newLetra) {
        letra = newLetra;
    }
    char getLetra(){
        return letra;
    }
};