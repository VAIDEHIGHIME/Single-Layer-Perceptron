#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "functions.h"

#define THRESHOLD 0
#define DATA_FILE "training_dataset.txt"
#define WT_FILE "output_file.txt"
#define TEST_FILE "testing_dataset.txt"
#define TEST_FILE_O "original_test.txt"
#define LEARNING_RATE 0.2
#define NO_OF_INPUTS 4
#define TEST_SAMPLES 10

// NOTE: bias is set to 1 and the inputs are augmented

int main(void)
{
    float input[NO_OF_INPUTS+1];
    float weight[NO_OF_INPUTS+1];   
    int i;
    int j;
    int epoch=1;
    float dot_product = 0;
    int actual_output = 0;
    float error = 0;
    bool incorrectClassifications = true;
    FILE * file_pointer_i = fopen(DATA_FILE, "r");
    FILE * file_pointer_w = fopen(WT_FILE, "w+");
    FILE * file_pointer_t = fopen(TEST_FILE,"r");
    FILE * file_pointer_ot = fopen(TEST_FILE_O,"r");

    int passed_test=0;
    int tar_test_op;
    float accuracy;
    if (file_pointer_i == NULL)
    {
        printf("Cannot open training data file.\n");
        printf( "Check permissions for data file.\n");
        exit(1);
    }    
    if (file_pointer_w == NULL)
    {
        printf( "Cannot open wt updation file.\n");
        printf("Check permissions for data file.\n");
        exit(1);
    }  
    if (file_pointer_t == NULL)
    {
        printf("Cannot open test file.\n");
        printf( "Check permissions for data file.\n");
        exit(1);
    }  
    if (file_pointer_ot == NULL)
    {
        printf("Cannot open  output test file.\n");
        printf( "Check permissions for data file.\n");
        exit(1);
    }    
    for(i=0;i<NO_OF_INPUTS+1;i++)
    {
	input[i]=0.0;
	weight[i]=0.0;
    }
    printf("PERCEPTRON TRAINING ALGORITHM IMPLEMENTATION\n");

    while(incorrectClassifications == true && epoch==1)
    {	
        incorrectClassifications = false;
        j= 1;
        while(1)
        {  
	    	    
            for(i=0;i<NO_OF_INPUTS+1;i++)
	    {
		input[i] = getInput(file_pointer_i);
    	    }
	    if(input[0]==999)
	    {
		break;
	    }
            dot_product = sumWeightedInputs(input,weight,NO_OF_INPUTS+1);
            actual_output = activationFunction(dot_product,THRESHOLD);
            printf("epoch:%d\n",epoch);
            printf("Data Set %d\n", j);
	    fprintf(file_pointer_w,"Epoch:%d\t",epoch);
            fprintf(file_pointer_w,"Dataset:%d\t",j);
            printf("\n"); 
            for(i=0;i<NO_OF_INPUTS+1;i++)
    	    {
		printf("Input %d = %.2f\n",i,input[i]);
    	    }
            printf("\n"); 
            for(i=0;i<NO_OF_INPUTS+1;i++)
    	    {
		printf("Weight %d = %.2f\n",i,weight[i]);
    	    }
            fprintf(file_pointer_w,"old_wt\t"); 
	    for(i=0;i<NO_OF_INPUTS+1;i++)
            {
	        fprintf(file_pointer_w,"%.2f\t",weight[i]);
            }
            fprintf(file_pointer_w,"\t\t"); 
            printf("\n"); 
            printf("Summation = %.2f\n", dot_product);
            printf("Object classified to class %d.\n", actual_output);
            error = checkOutput(file_pointer_i,actual_output);
            if (error == 0) 
	    {
		printf("Ouput correct.\n");
		
	    }
            else
            {
                incorrectClassifications = true;
                printf("Output incorrect.\n");
                printf("Error = %.0f\n", error);
                for(i=0;i<NO_OF_INPUTS+1;i++)
    	        {
		    weight[i]=updateWeights(weight[i],LEARNING_RATE,input[i],error);
    	        }
                printf("\n");
                printf("NEW WEIGHTS: \n");
                for(i=0;i<NO_OF_INPUTS+1;i++)
    	        {
		   printf("*** New weight %d: %.2f\n",i,weight[i]);
    	        }
            } 

	        


            printf("\n");
            printf("-----------------------------------------------\n");
            printf("-----------------------------------------------\n\n");


	    
	    fprintf(file_pointer_w,"new_wt\t"); 
	    for(i=0;i<NO_OF_INPUTS+1;i++)
            {
	        fprintf(file_pointer_w,"%.2f\t",weight[i]);
            }
	    fprintf(file_pointer_w,"\n");
            j++;
            sleep(1); 
        } 
	epoch++;
        rewind(file_pointer_i);
    } 
    printf("\n");
    printf("Final Weights: \n");
    for(i=0;i<NO_OF_INPUTS+1;i++)
    {
    	printf("*** Final weight %d: %.2f\n",i,weight[i]);
    }
    

    for(i=0;i<NO_OF_INPUTS+1;i++)
    {
	input[i]=0;
    }
    //let us predict
    printf("let us predict\n");
    j=0;
    while(j<TEST_SAMPLES)
    {
	    for(i=0;i<NO_OF_INPUTS+1;i++)
	    {
		input[i] = getInput(file_pointer_t);
	    }
	    if(input[0]==999)
	    {
		break;
	    }
	    for(i=0;i<NO_OF_INPUTS+1;i++)
    	    {
		printf("Input %d = %.2f\t",i,input[i]);
    	    }
	    dot_product = sumWeightedInputs(input,weight,NO_OF_INPUTS+1);
	    actual_output = activationFunction(dot_product,THRESHOLD);
	    tar_test_op=getInput(file_pointer_ot);
	    printf("Predicted output:%d\t",actual_output);
	    fprintf(file_pointer_w,"\nPredictes:\n");
            for(i=0;i<NO_OF_INPUTS+1;i++)
    	    {
		fprintf(file_pointer_w,"Input %d = %.2f\t",i,input[i]);
    	    }
	    fprintf(file_pointer_w,"Prediction:%d",actual_output);
            if(actual_output== tar_test_op)
            {
     	        fprintf(file_pointer_w,"correct");
                printf("correct\n");
		passed_test++;
	     }
	     else
	     {
	         fprintf(file_pointer_w,"incorrect");
		 printf("incorrect\n");
             }
	    j++;
    }  
    accuracy= ((float)passed_test/(float)TEST_SAMPLES)*100; 
    printf("\n\naccuracy::%f",accuracy);
    fprintf(file_pointer_w,"\n\naccuracy::%f",accuracy);
    fclose(file_pointer_i);
    fclose(file_pointer_w);
    fclose(file_pointer_t);
    fclose(file_pointer_ot);
    return(0);
}
