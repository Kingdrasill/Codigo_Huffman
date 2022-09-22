#include "documento.hpp"

void pegarDocumento(Documento *doc, std::string nome_text){
    List<Palavras> lPal;
    std::fstream myFile;
    int valor;
    std::string palavras,linha;

    doc->nome = nome_text;
    doc->qtd = 0;

	FLVazia(&lPal);
    myFile.open(doc->nome);
    if(myFile.is_open()) {
        while (getline(myFile,linha,'\n')) {
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
                    insertLPTamanho(&lPal,palavras);
                }
            }
        }
    } else {
        printf("\nOcorreu um erro ao abrir o arquivo %s!", nome_text.c_str());
    }
    doc->documento = lPal;
    doc->qtd = doc->documento.qtd;
    myFile.close();
}

void normalizeRP(Documento *doc) {
    float maxRP = findMaxRP(doc), minRP = findMinRP(doc); 
    Block<Palavras> *percorre;
    Block<Word> *palavras;

    percorre = doc->documento.cabeca;
    while(percorre->prox!=nullptr)
    {
        palavras=percorre->prox->dado.listPal.cabeca;
        while(palavras->prox!=nullptr)
        {
            palavras->prox->dado.RP = palavras->prox->dado.RP / (maxRP - minRP);
            palavras = palavras->prox;
        }
        percorre=percorre->prox;
    }
}

float findMaxRP(Documento *doc) {
    float max;
    bool first = true;

    Block<Palavras> *percorre;
    Block<Word> *palavras;

    percorre = doc->documento.cabeca;
    while(percorre->prox!=nullptr)
    {
        palavras=percorre->prox->dado.listPal.cabeca;
        while(palavras->prox!=nullptr)
        {
            if(!first) {
                if (max < palavras->prox->dado.RP)
                    max = palavras->prox->dado.RP;
            } else {
                first = false;
                max = palavras->prox->dado.RP;
            }
            palavras = palavras->prox;
        }
        percorre=percorre->prox;
    }

    return max;
}

float findMinRP(Documento *doc) {
    float min;
    bool first = true;

    Block<Palavras> *percorre;
    Block<Word> *palavras;

    percorre = doc->documento.cabeca;
    while(percorre->prox!=nullptr)
    {
        palavras=percorre->prox->dado.listPal.cabeca;
        while(palavras->prox!=nullptr)
        {
            if(!first) {
                if (min > palavras->prox->dado.RP)
                    min = palavras->prox->dado.RP;
            } else {
                first = false;
                min = palavras->prox->dado.RP;
            }
            palavras = palavras->prox;
        }
        percorre=percorre->prox;
    }

    return min;
}
 