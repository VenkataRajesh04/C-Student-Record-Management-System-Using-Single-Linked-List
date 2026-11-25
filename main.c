#include "header.h"

int main(void)
{
    SLL *headptr = NULL;
    char op;

    while (1)
    {
        printf("\n******** STUDENT RECORD MENU ********\n");
        printf("a/A : Add new record\n");
        printf("d/D : Delete a record\n");
        printf("s/S : Show the list\n");
        printf("m/M : Modify a record\n");
        printf("v/V : Save records\n");
        printf("e/E : Exit\n");
        printf("t/T : Sort the list\n");
        printf("l/L : Delete all the records\n");
        printf("r/R : Reverse the list\n");
        printf("Enter your choice: ");

        if (scanf(" %c", &op) != 1)
            break;

        switch (op)
        {
            case 'a':
            case 'A':
                add_record(&headptr);
                break;

            case 'd':
            case 'D':
                delete_record(&headptr);
                break;

            case 's':
            case 'S':
                show_list(headptr);
                break;

            case 'm':
            case 'M':
                modify_record(headptr);
                break;

            case 'v':
            case 'V':
                save_record(headptr);
                break;

            case 't':
            case 'T':
                sort_list(headptr);
                break;

            case 'l':
            case 'L':
                delete_all(&headptr);
                break;

            case 'r':
            case 'R':
                reverse_list(&headptr);
                break;

            case 'e':
            case 'E':
                delete_all(&headptr);
                return 0;

            default:
                printf("Unknown choice\n");
        }
    }

    delete_all(&headptr);
    return 0;
}

void add_record(SLL **ptr)
{
    SLL *newnode = malloc(sizeof(*newnode));

    if (newnode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter roll number, name and percentage: ");
    if (scanf("%d %29s %f", &newnode->rollno,
              newnode->name, &newnode->percentage) != 3)
    {
        printf("Invalid input\n");
        free(newnode);
        return;
    }

    newnode->next = *ptr;
    *ptr = newnode;
    printf("Record added successfully\n");
}

void show_list(SLL *ptr)
{
    if (ptr == NULL)
    {
        printf("No data found\n");
        return;
    }

    printf("-----------------------------------------------------------\n");
    printf("%-12s %-30s %s\n", "Roll No.", "Name", "Percentage");
    printf("-----------------------------------------------------------\n");

    while (ptr != NULL)
    {
        printf("%-12d %-30s %.2f\n",
               ptr->rollno, ptr->name, ptr->percentage);
        ptr = ptr->next;
    }

    printf("-----------------------------------------------------------\n");
}

void delete_record(SLL **ptr)
{
    char ch;

    if (*ptr == NULL)
    {
        printf("No records found\n");
        return;
    }

    printf("R/r: Delete by roll number\n");
    printf("N/n: Delete by name\n");
    printf("Enter choice: ");

    if (scanf(" %c", &ch) != 1)
        return;

    if (ch == 'R' || ch == 'r')
    {
        int rollno;
        printf("Enter roll number to delete: ");
        if (scanf("%d", &rollno) != 1)
            return;

        SLL *del = *ptr;
        SLL *prev = NULL;

        while (del != NULL)
        {
            if (del->rollno == rollno)
            {
                if (prev == NULL)
                    *ptr = del->next;
                else
                    prev->next = del->next;

                free(del);
                printf("Record deleted\n");
                return;
            }

            prev = del;
            del = del->next;
        }

        printf("Roll number not found\n");
    }
    else if (ch == 'N' || ch == 'n')
    {
        char name[30];
        int count = 0;
        int rollno = 0;

        printf("Enter name to delete: ");
        if (scanf("%29s", name) != 1)
            return;

        for (SLL *temp = *ptr; temp != NULL; temp = temp->next)
        {
            if (strcmp(temp->name, name) == 0)
            {
                count++;
                rollno = temp->rollno;
            }
        }

        if (count == 0)
        {
            printf("Name not found\n");
            return;
        }

        if (count > 1)
        {
            printf("Multiple records found:\n");
            for (SLL *temp = *ptr; temp != NULL; temp = temp->next)
            {
                if (strcmp(temp->name, name) == 0)
                    printf("%d %s %.2f\n",
                           temp->rollno, temp->name, temp->percentage);
            }

            printf("Enter roll number of the record to delete: ");
            if (scanf("%d", &rollno) != 1)
                return;
        }

        SLL *del = *ptr;
        SLL *prev = NULL;

        while (del != NULL)
        {
            if (del->rollno == rollno &&
                strcmp(del->name, name) == 0)
            {
                if (prev == NULL)
                    *ptr = del->next;
                else
                    prev->next = del->next;

                free(del);
                printf("Record deleted\n");
                return;
            }

            prev = del;
            del = del->next;
        }

        printf("Matching record not found\n");
    }
    else
    {
        printf("Invalid choice\n");
    }
}

void modify_record(SLL *ptr)
{
    char ch;
    SLL *target = NULL;
    int rno;

    if (ptr == NULL)
    {
        printf("No records found\n");
        return;
    }

    printf("Enter which record to search for modification\n");
    printf("R/r : Search by roll number\n");
    printf("N/n : Search by name\n");
    printf("P/p : Search by percentage\n");
    printf("Enter choice: ");

    if (scanf(" %c", &ch) != 1)
        return;

    if (ch == 'R' || ch == 'r')
    {
        printf("Enter roll number: ");
        if (scanf("%d", &rno) != 1)
            return;

        for (SLL *temp = ptr; temp != NULL; temp = temp->next)
        {
            if (temp->rollno == rno)
            {
                target = temp;
                break;
            }
        }
    }
    else if (ch == 'N' || ch == 'n')
    {
        char name[30];
        int count = 0;

        printf("Enter name: ");
        if (scanf("%29s", name) != 1)
            return;

        for (SLL *temp = ptr; temp != NULL; temp = temp->next)
        {
            if (strcmp(temp->name, name) == 0)
            {
                count++;
                target = temp;
            }
        }

        if (count > 1)
        {
            printf("Multiple records found:\n");
            for (SLL *temp = ptr; temp != NULL; temp = temp->next)
            {
                if (strcmp(temp->name, name) == 0)
                    printf("%d %s %.2f\n",
                           temp->rollno, temp->name, temp->percentage);
            }

            printf("Enter roll number of the record to modify: ");
            if (scanf("%d", &rno) != 1)
                return;

            target = NULL;
            for (SLL *temp = ptr; temp != NULL; temp = temp->next)
            {
                if (temp->rollno == rno &&
                    strcmp(temp->name, name) == 0)
                {
                    target = temp;
                    break;
                }
            }
        }
    }
    else if (ch == 'P' || ch == 'p')
    {
        float per;
        int count = 0;

        printf("Enter percentage: ");
        if (scanf("%f", &per) != 1)
            return;

        for (SLL *temp = ptr; temp != NULL; temp = temp->next)
        {
            if (temp->percentage == per)
            {
                count++;
                target = temp;
            }
        }

        if (count > 1)
        {
            printf("Multiple records found:\n");
            for (SLL *temp = ptr; temp != NULL; temp = temp->next)
            {
                if (temp->percentage == per)
                    printf("%d %s %.2f\n",
                           temp->rollno, temp->name, temp->percentage);
            }

            printf("Enter roll number of the record to modify: ");
            if (scanf("%d", &rno) != 1)
                return;

            target = NULL;
            for (SLL *temp = ptr; temp != NULL; temp = temp->next)
            {
                if (temp->rollno == rno && temp->percentage == per)
                {
                    target = temp;
                    break;
                }
            }
        }
    }
    else
    {
        printf("Invalid choice\n");
        return;
    }

    if (target == NULL)
    {
        printf("Record not found\n");
        return;
    }

    printf("Current record: %d %s %.2f\n",
           target->rollno, target->name, target->percentage);
    printf("Enter updated name and percentage: ");

    if (scanf("%29s %f", target->name, &target->percentage) != 2)
    {
        printf("Invalid input\n");
        return;
    }

    printf("Record modified\n");
}

/* Save the current linked-list records to student.dat. */
void save_record(SLL *ptr)
{
    FILE *fp = fopen("student.dat", "w");

    if (fp == NULL)
    {
        perror("Unable to open student.dat");
        return;
    }

    while (ptr != NULL)
    {
        fprintf(fp, "%d %s %.2f\n",
                ptr->rollno, ptr->name, ptr->percentage);
        ptr = ptr->next;
    }

    fclose(fp);
    printf("Records saved successfully\n");
}

int CountNode(SLL *ptr)
{
    int count = 0;

    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }

    return count;
}

