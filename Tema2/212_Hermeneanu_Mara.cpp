#include<bits/stdc++.h>
#include<ctime>
using namespace std;

class Persoana{
protected:

    string nume;
    string cnp;
    static int np; ///Variabila statica folosita pentru a numara cate persoane avem declarate

public:
    Persoana(string nume = "", string cnp = ""){ //Constructor de init si param
    np++;
    try{ //try & catch
        for (unsigned int i=0;i<cnp.length();i++)
            if (cnp[i]<'0'|| cnp[i]>'9')
                throw 1; 
    }
    catch(int i){
        cout<<"Eroare constructor, CNP-ul persoanei poate contine doar cifre.\n";
        exit(EXIT_FAILURE); 
    }

    
    int luna = (cnp[3]-'0')*10 + (cnp[4]-'0');
    int ziua = (cnp[5]-'0')*10 + (cnp[6]-'0');

    if (cnp != ""){
        if (luna > 12 || ziua > 31 || luna == 0 || ziua == 0 || cnp.length() != 13){
            cout<<"Eroare citire, nu ati introdus un CNP valid\n";
            exit(EXIT_FAILURE); 
        }
    }
    

    this->cnp=cnp; 
    this->nume=nume; 
    }


    Persoana(const Persoana& p){ //Constructor de copiere
        this->nume = p.nume;
        this->cnp = p.cnp;
       
    }
    
    virtual ~Persoana(){ //Destructor virtual
    }

    virtual void citire(istream& in);
    virtual void afisare(ostream& out);

    
    friend istream& operator>>(istream&, Persoana&);
    friend ostream& operator<<(ostream&, Persoana&);

    int calculVarsta();

    static void numarPersoane(){
        cout<<np;
    }
    Persoana& operator=(const Persoana&);
};

int Persoana::np; // Declarare variabila

void Persoana::citire(istream &in){
    string x;
    cout<<"CNP:";
    in>>x;
       
    try{
        for (unsigned int i=0;i<x.length();i++)
            if (x[i]<'0'|| x[i]>'9')
                throw 1;
    }
    catch(int i){
        cout<<"Eroare citire, CNP-ul persoanei poate contine doar cifre.\n";
        exit(EXIT_FAILURE);
    }

    
    int luna = (x[3]-'0')*10 + (x[4]-'0');
    int ziua = (x[5]-'0')*10 + (x[6]-'0');

    if (luna > 12 || ziua > 31 || luna == 0 || ziua == 0 || x.length() != 13){
        cout<<"Eroare citire, nu ati introdus un CNP valid\n";
        exit(EXIT_FAILURE); 
        
    }    

    this->cnp=x;
    cout<<"Nume:";
    in.get();
    string z;
    getline(in,z); //citire string cu spatii pana la enter 
    this->nume=z;
}
void Persoana::afisare(ostream& out){
    out<<"CNP: "<<this->cnp<<"\n";
    out<<"Nume: "<<this->nume<<"\n";
}
istream& operator>>(istream& in,Persoana& p){
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Persoana& p){
    p.afisare(out);
    return out;
}


Persoana& Persoana::operator=(const Persoana& p){
    if(this!=&p){
        this->nume = p.nume;
        this->cnp = p.cnp;
    }
    return *this;
}

int Persoana::calculVarsta(){
    
    int an;
    int nr = (cnp[1]-'0')*10 + (cnp[2]-'0');
    int luna = (cnp[3]-'0')*10 + (cnp[4]-'0');
    //cout<<luna;
    int ziua = (cnp[5]-'0')*10 + (cnp[6]-'0');
    //cout<<ziua;
    int varsta = 0;

    time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    //cout << "an curent = " << timePtr->tm_year+ 1900 << endl;
    //cout << "luna curenta = " << timePtr->tm_mon +1 << endl;
    //cout << "ziua curenta = " << timePtr->tm_mday << endl;
    if (cnp[0]=='1' || cnp[0]=='2')
        an = nr + 1900;
    else if(cnp[0]=='5' || cnp[0]=='6')
        an = nr + 2000;
    //else 
        //cout <<"Varsta se calculeaza doar pentru persoane nascute dupa 1900\n";       

    if(timePtr->tm_mon +1 > luna){
        varsta = (timePtr->tm_year+1900) - an;
    }    
    if(timePtr->tm_mon +1 < luna)
    {
        varsta = (timePtr->tm_year+1900) - an - 1;
    }
    if(timePtr->tm_mon +1 == luna)
    {
        if(timePtr->tm_mday >= ziua)
            varsta = (timePtr->tm_year+1900) - an;
        else
        {
            varsta = (timePtr->tm_year+1900) - an - 1;
        }
            
    }

    return varsta;

}


///////////////////////////////////////////////////////////////////////////////////////////////



