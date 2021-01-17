#include <iostream>
#include <vector>
#include <sstream>
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

  //stoi converte string pra inteiro
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

  /*   A ideia aqui é para cada pv inicial, criar uma camada com as possíveis rotas, buscando todos os possíveis caminhos e inserindo eles em um array.
    Para o primeiro exemplo presente na documentação, onde temos o c1 que vai para o PV1 e PV2, 
    primeiro eu verifico todos os postos de vacinação que podemos chegar a partir do PV1 sem que 
    isso ultrapasse o limite de temperatura e vou inserindo isso no meu modelo de camadas.    

    Por exemplo, para o PV1, a variável camadas fica da seguinte forma: [[1], [16]]. O que significa que como primeira opção, temos o PV1, e como segunda opção o PV16. 
    Caso a camada fosse [[1], [2,3]], significaria que como primeira opção temos o PV1, e como segunda opção para a nossa rota o PV2 ou o PV3.
    Se quiserem verificar como está o modelo de camadas, têm uma função comentada imprimeModeloCamadas.

    Para verificar se já chegamos no limite de temperatura, eu só preciso checar se a
    (camadaAtual == camadasSize) pois o tamanho do vetor camadas é definido na 
    função main baseado no limite de temperatura e na perda após cada PV.*/

  for (int i = 0; i < proximosPVSSize; i++)
  {
    camadas.at(camadaAtual).push_back(proximosPVS.at(i));
    preencheCamadas(proximosPVS.at(i), arrayPV, camadaAtual + 1, camadas);
  }
}

bool hasDuplicates(const std::vector<int> &arr)
{
  // a ideia aqui é verificar se existe PVS duplicados em uma mesma camada, o que significaria que o caminhão poderia passar mesmo posto de vacinação na mesma rota.
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
  /* Como eu utilizei uma estrutura de dados com três arrays, eu preciso de 3 for, para percorrer o meu array de resultados, 
  o que cria uma complexidade n³ apenas para a impressão do meu resultado. Na minha visão esta foi a parte mais negativa do meu algoritmo.  */
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

  cout << "\n"
       << numeroDeRotasComMesmoPV << "\n";
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
} */

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
    /* Para cada PV Inicial eu crio uma camada e depois coloco isso em um vetor. Veja os comentários da função preencheCamadas que está com mais detalhes. */
    preencheCamadas(listaPvsIniciais.at(i), arrayPV, 0, camadas);

    vector<int> temp;
    temp.push_back(listaPvsIniciais.at(i));
    camadas.insert(camadas.begin(), temp);
    listaCamadas.push_back(camadas);
  }

  vector<int> pvsAlcancados;
  int numeroDeRotasComMesmoPV = 0;
  preencherResultado(listaCamadas, pvsAlcancados, numeroDeRotasComMesmoPV);
  /* imprimeModeloDeCamadas(listaCamadas); */
  imprimeResultado(pvsAlcancados, numeroDeRotasComMesmoPV);
  system("pause");
  return 0;
}