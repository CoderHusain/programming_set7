/**
*  A menu-driven program for Employee Presence Monitoring System
*  @author: Team NARAC - Nisha, Anshika, Retesh, Chaitali, Akshat
*  @language: C
*  This program does some magic, anshika and nisha will be explaining soon in a doc
*  Assumptions:
*  1. DB folder was already built in the directory outside project directory
**/

// List of library functions
#include <stdio.h> //for input output functions like printf, scanf
#include <stdlib.h>  
#include <string.h>  //string operations
#include <time.h>   //time operations

// Structure for employee details
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

struct taskDetails{
    char taskName[50];
    char empId[10];
    char req_skills[50];
    char description[100];
};


int selectScope(){
    int scope;
    printf("Please Make a Selection:\n\n");
    printf("\t1. Admin\n\t2. Employee\n\t3.EXIT");
    printf("\n\tEnter the options[1/2/3]:");
    scanf("\n%d",&scope);
    return scope;
    switch(scope){
        case 1:
            getCredentials(1);
            break;
        case 2:
            getCredentials(2);
            break;
        case 3:
            exit(0);
        default:
            printf("Please select from the options above");
    }

}



int getCredentials(int flag){
    int result;
    if(flag == 1){
        char pass[20];
        printf("\t\nEnter the password:");
        scanf("%s",pass);
        if(!strcmp(pass,"incorrect")){
            admin_menu();
            result = 1;
        }
        else{
            printf("\tEntered password is incorrect\n");
            exit(0);
        }
    }
    else{
        char id[10],password[20];
        printf("\tEnter the id:");
        gets(id);
        // fflush(stdin);
    }
    return result;
}



// Menu for admin
int admin_menu()
{
    int selection;
    printf("Please Make a Selection:\n\n");
    printf("\t1. Add Employee\n");
    printf("\t2. View Employee by ID\n");
    printf("\t3. Assign task to employees\n");
    printf("\t4. Log Out\n");
    fflush(stdin);
    printf("\n\t\tYour Choice:\t");
    fflush(stdin);
    scanf("\n%d", &selection);
    return selection;
}

int employee_menu(){
    int selection;
    printf("Please Make a Selection:\n\n");
    printf("\t1. View Profile\n");
    printf("\t2. Edit Profile\n");
    printf("\n\t\tYour Choice:\t");
    fflush(stdin);
    scanf("\n%d", &selection);
    return selection;
}

void add_employee(){
    struct empDetails e;
    printf("\tEmployee Id: ");
    scanf("%s",e.empId);
    printf("\t Employee contact: ");
    scanf("%s",e.contact);
    printf("\tQualification: ");
    scanf("%s",e.qualifications);
    printf("\tYears of Service: ");
    scanf("%f",&e.service_years);

    printf("%s,%s,%s,%.2f",e.empId,e.contact,e.qualifications,e.service_years);
}

void view_employee(){
    //view of employee
    printf("Employee View");
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

int main(){
    //Declare Variables
    int main_selection,admin_selection,employee_selection,cred_result;
    
    while(1)
    {
        main_selection = selectScope();
        system("@cls||clear"); //clears the window
        
        //enters the main selection view
        switch(main_selection){
            case 1:
                cred_result = getCredentials(1);
                if(cred_result != 1){
                    exit(0);
                }
                Admins_menu: admin_selection = admin_menu();
                system("@cls||clear");
                
                //enters the admin view
                switch(admin_selection){
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
                if(cred_result != 1){
                    exit(0);
                }
                break;
        }
    }
    return 0;
}
