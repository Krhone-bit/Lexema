#include <iostream>
#include <string.h>
#include <list>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

#define BUCLEF    	0
#define VAR         1
#define INF			2
#define ACORCHETE	3
#define NUM         4
#define COMA        5
#define CCORCHETE	6
#define DPUNTOSF	7
#define IMPRIMIR	8
#define APAR        9
#define CPAR        10

#define SI			11
#define MAYOR      	12
#define ACOMILLA    13
#define CADENA		14
#define CCOMILLA    15
#define ENTONCES	16

#define METODO		17
#define NMETODO		18
#define RETORNO		19
#define MAS        	20
#define TAB      	21
#define SALTO      	22
#define IGUAL       23
#define MENOR       24
#define DIGUAL      25

#define FIN     666
#define ERROR   999

#define null "6c3e226b4d4795d518ab341b0824ec29"
#define vacio "-"
#define asignado "asignado"

#define MAX 100 // Tamaño máximo de la pila

class Atributos{
    public:
        string lexema;
        int token;
        string tipo;
        string valor;
        string estado;
        Atributos(){
            lexema="";
            token=-999;
            tipo="";
            valor=null;
            estado="";
        }
        Atributos(string lex,int tok,string tip,string val,string est){
            lexema=lex;
            token=tok;
            tipo=tip;
            valor=val;
            estado=est;
        }
        void Mostrar(){
            cout<<"Tipo("<<tipo<<") \t";
            cout<<"Lexema("<<lexema<<") \t";
            cout<<"Token("<<token<<") \t";
            cout<<"Valor("<<valor<<") \t";
            cout<<"Estado("<<estado<<")"<<endl;

        }
};

class TablaSimbolos{
    private:
        list<Atributos> tabla;
    public:
        void Insertar(string lex,int tok,string tip,string val,string est){
            Atributos attr(lex,tok,tip,val,est);
            tabla.push_back(attr);
        }
        bool ActualizarValor(string lex,string val){
            for (auto &item:tabla){
                if(item.lexema == lex){
                    item.valor = val;
                    return true;
                }
            }
            return false;
        }
        bool ActualizarEstado(string lex,string est){
            for (auto &item:tabla){
                if(item.lexema == lex){
                    item.estado = est;
                    return true;
                }
            }
            return false;
        }
        void Mostrar(){
            for (auto item:tabla){
                item.Mostrar();
            }
        }
        bool Buscar(string lex,Atributos&attr){
            for (auto item:tabla){
                if(item.lexema == lex){
                    attr=item;
                    return true;
                }
            }
            return false;
        }
        bool BuscarPClave(string lex,Atributos&attr){
            for (auto item:tabla){
                if(item.lexema == lex && item.tipo == "pclave"){
                    attr=item;
                    return true;
                }
            }
            return false;
        }
        list<Atributos> getTabla(){
            return tabla;
        }
};

class Analisis{
    private:
        int i; /*apuntador al caracter actual*/
        char cad[1000];

        int estado;
        string numero;
        string variable;
        string cadena;
        int tTransicion[100][100];
        TablaSimbolos ts;
        int blockLevel;

