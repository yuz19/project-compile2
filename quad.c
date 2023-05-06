#define MAX_QUADS 1000
#include <stdlib.h>
#include "ctype.h"
typedef struct quadruplet {
  char op[20];
  char arg1[20];
  char arg2[20];
  char res[20];
} quadruplet;

quadruplet quadruplets[MAX_QUADS];
 
extern int qc;
void quadr(char *op, char *arg1, char *arg2, char *res) {

  if (qc >= MAX_QUADS) {
    printf("Erreur : capacité de quadruplets dépassée.\n");
    exit(EXIT_FAILURE);
  }
  
  strcpy(quadruplets[qc].op, op);
  strcpy(quadruplets[qc].arg1, arg1);
  strcpy(quadruplets[qc].arg2, arg2);
  strcpy(quadruplets[qc].res, res);
  qc++;
}

void ajour_quad(int ligne, int champ, char *val) {
  switch (champ) {
    case 1:
      strcpy(quadruplets[ligne].op, val);
      break;
    case 2:
      strcpy(quadruplets[ligne].arg1, val);
      break;
    case 3:
      strcpy(quadruplets[ligne].arg2, val);
      break;
    case 4:
      strcpy(quadruplets[ligne].res, val);
      break;
    default:
      printf("Erreur : champ de quadruplet invalide.\n");
      exit(EXIT_FAILURE);
  }
}
void affich_quad(){
    for (int i = 0; i < sizeof(quadruplets) / sizeof(quadruplets[0]); i++){
        if(strcmp(quadruplets[i].op, "") != 0 || 
        strcmp(quadruplets[i].arg1, "") != 0 || 
        strcmp(quadruplets[i].arg2, "") != 0 || 
        strcmp(quadruplets[i].res, "") != 0) {
        printf("\n %d - ( %s , %s , %s , %s )",i,quadruplets[i].op,quadruplets[i].arg1,quadruplets[i].arg2,quadruplets[i].res); 
        }
    }
}
int checkIfChange(quadruplet* quads,int num_quads,int indice_actuel){
  int changed = 0;
  quadruplet* q1 = &quads[indice_actuel];
  int i ;
    for (i= indice_actuel+1; i < num_quads; i++) {
       quadruplet* q2 = &quads[i];
      if (isalpha(q1->arg1[0])){
        if(strcmp(q1->arg1,q2->res) && strcmp(q2->op,"=")){
          return 1;
        }
      }else if (isalpha(q1->arg2[0])){
        if(strcmp(q1->arg2,q2->res) && strcmp(q2->op,"=")){
          return 1;
        }
      }
  }

     return 0;

 
}
int checkIfResChange(quadruplet* quads,int num_quads,int indice_actuel){
  int changed = 0;
  quadruplet* q1 = &quads[indice_actuel];
  int i ;
   printf("\n%d\n",indice_actuel);
    for (i= indice_actuel+1; i < num_quads; i++) {
       quadruplet* q2 = &quads[i];
      
      if (isalpha(q1->arg1[0])){
        if(strcmp(q1->res,q2->arg1)==0){
           printf("out");
          return 1;
        }
      }else if (isalpha(q1->arg2[0])){
        if(strcmp(q1->res,q2->arg2)==0){
          printf("out");

          return 1;
        }
      }
  }
  
   
     return 0;
 
 
}
void  Simplify(quadruplet* q1,int indice){
  char res[20];
  char resb[20];
  char savet[20];
  strcpy(savet,q1->res);
   int first=indice;
  //printf("%d",indice);
        quadruplet save[MAX_QUADS];
          // copier les valeurs de quadruplets dans save
          for (int i = 0; i < qc; i++){
              save[i] = quadruplets[i];
          }
      
          
          sprintf(resb,"%s%d",q1->res,0);
  if(isalpha(q1->arg1[0])){
 
      int max=atoi(q1->arg2);
      strcpy(quadruplets[indice].op, "+");
      strcpy(quadruplets[indice].arg1,q1->arg1);
      strcpy(quadruplets[indice].arg2, q1->arg1);
      strcpy(quadruplets[indice].res, resb);
    for(int i=1;i<max-1;i++){
      sprintf(res, "%s%d%d", "T",first, i);
      indice++;
      strcpy(quadruplets[indice].op, "+");
      strcpy(quadruplets[indice].arg1, resb);
      strcpy(quadruplets[indice].arg2, q1->arg1);
      strcpy(quadruplets[indice].res, res);
    }



    // modifier les valeurs de quadruplets à partir de l'indice donné
        for(int i=first+1;i<qc;i++){
            //printf("%d%d",i,qc+max-2);
            strcpy(quadruplets[i+max-2].op, save[i].op);
            strcpy(quadruplets[i+max-2].arg1,save[i].arg1);
            strcpy(quadruplets[i+max-2].arg2, save[i].arg2);
            strcpy(quadruplets[i+max-2].res, save[i].res);
        }
      

  }else if(isalpha(q1->arg2[0])){

            int max=atoi(q1->arg1);
            strcpy(quadruplets[indice].op, "+");
            strcpy(quadruplets[indice].arg1,q1->arg2);
            strcpy(quadruplets[indice].arg2, q1->arg2);
            strcpy(quadruplets[indice].res, resb);
          for(int i=1;i<max-1;i++){
            //printf("test");
            sprintf(res, "%s%d%d", "T",first, i);
            indice++;
            strcpy(quadruplets[indice].op, "+");
            strcpy(quadruplets[indice].arg1, resb);
            strcpy(quadruplets[indice].arg2, q1->arg2);
            strcpy(quadruplets[indice].res, res);
            sprintf(resb, "%s%d%d", "T",first, i);
          }



        // modifier les valeurs de quadruplets à partir de l'indice donné
    
        for(int i=first+1;i<qc;i++){
            //printf("%d%d",i,qc+max-2);
            strcpy(quadruplets[i+max-2].op, save[i].op);
            strcpy(quadruplets[i+max-2].arg1,resb);
            strcpy(quadruplets[i+max-2].arg2, save[i].arg2);
            strcpy(quadruplets[i+max-2].res, save[i].res);
        }
          
  }
}

