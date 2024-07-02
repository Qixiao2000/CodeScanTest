#include <stdio.h>  
#include <stdlib.h>  
  
// 定义双向链表的节点  
typedef struct Node {  
    int data;  
    struct Node* prev;  
    struct Node* next;  
} Node;  
  
// 创建新节点  
Node* createNode(int data) {  
    Node* newNode = (Node*)malloc(sizeof(Node));  
    if (!newNode) {  
        printf("Memory allocation failed.\n");  
        exit(1);  
    }  
    newNode->data = data;  
    newNode->prev = NULL;  
    newNode->next = NULL;  
    return newNode;  
}  
  
// 向双向链表的末尾添加节点  
void appendNode(Node** head, int data) {  
    Node* newNode = createNode(data);  
    if (*head == NULL) {  
        *head = newNode;  
        return;  
    }  
    Node* last = *head;  
    while (last->next != NULL) {  
        last = last->next;  
    }  
    last->next = newNode;  
    newNode->prev = last;  
}  
  
// 在双向链表的指定位置前插入节点  
void insertNode(Node** head, int position, int data) {  
    if (position <= 0) {  
        printf("Invalid position\n");  
        return;  
    }  
    Node* newNode = createNode(data);  
    Node* current = *head;  
    int count = 0;  
    while (current != NULL && count < position - 1) {  
        current = current->next;  
        count++;  
    }  
    if (current == NULL) {  
        printf("Position out of bounds\n");  
        free(newNode);  
        return;  
    }  
    newNode->next = current->next;  
    if (current->next != NULL) {  
        current->next->prev = newNode;  
    }  
    newNode->prev = current;  
    current->next = newNode;  
}  
  
// 删除双向链表中的节点  
void deleteNode(Node** head, int key) {  
    Node* temp = *head, *prev = NULL;  
    if (temp != NULL && temp->data == key) {  
        *head = temp->next; // 改变头指针  
        if ((*head) != NULL)  
            (*head)->prev = NULL;  
        free(temp);  
        return;  
    }  
  
    while (temp != NULL && temp->data != key) {  
        prev = temp;  
        temp = temp->next;  
    }  
  
    if (temp == NULL) return;  
  
    prev->next = temp->next;  
  
    if (temp->next != NULL)  
        temp->next->prev = prev;  
  
    free(temp);  
}  
  
// 修改双向链表中指定位置的节点数据  
void updateNode(Node* head, int oldData, int newData, int* position) {  
    Node* temp = head;  
    int count = 1;  
    while (temp != NULL) {  
        if (temp->data == oldData) {  
            temp->data = newData;  
            *position = count;  
            return;  
        }  
        temp = temp->next;  
        count++;  
    }  
    *position = -1; // 如果没有找到，返回-1  
}  
  
// 打印双向链表  
void printList(Node* node) {  
    while (node != NULL) {  
        printf("%d ", node->data);  
        node = node->next;  
    }  
    printf("\n");  
}  
  
// 主函数  
int main() {  
    Node* head = NULL;  
    appendNode(&head, 1);  
    appendNode(&head, 2);  
    appendNode(&head, 3);  
    printf("Original list: ");  
    printList(head);  
  
    insertNode(&head, 2, 2.5); // 注意这里为了简单起见，我们插入了一个int值，但在实际中可能需要转换  
    printf("After inserting 2.5 at position 2: ");  
    printList(head);  
  
    int pos;  
    updateNode(head, 2, 99, &pos);  
    printf("After updating 2 to 99 (position %d): ", pos);
    printList(head);  
  
    // 删除节点  
    deleteNode(&head, 99); // 假设我们删除了新值99的节点  
    printf("After deleting 99: ");  
    printList(head);  
  
    // 释放链表内存（这是一个好习惯，虽然在这个简单示例中可能没有做到彻底）  
    while (head != NULL) {  
        Node* temp = head;  
        head = head->next;  
        free(temp);  
    }  
  
    return 0;  
}