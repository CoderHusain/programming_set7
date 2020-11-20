/**
*  A menu-driven program for Employee Presence Monitoring System
*  @author: Team 7 - Husain,Stuti,Debadrita,Nikhil,Vasundhara,Aditi
*  @language: C
*  Assumptions:
*  1. DB folder was already built in the directory outside project directory
**/

// List of library functions
#include <stdio.h> //for input output functions like printf, scanf
#include <stdlib.h>
#include <string.h> //string operations
#include <time.h>   //time operations

// Structure for employee details
static int i = 0;
// static char ino[7];

struct empDetails
{
    char empId[10];
    char password[25];
    char name[40];
    short age;
    char address[100];
    char contact[14];
    char qualifications[50];
    float service_years;
};

struct empDetails emp[50];
struct taskDetails
{
    char taskName[50];
    char empId[10];
    char req_skills[50];
    char description[100];
};

int selectScope()
{
    int scope;
    printf("Please Make a Selection:\n\n");
    printf("\t1. Admin\n\t2. Employee\n\t3. EXIT");
    printf("\n\tEnter the options[1/2/3]:");
    scanf("\n%d", &scope);
    return scope;
}

void edit_employee()
{

    char ino[7];
    printf("\nEnter Your INo. ");
    scanf("%s", ino);
    printf("\n Enter Your Details :\n");
    for (int i = 0; i < 2; i++)
    {
        if (!strcmp(ino, emp[i].empId))
        {

            printf("\t Employee contact: ");
            scanf("%s", emp[i].contact);
            printf("\t Qualification: ");
            scanf("%s", emp[i].qualifications);
            printf("\t Years of Service: ");
            scanf("%f", &emp[i].service_years);
        }
        break;
    }

    printf("\n Your Details Updated Successfully !!");
    system("@cls||clear");
}
int getCredentials(int flag)
{
    int result;
    if (flag == 1)
    {
        char pass[20];
        printf("\t\nEnter the password:");
        scanf("%s", pass);
        if (!strcmp(pass, "incorrect"))
        {
            // admin_menu();
            result = 1;
        }
        else
        {
            printf("\t\nEntered password is incorrect\n");
            if (result != 1)
            {
                int val;

                printf("\t1.Try Entering Again \n");
                printf("\t2.Log Out \n");
                scanf("%d", &val);
                if (val == 1)
                    getCredentials(1);
                else
                    return -1;
            }
        }
    }
    else if (flag == 2)
    {
        char ino[7];
        printf("\t\nEnter Your INo.: ");
        scanf("%s", ino);
        for (int j = 0; j < 50; j++)
        {
            if (!strcmp(ino, emp[j].empId))
            {
                // employee_menu();
                result = 2;
                break;
            }
        }

        if (result != 2)
        {
            int val;
            printf("\tEntered INo is incorrect\n");
            printf("\t1.Try Entering Again \n");
            printf("\t2.Log Out \n");
            scanf("%d", &val);
            if (val == 1)
                getCredentials(2);
            else
                return -1;
        }
    }
    else
    {
        printf("\t Wrong Choice Entered "); // check if this is necessary
    }
    return result;
}

