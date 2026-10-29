// Parcial #1: Gabriel Picado y Eimy Vega

#include <iostream>

using namespace std;

class nodo {
public:
	nodo(int v)
	{
		valor = v;
		siguiente = NULL;
	}
	nodo(int v, nodo* signodo)
	{
		valor = v;
		siguiente = signodo;
	}

private:
	int valor = 0;
	nodo* siguiente;

	friend class lista;
};

typedef nodo* pnodo;

class lista {
public:
	lista() { primero = NULL; }
	~lista();

	void InsertarInicio(int v);
	void InsertarFinal(int v);
	bool ListaVacia() { return primero == NULL; }
	void Mostrar();
	void MostrarSublistas();
	void FormarLista(long long numero);
	int buscarPosicion(int pos);
	int largoLista();

private:
	pnodo primero;

};

lista::~lista()
{
	pnodo aux;
	while (primero) {
		aux = primero;
		primero = primero->siguiente;
		delete aux;
	}
	primero = NULL;
}

int lista::largoLista() {
	int cont = 0;
	pnodo aux = primero;
	while (aux != NULL) {
		aux = aux->siguiente;
		cont++;
	}
	return cont;
}

void lista::InsertarInicio(int v)
{
	if (ListaVacia())
		primero = new nodo(v);
	else
		primero = new nodo(v, primero);
}

void lista::InsertarFinal(int v)
{
	if (ListaVacia())
		primero = new nodo(v);
	else
	{
		pnodo aux = primero;
		while (aux->siguiente != NULL)
			aux = aux->siguiente;
		aux->siguiente = new nodo(v);
	}
}

//Devuelve el valor de la posicion pos (la primera posicion es 1), si la posicion no existe devuelve 10
int lista::buscarPosicion(int pos) {
	if ((pos > largoLista()) || (pos < 1)) {
		return 10;
	}
	pnodo aux = primero;
	int cont = 1;
	while (cont < pos) {
		aux = aux->siguiente;
		cont++;
	}
	return aux->valor;
}

void lista::Mostrar()
{
	pnodo aux;
	if (primero == NULL)
		cout << "No hay elementos aquí";
	else
	{
		aux = primero;
		while (aux)
		{
			cout << aux->valor << "-> ";
			aux = aux->siguiente;
		}
		cout << endl;
	}
}

//Imprime la lista del ejercicio 4 con una sublista por linea
void lista::MostrarSublistas()
{
	pnodo aux = primero;
	while (aux)
	{
		if (aux->valor == 10) {
			cout << "010->" << endl;
		}
		else {
			cout << aux->valor << "->";
		}
		aux = aux->siguiente;
	}
	cout << endl;
}

//Separa el numero en digitos y los guarda en la lista, en el mismo orden
//Uso long long porque un numero de 10 digitos no cabe en un int
void lista::FormarLista(long long numero) {
	while (numero / 10 != 0) {
		InsertarInicio(numero % 10);
		numero = numero / 10;
	}
	InsertarInicio(numero % 10);
}
//Ejercicio #2
void DOS(double num) {
	cout << "Ejercicio #2: " << endl;

	//El numero tiene que ser entero
	if (num != (long long)num) {
		cout << "El numero no es entero." << endl;
		return;
	}
	long long numero = (long long)num;
	if (numero < 0) {
		numero = numero * -1; //abs
	}

	lista digitos;
	digitos.FormarLista(numero);
	int largo = digitos.largoLista();
	// Eel largo tiene que ser multiplo de 5
	if (largo % 5 != 0) {
		cout << "El largo del numero no es multiplo de 5." << endl;
		return;
	}

	int filas = largo / 5;
	cout << "Numero original: " << numero << endl;

	//Listas iniciales: cada 5 digitos forman una lista
	for (int f = 0; f < filas; f++) {
		lista fila;
		for (int j = 1; j <= 5; j++) {
			fila.InsertarFinal(digitos.buscarPosicion(f * 5 + j));
		}
		cout << "L" << f + 1 << " inicial: ";
		fila.Mostrar();
	}

	//Listas finales
	for (int f = 0; f < filas; f++) {
		lista fila;
		lista nueva;
		for (int j = 1; j <= 5; j++) {
			fila.InsertarFinal(digitos.buscarPosicion(f * 5 + j));
		}
		int centro = fila.buscarPosicion(3); //el centro de 5 elementos es el tercero

		for (int j = 1; j <= 5; j++) {
			int actual = fila.buscarPosicion(j);
			if (j == 3) {
				if (f % 2 == 0) {
					nueva.InsertarFinal(centro * centro); //listas pares: centro por centro
				}
				else {
					int resultado = 1;
					for (int k = 0; k < centro; k++) {
						resultado = resultado * centro; //listas impares: centro elevado al centro
					}
					nueva.InsertarFinal(resultado);
				}
			}
			else {
				if (f % 2 == 0) {
					nueva.InsertarFinal(actual + centro); //listas pares: suma el centro
				}
				else {
					nueva.InsertarFinal(actual - centro); //listas impares: resta el centro
				}
			}
		}
		cout << "L" << f + 1 << " nueva: ";
		nueva.Mostrar();
	}
}