class Abonat: public Persoana{
    int nrMaxCarti;
    int nrCartiImprumutate;
    int pretAbonament;
public:
    Abonat(string nume = "", string cnp = "", int nrmaxc= 0, int nrcimp = 0,int pretab =0):Persoana(nume,cnp){ //constructor
        pretAbonament = pretab;
        try{
          if (nrmaxc>pretAbonament)
            throw 1;  
        }
        catch(int i){
            cout<<"Eroare constructor, nr. maxim de carti trebuie sa fie mai mic ";
            cout<< "decat pretul abonamentului\n";
            exit(EXIT_FAILURE);
        }
        nrMaxCarti = nrmaxc;
        try{
          if (nrcimp>nrmaxc)
            throw 1;  
        }
        catch(int i){
            cout<<"Eroare constructor, nr. de carti imprumutate trebuie sa fie mai mic ";
            cout<< "decat nr. max de carti \n";
            exit(EXIT_FAILURE);
        }
        nrCartiImprumutate = nrcimp;
    }

    Abonat(const Abonat& a):Persoana(a){ //constructor de copiere 
        nrMaxCarti = a.nrMaxCarti;
        nrCartiImprumutate = a.nrCartiImprumutate;
        pretAbonament = a.pretAbonament;

    }

    ~Abonat(){  // destructor  /// nu este nevoie sa avem virtual in derivata
    }; 

    void citire(istream& in);
    void afisare(ostream& out);

    
    friend istream& operator>>(istream&, Abonat&);
    friend ostream& operator<<(ostream&, Abonat&);

    Abonat& operator=(const Abonat&);
};

void Abonat::citire(istream& in){
    Persoana::citire(in);
    cout<<"Dati pretul abonamentului:";
    in>>pretAbonament;
    cout<<"Dati nr. max. de carti:";
    int nr;
    in>>nr;
    try{
        if (nr>pretAbonament)
        throw 1;  
    }
    catch(int i){
            cout<<"Eroare constructor, nr. maxim de carti trebuie sa fie mai mic ";
            cout<< "decat pretul abonamentului\n";
            exit(EXIT_FAILURE);
    }
    nrMaxCarti = nr;
    cout<<"Dati nr. de carti imprumutate:";
    in>>nr;
    try{
        if (nr>nrMaxCarti)
        throw 1;  
    }
    catch(int i){
        cout<<"Eroare constructor, nr. de carti imprumutate trebuie sa fie mai mic ";
        cout<< "decat nr. max de carti \n";
        exit(EXIT_FAILURE);
    }
    nrCartiImprumutate=nr;
}

void Abonat::afisare(ostream& out){
    Persoana::afisare(out);
    out<<"Numarul maxim de carti:";
    out<<nrMaxCarti<<"\n";
    out<<"Numarul de carti imprumutate:";
    out<<nrCartiImprumutate<<"\n";
    out<<"Pretul abonamentului:";
    out<<pretAbonament<<"\n";

}

istream& operator>>(istream& in,Abonat& a){
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Abonat& a){
    a.afisare(out);
    return out;
}

