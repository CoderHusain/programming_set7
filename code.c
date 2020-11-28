/**
*  @author: Team 7 - Aditi, Debadrita, Husain, Nikhil, Stuti, Vasundhara
*  @language: C
**/

// List of library functions
#include <stdio.h> //for input output functions like printf, scanf
#include <stdlib.h>
#include <string.h> //string operations
#include <windows.h>

struct empDetails //structure for employee details
{
    char empId[10];
    char password[25];
    char name[40];
    short age;
    char address[100];
    char contact[11];
    char qualifications[50];
    char skills[50];
    float service_years;
};

struct empAward //structure for awards recieved by employee
{
    char empId[10];
    char awardName[20];
    char awardField[20];
    char description[50];
};

struct empContribution //structure for employee contribution to organisation
{
    char empId[10];
    char softwareName[20];
    char desc[50];
    char isPatent[4];
};

struct empAchievement //structure for meritorious achievement by employee
{
    char empId[10];
    char isAchievement[4];
    char achievementDetails[50];
};

struct taskDetails //structure for employee task
{
    char empId[10];
    char taskName[50];
    char req_skills[50];
    char description[100];
};

//function declarations
int selectScope();
void getCredentials();
int checkEmployee(char emp_id[10]);
void getEmpPassword(char emp_id[10]);
void emp_award_view(char emp_id[10]);
void emp_cont_view(char emp_id[10]);
void emp_ach_view(char emp_id[10]);
void emp_task_view(char emp_id[10]);
int admin_menu();
int employee_menu();
void emp_view_employee(char emp_id[10]);
void emp_details_update(char emp_id[10]);
void emp_edit_employee(char emp_id[10]);
void admin_add_employee();
void admin_view_employee();
void add_emp_award(char emp_id[10]);
void add_emp_cont(char emp_id[10]);
void add_emp_ach(char emp_id[10]);
void admin_edit_employee();
void admin_assign_task();
void AdditionalTrainingCheck(char emp_id[10]);

int selectScope() // menu to select the user
{
    int scope;
    printf("Please Make a Selection:\n\n");
    printf("\t1. Admin\n\t2. Employee\n\t3. EXIT");
    printf("\n\tEnter the options[1/2/3]:");
    scanf("\n%d", &scope);
    return scope;
}

void getCredentials() //function to check admin password
{
    int result = 1;
    char pass[20];

    do
    {
        printf("\t\nEnter the password:");
        scanf("%s", &pass);
        if (!strcmp(pass, "incorrect")) //if password is correct,return 0
        {
            result = 0;
        }
        else
        {
            printf("\t\nEntered password is incorrect\n"); //if password is incorrect
            int val;
            printf("\t1.Try Entering Again \n");
            printf("\t2.Log Out \n");
            scanf("%d", &val);
            if (val == 1)
                continue;
            else
            {
                system("@cls||clear");
                printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n"); //will logout
                exit(0);
            }
        }
    } while (result);
}

int checkEmployee(char emp_id[10]) //function to check if the employee exists or not
{
    FILE *infile;
    struct empDetails e;

    infile = fopen("emp.dat", "a+");
    while (fread(&e, sizeof(struct empDetails), 1, infile)) //loop to iterate over file
    {
        if (!strcmpi(e.empId, emp_id))
        {
            fclose(infile);
            return 1;
        }
    }
    fclose(infile);
    return 0;
}

