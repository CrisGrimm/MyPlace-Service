#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

const int ROOM_COST_PER_DAY = 100;
const int NUM_ROOMS = 4;//este valor tiene que ser const pq el tamaNo de el array no debe cambiar a lo largo de el programa
struct Habitacion {//esto es un array lleno de struct
        string name;
        bool ocupada;
    }bedrooms[NUM_ROOMS];
void showAvailableRooms(int NUM_ROOMS) {
    cout << "Cuartos disponibles:\n";
    for (int i = 0; i < NUM_ROOMS; i++) {
       
      cout << "Cuarto " << i << " esta disponible\n";
      
    }
}
int calcularCostoTotal(int dias, bool contiguo) {
    int costoTotal = ROOM_COST_PER_DAY * dias;
    if (contiguo) {
        costoTotal *= 2;
    }
    return costoTotal;
}
bool checkRoomAvailability(const  Habitacion bedrooms[], int roomNumber, int NUM_ROOMS) {
    if (roomNumber < 0 || roomNumber >= NUM_ROOMS) {
        cout << "Numero de habitación inválido." << endl;
        return false;
    }
    if (bedrooms[roomNumber].ocupada) {
        cout << "La habitacion " << roomNumber << " ya está ocupada." << endl;
        return false;
    }
    return true;
}

int main() {

    int roomNumber,choice,numb, totalCost, days;
    char contig;
    
    cout << "Bienvenido myPlace" << endl;

    while (true) {
        cout << "Elija una opción:\n";
        cout << "1. Reservar un cuarto\n";
        cout << "2. Salir\n";
        
        cin >> choice;

        if (choice == 2) {
            cout << "Gracias por visitarnos. ¡Hasta luego!" << endl;
            break;
        }

        if (choice == 1) {
            showAvailableRooms(NUM_ROOMS);

            cout << "Seleccione el numero del cuarto que desea reservar (0-" << NUM_ROOMS - 1 << "): ";
            cin >> roomNumber;

            if (!checkRoomAvailability(bedrooms, roomNumber, NUM_ROOMS)) {
                continue;
            }
            cout << "¿Desea reservar un cuarto contiguo (S/N)? ";

            cin >> contig;
            if (contig == 'S' || contig == 's') {
                cout << "Su habitacion escogida es la " << roomNumber << " y la puede combinar con las habitacion/es ";
                if (roomNumber + 1 >= NUM_ROOMS && roomNumber - 1 >= 0) {
                    cout << roomNumber - 1;
                }
                else if (roomNumber + 1 < NUM_ROOMS && roomNumber - 1 < 0) {
                    cout << roomNumber + 1;
                }
                else if (roomNumber + 1 < NUM_ROOMS && roomNumber - 1 >= 0) {
                    cout << roomNumber + 1 << " y " << roomNumber - 1;
                }

                do {
                    cout << endl<< "Entre con cual desea combinar: ";
                    cin >> choice;
                    if (bedrooms[choice].ocupada == true) {
                        cout << "La habitacion esta ocupada"<<endl;
                    }
                    else {
                        cout << "La habitacion esta disponible"<<endl;
                    }

                } while (choice != roomNumber + 1 && choice != roomNumber - 1);
                cout << "Usted ha reservado las habitaciones " << roomNumber << " y " << choice << endl;
                bedrooms[choice].ocupada = true;
                bedrooms[roomNumber].ocupada = true;
                cout << "Que nombre desea poner en las habitaciones"<<endl;
                cout << "Habitacion " << roomNumber << ":" << endl;
                cin >> bedrooms[roomNumber].name;
                cout << "Habitacion " << choice << ":" << endl;
                cin >> bedrooms[choice].name;
            }
            else {
                cout << "Usted ha reservado la habitacion " << roomNumber << endl;
                bedrooms[roomNumber].ocupada = true;
                cout << "Que nombre desea poner en la habitacion";
                cout << "Habitacion " << roomNumber << ":" << endl;
                cin >> bedrooms[roomNumber].name;
            }


        }
            cout << "¿Cuántos días se quedará? ";
            cin >> days;
            system("cls");
            calcularCostoTotal(days, contig);

       totalCost = ROOM_COST_PER_DAY * days;
            if (contig == 's' || contig == 'S') {

                
                cout << "El costo total por " << days << " días y dos habitaciones es: $" << calcularCostoTotal(days, contig) << endl;
                cout << "Su informacion ya esta en nuestro sistema con su nombre, por favro pase al mostrador"<<endl;
                //generate a file
                ofstream textFile("myPlace.txt");
                //write to the file
                textFile << "Las habitaciones escojidas son la " << roomNumber <<" y la "<<choice<< endl;
                textFile << "La misma le costara: " << calcularCostoTotal(days, contig) << endl;
                textFile << "Nombre de cuarto " << roomNumber << ": " << bedrooms[roomNumber].name;
                textFile << "Nombre de cuarto " << choice << ": " << bedrooms[choice].name;
                //close the file
                textFile.close();

            }
            else {
                cout << "El costo total por " << days << " días es: $" << calcularCostoTotal(days, contig) << endl;
                cout << "Su informacion ya esta en nuestro sistema con su nombre, por favro pase al mostrador" << endl;
                //generate a file
                ofstream textFile("myPlace.txt");
                //write to the file
                textFile << "La habiacion escojida es la " << roomNumber << endl;
                textFile << "La misma le costara" << calcularCostoTotal(days, contig) << endl;
                textFile << endl;
                //close the file
                textFile.close();
            }
            
        
            
    }

    return 0;
}
