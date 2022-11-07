/*to create a database of 200 students
 *to store name,roll no and class of each student
 *add, access(read and display), del, update, num of students at present*/

//to-do: 
//      1. Modularize Code 
//      2. To store data to a file
//      3. To reuse the blanks in pointer array
//      4. How to dynamically change pointer array size ?


#include<stdio.h>
#include<stdlib.h>



struct Student
{
    char name[20]; // 1 byte * 20 = 20 bytes
    int roll_no; // 4 bytes
    int class; // 4 bytes
};// 1 Student memory = 28 bytes



int addstudent(struct Student *ptr)
{
    printf("Enter Name:\n");
    fflush(stdin);
    scanf("%s", ptr->name);
    printf("Enter Roll Number:\n");
    scanf("%d", &ptr->roll_no);
    printf("Enter Class:\n");
    scanf("%d", &ptr->class);
    return 1;
}



int main(int argc, char** argv)
{
    int i = 0, j = 0, choice = 0, id;
    int found = 0;
    struct Student *ptr;
    struct Student *parr[10];
    
    // char a ='10';
    // char *b = &a;
    // printf("a = %d, b = %d, *b = %d\n", sizeof(a), sizeof(b), sizeof(*b));
    // printf("%d-%d-%d\n",sizeof(sarr),sizeof(parr),sizeof(ptr));
    // printf("%d-%d-%d",sizeof(long),sizeof(int), sizeof(int*));
    // exit(0);
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
        printf("Your Choice : %d\n", choice);
        switch(choice)
        {
            case 1:
                ptr = (struct Student *)malloc(sizeof(struct Student));
                parr[i++] = ptr;
                //printf("Pointer address: %p\n", ptr);
                if(addstudent(ptr))
                {
                    printf("Record Added Succesfully!!");
                }

                break;
            case 2:
                for(j=0;j<i;j++)
                {
                    if(parr[j] == NULL) continue;
                    printf("%s\t%d\t%d\n", parr[j]->name, parr[j]->roll_no, parr[j]->class);
                }
                break;
            case 3:
                printf("Enter Roll No:\n");
                scanf("%d", &id);
                found = 0;
                for(j=0;j<i;j++)
                {
                    //if(parr[j] == NULL) continue;
                    if(parr[j] != NULL && parr[j]->roll_no == id)
                    {
                        printf("%s\t%d\t%d\n", parr[j]->name, parr[j]->roll_no, parr[j]->class);
                        found = 1;
                        break;
                    }
                }
                if(!found)
                {
                    printf("\nRecord NOT FOUND\n\n Enter a Valid Number\n");
                }
                break;
            case 4:
                printf("Enter Roll No:\n");
                scanf("%d", &id);
                found = 0;
                for(j=0;j<i;j++)
                {
                    if(parr[j] != NULL && parr[j]->roll_no == id)
                    {
                        free(parr[j]);
                        parr[j] = NULL;
                        found = 1;
                        break;
                    }
                }
                if(!found)
                {
                    printf("\nRecord NOT FOUND\n\n Enter a Valid Number\n");
                }
                break;
            case 5: 
                printf("Enter Roll No:\n");
                scanf("%d", &id);
                found = 0;
                for(j=0;j<i;j++)
                {
                    if(parr[j] != NULL && parr[j]->roll_no == id)
                    {
                        printf("Existing record details:\n");
                        printf("\n%s\t%d\t%d\n", parr[j]->name, parr[j]->roll_no, parr[j]->class);
                        if(addstudent(parr[j]))
                        {
                            printf("\nUpdated Successfully!!!\n");
                        }
                    }
                }
                if(!found)
                {
                    printf("\nRecord NOT FOUND\n\n Enter a Valid Number\n");
                }
            case 6: return -1;
            default: 
                printf("Choice does not exist\nEnter Correct Choice\n");
                break;
        }
    }
}