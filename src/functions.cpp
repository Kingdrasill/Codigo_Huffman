#include "functions.hpp"

void createWordRank(List<Record> *rank, Documento *doc) {
	Block<Palavras> *percorre;
    Block<Word> *palavras;
    Record r;

    percorre = doc->documento.cabeca;
    while(percorre->prox!=nullptr)
    {
        palavras = percorre->prox->dado.listPal.cabeca;
        while(palavras->prox!=nullptr)
        {
            r.palavra = palavras->prox->dado.palavra;
            r.lenght = palavras->prox->dado.lenght;
            r.value = palavras->prox->dado.value;
            r.RP = palavras->prox->dado.RP + (palavras->prox->dado.RP / palavras->prox->dado.palavra[0]);
            
            insertListaRankeamento(rank, r);
            palavras = palavras->prox;
        }
        percorre=percorre->prox;
    }
}

void insertListaRankeamento(List<Record> *lista, Record r) {

    if(lista->cabeca != lista->cauda) 
    {
        Block<Record>* tmp = new Block<Record>;
        Block<Record>* aux; 

        tmp->dado = r;
        aux = lista->cabeca;
        while (aux->prox != nullptr && aux->prox->dado.RP < r.RP) {
            aux = aux->prox;
        }
        
        if(aux->prox == nullptr)
        {
            tmp->prox = aux->prox;
            aux->prox = tmp;
            lista->cauda = tmp;
        }
        else {
            if(aux->prox->dado.RP > r.RP) 
            {
                tmp->prox = aux->prox;
                aux->prox = tmp;
                if(tmp->prox == nullptr)
                    lista->cauda = tmp;
            } else {
                while(aux->prox != nullptr && aux->prox->dado.RP == r.RP && aux->prox->dado.lenght > r.lenght) {
                    aux = aux->prox;
                }
                if(aux->prox == nullptr) {
                    tmp->prox = aux->prox;
                    aux->prox = tmp;
                    lista->cauda = tmp;
                } else {
                    if(aux->prox->dado.lenght < r.lenght) {
                        tmp->prox = aux->prox;
                        aux->prox = tmp;
                        if(tmp->prox == nullptr)
                            lista->cauda = tmp;
                    } else {
                        while(aux->prox != nullptr && aux->prox->dado.RP == r.RP && aux->prox->dado.lenght == r.lenght && aux->prox->dado.value > r.value) {
                            aux = aux->prox;
                        }
                        tmp->prox = aux->prox;
                        aux->prox = tmp;
                        if(tmp->prox == nullptr)
                            lista->cauda = tmp;
                    }
                }
            }
        }
    } 
    else { 
        lista->cauda->prox = new Block<Record>;
        lista->cauda = lista->cauda->prox;
        lista->cauda->dado = r;
        lista->cauda->prox = nullptr;
    }
    lista->qtd++;
}

void createListNos(List<Tree*> *nos, List<Record> *rank) {
    Block<Record> *percorre;

    percorre = rank->cabeca;
    while(percorre->prox!=nullptr)
    {
        insertListNos(nos, percorre->prox->dado);
        nos->qtd++;
        percorre = percorre->prox;
    }
}

void insertListNos(List<Tree*> *lista, Record r) {
    Tree *t = CreateTree();
    insertTree(&t, r);

    lista->cauda->prox = new Block<Tree*>;
    lista->cauda = lista->cauda->prox;
    lista->cauda->dado = t;
    lista->cauda->prox = nullptr;
}

void identificadores(Tree** t, std::deque<bool> array, Documento *doc) {
    std::deque<bool> copy = array;
    if(*t != nullptr) {
        (*t)->reg.size = static_cast<int>(copy.size());
        if(copy.size() > 0) {
            (*t)->reg.bits = new bool[(*t)->reg.size];
            for(int i=0; i<(*t)->reg.size; i++) {
                (*t)->reg.bits[i] = copy.front();
                copy.pop_front();
            }
        }
        if((*t)->reg.palavra != " ") {
            setTreeLPTamanho(&doc->documento, (*t)->reg.palavra, *t);
        }
        array.push_back(false);
        identificadores(&(*t)->esq, array, doc);
        array.pop_back();
        array.push_back(true);
        identificadores(&(*t)->dir, array, doc);
    }
}

