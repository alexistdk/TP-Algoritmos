#include <iostream>
#include <string.h>
using namespace std;

void presentaParticipante(string nombre);

void reglamento();

int main(){

    cout << "Bienvenidos a ¿Quién quiere ser billonario?, el único programa que premia el conocimiento." << endl;
    
    cout << "Hoy tenemos a 5 participantes nuevos que competiran por el gran premio." << endl;

    string participante1;

    string participante2;

    string participante3;

    string participante4;

    string participante5;

    cout << "Participantes, ingresen sus nombres: ";

    cin >> participante1;

    presentaParticipante(participante1);

    cin >> participante2;

    presentaParticipante(participante2);

    cin >> participante3;

    presentaParticipante(participante3);

    cin >> participante4;

    presentaParticipante(participante4);

    cin >> participante5;

    presentaParticipante(participante5);

    reglamento();

    string Categorias[7] = {"Historia", "Deporte", "Arte", "Geografía", "Cultura", "Cine", "Series"};    

    return 0;
}

void presentaParticipante(string nombre){

    cout << "Bienvenido " << nombre << ", le deseamos mucha suerte!" << endl;
    
}

void reglamento(){

    cout << "Las reglas del juego son simples, son 7 categorias elegidas totalmente al azar. ";
    
    cout << "Cada participante tendrá 5 turnos y ganará el que más puntos tenga. ";
    
    cout << "En caso de empate, se hará una pregunta a cada participante hasta que uno se equivoque." << endl;

}