#include "functions.h"
#include <stdio.h>

float getInput(FILE * ftp)
{
  float input;
  fscanf(ftp, "%f ", &input);
  return(input);
}

float sumWeightedInputs(float input[],float weight[],int n_ip)
{
  float sum = 0;
  int i;
  for(i=0;i<n_ip+1;i++)
  {
  	sum = sum+input[i]*weight[i];
  }
  return(sum);
}

float updateWeights(float weight, float learning_rate, float input, float error)
{
    float new_weight=0;  
    new_weight=weight + (learning_rate * input * error);   
    return(new_weight);
}

int activationFunction(float weighted_sum,float threshold)
{
  if (weighted_sum > threshold)
  {
  	return(1);
  }
  else
  {
  	return(0);
  }
}

float checkOutput(FILE * ftp, float actual_output)
{
  float expected_output = 0;
  float error = 0;
  fscanf(ftp, "%f ", &expected_output);
  printf("\n"); 
  printf("Expected Output: %.2f\n", expected_output);
  printf("Actual Output: %.2f\n", actual_output);
  error = expected_output - actual_output;
  return error;
}
