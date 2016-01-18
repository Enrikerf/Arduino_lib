#ifndef MSerial_h
#define MSerial_h
#include"Arduino.h"

class MSerial{
  public:
    MSerial();        // Constructor por defecto (filtra 30 Caract ASCII
		      // como máximo y para obtener 5 float como máximo
//----------------------------------------------------------------------					  
    MSerial(int Tam); // Redefinir la cantidad(Tam) de Caract ASCII que
	              // es capaz de filtrar: para Tam/2 floats
//----------------------------------------------------------------------   
    int GetSerialNum(float *&DatosDepurados);
    // DatosDepurados: puntero a los floats obtenidos
    // Return: numero de floats leidos.
//----------------------------------------------------------------------
    ~MSerial();
private:  
    int NDatDep;// Numero de datos depurados
    float *DatosDep;  // Datos depurados
    int MaxTamBuffer,*Datos;// Maximo de datos ASCII, Buffer de Datos 
							// ASCII leidos
    int MBuffer;            // Manejador que recorre el buffer llenandolo
//---------------------------------------------------
    void DepDatNum();// Convierte a float los datos del cogido ASCII adquirido por Pto Serie
    void InvertirDat();// los datos se depuran al reves por lo que hay que invertirlos
    double pow(double base, double exponente); // función potencia de math.h, para no incluir entera la librería.
       
};
#endif

