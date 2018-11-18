#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#define MAX 8
#define DER 77
#define IZQ 75
#define ABJ 80

using namespace std;


void bgcolor(WORD color); 
void textcolor(WORD textcolor);
void textbgcolor(WORD textcolor, WORD bgcolor);
void imprimir(int matriz[MAX][MAX],int vector[MAX],bool band,char cadena1[20],char cadena2[20]);
void ponerBloque(int matriz[MAX][MAX],int a, bool band);
void gotoxy(int x, int y);
int  validar(int matriz[MAX][MAX],bool band,bool op);
int  iniciarPartida(char cadena1[20],char cadena2[20]);
void limpiar(int matriz[MAX][MAX]);
void validar3EnLinea(int matriz[MAX][MAX],char cadena1[20],char cadena2[20]);


int main(int argc, char** argv){

	int gan1=0,gan2=0,empa=0,mo=0;
	int jugad1=0,jugad2=0,partJug=0;
	int mat[MAX][MAX]={0};
	int mov[MAX]={0};
	int tecla=0,inicia=0,cont=0;
	bool band;
    char cadena1[20],cadena2[20];
    int porc=0;
    cout<<"Ingrese nombre del jugador 1: ";
    cin.getline(cadena1,20);
    cout<<"Ingrese nombre del jugador 2: ";
    cin.getline(cadena2,20);    
    
	limpiar(mat);
	inicia=iniciarPartida(cadena1,cadena2);
	if(inicia==1) band=true;
	else band=false;
	
	while(tecla!='x'){
		
		mov[mo]=1;
		imprimir(mat,mov,band,cadena1,cadena2);
		tecla=getch();
		if(tecla==DER && mo!=MAX-1){
			mov[mo]=0;
			mo++;
		}
		if(tecla==IZQ && mo!=0){
			mov[mo]=0;
			mo--;
		}
		if(tecla==ABJ){
			cont++;
			ponerBloque(mat,mo,band);
			if(band){
			 jugad1++; 
			 band=false;
			}else{
			  jugad2++; band=true;
			} 
		}	
		if(validar(mat,band,false)!=0 || cont==64){
			cont=0;
			imprimir(mat,mov,band,cadena1,cadena2);
			cout<<"\n\n";
			if(cont==64){
				cout<<"**Partida empatada**"<<endl;
				cout<<"Jugadas: "<<endl;
				cout<<cadena1<<"= "<<jugad1<<endl;
				cout<<cadena2<<"= "<<jugad2<<endl;
				validar3EnLinea(mat,cadena1,cadena2);
				empa++;
				inicia=iniciarPartida(cadena1,cadena2);
				if(inicia==1) band=true;
				else band=false;
			
			}
			if(validar(mat,band,false)==1){
				validar(mat,band,true);
				band=true;
				cout<<"**"<<cadena1<<" ha ganado la partida!**"<<endl;
				gan1++;
				cout<<"Jugadas: "<<jugad1<<endl;
				
				if(gan1==3){
					cout<<"**"<<cadena1<<" HA GANADO EL JUEGO!**"<<endl;			
				}
			
			}
			if(validar(mat,band,false)==2){
				validar(mat,band,true);
				band=false;
				cout<<"**"<<cadena2<<" ha ganado la partida!**"<<endl;
				gan2++;
				cout<<"Jugadas: "<<jugad2<<endl;
				
				if(gan2==3){
					cout<<"**"<<cadena2<<" HA GANADO EL JUEGO!**"<<endl;		
				}
				
			}
			
			cout<<"Partidas ganadas \n"<<cadena1<<": "<<gan1<<"\n"<<cadena2<<": "<<gan2<<endl;
			partJug++;
			porc=(empa*100)/partJug;
			cout<<"Partidas empatadas: "<<empa<<endl;
			cout<<"Partidas jugadas: "<<partJug<<endl;
			cout<<"% empates= "<<porc<<endl;
			tecla=getch();
			limpiar(mat);
		}
	}
	return 0;
}


