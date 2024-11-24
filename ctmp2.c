#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void addApplicant();
void calculatePoints();
void setApplicantState (char* MajorList );
void printList();
void writeAssinedApplicants();

int count;

struct Applicant{
   int id;
   char applicant[20];
   char education[20];//in the main check if it “BSc” OR “MSc” only 
   char major[5];
   int Experience;
   float GPA;
   float Points;
   char State[10];
};
struct Applicant list[7];

int main(){

   addApplicant();
   calculatePoints();
   
   char* majorList="CSC,InS,SWE,CEN";
   setApplicantState(majorList);
   
   writeAssinedApplicants(); 
   printList();
   
   return 0;
}
void addApplicant(){
   FILE *file = fopen("Applicants.txt", "r");
   if (file == NULL) {
      perror("Error opening file");
      return;
   }
    
   char OneLine[100];
   count=0;
   int i;
    
   for(i=0;i<3;i++) //to skip the first two lines
      fgets(OneLine, sizeof(OneLine),file);
    
    
   while (fgets(OneLine, sizeof(OneLine), file) != NULL) {
      if (sscanf(OneLine, "%d %19s %19s %d %4s %f %9s",
                   &list[count].id,
                   list[count].applicant,
                   list[count].education,
                   &list[count].Experience,
                   list[count].major,
                   &list[count].GPA,
                   list[count].State) == 7) {
            
            // Validate education
         if (strcmp(list[count].education, "BSc") != 0 &&
                strcmp(list[count].education, "MSc") != 0) {
            printf("Invalid education format for applicant ID %d: %s\n",
                       list[count].id, list[count].education);
                      
            continue;  // Skip invalid entries
         }
      
            // Initialize Points and move to the next entry
         list[count].Points = 0;
         count++;
      }
     
   }
   fclose(file);
}


    


void calculatePoints(){
   int experience=0;
   int i;
   for(i = 0; i<7; i++){
      experience = list[i].Experience;
      if(strcmp(list[i].education, "MSc") == 0)
         experience+= 10;
      list[i].Points = list[i].GPA + experience;}
}
    
    

void setApplicantState (char* MajorList){

   for(int i = 0; i<count; i++){
  
      if(strstr(MajorList, list[i].major) !=NULL )
         strcpy(list[i].State, "Candidate");
   
   }

   int highest = 0;
   int index =0;
   for(int i = 0; i<count; i++){
      if(strcmp(list[i].State, "Candidate") == 0)
         if(list[i].Points>highest){
            highest = list[i].Points;
            index = i;
            }
   }
               strcpy(list[index].State, "Assigned");

   
}

void writeAssinedApplicants(){
   FILE *fpo= fopen("Output_Applicants.txt","w");
   if (fpo == NULL) {
      printf("Error opening file.\n");
      return;}
   fprintf(fpo, "The input applicants List is:\n");
   fprintf(fpo, "id\t\tName\t\tEducation\t\tExperience\t\tMajor\t\tGPA\t\tState\n");       
   int i;
   for (i=0; i<count ; i++){
   fprintf(fpo, "%d\t\t%s\t\t%s\t\t\t%d\t\t\t%s\t\t%.1f\t\t%s\n",
                list[i].id, list[i].applicant, list[i].education,
                list[i].Experience, list[i].major,
                list[i].GPA, "OWL");
                }

    /*  if (strcmp(list[i].State, "Assigned") == 0){
         fprintf(fpo, "%d\t\t%s\t\t%s\t\t\t%d\t\t\t%s\t\t%.1f\t\t%s\n",
                list[i].id, list[i].applicant, list[i].education,
                list[i].Experience, list[i].major,
                list[i].GPA, list[i].State);}
      else{             
         fprintf(fpo, "%d\t\t%s\t\t%s\t\t\t%d\t\t\t%s\t\t%.1f\t\t%s\n",
                list[i].id, list[i].applicant, list[i].education,
                list[i].Experience, list[i].major,
                list[i].GPA, "OWL");}
   }  */               
                
   fprintf(fpo, "----------------------------------------------------------------------------------------\n");            
   fprintf(fpo, "\nThe Candidates list is:\n");
   fprintf(fpo, "id\t\tName\t\tEducation\t\tExperience\t\tMajor\t\tPoints\t\tState\n");
   for (int i = 0; i <count ; i++) {
      if (strcmp(list[i].State, "Candidate") == 0 || strcmp(list[i].State, "Assigned") == 0) {   
         fprintf(fpo, "%d\t\t%s\t\t%s\t\t\t%d\t\t\t%s\t\t%.1f\t\t%s\n",
                list[i].id, list[i].applicant, list[i].education,
                list[i].Experience, list[i].major,
                list[i].Points, "Candidate");}
   }
                 
   fprintf(fpo, "----------------------------------------------------------------------------------------\n");            
   fprintf(fpo, "\nAssigned Applicant is:\n");
   fprintf(fpo, "id\t\tName\t\tEducation\t\tExperience\t\tMajor\t\tPoints\t\tState\n");
   for (int i = 0; i <count ; i++) {
      if (strcmp(list[i].State, "Assigned") == 0) {   
         fprintf(fpo, "%d\t\t%s\t\t%s\t\t\t%d\t\t\t%s\t\t%.1f\t\t%s\n",
                list[i].id, list[i].applicant, list[i].education,
                list[i].Experience, list[i].major,
                list[i].Points, list[i].State);}
   }   
    fclose(fpo); 
}   



void printList() {
    printf("\nThe input applicants list is:\n");
    printf("ID   %-15s %-15s %-10s %-15s %-5s %-10s\n", "Name", "Education", "Experience", "Major", "GPA", "State");
    printf("-------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-4d %-15s %-15s %-10d %-15s %-5.2f %-10s\n",
               list[i].id,
               list[i].applicant,
               list[i].education,
               list[i].Experience,
               list[i].major,
               list[i].GPA,
               "OWL");
    }
    printf("-------------------------------------------------------------------------------------------\n");

    printf("\nThe Candidates list is:\n");
    printf("ID   %-15s %-15s %-15s %-10s %-10s\n", "Applicant", "Education", "Major", "Points", "State");
    printf("-------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].State, "Candidate") == 0 || strcmp(list[i].State, "Assigned") == 0) {
            printf("%-4d %-15s %-15s %-15s %-10.2f %-10s\n",
                   list[i].id,
                   list[i].applicant,
                   list[i].education,
                   list[i].major,
                   list[i].Points,
                   "Candidate");
        }
    }

    printf("-------------------------------------------------------------------------------------------\n");
    printf("Assigned Applicant is:\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].State, "Assigned") == 0) {
            printf("%-4d %-15s %-15s %-15s %-10.2f %-10s\n",
                   list[i].id,
                   list[i].applicant,
                   list[i].education,
                   list[i].major,
                   list[i].Points,
                   list[i].State);
            break;
        }
    }
}
