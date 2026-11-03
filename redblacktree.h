#pragma once

typedef enum { NODE_COLOR_RED, NODE_COLOR_BLACK } RedblacktreeNodeColor;

struct redblacktree_node {
    struct redblacktree_node *left, *right, *p;
    RedblacktreeNodeColor color;
    void *data;
};

typedef struct redblacktree_node RedblacktreeNode;

typedef struct {
    struct redblacktree_node *root, *nil;
    int nodecount;
    int (*compar)(const void*, const void*);
} RedBlackTree;

RedBlackTree *redblacktree_init(int (*compar)(const void*, const void*));
void *redblacktree_query(RedBlackTree *T, void *data);
void redblacktree_inorder(RedBlackTree *T, void (*func)(void *, void *), void *ptr);
int redblacktree_nodecount(RedBlackTree *T);
void *redblacktree_pop_leftmost(RedBlackTree *T);
void *redblacktree_delete(RedBlackTree *T, void *data);
void *redblacktree_insert(RedBlackTree *T, void *data);
void *redblacktree_insert_or_free(RedBlackTree *T, void *data);