//Ejercicio #4
void CUATRO(double num1, double num2, double num3) {
	cout << "Ejercicio #4: " << endl;

	//Los tres numeros tienen que ser enteros
	if (num1 != (long long)num1 || num2 != (long long)num2 || num3 != (long long)num3) {
		cout << "Los numeros deben ser enteros." << endl;
		return;
	}

	//Se trabaja con copias, los numeros originales no se destruyen
	long long a = (long long)num1;
	long long b = (long long)num2;
	long long c = (long long)num3;

	//positivos (abs)
	if (a < 0) { a = a * -1; }
	if (b < 0) { b = b * -1; }
	if (c < 0) { c = c * -1; }

	lista l1;
	lista l2;
	lista l3;
	l1.FormarLista(a);
	l2.FormarLista(b);
	l3.FormarLista(c);
	int n = l1.largoLista();

	// mismo largo, impar y minimo 3
	if (n != l2.largoLista() || n != l3.largoLista()) {
		cout << "Los numeros son de largo distinto." << endl;
		return;
	}
	if (n % 2 == 0) {
		cout << "El largo de los numeros no es impar." << endl;
		return;
	}
	if (n < 3) {
		cout << "El largo minimo es 3." << endl;
		return;
	}

	cout << "Numero 1 original: " << a << endl;
	cout << "Numero 2 original: " << b << endl;
	cout << "Numero 3 original: " << c << endl;

	lista listaNueva;
	int centro = (n + 1) / 2;
	int c1 = l1.buscarPosicion(centro); //centro del numero 1
	int c2 = l2.buscarPosicion(centro); //centro del numero 2
	int c3 = l3.buscarPosicion(centro); //centro del numero 3

	//En cada pasada se toma un digito de la izquierda y uno de la derecha
	for (int k = 1; k <= (n - 1) / 2; k++) {
		int izq = k;
		int der = n + 1 - k;

		//Sublista 1
		listaNueva.InsertarFinal(101);
		listaNueva.InsertarFinal(c1);
		listaNueva.InsertarFinal(l3.buscarPosicion(izq));
		listaNueva.InsertarFinal(l3.buscarPosicion(der));
		listaNueva.InsertarFinal(10); //patron final "010" (se imprime como 010)

		//Sublista 2
		listaNueva.InsertarFinal(101);
		listaNueva.InsertarFinal(c3);
		listaNueva.InsertarFinal(l1.buscarPosicion(izq));
		listaNueva.InsertarFinal(l1.buscarPosicion(der));
		listaNueva.InsertarFinal(10);

		//Sublista 3
		listaNueva.InsertarFinal(101);
		listaNueva.InsertarFinal(c1);
		listaNueva.InsertarFinal(l2.buscarPosicion(izq));
		listaNueva.InsertarFinal(c2);
		listaNueva.InsertarFinal(10);

		//Sublista 4
		listaNueva.InsertarFinal(101);
		listaNueva.InsertarFinal(c3);
		listaNueva.InsertarFinal(l2.buscarPosicion(der));
		listaNueva.InsertarFinal(c2);
		if (k == (n - 1) / 2) {
			listaNueva.InsertarFinal(101); //la ultima sublista termina en 101
		}
		else {
			listaNueva.InsertarFinal(10);
		}
	}
	cout << "Lista nueva: " << endl;
	listaNueva.MostrarSublistas();
}

int main()
{
	DOS(4567895987);
	cout << endl;
	CUATRO(31235, 89012, 43576);
	return 0;
}