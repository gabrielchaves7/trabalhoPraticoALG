#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list> 
using namespace std; 

void leEntradaCds(int quantidadeCentrosDeDistribuicao, vector<vector<int>> &arrayCD){
  string line;
  for (int i = 0; i < quantidadeCentrosDeDistribuicao; i++)
  {
    getline(cin, line);
    istringstream iss(line);
    vector<int> temp;
    for(string s; iss >> s; )
      temp.push_back(stoi(s));
    arrayCD.push_back(temp);
  }
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
  for(string s; iss >> s; ) 
      result.push_back(s);

  quantidadeCentrosDeDistribuicao = stoi(result.at(0));
  quantidadePontosDeVacinacao = stoi(result.at(1));
  perdaTemperatura = stoi(result.at(2));

  vector<vector<int>> arrayCD;
  leEntradaCds(quantidadeCentrosDeDistribuicao, arrayCD);
  for (unsigned i=0; i<arrayCD.size(); i++){
    int teste = arrayCD.at(0).at(i);
    cout << ' ' << teste;
  }
  system("pause");
  return 0;
}