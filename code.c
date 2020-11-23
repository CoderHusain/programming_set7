/**
*  @author: Team 7 - Aditi, Debadrita, Husain, Nikhil, Stuti, Vasundhara
*  @language: C
**/

// List of library functions
#include <stdio.h> //for input output functions like printf, scanf
#include <stdlib.h>
#include <string.h> //string operations

struct empDetails
{
    char empId[10];
    char password[25];
    char name[40]; 
    short age;
    char address[100];
    char contact[14];
    char qualifications[50];
    char skills[40];
    float service_years;
};

//struct empDetails emp[50];
struct taskDetails
{
    char empId[10];
    char taskName[50];
    char req_skills[50];
    char description[100];
};

struct empAward
{
    char empId[10];
    char awardName[20];
    char skill[20];
    char achievement[50];
};

struct empUpgrade
{
    char empId[10];
    char incentive;
    char promotion;
};

// select the user
int selectScope()
{
    int scope;
    printf("Please Make a Selection:\n\n");
    printf("\t1. Admin\n\t2. Employee\n\t3. EXIT");
    printf("\n\tEnter the options[1/2/3]:");
    scanf("\n%d",&scope);
    return scope;
}

//edit employee details
void emp_edit_employee(char id[10])
{
    emp_view_employee(id);

    int ch;
    printf("\nDo you wish to update the details?\n1. Yes\n2. No\nEnter your choice (1 or 2): ");
    scanf("%d", ch);
    if (ch == 1)
    {
        //edit options
        printf("\n Your Details Updated Successfully !!");
        system("@cls||clear");
    }
    else if (ch == 2)
    {
        return; //logging out, IDK
    }
    else
    {
        printf("Invalid choice!!!");
    }
}

//to navigate into admin or employee view
int getCredentials()
{
    int result = 0;
    char pass[20];
    printf("\t\nEnter the password:");
    scanf("%s", pass);
    if (!strcmp(pass, "incorrect"))
    {
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
                getCredentials;
            else
                return -1;
        }
    }
    return result;
}

int getEmpPassword(char id[10])
{

    FILE *infile;
    int result = 0;
    struct empDetails e;
    infile = fopen("emp.txt", "a+");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return -1;
    }

    //Read the file contents till end of the file
    while (fread(&e, sizeof(struct empDetails), 1, infile))
    {
        if (!strcmp(e.empId, id))
        {
            char pass[20];
            printf("\t\nEnter the password: ");
            scanf("%s", pass);
            if (!strcmp(pass, e.password))
            {
                result = 2;
            }
            else
            {
                int val;
                printf("\n\nIncorrect Password!!!\n ");
                printf("\t1.Try Entering Again \n");
                printf("\t2.Log Out \n");
                scanf("%d", &val);
                if (val == 1)
                    getEmpPassword(e.empId);
                else
                    result = 1;
            }
        }
    }

    if (result == 0)
    {
        int val;
        printf("\tEmployee ID is incorrect\n");
        printf("\t1.Try Entering Again \n");
        printf("\t2.Log Out \n");
        scanf("%d", &val);
        if (val == 1)
            getCredentials(2);
        else
            result = 1;
    }
    return result;
}

// printing the details
void emp_view_employee(char emp_id[10])
{
    // printing employee details and tasks
    FILE *ofile1, *ofile2, *ofile3;
    struct empDetails e;
    struct taskDetails task;
    struct empUpgrade u;
    int flag = 0;

    //Open the file for reading
    ofile1 = fopen("emp.txt", "r");
    if (ofile1 == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return;
    }

    //Read the file contents till end of the file
    while (fread(&e, sizeof(struct empDetails), 1, ofile1))
    {
        if (!strcmpi(e.empId, emp_id))
        {
            flag=1;
            printf("\n-------------------Employee Data-----------------------\n\n");
            printf("\nID:\t\t%s", e.empId);
            printf("\nName:\t\t%s", e.name);
            printf("\nAge:\t\t%d", e.age);
            printf("\nAddress:\t%s", e.address);
            printf("\nContact:\t%s", e.contact);
            printf("\nQualification:\t%s", e.qualifications);
            printf("\nSkills\t\t:%s", e.skills);

            if (e.service_years >= 6)
            {
                ofile3 = fopen("upgrade.txt", "r");
                while (fread(&u, sizeof(struct empUpgrade), 1, ofile3))
                {
                    if (!strcmpi(e.empId, u.empId))
                    {
                        u.incentive = 'y';
                        printf("\n\nIncentive Credited for completing 6 years of service!!!\n\n");
                    }
                }
                fclose(ofile3);
            }
        }
    }

    if(flag==0){
        printf("\n Employee doesn't exist. Check your details properly!!!");
        return;
    }

    ofile2 = fopen("tasks.txt", "r");
    if (ofile2 == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return;
    }

    //Read the file contents till end of the file
    while (fread(&task, sizeof(struct taskDetails), 1, ofile2))
    {
        if (!strcmp(task.empId, emp_id))
        {
            printf("\n\n-------------------Employee Task Data-----------------------\n\n");
            printf("Task name: \t%s\nDescription: \t%s\nSkills: \t%s\n", task.taskName, task.description, task.req_skills);
        }
            
    }

    fclose(ofile1);
    fclose(ofile2);
    return;
}

// Menu for admin
int admin_menu()
{
    int selection;
    printf("\n----------------Admin View-------------------\n\n");
    printf("Please Make a Selection:\n\n");
    printf("\t1. Add Employee\n");
    printf("\t2. View Employee by ID \n");
    printf("\t3. Edit Employee details \n");
    printf("\t4. Assign task to employees\n");
    printf("\t5. Log Out\n");
    fflush(stdin);
    printf("\n\t\tYour Choice:\t");
    fflush(stdin);
    scanf("\n%d", &selection);
    return selection;
}

