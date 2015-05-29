#ifndef MAQUINA_TURING_MAQUINATURING_HPP
#define MAQUINA_TURING_MAQUINATURING_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Estado;

class MiniEstado
{
private:
  char leitura;
  char escrita;
  char direcao;
  Estado *novo_estado;

public:
  MiniEstado(char le, char grava, char move, Estado *novo);
  char getLeitura() {return leitura;}
  char getEscrita() {return escrita;}
  char getDirecao() {return direcao;}
  Estado* getNovoEstado() {return novo_estado;}
};

class Estado
{
private:
  int nome;
  int tamanho;
  vector<MiniEstado> lista_mini_estados;

public:
  Estado(int n);
  int getNome() {return nome;}
  void associaMiniEstado(MiniEstado miniEstado);
  MiniEstado* procuraMiniEstado(char lido);
};

class TabelaEstados
{
private:
  int tamanho;
  vector<Estado> lista_estados;

public:
  TabelaEstados(int tam);
  int getTamanho() {return tamanho;}
  Estado* procuraEstado(int n);
};

class Fita
{
private:
  int cabecote;
  char em_branco;
  string fita;

public:
  Fita(char branco) {cabecote = 0; em_branco = branco;}
  void safeGuard();
  void gravaString(string a_gravar);
  void gravaChar(char a_gravar);
  void moveCabecote(char direcao);
  char getChar();
  string getString();
};

class MaquinaTuring
{
private:
  TabelaEstados tabelaEstados;
  Fita fita;

public:
  MaquinaTuring(int ultimo, char branco);
  int cadastraEstado(int nome);
  void gravaString();
  int executaMaquina(Estado *estado);
};

#endif //MAQUINA_TURING_MAQUINATURING_HPP
