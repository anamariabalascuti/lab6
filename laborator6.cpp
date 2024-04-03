#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NUM_INGREDIENTS 4


typedef struct {
    int damage; 
    int health; 
} PowerPuffGirl;


typedef struct {
    PowerPuffGirl base;
} Bubbles;

typedef struct {
    PowerPuffGirl base;
} Blossom;

typedef struct {
    PowerPuffGirl base;
} Buttercup;


typedef struct {
    int ingredients[NUM_INGREDIENTS]; 
} Profesor;


typedef struct {
    int damage; 
    int health; 
} MojoJojo;


PowerPuffGirl* createRandomPowerPuffGirl(Profesor* prof) {
    
    if (prof->ingredients[0] >= 1 && prof->ingredients[1] >= 1 &&
        prof->ingredients[2] >= 1 && prof->ingredients[3] >= 1) {

        
        int chance = rand() % 3;
        PowerPuffGirl* girl;

       
        if (chance == 0) {
            Bubbles* bubbles = (Bubbles*)malloc(sizeof(Bubbles));
            if (bubbles != NULL) { 
            bubbles->base.damage = 10;
            bubbles->base.health = 100;
            girl = (PowerPuffGirl*)bubbles;
            }
        }
        else if (chance == 1) {
            Blossom* blossom = (Blossom*)malloc(sizeof(Blossom));
            if (blossom != NULL) {
                blossom->base.damage = 15;
                blossom->base.health = 120;
                girl = (PowerPuffGirl*)blossom;

            }
        }
        else {
            Buttercup* buttercup = (Buttercup*)malloc(sizeof(Buttercup));
            if (buttercup != NULL) {
                buttercup->base.damage = 20;
                buttercup->base.health = 80;
                girl = (PowerPuffGirl*)buttercup;
            }
        }

        
        prof->ingredients[0]--;
        prof->ingredients[1]--;
        prof->ingredients[2]--;
        prof->ingredients[3]--;

        
        return girl;
    }

  
    return NULL;
}


void simulateBattle(PowerPuffGirl** girls, int numGirls, MojoJojo* mojo) {
    
    while (1) {
        
        for (int i = 0; i < numGirls; i++) {
        
            if (girls[i] != NULL) {
               
                mojo->health -= girls[i]->damage;
                
                if (mojo->health <= 0) {
                    printf("MojoJojo a fost invins!\n");
                    return;
                }
            }
        }

        
        int targetIndex = rand() % numGirls;
       
        while (girls[targetIndex] == NULL) {
            targetIndex = rand() % numGirls;
        }
        
        girls[targetIndex]->health -= mojo->damage;
        
        if (girls[targetIndex]->health <= 0) {
          
            free(girls[targetIndex]);
            girls[targetIndex] = NULL;
        }

      
        int allDefeated = 1;
        for (int i = 0; i < numGirls; i++) {
            if (girls[i] != NULL) {
                allDefeated = 0;
                break;
            }
        }
        if (allDefeated) {
            printf("MojoJojo castiga!\n");
            return;
        }
    }
}


void printSurvivingGirls(PowerPuffGirl** girls, int numGirls) {
    int count = 0;
    for (int i = 0; i < numGirls; i++) {
        if (girls[i] != NULL) {
            printf("Fetita %d a supravietuit cu %d viata.\n", i + 1, girls[i]->health);
            count++;
        }
    }
    printf("Au supravietuit %d fetite in total.\n", count);
}

int main() {
   
    srand(time(0));

    
    Profesor prof;
    prof.ingredients[0] = 10; 
    prof.ingredients[1] = 10; 
    prof.ingredients[2] = 10; 
    prof.ingredients[3] = 10; 

    
    PowerPuffGirl* girls[5];
    int numGirls = 0;

 
    for (int i = 0; i < 5; i++) {
        PowerPuffGirl* girl = createRandomPowerPuffGirl(&prof);
       
        if (girl != NULL) {
            girls[numGirls++] = girl;
        }
    }

   
    MojoJojo mojo;
    mojo.damage = 30;
    mojo.health = 300;

    printf("Inceperea bataliei...\n");

    simulateBattle(girls, numGirls, &mojo);

    printf("\nRezultatul bataliei:\n");
  
    printSurvivingGirls(girls, numGirls);

 
    for (int i = 0; i < numGirls; i++) {
        if (girls[i] != NULL) {
            free(girls[i]);
        }
    }
    return 0;
}