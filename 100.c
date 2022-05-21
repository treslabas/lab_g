#include <libc.h>
#include "stdlib.h"
#include "stdio.h"

struct edge {
    int to;
    int weight;
    struct edge *next;
};

struct edge *edges[100];

void add_edge2(int from, int to, int weight) {
    struct edge *e = malloc(sizeof(struct edge));
    e->to = to;
    e->weight = weight;
    e->next = edges[from];
    edges[from] = e;
}


void add_edge(int from, int to, int weight) {
    struct edge *e = malloc(sizeof(struct edge));
    e->to = to;
    e->weight = weight;
    e->next = edges[from];
    edges[from] = e;
    add_edge2(to, from, weight);
}

void init() {
    add_edge(1, 2, 2);
    add_edge(2, 3, 4);
    add_edge(3, 4, 2);
    add_edge(4, 7, 5);
    add_edge(7, 8, 2);
    add_edge(8, 1, 5);
    add_edge(1, 6, 3);
    add_edge(2, 6, 1);
    add_edge(3, 6, 3);
    add_edge(4, 6, 6);
    add_edge(6, 6, 1);
    add_edge(8, 6, 3);
    add_edge(4, 5, 1);
    add_edge(4, 3, 2);
    add_edge(4, 7, 5);
}

int buffer[100][100];

int main() {
    init();
    for (int i = 0; i < 1000; ++i) {
        printf("Операции:\n");
        printf("1) Удалить вершину: 7\n");
        printf("2) Удалить вес 2\n");
        printf("3) Вывести матрицу смежности\n");
        printf("4) Выход\n");
        int choice;
        scanf("%d", &choice);
        if(choice == 1) {
            edges[7] = NULL;
            printf("Вершина удалена\n");
        }
        if(choice == 2) {
            for (int j = 0; j < 100; ++j) {
                if(edges[j] != NULL) {
                    if(edges[j]->weight == 2) {
                        edges[j] = edges[j]->next;
                    }
                    struct edge *e = edges[j];
                    while(e->next != NULL) {
                        if(e->next->weight == 2) {
                            e->next = e->next->next;
                            break;
                        }
                        e = e->next;
                    }
                }
            }
            printf("Вес удален\n");
        }
        if (choice == 3) {
            memset(buffer, 0, sizeof(buffer));
            for (int j = 0; j < 100; ++j) {
                if(edges[j] != NULL) {
                    struct edge *e = edges[j];
                    while(e != NULL) {
                        buffer[j][e->to] = e->weight;
                        e = e->next;
                    }
                }
            }
            printf("   ");
            for (int j = 0; j < 10; ++j) {
                printf("%d ", j);
            }
            printf("\n");
            for (int j = 0; j < 10; ++j) {
                printf("%d |", j);
                for (int k = 0; k < 10; ++k) {
                    printf("%d ", buffer[j][k]);
                }
                printf("\n");
            }
        }
        if(choice == 4) {
            return 0;
        }
    }
}