void getEmpPassword(char id[10]) //function to check employee password
{
    int result = 0;
    char eId[10];
    do
    {
        result = checkEmployee(id);
        if (result == 0)
        {
            int val;
            system("@cls||clear");
            printf("\tEmployee ID is incorrect\n"); //if employee does not exist
            printf("\t1.Try Entering Again \n");
            printf("\t2.Log Out \n");
            scanf("%d", &val);
            if (val == 1)
            {
                fflush(stdin); // enter emp id
                printf("\n Enter ID: ");
                scanf("%s", &eId);
                strcpy(id, eId);
            }
            else if (val == 2)
            {
                system("@cls||clear");
                printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                exit(0);
            }
        }
    } while (result != 1);

    FILE *infile;
    struct empDetails e;
    int val;
    char pass[20];
    infile = fopen("emp.dat", "a+");

    //Read the file contents till end of the file
    while (fread(&e, sizeof(struct empDetails), 1, infile))
    {
        if (!strcmpi(e.empId, id))
        {
            do
            {
                fflush(stdin);
                printf("\t\nEnter the password: ");
                scanf("%s", &pass);
                printf("%s,%s", e.password, pass);
                if (!strcmp(pass, e.password))
                {
                    fclose(infile);
                    return;
                }
                system("@cls||clear"); //if password is incorrect
                printf("\n\nIncorrect Password!!!\n ");
                printf("\t1.Try Entering Again \n");
                printf("\t2.Log Out \n");
                scanf("%d", &val);
                if (val == 2)
                {
                    system("@cls||clear");
                    printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                    exit(0);
                }

            } while (val == 1);
        }
    }
}

void emp_award_view(char emp_id[10]) //function to view award details recieved by employee
{
    system("@cls||clear");
    FILE *ofile1;
    struct empAward a;
    ofile1 = fopen("award.dat", "a+");

    //Read the file contents till end of the file
    while (fread(&a, sizeof(struct empAward), 1, ofile1))
    {
        if (!strcmp(a.empId, emp_id))
        {
            printf("\n\n-------------------Employee Achievement Data-----------------------\n\n");
            printf("Award name:\t%s\n", a.awardName);
            printf("Award Field:\t%s\n", a.awardField);
            printf("Description:\t%s\n", a.description);

            //to check whether employee is eligible for incentives or not
            if (!strcmpi(a.awardField, "IT") || (!strcmpi(a.awardField, "Information Technology")))
                printf("\nIncentive Credited for Award in IT!!!\n");
        }
    }

    fclose(ofile1);
    printf("\n");
    system("pause");
    system("@cls||clear");
}

void emp_cont_view(char emp_id[10]) //function to view any contribution for the organisation
{
    system("@cls||clear");
    FILE *ofile1;
    struct empContribution cont;
    ofile1 = fopen("patent.dat", "a+");

    //Read the file contents till end of the file
    while (fread(&cont, sizeof(struct empContribution), 1, ofile1))
    {
        if (!strcmp(cont.empId, emp_id))
        {
            printf("\n\n-------------------Employee Contribution Data-----------------------\n\n");
            printf("Software name:\t%s\n", cont.softwareName);
            printf("Description:\t%s\n", cont.desc);
            if (!strcmpi(cont.isPatent, "YES")) // if the contribution is patented, then employee is promoted.
            {
                printf("\nCongratulations you have been promoted for your Contibution to the organization!!!\n");
                break;
            }
        }
    }

    fclose(ofile1);
    printf("\n");
    system("pause");
    system("@cls||clear");
}

void emp_ach_view(char emp_id[10]) //function to view any meritorious achievement by employee
{
    system("@cls||clear");
    FILE *ofile1;
    struct empAchievement ach;
    ofile1 = fopen("ach.dat", "a+");

    //Read the file contents till end of the file
    while (fread(&ach, sizeof(struct empAchievement), 1, ofile1))
    {
        if (!strcmp(ach.empId, emp_id))
        {
            printf("\n\n-------------------Employee Achievement Data-----------------------\n\n");
            printf("Achievement:\t%s\n", ach.achievementDetails);
            if (!strcmpi(ach.isAchievement, "YES"))
            {
                printf("\nCongratulations on your achievement!!!\n"); //congratulate employee in achievement
                break;
            }
        }
    }

    fclose(ofile1);
    printf("\n");
    system("pause");
    system("@cls||clear");
}