    public:
        Analisis(char input[100]){
            strcpy(cad,input);
            i=0;
            blockLevel = 0;

            ts.Insertar("for",BUCLEF,"pclave",vacio,vacio);
            ts.Insertar("var",VAR,"pclave",vacio,vacio);
            ts.Insertar("in",INF,"pclave",vacio,vacio);
            ts.Insertar("[",ACORCHETE,"pclave",vacio,vacio);
            ts.Insertar(",",COMA,"pclave",vacio,vacio);
            ts.Insertar("]",CCORCHETE,"pclave",vacio,vacio);
            ts.Insertar(":",DPUNTOSF,"pclave",vacio,vacio);
            ts.Insertar("print",IMPRIMIR,"pclave",vacio,vacio);
            ts.Insertar("(",APAR,"pclave",vacio,vacio);
            ts.Insertar(")",CPAR,"pclave",vacio,vacio);

            ts.Insertar("if",SI,"pclave",vacio,vacio);
            ts.Insertar(">",MAYOR,"pclave",vacio,vacio);
            ts.Insertar("<",MENOR,"pclave",vacio,vacio);
            ts.Insertar("==",DIGUAL,"pclave",vacio,vacio);
            ts.Insertar("=",IGUAL,"pclave",vacio,vacio);
            ts.Insertar("else",ENTONCES,"pclave",vacio,vacio);
            ts.Insertar("def",METODO,"pclave",vacio,vacio);
            ts.Insertar("sumar",NMETODO,"pclave",vacio,vacio);
            ts.Insertar("return",RETORNO,"pclave",vacio,vacio);
            ts.Insertar("+",MAS,"pclave",vacio,vacio);

            for(int ii=0;ii<8;ii++){
                for(int jj=0;jj<11;jj++){
                    tTransicion[ii][jj]=ERROR;
                }
            }
            tTransicion[0][VAR]=1;
            tTransicion[0][TAB]=0;
            tTransicion[1][IGUAL]=2;
            tTransicion[2][VAR]=3;
            tTransicion[2][NUM]=3;
            tTransicion[3][SALTO]=0;
            tTransicion[0][IMPRIMIR]=4;
            tTransicion[4][APAR]=5;
            tTransicion[5][VAR]=6;
            tTransicion[5][NUM]=6;
            tTransicion[5][CADENA]=6;
            tTransicion[6][COMA]=5;
            tTransicion[6][CPAR]=7;
            tTransicion[7][SALTO]=0;
            tTransicion[0][BUCLEF]=8;
            tTransicion[8][VAR]=9;
            tTransicion[9][INF]=10;
            tTransicion[10][ACORCHETE]=11;
            tTransicion[11][VAR]=12;
            tTransicion[11][NUM]=12;
            tTransicion[12][COMA]=11;
            tTransicion[12][CCORCHETE]=13;
            tTransicion[13][DPUNTOSF]=14;
            tTransicion[14][SALTO]=0;
            tTransicion[0][SI]=15;
            tTransicion[15][VAR]=16;
            tTransicion[15][NUM]=16;
            tTransicion[16][MAYOR]=17;
            tTransicion[16][MENOR]=17;
            tTransicion[16][DIGUAL]=17;
            tTransicion[17][VAR]=18;
            tTransicion[17][NUM]=18;
            tTransicion[18][DPUNTOSF]=0;
            tTransicion[0][ENTONCES]=19;
            tTransicion[19][DPUNTOSF]=0;
            tTransicion[0][METODO]=20;
            tTransicion[20][VAR]=21;
            tTransicion[21][APAR]=22;
            tTransicion[22][VAR]=23;
            tTransicion[23][COMA]=22;
            tTransicion[23][CPAR]=24;
            tTransicion[24][DPUNTOSF]=0;
            tTransicion[0][RETORNO]=25;
            tTransicion[25][VAR]=26;
            tTransicion[25][NUM]=26;
            tTransicion[26][SALTO]=0;
        }

        bool iselement(char c){
            char elements[100];
            strcpy(elements,"(),:[]=+><");
            int elements_cont=0;
            while(elements[elements_cont]!='\0'){
                if(elements[elements_cont]==c)
                    return true;
                elements_cont++;
            }
            return false;
        }

