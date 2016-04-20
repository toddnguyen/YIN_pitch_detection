#include <sndfile.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "autocorrelation.h"
#include "header.h"

int main(int argc, char **argv){

    if (argc != 2){
        puts ("    Usage : ./pitchdetection <Sound File>");
        puts ("    <Sound File> should be a mono audio file in format .snd or .wav\n");
        exit (1) ;
    } ;

    SNDFILE *sf;
    SF_INFO info;
    int num, num_items;
    int *buf;
    int num_samples,samplerate,c;
    int i;
    int format;

    /* Open the WAV file. */
    info.format = 0;
    //sf = sf_open("file.wav",SFM_READ,&info);
    sf = sf_open(argv[1],SFM_READ,&info);

    if (sf == NULL){
        printf("Failed to open the file.\n");
        exit(-1);
    }


    /* Print some of the info, and figure out how much data to read. */
    num_samples = info.frames;
    samplerate = info.samplerate;
    c = info.channels;
    format = info.format;

    switch(format & 0x0F0000){
        case SF_FORMAT_WAV:
        printf("Filetype: wav\n");
        break;

        case SF_FORMAT_AU:
        printf("Filetype: snd\n");
        break;

        default:
        printf("Not a valid sound file type (use .wav or .snd)\n");
        exit(1);
    }

    if(c != 1){
        printf("Not valid sound file. Please use mono files only.\n");
        exit(1);
    }

    printf("# of samples = %d\n",num_samples);
    printf("samplerate = %d\n",samplerate);
    printf("channels = %d\n",c);
    num_items = num_samples*c;
    printf("num_items = %d\n",num_items);
    /* Allocate space for the data to be read, then read it. */
    buf = (int *) malloc(num_items*sizeof(int));
    num = sf_read_int(sf,buf,num_items);
    sf_close(sf);
    printf("Read %d items\n",num);


    /* Set framesize to 6ms */
    int framesize = 0.006*samplerate;
    printf("Frame Size= %d Samples\n",framesize);


    /* Allocate buffer to hold pitches for each frame */
    int numframes = ceil((double)num_samples/framesize);
    printf("Number of frames = %d\n",numframes);
    int * pitches = (int *) malloc(numframes*sizeof(int));
    memset(pitches, 0, numframes*sizeof(int));


    /* Go through each frame, find fundamental frequency */
    int remaining_samples = num_samples;
    for(i = 0; i < numframes-2; i++){
        int length = framesize;
        if(remaining_samples < framesize){
            length = remaining_samples;
        }
        pitches[i] = pitch_detect(&(buf[framesize*i]), length, samplerate);

        remaining_samples -= length;
    }


    /* Write Output file */
    FILE * pitch_output;
    pitch_output = fopen("pitch_output.out","w");
    for (i = 0; i < numframes; i ++){
        fprintf(pitch_output,"%d ",pitches[i]);
        fprintf(pitch_output,"\n");
    }
    fclose(pitch_output);


    free(buf);
    free(pitches);

    return 0;
}
