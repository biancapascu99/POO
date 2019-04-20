#include <iostream>
using namespace std;

class nod
{
private:
	char info;
	nod *urm;

	public:
		nod();
		nod(char, nod*);				
		char get_info();
		nod* get_urm();
		void set_urm(nod*);
	    friend class coada;

};

nod::nod()
{
	urm = NULL;
}

nod::nod(char c, nod* nod_urm = 0)
{
	this->info = c;
	this->urm = nod_urm;
}

char nod::get_info()
{
	return info;
}
nod* nod::get_urm()
{
	return urm;
}

void nod::set_urm(nod* urm_nou)
{
	urm = urm_nou;
}

class coada
{ 
	
private:
		nod* vf;
		nod* sf;
	
	public:
		coada();
		int coada_goala();
		void push(nod);
		nod* pop();
		void top();
		nod* get_vf();
		nod* get_sf();
		void set_vf(nod*);
		friend class nod;
		friend ostream& operator<<(ostream& out, coada&); 
		friend istream& operator>>(istream& in, coada&);
		friend coada operator+(coada const &, coada const &);
		friend coada operator-(coada const &, coada const &);


};
coada::coada() {
	vf = sf = 0;
}
int coada::coada_goala()
{
	return vf == 0;
}
void coada::push(nod n)
{
	nod* p;
	p = new nod(n.info, 0);
	if (coada_goala())
	{
		sf = vf = p;
	}
	else
	{
		sf->urm = p;
		sf = p;
	}
}

nod *coada::get_vf()
{
	return vf;
}

nod *coada::get_sf()
{
	return sf;
}


void coada::set_vf(nod* vf_nou)
{
	vf = vf_nou;
}


nod* coada::pop()
{
	if (coada_goala())
	{
		cout << "Coada este goala" << endl;
		return NULL;
	}
	else
	{
		nod *p;
		p = vf;
		vf = vf->urm;
		return p;
	}
}
void coada::top()
{
	if (coada_goala())
	{
		cout << "Coada este goala" << endl;
	}
	else
		cout << "Primul element al cozii este: "<< vf->info << endl;
}
ostream& operator<< (ostream& out, coada& coada1)
{
	while(!coada1.coada_goala())
	{
			cout << coada1.pop()->get_info() << " ";
	}
	cout << endl;
	return out;
}
istream& operator>> (istream& in, coada& coada1)
{
	char n;
	in >> n; 
	while (n != '$')
	{
		nod nou(n);
		coada1.push(n);
		in >> n;
	}
	return in;
}
coada operator+(coada  &q1, coada  &q2)
{
	coada q3;
	nod *p = q1.get_vf();
	if (q1.coada_goala() && q2.coada_goala())
	
		return q3;
	
	else if (q1.coada_goala() && !q2.coada_goala())
	
		return q2;
	
	else if (!q1.coada_goala() && q2.coada_goala())
	
		return q1;
	
	else
	{
		while (p != NULL)
		{
			q3.push(*p);
			p = p->get_urm();
		}
		q3.get_sf()->set_urm(q2.get_vf());

		return q3;
	}


}
coada operator-(coada &q1, coada &q2)
{
	coada q3;
	nod *p1 = q1.get_vf(), *p2 = q2.get_vf();


	while (!q1.coada_goala() && !q2.coada_goala())
	{
		p1 = q1.get_vf();
		p2 = q2.get_vf();
		if (p1->get_info() != p2->get_info())
		{
			q3.push(*p1);
			q1.pop();
			q2.pop();


		}
		else
		{
			q1.pop();
			q2.pop();
		}
	}
	return q3;


}

int main()
{
	coada q1,q2,q3,q4;
	cout << "Citire coada1 pana la caracterul $ : " << endl;
	cin >> q1;
	cout << "Citire coada2 pana la caracterul $ : " << endl;
	cin >> q2;
	q3 = q1 + q2;
	cout << "Adunarea celor doua cozi : " << q3 << endl;
	q4 = q1 - q2;
	cout << "Scaderea celor doua cozi : " << q4 << endl;
}
