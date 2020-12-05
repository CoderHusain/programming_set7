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
    short service_years;
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
void selectScope();
void getCredentials();
int checkEmployee(char emp_id[10]);
void getEmpPassword(char emp_id[10]);
void emp_award_view(char emp_id[10]);
void emp_cont_view(char emp_id[10]);
void emp_ach_view(char emp_id[10]);
void emp_task_view(char emp_id[10]);
void admin_menu();
void employee_menu(char emp_id[10]);
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

void selectScope() // menu to select the user
{
    char main_selection[10], id[10];

    while (1)
    {
        system("@cls||clear");
        printf("Please Make a Selection:\n\n");
        printf("\t1. Admin\n\t2. Employee\n\t3. EXIT");
        printf("\n\tEnter the options[1/2/3]:");
        scanf(" %s", &main_selection);
        if (strlen(main_selection) > 1)
        {
            main_selection[0] = 'a';
        }

        switch (main_selection[0])
        {
        case '1':
            getCredentials();
            admin_menu();
            continue;

        case '2':
            system("@cls||clear");
            printf("\n Enter ID: ");
            scanf("%s", &id);

            getEmpPassword(id);
            employee_menu(id);
            continue;

        case '3':
            system("@cls||clear");
            printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
            exit(0);

        default:
            printf("Invalid choice\n");
            Sleep(1000);
            break;
        }
    }
}

