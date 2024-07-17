/*** EJEMPLOS DEL LENGUAJE GRAFICADOR ***
graficos(){
    cuadrado(100,100,50);
	circulo(125,125,50);
	rectangulo(100,100,200,50);
	linea(100,100,200,50);
}

graficos(){
	posx1=120;
	posx2=120;
	posx=175;
	posy=100;
	tam1=100;
	tam2=75;
	cuadrado(200,200,tam1);
	linea(100,100,tam1,50);
	rectangulo(posx1,posy,tam2,50);
	radio=24;
	circulo(posx,posy,radio);
}

graficos(){
    lado=50;
    cuadrado(100,100,lado);
    ancho=150;
    rectangulo(x1,y1,100,ancho);
}

*** PALABRAS CLAVE Y SIGNOS QUE CORRESPONDEN AL LENGUAJE ****
graficos
(
)
{
}
=
;
cuadrado
rectangulo
circulo
linea
,
VAR
NUM

*** LISTA DE SENTENCIAS ***************
ASIGNACIONES
DIBUJAR CUADRADO
DIBUJAR RECTANGULO
DIBUJAR CIRCULO
DIBUJAR LINEA

*** DIBUJAR EL AUTOMATA ***************

*** ERRORES SEMANTICOS **************
LAS VARIABLES NO ESTAN REGISTRADAS EN LA TABLA DE SIMBOLOS
LAS VARIABLES NO TIENEN UN VALOR ASIGNADO

************************/

#include <iostream>
#include <string.h>
#include <list>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
//graficos(){ posx1=120; posx2=120; posx=175; posy=100; tam1=100; tam2=75; cuadrado(200,200,tam1); linea(100,100,tam1,50); rectangulo(posx1,posy,tam2,tam2); radio=24; circulo(posx,posy,radio); }
/*Modificar los tokens*/
/* #define GRAFICOS    0
#define APAR        1
#define CPAR        2
#define ALLAVE      3
#define CLLAVE      4
#define IGUAL       5
#define PCOMA       6
#define CUADRADO    7
#define RECTANGULO  8
#define CIRCULO     9
#define LINEA       10
#define COMA        11
#define VAR         12
#define NUM         13
#define CADENA      14 */
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

