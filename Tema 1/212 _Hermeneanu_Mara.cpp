#include<iostream>
using namespace std;

class Nod{
    char info;
    Nod* next;
    friend class Coada_de_caractere;
public:
    Nod(char info = ' ', Nod* next = NULL){
        this-> info = info;
        this-> next = next;
    }
    ~Nod(){
    } // sau = default
	Nod* get_next();
    void set_info(char);
    char get_info();

    // Nod& operator=(Nod *x){
    //     if (this != x){
    //         this->info = x->info;
    //         this->next = x->next;
    //     }
    //     return *this;
    //  }
};

Nod* Nod::get_next()
{
	return this->next;
}

void Nod::set_info(char c){
    info = c;
}
char Nod::get_info(){
    return info;
}

class Coada_de_caractere{
    Nod *rear, *front;

public:
    Coada_de_caractere(){
        this->front = NULL;
        this->rear = NULL;
    }

    char coada_pop();
    void coada_push(char x);
    bool coada_isempty();
    void afisare(ostream &out);
    void citire(istream &in);
    //char afiseaza_head();
    void afisare_fara_golire();
    friend istream& operator>>(istream& in, Coada_de_caractere& x); //push uri succesive
    friend ostream& operator<<(ostream& out, Coada_de_caractere& x); //afisare concomitent cu golire
    friend Coada_de_caractere operator+(Coada_de_caractere& x,Coada_de_caractere& y); //concatenare
    friend Coada_de_caractere operator-(Coada_de_caractere& x,Coada_de_caractere& y); //cod ascii mai mare
    Coada_de_caractere& operator=(const Coada_de_caractere& x);
    ~Coada_de_caractere();
};


bool Coada_de_caractere::coada_isempty()
{
    return (front == NULL);
}


void Coada_de_caractere::coada_push(char x)
{

    if(rear == NULL){
        rear = new Nod(x);
        front = rear;
    }
    else{
        Nod *aux = new Nod;
        aux->info = x;
        aux->next = NULL;
        rear->next = aux;
        rear = aux;
    }
}

void Coada_de_caractere::citire(istream &in){

    char caracter;
	char finish = '~';
	in>>caracter;
	while (caracter != finish){

        this->coada_push(caracter);
		in >> caracter;
    }

}

inline istream& operator>>(istream& in, Coada_de_caractere& x){
    x.citire(in);
    return in;
}


char Coada_de_caractere::coada_pop()
{
    if(this->coada_isempty()){
        cout<< "Coada este vida" <<endl;
        return 0;
        }


    char elem = front->info;

    if (front -> next != NULL){
        Nod *aux = front->next;
		delete front;
        front = aux;

    }
    else{
        front = NULL;
        rear = NULL;
    }

    return elem;
}


void Coada_de_caractere::afisare_fara_golire(){
   if (this -> coada_isempty()){
       cout <<"Coada e vida\n";
   }
   else{
        Nod* temp;
        temp = front;
        while(temp != NULL){
            cout<< temp -> info;
            cout << ' ';
            temp = temp->next;
        }
        cout<<"\n";
   }
}

void Coada_de_caractere::afisare(ostream &out){
   char caracter;
   if (this -> coada_isempty()) cout <<"Coada e vida\n";
   else
        while(!(this->coada_isempty())){
            caracter = coada_pop();
            out<< caracter;
            out<<' ';
        }
}


inline ostream& operator<<(ostream& out, Coada_de_caractere& x){
    x.afisare(out);
    return out;
}


Coada_de_caractere::~Coada_de_caractere()
{
    while(front != NULL){
            Nod *aux;
            aux = front->next;
            delete front;
            front = aux;
    }
}

inline Coada_de_caractere operator-(Coada_de_caractere& x,Coada_de_caractere& y){
    Coada_de_caractere z;
    char c1, c2;

    while( ! x.coada_isempty() && ! y.coada_isempty())
    {
        c1 = x.coada_pop();
        c2 = y.coada_pop();

        if (c1 > c2){
            z.coada_push(c1);
        }
        else{
            z.coada_push(c2);
        }
    }
    // - fara golire 
    // Nod *nc1, *nc2;
    // nc1 = x.front;
    // nc2 = y.front;
    // while (nc1 != NULL && nc2 != NULL){
    //     c1 = nc1->get_info();
    //     c2 = nc2->get_info();
    //     if (c1 > c2){
    //         z.coada_push(c1);
    //     }
    //     else{
    //         z.coada_push(c2);
    //     }
    //     nc1 = nc1->get_next();
    //     nc2 = nc2->get_next();
    // }
    return z;

}

Coada_de_caractere& Coada_de_caractere:: operator=(const Coada_de_caractere& x){
	while (!this->coada_isempty() ){
		    this->coada_pop();
	}

	Nod* aux = x.front;
	while (aux != NULL)
	{
		this->coada_push(aux->info);
		aux = aux->next;
    }

    return *this;

}


inline Coada_de_caractere operator+(Coada_de_caractere& x,Coada_de_caractere& y){
    Coada_de_caractere z;
    char c;
    Nod *aux = x.front;
    while (aux != NULL){
        c = aux->get_info();
        z.coada_push(c);
        aux = aux -> get_next();
    }
    aux = y.front;
    while (aux != NULL){
        c = aux->get_info();
        z.coada_push(c);
        aux = aux -> get_next();
    }
    // + cu golire
    // while (! x.coada_isempty())
    // {   c = x.coada_pop();
    //     z.coada_push(c);
    // }
    // while (! y.coada_isempty())
    // {
    //     c = y.coada_pop();
    //     z.coada_push(c);
    // }
    return z;
}


