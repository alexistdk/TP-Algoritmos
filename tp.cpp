#include <iostream>
#include <string.h>
using namespace std;

void presentaParticipante(string nombre);

void reglamento();

void introduccion();

int main(){
    
    string Categorias[7] = {"Historia", "Deporte", "Arte", "Geografía", "Cultura", "Entretenimiento", "Ciencia"};    
    
    string Participantes[5] = {"Participante1", "Participante2", "Participante3", "Participante4", "Participante5"};

    string nombreParticipante;

    introduccion();

    cout << "Participantes, ingresen sus nombres: ";

    for(int i = 0; i < 5; i++){

        cin >> nombreParticipante;

        Participantes[i] = nombreParticipante;

        presentaParticipante(nombreParticipante);
    }

    reglamento();


    return 0;
}

void introduccion(){

    cout << "Bienvenidos a ¿Quién quiere ser billonario?, el único programa que premia el conocimiento." << endl;
    
    cout << "Hoy tenemos a 5 participantes nuevos que competiran por el gran premio." << endl;

}

void presentaParticipante(string nombre){

    cout << "Bienvenido " << nombre << ", le deseamos mucha suerte!" << endl;
    
}

void reglamento(){

    cout << "Las reglas del juego son simples, son 7 categorias elegidas totalmente al azar. ";
    
    cout << "Cada participante tendrá 5 turnos y ganará el que más puntos tenga. ";
    
    cout << "En caso de empate, se hará una pregunta a cada participante hasta que uno se equivoque." << endl;

}
