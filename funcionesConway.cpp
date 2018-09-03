#include<iostream>
#include<string>

using namespace std;

void generarMatriz(int matriz[20][80]){

	int fila,columna;

	for(fila=0;fila<20;fila++){
		for(columna=0;columna<80;columna++){
			matriz[fila][columna] = 0;
		}
	}
}

int verificadorPosicion(int x, int y){

	int posicionCorregida;

	while(x > 20 || y > 80){
		if(x > 20){
			cout<<"ERROR! La coordenada x debe ser menor o igual a 20:";
			cin>>posicionCorregida;
			x = posicionCorregida;
		}
		else{
			cout<<"ERROR! La coordenada y debe ser menor o igual a 80:";
			cin>>posicionCorregida;
			y = posicionCorregida;
		}
	}
	return posicionCorregida;
}

int pedirCelulasDeArranque(int matriz[20][80]){

	int coordenadaX,coordenadaY;
	char seguir='S';
	int celulas;

	while(seguir=='S' || seguir=='s'){
		cout<<"Ingrese la coordenada en x:";
		cin>>coordenadaX;
		cout<<"Ingrese la coordenada en y:";
		cin>>coordenadaY;
		while(coordenadaX > 20 || coordenadaY > 80){
			coordenadaX = verificadorPosicion(coordenadaX,0);
			coordenadaY = verificadorPosicion(0,coordenadaY);
		}
		celulas++;
		matriz[coordenadaX-1][coordenadaY-1] = 1;

		if(celulas > 1600){
			cout<<"Hey! Son muchas celulas! Se jugara con las que ya hay ingresadas.";
			seguir = 'N';
		}
		else{
			cout<<"Desea continuar cargando celulas?[S/N]:";
			cin>>seguir;
		}
	}
	return celulas;
}

int celulasAdyacentes(int matriz[20][80],int puntoX,int puntoY){

	int deltaX, deltaY;
	int filas=20;
	int columnas=80;
	int celulas=0;

	for(deltaX = (puntoX > 0 ? -1 : 0); deltaX <= (puntoX < filas ? 1 : 0); ++deltaX){
		for(deltaY = (puntoY > 0 ? -1 : 0); deltaY <= (puntoY < columnas ? 1 : 0); ++deltaY){
			if(deltaX != 0 || deltaY != 0){
				if(matriz[deltaX+puntoX][deltaY+puntoY]==1){
					celulas++;
				}
			}
		}
	}
	return celulas;
}

int celulasVivas(int matriz[20][80]){

	int celulas;
	int fila,columna;

	for(fila = 0 ; fila < 20 ; fila++){
		for(columna = 0 ; columna < 80 ; columna++){
			if(matriz[fila][columna] == 1){celulas++;}
		}
	}
	return celulas;
}

void mostrarMatriz(int matriz[20][80]){

	for(int i=0;i<20;i++){
		cout<<"\n";
			for(int j=0;j<80;j++){
				cout<<matriz[i][j];
		}
	}
}

int controlador(int matriz[20][80]){

	int celulas;
	int fila,columna;
	int matrizAuxiliar[20][80];//LA MATRIZ AUXILIAR SOLO VIVE EN ESTA FUNCION.

	for(fila=0;fila<20;fila++){//copio la matriz original en otra auxiliar asi no se modifica sobre la marcha.
		for(columna=0;columna<80;columna++){
			matrizAuxiliar[fila][columna]=matriz[fila][columna];
		}
	}
	for(fila=0;fila<20;fila++){
			for(columna=0;columna<80;columna++){
				if(matrizAuxiliar[fila][columna]==1){//CELULA VIVA.
					celulas = celulasAdyacentes(matrizAuxiliar,fila,columna);
					if(celulas < 2 || celulas > 3){
						matriz[fila][columna]=0;
					}
					else{
						matriz[fila][columna]=1;
					}
				}
				else{//CELULA MUERTA.
					celulas = celulasAdyacentes(matrizAuxiliar,fila,columna);
					if(celulas != 3){
						matriz[fila][columna]=0;
					}
					else{
						matriz[fila][columna]=1;
				}
			}
		}
	}
	celulas = celulasVivas(matrizAuxiliar);
	return celulas;
}

int organizador(){

	int respuesta;

	cout<<"\n[1] SEGUIR CON LA EVOLUCION";
	cout<<"\n[2] REINICIAR EL JUEGO";
	cout<<"\n[3] TERMINAR";
	cout<<"\nRESPUESTA:";
	cin>>respuesta;
	while(respuesta < 1 || respuesta > 3){
		cout<<"RESPUESTA INVALIDA! Vuelva a intentar:";
		cin>>respuesta;
	}
	return respuesta;
}

void juego(){

	int matriz[20][80];
	int respuesta;
	int celulasArranque,celulas;

	generarMatriz(matriz);
	celulasArranque = pedirCelulasDeArranque(matriz);
	mostrarMatriz(matriz);

	cout<<"Celulas de arranque:"<<celulasArranque;

	respuesta = organizador();

	while(respuesta != 3){
		if(respuesta ==  1){
			cout<<"-------------------------------------------------------------------------";
			celulas=controlador(matriz);
			cout<<"\nCantidad de celulas con vida:"<<celulas;
			//PROMEDIO DE NACIMIENTOS
			//PROMEDIO DE MUERTES
			//SI NO HUBO CAMBIO EN LOS ULTIMOS DOS TURNOS
			mostrarMatriz(matriz);
		}
		if(respuesta == 2){
			cout<<"REINICIANDO JUEGO...\n";
			generarMatriz(matriz);
			pedirCelulasDeArranque(matriz);
			mostrarMatriz(matriz);
			respuesta = organizador();
		}
	respuesta = organizador();
	}
	cout<<"\nJUEGO FINALIZADO";
}

int main(){

	juego();

	return 0;
}
