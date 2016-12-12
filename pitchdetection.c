#include <sndfile.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "autocorrelation.h"
#include "header.h"
#include "byteorder.h"
#include <fcntl.h>

//Change this to 1 to enable debugging features
#define DEBUG 0

//Frame size (Currently set to 15ms)
#define FRAMESIZE 0.015

int main(int argc, char **argv){

    if (argc != 3){
        puts ("    Usage : ./pitchdetection <Sound File> <Output>");
        puts ("    <Sound File> should be a mono audio file in format .snd or .wav\n");
        puts ("    <Output> should be a file in format .ff\n");
        exit (1) ;
    } ;

    //Variables for libsndfile
    SNDFILE *sf;
    SF_INFO info;
    //HEADER ffheader;
    int num, num_items;
    int *buf;
    int num_samples,samplerate,c;
    int i;
    int format;

    printf("------ Reading File: %s ------\n", argv[1]);

    /* Open the WAV file. */
    info.format = 0;
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

    printf("File Read Successful\n");
    /* Determine the file format and print it out to terminal */
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

    /* If stereo recording, end program. */
    if(c != 1){
        printf("Not valid sound file. Please use mono files only.\n");
        exit(1);
    }


    /* If a valid sound file, print out some information about it */
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
    int framesize = FRAMESIZE*samplerate;
    printf("Frame Size= %d Samples\n",framesize);


    /* Allocate buffer to hold pitches for each frame */
    int numframes = ceil((double)num_samples/framesize);
    printf("Number of frames = %d\n",numframes);
    float * pitches = (float *) malloc(numframes*sizeof(float));
    memset(pitches, 0, numframes*sizeof(float));


    printf("------ Starting Pitch Analysis ------ \n");
    /* Go through each frame, find fundamental frequency */
    int remaining_samples = num_samples;
    for(i = 0; i < numframes-2; i++){
        int length = framesize;
        if(remaining_samples < framesize){
            length = remaining_samples;
        }
        pitches[i] = (float)pitch_detect(&(buf[(int)(framesize*i)]), length, samplerate);

        remaining_samples -= length;
    }
    printf("Analysis Completed\n");


    /* If debugging is enabled, write output file with list of all frequencies*/
    #if DEBUG
    printf("------ Creating debug file pitch_output.out ------\n");
    FILE * pitch_output;
    pitch_output = fopen("pitch_output.out","w+");
    for (i = 0; i < numframes; i ++){
        fprintf(pitch_output,"%f ",pitches[i]);
        fprintf(pitch_output,"\n");
    }
    fclose(pitch_output);
    #endif


    /* Create file/get file descriptor for output .ff file */
    printf("------ Creating Output File: %s ------\n", argv[2]);
    char * file = argv[2];

    char performer[32];
    char instrument[32];
    char date[32];
    char vibra[32];
    char part[32];
    char comments[64];

    printf("Write the name of the performer, then hit enter:\n");
    fgets(performer, 31, stdin);
    printf("Write the instrument used, then hit enter:\n");
    fgets(instrument, 31, stdin);
    printf("Write the date of recording, then hit enter:\n");
    fgets(date, 31, stdin);
    printf("Is vibrato used? Answer (YES/NO), then hit enter:\n");
    fgets(vibra, 31, stdin);
    printf("Write the part played (beg, middle, end, all), then hit enter:\n");
    fgets(part, 31, stdin);
    printf("Write any additional comments, then hit enter:\n");
    fgets(comments, 63, stdin);

    /* Fill in header */
    HEADER temp_header;
    temp_header.performer = performer;     /* name of performer                        */
    temp_header.instrument = instrument;    /* instrument used                          */
    temp_header.date = date;          /* date of recording                        */
    temp_header.pitch = "N/A";         /* pitch played                             */
    temp_header.dyn = "N/A";           /* dynamic level                            */
    temp_header.vibra = vibra;         /* vibrato (YES/NO)                         */
    temp_header.part = part;          /* portion of tone (beg., middle, end, all) */
    temp_header.type = "full";          /* "full" or "compressed" data format       */
    temp_header.comments = comments;      /* additional comments                      */
    temp_header.andate = "N/A";        /* date of analysis, if analysis file       */
    temp_header.interpval = FRAMESIZE;     /* analysis reinterp. factor                */
    temp_header.sr = samplerate;            /* signal sample rate                       */
    temp_header.tl = (float)num_samples/samplerate;            /* tone length, seconds                     */
    temp_header.smax = 10000;           /* max. amplitude of input signal           */
    temp_header.fa = 0;            /* fundamental freq. assumed in analysis    */
    temp_header.dt = FRAMESIZE;            /* time between analysis blocks, seconds    */
    temp_header.fftlen = 0;        /* analysis block size                      */
    temp_header.nhar = 0;          /* number of harmonics                      */
    temp_header.nchans = 1;        /* number of channels recorded              */
    temp_header.npts = numframes;          /* number of analysis blocks                */

    printf("------ Writing Output File: %s ------\n", argv[2]);

    int fd = creat(file,0644);
    wdat(fd, &temp_header);

    int byte_reverse = byte_order();
    for(i = 0; i < numframes; i++){
        if(byte_reverse){
            byteswap4((int*)pitches+i);
        }
        if(write(fd, &pitches[i], sizeof(float)) < sizeof(float)){
            printf("Write error, ending program. \n");
            exit(1);
        }
    }
    close(fd);

    printf("Write Completed\n");

    /* Free memory */
    free(buf);
    free(pitches);

    return 0;
}
