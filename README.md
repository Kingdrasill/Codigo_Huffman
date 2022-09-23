# Implementação código de Huffman para compactar textos

<div style="display: inline-block;">
<img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white"/>
<img src="https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white"/> 
<img src="https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white"/> 
<a href="https://github.com/mpiress/midpy/issues">
</a> 
</div>

<p align="justify">
  O objetivo deste código foi elaborar uma árvore binária que utilize o código de Huffman para comprimir arquivos. Para tanto, primeiro precisa-se contabilizar a recorrência de cada palavra (RP) no arquivo, depois normalizar a contabilização entre 0 e 1 utilizando a formula -> RP / (max(RP) - min(RP)), depois montar a árvore com as regras apresentadas por Huffman, depois trocar as palavras pela codificação binária (utilizar booleano para representar 0 e 1), e por último salvar o arquivo em formato binário e observe qual foi o ganho de espaço obtido.
</p>

# Estruturas utilizadas

<p align="justify">
  A primiera estrutura utilizada foi a utilizada para pegar as palavras do texto, está estrutura é uma lista de listas dinâmicas. O nível de estrutra mais baixo desta estrutra de lista de listas é onde a palavra do texto é guardada, o nome dado a ela foi Word. A imagem abaixo mosta está estrutura.
  <p align="center">
    <img src="imgs/palavra.png">
  </p>
  Na estrutura Word tem-se seis dados sendo eles: 'palavra' que é uma string que gurada a palavra do texto, 'lenght' que é um short int que guarda o tamanho de 'palavra', 'RP' que é um float que guarda o número de vezes que 'palavra' já apareceu no texto, 'value' que é um short int que guarda o valor ASCII de todos os caracteres de 'palavra', 'initial' que é um char que guarda a inicial de 'palavra' e 't' que é um ponteiro para onde 'palavra' vau estar na árvore de Huffman, o porque este dado é importante vai ser explicado depois.
  <br><br>
  A estrutura acima de Word é Palavras que gurada uma lista dinâmica de Word que possuem o mesmo tamanho. Nela se tem três dados 'listPal' que é a lista dinâmica de Word que guarda as palavras de um certo tamanho, 'tam' que é um int que guarda qual o tamanho das palavras em 'listPal' e 'qtd' que é um int que guarda o número de palavras em 'listPal'. A imagem abaixo ilustra está estrutura.
  <p align="center">
    <img src="imgs/listPalavra.png">
  </p>
  E acima de Palavras tem-se Documento, que o último nível de lista de lista, que guarda uma lista dinâmica de Palavras. Nela se tem três dados 'documento' que é uma lista dinâmica de Palavras que guarda todas as palavras do texto separadas em listas por tamanho, 'nome' que é um string que gurada o nome do arquivo  e 'qtd' que é um int que guarda a quantidade de palavras que tem no texto.
  <p align="center">
    <img src="imgs/documento.png">
  </p>
  E a última estrutura é Tree que utilizada para criar a árvore de Huffman, ela se baseia em uma árvore binária mais sobre elas em <a href="https://github.com/mpiress/basic_tree">https://github.com/mpiress/basic_tree</a>. Nesta estrutura Tree a uma abaixo dela que é Record que guarda as informações do nó da árvore, nele se tem sete dados sendo eles: 'palavra' que é um string que guarda a palavra salva no nó, 'lenght' que guarda o tamanho de 'palavra', 'RP' que guarda o número de repetições da palavra, 'bits' que é um vetor que guarda o caminho para chegar neste nó, 'size' que guarda o tamanho de 'bits' e 'max_Size' que gurada a altura desta árvore. A imagem abaixo mostra estas estruturas.
  <p align="center">
    <img src="imgs/tree.png">
  </p>
</p>

# Compactar um texto

