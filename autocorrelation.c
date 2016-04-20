#include "autocorrelation.h"

#define TRESHOLD 0.1

double pitch_detect(int * frame, int length, int samplerate){

    int W = length;
    int i,t,j;


    /** Step 0: Detect silence **/


    /** Step 1: Autocorrelate **/
    // long * acf = (long *) malloc(length*sizeof(long));
    // memset(acf, 0, length*sizeof(long));
    //
    // for(t = 0; t < length; t++){
    //     for(j = 1; j < W-t; j++){
    //         acf[t] += (long)frame[j]*frame[j+t];
    //         // printf("%ld\n", (long)frame[j]*frame[j+t]);
    //     }
    // }
    //
    // int maxima = W-1;
    // //Find largest Local Maxima
    // for(i = 1; i < W-1; i++){
    //     if(acf[i] >= fmax(acf[i-1], acf[i+1]) && acf[i] > acf[maxima]){
    //         maxima = i;
    //     }
    // }

    // FILE * acf_output;
    // acf_output = fopen("acf_output.out","w");
    // for (i = 0; i < length; i ++){
    //     fprintf(acf_output,"%ld ",acf[i]);
    //     fprintf(acf_output,"\n");
    // }
    // fclose(acf_output);


    /** Step 2: Generate Difference Function **/
    double * difference = (double *) malloc(length*sizeof(double));
    memset(difference, 0, length*sizeof(double));

    for(t = 0; t<length; t++){
        for(j = 1; j < W+1; j++){
            difference[t] += pow(((double)frame[j]-frame[j+t]),2);
        }
    }


    /** Step 3: Cumulative Normalized Difference Mean **/
    double * cmndifference = (double *) malloc(length*sizeof(double));
    memset(cmndifference, 0, length*sizeof(double));

    for(t = 0; t<length; t++){
        if(t == 0){
            cmndifference[t] = 1;
        }
        else{
            double denominator = 0;
            for(j = 1; j < t+1; j++){
                denominator += difference[j];
            }
            denominator /= t;
            if(denominator != 0){
                cmndifference[t] = difference[t]/denominator;
            }
            else{
                cmndifference[t] = 1;
            }

        }
    }


    /** Step 4: Aboslute Threshold **/
    int minima = 999999;
    //Find smallest min below threshold
    for(i = 1; i < W-1; i++){
        if(cmndifference[i] <= fmin(cmndifference[i-1], cmndifference[i+1]) && cmndifference[i] <= TRESHOLD){
            minima = i;
            break;
        }
    }

    // free(acf);
    free(difference);
    free(cmndifference);

    return samplerate/minima;
}