void compressFile(Documento *doc, std::string nome_text) {
    std::fstream texto, compressed;
    int valor;
    std::string palavras,linha, nome;
    Word w;

    printf("\nQual o nome do arquivo onde sera comprimido o texto(com extensão, sendo extensão para arquivo binário com .dat ou .bin): ");
	std::cin >> nome;

    compressed.open(nome, std::ios::out|std::ios::binary);
    if(compressed.is_open()) {
        texto.open(nome_text);
        if(texto.is_open()) {
            while (getline(texto,linha,'\n')) {
                linha.append(" ");
                std::stringstream X(linha);
                while (getline(X, palavras, ' ')){
                    while(palavras.back() == ',' || palavras.back() =='.' || palavras.back() =='!' || palavras.back() =='?' || palavras.back() ==';' || palavras.back() ==':' || palavras.back() ==')' || palavras.back() =='-' || palavras.back() =='\'' || palavras.back() =='\"' || palavras.back() =='/')
                        palavras.pop_back();
                    while(palavras.front()=='('||palavras.front()=='-'||palavras.front()=='\''||palavras.front()=='\"')
                        palavras.erase(palavras.begin());
                    valor=palavras[1];
                    if(palavras.front()==-61 && valor>=-128 && valor<=-99)
                        palavras[1]=palavras[1]+32;
                    std::transform(palavras.begin(), palavras.end(), palavras.begin(),[](unsigned char c){ return std::tolower(c); });
                    if (palavras.size()>0) {
                        w = searchWordLPTamanho(&doc->documento, palavras);
                        std::string sc = boolToChar(w.t->reg.bits, w.t->reg.size);
                        char c[2];
                        strcpy(c, sc.c_str());
                        compressed.write(c, 2);
                    }
                }
            }
        } else {
            printf("\nOcorru um erro ao abrir o arquivo %s!\n", nome_text.c_str());
        }
        texto.close();
    } else {
        printf("\nOcorreu um erro ao abrir o arquivo %s!\n", nome.c_str());
    }
    compressed.close();
}

void decompressFile(Tree* raiz) {
    short int max_s = raiz->reg.max_size;
    std::fstream compressed, decompressed;
    std::string nome_com, nome_dec;

    printf("\nQual o nome do arquivo comprimido(com extensão): ");
	std::cin >> nome_com;

    printf("\nQual o nome do arquivo onde sera descomprimido(com extensão): ");
	std::cin >> nome_dec;

    compressed.open(nome_com, std::ios::in|std::ios::binary);
    if(compressed.is_open()) {
        decompressed.open(nome_dec, std::ios::out);
        if(decompressed.is_open()) {
            bool *b =  new bool[max_s];
            char *c = new char[2];
            while(compressed.read(c, 2)) {
                Tree* t = raiz;
                charToBool(c, max_s, b);
                for(int i = 0; i < max_s; i++) {
                    if (b[i]) {
                        t = t->dir;
                    } else {
                        t = t->esq;
                    }
                    if(t->reg.palavra != " ")
                        break;
                }
                decompressed << t->reg.palavra << " ";
            }
        } else {
            printf("\nOcorru um erro ao abrir o arquivo %s!\n", nome_dec.c_str());
        }
        decompressed.close();
    } else {
        printf("\nOcorreu um erro ao abrir o arquivo %s!\n", nome_com.c_str());
    }
    compressed.close();
}

std::string boolToChar(bool *bools, short int s) {
    unsigned char c[2] = {0,0};
	for(int i = 7; i >= 0; i--)
       	if (bools[i])
           	c[0] += pow(2,i);
    if(s>=9) {
        for(int i = s-1; i >= 8; i--)
            if(bools[i])
                c[1] += pow(2,i-8);
    }
    return std::string(reinterpret_cast<char*>(c));
}

void charToBool(char *c, short int s, bool *b) {
    unsigned char c0 = c[0], c1 = c[1];
    for(int i = 7; i >= 0; i--) {
       	if (c0 >= pow(2,i)) {
           	c0 -= pow(2,i);
            b[i] = 1;
        } else {
            b[i] = 0;
        }
    }
    if(s>8) {
        for(int i = s; i >= 8; i--) {
            if(c1 >= pow(2,i-8)) {
                c1 -= pow(2,i-8);
                b[i] = 1;
            } else {
                b[i] = 0;
            }
        }
    }
}
