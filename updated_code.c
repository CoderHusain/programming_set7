#include <stdio.h> //for input output functions like printf, scanf
#include <stdlib.h>
#include <string.h> //string operations
#include <time.h>   //time operations

// Structure for employee details
static int i=0;
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
    printf("\n\tPlease Make a Selection:\n\n");
    printf("\t1. Admin\n\t2. Employee\n\t3.EXIT");
    printf("\n\tEnter the options[1/2/3]:");
    scanf("\n%d", &scope);
    return scope;
    switch (scope)
    {
    case 1:
        getCredentials(1);
        break;
    case 2:
        getCredentials(2);
        break;
    case 3:
        exit(0);
    default:
        printf("\nPlease select from the options above");
    }
}

void edit_employee(){

    char ino[7];
    printf("\nEnter Your INo. ");
    scanf("%s",ino);
    printf("\n Enter Your Details :\n");
    for(int i=0;i<2;i++)
    {
        if (!strcmp(ino, emp[i].empId))
        {
    
    printf("\t Employee contact: ");
    scanf("%s",emp[i].contact);
    printf("\t Qualification: ");
    scanf("%s",emp[i].qualifications);
    printf("\t Years of Service: ");
    scanf("%f",&emp[i].service_years);
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

int admin_menu()
{
    int selection;
    printf("\n Please Make a Selection:\n\n");
    printf("\t1. Add Employee\n");
    printf("\t2. View All Employees \n");
    printf("\t3. Assign task to employees\n");
    printf("\t4. Log Out\n");
    fflush(stdin);
    printf("\n\t\tYour Choice:\t");
    scanf("\n%d", &selection);
    return selection;
}

int employee_menu(){
    int selection;
    printf("\n Please Make a Selection:\n\n");
    printf("\t1. View Profile\n");
    printf("\t2. Edit Profile\n");
    printf("\t3.Log Out\n");
    printf("\n\t\tYour Choice:\t");
    fflush(stdin);
    scanf("\n%d", &selection);
    return selection;
}

void add_employee(){
    printf("\n \t Employee Id: ");
    scanf("%s",emp[i].empId);
    printf("\t Employee contact: ");
    scanf("%s",emp[i].contact);
    printf("\t Qualification: ");
    scanf("%s",emp[i].qualifications);
    printf("\t Years of Service: ");
    scanf("%f",&emp[i].service_years);

    printf(" \n %s,%s,%s,%.2f",emp[i].empId,emp[i].contact,emp[i].qualifications,emp[i].service_years);
    i++;
}

void admin_view_employee(){
         //view of employee
    printf("\n Details Are :\n");
    for(int i=0;i<2;i++)                          //insted of 1 ( max records limit to be set)
    {
        // if (strcmp(ino, ""))
        // {
    printf("\n \t Employee Id: %s",emp[i].empId);               //giving empty output bcs not storing anything now
    printf("\n\t Employee contact: %s",emp[i].contact);
    printf("\n\t Qualification: %s",emp[i].qualifications);
    printf("\n\t Years of Service: %.2f",emp[i].service_years);
    // }
    }

}

void emp_view_employee(){
        //  view of employee
    char ino[7];
    printf("Enter Your INo. ");
    scanf("%s",ino);
    printf("\n Your Details Are :\n");
    for(int i=0;i<2;i++)
    {
        if (!strcmp(ino, emp[i].empId))
        {
            // printf("\n Your Details Are :\n");
            printf("\n\t Employee Id: %s",emp[i].empId);               //giving empty output bcs not storing anything now
    printf("\n\t Employee contact: %s",emp[i].contact);
    printf("\n\t Qualification: %s",emp[i].qualifications);
    printf("\n\t Years of Service: %.2f",emp[i].service_years);
        }
        break;
    }

}

void assign_task(){
    //assign task to empployee
    struct taskDetails task;
    fflush(stdin);
    printf("Enter the task name: ");
    gets(task.taskName);
    printf("Enter the task description: ");
    gets(task.description);
    printf("Enter the required skills for the task : ");
    gets(task.req_skills);
    printf("Enter the employee id to whom the task is assigned : ");
    gets(task.req_skills);
    printf("%s,%s,%s,%s",task.taskName,task.description,task.req_skills,task.empId);
}


int main()
{
    int main_selection,admin_selection,employee_selection,cred_result;

    while(1)
    {
        main_selection = selectScope();
        system("@cls||clear");

        switch(main_selection){
            case 1: 
            cred_result = getCredentials(1);
                if(cred_result != 1){
                    selectScope();
                }
                Admins_menu: admin_selection = admin_menu();
                system("@cls||clear");
                 switch(admin_selection){
                    case 1:
                        add_employee();
                        goto Admins_menu; // goes to admin menu
                        break;
                    case 2:
                        admin_view_employee();
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
                if(cred_result != 2){
                    selectScope();
                }

                Employee_menu: employee_selection = employee_menu();
                system("@cls||clear");
                
                //enters the employee view
                switch(employee_selection){
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

                    default: {
                        printf("Wrong Choice Entered");
                        goto Employee_menu;
                         break;
                }
                break;
        }

              case 3: 
             
              printf(" ***** SUCCESSFULLY LOGGED OUT ******");
              exit(0);
    }
    }
    return 0;
}