#include "maquina_turing.hpp"

MiniEstado::MiniEstado(char le, char grava, char move, Estado *novo)
{
  leitura = le;
  escrita = grava;
  direcao = move;
  novo_estado = novo;
}

Estado::Estado(int n)
{
  nome = n;
  tamanho = 0;
}

void Estado::associaMiniEstado(MiniEstado miniEstado)
{
  lista_mini_estados.push_back(miniEstado);
  tamanho++;
}

MiniEstado* Estado::procuraMiniEstado(char lido)
{
  for (int i = 0; i < tamanho; i++) {
    if (lista_mini_estados[i].getLeitura() == lido) {
      return &lista_mini_estados[i];
    }
  }

  return NULL;
}

TabelaEstados::TabelaEstados(int tam) : tamanho(tam + 1)
{
  for (int i = 0; i < tamanho; i++) {
    Estado estado(i);
    lista_estados.push_back(estado);
  }
}

Estado* TabelaEstados::procuraEstado(int n)
{
  for (int i = 0; i < tamanho; i++) {
    if (lista_estados[i].getNome() == n) {
      return &lista_estados[i];
    }
  }
}

void Fita::safeGuard()
{
  if (fita[0] != em_branco) {
    fita = em_branco + fita;
    cabecote++;
  }

  if (fita.back() != em_branco) {
    fita += em_branco;
  }
}

void Fita::gravaString(string a_gravar)
{
  fita = a_gravar;
  safeGuard();
}

void Fita::gravaChar(char a_gravar)
{
  fita[cabecote] = a_gravar;
  safeGuard();
}

void Fita::moveCabecote(char direcao)
{
  direcao == 'd' ? (cabecote++) : (cabecote--);
}

char Fita::getChar()
{
  return fita[cabecote];
}

string Fita::getString()
{
  while (fita.front() == em_branco) {
    fita.erase(fita.begin());
  }

  while (fita.back() == em_branco) {
    fita.pop_back();
  }

  return fita;
}

MaquinaTuring::MaquinaTuring(int ultimo, char branco) : tabelaEstados(ultimo)
        , fita(branco)
{
  for (int i = 0; i < tabelaEstados.getTamanho(); ) {
    if (cadastraEstado(i)) {
      i++;
    }
  }

  gravaString();

  Estado *estado_inicial = tabelaEstados.procuraEstado(0);
  if (executaMaquina(estado_inicial)) {
    cout << "Aceita!" << endl;
    cout << fita.getString() << endl;
  } else {
    cout << "Erro!" << endl;
  }
}

int MaquinaTuring::cadastraEstado(int nome)
{
  Estado *estado = tabelaEstados.procuraEstado(nome);

  cout << "Cadastrando estado " << estado->getNome() << "." << endl;

  cout << "Le: ";
  char leitura;
  cin >> leitura;

  cout << "Grava: ";
  char escrita;
  cin >> escrita;

  char direcao;
  while (1) {
    cout << "Direcao (d|e|a): ";
    cin >> direcao;
    tolower(direcao);

    if ((direcao == 'd') || (direcao == 'e') || (direcao == 'a')) {
      break;
    } else {
      cout << "Entrada invalida! Tente novamente..." << endl;
    }
  }

  int novo;
  if (direcao != 'a') {
    cout << "Novo estado: ";
    cin >> novo;
  }

  cout << "Estado: " << estado->getNome();
  cout << "; Le: " << leitura;
  cout << "; Grava: " << escrita;
  cout << "; Move: " << direcao;
  if (direcao != 'a') {
    cout << "; Novo estado: " << novo;
  }
  cout << "." << endl;

  cout << "Confirma (s|n)? ";
  char opc;
  cin >> opc;
  tolower(opc);

  if (opc == 's') {
    if (direcao != 'a') {
      MiniEstado miniEstado(leitura, escrita, direcao, tabelaEstados
              .procuraEstado(novo));
      estado->associaMiniEstado(miniEstado);
    } else {
      MiniEstado miniEstado(leitura, escrita, direcao, NULL);
      estado->associaMiniEstado(miniEstado);
    }
  }

  cout << "Deseja cadastrar outro estado " << estado->getNome();
  cout << " (s|n)? " << endl;
  cin >> opc;
  tolower(opc);

  if (opc == 'n') {
    return 1;
  } else {
    return 0;
  }
}

void MaquinaTuring::gravaString()
{
  cout << "Digite o conteudo da fita:" << endl;
  string a_gravar;
  cin >> a_gravar;
  fita.gravaString(a_gravar);
}

int MaquinaTuring::executaMaquina(Estado *estado)
{
  char lido = fita.getChar();
  MiniEstado *miniEstado = estado->procuraMiniEstado(lido);

  if (miniEstado == NULL) {
    cout << "Nao existe estado " << estado->getNome();
    cout << " que leia " << lido << "!" << endl;
    return 0;
  }

  char escrever = miniEstado->getEscrita();
  fita.gravaChar(escrever);

  char mover = miniEstado->getDirecao();
  if (mover == 'a') {
    return 1;
  } else {
    fita.moveCabecote(mover);
    Estado *novo_estado = miniEstado->getNovoEstado();

    // Recursividade!
    return executaMaquina(novo_estado);
  }
}