quadruplet* optimize_quads(quadruplet* quads,int num_quads) {
 
    
    int optimized = 1;
    while (optimized) {
        optimized = 0; 
        
        for (int i = 0; i < num_quads; i++) {
            
            quadruplet* q1 = &quads[i];
            for (int j = i+1; j < num_quads; j++) {
                
                quadruplet* q2 = &quads[j];
                // Propagation de copie
                 if (isalpha(q1->arg1[0]) && (strncmp(q1->arg1, "T", 1) != 0) && strcmp(q1->op, "=") == 0) {
                    //check if its variable
                     
                        if(strcmp(q1->arg1, q2->arg1) == 0){
                          printf("propagation copie arg1\n");
                          strcpy(q2->arg1, q1->res);
                          optimized = 1;
                        }else if(strcmp(q1->arg1, q2->arg2) == 0){
                          printf("propagation copie arg2\n");
                          strcpy(q2->arg2, q1->res);
                          optimized = 1;
                        }
                   
                }
                // Propagation d'expression
                  else if (strcmp(q1->op, "=") == 0 && (strncmp(q1->arg1, "T", 1) == 0)) {
                    if (strcmp (q1->res,q2->arg1) ==0){
                    printf("Propagation d'expression arg1\n");
                      strcpy(q2->arg1, q1->arg1);
                      optimized = 1;
                    }else if(strcmp (q1->res,q2->arg2)==0){
                      printf("Propagation d'expression arg2\n");
                      strcpy(q2->arg2, q1->arg1);
                      optimized = 1;
                    }
              
                  }
                // Élimination d'expressions redondantes
                else if ((strcmp (q1->arg1,q2->arg1) ==0 && strcmp (q1->arg2,q2->arg2)==0) || (strcmp (q1->arg1,q2->arg2) ==0 && strcmp (q1->arg2,q2->arg1)==0)) {
                                printf("d");
                                for(int k=j+1;k<qc;k++){
                                   quadruplet* q3 = &quads[k];
                                    if(strcmp (q3->arg1,q2->res)==0 && strcmp (q3->op,"=")==0){
                                       printf("%d",k);
                                      strcpy(q3->arg1,q1->res);
                                    }
                                }
                                if(checkIfChange(quads,num_quads,j)==0){
                                    memmove(q2, q2+1, (num_quads-j)*sizeof(quadruplet));
                                    num_quads--;
                                    j--;
                                }
           
                            }
                // Simplification algébrique             
                  else if (strcmp(q1->op, "*") == 0 && ((atoi(q1->arg1) && isalpha(q1->arg2[0])) || (atoi(q1->arg2) && isalpha(q1->arg1[0])) ) ) {
                      printf("Simplification algebrique\n");

                      Simplify(q1,i);
                      optimized = 1;
                  } 
                // Élimination de code inutile
                else if (strcmp(q1->res, q2->arg1) == 0 && strcmp(q1->op, "=") == 0
                    && strcmp(q2->op, "=") == 0) {
                    printf("Elimination de code inutile");

                    memmove(q2, q2+1, (num_quads-j)*sizeof(quadruplet));
                    num_quads--;
                    j--;
                    optimized = 1;
                }
            }
             
        }
    
         
           
    }
    
    return quads;
}




