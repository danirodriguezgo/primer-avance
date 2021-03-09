#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct producto {
	int cantidad;
	char nombre[20];
	producto* siguiente;
	producto* previo;
}*inicio, *fin;


void agregar() {
	cout << "AGREGAR PRODUCTO" << endl;
	if (inicio == NULL) {
		inicio = new producto;
		cout << "NOMBRE:";
		cin >> inicio->nombre;
		cout << "CANTIDAD:";
		cin >> inicio->cantidad;
		inicio->previo = NULL;
		inicio->siguiente = NULL;
		fin = inicio;
	}
	else {
		while (fin->siguiente != NULL) {
			fin = fin->siguiente;
		}
		fin->siguiente = new producto;
		fin->siguiente->siguiente = NULL;
		fin->siguiente = fin;
		fin->siguiente->previo = fin;
		fin = fin->siguiente;
		cout << "NOMBRE:";
		cin >> fin->nombre;
		cout << "CANTIDAD:";
		cin >> fin->cantidad;
		fin = inicio;
	}
	system("PAUSE");
}

void eliminar() {
	cout << "ELIMINAR PRODUCTO" << endl;
	producto* recorredor = inicio;
	producto* atras = NULL;
	if (inicio == NULL) {
		cout << "LA LISTA ESTA VACIA" << endl;
		return;
	}
	cout << "INTRODUZCA EL NOMBRE DEL PRODUCTO A ELIMINAR:";
	int indice;
	cin >> indice;
	for (int i = 0; i < indice; i++) {
		atras = recorredor;
		recorredor = recorredor->siguiente;
	}
	if (inicio == fin && recorredor == inicio) {
		delete recorredor;
		inicio = NULL;
		fin = NULL;
		return;
	}
	if (indice == 0) {
		inicio = recorredor->siguiente;
	}
	else {
		atras->siguiente = atras->siguiente->siguiente;
		if (recorredor->siguiente == NULL) {
			fin = atras;
		}
	}
	delete recorredor;
}

void modificar() {
	producto* recorredor = inicio;
	if (inicio == NULL) {
		cout << "LA LISTA ESTA VACIA" << endl;
		return;
	}
	cout << "INTRODUZCA EL NOMBRE DEL PRODUCTO A ELIMINAR:";
	int indice;
	cin >> indice;
	for (int i = 0; i < indice; i++) {
		recorredor = recorredor->siguiente;
	}
	cout << "PRODUCTO" << "(ANTES" << recorredor->nombre << "):";
	cin >> recorredor->nombre;
	cout << "CANTIDAD" << "(ANTES" << recorredor->cantidad << "):";
	cin >> recorredor->cantidad;
}

void mostrar() {
	producto* recorredor = inicio;
	if (inicio == NULL) {
		cout << "LA LISTA ESTA VACIA" << endl;
		return;
	}
	while (recorredor != NULL) {
		cout << "PRODUCTO:" << recorredor->nombre << "CANTIDAD:" << recorredor->cantidad << endl;
		recorredor = recorredor->siguiente;
	}
}

void guardar() {
	producto* recorredor = inicio;
	if (inicio == NULL) {
		cout << "LA LISTA ESTA VACIA" << endl;
		return;
	}
	char cadena[225];
	cout << "NOMBRE DEL ARCHIVO:";
	cin >> cadena;
	ofstream escribir;
	escribir.open(cadena, ios::out | ios::binary);
	if (escribir.is_open()) {
		while (recorredor != NULL) {
			escribir.write(reinterpret_cast<char*>(recorredor), sizeof(producto));
			recorredor = recorredor->siguiente;
		}
	}
	escribir.close();
}

void cargar() {
	salir();
	char cadena[225];
	cout << "NOMBRE DEL ARCHIVO:";
	cin >> cadena;
	ifstream leer;
	leer.open(cadena, ios::in | ios::binary);
	if (leer.is_open()) {
		producto* auxiliar = new producto;
		leer.read(reinterpret_cast<char*>(auxiliar), sizeof(producto));

		while (!leer.eof()) {
			if (inicio != NULL) {
				fin->siguiente = new producto;
				fin = fin->siguiente;
			}
			else {
				inicio = new producto;
				fin = inicio;
			}
			fin->cantidad = auxiliar->cantidad;
			strcpy_s(fin->nombre,auxiliar->nombre);
			fin->siguiente = NULL;
			leer.read(reinterpret_cast<char*>(auxiliar), sizeof(producto));
		}
	}
	leer.close();
}

void salir() {
	producto* recorredor = inicio;
	if (inicio == NULL) {
		cout << "LA LISTA ESTA VACIA" << endl;
		return;
	}
	while (recorredor != NULL) {
		producto* algo = recorredor->siguiente;
		delete recorredor;
		recorredor = algo;
	}
	inicio = NULL;
	fin = NULL;
}

int main() {
	int opcion;
	inicio = fin = NULL;
	while (opcion != 7) {
		cout << "SELECCIONE UNA DE LAS SIGUIENTES OPCIONES:" << endl;
		cout << "1: AGREGAR PRODUCTO" << endl;
		cout << "2: ELIMINAR PRODUCTO" << endl;
		cout << "3: MODIFICAR PRODUCTO" << endl;
		cout << "4: MOSTRAR LISTA DE PRODUCTOS" << endl;
		cout << "5: GUARDAR ARCHIVO DE PRODUCTOS" << endl;
		cout << "6: CARGAR ARCHIVO DE PRODUCTOS" << endl;
		cout << "7: SALIR DEL PROGRAMA" << endl;
		cin >> opcion;
		system("cls");

		switch (opcion) {
		case 1: {
			agregar();
			break;
		}
		case 2: {
			eliminar();
			break;
		}
		case 3: {
			modificar();
			break;
		}
		case 4: {
			mostrar();
			break;
		}
		case 5: {
			guardar();
			break;
		}
		case 6: {
			cargar();
			break;
		}
		case 7: {
			salir();
			break;
		} 
		default: {
			break;
		}
		}
	}
	return 0;
}