<p align="justify">
  Quando o programa é rodado o usuário tem duas opções 1 - Compactar um texto e 2 - Descompactar um arquivo, primeiro vai ser explicada a opção 1. Quando ela é escolhida as seguintes opercações acontecem: primeiro um texto é informado pelo usuário, depois o texto é pego, depois o RP é normalizado, depois se cria uma lista de rankeamento, depois é criada a floresta de Huffman, depois se cria a árvore de Huffman, depois se pega a altura da árvore, as folhas das árvores recebem seus caminhos, depois o arquivo é comprimido e por último se cria o arquivo onde a árvore será salva. A imagem abaixo ilustra este processo.
  <p align="center">
    <img src="imgs/compacta.png">
  </p>
  Depois do nome do arquivo do texto ser informado, o método 'pegarDocumento' é chamado nele é se passado um ponteiro de Documento e o nome do arquivo. No método o arquivo com o nome é aberto, se ele não for aberto aparecerá uma mensagem de erro, são pegos dados até achar um '\n' no arquivo, com cada linha de dados vão ser pegos dados separados por ' ', com este dado vai ser tirado qualquer pontuação no início e no fim do dado e passara ele para minuscúlo, este processo vai ser feito até não tiver mais dados a serem pegos no arquivo. Depois dos tratamentos do dado eles serão em uma lista de Palavras, depois de todos os dados forem adicionados na lista eles são adicionados no Documento passado, e por último o arquivo é fechado. A imagem abaixo ilustra o método.
  <p align="center">
    <img src="imgs/pegarDocumento.png">
  </p>
  Depois do método 'pegarDocumento' o método 'normalizeRP' é chamado nele é se passado o ponteiro do Documento criado no método anterior. Antes de explicar este método dois outros métodos são importantes que são 'findMaxRP' e 'findMinRP' que buscam o maior e menor RP respectivamente no Documento passado. O método 'normalizeRP' pega cada Word no Documento passado e atualiza o RP dela para ser igual a ele mesmo divido pelo maior menos o menor RP, pegos pelos métods descritos antes. As imagens abaixo ilustram estes métodos. 
  <p align="center">
    <img src="imgs/findMaxRP.png">
    <img src="imgs/findMinRP.png">
  </p>
  <p align="center">
    <img src="imgs/normalizeRP.png">
  </p>
  Depois do método 'normalizeRP' o método chamado é o 'createWordRank' nele se é passado um ponteiro de uma lista de Record e o ponteiro do Doumento. Este método pega cada Word no Documento e cria um Record com as informações de Word, o RP é modificado um pouco para tentar não haver RPs iguais. Após Record é criado ele é adiconado na lista de Record passada, nesta lista quando um dado é adicionado ele já é ordenado com ordem sendo em ordem de RP crescente, se algum RP for igual a ordem destes iguas vai ser decrescente com tamanho da palavra, se o tamanho e o RP for igual o valor ASCII é usado para colocar os dados em ordem crescente, e se RP, tamanho e valor forem iguais ele apenas é colocado na frente do elemento onde todos forem iguais.
  <p align="center">
    <img src="imgs/createWordRank.png">
  </p>
  Depois do método 'createWordRank' tem se o método 'createListNos' que recebe os ponteiros de duas listas uma de Record e uma de ponteiro de Tree. Este método faz a mesma coisa que o anterior sendo isto ele pega um Record e cria um Tree com ele, adicionando o ponteiro deste Tree sempre no final da lista de ponteiro de Tree, pois os dados já estão ordenados.
  <br><br>
  Depois do método 'createListNos' vem o método 'createHuffmanTree' que recebe o ponteiro para lista de ponteiro de Tree para criar a árvore de Huffman. Este método ficara rodando até que só tem um elemento na lista, sendo ele a árvore completa, repetindo os seguintes passos: se pega e remove os dois primeiro Tree da lista, eles são pegos usando o método 'dequeueListNos', e os manda para o método 'insertHuffmanForest' junto com a lista. No método 'insertHuffmanForest' o seguinte processo acontece, primeiro um novo Tree é criado com seu 'reg' tendo os dados a seguir palavra sendo ' ', o RP, lenght, e value sendo a soma dos mesmos dados dos dois Tree passados para o método. Depois é se colocado no ponteiro 'esq' do novo Tree o Tree passado que tiver o maior RP e no ponteiro 'dir' o Tree com menor RP, se os RP forem iguais o tamanho é utilizado e se os tamanhos forem iguias o valor ASCII é usado. Após isto este novo Tree é inserido na lista seguindo a mesma lógica de 'createWordRank', ordem de RP crecente e se RP igual ordem de lenght e valor ASCII decrescente. As imagens abaixo mostram os métodos 'createHuffmanTree' e 'insertHuffmanForest'.
  <p align="center">
    <img src="imgs/createHuffmanTree.png">
  </p>
  <p align="center">
    <img src="imgs/insertHuffmanForest.png">
  </p>
  Depois do método 'creataHuffmanTree' o único dado na lista de ponteiro de Tree vai ser a árvore de Huffman, ela é removida da lista e armazenada, depois é usado o método 'altura' para setar o dado max_size do 'reg' da raiz da árvore, no método 'altura' é passado a raiz da árvore. A imagem ilustra o método recursivo 'altura'.
  <p align="center">
    <img src="imgs/altura.png">
  </p>
  Depois é chamado 'identificadores' que é passado a raiz da árvore, um deque de bool vazio e o ponteiro do Doumento criado anteriormente. Este método é um recursivo que serve para setar a altura de todos os nós da árvore passada e em todos nós, menos a raiz, vão atualizar no dado 'reg' o valor de bits para ser igual ao deck passado. Nos nós em que a palavra é diferente de ' ' a palavra vai ser procurada no Documento e se achar o dado 't' do Word onde ela foi salva vai receber o ponteiro para o nó da árvore que está palavra está. Depois que os dados do nó forem atualizados o método é chamado para o filho esquerdo e diretiro, só que o deck do esquerdo vai ter um bool false extra no final e no deck do direito um bool true no final. A imagem abaixo ilustra o método recursivo.
  <p align="center">
    <img src="imgs/identificadores.png">
  </p>
  Depois é chamado 'compressFile' que é passado o ponteiro do Documento e o nome do arquivo do texto que vai ser compactado, para o texto ser compactado a árvore de Huffman tem que ter no máximo 16 de altura. Neste método primeiro é se perguntado qual vai ser o nome do arquivo binário onde o texto vai ser compactado, depois abri-se os arquivos dois arquivos, o passado para método e o que vai ser o compactado o texto, depois de abertos é pego uma palavra do texto usando a mesma lógica do método 'pegarDocumento', a mesma é procurada em Documento se for achada se retorna o Word onde ela esta com ele é se utilizado o ponteiro de Tree para pegar o array de bool na árvore de Huffman da palavra, como arquivos binários trabalham com char e não bools o array de bool são convertidos para dois char, ai está o motivo de ser no máximo altura 16, e por último os chars são adicionados no arquivo binário, isto é feito para toas palavras no texto. A imagem abaixo ilustra este método.
  <p align="center">
    <img src="imgs/compressFile.png">
  </p>
  E o último método chamdo é o 'createTreeFile' que é passado a árvore de Huffman para guardar ela num arquivo para o texto poder ser descompactado. Nele é primeiro criado um deque com a raiz da árvore, isto serve para andar em largura, pedido o nome do arquivo onde a árvore vai ser salva, depois o arquivo é aberto e com isto é começado o seguinte processo é repetido até que o deque fique vazio: primeiro pega e remove o primeiro elemento do deque, depois com o elemento é escrito no arquivo em linhas diferentes os dados de bits e a palavra do elemento, isto não é feito para raiz, depois é se adicionado os filhos esquerdo e direito do elemento no deque. A imagem abaixo mostra este método.  
  <p align="center">
    <img src="imgs/createTreeFile.png">
  </p>
