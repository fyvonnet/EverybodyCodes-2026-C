#pragma once

struct QueueNode {
        void *data;
        struct QueueNode *next;
};

typedef struct QueueNode QueueNode;

typedef struct { QueueNode *head, *tail; } Queue;


Queue *queue_create();
void queue_enqueue(Queue *queue, void *data);
void *queue_dequeue(Queue *queue);
void *queue_peek(Queue *queue);