        int getToken(){
            while(cad[i]==' '){
                i++;
            }
            if(cad[i]=='\n'){
                i++;
                return SALTO;
            }
            if(cad[i]=='\t'){
                i++;
                return TAB;
            }
            if(cad[i]=='\0'){
                return FIN;
            }
            else if(isalpha(cad[i])){
                char tmp[100];
                int tmp_cont=0;
                while(isalpha(cad[i]) || isdigit(cad[i])){
                    tmp[tmp_cont]=cad[i];
                    tmp_cont++;
                    i++;
                }
                tmp[tmp_cont]='\0';
                Atributos attr;
                string lex=tmp;
                for(auto item:ts.getTabla()){
                    if(ts.BuscarPClave(lex,attr)){
                        return attr.token;
                    }
                }
                variable=tmp;
                return VAR;
            }
            else if(isdigit(cad[i])){
                char tmp[100];
                int tmp_cont=0;
                while(isdigit(cad[i]) || cad[i]=='.'){
                    tmp[tmp_cont]=cad[i];
                    tmp_cont++;
                    i++;
                }
                tmp[tmp_cont]='\0';
                numero=tmp;
                return NUM;
            }
            else if(iselement(cad[i])){
                if(iselement(cad[i+1])){
                    char tmp[3];
                    tmp[0]=cad[i];
                    tmp[1]=cad[i+1];
                    tmp[2]='\0';
                    Atributos attr;
                    string lex=tmp;
                    for(auto item:ts.getTabla()){
                        if(ts.BuscarPClave(lex,attr)){
                            i++;
                            i++;
                            return attr.token;
                        }
                    }
                }
                char tmp[2];
                tmp[0]=cad[i];
                tmp[1]='\0';
                Atributos attr;
                string lex=tmp;
                for(auto item:ts.getTabla()){
                    if(ts.BuscarPClave(lex,attr)){
                        i++;
                        return attr.token;
                    }
                }
                i++;
                return ERROR;
            }
            else if(cad[i]==39){
                char tmp[100];
                int tmp_cont=0;
                i++;
                while(cad[i]!=39){
                    tmp[tmp_cont++]=cad[i];
                    i++;
                }
                tmp[tmp_cont++]='\0';
                cadena=tmp; 
                i++;
                return CADENA;
            }
            else{
                i++;
                return ERROR;
            }
        }

        bool leerArchivo (const char direccion[]){
            ifstream archivo(direccion);
            
            if (archivo.bad())
                return false;

            archivo.get(cad, 999, '\0');

            archivo.close();
            return true;
        }

        bool Lexico(){
            i=0;
            int token=0;
            while(true){
                token=getToken();
                if(token==FIN){
                    return true;
                }
                else if(token==VAR){
                    Atributos attr;
                    if(!ts.Buscar(variable,attr)){
                        ts.Insertar(variable,VAR,"var",null,null);
                    }
                }
                else if(token==ERROR){
                    Error(100);
                    return false;
                }
            }
        }

        bool Sintactico(){
            i=0;
            int token=0;
            estado=0;
            while(true){
                token=getToken();
                if(token==FIN){
                    if(estado==0)
                        return true;
                    Error(2000);
                    return false;
                }
                else if (token == VAR) {
                    Atributos attr;
                    if (!ts.Buscar(variable, attr)){
                        ts.Insertar(variable, VAR, "var", null, null);
                    }
                }
                estado=tTransicion[estado][token];
                if(estado==ERROR){
                    Error(400);
                    return false;
                }
            }
            return false;
        }
        
