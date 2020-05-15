#include<bits/stdc++.h>

using namespace std;

vector<string> materii;

class Examen{
protected:
	int indexExam;
	string materie;
	string dataExam;
	double notaScris;
	static int ne;    
public: 
	Examen(string, string, double);
	Examen(const Examen&);
	virtual ~Examen();

	void citireMaterie(istream&);
	virtual void citire(istream&);
	
	void afisareMaterie(ostream&);
    virtual void afisare(ostream&);

    friend istream& operator>>(istream&, Examen&);
    friend ostream& operator<<(ostream&, Examen&);

	Examen& operator=(const Examen&); //const 

	static void numarExamene(){  //met statica 
        cout<<ne;
    }
	void setIndexExam(int x){
		this->indexExam = x;
	}
	int getIndexExam() const{
		return indexExam;
	}

};
int Examen::ne; // declarare variabila statica

Examen::Examen(string materie = "", string dataExam = "" , double notaScris = 1){   
	ne++;
	
	if(materie.length()){
		int ok = 0;
		for(unsigned int i = 0;i<materii.size();i++){
			if (materie == materii[i]){
				this->materie = materie;
				this->indexExam = i+1;
				ok = 1;
			}
		}	
		if(!ok){
			cout<<"Eroare constructor examen - materie";
			exit(EXIT_FAILURE);
		}
	}
	else{
		this->materie = materie;
		this->indexExam = 0;
	}

    if(dataExam.length()){
		int zi = (dataExam[0]-'0')*10 + (dataExam[1]-'0');
		int luna = (dataExam[3]-'0')*10 +(dataExam[4]-'0');
		int an = (dataExam[6]-'0')*1000 + (dataExam[7]-'0')*100 + (dataExam[8]-'0')*10 + (dataExam[9]-'0'); 
		try{	
			if(dataExam.length() != 10 || zi <= 0 || zi> 31 || luna <= 0 || luna >12 || an < 1900 || an > 2020)
			throw 1;	

		}catch(int i){
        	cout<<"\nEroare constructor examen - data examen";
        	exit(EXIT_FAILURE); 
    	}
	}
	
	this->dataExam = dataExam;

	if(notaScris >= 1 && notaScris <=10)
		this->notaScris = notaScris;
	else
	{
		cout<<"\nEroare constructor examen - nota scris";
		exit(EXIT_FAILURE);
	}
		
}

Examen::Examen(const Examen& e){
	ne++;
	this->indexExam = e.indexExam;
	this->materie = e.materie;
	this->dataExam = e.dataExam;
	this->notaScris = e.notaScris;
}

Examen::~Examen(){ ne--;}

void Examen::citireMaterie(istream& in){
	
	int ok = 0;
	while (!ok){
		cout<<"\nIntroduceti denumirea materiei: ";
		string z;
		getline(in,z); 
		for(unsigned int i = 0;i<materii.size();i++){
			if (z == materii[i]){
				this->materie = z;
				this->indexExam = i+1;
				ok = 1;
			}
		}
		if(!ok){
			cout<<"Nu ati introdus o materie valida.";
		}
	}
}

void Examen::citire(istream &in){

	cout<<"Introduceti data examenului (format ZZ.LL.AAAA): "; //fara spatii 
	string dataEx;
	cin>>dataEx;

	int zi = (dataEx[0]-'0')*10 + (dataEx[1]-'0');
	int luna = (dataEx[3]-'0')*10 +(dataEx[4]-'0');
	int an = (dataEx[6]-'0')*1000 + (dataEx[7]-'0')*100 + (dataEx[8]-'0')*10 + (dataEx[9]-'0'); 
		
	while(dataEx.length() != 10 || zi <= 0 || zi> 31 || luna <= 0 || luna >12 || an < 1900 || an > 2020){
		cout <<"Nu ati introdus o data valida.";
		cout<<"Introduceti data examenului (format ZZ.LL.AAAA): ";	
		in>>dataEx;

		zi = (dataEx[0]-'0')*10 + (dataEx[1]-'0');
		luna = (dataEx[3]-'0')*10 +(dataEx[4]-'0');
		an = (dataEx[6]-'0')*1000 + (dataEx[7]-'0')*100 + (dataEx[8]-'0')*10 + (dataEx[9]-'0'); 

    }
	this->dataExam = dataEx;

	cout <<"Introduceti nota la scris: ";
	double x;
	in>>x;
	while(x<1 || x>10){
		cout<<"Nota trebuie sa fie intre 1 si 10.";
		cout<<"Introduceti nota la scris: ";
		in>>x;
	}
	this->notaScris = x; 
}
void Examen::afisareMaterie(ostream& out){
	out<<"Denumirea materiei: "<< this->materie << endl;
}
void Examen::afisare(ostream& out){
	out<<"Id examen: " << this->indexExam << endl;
	out<<"Data examenului: " << this->dataExam << endl;
	out<<"Nota la scris: "<< this->notaScris << endl; 
}