void emp_task_view(char emp_id[10]) //function to view tasks assigned to employee
{
    system("@cls||clear");
    FILE *ofile1;
    struct taskDetails task;
    ofile1 = fopen("tasks.dat", "a+");

    //Read the file contents till end of the file
    while (fread(&task, sizeof(struct taskDetails), 1, ofile1))
    {
        if (!strcmp(task.empId, emp_id))
        {
            printf("\n\n-------------------Employee Task Data-----------------------\n\n");
            printf("Task name: \t%s\nDescription: \t%s\nSkills: \t%s\n\n", task.taskName, task.description, task.req_skills);
            AdditionalTrainingCheck(emp_id); //to check if the user needs any additional training to complete the task
        }
    }

    fclose(ofile1);
    printf("\n");
    system("pause");
    system("@cls||clear");
}

int admin_menu() // Menu for admin operations
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

int employee_menu() //Menu for employee operations
{
    system("@cls||clear");
    int selection;
    printf("\n----------------Employee View-------------------\n\n");
    printf("Please Make a Selection:\n\n");
    printf("\t1. View Personal Details\n");
    printf("\t2. View Tasks\n");
    printf("\t3. Edit Profile\n");
    printf("\t4. Log Out\n");
    printf("\n\t\tYour Choice:\t");
    fflush(stdin);
    scanf("\n%d", &selection);
    return selection;
}

void emp_view_employee(char emp_id[10]) // function for printing employee details and tasks
{
    FILE *ofile1;
    struct empDetails e;
    int ch;

    do
    {
        fflush(stdin);
        system("@cls||clear");
        printf("\n What do you wish to view?\n");
        printf("\n\t1. Personal Details");
        printf("\n\t2. Awards Recieved");
        printf("\n\t3. Meritorious Achievement");
        printf("\n\t4. Patented Contibution");
        printf("\n\t5. Back");
        printf("\n Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            system("@cls||clear");
            //Open the file for reading
            ofile1 = fopen("emp.dat", "a+");

            //Read the file contents till end of the file
            while (fread(&e, sizeof(struct empDetails), 1, ofile1))
            {
                if (!strcmpi(e.empId, emp_id))
                {
                    printf("\n-------------------Employee Data-----------------------\n\n");
                    printf("\nID:\t\t%s", e.empId);
                    printf("\nName:\t\t%s", e.name);
                    printf("\nAge:\t\t%d", e.age);
                    printf("\nAddress:\t%s", e.address);
                    printf("\nContact:\t%s", e.contact);
                    printf("\nQualification:\t%s", e.qualifications);
                    printf("\nSkills:\t\t%s", e.skills);

                    //check if incentive should be granted or not
                    if (e.service_years >= 6)
                    {
                        printf("\n\nIncentive Credited for completing 6 years of service!!!\n");
                    }
                }
            }

            fclose(ofile1);
            printf("\n");
            system("pause");
            system("@cls||clear");
            continue;

        case 2:
            emp_award_view(emp_id); //to view awards
            continue;

        case 3:
            emp_ach_view(emp_id); //to view achievement
            continue;

        case 4:
            emp_cont_view(emp_id); //to view contribution
            continue;

        case 5:
            return;

        default:
            printf("\n Invalid Choice, enter again");
            Sleep(1000);
            continue;
        }
    } while (1);
}