void sort_list(SLL *ptr)
{
    char ch;

    if (ptr == NULL)
    {
        printf("No records found\n");
        return;
    }

    printf("N/n : Sort by name\n");
    printf("P/p : Sort by percentage (descending)\n");
    printf("Enter choice: ");

    if (scanf(" %c", &ch) != 1)
        return;

    if (ch != 'N' && ch != 'n' && ch != 'P' && ch != 'p')
    {
        printf("Invalid choice\n");
        return;
    }

    for (SLL *p1 = ptr; p1 != NULL; p1 = p1->next)
    {
        for (SLL *p2 = p1->next; p2 != NULL; p2 = p2->next)
        {
            int cond;

            if (ch == 'N' || ch == 'n')
                cond = strcmp(p1->name, p2->name) > 0;
            else
                cond = p1->percentage < p2->percentage;

            if (cond)
            {
                int temp_rollno = p1->rollno;
                char temp_name[30];
                float temp_percentage = p1->percentage;

                strcpy(temp_name, p1->name);

                p1->rollno = p2->rollno;
                strcpy(p1->name, p2->name);
                p1->percentage = p2->percentage;

                p2->rollno = temp_rollno;
                strcpy(p2->name, temp_name);
                p2->percentage = temp_percentage;
            }
        }
    }

    printf("Sorted successfully\n");
}

void delete_all(SLL **ptr)
{
    SLL *del = *ptr;

    while (del != NULL)
    {
        *ptr = del->next;
        free(del);
        del = *ptr;
    }

    printf("All records deleted\n");
}

void reverse_list(SLL **ptr)
{
    SLL *prev = NULL;
    SLL *current = *ptr;
    SLL *next = NULL;

    if (current == NULL)
    {
        printf("No records found\n");
        return;
    }

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *ptr = prev;
    printf("List reversed successfully\n");
}

