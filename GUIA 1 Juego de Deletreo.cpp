#include <iostream>
#include <algorithm>
#include <cctype>
#include <stdlib.h>     
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

int num_jugadores;
vector <string> jugadores;
string otra_vez;
bool salir;
bool correcto;
ifstream arch;
struct registros
    {
    	string nombre;
    	int puntuacion;
	};

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
        	this_thread::sleep_for(chrono::seconds(2));
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

    while (getline(archivo, respuesta_correcta)) 
	{
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


void Ingresar_ganador(int indice)
{
	fstream archivo;
	string renglon;
	string records;
	string ganador = jugadores[indice];
	int puntos = puntuaciones[indice][0];
	string puntos_ganador = to_string(puntos);

	archivo.open("records.txt", ios::in);
	if (!archivo.is_open())
	{
    	cerr << "No se pudo abrir el archivo, se perderan los records registrados en esta partida." << endl;
    	return;
    }
	
    string registrosActuales;
    bool jugadorEncontrado = false;
	
	archivo.seekg(0, std::ios::beg);
	while (getline(archivo, renglon))
    {
		size_t pos = renglon.find(":");
    	if (pos != string::npos)
    	{
    		string nombre = renglon.substr(0, pos);
    		if (nombre==ganador)
    		{
    			int puntajeExistente = stoi(renglon.substr(pos+2));
    			puntajeExistente += puntos;
    			renglon = ganador + ": " + to_string(puntajeExistente);
    			jugadorEncontrado = true;
			}
		}
		registrosActuales += renglon + "\n";
	} 
	
	if (!jugadorEncontrado)
	{
		registrosActuales += ganador + ": " + puntos_ganador+"\n";
	}
	archivo.close();
	
	archivo.open("records.txt", ios::out);
	if (!archivo.is_open())
	{
    	cerr << "No se pudo abrir el archivo, se perderan los records registrados en esta partida." << endl;
    	return;
    }
	archivo.seekp(0, ios::beg);
	archivo << registrosActuales<< endl;
    archivo.close();

}

void merge(vector<registros>& arr, int l, int m, int r) 
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<registros> L(n1);
    vector<registros> R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) 
	{
        if (L[i].puntuacion >= R[j].puntuacion) 
		{
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
	{
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
	{
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<registros>& arr, int l, int r) 
{
    if (l < r) 
	{
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void OrganizarRecords()
{
	fstream archivo;
	archivo.open("records.txt", ios::in);
	if (!archivo.is_open())
	{
    	cerr << "No se pudo abrir el archivo, se perderan los records registrados en esta partida." << endl;
    	return;
    }
    
	registros datos;
	
	string renglon;
	vector<registros> ordenar;
	archivo.seekg(0, ios::beg);
	while (getline(archivo, renglon))
    {
		size_t pos = renglon.find(":");
    	if (pos != string::npos)
    	{
    		datos.nombre = renglon.substr(0, pos);
    		datos.puntuacion = stoi(renglon.substr(pos+2));
    		ordenar.push_back(datos);
		}
	}
	mergeSort(ordenar, 0, ordenar.size() - 1);
	archivo.close();

    archivo.open("records.txt", ios::out);
	if (!archivo.is_open())
	{
    	cerr << "No se pudo abrir el archivo, se perderan los records registrados en esta partida." << endl;
    	return;
    }
    
    string devolver;
    for (const auto& registros : ordenar)
    {
    	devolver+=registros.nombre+": "+to_string(registros.puntuacion)+"\n";
	}
    
    archivo.clear();
	archivo.seekp(0, ios::beg);
	archivo <<devolver<< endl;
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
			this_thread::sleep_for(chrono::seconds(2));
			cout<<"AHORA ES EL TURNO DE "<<jugadores[turno]<<endl;
			cout<<"A que palabra en ingles corresponde la siguiente definicion?:"<<endl;
			cout<<endl;
			leer_definicion(aleatorio);
			cout<<endl;
			this_thread::sleep_for(chrono::seconds(2));
			cout<<"Ingresa tu respuesta (si necesitas una pista ingresa la palabra 'pista'):"<<endl;
			getline(cin, palabra_usuario);
			transform(palabra_usuario.begin(), palabra_usuario.end(), palabra_usuario.begin(), ::toupper);
			cout<<endl;
			
			if (palabra_usuario== "PISTA")
			{
				cout<<endl;
				cout<<"LA PALABRA QUE TIENES QUE ADIVINAR, AL TRADUCIRLA AL ESPANOL ES: "<< leer_pista(aleatorio);
				pista=true;
				cout<<endl;
				
				cout<<"Ahora si, ingresa tu respuesta final: "<<endl;
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
				cout<<"************************************************************"<<endl;
				cout<<"Respuesta correcta !felicitaciones!, has ganado 1000 puntos."<<endl;
				cout<<"************************************************************"<<endl;
				cout<<endl;
				puntuaciones[turno][0]=(puntuaciones[turno][0] + 1000);
				cout<<"Siguiente turno."<<endl;
				cout<<endl;
			}
				
			else
			{
				if( correcto==true and pista==true)
					{
						cout<<"*************************************************************************************"<<endl;
						cout<<"Respuesta correcta !felicitaciones!, has ganado 500 puntos por haber usado una pista."<<endl;
						cout<<"*************************************************************************************"<<endl;
						cout<<endl;
						puntuaciones[turno][0]=(puntuaciones[turno][0] + 500);
						cout<<"Siguiente turno."<<endl;
						cout<<endl;
					}
				
				else
				{
					if ( correcto==false and pista==false)
					{
						cout<<"*****************************************"<<endl;
						cout<<"Respuesta incorrecta, pierdes 500 puntos."<<endl;
						cout<<"*****************************************"<<endl;
						cout<<endl;
						puntuaciones[turno][0]=(puntuaciones[turno][0] - 500);
						cout<<"Siguiente turno."<<endl;
						cout<<endl;
					}

					else
					{
						if( correcto==false and pista==true)
						{
						cout<<"********************************************************************"<<endl;
						cout<<"Respuesta incorrecta, pierdes 1000 puntos por haber usado una pista."<<endl;
						cout<<"********************************************************************"<<endl;
						cout<<endl;
						puntuaciones[turno][0]=(puntuaciones[turno][0] - 1000);
						cout<<"Siguiente tuno."<<endl;
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
	cout<<endl;
	cout<<"EL GANADOR HA SIDO "<<jugadores[renglon]<<" CON UN TOTAL DE "<<ganador<<" PUNTOS. !FELICITACIONES!."<<endl;
	cout<<endl;
	return renglon;
}


						
int main()
{
	do
	{
		cout<<"INGRESE EL NUMERO DE JUGADORES: "<<endl;
		cin>>num_jugadores;
		if (cin.fail()) 
		{
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	cout << "Ingresa solo numeros enteros en este espacio por favor." << endl;
    	}
    	
    	else if (num_jugadores < 2 or num_jugadores > 4) 
		{
        	cout << "El juego solo esta disponible para grupos de 2 a 4 jugadores." << endl;
    	}
		cout<<endl;
		cin.ignore();
		
	}while (num_jugadores<2 or num_jugadores>4);
	
	string username;
	cout<<endl;	
	cout<<"Ingrese el nombre de cada uno de los jugadores:"<<endl;
	for (int i=1 ; i<=num_jugadores ; i++)
	{	
		cout<<"JUGADOR "<<i<<": ";
		getline(cin, username);
		transform(username.begin(), username.end(), username.begin(), ::toupper);
		jugadores.push_back(username);
		cout<<endl;
	}


	do
	{
		salir=false;
		int ganador_ronda=modo1 (num_jugadores);
		puntuaciones[ganador_ronda][1] += 1;
		Ingresar_ganador(ganador_ronda);
		cout<<"Asi va la tabla de puntuaciones hasta ahora: "<<endl;
		cout<<endl;
		for (int i=0 ; i<num_jugadores ; i++)
		{
			cout<<jugadores[i]<<": "<<puntuaciones[i][1]<<endl;
		}
		cout<<endl;
		OrganizarRecords();
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
