#include "Arduino.h"
#include "MSerial.h"

//-----------------------------------------------------------
// CONSTRUCTORES Y DESTRUCTORES
//-----------------------------------------------------------
 
MSerial::MSerial(){
    NDatDep       = 0; 
    DatosDep      = (float*)malloc(10*sizeof(float));  //PONER SEGURIDAD A LOS MALLOC!!!!!!
    MaxTamBuffer  = 100;
    Datos         = (int*)malloc(50*sizeof(int)); //PONER SEGURIDAD A LOS MALLOC!!!!!!
    MBuffer       = 0;
}

MSerial::MSerial(int MaxTam){
    NDatDep       = 0; 
    DatosDep      = (float*)malloc((MaxTam/2)*sizeof(float));
    MaxTamBuffer  = MaxTam;
    Datos         = (int*)malloc(MaxTam*sizeof(int)); 
    MBuffer       = 0;
  
}


// Falta poner los destructores: Depurar esta parte
MSerial::~MSerial(){
	//delete Datos;
	//delete DatosDep;
}

//-----------------------------------------------------------
// PUBLIC
//-----------------------------------------------------------

int MSerial::GetSerialNum(float *&DatosDepurados){
    MBuffer=0;
    if(Serial.available()>0){
        Datos[MBuffer] = Serial.read();
        while(Serial.available()>0 && Datos[MBuffer] != 124 && MBuffer< MaxTamBuffer){
          
//          Serial.print("|"); 
//          Serial.print(Datos[MBuffer]);  
//          Serial.print("|");  
          // Debug
          MBuffer++;
          Datos[MBuffer] = Serial.read();
        }  
        DepDatNum();
//        InvertirDat();   		     // Fuente de errores
        DatosDepurados = DatosDep;   // Se apunta el puntero al array obtenido   
        return NDatDep;              // Se devuelve el numero de datos leidos
    }
    else
      return -1; // Si no se ha leido nada por Pto Serie ser responde error
}

//-----------------------------------------------------------
//  PRIVATE
//-----------------------------------------------------------

void MSerial::DepDatNum(){
  float num		= 0.0				;
  int   flagSig	= 1, 	PosUoD	=0	;
  NDatDep 		= 0;  
  
  for(int j=MBuffer;j>=0;j--){
      if( Datos[j]== 45 )flagSig=-1;          			// signo menos
      
      else if(Datos[j] >=  48 && Datos[j] <=  57){		//Si es un numero del uno al nueve   
        num +=(Datos[j]-48)*pow(10.0,PosUoD);         
        PosUoD++;
      }
      else if(Datos[j] == 46 || Datos[j] == 44){		//Si empieza la parte entera todo lo anterior era decimal Se acepta el punto y la coma
        num = num/pow(10.0,PosUoD);          
        PosUoD = 0;        
      };
      //------------Si ha llegado al fin de la cadena o empieza el siguiente: Dato se guarda.('|'-> es el caracter de fin de cadena)
      if(Datos[j] == 32 || j == 0){
        DatosDep[NDatDep] = num*flagSig;   
        // Debug    
//        Serial.print("\ndatodepurado dentro de la funcion depurar:");
//        Serial.print(DatosDep[NDatDep]); 
        // Debug   
        NDatDep++;    
        flagSig = 1;
        PosUoD  = 0;
        num     = 0.0;
      };
  }//for
}//funcion  

void MSerial::InvertirDat(){
	int i,j;
	float *aux= (float*)malloc(sizeof(float)*NDatDep); //PONER SEGURIDAD A LOS MALLOC!!!
	
	for(i=0, j =1; i<NDatDep ;i++,j++){
		aux[i] = DatosDep[NDatDep-j];
	}
	DatosDep = aux;
	free(aux);
}

double MSerial::pow(double base,double exponente){
  double total = base;
  for(int i = 1;i<exponente;i++)total = total*base;
  if(exponente==0)total = 1;
  return total;
}