using namespace std;

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
        //graficos(){ posx1=120; posx2=120; posx=175; posy=100; tam1=100; tam2=75; cuadrado(200,200,tam1); linea(100,100,tam1,50); rectangulo(posx1,posy,tam2,tam2); radio=24; circulo(posx,posy,radio); }
        char cad[1000];

        int estado;
        string numero;
        string variable;
        string cadena;
        int tTransicion[100][100];
        TablaSimbolos ts;
        // streambuf archivo;
    public:
        Analisis(char input[100]){
            //Aqui hacer la apertura de archivo de texto plano
            strcpy(cad,input);
            i=0;

            /*Modificar: Adecuar su tabla de simbolos*/
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
            // tTransicion[20][NMETODO]=21;
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
            /*AQUI DEBEN DE DEFINIR LOS CARACTERES QUE NO SEAN LETRAS O NUMEROS Y QUE CORRESPONDAN AL LENGUAJE*/
            /*NO DEBEN DE REPETIR CARACTERES*/
            strcpy(elements,"(),:[]=+><");/*<- AQUI MODIFICAR*/
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
            // /AQUI PUEDE QUE SE TRATE DE UNA VARIABLE O UNA PALABRA CLAVE/
            else if(isalpha(cad[i])){ // nos pregunta si es un caracter
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
                //buscando en la tabla de simbolos
                for(auto item:ts.getTabla()){
                    if(ts.BuscarPClave(lex,attr)){
                        return attr.token;
                    }
                }
                variable=tmp;
                return VAR;
            }
            else if(isdigit(cad[i])){ // x=78.45; adecuar para que reconozca solo un punto
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
                if(iselement(cad[i+1])){ // += !=
                    char tmp[3];
                    tmp[0]=cad[i];
                    tmp[1]=cad[i+1];
                    tmp[2]='\0';
                    Atributos attr;
                    string lex=tmp;
                    //cout<<"de 2:"<<lex<<endl;
                    for(auto item:ts.getTabla()){
                        if(ts.BuscarPClave(lex,attr)){
                            i++;
                            i++;
                            return attr.token;
                        }
                    }
                    //cout<<"salio"<<endl;
                }
                char tmp[2];
                tmp[0]=cad[i];
                tmp[1]='\0';
                Atributos attr;
                string lex=tmp;
                //cout<<"de 1:"<<lex<<endl;
                for(auto item:ts.getTabla()){
                    if(ts.BuscarPClave(lex,attr)){ //graficos (+)
                        i++;
                        return attr.token;
                    }
                }
                //cout<<"salio"<<endl;
                i++;
                return ERROR;
            }
            else if(cad[i]==39){
                //cout<<int('\'')<<endl; cadena = 'hola sistemas';
                char tmp[100];
                int tmp_cont=0;
                i++;
                while(cad[i]!=39){
                    tmp[tmp_cont++]=cad[i];
                    i++;
                }
                tmp[tmp_cont++]='\0';
                //cout<<"La cadena capturada es: "<<tmp<<endl<<endl;
                cadena=tmp; //almacena que cadena esta encontrando
                i++;
                return CADENA;
            }
            else{
                i++;
                return ERROR;
            }
        }
        bool leerArchivo (const char direccion[])
        {
            ifstream archivo(direccion);
            
            if (archivo.bad())
                return false;

            archivo.get(cad, 999, '\0');

            archivo.close();
            return true;
        }

        bool Lexico(){
            i=0;
            // cout<<cad<<endl;
            int token=0;
            while(true){
                token=getToken();
                // cout<<token<<endl;
                //cout<<"Lexico: "<<token<<endl;
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
                    //Aqui deben de mostrar el error lo m�s especifico posible
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
                    if(estado==0)/*VERIFICAR EL ESTADO FINAL*/
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
                // cout<<"(e"<<estado<<",t"<<token<<")"<<endl;
                estado=tTransicion[estado][token];
                if(estado==ERROR){
                    Error(400);
                    return false;
                }
            }
            return false;
        }
        
        bool Semantico(){
            // ts.Mostrar();
            i=0;
            int token=0;
            // while (true)
            // {
            //     if(token == VAR){
            //         Atributos attr;
            //         if (!ts.Buscar(variable, attr)){
            //             Error(500);
            //             return false;
            //         }
            //     }
            // }
            
            // int token=0;
            //  while(true){
            //     token=getToken();
            //     if (token == VAR){

            //     }
            //     if (token == IMPRIMIR){

            //     }
            //     if (token == BUCLEF){

            //     }
            //     if (token == SI){

            //     }
            //     if (token == ENTONCES){

            //     }
            //     if (token == RETORNO){

            //     }
            //     if(token == TAB){

            //     }
            //     if (token == METODO){

            //     }
            // }
            return true;
        }


