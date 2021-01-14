#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
using namespace std;
const int temperaturaInicial = -90;
const int limiteTemperatura = -60;

void leEntradaPrincipal(int &quantidadeCentrosDeDistribuicao, int &quantidadePontosDeVacinacao, int &perdaTemperatura)
{
  string temp;
  getline(cin, temp);
  vector<string> result;
  istringstream iss(temp);
  for (string s; iss >> s;)
    result.push_back(s);

  quantidadeCentrosDeDistribuicao = stoi(result.at(0));
  quantidadePontosDeVacinacao = stoi(result.at(1));
  perdaTemperatura = stoi(result.at(2));
}

void leEntradaCds(int quantidadeCentrosDeDistribuicao, vector<int> &listaPvsIniciais)
{
  string line;
  for (int i = 0; i < quantidadeCentrosDeDistribuicao; i++)
  {

    getline(cin, line);
    istringstream iss(line);
    for (string s; iss >> s;)
      listaPvsIniciais.push_back(stoi(s));
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

void preencherProximasCamadas(int pvAtual, vector<vector<int>> arrayPV, int camadaAtual, vector<vector<int>> &camadas)
{
  vector<int> proximosPVS = arrayPV.at(pvAtual - 1);

  if (camadaAtual == (camadas.size()) || (proximosPVS.at(0) == 0))
    return;

  for (int i = 0; i < proximosPVS.size(); i++)
  {
    camadas.at(camadaAtual).push_back(proximosPVS.at(i));
    preencherProximasCamadas(proximosPVS.at(i), arrayPV, camadaAtual + 1, camadas);
  }
}

bool hasDuplicates(const std::vector<int> &arr)
{
  for (std::size_t i = 0; i < arr.size(); ++i)
  {
    for (std::size_t j = i + 1; j < arr.size(); ++j)
    {
      if (arr[i] == arr[j])
        return true;
    }
  }
  return false;
}

void preencherResultado(vector<vector<vector<int>>> listaCamadas, vector<int> listaPvsIniciais, vector<int> &postosAlcancados, int &numeroDeRotasComMesmoPV)
{
  for (int i = 0; i < listaCamadas.size(); i++)
  {
    vector<vector<int>> camadaAtual = listaCamadas.at(i);
    vector<int> temp;
    temp.push_back(listaPvsIniciais.at(i));
    camadaAtual.insert(camadaAtual.begin(), temp);

    vector<int> postosCamadaAtual;
    for (int j = 0; j < camadaAtual.size(); j++)
    {
      vector<int> vetorPostos = camadaAtual.at(j);
      for (int k = 0; k < vetorPostos.size(); k++)
      {
        int postoAtual = vetorPostos.at(k);

        postosCamadaAtual.push_back(postoAtual);

        if (!count(postosAlcancados.begin(), postosAlcancados.end(), postoAtual))
          postosAlcancados.push_back(postoAtual);
      }
    }

    if (hasDuplicates(postosCamadaAtual))
      numeroDeRotasComMesmoPV = numeroDeRotasComMesmoPV + 1;
  }
}

void imprimeResultado(vector<int> postosAlcancados, int numeroDeRotasComMesmoPV)
{
  cout << "\n \n Testando resultado PARTE 2\n";
  cout << postosAlcancados.size() << " //Quantidade de postos alcancados \n";
  sort(postosAlcancados.begin(), postosAlcancados.end());
  for (int i = 0; i < postosAlcancados.size(); i++)
  {
    cout << postosAlcancados.at(i) << " ";
  }
  cout << " // Postos alcancados \n";
  cout << numeroDeRotasComMesmoPV << "// duplicados \n";
}

void imprimeModeloDeCamadas(vector<vector<vector<int>>> listaCamadas, vector<int> listaPvsIniciais)
{
  cout << "Testando resultado\n";
  for (int j = 0; j < listaCamadas.size(); j++)
  {
    vector<vector<int>> camadas = listaCamadas.at(j);
    vector<int> temp;
    temp.push_back(listaPvsIniciais.at(j));
    camadas.insert(camadas.begin(), temp);
    for (int i = 0; i < camadas.size(); i++)
    {
      cout << "[";
      for (int k = 0; k < camadas.at(i).size(); k++)
      {
        cout << camadas.at(i).at(k) << " ";
      }
      cout << "]";
    }
    cout << "\n";
  }
}

int main()
{
  int quantidadeCentrosDeDistribuicao;
  int quantidadePontosDeVacinacao;
  int perdaTemperatura;
  vector<int> listaPvsIniciais;
  vector<vector<int>> arrayPV;

  leEntradaPrincipal(quantidadeCentrosDeDistribuicao, quantidadePontosDeVacinacao, perdaTemperatura);
  leEntradaCds(quantidadeCentrosDeDistribuicao, listaPvsIniciais);
  leEntradaPvs(quantidadePontosDeVacinacao, arrayPV);

  int numeroCamadas = abs(((temperaturaInicial - limiteTemperatura) / perdaTemperatura));

  vector<vector<vector<int>>> listaCamadas;
  for (int i = 0; i < listaPvsIniciais.size(); i++)
  {
    vector<vector<int>> camadas(numeroCamadas - 1, vector<int>());
    preencherProximasCamadas(listaPvsIniciais.at(i), arrayPV, 0, camadas);
    listaCamadas.push_back(camadas);
  }

  vector<int> postosAlcancados;
  int numeroDeRotasComMesmoPV = 0;
  preencherResultado(listaCamadas, listaPvsIniciais, postosAlcancados, numeroDeRotasComMesmoPV);
  imprimeResultado(postosAlcancados, numeroDeRotasComMesmoPV);
  system("pause");
  return 0;
}