int main()
{
	system("cls");
    int m;
    int ct;
    int n = 0;
    Coada_de_caractere *C = nullptr;
    Coada_de_caractere coada;
    bool exit = false;

  do{
        cout<<"\t\t\tHermeneanu Mara - Grupa: 212 - Proiect: 5 - Coada de caractere"<<endl;
        cout<<"\n\n\t\t\t\t\t\t\tMENIU"<<endl;
        cout<<"========================================================================================================================"<<endl;

        cout<<endl;
        cout<<"\n\t1.Adaugare elemente in coada"<<endl;
        cout<<"\t2.Eliminearea unui caracter din coada"<<endl;
        cout<<"\t3.Verificare daca coada este vida"<<endl;
        cout<<"\t4.Afisarea cozii concomitent cu golirea ei"<<endl;
        cout<<"\t5.Concatenarea a doua cozi"<<endl;
        cout<<"\t6.Diferenta a doua cozi"<<endl;
        cout<<"\t0.Iesire."<<endl;
        cout<<"\n\nIntroduceti o actiune: ";
        cin>>m;

        switch(m)
        {
            case 0:
                cout<<endl;
                cout<<"\tExit"<<endl;
                exit = true;
                return 0;

            case 1:
                cout<<"Introduceti numarul de cozi:";
                cin>>n;
                cout<<"Pentru fiecare coada se citesc caractere pana la inalnirea caracterului '~':\n";
                C = new Coada_de_caractere[n];

                for(int i = 0; i<n; i++){
                    cin>>C[i];
                }

                for(int i=0;i<n;i++){
                         cout<< "Coada " << i+1 << ": ";
                         C[i].afisare_fara_golire();
                }
                break;

            case 2:
                ct = 0;
                for (int i=0; i<n;i++){
                    if(!C[i].coada_isempty())
                        ct++;
                }
                if (n==0 || ct<2){
                    cout<< "Nu exista nicio coada nevida";
                }
                else{
                    for(int i=0;i<n;i++){
                         cout<< "Coada " << i+1 << ": ";
                         C[i].afisare_fara_golire();
                     }

                   cout << "\nIndicati numarul de ordine al cozii din care doriti sa eliminati un caracter:\n";
                    int nr;
                    cin >> nr;
                    char caracter;

                    if (nr > n) cout <<"Nu ai citit " << nr<<" cozi\n";
                    else{
                        caracter = C[nr-1].coada_pop();
                        if (caracter == 0)
                            cout<<"Eroare la stergere!"<<endl;
                        else{
                            cout<<"Caracterul '"<< caracter <<"' a fost sters cu succes."<<endl;
                            cout << "Coada devine: " ;
                            C[nr-1].afisare_fara_golire();

                        }
                    }

                }
                break;

            case 3:
                if (n==0){
                    cout<< "Nu ati citit nicio coada";
                }
                else{
                    for(int i=0;i<n;i++){
                    bool rezultat;
                    rezultat = C[i].coada_isempty();
                    if( rezultat == 0)
                        cout<<"Coada "<< i+1 <<" nu este vida"<<endl;
                    else
                        cout<<"Coada " << i+1 <<" este vida"<<endl;
                    }
                }
                break;
            case 4:
                for(int i = 0; i<n; i++){
                    cout << "\nCoada " << i+1 << ": ";
                    cout << C[i];
                }
                break;

            case 5:
                for(int i=0;i<n;i++){
                    cout<< "Coada " << i+1 << ": ";
                    C[i].afisare_fara_golire();
                }
                ct = 0;
                for (int i=0; i<n;i++){
                    if(!C[i].coada_isempty())
                        ct++;
                }
                if (n<2 || ct<2){
                    cout<<"Nu exista suficiente cozi nevide";
                }
                else{
                    cout << "Indicati numarul de ordine al cozilor pe care vreti sa le concatenati:\n";
                    int nr1,nr2;
                    cin >> nr1;
                    cin >> nr2;
                    coada = C[nr1-1] + C[nr2-1];
                    cout << "Coada rezultata este: ";
                    cout << coada;
                }
                break;
            case 6:
                for(int i=0;i<n;i++){
                    cout<< "Coada " << i+1 << ": ";
                    C[i].afisare_fara_golire();
                }
                ct = 0;
                for (int i=0; i<n;i++){
                    if(!C[i].coada_isempty())
                        ct++;
                }
                if (n<2 || ct<2){
                    cout<<"Nu exista suficiente cozi nevide";
                }
                else{
                    cout << "Indicati numarul de ordine al cozilor pentru care vreti sa calcultati diferenta:\n";
                    int nr1,nr2;
                    cin >> nr1;
                    cin >> nr2;
                    coada = C[nr1-1] - C[nr2-1];
                    cout << "Coada rezultata este: ";
                    cout << coada;
                }
                break;
            default:
                cout<<"Optiune invalida\n";
                break;

        }

        cout << "\nApasa ENTER pentru a continua...\n";
        cin.get();
        cin.get();
        if (exit) break;
        system("CLS");

    } while(true);
    return 0;
}

