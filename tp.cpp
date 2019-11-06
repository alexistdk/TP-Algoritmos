#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>
using namespace std;

struct	Participante{
    char	nombre[50];
    int		turnos;
    int		puntaje;
    int 	sigParticipante;
	bool	empate;	
	int		identificador;	
};

struct	Respuesta{
    char	opcion;
    char 	respuesta[200];
};

struct	Preguntas{
    char		pregunta[500];
    Respuesta	vecRespuestas[4];
    char 		respuestaCorrecta;
    int 		indicePreg;
    int 		indiceCat;
    bool 		pregUsada;
};

struct	Categoria{
	char 		nombreCategoria[20];
    Preguntas 	vecDatos[6];
    int 		indiceCat;
    bool 		catUsada;
};

struct	Lista{
	char 			pregunta[500];
	Respuesta		vecRespuestas[4];
	char 			respuestaCorrecta;
	char			respuestaUsuario;
	Participante	datosParticipante;
	char 			horario[9];
};

struct	Nodo{
	Nodo*	sig;
	Lista 	info;	
};

void	presentaParticipante(char	nombre[]);
void 	reglamento();
void 	introduccion();
int 	numeroAleatorio(int	numMax);
void 	agregarNodo(Nodo*&	lista,	Lista	datos);
int 	recuperaParticipanteUltTurno(Nodo*&	lista);
Preguntas 	hacerPregunta(Categoria vecCategorias[], Participante vecParticipantes[],int posTurno,char& respUsuario);
char	elijeRespuesta();
bool	resultadoRta(Categoria vecCategorias[], char	respuestaPart, int	numCategoria, int numPregunta, Participante	vecParticipante[], int&	posTurno);
void	sgtePregunta(Categoria vecCategorias[], int numPregunta, int numCategoria);
void	bastaDePreguntas(int noMasPreguntas, int numCategoria, int numPregunta, Categoria vecCategorias[], Participante vecParticipantes[], int& posTurno, char respuestaPart);
void mostrarPuntajes(Participante vecParticipantes[]);
int hayEmpate(Participante vecP[],Participante vecE[]);
void mostrarLista(Nodo* lista);
void horarioPC(char horario[]);