void validar3EnLinea(int matriz[MAX][MAX],char cadena1[20],char cadena2[20]){
	int hor1=0,hor2=0,v1=0,v2=0,d1=0,d2=0;
	
	for(int x=0;x<MAX;x++){
		for(int y=0;y<MAX;y++){
			if(matriz[x][y]!=0){
				//jugador1
				if(matriz[x][y]==1 && matriz[x+1][y]==1 && matriz[x+2][y]==1 ){//vertical
					v1++;
				}
				if(matriz[x][y]==1 && matriz[x][y+1]==1 && matriz[x][y+2]==1 ){//horizontal
					hor1++;
				}
				if(matriz[x][y]==1 && matriz[x+1][y+1]==1 && matriz[x+2][y+2]==1 ){//diagonal 1
					d1++;
				}
				if(matriz[x][y]==1 && matriz[x+1][y-1]==1 && matriz[x+2][y-2]==1 ){//diagonal 2
					d1++;
				}
				
				//jugador2
				if(matriz[x][y]==2 && matriz[x+1][y]==2 && matriz[x+2][y]==2 ){//vertical
					v2++;
				}
				if(matriz[x][y]==2 && matriz[x][y+1]==2 && matriz[x][y+2]==2 ){//horizontal
					hor2++;
				}
				if(matriz[x][y]==2 && matriz[x+1][y+1]==2 && matriz[x+2][y+2]==2 ){//diagonal 1
					d2++;
				}
				if(matriz[x][y]==2 && matriz[x+1][y-1]==2 && matriz[x+2][y-2]==2 ){//diagonal 2
					d2++;
				}
			}
	 	}
	}
	cout<<"Tres en linea de "<<cadena1<<":"<<endl;
	cout<<"Horizontal: "<<hor1<<endl;
	cout<<"Vertical: "<<v1<<endl;
	cout<<"Diagonales: "<<d1<<endl;
	
	cout<<"\nTres en linea de "<<cadena2<<":"<<endl;
	cout<<"Horizontal: "<<hor2<<endl;
	cout<<"Vertical: "<<v2<<endl;
	cout<<"Diagonales: "<<d2<<endl;
	getch();
}

void limpiar(int matriz[MAX][MAX]){
	for(int x=0;x<MAX;x++){
		for(int y=0;y<MAX;y++){
			matriz[x][y]=0;
		}
	}
}
int iniciarPartida(char cadena1[20],char cadena2[20]){
	srand(time(NULL));
	int dado1;
	int dado2;
	int tecla=0,jugador=0;
	
	while(tecla==0){
		system("cls");
		if(_kbhit())
		tecla=getch();
		cout<<cadena1<<"= ";
		dado1=rand()%6+1;
		cout<<dado1<<endl;
		Sleep(100);	
	}
	
	tecla=getch();
	tecla=0;
	while(tecla==0 || dado1==dado2){
		system("cls");
		if(_kbhit())
		tecla=getch();
		cout<<cadena2<<"= ";
		dado2=rand()%6+1;
		cout<<dado2<<endl;
		Sleep(100);	
	}
	
	tecla=0;
	tecla=getch();
	
	system("cls");
	
	cout<<cadena1<<"= "<<dado1<<endl;
	cout<<cadena2<<"= "<<dado2<<endl;
	if(dado1>dado2){
		cout<<"Empieza "<<cadena1;
		jugador=1;
	}else{
		cout<<"Empieza "<<cadena2;
		jugador=2;
	}
	tecla=0;
	tecla=getch();
	
	return jugador;
}

