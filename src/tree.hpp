#ifndef TREE_H 
#define TREE_H

#include "list.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <deque>

typedef struct Record Record;
typedef struct Tree Tree;

struct Record{
	std::string palavra;
    short int lenght;
    int value;
    float RP;
    bool* bits;
    short int size;
    short int max_size;
};

struct Tree{
	Record reg;
	Tree *esq, *dir;
};

Tree* CreateTree();
void insertTree(Tree **t, Record r);
void pesquisa(Tree **t, Tree **aux, Record r);

void removeTree(Tree **t, Record r);
void antecessor(Tree **t, Tree *aux);

void preordem(Tree *t);
void central(Tree *t);
void posordem(Tree *t);

int altura(Tree *raiz);

#endif