void getCredentials() //function to check admin password
{
    int result = 1;
    char pass[20];

    do
    {
        system("@cls||clear");
        printf("\t\nEnter the password:");
        scanf("%s", &pass);
        if (!strcmp(pass, "incorrect")) //if password is correct,return 0
        {
            return;
        }
        else
        {
            printf("\t\nEntered password is incorrect\n"); //if password is incorrect
            int val;
            printf("\t1.Try Entering Again \n");
            printf("\t2.Back \n");
            scanf("%d", &val);
            if (val == 1)
                continue;
            else if (val == 2)
            {
                system("@cls||clear");
                // printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n"); //will logout
                // exit(0);
                return;
            }
            else
            {
                printf("Invalid Choice!!!");
                Sleep(1000);
            }
        }
    } while (1);
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
            printf("\t2.Back \n");
            scanf("%d", &val);
            if (val == 1)
            {
                fflush(stdin); // enter emp id
                system("@cls||clear");
                printf("\n Enter ID: ");
                scanf("%s", &eId);
                strcpy(id, eId);
            }
            else if (val == 2)
            {
                system("@cls||clear");
                // printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                // exit(0);
                return;
            }
            else
            {
                printf("Invalid Choice!!!\n");
                Sleep(1000);
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
                system("@cls||clear");
                printf("\t\nEnter the password: ");
                scanf("%s", &pass);
                // printf("%s,%s", e.password, pass);
                if (!strcmp(pass, e.password))
                {
                    fclose(infile);
                    return;
                }
                system("@cls||clear"); //if password is incorrect
                printf("\n\nIncorrect Password!!!\n ");
                printf("\t1.Try Entering Again \n");
                printf("\t2.Back \n");
                scanf("%d", &val);
                if (val == 1)
                {
                    continue;
                }
                else if (val == 2)
                {
                    system("@cls||clear");
                    // printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                    // exit(0);
                    return;
                }
                else
                {
                    printf("Invalid Choice!!!\n");
                    Sleep(1000);
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
            system("@cls||clear");
            printf("\n\n-------------------Employee Award Data-----------------------\n\n");
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
            system("@cls||clear");
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
            system("@cls||clear");
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

void admin_menu() // Menu for admin operations
{
    do
    {
        system("@cls||clear");
        char admin_selection[10];
        printf("\n----------------Admin View-------------------\n\n");
        printf("Please Make a Selection:\n\n");
        printf("\t1. Add Employee\n");
        printf("\t2. View Employee by ID \n");
        printf("\t3. Add Additional details \n");
        printf("\t4. Assign task to employees\n");
        printf("\t5. Back\n");
        printf("\n\t\tYour Choice:\t");
        fflush(stdin);
        scanf("%s", &admin_selection);
        if (strlen(admin_selection) > 1)
        {
            admin_selection[0] = 'a';
        }

        //enters the admin view
        switch (admin_selection[0])
        {
        case '1':
            admin_add_employee();
            continue;

        case '2':
            admin_view_employee();
            continue;

        case '3':
            admin_edit_employee();
            continue;

        case '4':
            admin_assign_task();
            continue;

        case '5':
            //logs out
            system("@cls||clear");
            return;

        default:
            printf("Invalid choice\n");
            Sleep(1000);
        }
    } while (1);
}

void employee_menu(char emp_id[10]) //Menu for employee operations
{
    do
    {
        system("@cls||clear");
        fflush(stdin);
        char employee_selection[10];
        printf("\n----------------Employee View-------------------\n\n");
        printf("Please Make a Selection:\n\n");
        printf("\t1. View Personal Details\n");
        printf("\t2. View Tasks\n");
        printf("\t3. Add Additional Details\n");
        printf("\t4. Back\n");
        printf("\n\t\tYour Choice:\t");
        scanf("%s", &employee_selection);

        if (strlen(employee_selection) > 1)
        {
            employee_selection[0] = 'a';
        }

        //enters the employee view
        switch (employee_selection[0])
        {
        case '1':
            emp_view_employee(emp_id);
            continue;

        case '2':
            emp_task_view(emp_id);
            continue;

        case '3':
            emp_edit_employee(emp_id);
            continue;

        case '4':
            system("@cls||clear");
            return;

        default:

            printf("Wrong Choice Entered\n");
            Sleep(1000);
            continue;
        }

    } while (1);
}

void emp_view_employee(char emp_id[10]) // function for printing employee details and tasks
{
    FILE *ofile1;
    struct empDetails e;
    char selection[10];

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
        scanf(" %s", &selection);
        if (strlen(selection) > 1)
        {
            selection[0] = 'a';
        }

        switch (selection[0])
        {
        case '1':
            system("@cls||clear");
            //Open the file for reading
            ofile1 = fopen("emp.dat", "a+");

            //Read the file contents till end of the file
            while (fread(&e, sizeof(struct empDetails), 1, ofile1))
            {
                if (!strcmpi(e.empId, emp_id))
                {
                    system("@cls||clear");
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

        case '2':
            emp_award_view(emp_id); //to view awards
            continue;

        case '3':
            emp_ach_view(emp_id); //to view achievement
            continue;

        case '4':
            emp_cont_view(emp_id); //to view contribution
            continue;

        case '5':
            return;

        default:
            printf("\n Invalid Choice, enter again");
            Sleep(1000);
            continue;
        }
    } while (1);
}

int checkString(char String[50])
{
    int isValid;

    for (int i = 0; i < strlen(String); i++)
    {
        if ((((String[i] >= 65) && (String[i] <= 90)) || ((String[i] >= 97) && (String[i] <= 122))) || String[i] == 32) //check for characters only in name
        {
            isValid = 1;
        }
        else
        {
            isValid = 0;
            break;
        }
    }

    return isValid;
}

void emp_details_update(char emp_id[10]) //function to add employee personal details
{
    FILE *outfile, *fdel;
    struct empDetails e;
    strcpy(e.empId, emp_id);
    fflush(stdin);
    printf("\t Employee password: ");
    gets(e.password);

    while (1)
    {
        fflush(stdin);
        printf("\t Employee name: ");
        gets(e.name);

        if (checkString(e.name))
        {
            break;
        }
        else
        {
            printf("\n Invalid Name format, enter again\n");
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

    int isValid = 1;
    while (1)
    {
        fflush(stdin);
        printf("\t Employee contact: ");
        gets(e.contact);
        if ((e.contact[0] == '0') || (strlen(e.contact) > 10))
        {
            isValid = 0;
            printf("\n Invalid number format, enter again\n");
            continue;
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
            printf("\n Invalid number format, enter again\n");
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
        scanf("%d", &e.service_years);
        if ((e.service_years > 0) && (e.service_years < 40)) //check for valid age
        {
            break;
        }
        else
        {
            printf("\n Invalid, enter again\n");
            continue;
        }
    }

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

    //Open the file
    file = fopen("award.dat", "a+");
    fflush(stdin);
    strcpy(a.empId, emp_id);

    while (1)
    {
        fflush(stdin);
        printf("\nEnter Award Name: ");
        gets(a.awardName);

        if (checkString(a.awardName))
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
        printf("\nEnter Award Field (IT/Management/HR/etc): ");
        gets(a.awardField);

        if (checkString(a.awardField))
        {
            break;
        }
        else
        {
            printf("\n Field should not contain integer or special characters, enter again\n");
        }
    }

    while (1)
    {
        fflush(stdin);
        printf("\nEnter Award Description: ");
        gets(a.description);

        if (a.description)
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

    while (1)
    {
        fflush(stdin);
        printf("\nEnter Software Name: ");
        gets(c.softwareName);

        if (checkString(c.softwareName))
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
        printf("\nEnter Description: ");
        gets(c.desc);

        if (checkString(c.desc))
        {
            break;
        }
        else
        {
            printf("\n Description should not contain integer or special characters, enter again\n");
        }
    }

    while (1)
    {
        fflush(stdin);
        printf("\nIs it patented (yes/no): ");
        gets(c.isPatent);

        if ((!strcmpi(c.isPatent, "YES")) || (!strcmpi(c.isPatent, "NO")))
        {
            break;
        }
        else
        {
            printf("\n It should either be yes or no, enter again\n");
        }
    }

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

    while (1)
    {
        fflush(stdin);
        printf("\nIs it a meritorious Achievement (yes/no): ");
        gets(a.isAchievement);

        if ((!strcmpi(a.isAchievement, "YES")) || (!strcmpi(a.isAchievement, "NO")))
        {
            break;
        }
        else
        {
            printf("\n It should either be yes or no, enter again\n");
        }
    }

    while (1)
    {
        fflush(stdin);
        printf("\nEnter Description: ");
        gets(a.achievementDetails);

        if (checkString(a.achievementDetails))
        {
            break;
        }
        else
        {
            printf("\n Description should not contain integer or special characters, enter again\n");
        }
    }

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

void emp_edit_employee(char emp_id[10]) //function to add employee details
{
    char selection[10];

    do
    {
        //add options
        system("@cls||clear");

        printf("\n--------------------Add Details Menu---------------------\n");
        printf("\n\t1. Add Award details");
        printf("\n\t2. Add Patented Software");
        printf("\n\t3. Add any Meritorious Achievement");
        printf("\n\t4. Back");
        printf("\n Select your option: ");
        scanf("%s", &selection);
        if (strlen(selection) > 1)
        {
            selection[0] = 'a';
        }
        system("@cls||clear");
        switch (selection[0])
        {

        case '1':
            add_emp_award(emp_id);
            continue;

        case '2':
            add_emp_cont(emp_id);
            continue;

        case '3':
            add_emp_ach(emp_id);
            continue;

        case '4':
            return;

        default:

            printf("\nInvalid choice!!!");
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
    int ch;
    if (result)
    {
        printf("\nEmployee already exist!!!\n\n");
        Sleep(1000);
        return;
    }

    emp_details_update(id);

    return;
}

void admin_view_employee() //function for admin to view employee
{
    // enter emp id
    char id[10], eId[10];
    int result;
    system("@cls||clear");
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
            printf("\t2.Back \n");
            scanf("%d", &val);
            if (val == 1)
            {
                // enter emp id
                fflush(stdin);
                system("@cls||clear");
                printf("\n Enter ID: ");
                scanf("%s", &eId);
                strcpy(id, eId);
                printf("\n%s", id);
            }
            else if (val == 2)
            {
                system("@cls||clear");
                // printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                // exit(0);
                return;
            }
            else
            {
                printf("Invalid Choice!!!\n");
                Sleep(1000);
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
            printf("\t2.Back\n");
            scanf("%d", &val);
            if (val == 1)
            {
                // enter emp id
                fflush(stdin);
                system("@cls||clear");
                printf("\n Enter ID: ");
                scanf("%s", &eId);
                strcpy(id, eId);
                printf("\n%s", id);
            }
            else if (val == 2)
            {
                system("@cls||clear");
                // printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                // exit(0);
                return;
            }
            else
            {
                printf("Invalid Choice!!!\n");
                Sleep(1000);
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
            printf("\t2.Back \n");
            scanf("%d", &val);
            if (val == 1)
            {
                // enter emp id
                fflush(stdin);
                system("@cls||clear");
                printf("\n Enter ID: ");
                scanf("%s", &eId);
                strcpy(id, eId);
                printf("\n%s", id);
            }
            else if (val == 2)
            {
                system("@cls||clear");
                // printf("\n\n ***** SUCCESSFULLY LOGGED OUT ******\n\n");
                // exit(0);
            }
            else
            {
                printf("Invalid Choice!!!\n");
                Sleep(1000);
            }
        }
    } while (result != 1);

    strcpy(task.empId, id);

    while (1)
    {
        fflush(stdin);
        printf("Enter the task name: ");
        gets(task.taskName);

        if (checkString(task.taskName))
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
        printf("Enter the task description: ");
        gets(task.description);

        if (checkString(task.description))
        {
            break;
        }
        else
        {
            printf("\n Description should not contain integer or special characters, enter again\n");
        }
    }

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
    selectScope();
    return 0;
}