        bool Semantico(){
            i=0;
            int token=0;
            while(true){
                token=getToken();
                if(token==FIN){
                    return true;
                }
                if (token == VAR){
                    token=getToken();
                    token=getToken();
                    if(token==VAR){
                        Atributos attr;
                        if(!ts.Buscar(variable,attr)){
                            Error(101);
                            return false;
                        }
                        else if(attr.estado == null){
                            Error(101);
                            return false;
                        }
                    }
                    token=getToken();//;
                }
                else if (token == SI){
                    token=getToken();
                    Atributos attr;
                    for(int ii=0;ii<4;ii++){
                        token=getToken();
                        if(token==VAR){
                            if(!ts.Buscar(variable,attr)){
                                Error(200);
                                return false;
                            }
                            else if(attr.estado == null){
                                Error(200);
                                return false;
                            }
                        }
                        token=getToken();
                    }
                    token=getToken();
                }
                if (token == IMPRIMIR){
                    token = getToken();
                    token = getToken();
                    Atributos attr;
                    for(int ii=0;ii<3;ii++){
                        token=getToken();
                        if(token==VAR && variable.length()==1 && attr.valor!=null){
                            if(!ts.Buscar(variable,attr)){
                                Error(300);
                                return false;
                            }
                            else if(attr.estado == null){
                                Error(300);
                                return false;
                            }
                        }
                        token=getToken();
                    }
                    token=getToken();
                }
                if (token == BUCLEF){
                    token = getToken();
                    Atributos attr;
                    for(int ii=0;ii<3;ii++){
                        token=getToken();
                        if(token==VAR){
                            if(!ts.Buscar(variable,attr)){
                                Error(400);
                                return false;
                            }
                            else if(attr.estado == null){
                                Error(400);
                                return false;
                            }
                        }
                        token=getToken();
                    }
                    token=getToken();
                }
                if (token == ENTONCES){
                    token = getToken();
                    if (token== DPUNTOSF){
                        token = getToken();
                        if (token != SALTO) Error(501);
                    }
                }
                if (token == RETORNO){
                    token = getToken();
                    Atributos attr;
                    for(int ii=0;ii<1;ii++){
                        token=getToken();
                        if(token==VAR){
                            if(!ts.Buscar(variable,attr)){
                                Error(600);
                                return false;
                            }
                            else if(attr.estado == null){
                                Error(600);
                                return false;
                            }
                        }
                        token=getToken();
                    }
                    token=getToken();
                }
                if(token == TAB){
                    int tmp_token = token;
                    tmp_token = getToken();
                    if (tmp_token == SALTO) Error(700);

                }
                if (token == METODO){
                    token = getToken();
                    Atributos attr;
                    for(int ii=0;ii<5;ii++){
                        token=getToken();
                        if(token==VAR && attr.valor!=null){
                            if(!ts.Buscar(variable,attr)){
                                Error(800);
                                return false;
                            }
                            else if(attr.estado == null){
                                Error(800);
                                return false;
                            }
                        }
                        token=getToken();
                    }
                    token=getToken();
                }
            }
        }

