#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
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

void imprimirResultado(int rotaComPostoDuplicado, vector<int> &listaPvsAlcancados){
    cout<<"\n";
    cout<<"Resultado";
    cout<<"\n";    
    cout<<listaPvsAlcancados.size();
    cout<<"\n";
    sort(listaPvsAlcancados.begin(), listaPvsAlcancados.end()); 
    for (unsigned i = 0; i < listaPvsAlcancados.size(); i++)
    {
      int pv = listaPvsAlcancados.at(i);
      cout << pv << ' ';
    }
    cout<<"\n";
    cout<<rotaComPostoDuplicado;
    cout<<"\n";
}

void realizaLogistica(int inicio, int rotaComPostoDuplicado, vector<int> &listaPvsAnteriores, vector<int> &listaPvsAlcancados, vector<vector<int>> arrayPV, int temperaturaAtual, int perdaTemperatura)
{
  temperaturaAtual = temperaturaAtual + perdaTemperatura;
  if (temperaturaAtual >= limiteTemperatura){
    imprimirResultado(rotaComPostoDuplicado, listaPvsAlcancados);
    return;
  }

  int qtdPvsJaAlcancados = listaPvsAlcancados.size();
  for (int i = inicio; i < qtdPvsJaAlcancados; i++)
  {
    int pvAtual = listaPvsAlcancados.at(i);
    int quantidadePvsAlcancaveis = arrayPV[pvAtual - 1].size();
    for (int k = 0; k < quantidadePvsAlcancaveis; k++)
    {
      int novoPvAlcancado = arrayPV[pvAtual - 1].at(k);

      if (find(listaPvsAnteriores.begin(), listaPvsAnteriores.end(), novoPvAlcancado) != listaPvsAnteriores.end())
        rotaComPostoDuplicado = rotaComPostoDuplicado + 1;

      if (find(listaPvsAlcancados.begin(), listaPvsAlcancados.end(), novoPvAlcancado) == listaPvsAlcancados.end())
        listaPvsAlcancados.push_back(novoPvAlcancado);
    }
  }

  listaPvsAnteriores = listaPvsAlcancados;

  return realizaLogistica(qtdPvsJaAlcancados, rotaComPostoDuplicado, listaPvsAlcancados, listaPvsAlcancados, arrayPV, temperaturaAtual, perdaTemperatura);
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
  vector<int> listaPvsAnteriores = listaPvsAlcancados;
  leEntradaPvs(quantidadePontosDeVacinacao, arrayPV);
  realizaLogistica(0, 0, listaPvsAnteriores, listaPvsAlcancados, arrayPV, temperaturaInicial, perdaTemperatura);
  system("pause");
  return 0;
}