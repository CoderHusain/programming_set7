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
    char skills[50];
    float service_years;
};

struct empAward
{
    char empId[10];
    char awardName[20];
    char awardField[20];
    char description[50];
};

struct empContribution
{
    char empId[10];
    char softwareName[20];
    char desc[50];
    char isPatent[5];
};

struct empAchievement
{
    char empId[10];
    char isAchievement[5];
    char achievementDetails[50];
};

struct taskDetails
{
    char empId[10];
    char taskName[50];
    char req_skills[50];
    char description[100];
    //char additionalTraining[50];
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
    scanf("\n%d", &scope);
    return scope;
}

//to navigate into admin
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
    infile = fopen("emp.dat", "a+");
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

void emp_award_view(char emp_id[10])
{
    FILE *ofile1;
    struct empAward a;
    ofile1 = fopen("award.dat", "a+");
    if (ofile1 == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return;
    }

    //Read the file contents till end of the file
    while (fread(&a, sizeof(struct empAward), 1, ofile1))
    {
        if (!strcmp(a.empId, emp_id))
        {
            printf("\n\n-------------------Employee Achievement Data-----------------------\n\n");
            printf("\n%s", a.awardName);
            printf("\n%s", a.awardField);
            printf("\n%s", a.description);
        }
    }

    fclose(ofile1);
}

void emp_cont_view(char emp_id[10])
{
    FILE *ofile1;
    struct empContribution cont;
    ofile1 = fopen("patent.dat", "a+");
    if (ofile1 == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return;
    }

    //Read the file contents till end of the file
    while (fread(&cont, sizeof(struct empContribution), 1, ofile1))
    {
        if (!strcmp(cont.empId, emp_id))
        {
            printf("\n\n-------------------Employee Contribution Data-----------------------\n\n");
            printf("\n%s", cont.softwareName);
            printf("\n%s", cont.desc);
            printf("\n%s", cont.isPatent);
        }
    }

    fclose(ofile1);
}

void emp_ach_view(char emp_id[10])
{
    FILE *ofile1;
    struct empAchievement ach;
    ofile1 = fopen("ach.dat", "a+");
    if (ofile1 == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return;
    }

    //Read the file contents till end of the file
    while (fread(&ach, sizeof(struct empAchievement), 1, ofile1))
    {
        if (!strcmp(ach.empId, emp_id))
        {
            printf("\n\n-------------------Employee Achievement Data-----------------------\n\n");
            printf("\n%s", ach.isAchievement);
            printf("\n%s", ach.achievementDetails);
        }
    }

    fclose(ofile1);
}

void emp_task_view(char emp_id[10])
{
    FILE *ofile1;
    struct taskDetails task;
    ofile1 = fopen("tasks.dat", "r");
    if (ofile1 == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return;
    }

    //Read the file contents till end of the file
    while (fread(&task, sizeof(struct taskDetails), 1, ofile1))
    {
        if (!strcmp(task.empId, emp_id))
        {
            printf("\n\n-------------------Employee Task Data-----------------------\n\n");
            printf("Task name: \t%s\nDescription: \t%s\nSkills: \t%s\n\n", task.taskName, task.description, task.req_skills);
            AdditionalTrainingCheck(emp_id);
        }
    }

    fclose(ofile1);
}

