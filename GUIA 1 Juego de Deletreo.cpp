#include <iostream>
#include <algorithm>
#include <stdlib.h>     
#include <time.h>       
#include <string>
#include <vector>
using namespace std;

int num_jugadores;
vector <string> jugadores;
string otra_vez;
bool salir;

string directorio[30][3] = {
							{"scissors","A device used for cutting materials such as paper, cloth, and hair, consisting of two sharp blades that are joined in the middle, and two handles with holes to put your fingers through","tijeras"},
							{"glue", "A sticky substance that is used for joining things together permanently, produced from animal bones and skins or by a chemical process", "pegamento"},
							{"notebook", "A book of plain paper or paper with lines, for writing on", "cuaderno"},
							{"folder", "a piece of plastic or cardboard folded down the middle and used for keeping loose papers in", "carpeta"}
							,{"highlighter", "A special pen containing bright ink, used to mark words in a book, magazine, etc.", "resaltador"}
							,{"crayons", "A small stick of coloured wax used for drawing or writing", "crayones"}
							,{"compass", "A V-shaped device that is used for drawing circles or measuring distances on maps", "compás"}
							,{"chalk", "A type of soft rock or a similar substance used for writing or drawing", "tiza"}
							,{"schedule", "A list of planned activities or things to be done showing the times or dates when they are intended to happen or be done.", "horario"}
							,{"dictionary", "A book that contains a list of words in alphabetical order and explains their meanings, or gives a word for them in another language", "diccionario"}
							,{"syringe", "Small tube with a fine hollow needle, used for injecting drugs or for taking blood from someone's body.", "jeringa"}
							,{"glasses", "Lenses mounted in a frame that holds them in front of a person's eyes", "gafas"}
							,{"bottle", "Is a glass or plastic container in which drinks and other liquids are kept", "botella"}
							,{"heart", "Is the main organ of your cardiovascular system", "corazón"}
							,{"bullet", "A small metal projectile", "bala"}
							,{"sword", "A hand weapon having a long, sharp-pointed Blade", "espada"}
							,{"dishes", "All the objects that have been used to cook, serve, and eat a meal", "platos"}
							,{"kite", "It consists of a light frame covered with paper or cloth and has a long string", "cometa"}
							,{"lock", "Is a tool that keeps a room, house, drawer, or box securely closed.", "candado"}
							,{"door", "It serves to prevent entry and exit, to close or open a closet or piece of furniture.", "puerta"}
							,{"floor", "Natural or artificial pavement of rooms, streets, paths, etc.", "suelo"}
							,{"garden", "Land where plants are grown.", "jardin"}
							,{"kitchen", "Room or place in the house in which food is cooked.", "cocina"}
							,{"wall", "Plate of any material with which a space is divided or closed", "muro"}
							,{"window", "Opening in a wall or wall where an element is placed and which generally serves to look out and provide light and ventilation.", "ventana"}
							,{"oven", "Closed metal device, inside which food is roasted, cooked, heated or gratinated", "horno"}
							,{"spoon", "Utensil that consists of an extended concave part in a handle, and that is used, especially, to put liquid, soft or small things in the mouth.", "cuchara"}
							,{"table", "Furniture essentially formed by a smooth surface supported by one or more feet and that serves different uses", "mesa"}
							,{"lighter", "A small device that produces a flame that is used to light cigarettes", "encendedor"}
							,{"letter", "a written message from one person to another, usually put in an envelope and sent by post", "carta"}
							};
							
int puntuaciones[4][2] = {
						{0 ,0},
						{0 ,0},
						{0 ,0},
						{0 ,0}
						};
						
		
		
int modo1 (int x)
{	
	string palabra_usuario;
	string palabra_correcta;
	bool pista=false;
	int numero_aleatorio;
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
			aleatorio=rand() % rango;
			cout<<"Ahora es el turno de "<<jugadores[turno]<<". A que palabra en ingles corresponde la siguiente definicion?:"<<endl;
			cout<<endl;
			cout<<directorio[aleatorio][1];
			palabra_correcta=directorio[aleatorio][0];
			cout<<endl;
			cout<<"ingresa tu respuesta (si necesitas una pista ingresa la palabra 'pista'):"<<endl;
			cin>>palabra_usuario;
			cout<<endl;
			
			if (palabra_usuario== "pista")
			{
				cout<<endl;
				cout<<"La palabra que tienes que adivinar, al traducirla al espanol es: "<<directorio[aleatorio][2]<<endl;
				pista=true;
				cout<<endl;
				
				cout<<"ahora si, ingresa tu respuesta final: "<<endl;
				cin>>palabra_usuario;
				cout<<endl;
			}
			
			if(palabra_usuario==palabra_correcta and pista==false)
			{
				cout<<"Respuesta correcta !felicitaciones!, has ganado 1000 puntos."<<endl;
				cout<<endl;
				puntuaciones[turno][0]=(puntuaciones[turno][0] + 1000);
				cout<<"Siguiente turno."<<endl;
				cout<<endl;
			}
				
			else
			{
				if(palabra_usuario==palabra_correcta and pista==true)
					{
						cout<<"Respuesta correcta !felicitaciones!, has ganado 500 puntos por haber usado una pista."<<endl;
						cout<<endl;
						puntuaciones[turno][0]=(puntuaciones[turno][0] + 500);
						cout<<"siguiente turno."<<endl;
						cout<<endl;
					}
				
				else
				{
					if (palabra_usuario!=palabra_correcta and pista==false)
					{
						cout<<"Respuesta incorrecta, pierdes 500 puntos."<<endl;
						cout<<endl;
						puntuaciones[turno][0]=(puntuaciones[turno][0] - 500);
						cout<<"siguiente turno."<<endl;
						cout<<endl;
					}

					else
					{
						if(palabra_usuario!=palabra_correcta and pista==true)
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