istream& operator>>(istream& in, Examen& e){
    e.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Examen& e){
    e.afisare(out);
    return out;
}

Examen& Examen::operator=(const Examen& e){
	if(this != &e){
		this->indexExam = e.indexExam;
		this->materie = e.materie;
		this->dataExam = e.dataExam;
		this->notaScris = e.notaScris;
	}	
	return *this;
}


////////////////////////////////////////////////////////////////////////////////////////
class Partial: public Examen{
	double notaOral;
	double pondereOral;
	double ponderePartial;
	double notaPartial;

	friend class ExamenFinal;
public: 
	Partial(string, string, double, double, double, double);
	Partial(const Partial&);
	~Partial();
	
	void citire(istream& in);
    void afisare(ostream& out);

	Partial& operator=(const Partial&);

};

Partial::Partial(string materie = "", string dataExam = "" , double notaScris = 1,
	double notaOral = 1, double pondereOral = 0, double ponderePartial = 0):Examen(materie, dataExam, notaScris){
		if(notaOral >=1 && notaOral <=10)
			this->notaOral = notaOral;
		else{
			cout<<"Eroare constructor partial - nota oral"; 
			exit(EXIT_FAILURE);
		}

		if(pondereOral <=100 && ponderePartial >=0)
			this->pondereOral = pondereOral;
		else{
			cout<<"Eroare constructor partial - pondere oral";
			exit(EXIT_FAILURE);
		}

		if(ponderePartial <=100 && ponderePartial >= 0)
			this->ponderePartial = ponderePartial;
		else{
			cout<<"Eroare constructor partial - pondere partial";
			exit(EXIT_FAILURE);
		}

		this->notaPartial = (this->notaScris*(100-this->pondereOral) + this->notaOral*this->pondereOral)/100;
			
}

Partial::Partial(const Partial& p):Examen(p){
	this->notaOral = p.notaOral;
	this->pondereOral = p.pondereOral;
	this->ponderePartial = p.ponderePartial;
	this->notaPartial = p.notaPartial;
}

Partial::~Partial(){}


void Partial::citire(istream &in){
	Examen::citireMaterie(in);
	Examen::citire(in);

	cout<<"Introduceti nota la oral: ";
	double x;
	in>>x;
	while(x<1 || x>10){
		cout<<"Nota trebuie sa fie intre 1 si 10.";
		cout<<"Introduceti nota la oral: ";
		in>>x;
	}
	this->notaOral = x; 

	cout<<"Introduceti ponderea notei de la oral (procente): ";
	in>>x;
	while(x<0 || x>100){
		cout<<"Ponderea trebuie sa fie intre 0 si 100.";
		cout<<"Introduceti ponderea notei de la oral: ";
		in>>x;
	}
	this->pondereOral = x;

	cout<<"Introduceti ponderea partialului (procente): "; 
	in>>x;
	while(x<0 || x>100){
		cout<<"Ponderea trebuie sa fie intre 0 si 100.";
		cout<<"Introduceti ponderea notei de la oral: ";
		in>>x;
	}
	this->ponderePartial = x;

	this->notaPartial = (this->notaScris*(100-this->pondereOral) + this->notaOral*this->pondereOral)/100;

}

