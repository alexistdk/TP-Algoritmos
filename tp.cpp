#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
using namespace std;

struct Participante{
    char nombre[50];
    int turnos;
    int puntaje;
    int sigParticipante;		
};

struct Respuesta{
    char opcion;
    char respuesta[200];
};

struct Preguntas{
    char pregunta[500];
    Respuesta vecRespuestas[4];
    char respuestaCorrecta;
    int indicePreg;
    int indiceCat;
    bool respCorrecta;
    bool pregUsada;
};

struct Categoria{
	char nombreCategoria[20];
    Preguntas vecDatos[6];
    int indiceCat;
    bool catUsada;
};

struct Lista{
	char pregunta[500];
	Respuesta vecRespuestas[4];
	char respuestaCorrecta;
	char respuestaUsuario;
	Participante datosParticipante;
};

struct Nodo{
	Nodo* sig;
	Lista info;	
};

void presentaParticipante(char nombre[]);
void reglamento();
void introduccion();
int numeroAleatorio(int numMax);
void agregarNodo(Nodo*& lista,Lista datos);
int recuperaParticipanteUltTurno(Nodo*& lista);
void hacerPregunta(Categoria& vec);

int main(){
    FILE* preguntas=fopen("preguntas.dat","rb");          //Preguntas que solo se leen 
    FILE* preguntasAux=fopen("preguntasAux.dat","rb+");   //Aca se escriben las que se usaron
    FILE* participantes=fopen("participantes.dat","rb+");
    FILE* historico=fopen("historico.dat","rb+");
    
    Categoria vecCategorias[7];    //Vector donde se cargan las preguntas y despues se comparan con el archivo aux 
    Categoria regCategoria;
    Participante vecParticipantes[5];
    Participante regParticipante;
    Preguntas regPreguntas;
    Lista regHistorico;
    Nodo* lista=NULL;
    for(int i=0;i<7;i++){
	fread(&regCategoria,sizeof(Categoria),1,preguntas);
	vecCategorias[i]=regCategoria;
    }
    int posTurno;
    char partidaNueva;
    cout<<"Desea cargar una partida nueva? (s/n)"<<endl;
    cin>>partidaNueva;
    while(partidaNueva!='s'&&partidaNueva!='n'&&partidaNueva!='S'&&partidaNueva!='N'){
        cout<<"Caracter incorrecto. Ingrese s o n"<<endl;
        cin>>partidaNueva;
    }    
    if(partidaNueva=='s'||partidaNueva=='S'){
       remove("preguntasAux.dat");
       remove("participantes.dat");
       remove("historico.dat");
       FILE* participantes=fopen("participante1.dat","rb+");
       FILE* preguntasAux=fopen("preguntasAux.dat","rb+");
       FILE* historico=fopen("historico.dat","rb+");
       introduccion();                     
       char nombreParticipante[50];
       cout << "Participantes, ingresen sus nombres: "<<endl;
       cin.ignore();
       for(int i = 0; i < 5; i++){
	       cout<<"Participante "<<i+1<<": ";
           cin.getline(nombreParticipante,50);
	       presentaParticipante(nombreParticipante);
           strcpy(regParticipante.nombre,nombreParticipante);
           regParticipante.turnos=5;
	       regParticipante.puntaje=0;
	       regParticipante.sigParticipante=i+1;
	       if(regParticipante.sigParticipante==5){
	   	      regParticipante.sigParticipante=0;
	        }
	        fwrite(&regParticipante,sizeof(Participante),1,participantes);
	   		vecParticipantes[i]=regParticipante;
    	}
    	posTurno=0;
    	reglamento();
    }else{
	   for(int i=0;i<5;i++){
		 fread(&regParticipante,sizeof(Participante),1,participantes);
		 vecParticipantes[i]=regParticipante;
	    }
	    fread(&regPreguntas,sizeof(Preguntas),1,preguntasAux);
	    while(!feof(preguntasAux)){
			vecCategorias[regPreguntas.indiceCat].vecDatos[regPreguntas.indicePreg].pregUsada=false;
			fread(&regPreguntas,sizeof(Preguntas),1,preguntasAux);
        }
        for(int i=0;i<7;i++){
        	int contador=0;
        	for(int j=0;j<6;j++){
        		if(!vecCategorias[i].vecDatos[j].pregUsada){
        			contador++;
				}
			}
			if(contador==6){
				vecCategorias[i].catUsada=false;
			}
		}
		fread(&regHistorico,sizeof(Lista),1,historico);
		while(!feof(historico)){
			agregarNodo(lista,regHistorico);
			fread(&regHistorico,sizeof(Lista),1,historico);
		}
		posTurno=recuperaParticipanteUltTurno(lista);
	}
	while(vecParticipantes[0].turnos!=0&&vecParticipantes[1].turnos!=0&&vecParticipantes[2].puntaje!=0&&vecParticipantes[3].turnos!=0&&vecParticipantes[4].turnos!=0){
		
	}
	
	
    return 0;
}