void emp_details_update(char emp_id[10]) //function to edit employee personal details
{
    FILE *outfile, *fdel;
    struct empDetails e;
    strcpy(e.empId, emp_id);
    fflush(stdin);
    printf("\t Employee password: ");
    gets(e.password);

    int isValid = 1;
    while (1)
    {
        fflush(stdin);
        printf("\t Employee name: ");
        gets(e.name);
        for (int i = 0; i < 20; i++)
        {
            if ((e.name[i] >= 65) && (e.name[i] <= 112)) //check for characters only in name
            {
                isValid = 1;
                break;
            }
            else
            {
                isValid = 0;
            }
        }
        if (isValid)
        {
            break;
        }
        else
        {
            printf("\n Name should not contain integer or special characters, enter again\n");
        }
    }

    while (1)
    {
        fflush(stdin);
        printf("\t Employee age: ");
        scanf("%d", &e.age);
        if ((e.age > 18) && (e.age < 58)) //check for numbers only (58 is retirement age)
        {
            break;
        }
        else
        {
            printf("\n Invalid Age, enter again\n");
            continue;
        }
    }

    isValid = 1;
    while (1)
    {
        fflush(stdin);
        printf("\t Employee contact: ");
        gets(e.contact);
        if (!strcmpi(e.contact, "0000000000"))
        {
            isValid = 0;
        }

        for (int i = 0; i < 10; i++)
        {
            if ((e.contact[i] < 48) || (e.contact[i] > 57)) //check for numbers only
            {
                isValid = 0;
                break;
            }
            else
            {
                isValid = 1;
            }
        }
        if (isValid)
        {
            break;
        }
        else
        {
            printf("\n Contact number should not contain characters, enter again\n");
        }
    }

    fflush(stdin);
    printf("\t Employee Address: ");
    gets(e.address);

    fflush(stdin);
    printf("\t Qualification: ");
    gets(e.qualifications);

    fflush(stdin);
    printf("\t Employee skills: ");
    gets(e.skills);

    isValid = 1;
    while (1)
    {
        fflush(stdin);
        printf("\t Years of Service: ");
        scanf("%f", &e.service_years);
        if ((e.age >= 0) && (e.age <= 40)) //check for valid age
        {
            break;
        }
        else
        {
            printf("\n Invalid, enter again\n");
            continue;
        }
    }

    // //Open file for writing
    // outfile = fopen("emp.dat", "a+");

    // //delete the previous record
    // int found;
    // fdel = fopen("tmp.bin", "wb");
    // if (!fdel)
    // {
    //     printf("Unable to open file temp file.");
    //     return;
    // }

    // while (fread(&e, sizeof(struct empDetails), 1, outfile) != NULL)
    // {

    //     fwrite(&e, sizeof(struct empDetails), 1, fdel);
    // }

    // fclose(outfile);
    // fclose(fdel);

    // remove("emp.dat");
    // rename("tmp.bin", "emp.dat");

    //Open file for writing
    outfile = fopen("emp.dat", "a+");

    //Write struct to the file
    fwrite(&e, sizeof(struct empDetails), 1, outfile);

    if (fwrite != 0)
    {
        printf("Contents to file writen successfully! \n");
        system("pause");
    }
    else
        printf("Error writing file!\n");

    //Close file
    fclose(outfile);
}

void add_emp_award(char emp_id[10]) //function to add employee award
{
    FILE *file;
    struct empAward a;
    int isValid;

    //Open the file
    file = fopen("award.dat", "a+");
    fflush(stdin);
    strcpy(a.empId, emp_id);

    while (1)
    {
        fflush(stdin);
        printf("\nEnter Award Name: ");
        gets(a.awardName);
        for (int i = 0; i < 20; i++)
        {
            if ((a.awardName[i] >= 65) && (a.awardName[i] <= 112)) //check for characters only in name
            {
                isValid = 1;
                break;
            }
            else
            {
                isValid = 0;
            }
        }
        if (isValid)
        {
            break;
        }
        else
        {
            printf("\n Name should not contain integer or special characters, enter again\n");
        }
    }

    isValid = 1;
    while (1)
    {
        fflush(stdin);
        printf("\nEnter Award Field (IT/Management/HR/etc): ");
        gets(a.awardField);
        for (int i = 0; i < 20; i++)
        {
            if ((a.awardField[i] >= 65) && (a.awardField[i] <= 112)) //check for characters only in name
            {
                isValid = 1;
                break;
            }
            else
            {
                isValid = 0;
            }
        }
        if (isValid)
        {
            break;
        }
        else
        {
            printf("\n Field should not contain integer or special characters, enter again\n");
        }
    }

    isValid = 1;
    while (1)
    {
        fflush(stdin);
        printf("\nEnter Award Description: ");
        gets(a.description);
        for (int i = 0; i < 50; i++)
        {
            if ((a.description[i] >= 65) && (a.description[i] <= 112)) //check for characters only in name
            {
                isValid = 1;
                break;
            }
            else
            {
                isValid = 0;
            }
        }
        if (isValid)
        {
            break;
        }
        else
        {
            printf("\n Description should not contain integer or special characters, enter again\n");
        }
    }

    //Write struct to the file
    fwrite(&a, sizeof(struct empAward), 1, file);

    if (fwrite != 0)
    {
        printf("Contents to file writen successfully! \n");
        system("pause");
    }
    else
        printf("Error writing file!\n");
    fclose(file);
}

