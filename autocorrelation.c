#include "autocorrelation.h"

double pitch_detect(int * frame, int length, int samplerate){

    /** Step 1: Autocorrelate **/
    long * acf = (long *) malloc(length*sizeof(long));
    memset(acf, 0, length*sizeof(long));

    int W = length;

    int i,t,j;
    for(t = 0; t < length; t++){
        for(j = 1; j < W-t; j++){
            acf[t] += (long)frame[j]*frame[j+t];
            // printf("%ld\n", (long)frame[j]*frame[j+t]);
        }
    }

    int maxima = W-1;
    //Find largest Local Maxima
    for(i = 1; i < W-1; i++){
        if(acf[i] > fmax(acf[i-1], acf[i+1]) && acf[i] > acf[maxima]){
            maxima = i;
        }
    }

    // printf("Maxima : %d\n", maxima);

    FILE * acf_output;
    acf_output = fopen("acf_output.out","w");
    for (i = 0; i < length; i ++){
        fprintf(acf_output,"%ld ",acf[i]);
        fprintf(acf_output,"\n");
    }
    fclose(acf_output);

    /** Step 2: Generate Difference Function **/

    /** Step 3: Cumulative Normalized Difference Mean **/




    free(acf);

    //lags/samplingrate = seconds * lags
    return samplerate/maxima;
}
