// Parcial #1: Gabriel Picado y Eimy Vega

#include <iostream>

using namespace std;

class nodo { // Constructores
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

typedef nodo* pnodo; //Alias

class lista {
public:
	lista() { primero = NULL; }
	~lista();

	void InsertarInicio(int v);//No retornan nada
	void InsertarFinal(int v);
	void InsertarPos(int v, int pos);
	bool ListaVacia() { return primero == NULL; } //retorna True o False
	void Imprimir();
	void Borrar(int v);
	void Mostrar();
	void Siguiente();
	void BorrarFinal();
	void BorrarInicio();
	void borrarPosicion(int pos);
	void FormarLista(int numero);
	int ObtenerPrimero();
	int buscarPosicion(int pos);
	int posicionCircular(int pos);
	int largoLista();// retorno un valor numerico

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
	if (ListaVacia()) {
		return cont;
	}
	else {
		while (aux != NULL) {
			aux = aux->siguiente;
			cont++;
		}
		return cont;
		cout << endl;
	}

}

void lista::InsertarInicio(int v)
{
	if (ListaVacia())
	{

		primero = new nodo(v);

	}
	else
	{

		primero = new nodo(v, primero);




	}
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


void lista::InsertarPos(int v, int pos)
{
	if (ListaVacia())
		primero = new nodo(v);
	else {
		if (pos <= 1)
		{
			InsertarInicio(v);
		}
		else {
			nodo* aux = primero;
			int i = 2;
			while ((i != pos) && (aux->siguiente != NULL)) {
				i++;
				aux = aux->siguiente;
			}
			pnodo nuevo = new nodo(v);
			nuevo->siguiente = aux->siguiente;
			aux->siguiente = nuevo;

		}
	}
}

int lista::buscarPosicion(int pos) {
	if (ListaVacia()) {
		return 10;
	}
	else {
		if ((pos > largoLista()) || (pos < 0)) {
			return 10;
		}
		else {
			if (pos == 1)
			{
				return primero->valor;
				//BorrarInicio();
			}
			else {
				int cont = 2;
				pnodo aux = primero;
				while (cont < pos) {
					aux = aux->siguiente;
					cont++;
				}
				pnodo temp = aux->siguiente;
				return temp->valor;
			}
		}
	}
}

void lista::Mostrar()
{
	nodo* aux;
	if (primero == NULL)
		cout << "No hay elementos AQUI";
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

void lista::FormarLista(int numero) {
	while (numero / 10 != 0) {
		InsertarInicio(numero % 10);
		numero = numero / 10;
	}
	InsertarInicio(numero % 10);
}

//Ejercicio #1
void UNO(int num1, int num2) {
	lista l1;
	lista l2;
	lista listaNueva;
	int pos = 1;
	l1.FormarLista(num1);
	l2.FormarLista(num2);
	int numActual = l1.buscarPosicion(pos);
	cout << "Ejercicio #1: " << endl;
	if (l1.largoLista() != l2.largoLista())
	{
		cout << "Los numeros son de largo distinto." << endl;
	}
	else
	{
		cout << "Numero 1 original: " << num1 << endl;
		cout << "Numero 2 original: " << num2 << endl;
		cout << "Lista 1 inicial: ";
		l1.Mostrar();
		cout << "Lista 2 inicial: ";
		l2.Mostrar();
		while (numActual != 10)
		{
			if (pos % 2 != 0) {
				listaNueva.InsertarFinal(101);
			}
			else
			{
				listaNueva.InsertarFinal(-202);
			}
			listaNueva.InsertarFinal(numActual + 1);
			listaNueva.InsertarFinal(numActual);
			listaNueva.InsertarFinal((numActual + 1) + numActual - (numActual - 1));
			listaNueva.InsertarFinal((numActual - 1));
			pos++;
			if ((pos - 1) % 2 != 0) {
				listaNueva.InsertarFinal(-101);
				numActual = l2.buscarPosicion(pos);
			}
			else
			{
				listaNueva.InsertarFinal(202);
				numActual = l1.buscarPosicion(pos);
			}
		}
		pos--;
		while (pos != 0)
		{
			if (pos % 2 != 0) {
				listaNueva.InsertarFinal(-202);
				numActual = l2.buscarPosicion(pos);
			}
			else
			{
				listaNueva.InsertarFinal(101);
				numActual = l1.buscarPosicion(pos);
			}
			listaNueva.InsertarFinal(numActual + 1);
			listaNueva.InsertarFinal(numActual);
			listaNueva.InsertarFinal((numActual + 1) + numActual - (numActual - 1));
			listaNueva.InsertarFinal((numActual - 1));
			pos--;
			if (pos >= 0)
			{
				if ((pos - 1) % 2 != 0) {
					listaNueva.InsertarFinal(202);
					numActual = l2.buscarPosicion(pos);
				}
				else
				{
					listaNueva.InsertarFinal(-101);
					numActual = l1.buscarPosicion(pos);
				}
			}
		}
		cout << "Lista nueva: ";
		listaNueva.Mostrar();
	}
}

//Ejercicio #2

//Ejercicio #3
int lista::posicionCircular(int pos) {
	int cont = 2;
	pnodo aux = primero;
	if ((pos > largoLista()) || (pos < 0)) {
		pos -= largoLista();
	}
	if (pos == 1)
	{
		return primero->valor;
		//BorrarInicio();
	}
	while (cont < pos) {
		aux = aux->siguiente;
		cont++;
	}
	pnodo temp = aux->siguiente;
	return temp->valor;
}

void TRES(lista& l) {
	int tamano = l.largoLista();
	cout << "Ejercicio #3: " << endl;
	if (tamano % 2 != 0)
	{
		cout << "Lista original: ";
		l.Mostrar();
		int pos = 0;
		lista listaNueva;
		while (tamano != 0)
		{
			if (pos % 2 == 0)
			{
				listaNueva.InsertarFinal(101);
			}
			else
			{
				listaNueva.InsertarFinal(-202);
			}
			listaNueva.InsertarFinal(l.posicionCircular(pos + 1) + l.posicionCircular(pos + 3) - l.posicionCircular(pos + 5));
			if (pos % 2 == 0)
			{
				listaNueva.InsertarFinal(-101);
			}
			else
			{
				listaNueva.InsertarFinal(202);
			}
			pos++;
			tamano--;
		}
		cout << "Lista nueva: ";
		listaNueva.Mostrar();
	}
	else
	{
		cout << "El tamano de la lista no es impar.";
	}
}

int main()
{
	UNO(612345, 107895);

	//Ejercicio 3
	lista l3;
	l3.InsertarFinal(6);
	l3.InsertarFinal(1);
	l3.InsertarFinal(5);
	l3.InsertarFinal(8);
	l3.InsertarFinal(9);
	TRES(l3);
	return 0;
}


