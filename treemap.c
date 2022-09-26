#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * tree = (TreeMap *)malloc(sizeof(TreeMap));
  tree->lower_than=lower_than;
  if (lower_than==NULL) return NULL;
  return tree;
}



void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode * aux;
  TreeNode * newNode=createTreeNode(key,value);
  aux = tree->root;
  while (aux!=NULL){
    tree->current=aux;
    if (tree->lower_than(key,aux->pair->key)==1){
      aux=tree->current->left;
    }
    else if (tree->lower_than(aux->pair->key,key)==1){
      aux=tree->current->right;
    }
    else{
      return;
    }
  }
  newNode->parent=tree->current;
}

TreeNode * minimum(TreeNode * x){
  while (x->left != NULL){
    x=x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current=tree->root;
  TreeNode * aux = tree->current;
  while (aux != NULL){
    if (is_equal(tree,key,aux->pair->key)==1){
      return aux->pair;
      } 
    else if (tree->lower_than(aux->pair->key,key)==1){
      aux=tree->current->right;
    }
    else if (tree->lower_than(key,aux->pair->key)==1){
      aux=tree->current->left;
    }
    tree->current=aux;
  }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
