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
	int celulas=0;

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
			cout<<"Son muchas celulas! Se jugara con las que ya hay ingresadas.";
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

int contadorCelulasVivas(int matriz[20][80]){

	int celulas=0;
	int fila,columna;
	for(fila = 0 ; fila < 20 ; fila++){
		for(columna = 0 ; columna < 80 ; columna++){
			if(matriz[fila][columna] == 1){
				celulas++;}
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

void juegoCongelado(int matriz[20][80],int matrizAuxiliar[20][80]){

	int fila,columna;
	int casilleros=0;
	for(fila=0;fila<20;fila++){
		for(columna=0;columna<80;columna++){
			if(matriz[fila][columna]==matrizAuxiliar[fila][columna]){
				casilleros++;
			}
		}
	}
	if(casilleros == 1600){
		cout<<"\nEl tablero no sufrio cambios!";
	}
}

int estadoCelulas(int celulasActuales,int celulasAnteriores){

	int total=0;
	total = (celulasActuales-celulasAnteriores);
	if(total > 0){
		cout<<"\nNacieron "<<total<<" celulas";
	}
	if(total < 0){
		cout<<"\nMuerieron "<<total<<" celulas";
	}
	return total;
}

void celulaViva(int matrizAuxiliar[20][80],int matriz[20][80],int fila,int columna){

	int celulas;
	celulas = celulasAdyacentes(matrizAuxiliar,fila,columna);
	if(celulas < 2 || celulas > 3){
		matriz[fila][columna]=0;
	}
	else{
		matriz[fila][columna]=1;
	}
}

void celulaMuerta(int matrizAuxiliar[20][80],int matriz[20][80],int fila,int columna){

	int celulas;
	celulas = celulasAdyacentes(matrizAuxiliar,fila,columna);
	if(celulas != 3){
		matriz[fila][columna]=0;
	}
	else{
		matriz[fila][columna]=1;
	}
}

int actualizarMatriz(int matrizAuxiliar[20][80],int matriz[20][80]){

	int celulasNacidas=0;
	for(int fila=0;fila<20;fila++){
		for(int columna=0;columna<80;columna++){
			if(matrizAuxiliar[fila][columna]==1){//CELULA VIVA
				celulasNacidas++;
				celulaViva(matrizAuxiliar,matriz,fila,columna);
			}
			else{//CELULA MUERTA.
				celulaMuerta(matrizAuxiliar,matriz,fila,columna);
			}
		}
	}
	return celulasNacidas;
}

int controlador(int matriz[20][80]){

	int celulasNacidas=0;
	int celulasAuxiliar;
	int matrizAuxiliar[20][80];//LA MATRIZ AUXILIAR SOLO VIVE EN ESTA FUNCION.

	for(int fila=0;fila<20;fila++){//Copio la matriz original en otra auxiliar asi no se modifica en la ejecucion.
		for(int columna=0;columna<80;columna++){
			matrizAuxiliar[fila][columna]=matriz[fila][columna];
		}
	}
	celulasNacidas=actualizarMatriz(matrizAuxiliar,matriz);//CELULAS NACIDAS EN EL ULTIMO TURNO
	celulasAuxiliar = contadorCelulasVivas(matriz);//CELULAS NACIDAS EN EL TURNO ANTERIOR
	juegoCongelado(matriz,matrizAuxiliar);
	estadoCelulas(celulasAuxiliar,celulasNacidas);
	return celulasAuxiliar;
}

int peticionUsuario(){

	int respuesta;
	cout<<"\n[1] SEGUIR CON LA EVOLUCION";
	cout<<"\n[2] REINICIAR EL JUEGO";
	cout<<"\n[3] TERMINAR";
	cout<<"\nRESPUESTA:";
	cin>>respuesta;
	while(respuesta < 1 || respuesta > 3){
		cout<<"\nRESPUESTA INVALIDA! Vuelva a intentar:";
		cin>>respuesta;
	}
	return respuesta;
}

void respuesta1(int matriz[20][80]){

	int celulas;
	for(int i=0; i<=10; i++){//PARA QUE SEA MAS FLUIDA LA CORRECCION.
		cout<<"\n---------------------------------------------------";
		celulas=controlador(matriz);
		cout<<"\nCantidad de celulas con vida:"<<celulas;
		mostrarMatriz(matriz);
	}
}

void respuesta2(int matriz[20][80]){

	int celulasArranque;

	cout<<"COMENZANDO UN NUEVO JUEGO...\n";
	generarMatriz(matriz);
	celulasArranque=pedirCelulasDeArranque(matriz);
	cout<<"\nCelulas de arranque:"<<celulasArranque;
	mostrarMatriz(matriz);
}

void juego(){

	int matriz[20][80];
	int respuesta=2;
	while(respuesta != 3){
		if(respuesta ==  1){
			respuesta1(matriz);
		}
		if(respuesta == 2){
			respuesta2(matriz);
		}
	respuesta = peticionUsuario();
	}
	cout<<"\nJUEGO FINALIZADO\n";
}

int main(){

	juego();

	return 0;
}
