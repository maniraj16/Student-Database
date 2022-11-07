/*to create a database of 200 students
 *to store name,roll no and class of each student
 *add, access(read and display), del, update, num of students at present*/

//to-do: 
//      1. Modularize Code 
//      2. To store data to a file
//      3. To reuse the blanks in pointer array
//      4. How to dynamically change pointer array size ? --Done
//      5. To arrange the records in order of roll numbers.
//      6. Doubly linked list.


#include<stdio.h>
#include<stdlib.h>

struct Student *ptr;
struct Student *pptr;
struct Student *head;
struct Student *tail;

struct Student
{
    char name[20]; // 1 byte * 20 = 20 bytes
    int roll_no; // 4 bytes
    int class; // 4 bytes
    struct Student *next; // 8 bytes
    struct Student *prev; // 8 bytes
};// 1 Student memory = 44 bytes


struct Student* std_address(int id)
{
    pptr = head;
    while(pptr != NULL)
    {
        if(pptr->roll_no == id)
        {
            return pptr;
        }
        pptr = pptr->next;
    }
    return 0;
}

//left->current->right
//left->right->current

//left[next]->current
//current[next]->right

//current[prev]->left
//right[prev]->current

//temp = right[next]

//left[next] = right
//right[next] = current
//current[next] = temp

//temp[prev] = current
//current[prev] = right
//right[prev]->left

void swapnodes(struct Student *right, struct Student *curr)
{
    struct Student *left;
    struct Student *temp;

    if(curr == head && right == tail)
    {
        head = right;
        tail = curr;

        curr->prev = curr->next;
        right->next = right->prev;
        right->prev = NULL;
        curr->next = NULL;
    }
    else if(curr == head)
    {
        temp = right->next;
        head = right;

        right->next = curr;
        curr->next = temp;
        temp->prev = curr;
        curr->prev = right;
        right->prev = NULL;
    }
    else if(right == tail)
    {
        left = curr->prev;
        tail = curr;

        left->next = right;
        right->next = curr;
        curr->next = NULL;
        curr->prev = right;
        right->prev = left;
    }
    else
    {
        left = curr->prev;
        temp = right->next;

        left->next = right;
        right->next = curr;
        curr->next = temp;
        temp->prev = curr;
        curr->prev = right;
        right->prev = left;
    }
}



void sort()
{
    struct Student *rptr;
    struct Student *kptr;

    pptr = head;
    while(pptr != NULL)
    {
        rptr = head;
        while(rptr != NULL && rptr->next != NULL)
        {
            kptr = rptr;
            if(kptr->roll_no > kptr->next->roll_no)
            {
                swapnodes(kptr->next, kptr);
            }
            rptr = rptr->next;
        }
        pptr = pptr->next;
    }
}


int add_std(struct Student *ptr)
{
    printf("\n\n*** Enter Details ***\n\n");
    printf("Enter Name:\n");
    fflush(stdin);
    scanf("%s", ptr->name);
    printf("Enter Roll Number:\n");
    scanf("%d", &ptr->roll_no);
    printf("Enter Class:\n");
    scanf("%d", &ptr->class);
    ptr->prev = tail;
    ptr->next = NULL;
    tail = ptr;
    return 1;
}


int main(int argc, char** argv)
{
    int i = 0, j = 0, choice = 0, id;
    head = NULL;
    tail = NULL;
    while(choice!=6)
    {
        printf("\n\n1. Add New Student Record\n");
        printf("2. View Details of an All Existing Student Records\n");
        printf("3. View Details of a single Existing Student Record\n");
        printf("4. Delete a student record\n");
        printf("5. Update record\n");
        printf("6. Exit\n");
        choice = 0;
        printf("\n\nEnter Choice:\n");
        fflush(stdin);
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                ptr = (struct Student *)malloc(sizeof(struct Student));
                if(head == NULL)
                    head = ptr;
                if(tail != NULL)
                    tail->next = ptr;
                // printf("%x, %x", head, tail);
                if(add_std(ptr))
                {
                    printf("\n*** Record Added Successfully!! ***\n");
                }
                break;
            case 2:
                if(head == NULL)
                    printf("\n\n*** NO RECORDS AVAILABLE ***\n\n");
                else
                {
                    sort();
                    pptr = head;
                    printf("\nNAME\t\t\tROLL NO\t\t\tCLASS\n");
                    while(pptr != NULL)
                    {
                        printf("%s\t\t\t%d\t\t\t%d\n", pptr->name, pptr->roll_no, pptr->class);
                        pptr = pptr->next;
                    }
                }
                break;
            case 3:
                printf("\n\nEnter Roll Number:\n");
                scanf("%d", &id);
                if(head == NULL)
                {
                    printf("\n\n*** NO RECORDS AVAILABLE ***\n");
                    break;
                }
                else
                {
                    pptr = std_address(id);
                    if(pptr == 0)
                        printf("\nRecord not Found\nEnter correct Roll Number\n");
                    else
                    {
                        printf("\nNAME\t\t\tROLL NO\t\t\tCLASS\n");
                        printf("%s\t\t\t%d\t\t\t%d\n", pptr->name, pptr->roll_no, pptr->class);
                    }
                }
                break;
            case 4:
                if(head == NULL)
                {
                    printf("\n*** NO RECORDS AVAILABLE ***\n\n");
                    break;
                }
                printf("Enter Roll No:\n");
                scanf("%d", &id);
                    pptr = std_address(id);
                if(pptr == 0)
                    printf("\nRecord not Found\nEnter correct Roll Number\n");
                else
                {
                    if (pptr == tail && pptr == head)
                    {
                        free(pptr);
                        head = NULL;
                        tail = NULL;
                    }
                    else if (pptr == tail)
                    {
                        pptr->prev->next = NULL;
                        tail = pptr->prev;
                        free(pptr);
                    }
                    else if(pptr == head)
                    {
                        pptr->next->prev = NULL;
                        head = pptr->next;
                        free(pptr);
                    }
                    else
                    {
                        pptr->prev->next = pptr->next;
                        pptr->next->prev = pptr->prev;
                        free(pptr);
                    }
                    printf("\n\n*** RECORD DELETED SUCCESSFULLY ***\n");
                }
                break;
            case 5:
                if(head == NULL)
                {
                    printf("\n\n*** NO RECORDS AVAILABLE ***\n");
                    break;
                }
                printf("Enter Roll No:\n");
                scanf("%d", &id);
                pptr = std_address(id);
                if(pptr == 0)
                    printf("\nRecord not Found\nEnter correct Roll Number\n");
                else
                {
                    printf("\nExisting Student Record:\n\nNAME\t\t\tROLL NO\t\t\tCLASS\n");
                    printf("%s\t\t\t%d\t\t\t%d\n\n", pptr->name, pptr->roll_no, pptr->class);
                    if(add_std(ptr))
                    {
                        printf("\n\nRecord Updated Successfully!!");
                    }
                }
                break;
            case 6: exit(0);
            default: 
                printf("\n\nChoice does not exist\nEnter Correct Choice\n");
                break;
        }
    }
}