bool Ejecucion() {
    int i = 0;
    int token = getToken();
    while (true) {
        // token = getToken();
        if (token == FIN) {
            return true;
        }
        if (token == TAB){
            cout << "\t";
            token = getToken();
            if (token == TAB) {
                cout << "\t";
                token = getToken();
            }
        }
        if (token == VAR) {
            string tmp_var = variable;
            cout << "const " << tmp_var;
            token = getToken();
            if (token == IGUAL) {
                cout << "=";
            }
            token = getToken();
            if (token == VAR) {
                Atributos attr;
                ts.Buscar(variable, attr);
                cout << attr.valor;
            } else if (token == NUM) {
                ts.ActualizarValor(tmp_var, numero);
                cout << numero;
            }
            token = getToken();
            if (token == SALTO) {
                cout << ";" << endl;
            }
            // token = getToken();
            // cout << "=======" << token << endl;
        } 
        if (token == IMPRIMIR) {
            cout << "console.log";
            token = getToken();
            cout << "(";
            token = getToken();
            Atributos attr;
            if (token == VAR) {
                ts.Buscar(variable, attr);
                cout << variable;
            } else if (token == CADENA) {
                cout << "\"" << cadena << "\"";
            } else if (token == NUM) {
                cout << numero;
            }
            token = getToken();
            cout << ")";
            token = getToken();
            cout << ";" << endl;
            token = getToken();
        } else if (token == BUCLEF) {
            cout << "for(";
            token = getToken();
            string loop_var = variable; // Guardar la variable del bucle
            cout << "const " << loop_var;
            token = getToken();
            cout << " of ";
            token = getToken();
            cout << "[";
            Atributos attr;
            while (token != CCORCHETE) {
                token = getToken();
                if (token == NUM) {
                    cout << numero;
                } else if (token == COMA) {
                    cout << ",";
                }
            }
            cout << "]";
            token = getToken(); // :
            cout << ")";
            cout << "{" << endl;
            token = getToken(); // SALTO
            // token = getToken(); // TAB
            while (true){
                token = getToken(); // IMPRIMIR
                if (token == FIN || token == METODO) {
                    
                    cout << "}" << endl;
                    break;
                }
                if (token == BUCLEF) {
                    // token = getToken();
                    // cout << "==========" << token << endl;
                    // cout << "}" << endl;
                    break;
                }
                // token = getToken();
                if (token == IMPRIMIR) {
                    cout << "\tconsole.log";
                    token = getToken();
                    cout << "(";
                    token = getToken();
                    if (token == VAR) {
                        ts.Buscar(variable, attr);
                        cout << variable;
                    } else if (token == CADENA) {
                        cout << "\"" << cadena << "\"";
                    } else if (token == NUM) {
                        cout << numero;
                    }
                    token = getToken();
                    token = getToken();
                    cout << ");" << endl;
                }
                if (token==VAR){
                    string tmp_var = variable;
                    cout << "\tconst " << tmp_var;
                    token = getToken();
                    if (token == IGUAL) {
                        cout << "=";
                    }
                    token = getToken();
                    if (token == VAR) {
                        Atributos attr;
                        ts.Buscar(variable, attr);
                        cout << attr.valor;
                    } else if (token == NUM) {
                        ts.ActualizarValor(tmp_var, numero);
                        cout << numero;
                    }
                    cout << ";" << endl;
                    token = getToken();
                    // cout << ">>>>>>" << token << endl;
                }
                if (token == SI){
                    cout << "\tif(";
                    token = getToken();
                    if (token == VAR) {
                        cout << variable;
                        token = getToken();
                    }
                    if (token == MAYOR) {
                        cout << " > ";
                        token = getToken();
                    }else if (token == MENOR) {
                        cout << " < ";
                        token = getToken();
                    }else if (token == DIGUAL) {
                        cout << " == ";
                        token = getToken();
                    }
                    if (token == NUM) {
                        cout << numero;
                        token = getToken();
                    }
                    token = getToken();
                    cout << "){" << endl;
                    token = getToken();
                    // token = getToken();
                    // token = getToken();
                    if (token == IMPRIMIR) {
                        cout << "\t\tconsole.log";
                        token = getToken();
                        cout << "(";
                        token = getToken();
                        if (token == VAR) {
                            ts.Buscar(variable, attr);
                            cout << variable;
                        } else if (token == CADENA) {
                            cout << "\"" << cadena << "\"";
                        } else if (token == NUM) {
                            cout << numero;
                        }
                        token = getToken();
                        token = getToken();
                        cout << ");" << endl;
                        token = getToken();
                        token = getToken();
                        cout << "\t}" << endl;
                    }
                    if (token == ENTONCES){
                        token = getToken();
                        token = getToken();
                        token = getToken();
                        token = getToken();
                        token = getToken();
                        cout << "else{" << endl;
                        if (token == IMPRIMIR) {
                            cout << "\t\tconsole.log";
                            token = getToken();
                            cout << "(";
                            token = getToken();
                            if (token == VAR) {
                                ts.Buscar(variable, attr);
                                cout << variable;
                                token = getToken();
                            } else if (token == CADENA) {
                                cout << "\"" << cadena << "\"";
                                token = getToken();
                            } else if (token == NUM) {
                                cout << numero;
                                token = getToken();
                            }
                            cout << ");" << endl;
                            token = getToken();
                            cout << "\t}"<<endl;
                            // cout << "TOKEN: " << token << endl;
                        }
                    } 
                }
            }
            // token=getToken();
            // cout<< ">>>>>>" << token << endl;
        }else if (token == SI){
            cout << "if(";
            token = getToken();
            if (token == VAR) {
                cout << variable;
                token = getToken();
            }
            if (token == MAYOR) {
                cout << " > ";
                token = getToken();
            }else if (token == MENOR) {
                cout << " < ";
                token = getToken();
            }else if (token == DIGUAL) {
                cout << " == ";
                token = getToken();
            }
            if (token == NUM) {
                cout << numero;
                token = getToken();
            }
            if (token == VAR) {
                cout << variable;
                token = getToken();
            }
            cout << "){" << endl;
            token = getToken();
        }else if (token == ENTONCES){
            cout << "}else{" << endl;
            token = getToken();
            token = getToken();
            token = getToken();
            Atributos attr;
            if (token == IMPRIMIR) {
                cout << "\tconsole.log";
                token = getToken();
                cout << "(";
                token = getToken();
                if (token == VAR) {
                    ts.Buscar(variable, attr);
                    cout << variable;
                } else if (token == CADENA) {
                    cout << "\"" << cadena << "\"";
                } else if (token == NUM) {
                    cout << numero;
                }
                token = getToken();
                token = getToken();
                cout << ");" << endl;
                token = getToken();
                token = getToken();
            }
            cout << "}" << endl;
        } else if (token == METODO) {
            cout << "function ";
            token = getToken();
            if (token == VAR) {
                cout << variable;
            }
            token = getToken();
            if (token == APAR) {
                cout << "(";
                token = getToken();
                while (token != CPAR) {
                    if (token == VAR) {
                        cout << variable;
                    }
                    token = getToken();
                    if (token == COMA) {
                        cout << ", ";
                        token = getToken();
                    }
                }
                cout << ")";
            }
            token = getToken(); // :
            cout << " {" << endl;
            token = getToken(); // salto de linea
            token = getToken(); // tab
            // cout << "======" << token << endl;
            // while (token == TAB) {
            //     token = getToken();
                if (token == RETORNO) {
                    cout << "\treturn ";
                    token = getToken();
                    if (token == VAR) {
                        cout << variable;
                    } else if (token == NUM) {
                        cout << numero;
                    }
                    token = getToken();
                    if (token == SALTO) {
                        cout << ";" << endl;
                        token = getToken();
                    }
                }
            // }
            cout << "}" << endl;
        } else {
            token = getToken();
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
            /*Gestor de Errores*/
            cout<<"Error "<<nroError<<": ";
            if(nroError==100){ //Error de Analisis Lexico
                cout<<"No se reconoce: "<<cad[i]<<" en la posicion "<<i;
            }
            if(nroError==500){
                cout<<"La variable: "<<variable<<" no ha sido declarada";
            }
        }
};

int main()
{
    // Analisis*obj=new Analisis("graficos(){ posx1=120; posx2=120; posx=175; posy=100; tam1=100; tam2=75; cuadrado(200,200,tam1); linea(100,100,tam1,50); rectangulo(posx1,posy,tam2,tam2); radio=24; circulo(posx,posy,radio); }");
    // Analisis*obj=new Analisis("for e in [1,2,3,4,5]: print(e)");
    // Analisis*obj=new Analisis("for e in [1,2,3,4,5]:nn if e > 2:nn print(2)nn else: print(3) nn");
    Analisis*obj = new Analisis("");
    // Analisis*obj=new Analisis("print(1) nn");
    // Analisis*obj=new Analisis("def sumar(a): return a+1 if a > 0 else a+23");
    // obj->leerArchivo("input.py");
    // obj->leerArchivo("input2.py");
    // obj->leerArchivo("input3.py");
    // obj->leerArchivo("input4.py");
    // obj->leerArchivo("input5.py");
    // obj->leerArchivo("input6.py");
    // obj->leerArchivo("input7.py");
    // obj->leerArchivo("input8.py");
    // obj->leerArchivo("input9.py");
    obj->leerArchivo("input10.py");
    obj->Analizar();
    return true;
}