void add_emp_cont(char emp_id[10]) //function to add employee contribution
{
    FILE *file;
    struct empContribution c;

    //Open the file
    file = fopen("patent.dat", "a+");
    fflush(stdin);
    strcpy(c.empId, emp_id);
    printf("\nEnter Software Name: ");
    gets(c.softwareName);
    printf("\nEnter Description: ");
    gets(c.desc);
    printf("\nIs it patented (yes/no): ");
    gets(c.isPatent);

    //Write struct to the file
    fwrite(&c, sizeof(struct empContribution), 1, file);

    if (fwrite != 0)
    {
        printf("Contents to file writen successfully! \n");
        system("pause");
    }
    else
        printf("Error writing file!\n");
    fclose(file);
}

void add_emp_ach(char emp_id[10]) //function to add employee achievement
{
    FILE *file;
    struct empAchievement a;

    //Open the file
    file = fopen("ach.dat", "a+");
    fflush(stdin);
    strcpy(a.empId, emp_id);
    printf("\nIs it a meritorious Achievement (yes/no): ");
    gets(a.isAchievement);
    printf("\nEnter Description: ");
    gets(a.achievementDetails);

    //Write struct to the file
    fwrite(&a, sizeof(struct empAchievement), 1, file);

    if (fwrite != 0)
    {
        printf("Contents to file writen successfully! \n");
        system("pause");
    }
    else
        printf("Error writing file!\n");
    fclose(file);
}

void emp_edit_employee(char emp_id[10]) //function to edit employee details
{
    int choice, x;

    do
    {
        system("@cls||clear");
        printf("\n\t1. View Details\n\t2. Edit Details\n\t3. Back\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            emp_view_employee(emp_id);
            continue;

        case 2:

            do
            {
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
                    emp_details_update(emp_id);
                    continue;

                case 2:
                    add_emp_award(emp_id);
                    continue;

                case 3:
                    add_emp_cont(emp_id);
                    continue;

                case 4:
                    add_emp_ach(emp_id);
                    continue;

                case 5:
                    return;

                default:

                    printf("\nInvalid choice!!!");
                    Sleep(1000);
                    continue;
                }
            } while (1);

        case 3:
            return;

        default:
            printf("Invalid choice!!!");
            Sleep(1000);
            continue;
        }
    } while (1);
}

void admin_add_employee() //function for admin to add employee
{
    system("@cls||clear");
    char id[10];
    printf("\n----------------Admin View-------------------\n\n");
    printf("\t Employee Id: ");
    scanf("%s", &id);

    int result = checkEmployee(id);
    int ch = 0;
    if (result)
    {
        do
        {
            printf("\nEmployee already exist!!!\n\n");
            printf("Do you wish to update the employee details?\n1. Yes\n2. No\n: ");
            scanf("%d", ch);
            if (ch == 1)
            {
                emp_edit_employee(id);
                continue;
            }
            else if (ch == 2)
            {
                return;
            }
            else
            {
                printf("\nInvalid choice");
                Sleep(1000);
                continue;
            }
        } while (1);
    }

    emp_details_update(id);

    return;
}

void admin_view_employee() //function for admin to view employee
{
    // enter emp id
    char id[10], eId[10];
    int result;
    printf("\n Enter ID: ");
    scanf("%s", &id);
    do
    {
        result = checkEmployee(id);
        printf("\n%d", result);
        if (result == 0)
        {
            int val;
            system("@cls||clear");
            printf("\tEmployee ID is incorrect\n");
            printf("\t1.Try Entering Again \n");
            printf("\t2.Log Out \n");
            scanf("%d", &val);
            if (val == 1)
            {
                // enter emp id
                fflush(stdin);
                printf("\n Enter ID: ");
                scanf("%s", &eId);
                strcpy(id, eId);
                printf("\n%s", id);
            }
            else if (val == 2)
            {
                system("@cls||clear");
                printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                exit(0);
            }
        }
    } while (result != 1);

    fflush(stdout);
    emp_view_employee(id);

    fflush(stdout);
    return;
}