// printing the details
int emp_details(int emp_id)
{
    // printing employee details and tasks
    FILE *ofile1, *ofile2;
    struct empDetails e;
    struct taskDetails task;
    int flag = 0;

    //Open the file for reading
    ofile1 = fopen("emp.dat", "r");
    if (ofile1 == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    //Read the file contents till end of the file
    while (fread(&e, sizeof(struct empDetails), 1, ofile1))
    {
        if (strcmp(e.empId, emp_id) == 0)
        {
            flag = 1;
            printf("\n-------------------Employee Data-----------------------\n\n");
            printf("ID:%s \nContact:%s \nQualifications:%s \nService Years:%f \n", e.empId, e.contact, e.qualifications, e.service_years);
        }
    }

    if (flag == 0)
    {
        printf("\n Employee doesn't exist. Check your details properly!!!");
        return 0;
    }

    ofile2 = fopen("tasks.dat", "r");
    if (ofile2 == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    //Read the file contents till end of the file
    while (fread(&task, sizeof(struct taskDetails), 1, ofile2))
    {
        //printf("%s\n",task.empId);
        if (strcmp(task.empId, emp_id) == 0)
        {
            printf("\n-------------------Employee Task Data-----------------------\n\n");
            printf("Task name: %s\nDescription: %s\n Skills: %s\n", task.taskName, task.description, task.req_skills);
        }
    }

    fclose(ofile1);
    fclose(ofile2);
    return 1;
}

// Menu for admin
int admin_menu()
{
    int selection;
    printf("\n----------------Admin View-------------------\n\n");
    printf("Please Make a Selection:\n\n");
    printf("\t1. Add Employee\n");
    printf("\t2. View Employee by ID \n");
    printf("\t3. Assign task to employees\n");
    printf("\t4. Log Out\n");
    fflush(stdin);
    printf("\n\t\tYour Choice:\t");
    scanf("\n%d", &selection);
    return selection;
}

int employee_menu()
{
    int selection;
    printf("\n----------------Employee View-------------------\n\n");
    printf("Please Make a Selection:\n\n");
    printf("\t1. View Profile\n");
    printf("\t2. Edit Profile\n");
    printf("\t3.Log Out\n");
    printf("\n\t\tYour Choice:\t");
    fflush(stdin);
    scanf("\n%d", &selection);
    return selection;
}

void add_employee()
{
    struct empDetails e;
    FILE *outfile;
    printf("\n----------------Admin View-------------------\n\n");
    printf("\tEmployee Id: ");
    scanf("%s", e.empId);
    printf("\t Employee contact: ");
    scanf("%s", e.contact);
    printf("\tQualification: ");
    scanf("%s", e.qualifications);
    printf("\tYears of Service: ");
    scanf("%f", &e.service_years);
    //Open file for writing
    outfile = fopen("emp.dat", "a+");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError in opening file");
        exit(1);
    }

    //Write struct to the file
    fwrite(&e, sizeof(struct empDetails), 1, outfile);

    if (fwrite != 0)
        printf("Contents to file writen successfully! \n");
    else
        printf("Error writing file!\n");

    //Close file
    fclose(outfile);
}

void view_employee()
{
    //view of employee
    printf("\n----------------Employee View-------------------\n\n");
    FILE *infile;
    struct empDetails e;
    char id[10];

    // enter emp id
    printf("\n Enter ID");
    scanf("%s", &id);

    //Open the file for reading
    infile = fopen("emp.dat", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    //Read the file contents till end of the file
    while (fread(&e, sizeof(struct empDetails), 1, infile))
    {
        if (strcmp(e.empId, id) == 0)
            printf("ID:%s \nContact:%s \nQualifications:%s \nService Years:%f \n", e.empId, e.contact, e.qualifications, e.service_years);
    }

    //Close file
    fclose(infile);
}


void emp_view_employee()
{
    //  view of employee
    char ino[7];
    printf("Enter Your INo. ");
    scanf("%s", ino);
    printf("\n Your Details Are :\n");
    for (int i = 0; i < 2; i++)
    {
        if (!strcmp(ino, emp[i].empId))
        {
            // printf("\n Your Details Are :\n");
            printf("\n\t Employee Id: %s", emp[i].empId); //giving empty output bcs not storing anything now
            printf("\n\t Employee contact: %s", emp[i].contact);
            printf("\n\t Qualification: %s", emp[i].qualifications);
            printf("\n\t Years of Service: %.2f", emp[i].service_years);
        }
        break;
    }
}

void assign_task()
{
    //assign task to empployee
    struct taskDetails task;
    FILE *outfile;
    fflush(stdin);
    printf("\n----------------Task View-------------------\n\n");
    printf("Enter the employee id to whom the task is assigned : ");
    gets(task.empId);
    printf("Enter the task name: ");
    gets(task.taskName);
    printf("Enter the task description: ");
    gets(task.description);
    printf("Enter the required skills for the task : ");
    gets(task.req_skills);


    //Open file for writing
    outfile = fopen("tasks.dat", "a+");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError in opening file");
        exit(1);
    }

    //Write struct to the file
    fwrite(&task, sizeof(struct taskDetails), 1, outfile);

    if (fwrite != 0)
        printf("Contents to file writen successfully! \n");
    else
        printf("Error writing file!\n");

    //Close file
    fclose(outfile);
}

int main()
{
    int main_selection, admin_selection, employee_selection, cred_result;

    while (1)
    {
        main_selection = selectScope();
        system("@cls||clear");

        switch (main_selection)
        {
            case 1:
                cred_result = getCredentials(1);
                if (cred_result != 1)
                {
                    selectScope();
                }
            Admins_menu:
                admin_selection = admin_menu();
                system("@cls||clear");

                //enters the admin view
                switch (admin_selection)
                {
                case 1:
                    add_employee();
                    goto Admins_menu; // goes to admin menu
                    break;
                case 2:
                    view_employee();
                    goto Admins_menu; // goes to admin menu
                    break;
                case 3:
                    assign_task();
                    goto Admins_menu; // goes to admin menu
                    break;
                case 4:
                    //logs out of the admin view
                    break;
                }
                break;

            case 2:
                cred_result = getCredentials(2);
                if (cred_result != 2)
                {
                    selectScope();
                }

            Employee_menu:
                employee_selection = employee_menu();
                system("@cls||clear");

                //enters the employee view
                switch (employee_selection)
                {
                case 1:
                    emp_view_employee();
                    goto Employee_menu; // goes to employee menu
                    break;
                case 2:
                    edit_employee();
                    goto Employee_menu; // goes to employee menu
                    break;

                case 3:
                    selectScope();
                    break;

                default:
                {
                    printf("Wrong Choice Entered");
                    goto Employee_menu;
                    break;
                }
                break;
                }
            case 3:
                printf(" ***** SUCCESSFULLY LOGGED OUT ******");
                exit(0);
            default:
                printf("Invalid choice");
                break;
        }
    }
    return 0;
}