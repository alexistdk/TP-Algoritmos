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
    int turnos;
    int puntaje;
    int identificador;	
};
struct Categoria{                  //Cada Categoria
    Preguntas vecDatos[6];
};

struct Respuesta{                  //Sirve para armar el vector y hacer el multiple choice.
    char opcion;
    char respuesta[200];
};

struct Preguntas{                  //La pregunta en si, con las supuestas respuestas (1 es la correcta) y el bool para marcar el uso.
    char pregunta[500];
    Respuesta vecRespuestas[4];
    char respuestaCorrecta;
    bool respCorrecta;
};

struct NodoCola{			//Esta bien la info del nodo?
	NodoCola* sig;
	Participante info;	
};

int main(){
    FILE* preguntas=fopen("preguntas.dat","rb");          //Preguntas que solo se leen 
    FILE* preguntasAux=fopen("preguntasAux.dat","rb+");   //Aca se escriben las que se usaron
    FILE* participantes=fopen("participantes.dat","rb+");
    FILE* historico=("historico.dat","rb+");
    
    Categoria vecCategorias[7];    //Vector donde se cargan las preguntas y despues se comparan con el archivo aux 
    Categoria regCategoria;
    Participante participantes[5];
    Participante regParticipante;
    for(int i=0;i<7;i++){
	regCategoria=fread(&aux,sizeof(Categoria),1,preguntas);
	vecCategorias[i]=regCategoria;
    }
    char partidaNueva;
    cout<<"Desea cargar una partida nueva? (s/n)"<<endl;
    cin>>partidaNueva;
    while(partidaNueva!='s'&&partidaNueva!='n'&&partidaNueva!='S'&&partidaNueva!='N'){
        cout<<"Caracter incorrecto. Ingrese s o n"<<endl;
        cin>>partidaNueva;
    }    
    if(partidaNueva=='s'){
       remove("preguntasAux.dat");
       remove("participantes.dat");
       remove("historico.dat");
       FILE* participantes=fopen("participante1.dat","rb+");
       FILE* preguntasAux=fopen("preguntasAux.dat","rb+");
       FILE* historico=fopen("historico.dat","rb+");
       introduccion();                     
       char nombreParticipante[50];
       cout << "Participantes, ingresen sus nombres: ";
       for(int i = 0; i < 5; i++){
	   cout<<"Participante ",(i+1),": "<<endl;
           cin.getline(nombreParticipante,50);
	   presentaParticipante(nombreParticipante);
           strcpy(regParticipante.nombre,nombreParticipante);
           regParticipante.turnos=5;
	   regParticipante.puntaje=0;
	   regParticipante.identificador=i+1;
	   fwrite(&regParticipante,sizeof(Participante),1,participantes);
	   vecParticipantes[i]=regParticipante;
       }
    reglamento();
    }else{
	 for(int i=0;i<5;i++){
		 regParticipante=fread(&regParticipante,sizeof(Participante),1,participantes);
		 vecParticipantes[i]=regParticipante;
	 }
	 while(!feof(preguntasAux)){
		 fread(&regCategorias,sizeof(Categoria),1,preguntasAux);
	 }
    }
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