void admin_edit_employee() //function for admin to edit employee details
{
    system("@cls||clear");
    // enter emp id
    char id[10], eId[10];
    int result;
    printf("\n Enter ID: ");
    scanf("%s", &id);
    do
    {
        result = checkEmployee(id);
        if (result == 0)
        {
            int val;
            system("@cls||clear");
            printf("\tEmployee ID is incorrect\n");
            printf("\t1.Try Entering Again \n");
            printf("\t2.Log Out \n");
            scanf("%d", &val);
            if (val == 1)
            {
                // enter emp id
                fflush(stdin);
                printf("\n Enter ID: ");
                scanf("%s", &eId);
                strcpy(id, eId);
                printf("\n%s", id);
            }
            else if (val == 2)
            {
                system("@cls||clear");
                printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                exit(0);
            }
        }
    } while (result != 1);

    emp_edit_employee(id);
    return;
}

void AdditionalTrainingCheck(char emp_id[10]) //function to check additional tasks required by employee to do a specific task
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

void admin_assign_task() //function for admin to assign task to employee
{
    system("@cls||clear");
    //assign task to employee
    struct taskDetails task;
    FILE *outfile;
    char id[10], eId[10];
    int result;
    fflush(stdin);
    printf("\n----------------Admin View-------------------\n\n");
    printf("Enter the employee id to whom the task is assigned : ");
    scanf("%s", &id);
    do
    {
        result = checkEmployee(id);
        if (result == 0)
        {
            int val;
            system("@cls||clear");
            printf("\tEmployee ID is incorrect\n");
            printf("\t1.Try Entering Again \n");
            printf("\t2.Log Out \n");
            scanf("%d", &val);
            if (val == 1)
            {
                // enter emp id
                fflush(stdin);
                printf("\n Enter ID: ");
                scanf("%s", &eId);
                strcpy(id, eId);
                printf("\n%s", id);
            }
            else if (val == 2)
            {
                system("@cls||clear");
                printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                exit(0);
            }
        }
    } while (result != 1);

    strcpy(task.empId, id);

    int isValid = 1;
    while (1)
    {
        fflush(stdin);
        printf("Enter the task name: ");
        gets(task.taskName);
        for (int i = 0; i < 20; i++)
        {
            if ((task.taskName[i] >= 65) && (task.taskName[i] <= 112))
            {
                isValid = 1;
                break;
            }
            else
            {
                isValid = 0;
            }
        }
        if (isValid)
        {
            break;
        }
        else
        {
            printf("\n Name should not contain integer or special characters, enter again\n");
        }
    }

    printf("Enter the task description: ");
    gets(task.description);
    printf("Enter the required skills for the task : ");
    gets(task.req_skills);

    //Open file for writing

    outfile = fopen("tasks.dat", "a+");

    //Write struct to the file
    fwrite(&task, sizeof(struct taskDetails), 1, outfile);

    if (fwrite != 0)
    {
        printf("Contents to file writen successfully! \n");
        system("pause");
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
            getCredentials();

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
                //logs out
                system("@cls||clear");
                printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                exit(0);
            default:
                printf("Invalid choice\n");
                Sleep(1000);
                goto Admins_menu;
                break;
            }
        case 2:
            printf("\n Enter ID: ");
            scanf("%s", &id);

            getEmpPassword(id);

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
                emp_task_view(id);
                goto Employee_menu; // goes to employee menu
                break;

            case 3:
                emp_edit_employee(id);
                goto Employee_menu; // goes to employee menu
                break;

            case 4:
                system("@cls||clear");
                printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                exit(0);

            default:

                printf("Wrong Choice Entered\n");
                Sleep(1000);
                goto Employee_menu;
                break;
            }
            break;

        case 3:
            system("@cls||clear");
            printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
            exit(0);

        default:
            printf("Invalid choice\n");
            Sleep(1000);
            break;
        }
    }

    return 0;
}
