# Autómata para el Análisis Léxico y Sintáctico

## Descripción del Autómata

1. **Estado inicial (e0):**

   - Se reconoce la palabra clave `def` que lleva al estado `e1`.

2. **Definición de funciones (e1 - e5):**

   - Estado `e1`: Se reconoce el nombre del método (`NMETODO`) y se pasa al estado `e2`.
   - Estado `e2`: Se espera un paréntesis abierto `(`, transiciona al estado `e3`.
   - Estado `e3`: Se reconoce una variable (`VAR`), transiciona al estado `e4`.
   - Estado `e4`: Se espera un paréntesis cerrado `)`, transiciona al estado `e5`.
   - Estado `e5`: Se espera un `:` para indicar el inicio del bloque, transiciona al estado `e6`.

3. **Bloque de código del método (e6 - e10):**

   - Estado `e6`: Se reconoce la palabra clave `return`, transiciona al estado `e7`.
   - Estado `e7`: Se reconoce una variable (`VAR`), transiciona al estado `e8`.
   - Estado `e8`: Se reconoce el operador `+`, transiciona al estado `e9`.
   - Estado `e9`: Se reconoce un número (`NUM`), transiciona al estado `e10`.

4. **Condicional (e10 - e14):**
   - Estado `e10`: Se reconoce la palabra clave `if`, transiciona al estado `e11`.
   - Estado `e11`: Se reconoce una variable (`VAR`), transiciona al estado `e12`.
   - Estado `e12`: Se reconoce el operador `>`, transiciona al estado `e13`.
   - Estado `e13`: Se reconoce un número (`NUM`), transiciona al estado `e14`.
   - Estado `e14`: Se reconoce la palabra clave `else`, transiciona al estado `e15`.
   - Estado `e15`: Se reconoce una variable (`VAR`), transiciona al estado `e16`.

## Diagrama del Autómata en Mermaid

```mermaid
graph LR
    e0[Inicio] -->|def| e1[def]
    e1 -->|NMETODO| e2[NMETODO]
    e2 -->|"("| e3[Paréntesis abierto]
    e3 -->|VAR| e4[Variable]
    e4 -->|")"| e5[Paréntesis cerrado]
    e5 -->|":"| e6[Dos puntos]
    e6 -->|return| e7[Return]
    e7 -->|VAR| e8[Variable]
    e8 -->|"+| e9[Operador +]
    e9 -->|NUM| e10[Número]
    e10 -->|if| e11[If]
    e11 -->|VAR| e12[Variable]
    e12 -->|">"| e13[Operador >]
    e13 -->|NUM| e14[Número]
    e14 -->|else| e15[Else]
    e15 -->|VAR| e16[Variable]
```
