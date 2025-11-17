#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int key;
}element;

struct stack{
    element data;
    struct stack *link;
};
typedef struct stack * strptr;
strptr top=NULL;

int isEmpty(){
    return top==NULL;
}

void push(element item){
    strptr temp;
    temp=(strptr)malloc(sizeof(struct stack));
    temp->data=item;
    temp->link=top;
    top=temp;
}

element pop(){
    strptr temp=top;
    element item=top->data;
    top=top->link;
    free(temp);
    return item;
}
void display() {
    strptr temp = top;
    if (temp == NULL) {
        printf("Stack is empty!");
        return;
    }
    while (temp != NULL) {      // ✔ CORRECT
        printf("  %d  ", temp->data.key);
        temp = temp->link;
    }
}


int main(){
    element item;
    int choice;

    while (1) {
        printf("\n\n--- STACK MENU ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter element to push: ");
            scanf("%d", &item.key);
            push(item);
            break;

        case 2:
            if (isEmpty())
                printf("\nStack Underflow! Cannot pop.\n");
            else {
                item = pop();
                printf("\nPopped element: %d\n", item.key);
            }
            break;

        case 3:
            display();
            break;

        case 4:
            exit(0);

        default:
            printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;

}