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

#define FIN     666
#define ERROR   999

#define null "6c3e226b4d4795d518ab341b0824ec29"
#define vacio "-"
#define asignado "asignado"

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
        int Mostrar(){
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
        int tTransicion[22][14];
        TablaSimbolos ts;
    public:
        Analisis(char input[100]){
            //Aqui hacer la apertura de archivo de texto plano
            strcpy(cad,input);
            i=0;

            /*Modificar: Adecuar su tabla de simbolos*/
/*             ts.Insertar("graficos",GRAFICOS,"pclave",vacio,vacio);
            ts.Insertar("(",APAR,"pclave",vacio,vacio);
            ts.Insertar(")",CPAR,"pclave",vacio,vacio);
            ts.Insertar("{",ALLAVE,"pclave",vacio,vacio);
            ts.Insertar("}",CLLAVE,"pclave",vacio,vacio);
            ts.Insertar("=",IGUAL,"pclave",vacio,vacio);
            ts.Insertar(";",PCOMA,"pclave",vacio,vacio);
            ts.Insertar("cuadrado",CUADRADO,"pclave",vacio,vacio);
            ts.Insertar("rectangulo",RECTANGULO,"pclave",vacio,vacio);
            ts.Insertar("circulo",CIRCULO,"pclave",vacio,vacio);
            ts.Insertar("linea",LINEA,"pclave",vacio,vacio);
            ts.Insertar(",",COMA,"pclave",vacio,vacio); */
            ts.Insertar("for",BUCLEF,"pclave",vacio,vacio);
            ts.Insertar("var",VAR,"pclave",vacio,vacio);
            ts.Insertar("in",INF,"pclave",vacio,vacio);
            ts.Insertar("[",ACORCHETE,"pclave",vacio,vacio);
            // ts.Insertar("num",NUM,"pclave",vacio,vacio);
            ts.Insertar(",",COMA,"pclave",vacio,vacio);
            ts.Insertar("]",CCORCHETE,"pclave",vacio,vacio);
            ts.Insertar(":",DPUNTOSF,"pclave",vacio,vacio);
            ts.Insertar("print",IMPRIMIR,"pclave",vacio,vacio);
            ts.Insertar("(",APAR,"pclave",vacio,vacio);
            ts.Insertar(")",CPAR,"pclave",vacio,vacio);

            ts.Insertar("if",SI,"pclave",vacio,vacio);
            ts.Insertar(">",MAYOR,"pclave",vacio,vacio);
            ts.Insertar("else",ENTONCES,"pclave",vacio,vacio);
            ts.Insertar("def",METODO,"pclave",vacio,vacio);
            ts.Insertar("sumar",NMETODO,"pclave",vacio,vacio);
            ts.Insertar("return",RETORNO,"pclave",vacio,vacio);
            ts.Insertar("+",MAS,"pclave",vacio,vacio);
        }

        bool iselement(char c){
            char elements[100];
            /*AQUI DEBEN DE DEFINIR LOS CARACTERES QUE NO SEAN LETRAS O NUMEROS Y QUE CORRESPONDAN AL LENGUAJE*/
            /*NO DEBEN DE REPETIR CARACTERES*/
            strcpy(elements,"(),:[]+>");/*<- AQUI MODIFICAR*/
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
            while(cad[i]=='\n'){
                i++;
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

        bool Lexico(){
            i=0;
            int token=0;
            while(true){
                token=getToken();
                cout<<token<<endl;
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
            return true;
        }
        bool Semantico(){
            return true;
        }
        bool Ejecucion(){
            return true;
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
        }
};

int main()
{
    // Analisis*obj=new Analisis("graficos(){ posx1=120; posx2=120; posx=175; posy=100; tam1=100; tam2=75; cuadrado(200,200,tam1); linea(100,100,tam1,50); rectangulo(posx1,posy,tam2,tam2); radio=24; circulo(posx,posy,radio); }");
    // Analisis*obj=new Analisis("for e in [1,2,3,4,5]: print(e)");
    // Analisis*obj=new Analisis("for e in [1,2,3,4,5]: if e > 2: print('es mayor a 2') else: print('es mayor igual a 2')");
    Analisis*obj=new Analisis("def sumar(a): return a+1 if a > 0 else a+23");
    obj->Analizar();
    return true;
}