        bool Ejecucion(){
            std::stack<string> pilaBloque;
            std::vector<string> bloques;
            i=0;
            int token=0;
            while(true){
                token=getToken();
                if(token==FIN){
                    while (!pilaBloque.empty()){
                        if (pilaBloque.top() == "function"){
                            cout << "}" << endl;
                            pilaBloque.pop();
                            return true;
                        }
                        cout << "}" << endl;
                        pilaBloque.pop();
                    }
                    return true;
                }
                if (token == VAR){
                    string tmp_var = variable;
                    token=getToken();
                    token=getToken();
                    if (token == VAR){
                        Atributos attr;
                        ts.ActualizarValor(variable, attr.valor);
                    }
                    token = getToken();
                    if (token == SALTO){
                        cout << "const " << tmp_var << " = " << numero << ";" << endl;
                    }
                    if(token == DPUNTOSF){
                        cout << tmp_var;
                    }
                    bloques.push_back("var");
                }
                else if (token == SI){
                    cout << "if (";
                    string tmp_var = variable;
                    token=getToken();
                    if (token == VAR) cout<< variable;
                    token=getToken();
                    if (token == MAYOR){
                        cout << " > ";
                    }else if (token == MENOR){
                        cout << " < ";
                    }else{
                        cout << " == ";
                    }
                    token=getToken();
                    if (token == NUM) cout << numero;
                    if (token == VAR) cout << variable;
                    token=getToken();
                    if (token == DPUNTOSF) cout << ") {" << endl;
                    pilaBloque.push("if");
                    bloques.push_back("if");
                    token = getToken();
                    token = getToken();
                }
                if (token == IMPRIMIR){
                    cout << "console.log(";
                    token = getToken();
                    while(token != CPAR){
                        token = getToken();
                        if (token == VAR) cout << variable;
                        if (token == NUM) cout << numero;
                        if (token == CADENA) cout << "\"" << cadena << "\"";
                        if (token == COMA) cout << ",";
                    }
                    cout << ");" << endl;
                    token = getToken();
                    bloques.push_back("imprimir");
                }
                if (token == BUCLEF){
                    int lst = bloques.size()-1;
                    while(!pilaBloque.empty()){
                        if (pilaBloque.top() == "for" && bloques[lst] != "for"){
                            cout << "}" << endl;
                            pilaBloque.pop();
                        }
                        else{
                            break;
                        }
                    }
                    auto it = find(bloques.begin(), bloques.end(), "for");
                    if (it != bloques.end()) {
                        bloques.erase(it);
                    }
                    
                    cout << "for (";
                    token = getToken();
                    if (token == VAR) cout << "const " << variable;
                    token = getToken();
                    if (token == INF) cout << " of ";
                    token = getToken();
                    cout << "[";
                    while(token != CCORCHETE){
                        token = getToken();
                        if (token == NUM) cout << numero;
                        if (token == COMA) cout << ",";
                    }
                    cout << "]";
                    token = getToken();
                    if (token == DPUNTOSF) cout << ") {" << endl;
                    token = getToken();
                    pilaBloque.push("for");
                    bloques.push_back("for");
                }
                if (token == ENTONCES){
                    cout << "}else {" << endl;
                    token = getToken();
                    bloques.push_back("else");
                }
                if (token == RETORNO){
                    cout << "\treturn ";
                    token = getToken();
                    if (token == VAR) cout << variable;
                    if (token == NUM) cout << numero;
                    cout << ";" << endl;
                }
                if(token == TAB){
                    cout << "\t";
                }
                if (token == METODO){
                    for (int i = 0; i < bloques.size(); i++){
                        // cout << bloques[i] << endl;
                        if (bloques[i]=="for") cout << "}" << endl;
                        if (bloques[i]=="if") cout << "}" << endl;
                    }
                    cout << "function ";
                    token = getToken();
                    if (token == VAR) cout << variable;
                    token = getToken();
                    cout << "(";
                    while (token != CPAR){
                        token = getToken();
                        if (token == VAR) cout << variable;
                        if (token == COMA) cout << ", ";
                    }
                    if (token == CPAR) cout << ") ";
                    token = getToken();
                    if (token == DPUNTOSF) cout << " {" << endl;
                    // blockLevel++;
                    pilaBloque.push("function");
                    bloques.push_back("funcion");
                }
            }
        }

        void Analizar(){
            if(Lexico()){
                if(Sintactico()){
                    if(Semantico()){
                        Ejecucion();
                    }
                }
            }
        }

        void Error(int nroError){
            cout<<"Error "<<nroError<<": ";
            if(nroError==100){
                cout<<"No se reconoce: "<<cad[i]<<" en la posicion "<<i;
            }
            if(nroError==500){
                cout<<"La variable: "<<variable<<" no ha sido declarada";
            }
            if(nroError==101){
                cout<<"Error en la variable declarada";
            }
            if(nroError==200){
                cout<<"Error de semantica en condicional";
            }
            if(nroError==300){
                cout<<"Error de semantica en imprimir";
            }
            if(nroError==400){
                cout<<"Error de semantica en for";
            }
            if(nroError==501){
                cout<<"Error de semantica en condicional else";
            }
            if(nroError==600){
                cout<<"Error de semantica en return";
            }
            if(nroError==700){
                cout<<"Error de semantica en Tabulacion";
            }
            if(nroError==800){
                cout<<"Error de semantica en funcion";
            }
        }
};

int main()
{
    Analisis*obj = new Analisis("");
    obj->leerArchivo("input.py");
    obj->Analizar();
    return true;
}