int employee_menu(){
    int selection;
    printf("\n----------------Employee View-------------------\n\n");
    printf("Please Make a Selection:\n\n");
    printf("\t1. View Profile\n");
    printf("\t2. Edit Profile\n");
    printf("\t3. Log Out\n");
    printf("\n\t\tYour Choice:\t");
    fflush(stdin);
    scanf("\n%d", &selection);
    return selection;
}

void admin_add_employee()
{
    struct empDetails e;
    struct empUpgrade u;
    FILE *outfile, *outfile2, *infile;
    char id[10];
    printf("\n----------------Admin View-------------------\n\n");
    printf("\t Employee Id: ");
    scanf("%s", id);

    //Open file for reading
    infile = fopen("emp.txt", "a+");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError in opening file");
        return;
    }

    while (fread(&e, sizeof(struct empDetails), 1, infile))
    {
        if (!strcmp(e.empId, id))
        {
            int ch;
            printf("\nEmployee already exist!!!\n\n");
            printf("Do you wish to update the employee details?\n1. Yes\n2. No\n: ");
            scanf("%d", ch);
            if (ch == 1)
            {
                emp_edit_employee(e.empId);
            }
            else if (ch == 2)
            {
                break; //its getting out of code, IDK
            }
            else
            {
                printf("\nInvalid choice");
            }
            return;
        }
    }

    strcpy(e.empId, id);
    printf("\t Employee password: ");
    scanf("%s", &e.password);
    printf("\t Employee name: ");
    scanf("%s", &e.name);
    printf("\t Employee age: ");
    scanf("%d", &e.age);
    printf("\t Employee contact: ");
    scanf("%s", &e.contact);
    printf("\t Employee Address: ");
    scanf("%s", &e.address);
    printf("\t Qualification: ");
    scanf("%s", &e.qualifications);
    printf("\t Employee skills: ");
    scanf("%s", &e.skills);
    printf("\t Years of Service: ");
    scanf("%f", &e.service_years);
    //Open file for writing
    outfile = fopen("emp.txt", "a+");
    outfile2 = fopen("upgrade.txt", "a+");
    if ((outfile == NULL) || (outfile2 == NULL))
    {
        fprintf(stderr, "\nError in opening file");
        return;
    }

    //Write struct to the file
    fwrite (&e, sizeof(struct empDetails), 1, outfile);

    if(fwrite != 0)
        printf("Contents to file writen successfully! \n");
    else
        printf("Error writing file!\n");

    strcpy(u.empId, e.empId);
    u.incentive = 'n';
    u.promotion = 'n';
    fwrite(&u, sizeof(struct empUpgrade), 1, outfile2);

    //Close file
    fclose(outfile);
    fclose(outfile2);
    return;
}

void admin_view_employee()
{
    // enter emp id
    char id[10];
    printf("\n Enter ID: ");
    scanf("%s", &id);
    emp_view_employee(id);
    return;
}

void admin_edit_employee()
{
    // enter emp id
    char id[10];
    printf("\n Enter ID: ");
    scanf("%s", &id);
    emp_edit_employee(id);
    return;
}

void admin_assign_task()
{
    //assign task to empployee
    struct taskDetails task;
    FILE *outfile;
    fflush(stdin);
    printf("\n----------------Admin View-------------------\n\n");
    printf("Enter the employee id to whom the task is assigned : ");
    gets(task.empId);
    printf("Enter the task name: ");
    gets(task.taskName);
    printf("Enter the task description: ");
    gets(task.description);
    printf("Enter the required skills for the task : ");
    gets(task.req_skills);

    //Open file for writing
    outfile = fopen("tasks.txt", "a+");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError in opening file");
        return;
    }

    //Write struct to the file
    fwrite (&task, sizeof(struct taskDetails), 1, outfile);

    if(fwrite != 0)
        printf("Contents to file writen successfully! \n");
    else
        printf("Error writing file!\n");

    //Close file
    fclose(outfile);
    return;
}

int main()
{
    int main_selection, admin_selection, employee_selection, cred_result;
    char id[10];

    while (1)
    {
        main_selection = selectScope(); //navigationg to select the user
        system("@cls||clear");

        switch (main_selection)
        {
        case 1:
            cred_result = getCredentials();
            if (cred_result != 1)
            {
                continue;
            }
        Admins_menu:
            admin_selection = admin_menu();
            system("@cls||clear");

            //enters the admin view
            switch (admin_selection)
            {
            case 1:
                admin_add_employee();
                goto Admins_menu; // goes to admin menu
                break;
            case 2:
                admin_view_employee();
                goto Admins_menu; // goes to admin menu
                break;
            case 3:
                admin_edit_employee();
                goto Admins_menu; // goes to admin menu
                break;
            case 4:
                admin_assign_task();
                goto Admins_menu; // goes to admin menu
                break;
            case 5:
                //logs out of the admin view
                continue;
            }
            break;

        case 2:

            // enter emp id

            printf("\n Enter ID: ");
            scanf("%s", &id);

            cred_result = getEmpPassword(id);
            if (cred_result != 2)
            {
                continue;
            }

        Employee_menu:
            employee_selection = employee_menu();
            system("@cls||clear");

            //enters the employee view
            switch (employee_selection)
            {
            case 1:
                emp_view_employee(id);
                goto Employee_menu; // goes to employee menu
                break;
            case 2:
                emp_edit_employee(id);
                goto Employee_menu; // goes to employee menu
                break;

            case 3:
                continue;

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
