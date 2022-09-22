#include "functions.hpp"

void metodo1();
void metodo2();

int main(){ 
	int option;
	std::cout << "\nEscolha uma das opcoes abaixo:" << std::endl;
	std::cout << "\n1 - Compactar texto" << std::endl;
	std::cout << "2 - Descompactar arquivo" << std::endl;
	std::cout << "\nOpcao: ";
	std::cin >> option;

	switch (option) {
		case 1:
			metodo1();
			break;
		
		case 2:
			metodo2();
			break;
		
		default:
			std::cout << "\nOpcao Invalida!" << std::endl;
			break;
	}

	return 0;
}

void metodo1() {
	Tree* t;
	Documento Doc;
	std::deque<bool> b;
	List<Record> rank;
	List<Tree*> Nos;
	std::string nome;
	FLVazia(&rank);
	FLVazia(&Nos);

	std::cout << "\nQual o nome do arquivo onde o texto esta: ";
	std::cin >> nome;

	pegarDocumento(&Doc, nome);
	normalizeRP(&Doc);
	createWordRank(&rank, &Doc);

	createListNos(&Nos, &rank);
	FLVazia(&rank);
	createHuffmanTree(&Nos);
	t = dequeueListNos(&Nos);
	t->reg.max_size = altura(t);
	FLVazia(&Nos);
	identificadores(&t, b, &Doc);
	compressFile(&Doc, nome);
	createTreeFile(t);
	delete t;
}

void metodo2() {
	Tree* t;
	std::deque<Tree*> arvores;
	getTreeFromFile(&arvores);
	makeHuffmanTree(&arvores, &t);
	t->reg.max_size = altura(t);
	decompressFile(t);
	delete t;
}