void promotionCheck(char emp_id[10])
// {
//     FILE *file;
//     struct empAchievement a;
//     struct empContribution c;

//     //Open the file for reading
//     file = fopen("ach.dat", "r");
//     if (file == NULL)
//     {
//         fprintf(stderr, "\nError opening file\n");
//         return;
//     }

//     //Read the file contents till end of the file
//     while (fread(&a, sizeof(struct empAchievement), 1, file))
//     {
//         if (!strcmpi(a.empId, emp_id))
//         {
//             if (!strcmpi(a.isAchievement,"YES"))
//             {
//                 printf("\nCongratulations on your achievement!!!\n");
//                 break;
//             }
//         }
//     }
//     fclose(file);

//     //Open the file for reading
//     file = fopen("patent.dat", "r");
//     if (file == NULL)
//     {
//         fprintf(stderr, "\nError opening file\n");
//         return;
//     }

//     //Read the file contents till end of the file
//     while (fread(&c, sizeof(struct empContribution), 1, file))
//     {
//         if (!strcmpi(c.empId, emp_id))
//         {
//             if (!strcmpi(c.isPatent,"YES"))
//             {
//                 printf("\nCongratulations you have been promoted for your Contibution to the organization!!!\n");
//                 break;
//             }
//         }
//     }
//     fclose(file);

// }
