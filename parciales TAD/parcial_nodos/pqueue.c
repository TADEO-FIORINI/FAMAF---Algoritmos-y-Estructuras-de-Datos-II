#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node *front;
};

struct s_node
{
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    float priority = 0;
    priority = 0.5 * (average_grade/MAX_GRADE) + 0.5 * (approved_courses/TOTAL_COURSES);
    return priority;
}

static struct s_node *create_node(pqueue_elem e,
                                  float average_grade,
                                  unsigned int approved_courses)
{
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = calculate_priority(average_grade, approved_courses);
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q)
{
    bool b = true;
    if (q != NULL){
        if (!pqueue_is_empty(q)){
        struct s_node *previous = q->front;
        struct s_node *current = previous->next;
            while (current != NULL)
            {
                b = b && previous->priority >= current->priority;
                previous = current;
                current = current->next;
            }  
        }
    }
    else{
        b = false;
    }
    return b;
}

pqueue pqueue_empty(void)
{
    struct s_pqueue *q = malloc(sizeof(struct s_pqueue));
    assert(q!=NULL);
    q->size = 0;
    q->front = NULL;
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, float average_grade, unsigned int approved_courses)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e,average_grade,approved_courses); 
    if (q->front == NULL){
        q->front = new_node;
    }
    else{
        struct s_node *current = q->front;
        struct s_node *previous = NULL;
        while(current != NULL && new_node->priority <= current->priority){
            previous = current;
            current = current->next;
        }
        // el nuevo alumno tiene mas prioridad que el primero en la cola
        if (previous == NULL){
            new_node->next = q->front;
            q->front = new_node;
        }
        //caso general
        else{
            previous->next = new_node;
            new_node->next = current;
        }
    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    bool b = q->size == 0;
    return b;
}


pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q));
    assert(!pqueue_is_empty(q));
    pqueue_elem elem = q->front->elem;
    return elem;
}

float pqueue_peek_average_grade(pqueue q)
{
    assert(invrep(q));
    assert(!pqueue_is_empty(q));
    float average_grade = q->front->average_grade;
    return average_grade;
}

unsigned int pqueue_peek_approved_courses(pqueue q)
{
    assert(invrep(q));
    assert(!pqueue_is_empty(q));
    unsigned int approved_courses = q->front->approved_courses;
    return approved_courses;
}

float pqueue_peek_priority(pqueue q)
{
    assert(invrep(q));
    assert(!pqueue_is_empty(q));
    float priority = calculate_priority(q->front->average_grade, q->front->approved_courses);
    return priority;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    unsigned int size = q->size;
    return size;
}

pqueue pqueue_copy(pqueue q)
{
    assert(invrep(q));
    struct s_pqueue *copy = pqueue_empty();
    if (!pqueue_is_empty(q)){
        struct s_node *current = q->front;
        while (current != NULL){
            copy = pqueue_enqueue(copy,current->elem, current->average_grade,
                                 current->approved_courses);
            current = current->next;
        }
    }
    return copy;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q));
    if (q->front != NULL){
        struct s_node *killme = q->front;
        q->front = q->front->next;
        killme = destroy_node(killme);
        q->size--;
    }
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    if (q->front != NULL){
        struct s_node *node = q->front;
        while (node != NULL){
            struct s_node *killme = node;
            node = node->next;
            killme = destroy_node(killme); 
        }
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
