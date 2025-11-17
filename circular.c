#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// Macro for malloc
#define MALLOC(p, n, type) \
    p = (type *)malloc((n) * sizeof(type)); \
    if (p == NULL) { \
        printf("Memory Allocation Failed!\n"); \
        exit(1); \
    }

typedef struct {
    int *arr;
    int front, rear;
    int capacity;
} CircularQueue;

/* -------- Function Prototypes -------- */
void createQueue(CircularQueue *q, int size);
int isEmpty(CircularQueue *q);
int isFull(CircularQueue *q);
void resize(CircularQueue *q);
void insert(CircularQueue *q, int item);
int delete(CircularQueue *q);
void display(CircularQueue *q);

/* -------- Create Queue -------- */
void createQueue(CircularQueue *q, int size) {
    MALLOC(q->arr, size, int);
    q->capacity = size;
    q->front = q->rear = -1;
}

/* -------- Queue Empty -------- */
int isEmpty(CircularQueue *q) {
    return (q->front == -1);
}

/* -------- Queue Full -------- */
int isFull(CircularQueue *q) {
    return ((q->rear + 1) % q->capacity == q->front);
}

/* -------- Resize Queue (Double Size) -------- */
void resize(CircularQueue *q) {
    int newCapacity = q->capacity * 2;
    int *newArr;

    MALLOC(newArr, newCapacity, int);

    int i = q->front;
    int j = 0;

    while (i != q->rear) {
        i = (i + 1) % q->capacity;
        newArr[j++] = q->arr[i];
    }
    newArr[j++] = q->arr[q->rear];

    q->front = -1;
    q->rear = j - 1;
    q->capacity = newCapacity;

    free(q->arr);
    q->arr = newArr;

    printf("\nQueue resized to capacity: %d\n", newCapacity);
}

/* -------- Insert (Enqueue) -------- */
void insert(CircularQueue *q, int item) {
    if (isFull(q)) {
        resize(q);
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % q->capacity;
    }

    q->arr[q->rear] = item;
    printf("Inserted: %d\n", item);
}

/* -------- Delete (Dequeue) -------- */
int delete(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }

    int item = q->arr[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->capacity;
    }

    return item;
}

/* -------- Display Queue -------- */
void display(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Empty!\n");
        return;
    }

    printf("Queue contents: ");
    int i = q->front;

    while (i != q->rear) {
        printf("%d ", q->arr[i]);
        i = (i + 1) % q->capacity;
    }
    printf("%d\n", q->arr[q->rear]);
}

/* -------- Main Function -------- */
int main() {
    CircularQueue q;
    int size, choice, item;

    printf("Enter initial size of circular queue: ");
    scanf("%d", &size);

    createQueue(&q, size);

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item: ");
                scanf("%d", &item);
                insert(&q, item);
                break;

            case 2:
                item = delete(&q);
                if (item != -1)
                    printf("Deleted: %d\n", item);
                break;

            case 3:
                display(&q);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
