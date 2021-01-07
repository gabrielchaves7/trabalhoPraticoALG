#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
using namespace std;
const int temperaturaInicial = -90;
const int limiteTemperatura = -60;

void leEntradaCds(int quantidadeCentrosDeDistribuicao, vector<int> &arrayCD)
{
  string line;
  for (int i = 0; i < quantidadeCentrosDeDistribuicao; i++)
  {
    getline(cin, line);
    istringstream iss(line);
    for (string s; iss >> s;)
    {
      arrayCD.push_back(stoi(s));
    }
  }
}

void leEntradaPvs(int quantidadePontosDeVacinacao, vector<vector<int>> &arrayPV)
{
  string line;
  for (int i = 0; i < quantidadePontosDeVacinacao; i++)
  {
    getline(cin, line);
    istringstream iss(line);
    vector<int> caminhosPV;
    for (string s; iss >> s;)
      caminhosPV.push_back(stoi(s));
    arrayPV.push_back(caminhosPV);
  }
}

void realizaLogistica(int inicio, vector<int> &listaPvsAlcancados, vector<vector<int>> arrayPV, int temperaturaAtual, int perdaTemperatura)
{
  temperaturaAtual = temperaturaAtual + perdaTemperatura;
  if (temperaturaAtual >= limiteTemperatura)
    return;

  int qtdPvsJaAlcancados = listaPvsAlcancados.size();
  for (int i = inicio; i < qtdPvsJaAlcancados; i++)
  {
    int pvAtual = listaPvsAlcancados.at(i);
    int quantidadePvsAlcancaveis = arrayPV[pvAtual - 1].size();
    for (int k = 0; k < quantidadePvsAlcancaveis; k++)
    {
      listaPvsAlcancados.push_back(arrayPV[pvAtual - 1].at(k));
    }
  }

  return realizaLogistica(qtdPvsJaAlcancados, listaPvsAlcancados, arrayPV, temperaturaAtual, perdaTemperatura);
}

int main()
{
  int quantidadeCentrosDeDistribuicao;
  int quantidadePontosDeVacinacao;
  int perdaTemperatura;

  string temp;
  getline(cin, temp);
  vector<string> result;
  istringstream iss(temp);
  for (string s; iss >> s;)
    result.push_back(s);

  quantidadeCentrosDeDistribuicao = stoi(result.at(0));
  quantidadePontosDeVacinacao = stoi(result.at(1));
  perdaTemperatura = stoi(result.at(2));

  vector<int> listaPvsAlcancados;
  vector<vector<int>> arrayPV;
  leEntradaCds(quantidadeCentrosDeDistribuicao, listaPvsAlcancados);
  leEntradaPvs(quantidadePontosDeVacinacao, arrayPV);
  realizaLogistica(0, listaPvsAlcancados, arrayPV, temperaturaInicial, perdaTemperatura);

  for (unsigned i = 0; i < listaPvsAlcancados.size(); i++)
  {
    int teste = listaPvsAlcancados.at(i);
    cout << ' ' << teste;
  }

  system("pause");
  return 0;
}