int validar(int matriz[MAX][MAX],bool band,bool op){
	for(int x=0;x<MAX;x++){
		for(int y=0;y<MAX;y++){
			if(matriz[x][y]!=0){
				//jugador1
				
				if(matriz[x][y]==1 && matriz[x+1][y]==1 && matriz[x+2][y]==1 && matriz[x+3][y]==1){//vertical
					if(op){
					cout<<"Posicion de las fichas ganadoras: "<<endl;
					cout<<"("<<x<<","<<y<<")"<<"-"<<"("<<x+1<<","<<y<<")"<<"-"<<"("<<x+2<<","<<y<<")"<<"-"<<"("<<x+3<<","<<y<<")"<<endl;
					cout<<"Forma vertical "<<endl;
					}
					return 1;
				}
				if(matriz[x][y]==1 && matriz[x][y+1]==1 && matriz[x][y+2]==1 && matriz[x][y+3]==1){//horizontal
					if(op){
					cout<<"Posicion de las fichas ganadoras: "<<endl;
					cout<<"("<<x<<","<<y<<")"<<"-"<<"("<<x<<","<<y+1<<")"<<"-"<<"("<<x<<","<<y+2<<")"<<"-"<<"("<<x<<","<<y+3<<")"<<endl;
					cout<<"Forma horizontal "<<endl;					
					}
					return 1;
				}
				if(matriz[x][y]==1 && matriz[x+1][y+1]==1 && matriz[x+2][y+2]==1 && matriz[x+3][y+3]==1){//diagonal 1
					if(op){
					cout<<"Posicion de las fichas ganadoras: "<<endl;
					cout<<"("<<x<<","<<y<<")"<<"-"<<"("<<x+1<<","<<y+1<<")"<<"-"<<"("<<x+2<<","<<y+2<<")"<<"-"<<"("<<x+3<<","<<y+3<<")"<<endl;
					cout<<"Forma diagonal "<<endl;		
					}
					return 1;
				}
				if(matriz[x][y]==1 && matriz[x+1][y-1]==1 && matriz[x+2][y-2]==1 && matriz[x+3][y-3]==1){//diagonal 2
					if(op){
					cout<<"Posicion de las fichas ganadoras: "<<endl;
					cout<<"("<<x<<","<<y<<")"<<"-"<<"("<<x+1<<","<<y-1<<")"<<"-"<<"("<<x+2<<","<<y-2<<")"<<"-"<<"("<<x+3<<","<<y-3<<")"<<endl;
					cout<<"Forma diagonal "<<endl;		
					}
					return 1;
				}
				
				//jugador2
				if(matriz[x][y]==2 && matriz[x+1][y]==2 && matriz[x+2][y]==2 && matriz[x+3][y]==2){//vertical
					if(op){
					cout<<"Posicion de las fichas ganadoras: "<<endl;
					cout<<"("<<x<<","<<y<<")"<<"-"<<"("<<x+1<<","<<y<<")"<<"-"<<"("<<x+2<<","<<y<<")"<<"-"<<"("<<x+3<<","<<y<<")"<<endl;
					cout<<"Forma vertical "<<endl;
					}
					return 2;
				}
				if(matriz[x][y]==2 && matriz[x][y+1]==2 && matriz[x][y+2]==2 && matriz[x][y+3]==2){//horizontal
					if(op){
					cout<<"Posicion de las fichas ganadoras: "<<endl;
					cout<<"("<<x<<","<<y<<")"<<"-"<<"("<<x<<","<<y+1<<")"<<"-"<<"("<<x<<","<<y+2<<")"<<"-"<<"("<<x<<","<<y+3<<")"<<endl;
					cout<<"Forma horizontal "<<endl;
					}
					return 2;
				}
				if(matriz[x][y]==2 && matriz[x+1][y+1]==2 && matriz[x+2][y+2]==2 && matriz[x+3][y+3]==2){//diagonal 1
					if(op){
					cout<<"Posicion de las fichas ganadoras: "<<endl;
					cout<<"("<<x<<","<<y<<")"<<"-"<<"("<<x+1<<","<<y+1<<")"<<"-"<<"("<<x+2<<","<<y+2<<")"<<"-"<<"("<<x+3<<","<<y+3<<")"<<endl;
					cout<<"Forma diagonal "<<endl;
					}
					return 2;
				}
				if(matriz[x][y]==2 && matriz[x+1][y-1]==2 && matriz[x+2][y-2]==2 && matriz[x+3][y-3]==2){//diagonal 2
					if(op){
					cout<<"Posicion de las fichas ganadoras: "<<endl;
					cout<<"("<<x<<","<<y<<")"<<"-"<<"("<<x+1<<","<<y-1<<")"<<"-"<<"("<<x+2<<","<<y-2<<")"<<"-"<<"("<<x+3<<","<<y-3<<")"<<endl;
					cout<<"Forma diagonal "<<endl;
					}
					return 2;
				}
			}
	 	}
	}
	return 0;
}

void ponerBloque(int matriz[MAX][MAX],int a,bool band){
	int x=-1;
	
	while(matriz[x+1][a]==0 && x!=MAX-1){
		x++;
		
	}
	if(band) matriz[x][a]=1;
	else 	 matriz[x][a]=2;
}

void imprimir(int matriz[MAX][MAX],int vector[MAX],bool band,char cadena1[20],char cadena2[20]){
	char a;
	system("cls");
	textcolor(0xE);
	for(int x=0;x<8;x++){
		if(vector[x]==1){
			if(band) textcolor(0x9);
			else textcolor(0xC);
			cout<<"\31";
		}else{
			cout<<" ";	
		}
		
	} 
	
	for(int x=0;x<MAX;x++){
		cout<<endl;
		for(int y=0;y<MAX;y++){
			if(matriz[x][y]==1){	a=219; textcolor(0x9); cout<<a;	}
			if(matriz[x][y]==2){	a=219; textcolor(0xC); cout<<a;	}
			if(matriz[x][y]==0){	a=176; textcolor(0x8); cout<<a;	}
			
		}
	}
	
	if(band){
		textcolor(0x9);
		cout<<"  "<<cadena1<<endl;	
	}else{
		textcolor(0xC);
		cout<<"  "<<cadena2<<endl;
	} 	 
	textcolor(0xE);
}

void bgcolor(WORD color){
    char scolor[10];
    WORD bgcolor = (color & 0xF) << 4;
    sprintf(scolor, "color %x", bgcolor);
    system(scolor);
}

void textcolor(WORD textcolor){
    textbgcolor(textcolor, 0);
}

void textbgcolor(WORD textcolor, WORD bgcolor){
    WORD color = (bgcolor & 0xF) << 4 | (textcolor & 0xF);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, color);
}

void gotoxy(int x, int y){
    HANDLE hConsole;
    COORD dwPos;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hConsole, dwPos);
}

