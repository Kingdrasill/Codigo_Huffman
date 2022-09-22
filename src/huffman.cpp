#include "huffman.hpp"

Tree* dequeueListNos(List<Tree*> *lista) {
    Block<Tree*> *aux;
    Tree* t;
	if(lista->cabeca == lista->cauda){
		printf("LISTA VAZIA!\n");
		return nullptr;
    }
	
	aux = lista->cabeca->prox;
	lista->cabeca->prox = aux->prox;
	
	if (lista->cabeca->prox == NULL)
		lista->cauda= lista->cabeca;
	
	t = aux->dado;
	free(aux);
    return t;
}

bool isEmpty(List<Tree*> *lista) {
    if(lista->cabeca == lista->cauda){
		return true;
    }
	return false;
}

void createHuffmanTree(List<Tree*> *nos) {
    while(nos->qtd > 1) {
        Tree* no1 = dequeueListNos(nos);
        nos->qtd--;
        Tree* no2 = dequeueListNos(nos);
        nos->qtd--;
        insertHuffmanForest(nos, &no1, &no2);
    }
}

void insertHuffmanForest(List<Tree*> *nos, Tree** no1, Tree** no2) {
    Tree *raiz = CreateTree();
    Record r;

    r.palavra = " ";
    r.RP = (*no1)->reg.RP + (*no2)->reg.RP;
    r.lenght = (*no1)->reg.lenght + (*no2)->reg.lenght;
    r.value = (*no1)->reg.value + (*no2)->reg.value;

    insertTree(&raiz, r);
    if((*no1)->reg.RP > (*no2)->reg.RP) {
        raiz->esq = (*no1);
        raiz->dir = (*no2);
    } else if((*no1)->reg.RP < (*no2)->reg.RP) {
        raiz->esq = (*no2);
        raiz->dir = (*no1);
    } else {
        if((*no1)->reg.lenght> (*no2)->reg.lenght) {
            raiz->esq = (*no1);
            raiz->dir = (*no2);
        } else if((*no1)->reg.lenght < (*no2)->reg.lenght) {
            raiz->esq = (*no2);
            raiz->dir = (*no1);
        } else {
            if((*no1)->reg.value > (*no2)->reg.value) {
                raiz->esq = (*no1);
                raiz->dir = (*no2);
            } else {
                raiz->esq = (*no2);
                raiz->dir = (*no1);
            }
        }
    }

    if(nos->cabeca != nos->cauda)               // Caso a lista não esteja vazia
    {
        Block<Tree*>* tmp = new Block<Tree*>; // Novo elemento na lista
        Block<Tree*>* aux;                                 // Variável auxiliar para andar na lista

        tmp->dado = raiz;
        aux = nos->cabeca;
        while (aux->prox != nullptr && aux->prox->dado->reg.RP < r.RP) {   // Achar a posição em que a nova palavra deve ser inserida, está posição
            aux = aux->prox;                                                   // é em que o valor ASCii da palavra é maior do que o valor da palavra anterior
        }
        
        if(aux->prox == nullptr)
        {
            tmp->prox = aux->prox;
            aux->prox = tmp;
            nos->cauda = tmp;
        }
        else {
            if(aux->prox->dado->reg.RP > r.RP) 
            {
                tmp->prox = aux->prox;
                aux->prox = tmp;
                if(tmp->prox == nullptr)
                    nos->cauda = tmp;
            } else {
                while(aux->prox != nullptr && aux->prox->dado->reg.RP == r.RP && aux->prox->dado->reg.lenght > r.lenght) {
                    aux = aux->prox;
                }
                if(aux->prox == nullptr) {
                    tmp->prox = aux->prox;
                    aux->prox = tmp;
                    nos->cauda = tmp;
                } else {
                    if(aux->prox->dado->reg.lenght < r.lenght) {
                        tmp->prox = aux->prox;
                        aux->prox = tmp;
                        if(tmp->prox == nullptr)
                            nos->cauda = tmp;
                    } else {
                        while(aux->prox != nullptr && aux->prox->dado->reg.RP == r.RP && aux->prox->dado->reg.lenght == r.lenght && aux->prox->dado->reg.value > r.value) {
                            aux = aux->prox;
                        }
                        tmp->prox = aux->prox;
                        aux->prox = tmp;
                        if(tmp->prox == nullptr)
                            nos->cauda = tmp;
                    }
                }
            }
        }
    } 
    else {        // Caso a lista estiver vazia adionar a palavra de uma vez na lista
        nos->cauda->prox = new Block<Tree*>;
        nos->cauda = nos->cauda->prox;
        nos->cauda->dado = raiz;
        nos->cauda->prox = nullptr;
    }
    nos->qtd++;
}

void createTreeFile(Tree *raiz) {
	std::deque<Tree*> deck;
    deck.push_back(raiz);
    std::fstream file;
    std::string nome;

    printf("\nQual o nome do arquivo onde a arvore sera guardada: ");
    std::cin >> nome;

	file.open(nome, std::ios::out);
    if(file.is_open()) {
        while(!deck.empty()) {
            Tree *t = deck.front();
            deck.pop_front();
            if(t->reg.size != 0) {
                for(int i=0; i<t->reg.size; i++)
                    file << t->reg.bits[i];
                file << "\n";
                file << t->reg.palavra;
                file << "\n";
            }
            if(t->esq != nullptr)
                deck.push_back(t->esq);
            if(t->dir != nullptr)
                deck.push_back(t->dir);
        }
    } else {
        printf("\nOcorreu um erro ao abrir o arquivo %s!", nome.c_str());
    }
	file.close();
}

void getTreeFromFile(std::deque<Tree*> *arvores) {
    Tree *t = CreateTree();
    Record r;
    std::string nome;

    printf("\nQual o nome do arquivo onde a arvore esta guardada: ");
    std::cin >> nome;

    r.palavra = " ";
    r.size = 0;
    insertTree(&t, r);
    arvores->push_back(t);

    std::fstream file;
    std::string sbits, palavra;
    bool bits[16];

    file.open(nome, std::ios::in);
    if(file.is_open()) {
        while(getline(file, sbits, '\n') && getline(file, palavra, '\n')) {
            int size =  static_cast<int>(sbits.size());
            for(int i=0; i<size; i++) {
                bits[i] = sbits[i] == '1' ? 1 : 0;
            }
            Tree* aux = CreateTree();
            r.bits = new bool[size];
            for(int i=0; i<size; i++) {
                r.bits[i] = bits[i];
            }
            r.size = size;
            r.palavra = palavra;
            insertTree(&aux, r);
            arvores->push_back(aux);
        }
        file.close();
    } else {
        printf("\nNao foi posiivel abrir o arquivo %s\n", nome.c_str());
        return;
    }
}

void makeHuffmanTree(std::deque<Tree*> *arvores, Tree **raiz) {
    *raiz = arvores->front();
    arvores->pop_front();

    Tree *aux;
    Tree **t;
    while(!arvores->empty()) {
        t = raiz;
        aux = arvores->front();
        arvores->pop_front();
        for(int i=0; i<aux->reg.size; i++) {
            if(aux->reg.bits[i]) {
                t = &(*t)->dir;
            } else {
                t = &(*t)->esq;
            }
        }
        *t = aux;
    }
}