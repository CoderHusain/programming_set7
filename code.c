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
    printf("\t1. Admin\n\t2. Employee\n\t3. EXIT");
    printf("\n\tEnter the options[1/2/3]:");
    scanf("\n%d",&scope);
    return scope;
}

int getCredentials(int flag){
    int result=0;
    if(flag == 1)
    {
        char pass[20];
        printf("\t\nEnter the password:");
        scanf("%s",pass);
        if(!strcmp(pass,"incorrect"))
        {
            printf("\nLogin successful!!\n");
            result = 1;
        }
        else
        {
            printf("\tEntered password is incorrect\n");
            exit(0);
        }
    }
    else if(flag==2){
        char emp_id[10];
        printf("\n Enter ID: ");
        scanf("%s",&emp_id);
        result = emp_details(emp_id);   
    }
    else{
        printf("Invalid choice");
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
    int flag =0;
         
    //Open the file for reading
    ofile1 = fopen("emp.dat","r");
    if (ofile1 == NULL)
    {
    fprintf(stderr,"\nError opening file\n");
        exit(1);
    }

    //Read the file contents till end of the file
    while (fread(&e, sizeof(struct empDetails), 1, ofile1))
    {
        if(strcmp(e.empId,emp_id)==0)
        {
            flag=1;
            printf("\n-------------------Employee Data-----------------------\n\n");
            printf("ID:%s \nContact:%s \nQualifications:%s \nService Years:%f \n",e.empId,e.contact,e.qualifications,e.service_years);
        }        
    }

    if(flag==0){
        printf("\n Employee doesn't exist. Check your details properly!!!");
        return 0;
    }

    ofile2 = fopen("tasks.dat","r");
    if (ofile2 == NULL)
    {
        fprintf(stderr,"\nError opening file\n");
        exit(1);
    }

    //Read the file contents till end of the file
    while (fread(&task, sizeof(struct taskDetails), 1, ofile2))
    {
        //printf("%s\n",task.empId);
        if(strcmp(task.empId,emp_id)==0)
        {
            printf("\n-------------------Employee Task Data-----------------------\n\n");
            printf("Task name: %s\nDescription: %s\n Skills: %s\n",task.taskName,task.description,task.req_skills);
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
    printf("\n----------------Employee View-------------------\n\n");
    printf("Please Make a Selection:\n\n");
    printf("\t1. View Profile\n");
    printf("\t2. Edit Profile\n");
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
    scanf("%s",e.empId);
    printf("\t Employee contact: ");
    scanf("%s",e.contact);
    printf("\tQualification: ");
    scanf("%s",e.qualifications);
    printf("\tYears of Service: ");
    scanf("%f",&e.service_years);
    
    printf("%s\n,%s\n,%s\n,%.2f\n\n",e.empId,e.contact,e.qualifications,e.service_years);
    //Open file for writing
    outfile = fopen( "emp.dat" , "a+" );
    if(outfile == NULL)
    {
        fprintf(stderr, "\nError in opening file");
        exit(1);
    }

    //Write struct to the file
    fwrite (&e, sizeof(struct empDetails), 1, outfile);

    if(fwrite != 0)
        printf("Contents to file writen successfully! \n");
    else
        printf("Error writing file!\n");

    //Close file
    fclose(outfile);
}

void view_employee(){
    //view of employee
    printf("\n----------------Employee View-------------------\n\n");
    FILE *infile;
    struct empDetails e;
    char id[10];

    // enter emp id
    printf("\n Enter ID");
    scanf("%s",&id);

    //Open the file for reading
    infile = fopen("emp.dat","r");
    if (infile == NULL)
    {
        fprintf(stderr,"\nError opening file\n");
        exit(1);
    }

    //Read the file contents till end of the file
    while (fread(&e, sizeof(struct empDetails), 1, infile))
    {
        if(strcmp(e.empId,id)==0)
            printf("ID:%s \nContact:%s \nQualifications:%s \nService Years:%f \n",e.empId,e.contact,e.qualifications,e.service_years);
    }

    //Close file
    fclose(infile);
}

void assign_task(){
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
    
   
    printf("%s\n%s\n%s\n%s\n",task.empId,task.taskName,task.description,task.req_skills);

    //Open file for writing
    outfile = fopen( "tasks.dat" , "a+" );
    if(outfile == NULL)
    {
        fprintf(stderr, "\nError in opening file");
        exit(1);
    }

    //Write struct to the file
    fwrite (&task, sizeof(struct taskDetails), 1, outfile);

    if(fwrite != 0)
        printf("Contents to file writen successfully! \n");
    else
        printf("Error writing file!\n");

    //Close file
    fclose(outfile);
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
                switch(admin_selection)
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
                if(cred_result != 1)
                {
                    exit(0);
                }
                break;
            
            case 3:
                exit(0);

            default: printf("Please enter a valid option");
        }
    }
    return 0;
}