</p>

# Descompactar um arquivo

<p align="justify">
  A segunda opção que pode ser selecionada pelo usuário ao rodar o programa é a 2 - Descompactar um arquivo. Nela a primeira coisa feita é um deque de ponteiros de Tree, depois com a lista é criado a árvore de Huffman, depois pego a altura dela e depois o arquivo desejado pelo usuário é descompactado.
  <p align="center">
    <img src="imgs/descompacta.png">
  </p>
  O primeiro método chamado é o 'getTreeFromFile' é passado para ele um ponteiro de deque de Tree. Nele primeiro é perguntado o nome do arquivo onde a árvore está salva, depois um Tree vazio é criado e inserido no deque, ele é a raiz da árvore de Huffman, depois o arquivo é aberto com ele aberto é se repetido as seguintes operações até não ter mais informações no arquivo, neste loop os dados em duas linhas do arquivo são armazenados em sbits e palavra: primeiro é pego o tamanho de sbits depois a string sbtis é transformada em um array de bool bits, depois é criado um Tree novo e os dados bits e palavras são colocado no mesmo, e por último o ponteiro para o novo Tree é colocado no deque.  
  <p align="center">
    <img src="imgs/getTreeFromFile.png">
  </p>
  O próximo método chamado é o 'makeHuffmanTree' que passado o ponteiro do deque de ponteiros de Tree e um ponteiro de Tree. Nele primeiro o ponteiro de Tree recebe o primeiro elemento do deque e o mesmo é removido, depois vais e repetir os processos a seguir até que o deque fique vazio: pega e remove o primeiro dado de deque, depois anda-se em no Tree do ponteiro passado com o bits do dado peguo, e por último o dado é salvo no nó onde parou de andar.
  <p align="center">
    <img src="imgs/makeHuffmanTree.png">
  </p>
  O último método chamado é o 'decompressFile' que é passado a árvore de Huffman criada anteriormente. Nele primeiro é perguntado os nomes dos arquivos compactado e do onde o texto descompactado vai ser salvo, depois estes arquivos são abertos com eles abertos do arquivo compactado é pego dois chars que são transformados em um array de bool que é utilizado para andar na árvore até achar um nó em que a palavra não seja ' ' e palavra no nó é adiconado no arquivo do texto descompactado, este processo é feito até que não seja possível pegar dois chars do arquivo compactado.
  <p align="center">
    <img src="imgs/decompressFile.png">
  </p>
</p>

# Resultados

# Compilação e Execução

O código disponibilizado possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:

<div align="center">

| Comando                |  Função                                                                                           |
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

</div>
