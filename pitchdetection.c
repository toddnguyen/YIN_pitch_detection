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
    HEADER ffheader;
    int num, num_items;
    int *buf;
    int num_samples,samplerate,c;
    int i;
    int format;

    /* Fill in header */
    char *performer = "test";     /* name of performer                        */
    char *instrument = "instrument";    /* instrument used                          */
    char *date = "date";          /* date of recording                        */
    char *pitch = "pitch";         /* pitch played                             */
    char *dyn = "f";           /* dynamic level                            */
    char *vibra = "NO";         /* vibrato (YES/NO)                         */
    char *part = "all";          /* portion of tone (beg., middle, end, all) */
    char *type = "full";          /* "full" or "compressed" data format       */
    char *comments = "";      /* additional comments                      */
    char *andate = "Jan";        /* date of analysis, if analysis file       */
    float  interpval;     /* analysis reinterp. factor                */
    float  sr;            /* signal sample rate                       */
    float  tl;            /* tone length, seconds                     */
    float  smax;          /* max. amplitude of input signal           */
    float  fa;            /* fundamental freq. assumed in analysis    */
    float  dt;            /* time between analysis blocks, seconds    */
    int  fftlen;        /* analysis block size                      */
    int  nhar;          /* number of harmonics                      */
    int  nchans;        /* number of channels recorded              */
    int  npts;          /* number of analysis blocks                */


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
    float * pitches = (float *) malloc(numframes*sizeof(float));
    memset(pitches, 0, numframes*sizeof(float));


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
        fprintf(pitch_output,"%f ",pitches[i]);
        fprintf(pitch_output,"\n");
    }
    fclose(pitch_output);


    free(buf);
    free(pitches);

    return 0;
}
