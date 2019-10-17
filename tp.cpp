#include <iostream>
#include <string.h>
using namespace std;

void presentaParticipante(char nombre[]);
void reglamento();
void introduccion();
void sigCategoria();

struct Participante{
    char nombre[50];
    int turnos = 5;
    int puntaje = 0;
};

struct NodoCategorias{
    Historia info;
    Deportes info;
    Cultura info;
    Ciencia info;
    Geografia info;
    Entretenimiento info;
    Random info;
}

int main(){

    //Falta abrir todos los archivos!

    fopen catHistoria = ("historia.dat", "rb");
    fopen catDeportes = ("deportes.dat", "rb");
    fopen catCultura = ("cultura.dat", "rb");
    fopen catGeografia = ("geografia.dat", "rb");
    fopen catEntretenimiento = ("entretenimiento.dat", "rb");
    fopen catCiencia = ("ciencia.dat", "rb");
    fopen catRandom = ("random.dat", "rb");

    char partidaNueva;
    cout<<"Desea cargar una partida nueva? (s/n)"<<endl;
    cin>>partidaNueva;
    while(partidaNueva!='s'&&partidaNueva!='n'){
        cout<<"Caracter incorrecto. Ingrese s o n"<<endl;
        cin>>partidaNueva;
    }    
    if(partidaNueva=='s'){
       //Falta el delete de los archivos anteriores
       introduccion();    
       Participante participantes[5];    //Array de Structs para Participantes
       char nombreParticipante[50];
       cout << "Participantes, ingresen sus nombres: ";
       for(int i = 0; i < 5; i++){
           cin.getline(nombreParticipante,50);        
           strcpy(paricipantes[i].nombre,nombreParticipante);
           presentaParticipante(nombreParticipante);
       }
    reglamento();    //Falta el armado del archivo de cada participante!!!(open rb+)
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

/*
funcion que inicialize el archivo con puntaje parcial e inicie con valor 0

funcion que sume puntaje

archivo de preguntas

funcion que elimine pregunta

funcion que elimine categoria

*/
