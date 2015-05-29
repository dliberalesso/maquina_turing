#include "maquina_turing.hpp"

int ultimo()
{
  cout << "Informe o numero correspondente ao ultimo estado: ";
  int ultimo;
  cin >> ultimo;
  return ultimo;
}

char branco()
{
  cout << "Informe o caractere que representa o espaco em branco: ";
  char branco;
  cin >> branco;
  return branco;
}

int main()
{
  MaquinaTuring novaMaquina(ultimo(), branco());
  return 0;
}