int 	main(){
    FILE* preguntas = fopen("preguntas.dat","rb");          //Preguntas que solo se leen 
    FILE* preguntasAux = fopen("preguntasAux.dat","rb+");   //Aca se escriben las que se usaron
    FILE* participantes = fopen("participantes.dat","rb+");
    FILE* historico = fopen("historico.dat","rb+");
    
    Categoria vecCategorias[7];    //Vector donde se cargan las preguntas y despues se comparan con el archivo aux 
    Categoria regCategoria;
    Participante vecParticipantes[5];
    Participante vecEmpate[5];
    Participante regParticipante;
    Participante regParticipante2;
    Preguntas regPreguntas;
    Lista regHistorico;
    Nodo* lista=NULL;
    int contador;
    int lenEmpate;
    char nombreParticipante[50];
    int numero;

    for(int i=0;i<7;i++){
		fread(&regCategoria,sizeof(Categoria),1,preguntas);
		vecCategorias[i]=regCategoria;
    }
    int posTurno;
    char partidaNueva;
    char respUsuario;
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
       cout << "Participantes, ingresen sus nombres: "<<endl;
       cin.ignore();
       for(int i = 0; i < 5; i++){
	       cout<<"Participante "<<i+1<<": ";
           cin.getline(nombreParticipante,50);
	       presentaParticipante(nombreParticipante);
           strcpy(regParticipante.nombre,nombreParticipante);
           regParticipante.turnos=5;
	       regParticipante.puntaje=0;
	       regParticipante.empate=false;
	       regParticipante.identificador=i;
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
        	contador=0;
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
	while(vecParticipantes[0].turnos!=0&&vecParticipantes[1].turnos!=0&&vecParticipantes[2].puntaje!=0&&
		  vecParticipantes[3].turnos!=0&&vecParticipantes[4].turnos!=0){
		regPreguntas=hacerPregunta(vecCategorias,vecParticipantes,posTurno,respUsuario);
		fwrite(&regPreguntas,sizeof(Preguntas),1,preguntasAux);
		horarioPC(regHistorico.horario);
		regHistorico.datosParticipante=vecParticipantes[posTurno];
		strcpy(regHistorico.pregunta,regPreguntas.pregunta);
		regHistorico.respuestaCorrecta=regPreguntas.respuestaCorrecta;
		regHistorico.respuestaUsuario=respUsuario;
		for(int i=0;i<4;i++){
			regHistorico.vecRespuestas[i]=regPreguntas.vecRespuestas[i];
			agregarNodo(lista,regHistorico);
		}
		fwrite(&regHistorico,sizeof(Lista),1,historico);
		regParticipante=vecParticipantes[posTurno];
		rewind(participantes);
		if(posTurno==0){
			fwrite(&regParticipante,sizeof(Participante),1,participantes);
		}else{
			fread(&regParticipante2,sizeof(Participante),1,participantes);
			while(regParticipante2.sigParticipante!=regParticipante.sigParticipante-1){
				fread(&regParticipante2,sizeof(Participante),1,participantes);
			}
		fwrite(&regParticipante,sizeof(Participante),1,participantes);
		}
		posTurno=regParticipante.sigParticipante;
		mostrarPuntajes(vecParticipantes);
		cout<<"1: Ver historial de partida"<<endl;
		cin>>numero;
		if(numero==1){
			mostrarLista(lista);
		}
		cout<<"Presione una tecla para continuar..."<<endl;
		getch();
		system("CLS");
	}
	lenEmpate=hayEmpate(vecParticipantes,vecEmpate);
	if(lenEmpate>1){					
		cout<<"Hay "<<lenEmpate<<"jugadores empatados. Se debera desempatar a muerte subita."<<endl;
		for(int i=0;i<lenEmpate;i++){
			vecEmpate[i].sigParticipante=i+1;
			if(i==lenEmpate-1){
				vecEmpate[i].sigParticipante=0;
			}
		}
		posTurno=0;
		contador=lenEmpate;
		while(contador>1){
			if(vecEmpate[posTurno].empate){
				regPreguntas=hacerPregunta(vecCategorias,vecEmpate,posTurno,respUsuario);
				horarioPC(regHistorico.horario);
				fwrite(&regPreguntas,sizeof(Preguntas),1,preguntasAux);
				if(regPreguntas.respuestaCorrecta!=respUsuario){
					vecEmpate[posTurno].empate=false;
					contador--;
				}
				regHistorico.datosParticipante=vecEmpate[posTurno];
				strcpy(regHistorico.pregunta,regPreguntas.pregunta);
				regHistorico.respuestaCorrecta=regPreguntas.respuestaCorrecta;
				regHistorico.respuestaUsuario=respUsuario;
				for(int i=0;i<4;i++){
					regHistorico.vecRespuestas[i]=regPreguntas.vecRespuestas[i];
					agregarNodo(lista,regHistorico);
				}
				fwrite(&regHistorico,sizeof(Lista),1,historico);
				regParticipante=vecEmpate[posTurno];
				rewind(participantes);
				if(posTurno==0){
					fwrite(&regParticipante,sizeof(Participante),1,participantes);
				}else{
					fread(&regParticipante2,sizeof(Participante),1,participantes);
					while(regParticipante2.sigParticipante!=regParticipante.sigParticipante-1){
						fread(&regParticipante2,sizeof(Participante),1,participantes);
					}
					fwrite(&regParticipante,sizeof(Participante),1,participantes);
				}
				posTurno=regParticipante.sigParticipante;
				mostrarPuntajes(vecParticipantes);
				cout<<"1: Ver historial de partida"<<endl;
				cin>>numero;
				if(numero==1){
					mostrarLista(lista);
				}
				cout<<"Presione una tecla para continuar..."<<endl;
				getch();
				system("CLS");
			}else{
				posTurno=vecEmpate[posTurno].sigParticipante;
			}
		}
		for(int i=0;i<lenEmpate;i++){
			if(vecEmpate[i].empate){
				cout<<"El ganador es: "<<vecEmpate[i].nombre<<"-------- puntaje="<<vecEmpate[i].puntaje<<endl;
			}
		}
	}else{
		cout<<"El ganador es: "<<vecEmpate[0].nombre<<"-------- puntaje="<<vecEmpate[0].puntaje<<endl;
		cout<<"GRACIAS POR PARTICIPAR! ;)"<<endl;
	}
	fclose(participantes);
	fclose(historico);
	fclose(preguntas);
	fclose(preguntasAux);
    return 0;
}

void 	introduccion(){
    cout << "Bienvenidos a ¿Quien quiere ser billonario?, el unico programa que premia el conocimiento." << endl;
    cout << "Hoy tenemos a 5 participantes nuevos que competiran por el gran premio." << endl;
}

void 	presentaParticipante(char nombre[]){
    cout << "Bienvenido " << nombre << ", le deseamos mucha suerte!" << endl;
}

void 	reglamento(){
    cout << "Las reglas del juego son simples, son 7 categorias elegidas totalmente al azar. ";    
    cout << "Cada participante tendra 5 turnos y ganara el que mas puntos tenga. ";
    cout << "En caso de empate, se hara una pregunta a cada participante hasta que uno se equivoque." << endl;
}

int 	numeroAleatorio(int numMax){
    int c;
    srand(time(NULL));
	c	=	rand()%numMax;
	return c;
}    

void 	agregarNodo(Nodo*& lista,Lista datos){
	Nodo* p	=	new Nodo();
	Nodo* aux	=	lista;
	p->info	=	datos;
	p->sig	=	NULL;
	if(lista	==	NULL){
		lista	=	p;
	}else{
		while(aux->sig	!=	NULL){
			aux	=	aux->sig;
		}
		aux	=	aux->sig;
	}
	aux->sig	=	p;
}

int 	recuperaParticipanteUltTurno(Nodo*& lista){
	int resultado;
	Nodo* aux	=	lista;
	while(aux	!=	NULL){
		aux	=	aux->sig;
	}
	resultado	=	aux->info.datosParticipante.sigParticipante;
	return resultado; 
}

Preguntas 	hacerPregunta(Categoria vecCategorias[], Participante vecParticipantes[],int posTurno,char& respUsuario){
	int noMasPreguntas	=	0;
	int numCategoria;
	int numPregunta;
	int participanteActual;
	char respuestaPart;
	Preguntas regPregunta;
	for(int i=0; i<7; i++){
		if(!vecCategorias[i].catUsada){
			noMasPreguntas++;
		}
	}
	bastaDePreguntas(noMasPreguntas, numCategoria, numPregunta, vecCategorias, vecParticipantes, posTurno, respuestaPart);
	regPregunta=vecCategorias[numCategoria].vecDatos[numPregunta];
	respUsuario=respuestaPart;
	return regPregunta;
}

void	bastaDePreguntas(int noMasPreguntas, int numCategoria, int numPregunta, Categoria vecCategorias[],
		 Participante vecParticipantes[], int& posTurno, char respuestaPart){
	if(noMasPreguntas	!=	7){
		numCategoria	=	numeroAleatorio(7);
		while(!vecCategorias[numCategoria].catUsada){
			numCategoria	=	numeroAleatorio(7);
		}
		numPregunta	=	numeroAleatorio(6);
		while(!vecCategorias[numCategoria].vecDatos[numPregunta].pregUsada){
			numPregunta	=	numeroAleatorio(6);
		}
		sgtePregunta(vecCategorias, numPregunta, numCategoria);
		respuestaPart=elijeRespuesta();
		resultadoRta(vecCategorias, respuestaPart, numCategoria, numPregunta, vecParticipantes, posTurno);
		vecParticipantes[posTurno].turnos--;
		}	else	{
		cout	<<	"No hay mas preguntas capo, cerra el juego y empeza¡ una partida nueva"	<< endl;
	}
}

char	elijeRespuesta(){
	char respuestaPart;
	cout	<<	"Su opcion: "	<<	endl;
	cin		>>	respuestaPart;
	while(respuestaPart	!=	tolower('A')	&&	respuestaPart	!=	tolower('B')	&& 
		respuestaPart	!= 	tolower('C') 	&& 	respuestaPart 	!= 	tolower('D')){
			cout	<<	"Opcion inexistente. Elija a, b, c, d: "	<<	endl;
			cin	>>	respuestaPart;
	}
	return respuestaPart;
}

bool	resultadoRta(Categoria vecCategorias[], char	respuestaPart, int	numCategoria, int numPregunta, Participante	vecParticipante[], int&	posTurno){
	bool resultado;
	int cont=0;
	if(respuestaPart	==	vecCategorias[numCategoria].vecDatos[numPregunta].respuestaCorrecta){
		cout	<<	"Respuesta correcta!"	<<	endl;
		vecParticipante[posTurno].puntaje++;
		resultado=true;
	}	else	{
		cout	<<	"Respuesta incorrecta. La respueta correcta era la "
				<<	vecCategorias[numCategoria].vecDatos[numPregunta].respuestaCorrecta << "."	<<	endl;
		resultado=false;		
	}
	vecCategorias[numCategoria].vecDatos[numPregunta].pregUsada=false;
	for(int i=0;i<6;i++){
		if(vecCategorias[numCategoria].vecDatos[i].pregUsada=false){
			cont++;
		}
	}
	if(cont==6){
		vecCategorias[numCategoria].catUsada=false;
	}
	return resultado;
}

void	sgtePregunta(Categoria vecCategorias[], int numPregunta, int numCategoria){
	cout	<<	"Categoria: "	<<	vecCategorias[numCategoria].nombreCategoria;
	cout	<<	"La pregunta es la siguiente: "	<<	endl;
	cout	<<	vecCategorias[numCategoria].vecDatos[numPregunta].pregunta	<<	endl;
	for(int	i=0;	i<4;	i++){
		cout	<<	vecCategorias[numCategoria].vecDatos[numPregunta].vecRespuestas[i].opcion	<<
		".	"	<<	vecCategorias[numCategoria].vecDatos[numPregunta].vecRespuestas[i].respuesta	<<	endl;
	}
}

void		 	mostrarPuntajes(Participante vecParticipantes[]){
	for(int i=0;i<4;i++){
		cout<<"Puntaje "<<vecParticipantes[i].nombre<<": "<<vecParticipantes[i].puntaje<<endl;
	}
}

int hayEmpate(Participante vecP[],Participante vecE[]){
	int cont=0;
	int aux=-1;
	for(int i=0;i<5;i++){
		if(vecP[i].puntaje>aux){
			aux=vecP[i].puntaje;
		}
	}
	for(int i=0;i<5;i++){
		if(aux==vecP[i].puntaje){
			vecE[i]=vecP[i];
			vecE[i].empate=true;
			cont++;
		}
	}
	return cont;
}

void mostrarLista(Nodo* lista){
	Nodo* aux=lista;
	while(aux!=NULL){
		cout<<"Nombre: "<<aux->info.datosParticipante.nombre<<endl;
		cout<<"Pregunta: "<<aux->info.pregunta<<endl;
		cout<<"Respuesta escogida: "<<aux->info.respuestaUsuario<<endl;
		cout<<"Respuesta correcta: "<<aux->info.respuestaCorrecta<<endl;
		cout<<"Hora de respuesta: "<<aux->info.horario;
		cout<<"------------------------------------"<<endl;
		aux=aux->sig;
	}
	getch();
}

void horarioPC(char horario[]){
	SYSTEMTIME stHora;
    char hora[9];
    GetLocalTime(&stHora);
    GetTimeFormat(LOCALE_SYSTEM_DEFAULT,
                  TIME_FORCE24HOURFORMAT,
                  &stHora, "hh':'mm':'ss",
                  hora,
                  sizeof(hora));
    strcpy(horario,hora);
}