void Partial::afisare(ostream& out){
	Examen::afisareMaterie(out);
    Examen::afisare(out);

	out<<"Nota oral: " << this->notaOral << endl;
	out<<"Pondere oral (procente): " << this->pondereOral<<endl;
	out<<"Pondere partial (procente): "<< this->ponderePartial<<endl;
	out<<"Nota partial: " <<this->notaPartial<<endl;
}

Partial& Partial::operator=(const Partial& p){
	if(this != &p){
		Examen::operator=(p);
		this->notaOral = p.notaOral;
		this->pondereOral = p.pondereOral;
		this->ponderePartial = p.ponderePartial;
		this->notaPartial = p.notaPartial;
	}
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////// 
class Quiz: public Examen{
	int nrItemi;
	friend class ExamenFinal;

public: 	
	Quiz(string, string, double, int);
	Quiz(const Quiz&);
	~Quiz();

	void citire(istream& in);
    void afisare(ostream& out);

	Quiz& operator=(const Quiz&);
	
	void set_materie(string materie){
		this->materie = materie;
	}
};

Quiz::Quiz(string materie = "", string dataExam = "" , double notaScris = 1,int nrItemi = 0):Examen(materie, dataExam, notaScris){

		if(nrItemi < 0 || nrItemi != round(nrItemi)){
			cout<<"Eoare constructor quiz - nr itemi";
			exit(EXIT_FAILURE);
		}	
		else{
			this->nrItemi = nrItemi;
		}	
}
Quiz::Quiz(const Quiz& q):Examen(q){
	this->nrItemi = q.nrItemi;
}
Quiz::~Quiz(){}

void Quiz::citire(istream &in){
	Examen::citireMaterie(in);     
	Examen::citire(in);

	cout << "Introduceti numarul de itemi: ";
	int x;
	in>> x;
	while(x<=0){
		cout<<"Numarul de itemi trebuie sa fie cel putin 1.";
		cout<<"Introduceti numamrul de itemi: ";
		in>>x;
	}
	this->nrItemi = x;
}

void Quiz::afisare(ostream& out){
	Examen::afisareMaterie(out);
    Examen::afisare(out);

	cout<<"Numar de itemi: "<<this->nrItemi<<endl;
}

Quiz& Quiz::operator=(const Quiz& q){
	if(this != &q){
		Examen::operator=(q);
		this->nrItemi = q.nrItemi;
	}
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////// 
class ExamenFinal:public Examen{
	int puncteExtra;
	Partial partial;
	Quiz quiz;
	bool marire;
	int notaFinala;
public:	
	ExamenFinal();
	ExamenFinal(string, string, double,int,Partial, Quiz, bool, int);
	ExamenFinal(const ExamenFinal&);
	~ExamenFinal();

	void citire(istream& in);
    void afisare(ostream& out);

	ExamenFinal& operator=(const ExamenFinal&);

	bool getMarire(){
		return marire;
	}
	int getNotaFinala() const{
		return notaFinala;
	}
	int getIndex(){
		return indexExam;
	}
};

ExamenFinal::ExamenFinal():Examen(){
	this->puncteExtra = 0;
	this->marire = 0;
	this->notaFinala = 1;
}
ExamenFinal::ExamenFinal(string materie, string dataExam, double notaScris, int puncteExtra,Partial partial, Quiz quiz, bool marire, int notaFinala):
	Examen(materie,dataExam,notaScris){
		if(puncteExtra>=0 && puncteExtra <=10)
			this->puncteExtra = puncteExtra;
		else
		{
			cout<<"Eroare constructor examen final - puncte extra";
			exit(EXIT_FAILURE);
		}
		
		if((partial.notaPartial >= 5))
			this->partial = partial; 
		else{
			cout<<"Partialul nu a fost trecut, trebuie refacut";
			exit(EXIT_FAILURE);
		}

		int nf = round((this->notaScris*(100-partial.ponderePartial) + partial.notaPartial*partial.ponderePartial)/100) + puncteExtra;
		if(nf > 10)
			nf = 10;

		if(nf == notaFinala)
			this->notaFinala = notaFinala;
		else
		{
			cout<<"Eroare constructor examen final - nota finala";
			exit(EXIT_FAILURE);
		}
			
		this->marire = marire; 
		this->quiz = quiz;


		if(marire && (quiz.notaScris > this->notaFinala)){
			this->notaFinala = round(quiz.notaScris);
		}

}
ExamenFinal::ExamenFinal(const ExamenFinal& ef):Examen(ef){
	this->puncteExtra = ef.puncteExtra;
	this->partial = ef.partial;
	this->quiz = ef.quiz;
	this->marire = ef.marire;
	this->notaFinala = ef.notaFinala;
}

ExamenFinal::~ExamenFinal(){}

void ExamenFinal::citire(istream &in){
	cout <<"\nDate partial:\n";
	Partial p;
	in>>p;
	
	while(p.notaPartial < 5){
		cout<<"\nPartialul nu a fost luat. Refaceti partialul."; 
		in.get();
		in>>p;
		
	}
	this->partial = p;

	cout<<"------------------------------";
	cout << "\nDate examen scris:\n";
	Examen::citire(in);
	cout<<"------------------------------";

	cout<<"\nPuncte extra: ";
	int x; 
	in>>x; 
	while(x<0 || x>10){
		cout<<"Punctele extra trebuie sa fie intre 1 si 10.";
		cout<<"Puncte extra:";
	}
	this->puncteExtra = x;

	cout <<"\nSe doreste marirea notei? (1/0):";
	in>>this->marire;

	if(this->marire){
		in.get();
		cout<<"------------------------------";
		cout<<"\nDate quiz:\n";
		in>> this->quiz;
		this->quiz.setIndexExam(partial.getIndexExam()); // steaza indexul quizului cu indexul partialului
	}
	
	this->notaFinala = round((this->notaScris*(100-this->partial.ponderePartial) + this->partial.notaPartial*this->partial.ponderePartial)/100) + this->puncteExtra;
	if(this->notaFinala > 10)
		this->notaFinala = 10; 

	if(marire && (this->quiz.notaScris > this->notaFinala)){
			this->notaFinala = round(this->quiz.notaScris);
		}
	this->setIndexExam(partial.getIndexExam()); // seteaza indexul examenului final cu indexul partialului

}


void ExamenFinal::afisare(ostream& out){

	out<< "\nSituatie partial:\n";
	out<< this->partial;
	out << "\nSituatie examen scris:\n";
    Examen::afisare(out);
	out<<"\nPuncte extra: " << this->puncteExtra<<endl;
	out<<"\nDoreste marire: (1/0) " << this->marire<<endl;
	if(this->marire){
		out<<"\nSituatie quiz:\n";
		out<<quiz;
	}
	out<< "\nNota finala: " << this->notaFinala<<endl;

}

ExamenFinal& ExamenFinal::operator=(const ExamenFinal& ef){
	if(this != &ef){
		Examen::operator=(ef);
		this->puncteExtra = ef.puncteExtra;
		this->partial = ef.partial;
		this->quiz = ef.quiz;
		this->marire = ef.marire;
		this->notaFinala = ef.notaFinala;
	}
	return *this;
}


////////////////////////////////////////////////////////////////////////////////////
class Student{
	int nrExamene;
	string nume;
	vector<ExamenFinal> examene;
	static int ns;

public: 
	Student(int, string, vector<ExamenFinal>);
	Student(const Student&);
	~Student();

	void citire(istream& in);
    void afisare(ostream& out);

    friend istream& operator>>(istream&, Examen&);
    friend ostream& operator<<(ostream&, Examen&);

	Student& operator=(const Student&);

	int getNrStudenti() const{   //met const 
		return ns;
	}
	int nrquizuri();

	vector<int> materiiPicate(); 

	string getNume(){ 
		return nume;
	}

};


int Student::ns; // declarare variabila

Student::Student(int nrExamene = 0, string nume = "", vector<ExamenFinal> = {}){
	ns++;
	if(nrExamene >=0)
		this->nrExamene = nrExamene;
	else
	{
		cout<<"\nEroare constructor student - nr examene";
		exit(EXIT_FAILURE);
	}

	try {
        for (unsigned int i = 0; i<nume.size(); i++)
            if (nume[i] != ' '){
                if (nume[i] < 'A' || nume[i] > 'Z'){
                    if(nume[i] < 'a' || nume[i] > 'z'){
                        throw 1;
                    }
                }   
            }
    }catch (int x){
        cout <<"\nEroare constructor - Numele studentului trebuie sa contina doar litere";
        exit(EXIT_FAILURE);
    }
	this->nume = nume;
	
	for(unsigned int i=0;i<examene.size();i++){
		this->examene.push_back(examene[i]);
	}

	
}
Student::Student(const Student& s){

	this->nrExamene = s.nrExamene;
	this->nume = s.nume;

    for(unsigned int i=0;i<s.examene.size();i++){
        this->examene.push_back(s.examene[i]);
    }
}

Student::~Student(){
	ns--;
}


void Student::citire(istream &in){
	int ok=0;
	string z;
	
    while(!ok){
        cout<<"Introduceti numele studentului:";
        getline(in,z); //citire string cu spatii pana la enter 
        ok=1;
        for (unsigned int i = 0; i<z.size(); i++)
            if (z[i] != ' '){
                if (z[i] < 'A' || z[i] > 'Z'){
                    if(z[i] < 'a' || z[i] > 'z'){
                        ok = 0;
                    }
                }
            }
        if (!ok) 
            cout <<"Numele studentului trebuie sa contina doar litere\n";
    }

    this->nume=z;
	cout<<"Introduceti numarul de examene finale:";
	int x;
	in>>x;
	while(x <=0){
		cout<<"Numarul de examene trebuie sa fie cel putin 1.";
		cout<<"Introduceti numarul de examene:";
		in>>x;
	}
	this->nrExamene = x;
	cout<<"Introduceti datele examenelor finale:\n";
	
	ExamenFinal e;
	for(int i=0;i<nrExamene;i++){
		cout<<"Examen final  "<<i+1 << ":";
		in.get();
		in >> e;
		this->examene.push_back(e);
	}
}

void Student::afisare(ostream& out){
	out << "\nNume student: " << this->nume << endl;
	out << "Numar de examene: " << this->nrExamene << endl;
	for(int i=0;i<nrExamene;i++){
    	out << "Examenul " << i+1 << ":\n";
        out << examene[i];
		cout<<"--------------------------\n";
    }    

}

istream& operator>>(istream& in, Student& s){
    s.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Student& s){
    s.afisare(out);
    return out;
}


Student& Student::operator=(const Student& s){
	if(this != &s){
		this->nrExamene = s.nrExamene;
		this->nume = s.nume;
		examene.clear();

		for(unsigned int i=0;i<s.examene.size();i++){
			this->examene.push_back(s.examene[i]);
		}
	}
	return *this;
}

int Student::nrquizuri(){
	int nrq = 0;
	for(unsigned int i=0; i<examene.size(); i++){
		if(examene[i].getMarire())
			nrq++;
	} 
	return nrq;
}

vector<int> Student::materiiPicate(){
	vector<int> v;
	for(auto& i : examene){
		if(i.getNotaFinala() < 5){
			v.push_back(i.getIndex());
		}
	}
	return v;
}

/////////////////////////////////////TEMPLATE////////////////////////////////////////
template <class t> class CatalogIndividual{
	int nrMatricol;
	vector<t> exam;
	int nrExam;
	static int nc; 
public:
	CatalogIndividual(vector<t> exam = {}, int nrExam = 0){
		nc++;
		this->nrMatricol = nc; 
		this->nrExam = nrExam;

		for(unsigned int i=0;i<exam.size();i++){
            this->exam.push_back(exam[i]);
        }
	};

	CatalogIndividual(const CatalogIndividual& c){  
		nc++;
        this->nrExam = c.nrExam;
		this->nrMatricol = c.nrMatricol;
        for(unsigned int i=0;i<c.exam.size();i++){
            this->exam.push_back(c.exam[i]);
        }
	};

	~CatalogIndividual(){
		nc--;
	};
	CatalogIndividual& operator=(const CatalogIndividual& c){
		if(this != &c){
        	this->nrExam = c.nrExam;
			this->nrMatricol = c.nrMatricol;   
			exam.clear();
        	for(unsigned int i=0;i<c.exam.size();i++){
            	this->exam.push_back(c.exam[i]);
        	}
        }

		return *this;
	}	
	
	CatalogIndividual& operator+=(t& e){

      this->exam.push_back(e);
	  this->nrExam++;

      return *this;
	}
	

	friend istream& operator >>(istream &in, CatalogIndividual<t> &c){
		cout << "Nr de examene:";
    	in >> c.nrExam;
    	if (c.nrExam != 0){
        	cout << "Introduceti datele examenelor:\n";
        	t a;
       		for(int i=0;i<c.nrExam;i++){
				cout<<"Examenul " << i+1 <<":\n";	
				in.get();
            	in >> a;
            	c.exam.push_back(a);
       		}
    	}
    	else{
        	cout<<"Numarul de examene trebuie sa fie mai mare decat 0";
        	exit(EXIT_FAILURE);
		}
		return in;
	}
	friend ostream& operator <<(ostream &out, CatalogIndividual<t> &c){
		out<<"\nNumar matricol: "<<c.nrMatricol<<endl;
		out<<"In catalogul individual se gasesc urmatoarele "<<c.nrExam<<" examene:"<<endl;
		for(int i=0;i<c.nrExam;i++){
        	out << "Examenul " << i+1 << ":\n";
        	out << c.exam[i];
			out << "----------------------------\n";
		}  
		return out;
	}	


};

template <class t> int CatalogIndividual<t>::nc; //declarare variabila


/////////////////////////////SPECIALIZARE///////////////////////////////////
template <> class CatalogIndividual <Quiz>{
	int nrStud;
	vector<Student> vectStud;
	int minimDoua;
public:	
	CatalogIndividual(int nrStud = 0,vector<Student> vectStud = {}){
		minimDoua = 0;
		for(unsigned int i=0;i<vectStud.size();i++){
            this->vectStud.push_back(vectStud[i]);
			if(vectStud[i].nrquizuri()>=2)
				minimDoua++;
        }
		this->nrStud = nrStud;
		
	}
	CatalogIndividual(const CatalogIndividual& c){
		this->minimDoua = c.minimDoua;
        for(unsigned int i=0;i<c.vectStud.size();i++){
            this->vectStud.push_back(c.vectStud[i]);
        }
		this->nrStud = c.nrStud;

	}
	~CatalogIndividual(){
		
	}
	CatalogIndividual& operator=(const CatalogIndividual& c){
		if(this != &c){
			this->minimDoua = c.minimDoua;
			vectStud.clear();
        	for(unsigned int i=0;i<c.vectStud.size();i++){
            	this->vectStud.push_back(c.vectStud[i]);
        	}
			this->nrStud = c.nrStud;
		}
		return *this;
	}

	
	CatalogIndividual& operator+=(Student& e){
	  this->nrStud++;
      this->vectStud.push_back(e);
	  if(e.nrquizuri() >= 2){
		  minimDoua++;
	  }
      return *this;
	}
	

	friend istream& operator >>(istream &in, CatalogIndividual<Quiz> &c){
		cout <<"Introduceti numarul de studenti:";
		in >> c.nrStud;
		if (c.nrStud != 0){
        	cout << "Introduceti datele examenelor pentru fiecare student:\n";
        	Student a;
       		for(int i=0;i<c.nrStud;i++){
				cout<<"Studentul " << i+1 <<":\n"; 
				in.get();
            	in >> a;
            	c.vectStud.push_back(a);
				if(c.vectStud[i].nrquizuri()>=2)
					c.minimDoua++;
				cout << "-------------------------\n";

       		}
    	}
    	else{
        	cout<<"Numarul de studenti trebuie sa fie mai mare decat 0.";
        	exit(EXIT_FAILURE);
		}
		return in;
	}
	friend ostream& operator <<(ostream &out, CatalogIndividual<Quiz> &c){
		out<<"In catalogul se gasesc urmatorii "<<c.nrStud<<" studenti:"<<"\n";
		for(unsigned int i=0;i<c.vectStud.size();i++){
        	out << "Studentul " << i+1 << ":\n";
        	out << c.vectStud[i];
			out << "-------------------------\n";
		} 
		out<<"Dintre toti studentii, " << c.minimDoua << " au dat minim 2 quiz-uri\n";
		c.vectStud.clear();
		return out;
	}	

};


/////////////////////////////////////////////////////////////////////////////////////
void eticheta(Examen *&p, int &i) {
    string s;
    cout<<"\n";
    cout<<"Examen " << i+1 << ": "<< " Partial/Examen Final/Quiz?\n";
    getline(cin,s);
	cout <<s<<endl;
    cout<<"--------------------------\n";
    
    try{
        if(s =="partial" || s == "Partial"){
                p=new Partial;
                cin>>*p;
                i++;
        }
        else
            if(s =="examen final" || s == "Examen Final"){
                p=new ExamenFinal;
                cin>>*p;
                i++;
            }
            else 
				if( s == "quiz" || s == "Quiz"){
					p = new Quiz;
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
        cout<<"Invalid. Incercati partial,examen final sau quiz\n";
    }
}


/////////////////////////////////////MENIU///////////////////////////////////////////
int main()
{
	system("CLS");
    int m;
	int no;
	int nst;
	int N_p,N_ef,N_q;
	int nm;
    bool tixe = false;
	vector<Examen*> p;
	vector<Student> s;
	unordered_map<int, vector<Student>> picati;
	CatalogIndividual <Partial> x;
	CatalogIndividual <ExamenFinal> y; 
	CatalogIndividual <Quiz> z;
	Partial xx;
	ExamenFinal yy;
	Student ss;
	string a;
	string materie;

  do{
        cout<<"\t\t\t\t\tHermeneanu Mara - Grupa: 212 - Proiect: 3 "<<endl;
        cout<<"\n\n\t\t\t\t\t\t\tMENIU"<<endl;
        cout<<"========================================================================================================================"<<endl;

        cout<<endl;
		cout<<"\n\t0.Inainte de oricare actiune, introduceti materiile posibile"<<endl;
        cout<<"\n\t1. Citire si afisare n examene"<<endl; 
        cout<<"\t2. Afisare nr examene declarate "<<endl;
        cout<<"\t3. Citire n studenti si afisare picati pt fiecare examen"<<endl;
        cout<<"\t4. Afisare nr de studenti declarati"<<endl;
        cout<<"\t5. Template <partial> "<<endl;
        cout<<"\t6. Template <examen final> "<<endl;
        cout<<"\t7. Specializare template <quiz>, cati studenti au dat minim 2 quiz-uri"<<endl;
		cout<<"\t8. Adaugare fisa de observatie examen" <<endl;
		cout<<"\t9. Adugare fisa de observatie student" <<endl;
		cout<<"\t10. Dynamic cast - RTTI - Contorizare tipuri de examene de la 1"<<endl;
        cout<<"\n\nIntroduceti o actiune: ";
        cin>>m;

        switch(m)
        {
            case 0:
                cout<<"Introduceti numarul de discipline:";
				cin>>nm;
				cin.get();
				materii.resize(nm);
				for(int i=0;i<nm;i++){
					cout<<"Disciplina "<<i+1<<":";
					getline(cin,materie);
					materii.push_back(materie);
				}
                break;

            case 1:
				cout<<"Introduceti numarul de obiecte: ";
                cin >> no;
				cin.get();
				if (no>0)
            	{
					try{
						int copieI;
						for(int i = 0; i < no;){
							p.push_back(new Examen);
							copieI = i;
							eticheta(p[i], i);
							if (copieI != i)
								cin.get();
						}
					}
					catch (bad_alloc var){
						cout<<"Eroare de alocare\n";
						exit(EXIT_FAILURE);
					}

					for(int i = 0; i < no; i++){
							cout<<"\nExamenul " << i+1<<":\n";
							cout<<"--------------------------\n";
							cout << *p[i];
							
					}
				}
				else
				{
					cout<<"Numarul de obiecte trebuie sa fie pozitiv\n";
				}
					
				break;

			case 2:
				cout << "Numarul de examene declarate: ";
                Examen::numarExamene();
				cout<<"\n"; 
				break;
			case 3:
				cout<< "Nr. studenti:";
                cin>>nst;
                s.resize(nst);
                for(int i=0;i<nst;i++){
                    cout<<"Studentul " << i+1 << ":\n";
					cin.get();
                    cin>> s[i];
					
				}

				for(int i=0;i<nst;i++){
                    cout<<"\nStudentul " << i+1 << ":\n";
                    cout << s[i];
                    cout<<"--------------------------\n";
                }

				for (unsigned int i = 0 ; i < materii.size(); i++){
					vector <Student> studentiPicatiMaterieI;
					for (auto& stud : s){
						vector<int> indexuriMateriiPicate = stud.materiiPicate();
						vector<int> :: iterator it = find(indexuriMateriiPicate.begin(), indexuriMateriiPicate.end(), i + 1);
						if (it != indexuriMateriiPicate.end()){
							studentiPicatiMaterieI.push_back(stud);
						}
					}
					picati[i] = studentiPicatiMaterieI;
				}

				for (auto& i: picati){
					if(i.second.size()){
						cout << "La examenul de " << materii[i.first+1] << " au picat urmatorii studenti:\n";
        				for(auto& student : i.second){
            				cout << student.getNume() << endl;
        				}
					}
        			
    			}

				s.clear();

				break;

			case 4:
				cout << "Numar de studenti declarati: ";
				cout << s[0].getNrStudenti();
				break;
			case 5:
            	cin>>x;
            	cout<<x;
				break;
			case 6:
            	cin>>y;
            	cout<<y;
				break;
			case 7:
            	cin>>z;
            	cout<<z;
				break;
			case 8:
				cout<<"\nPentru ce tip de examen vreti sa adaugati fisa de observatie? Partial/Examen final: ";
				cin>>a;
				cin.get();
				try{
        			if(a =="partial" || a == "Partial"){
                		cin>>xx;
						x+=xx;
						cout<<x;
                		
        			}
        		else
            		if(a =="examen final" || a == "Examen Final"){ //pb de la in.get()
                		cin>>yy;
						y+=yy;
						cout<<y;
	                	
            		}
                	else
						throw 10;
    			}
    			catch (bad_alloc var){
        			cout << "Eroare de alocare\n";
        			exit(EXIT_FAILURE);
    			}
    			catch(int j){
        		cout<<"Invalid. Incercati partial sau examen final\n ";
    			}

				break;				
			case 9:
				cin.get();
				cin >> ss;
				z+=ss;
				cout<<z;

				break;	
			case 10:
				
            N_p=N_ef=N_q=0;
            for(unsigned int i=0;i<p.size();i++)
            {
                ///incerc cast catre partial
                Partial *p1=dynamic_cast<Partial*>(p[i]);
                ///incerc cast catre examen final
                ExamenFinal *p2=dynamic_cast<ExamenFinal*>(p[i]);
                ///incerc cast catre partial
                Quiz *p3=dynamic_cast<Quiz*>(p[i]);
                ///daca sunt nenuli atunci incrementez corespunzator
                if (p1)
                    N_p++;
                if (p2)
                    N_ef++;
                if (p3)
                    N_q++;
            }
            cout<<"Numarul de partiale: "<<N_p<<"\n";
            cout<<"Numarul de examene finale: "<<N_ef<<"\n";
            cout<<"Numarul de quiz-uri: "<<N_q<<"\n";
				break;
			default:
                tixe = true;
                break; 	
		}   
        system("pause");
        if (tixe) break;
        system("cls");

  	}while(true);
	
    return 0;	
}
