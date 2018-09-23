#include <stdio.h>
float getInput(FILE * ftp);
float sumWeightedInputs(float input[],float weight[],int n_ip);
float updateWeights(float weight, float learning_rate, float input, float error);
int activationFunction(float weighted_sum,float threshold);
float checkOutput(FILE * ftp, float actual_output);
