#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
using namespace std;
const int temperaturaInicial = -90;
const int limiteTemperatura = -60;

void leEntradaPrincipal(int &quantidadeCds, int &quantidadePvs, int &perdaTemperatura)
{
  string temp;
  getline(cin, temp);
  vector<string> result;
  istringstream iss(temp);
  for (string s; iss >> s;)
    result.push_back(s);

  quantidadeCds = stoi(result.at(0));
  quantidadePvs = stoi(result.at(1));
  perdaTemperatura = stoi(result.at(2));
}

void leEntradaCds(int quantidadeCds, vector<int> &listaPvsIniciais)
{
  string line;
  for (int i = 0; i < quantidadeCds; i++)
  {

    getline(cin, line);
    istringstream iss(line);
    for (string s; iss >> s;)
      listaPvsIniciais.push_back(stoi(s));
  }
}

void leEntradaPvs(int quantidadePvs, vector<vector<int>> &arrayPV)
{
  string line;
  for (int i = 0; i < quantidadePvs; i++)
  {
    getline(cin, line);
    istringstream iss(line);
    vector<int> caminhosPV;
    for (string s; iss >> s;)
      caminhosPV.push_back(stoi(s));
    arrayPV.push_back(caminhosPV);
  }
}

void preencheCamadas(int pvAtual, vector<vector<int>> arrayPV, int camadaAtual, vector<vector<int>> &camadas)
{
  vector<int> proximosPVS = arrayPV.at(pvAtual - 1);

  int camadasSize = camadas.size();
  int proximosPVSSize = proximosPVS.size();
  if (camadaAtual == camadasSize || (proximosPVS.at(0) == 0))
    return;

  for (int i = 0; i < proximosPVSSize; i++)
  {
    camadas.at(camadaAtual).push_back(proximosPVS.at(i));
    preencheCamadas(proximosPVS.at(i), arrayPV, camadaAtual + 1, camadas);
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

void preencherResultado(vector<vector<vector<int>>> arrayCamadas, vector<int> &postosAlcancados, int &numeroDeRotasComMesmoPV)
{
  int arrayCamadasSize = arrayCamadas.size();
  for (int i = 0; i < arrayCamadasSize; i++)
  {
    vector<vector<int>> camadaAtual = arrayCamadas.at(i);

    int camadaAtualSize = camadaAtual.size();
    vector<int> pvsCamadaAtual;
    for (int j = 0; j < camadaAtualSize; j++)
    {
      vector<int> arrayPvs = camadaAtual.at(j);
      int arrayPvsSize = arrayPvs.size();
      for (int k = 0; k < arrayPvsSize; k++)
      {
        int pvAtual = arrayPvs.at(k);

        pvsCamadaAtual.push_back(pvAtual);

        if (!count(postosAlcancados.begin(), postosAlcancados.end(), pvAtual))
          postosAlcancados.push_back(pvAtual);
      }
    }

    if (hasDuplicates(pvsCamadaAtual))
      numeroDeRotasComMesmoPV = numeroDeRotasComMesmoPV + 1;
  }
}

void imprimeResultado(vector<int> postosAlcancados, int numeroDeRotasComMesmoPV)
{
  cout << "RESULTADO: \n";
  cout << postosAlcancados.size() << "\n";
  sort(postosAlcancados.begin(), postosAlcancados.end());
  int postosAlcancadosSize = postosAlcancados.size();
  if (postosAlcancadosSize > 0)
  {
    for (int i = 0; i < postosAlcancadosSize; i++)
    {
      cout << postosAlcancados.at(i) << " ";
    }
  }
  else
  {
    cout << "*";
  }

  cout << "\n" << numeroDeRotasComMesmoPV << "\n";
}

/* void imprimeModeloDeCamadas(vector<vector<vector<int>>> listaCamadas)
{
  cout << "Testando resultado\n";
  for (int j = 0; j < listaCamadas.size(); j++)
  {
    vector<vector<int>> camadas = listaCamadas.at(j);
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
 */
int main()
{
  int quantidadeCds;
  int quantidadePvs;
  int perdaTemperatura;
  vector<int> listaPvsIniciais;
  vector<vector<int>> arrayPV;

  leEntradaPrincipal(quantidadeCds, quantidadePvs, perdaTemperatura);
  leEntradaCds(quantidadeCds, listaPvsIniciais);
  leEntradaPvs(quantidadePvs, arrayPV);

  int numeroCamadas = abs(((temperaturaInicial - limiteTemperatura) / perdaTemperatura));

  vector<vector<vector<int>>> listaCamadas;
  int listaPvsIniciaisSize = listaPvsIniciais.size();
  for (int i = 0; i < listaPvsIniciaisSize; i++)
  {
    if (numeroCamadas < 1)
      break;

    vector<vector<int>> camadas(numeroCamadas - 1, vector<int>());
    preencheCamadas(listaPvsIniciais.at(i), arrayPV, 0, camadas);

    vector<int> temp;
    temp.push_back(listaPvsIniciais.at(i));
    camadas.insert(camadas.begin(), temp);
    listaCamadas.push_back(camadas);
  }

  vector<int> pvsAlcancados;
  int numeroDeRotasComMesmoPV = 0;
  preencherResultado(listaCamadas, pvsAlcancados, numeroDeRotasComMesmoPV);
  //imprimeModeloDeCamadas(listaCamadas, listaPvsIniciais);
  imprimeResultado(pvsAlcancados, numeroDeRotasComMesmoPV);
  system("pause");
  return 0;
}