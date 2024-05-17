#include <iostream>
#include <algorithm>
#include <stdlib.h>     
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int num_jugadores;
vector <string> jugadores;
string otra_vez;
bool salir;
bool correcto;
ifstream arch;

int puntuaciones[4][2] = {
						{0 ,0},
						{0 ,0},
						{0 ,0},
						{0 ,0}
						};
					
ifstream abrir_archivo (const string& nombre)
{
	ifstream arch;
	arch.open(nombre, ios::in);
	if (!arch.is_open())
	{
    	cerr << "No se pudo abrir el archivo." << endl;
		exit(0);
    }
	return arch;
}

void leer_definicion(int numero_pregunta)
{
	string definicion;
	string nombrearchivo = "definiciones.txt";

	ifstream archivo = abrir_archivo(nombrearchivo);

    int numeroActualLinea = 0;

    while (getline(archivo, definicion)) 
	{
        numeroActualLinea++;
        if (numeroActualLinea == numero_pregunta) 
		{
            cout << definicion << endl;
            break;
        }
    }

    archivo.close();
}

string leer_pista(int numero_pregunta)
{
	string pista;
	string linea;
	string nombrearchivo = "pistas.txt";

	ifstream archivo = abrir_archivo(nombrearchivo);
    int numeroActualLinea = 0;

    while (getline(archivo, linea)) 
	{
        numeroActualLinea++;
        if (numeroActualLinea == numero_pregunta) 
		{
            pista=linea;
            break;
        }
    }

    archivo.close();
	return pista;
}

void leer_respuesta(int numero_pregunta, string Respuesta)
{
	string respuesta_correcta;
	string nombrearchivo = "palabras_correctas.txt";

	ifstream archivo = abrir_archivo(nombrearchivo);

    int numeroActualLinea = 0;

    while (getline(archivo, respuesta_correcta)) {
        numeroActualLinea++;
        if (numeroActualLinea == numero_pregunta) {
            if (respuesta_correcta == Respuesta)
			{
				correcto=true;
			}
            break;
        }
    }

    archivo.close();
}

int modo1 (int x)
{	
	string palabra_usuario;
	string palabra_correcta;
	bool pista=false;
	int renglon;
	int ganador;
	int rango=30;
	int aleatorio;
	int ronda=0;
	srand(time(NULL));
	
	do
	{
		for (int turno=0 ; turno<x ; turno++)
		{
			pista=false;
			correcto=false;
			aleatorio=rand() % rango;
			cout<<"Ahora es el turno de "<<jugadores[turno]<<". A que palabra en ingles corresponde la siguiente definicion?:"<<endl;
			cout<<endl;
			leer_definicion(aleatorio);
			// palabra_correcta=directorio[aleatorio][0];
			cout<<endl;
			cout<<"ingresa tu respuesta (si necesitas una pista ingresa la palabra 'pista'):"<<endl;
			cin>>palabra_usuario;
			cout<<endl;
			
			if (palabra_usuario== "pista")
			{
				cout<<endl;
				cout<<"La palabra que tienes que adivinar, al traducirla al espanol es: "<< leer_pista(aleatorio) <<endl;
				pista=true;
				cout<<endl;
				
				cout<<"ahora si, ingresa tu respuesta final: "<<endl;
				cin>>palabra_usuario;
				cout<<endl;
				leer_respuesta(aleatorio, palabra_usuario);
			}

			else
			{
				leer_respuesta(aleatorio, palabra_usuario);
			}

			if( correcto==true and pista==false)
			{
				cout<<"Respuesta correcta !felicitaciones!, has ganado 1000 puntos."<<endl;
				cout<<endl;
				puntuaciones[turno][0]=(puntuaciones[turno][0] + 1000);
				cout<<"Siguiente turno."<<endl;
				cout<<endl;
			}
				
			else
			{
				if( correcto==true and pista==true)
					{
						cout<<"Respuesta correcta !felicitaciones!, has ganado 500 puntos por haber usado una pista."<<endl;
						cout<<endl;
						puntuaciones[turno][0]=(puntuaciones[turno][0] + 500);
						cout<<"siguiente turno."<<endl;
						cout<<endl;
					}
				
				else
				{
					if ( correcto==false and pista==false)
					{
						cout<<"Respuesta incorrecta, pierdes 500 puntos."<<endl;
						cout<<endl;
						puntuaciones[turno][0]=(puntuaciones[turno][0] - 500);
						cout<<"siguiente turno."<<endl;
						cout<<endl;
					}

					else
					{
						if( correcto==false and pista==true)
						{
						cout<<"respuesta incorrecta, pierdes 1000 puntos por haber usado una pista."<<endl;
						cout<<endl;
						puntuaciones[turno][0]=(puntuaciones[turno][0] - 1000);
						cout<<"siguiente tuno."<<endl;
						cout<<endl;
						}
					}
				}
			}
		}
		ronda=ronda+1;
	}while (ronda!=20 and puntuaciones[0][0]<5000 and puntuaciones[1][0]<5000 and puntuaciones[2][0]<5000 and puntuaciones[3][0]<5000);
	
	ganador = puntuaciones[0][0];
	renglon = 0;
	for(int i=1; i<x ;i++)
	{	
		if (puntuaciones[i][0]>ganador)
		{
		ganador=puntuaciones[i][0] ; renglon=i;
		}
	}
	cout<<"el ganador ha sido "<<jugadores[renglon]<<" con un total de "<<ganador<<" puntos. !Felicitaciones!."<<endl;
	cout<<endl;
	return renglon;
}
						
int main()
{
	do
	{
		cout<<"ingrese el numero de jugadores: "<<endl;
		cin>>num_jugadores;
		if (cin.fail()) 
		{
        	// Limpiar el búfer de entrada en caso de error
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	cout << "Ingresa solo numeros enteros en este espacio por favor." << endl;
    	}
    	
    	else if (num_jugadores < 2 or num_jugadores > 4) 
		{
        	cout << "El juego solo esta disponible para grupos de 2 a 4 jugadores." << endl;
    	}
		cout<<endl;
		cin.ignore(); // Limpiar el búfer de entrada
		
	}while (num_jugadores<2 or num_jugadores>4);
	
	string username;	
	cout<<"ingrese el nombre de cada uno de los jugadores:"<<endl;
	for (int i=1 ; i<=num_jugadores ; i++)
	{	
		cout<<"jugador "<<i<<":";
		getline(cin, username);
		jugadores.push_back(username);
		cout<<endl;
		cout<<"iteracion "<<i;
	}


	do
	{
		salir=false;
		puntuaciones[modo1 (num_jugadores)][1] += 1;
		cout<<"asi va la tabla de puntuaciones hasta ahora: "<<endl;
		cout<<endl;
		for (int i=0 ; i<num_jugadores ; i++)
		{
			cout<<jugadores[i]<<": "<<puntuaciones[i][1]<<endl;
		}
		cout<<endl;
		cout<<"Quieres jugar otra partida? (si/no):"<<endl;
		cin>>otra_vez;
		if(otra_vez=="no")
		{
			salir=true;
		}
		cout<<endl;
		cout<<endl;
		cout<<endl;
	}while (salir==false);
}