void introduccion(){
    cout << "Bienvenidos a ¿Quien quiere ser billonario?, el unico programa que premia el conocimiento." << endl;
    cout << "Hoy tenemos a 5 participantes nuevos que competiran por el gran premio." << endl;
}

void presentaParticipante(char nombre[]){
    cout << "Bienvenido " << nombre << ", le deseamos mucha suerte!" << endl;
}

void reglamento(){
    cout << "Las reglas del juego son simples, son 7 categorias elegidas totalmente al azar. ";    
    cout << "Cada participante tendra 5 turnos y ganara el que mas puntos tenga. ";
    cout << "En caso de empate, se hara una pregunta a cada participante hasta que uno se equivoque." << endl;
}

int numeroAleatorio(int numMax){
    int c;
    srand(time(NULL));
	c=rand()%numMax;
	return c;
}    

void agregarNodo(Nodo*& lista,Lista datos){
	Nodo* p=new Nodo();
	Nodo* aux=lista;
	p->info=datos;
	p->sig=NULL;
	if(lista==NULL){
		lista=p;
	}else{
		while(aux->sig!=NULL){
			aux=aux->sig;
		}
		aux=aux->sig;
	}
	aux->sig=p;
}

int recuperaParticipanteUltTurno(Nodo*& lista){
	int resultado;
	Nodo* aux=lista;
	while(aux!=NULL){
		aux=aux->sig;
	}
	resultado=aux->info.datosParticipante.sigParticipante;
	return resultado; 
}

void hacerPregunta(Categoria& vecCategorias[7],Participante& vecParticipantes[4],int& posTurno){
	int noMasPreguntas=0;
	int numCategoria;
	int numPregunta;
	int participanteActual;
	char respuestaPart
	for(int i=0;i<7;i++){
		if(!vec[i].catUsada){
			noMasPreguntas++;
		}
	}
	if(noMasPreguntas!=7){
		numCategoria=numeroAleatorio(7);
	    while(!vec[numCategoria].catUsada){
		numCategoria=numeroAleatorio(7);
	    }
	    numPregunta=numeroAleatorio(6);
		while(!vec[numCategoria].vecDatos[numPregunta].pregUsada){
		numPregunta=numeroAleatorio(6);
		}
		cout<<"Categoria: "<<vecCategoria[numCategoria].nombreCategoria;
		cout<<"La pregunta es la siguiente: "<<endl;
		cout<<vec[numCategoria].vecDatos[numPregunta].pregunta<<endl;
		for(int i=0;i<4;i++){
			cout<<vec[numCategoria].vecDatos[numPregunta].vecRespuestas[i].opcion<<
			". "<<vec[numCategoria].vecDatos[numPregunta].vecRespuestas[i].respuesta<<endl;
		}
		cout<<"Su opcion: "<<endl;
		cin>>respuestaPart;
		while(respuestaPart!='a'&&respuestaPart!='A'&&respuestaPart!='b'&&respuestaPart!='B'
		&&respuestaPart!='c'&&respuestaPart!='C'&&respuestaPart!='d'&&respuestaPart!='D'){
			cout<<"Opcion no existente. Elija a, b, c, d: "<<endl;
			cin>>respuestaPart;
		}
		if(strcmp(respuestaPart,vec[numCategoria].vecDatos[numPregunta].respuestaCorrecta)){
			cout<<"Respuesta Correcta!!"<<endl;
			vecParticipantes[posTurno].puntaje++;
		}else{
			cout<<"Respuesta Incorrecta :(. La respuesta correcta era la "
			<<vec[numCategoria].vecDatos[numPregunta].respuestaCorrecta<<"."<<endl;
		}
		vecParticipantes[posTurno].turnos--;
		posTurno=vecParticipantes[posTurno].sigParticipante;		
	}else{
		cout<<"No hay mas preguntas capo, cerra el juego y hace una partida nueva"<<endl;
	}	
}

