# Descrição
Trabalho prático de matemática discreta

## Como executar?
Primeiro abra o diretório src do projeto no terminal. Note que dentro deste diretório têm um arquivo chamado **tp2.exe**, que é o executável do programa. Você pode usar o seu compilador de preferência para abrir o executável.

## Como gerar o tp2.exe novamente?
Para gerar o tp2.exe basta abrir o diretório src e digitar o comando **make**

## Executando o projeto em um sistema windows no VSCODE
Dentro do arquivo .zip já está a configuração do launch.json para executar o projeto após ter gerado o tp2.exe. Apenas se atente para o "miDebuggerPath" do launch.json, que deve ser trocado para o caminho do seu compilador de C para windows. Após trocar esse caminho, basta apertar f5 que o programa será executado :D

## Ainda têm alguma dúvida ou não conseguiu executar?
Estou a disposição para ajudar nesta etapa, basta me mandar um email: **gabrielbum@gmail.com** ou uma mensagem no whatsapp **(31) 98249-9345**


## Observações
Para saber se o usuário já terminou de digitar as entradas, o programa espera um **EOF (end of line)**. No Windows, um end of line pode ser obtido apertando um **enter** após digitar as entradas e depois **ctrl z**. Usando o exemplo 5, ficaria da seguinte maneira:
3 20 21 22
20 21
20 22
22 22
22 20 **enter** 
**ctrl z**