Abonat& Abonat::operator=(const Abonat& a){
    if(this!=&a){
        Persoana::operator=(a);
        nrMaxCarti = a.nrMaxCarti;
        nrCartiImprumutate = a.nrCartiImprumutate;
        pretAbonament = a.pretAbonament;
    }
    return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////////


class Dosar{
    vector<Abonat*> vectAbonati;
    int nrAbonati;  

public:

    Dosar(vector<Abonat*> vectAbonati = {}, int nrAbonati = 0){ //constructor
        for(unsigned int i=0;i<vectAbonati.size();i++){
            this->vectAbonati.push_back(vectAbonati[i]);
        }
        this->nrAbonati = nrAbonati;
    }
    Dosar(const Dosar &d){  //constructor de copiere
        
        for(unsigned int i=0;i<this->vectAbonati.size();i++){
            delete this->vectAbonati[i];
        }

        for(unsigned int i=0;i<d.vectAbonati.size();i++){
            this->vectAbonati.push_back(d.vectAbonati[i]);
        }
        this->nrAbonati = d.nrAbonati;
    }

    ~Dosar(){ // destructor
        for(unsigned int i=0;i<this->vectAbonati.size();i++){
            delete this->vectAbonati[i];
        }
        //vectAbonati.clear();
    }

    void citire(istream& in);
    void afisare(ostream& out);

    
    friend istream& operator>>(istream&, Dosar&);
    friend ostream& operator<<(ostream&, Dosar&);

    Dosar& operator=(const Dosar&);
};


Dosar& Dosar::operator=(const Dosar& d){ 
    if(this!=&d){
        for(unsigned int i=0;i<this->vectAbonati.size();i++){
            delete this->vectAbonati[i];
        }

        for(unsigned int i=0;i<d.vectAbonati.size();i++){
            this->vectAbonati.push_back(d.vectAbonati[i]);
        }
        this->nrAbonati = d.nrAbonati;
    }
    return *this;
}


void Dosar::citire(istream& in){
    cout << "Nr de abonati:\n";
    in >> nrAbonati;
    if (nrAbonati != 0){
        cout << "Introduceti datele abonatilor:\n";
        Abonat *a = new Abonat;
        for(int i=0;i<nrAbonati;i++){
            in >> *a;
            vectAbonati.push_back(a);
        }
        
    }
    else{
        cout<<"Numarul de abonati trebuie sa fie mai mare decat 0";
        exit(EXIT_FAILURE);
    }
    
}   

void Dosar::afisare(ostream& out){
    cout << "Dosarul contine " << nrAbonati << " abonat(i)\n";
    for(int i=0;i<nrAbonati;i++){
        out << "Abonatul " << i+1 << ":\n";
        out << *vectAbonati[i];


    }    
}

istream& operator>>(istream& in,Dosar& d){
    d.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Dosar& d){
    d.afisare(out);
    return out;
}


//////////////////////////////////////////////////////////////////////////////////////////////


void eticheta(Persoana *&p, int &i) {
    string s;
    cout<<"\n";
    cout<<"Entitate " << i+1 << ": "<< " Persoana/Abonat? ";
    cin>>s;
    cout<<"--------------------------\n";
    
    try{
        if(s=="persoana" || s== "Persoana"){
                p=new Persoana;
                cin>>*p;
                i++;
        }
        else
            if(s=="abonat" || s == "Abonat"){
                p=new Abonat;
                cin>>*p;
                i++;
            }
            else
                throw 10;
    }
    catch (bad_alloc var){
        cout << "Eroare de alocare\n";
        exit(EXIT_FAILURE);
    }
    catch(int j){
        cout<<"Invalid. Incercati persoana sau abonat.\n ";
    }
}


int main()
{
	system("CLS");
    int no;
    int m;
    int nd;
    int npd;
    bool tixe = false;

    vector<Dosar> D;

    Persoana **p;
    Abonat *a=(Abonat*)new Persoana; // exemplu downcast 


  do{
        cout<<"\t\t\t\t\tHermeneanu Mara - Grupa: 212 - Proiect: 11 "<<endl;
        cout<<"\n\n\t\t\t\t\t\t\tMENIU"<<endl;
        cout<<"========================================================================================================================"<<endl;

        cout<<endl;
        cout<<"\n\t1.Citire a n obiecte"<<endl; // Upcast// Late binding interactiv
        cout<<"\t2.Afisare obiecte citite"<<endl;
        cout<<"\t3.Afisare numar de persoane"<<endl;
        cout<<"\t4.Downcast"<<endl;
        cout<<"\t5.Calculul varstei unei persoane"<<endl;
        cout<<"\t6.Citire dosare"<<endl;
        cout<<"\t7.Afisare dosare"<<endl;
        cout<<"\t0.Iesire."<<endl;
        cout<<"\n\nIntroduceti o actiune: ";
        cin>>m;

        switch(m)
        {
            case 0:
                cout<<endl;
                cout<<"\tExit"<<endl;
                tixe = true;
                return 0;

            case 1:
                cout<<"Introduceti numarul de obiecte: ";
                cin >> no;
                try{
                    p = new Persoana*[no];
                    for(int i=0;i<no;)
                        eticheta(p[i],i); 
                }
                catch (bad_alloc var){
                    cout<<"Eroare de alocare\n";
                    exit(EXIT_FAILURE);
                }
                break;
            case 2: 
                cout<<"\nAfisam persoanele citite anterior:\n";
                for(int i=0;i<no;i++){
                    cout<<"\n"<<*p[i]; 
                    cout<<"--------------------------\n";
                }
                break;
            case 3:
                cout << "Numarul de persoane declarate: ";
                Persoana::numarPersoane();

                break;
            case 4: 
                cout << "Aloc memorie pentru un obiect de tip persoana pe care il etichetez ca abonat";
                cin>>*a;
                cout<<"--------------------------\n";
                cout<<*a;
                break;
            case 5:
                if(no>0){
                    cout <<"\nIntroduceti nr. de ordine al persoanei:";
                    cin>> npd;
                    cout <<"\nVarsta persoanei este de ";
                    cout << p[npd-1]->calculVarsta();
                    cout << " de ani";
                }
                else
                    cout<<"Nu ati citit nicio persoana\n";
            
                break;
            case 6:
                cout<< "Nr. dosare:";
                cin>>nd;
                D.resize(nd);
                for(int i=0;i<nd;i++){
                    cout<<"Dosarul " << i+1 << ":\n";
                    cin>> D[i];
                }    
                break;    
            case 7:
                for(int i=0;i<nd;i++){
                    cout<<"Dosarul " << i+1 << ":\n";
                    cout << D[i];
                    cout<<"--------------------------\n";
                } 
                break;       
            default:
                cout<<"Optiune invalida";
                break;    

        }   
        cout << "\nApasa ENTER pentru a continua...";
        cin.get();
        cin.get();
        if (tixe) break;
        system("CLS");

    } while(true);

    return 0;

}