// printing the details
void emp_view_employee(char emp_id[10])
{
    system("@cls||clear");

    // printing employee details and tasks
    FILE *ofile1, *ofile3;
    struct empDetails e;
    struct empUpgrade u;
    int flag = 0;

    //Open the file for reading
    ofile1 = fopen("emp.dat", "r");
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
            flag = 1;
            printf("\n-------------------Employee Data-----------------------\n\n");
            printf("\nID:\t\t%s", e.empId);
            printf("\nName:\t\t%s", e.name);
            printf("\nAge:\t\t%d", e.age);
            printf("\nAddress:\t%s", e.address);
            printf("\nContact:\t%s", e.contact);
            printf("\nQualification:\t%s", e.qualifications);
            printf("\nSkills\t\t:%s", e.skills);

            emp_task_view(emp_id);
            emp_award_view(emp_id);
            emp_cont_view(emp_id);
            emp_ach_view(emp_id);

            if (e.service_years >= 6)
            {
                ofile3 = fopen("upgrade.dat", "r");
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

    fclose(ofile1);

    if (flag == 0)
    {
        printf("\n Employee doesn't exist. Check your details properly!!!");
        return;
    }
    int ch;
    printf("\n\n\n\t1. Back to menu\t\t2. Logout\n");
    scanf("%d", &ch);
    if (ch == 1)
    {
        return;
    }
    else
    {
        system("@cls||clear");
        printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
        exit(0);
    }
}

//edit employee details
void emp_edit_employee(char emp_id[10])
{
    FILE *file;
    int choice, x;

    printf("\n\t1. View Details\n\t2. Edit Details\n\t3. Back\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        emp_view_employee(emp_id);
        break;

    case 2:
    {
    UpdateMenu:
        //edit options
        system("@cls||clear");

        printf("\n--------------------Edit Menu---------------------\n");
        printf("\n\t1. Edit General Details");
        printf("\n\t2. Add Award details");
        printf("\n\t3. Add Patented Software");
        printf("\n\t4. Add any Meritorious Achievement");
        printf("\n\t5. Back");
        printf("\n Select your option: ");
        scanf("%d", &x);

        system("@cls||clear");

        switch (x)
        {
        case 1:
        {
            struct empDetails e;
            //Open the file
            file = fopen("emp.dat", "a+");
            if (file == NULL)
            {
                fprintf(stderr, "\nError opening file\n");
                return;
            }
            break;
        }

        case 2:
        {
            struct empAward a;

            //Open the file
            file = fopen("award.dat", "a+");
            if (file == NULL)
            {
                fprintf(stderr, "\nError opening file\n");
                return;
            }

            strcpy(a.empId, emp_id);
            printf("\nEnter Award Name: ");
            scanf("%s", &a.awardName);
            printf("\nEnter Award Field (IT/Management/HR/etc): ");
            scanf("%s", &a.awardField);
            printf("\nEnter Award Description: ");
            scanf("%s", &a.description);

            //Write struct to the file
            fwrite(&a, sizeof(struct empAward), 1, file);

            if (fwrite != 0)
                printf("Contents to file writen successfully! \n");
            else
                printf("Error writing file!\n");

            break;
        }

        case 3:
        {
            struct empContribution c;

            //Open the file
            file = fopen("patent.dat", "a+");
            if (file == NULL)
            {
                fprintf(stderr, "\nError opening file\n");
                return;
            }

            strcpy(c.empId, emp_id);
            printf("\nEnter Software Name: ");
            scanf("%s", &c.softwareName);
            printf("\nEnter Description: ");
            scanf("%s", &c.desc);
            printf("\nIs it patented (yes/no): ");
            scanf("%s", &c.isPatent);

            //Write struct to the file
            fwrite(&c, sizeof(struct empContribution), 1, file);

            if (fwrite != 0)
                printf("Contents to file writen successfully! \n");
            else
                printf("Error writing file!\n");

            break;
        }

        case 4:
        {
            struct empAchievement a;

            //Open the file
            file = fopen("ach.dat", "a+");
            if (file == NULL)
            {
                fprintf(stderr, "\nError opening file\n");
                return;
            }

            strcpy(a.empId, emp_id);
            printf("\nIs it a meritorious Achievement (yes/no): ");
            scanf("%s", &a.isAchievement);
            printf("\nEnter Description: ");
            scanf("%s", &a.achievementDetails);

            //Write struct to the file
            fwrite(&a, sizeof(struct empAchievement), 1, file);

            if (fwrite != 0)
                printf("Contents to file writen successfully! \n");
            else
                printf("Error writing file!\n");

            break;
        }
        case 5:
            return;

        default:
        {
            printf("\nInvalid choice!!!");
            //goto UpdateMenu;
        }

            fclose(file);
        }
    }

    case 3:
        return;

    default:
        printf("Invalid choice!!!");
    }
}

// Menu for admin
int admin_menu()
{
    system("@cls||clear");
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

int employee_menu()
{
    system("@cls||clear");
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
    system("@cls||clear");
    struct empDetails e;
    struct empUpgrade u;
    FILE *outfile, *outfile2, *infile;
    char id[10];
    printf("\n----------------Admin View-------------------\n\n");
    printf("\t Employee Id: ");
    scanf("%s", id);

    //Open file for reading
    infile = fopen("emp.dat", "a+");
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
    scanf("%d", &e.age); //validation
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
    outfile = fopen("emp.dat", "a+");
    outfile2 = fopen("upgrade.dat", "a+");
    if ((outfile == NULL) || (outfile2 == NULL))
    {
        fprintf(stderr, "\nError in opening file");
        return;
    }

    //Write struct to the file
    fwrite(&e, sizeof(struct empDetails), 1, outfile);

    if (fwrite != 0)
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
    system("@cls||clear");
    // enter emp id
    char id[10];
    printf("\n Enter ID: ");
    scanf("%s", &id);
    emp_edit_employee(id);
    return;
}

void AdditionalTrainingCheck(char emp_id[10])
{
    struct empDetails e;
    struct taskDetails t;
    FILE *ofile1, *ofile2;
    //int flag = 0;

    char newString[10][10], rs[10][10];
    char n[10][10];
    int i, j, ctr1, ctr2, flag, s;
    char str1[50], str2[50];
    //ctr1 - Required Skills
    //ctr2 - Skills there

    fflush(stdin);

    ofile1 = fopen("tasks.dat", "a+");
    ofile2 = fopen("emp.dat", "a+");

    while (fread(&t, sizeof(struct taskDetails), 1, ofile1))
    {
        if (!strcmp(t.empId, emp_id))
        {
            strcpy(str1, t.req_skills);
            break;
        }
    }

    while (fread(&e, sizeof(struct empDetails), 1, ofile2))
    {
        if (!strcmp(e.empId, emp_id))
        {
            strcpy(str2, e.skills);
            break;
        }
    }

    j = 0;
    ctr1 = 0;
    for (i = 0; i <= (strlen(str1)); i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if (str1[i] == ',' || str1[i] == '\0')
        {
            newString[ctr1][j] = '\0';
            ctr1++; //for next word
            j = 0;  //for next word, init index to 0
        }
        else
        {
            newString[ctr1][j] = str1[i];
            j++;
        }
    }

    j = 0;
    ctr2 = 0;
    for (i = 0; i <= (strlen(str2)); i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if (str2[i] == ',' || str2[i] == '\0')
        {
            n[ctr2][j] = '\0';
            ctr2++; //for next word
            j = 0;  //for next word, init index to 0
        }
        else
        {
            n[ctr2][j] = str2[i];
            j++;
        }
    }

    flag = ctr1;
    s = 0;
    for (i = 0; i < ctr1; i++)
    {
        strcpy(rs[s], newString[i]);
        s++;
        for (j = 0; j < ctr2; j++)
        {
            if (strcmpi(newString[i], n[j]) == 0)
            {
                flag--;
                s--;
                continue;
            }
        }
    }
    if (flag == 0)
        printf("No training");
    else
    {
        printf("\nTraining required for the following technologies:\n");
        for (i = 0; i < s; i++)
            printf("\n\t%s", rs[i]);
        
    }
}

void admin_assign_task()
{
    system("@cls||clear");
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

    // AdditionalTrainingCheck(task.empId);

    //Open file for writing

    outfile = fopen("tasks.dat", "a+");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError in opening file");
        return;
    }

    //Write struct to the file
    fwrite(&task, sizeof(struct taskDetails), 1, outfile);

    if (fwrite != 0)
    {
        printf("Contents to file writen successfully! \n");
    }
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
            printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
            exit(0);
        default:
            printf("Invalid choice");
            break;
        }
    }
    return 0;
}
