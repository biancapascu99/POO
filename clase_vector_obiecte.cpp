#include "pch.h"
#include <iostream>

using namespace std;

class Object
{
public:
	Object() {};
	virtual ~Object() {}; //cout << "Am sters obiect" << endl;
	virtual void display() = 0;

};

class ObArray : public Object
{
	Object **p; // vector de pointeri
	int size; // numar de elemente la un moment dat
	int grows; // increment de creştere a dimensiunii
	int dimens; // dimensiune vector
public:
	ObArray(int grows = 0, int dimens = 0, int size = 0);//Constructor
	~ObArray();//Destructor
	ObArray(ObArray&);
	void RemoveAll();//Elimina toate obiectele din vector
	int getSize(); // Intoarce numarul de elemente din vector.
	int add(Object* x); //Adauga un element la vector.
	int insertAt(int i, Object *x);//Insereaza un element pe // o pozitie data
	int removeAt(int i); //Elimina elementul de pe pozitia i
	Object* getAt(int i); //Intoarce elementul de la pozitia i
	void display();// Afisare elementelor din tablou.

	friend ostream& operator<<(ostream&, ObArray&);
	void operator=( ObArray&);
};

ObArray::ObArray(int grows, int dimens, int size)
{
	this->size = size;
	this->grows = grows;
	this->dimens = dimens;
	p = new Object*[dimens];
}

ObArray::~ObArray()
{
	delete[] p;
	//cout << " am sters ";
}

ObArray::ObArray(ObArray &array)
{
	this->size = array.size;
	this->grows = array.grows;
	this->dimens = array.dimens;
	p = new Object*[this->dimens];
	for (int i = 0; i < size; ++i)
	{
		Object* aux(array.getAt(i));
		p[i] = aux;
	}
}
void ObArray::operator=(ObArray& array)
{
	this->size = array.size;
	this->grows = array.grows;
	this->dimens = array.dimens;
	p = new Object*[this->dimens];
	for (int i = 0; i < size; ++i)
	{
		Object* aux(array.getAt(i));
		p[i] = aux;
	}
}

int ObArray::getSize()
{
	return size;
}

int ObArray::add(Object* x)
{
	if (size + 1 <= dimens)
	{
		size++;
		p[size - 1] = x;
	}
	else
	{
		dimens = dimens + grows;
		Object** nou;
		nou = new Object*[dimens];
		for (int i = 0; i < size; i++)
		{
			nou[i] = p[i];

		}
		size++;
		nou[size-1] = x;
		p = nou;
	}
	return size;
}

void ObArray::RemoveAll()
{
	//for (int i = 0; i < size; ++i)
	//{
	//	delete p[i];
	//}
	size = 0;
}

int ObArray::insertAt(int i, Object *x)
{
	if (i > size)
	{
		cout << "Pozitia nu exista!";
		return 0;
	}

	if (size + 1 <= dimens && i < size && i >= 0)
	{
		int j;
		size++;
		for (j = size-1; j > i; j--)
		{
			p[j] = p[j - 1];
		}
		p[i] = x;

		return 1;
	}

	if (size + 1 == dimens + 1)
	{
		dimens = dimens + grows;
		size++;

		Object** nou;
		nou = new Object*[dimens];

		for (int j = 0; j < i; j++)
		{
			nou[j] = p[j];
		}

		nou[i] = x;

		for (int j = i + 1; j < size; j++)
		{
			nou[j] = p[j - 1];
		}

		p = nou;

		return 1;
	}

}
int ObArray::removeAt(int i)
{
	if (i <= size || i < 0)
	{
		//delete p[i];
		for (int j = i + 1; j <= size; ++j)
		{
			p[j - 1] = p[j];
		}
		size--;
	}
	else
	{
		cout << "Pozitia nu exista! "<<endl;
	}
	return size;
}

Object* ObArray::getAt(int i)
{
	if (i <= size || i < 0)
	{
		return p[i];
	}
	else
	{
		cout << "Pozitia nu exista! " << endl;
		return 0;
	}
}

void ObArray::display()
{
	for (int i = 0; i < size; ++i)
	{
		p[i]->display();
		cout << endl;
	}
}

ostream& operator<<(ostream& out, ObArray& array)
{
	array.display();
	return out;
}

class Punct :public Object
{
	float x;
	float y;
public:
	Punct(float x = 0, float y = 0) { this->x = x; this->y = y; };
	~Punct() {};
	Punct(Punct&);
	void display() { cout << "(" << x << ", " << y << ")"; };

	friend ostream& operator<<(ostream&, Punct&);
	friend istream& operator>>(istream&, Punct&);
};
Punct::Punct(Punct& punct)
{
	this->x = punct.x;
	this->y = punct.y;
}

istream& operator>>(istream& in, Punct& punct)
{
	float x, y;
	in >> punct.x >> punct.y;

	return in;
}

ostream& operator<<(ostream& out, Punct& punct)
{
	punct.display();
	return out;
}

class Complex :public Object
{
	float real;
	float imaginar;
public:
	Complex(float a = 0, float b = 0) { this->real = a; this->imaginar = b; }
	~Complex() {};
	Complex(Complex&);
	float get_real();
	float get_imag();
	void display() { cout << real << " + " << imaginar<<"i" ; };

	friend ostream& operator<<(ostream&, Complex&);
	friend istream& operator>>(istream&, Complex&);
};

float Complex::get_real()
{
	return real;
}

float Complex::get_imag()
{
	return imaginar;
}

Complex::Complex(Complex& complex)
{
	this->real = complex.real;
	this->imaginar = complex.imaginar;
}


istream& operator>>(istream& in, Complex& complex)
{
	float real, imaginar;
	in >> complex.real >> complex.imaginar;

	return in;
}

ostream& operator<<(ostream& out, Complex& complex)
{
	complex.display();
	return out;
}

int main()
{
	int n; cout << "Numarul de puncte: " << endl;
	cin >> n;
	ObArray ob1(2, 2, 0);
	cout << "Citire vector puncte: " << endl;
	for (int i = 0; i < n; i++)
	{
		Punct* p = new Punct;
		cin >> *p;
		ob1.add(p);
	}
	cout << "Vectorul de puncte este: " << endl;
	cout << ob1 << endl;
	cout << "Numarul de numere complexe" << endl;
	int m;
	cin >> m;
	ObArray ob2(3, 1, 0);
	cout << "Citire numere compelxe" << endl;
	for (int i = 0; i < m; i++)
	{
		Complex* p = new Complex;
		cin >> *p;
		ob2.add(p);
	}
	cout << "Vectorul de numere complese este: " << endl;
	cout << ob2;

	for (int i = 0; i < ob1.getSize(); i++)
	{
		delete ob1.getAt(i);
	}

	for(int i=0;i<ob2.getSize();i++)
	{
		delete ob2.getAt(i);
	}
}
