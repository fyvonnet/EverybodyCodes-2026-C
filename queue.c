#include <stdlib.h>
#include "queue.h"

Queue *queue_create()
{
        Queue *queue = malloc(sizeof(Queue));
        queue->head = NULL;
        return queue;
}

void queue_enqueue(Queue *queue, void *data)
{
        QueueNode *node = malloc(sizeof(QueueNode));
        node->data = data;
        node->next = NULL;

        if (queue->head == NULL)
                queue->head = queue->tail = node;
        else
                queue->tail = queue->tail->next = node;
}

void *queue_dequeue(Queue *queue)
{
        if (queue->head == NULL)
                return NULL;

        QueueNode *node = queue->head;
        void *data = node->data;

        queue->head = node->next;
        free(node);
        return data;
}

void *queue_peek(Queue *queue)
{
        if (queue->head == NULL)
                return NULL;

       return queue->head->data;
}

