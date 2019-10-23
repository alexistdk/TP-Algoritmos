#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void presentaParticipante(char nombre[]);
void reglamento();
void introduccion();
int numeroAleatorio(int numMax);

struct Participante{
    char nombre[50];
    int turnos = 5;
    int puntaje = 0;
};
struct Categoria{                  //Cada Categoria
    Preguntas vecDatos[6];
    bool catUsada;
};

struct Respuesta{                  //Sirve para armar el vector y hacer el multiple choice.
    char caracter;
    char respuesta[200];
};

struct Preguntas{                  //La pregunta en si, con las supuestas respuestas (1 es la correcta) y el bool para marcar el uso.
    char pregunta[500];
    Respuesta vecRespuestas[4];
    char respuestaCorrecta;
    bool pregUsada;
};

struct NodoCola{			//Falta completar con la info del nodo
	NodoCola* colaFte;
	NodoCola* colaFin;
	
};

int main(){
    FILE* preguntas=fopen("preguntas.dat","rb");          //Preguntas que solo se leen 
    FILE* preguntasAux=fopen("preguntasAux.dat","rb+");   //Aca se escriben las que se usaron
    FILE* participante1=fopen("participante1.dat","rb+");
    FILE* participante2=fopen("participante2.dat","rb+");
    FILE* participante3=fopen("participante3.dat","rb+");
    FILE* participante4=fopen("participante4.dat","rb+");
    FILE* participante5=fopen("participante5.dat","rb+");
    FILE* historico=("historico.dat","rb+");
    
    Categoria vecCategorias[7];
    char partidaNueva;
    cout<<"Desea cargar una partida nueva? (s/n)"<<endl;
    cin>>partidaNueva;
    while(partidaNueva!='s'&&partidaNueva!='n'&&partidaNueva!='S'&&partidaNueva!='N'){
        cout<<"Caracter incorrecto. Ingrese s o n"<<endl;
        cin>>partidaNueva;
    }    
    if(partidaNueva=='s'){
       //remove del archivo 
       introduccion();    
       Participante participantes[5];                       //Array de Structs para Participantes
       char nombreParticipante[50];
       cout << "Participantes, ingresen sus nombres: ";
       for(int i = 0; i < 5; i++){
	   cout<<"Participante ",(i+1)
           cin.getline(nombreParticipante,50);    
           strcpy(paricipantes[i].nombre,nombreParticipante);
           presentaParticipante(nombreParticipante);
       }
    reglamento();
    }                                            //Despues del if hay que armar la Cola para los turnos teniendo en cuenta a los turnos
    
    return 0;
}

void introduccion(){
    cout << "Bienvenidos a ¿Quién quiere ser billonario?, el único programa que premia el conocimiento." << endl;
    cout << "Hoy tenemos a 5 participantes nuevos que competiran por el gran premio." << endl;
}

void presentaParticipante(char nombre[]){
    cout << "Bienvenido " << nombre << ", le deseamos mucha suerte!" << endl;
}

void reglamento(){
    cout << "Las reglas del juego son simples, son 7 categorias elegidas totalmente al azar. ";    
    cout << "Cada participante tendrá 5 turnos y ganará el que más puntos tenga. ";
    cout << "En caso de empate, se hará una pregunta a cada participante hasta que uno se equivoque." << endl;
}

int numeroAleatorio(int numMax){
    int c;
    srand(time(NULL));
	c=1+rand()%numMax;
	return c;
}    

/*
funcion que inicialize el archivo con puntaje parcial e inicie con valor 0

funcion que sume puntaje

archivo de preguntas

funcion que elimine pregunta

funcion que elimine categoria

*/
