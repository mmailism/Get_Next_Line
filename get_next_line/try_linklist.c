#include <stdio.h>

#define true 1
#define false 0
typedef int boolean;
struct Node *new_node;
struct Node *head;
struct Node *curr;
struct Node *prev;

//เพิ่ม Node ใน linklist
void add(int newItem)
{
    if (head == NULL)
        new_node = createNode(newItem, NULL);
    else
        new_node = createNode(newItem, head);
    head = new_node;
}

// ค้นหาข้อมูลใน linklist
boolean searchItem(int item)
{
    curr = head;
    prev = NULL;
    boolean status = false;
    while (curr != NULL)
    {
        if (getItem(curr) == item)
        {
            status = true;
            break;
        }
        else
        {
            prev = curr
            curr = getNext(curr);
        }
    }
    return (status);
}

// ลบข้อมูลใน linklist
void deleteNode(int item)
{
    if (searchItem(item))
    {
        if (prev == NULL)
            head = getNext(curr);
        else
            setNext(prev, getNext(curr));
    }
    else
        printf("Not found item. \n");
}

// แทรก Node ใน linklist
void insert(int item_insert, int new_item)
{
    new_node = createNode(new_item, NULL)
    if (searchItem(item_insert))
    {
        if (prev == NULL)
        {
            setNext(new_node, curr);
            head = new_node;
        }
        else
        {
            setNext(new_node, curr);
            setNext(prev, new_node);
        }
    }
    else
    {
        if (head == NULL)
        {
            setNext(new_node, curr);
            head = new_node;
        }
        else if (curr == NULL)
            setNext(prev, new_node);
    }
}

// แสดงข้อมูลใน linklist
void showdata()
{
    curr = head;
    while (curr != head)
    {
        printf("%d", getItem(curr));
        curr = getNext(curr);
    }
    printf("\n");
}

void main()
{
    add(9);
    printf("add 9 : ");
    showdata();
    add(10);
    printf("add 10 : ");
    showdata();
    add(11);
    printf("add 11 : ");
    showdata();
    add(12);
    printf("add 12 : ");
    showdata();
    deleteNode(10);
    printf("delete 10 : ");
    showdata();
    deleteNode(12);
    printf("delete 12 : ");
    showdata();
    insert(11, 15);
    printf("insert 15 before 11 :");
    showdata();
    insert(11, 17);
    printf("insert 17 before 11 :");
    showdata();
    insert(18, 19);
    printf("insert 19 at last linklist :");
    showdata();
    scanf("%d");
}
