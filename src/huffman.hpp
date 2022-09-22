#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "tree.hpp"

Tree* dequeueListNos(List<Tree*> *lista);
bool isEmpty(List<Tree*> *lista);
void createHuffmanTree(List<Tree*> *nos);
void insertHuffmanForest(List<Tree*> *nos, Tree** no1, Tree** no2);
void createTreeFile(Tree *raiz);
void getTreeFromFile(std::deque<Tree*> *arvores);
void makeHuffmanTree(std::deque<Tree*> *arvores, Tree **raiz);
void addToHuffmanTree(Tree **raiz, Tree **add, int pointer);

#endif