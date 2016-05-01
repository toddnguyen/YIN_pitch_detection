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

//Frame size (Currently set to 6ms)
#define FRAMESIZE 0.006

int main(int argc, char **argv){

    if (argc != 2){
        puts ("    Usage : ./pitchdetection <Sound File>");
        puts ("    <Sound File> should be a mono audio file in format .snd or .wav\n");
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


    /* Create file/get file descriptor for output .ff file */
    //FILE * ffoutput = fopen("output.ff", "w+");
    char file[] = "output.ff";

    /* Fill in header */
    HEADER temp_header;
    temp_header.performer = "Neil Leonard";     /* name of performer                        */
    temp_header.instrument = "alto saxophone";    /* instrument used                          */
    temp_header.date = "1998";          /* date of recording                        */
    temp_header.pitch = "??";         /* pitch played                             */
    temp_header.dyn = "??";           /* dynamic level                            */
    temp_header.vibra = "NO";         /* vibrato (YES/NO)                         */
    temp_header.part = "all";          /* portion of tone (beg., middle, end, all) */
    temp_header.type = "full";          /* "full" or "compressed" data format       */
    temp_header.comments = "special cadenza passage improvised";      /* additional comments                      */
    temp_header.andate = "a";        /* date of analysis, if analysis file       */
    temp_header.interpval = 0.006;     /* analysis reinterp. factor                */
    temp_header.sr = samplerate;            /* signal sample rate                       */
    temp_header.tl = (float)num_samples/samplerate;            /* tone length, seconds                     */
    temp_header.smax = 10000;           /* max. amplitude of input signal           */
    temp_header.fa = 0;            /* fundamental freq. assumed in analysis    */
    temp_header.dt = 0.006;            /* time between analysis blocks, seconds    */
    temp_header.fftlen = 256;        /* analysis block size                      */
    temp_header.nhar = 3;          /* number of harmonics                      */
    temp_header.nchans = 1;        /* number of channels recorded              */
    temp_header.npts = numframes;          /* number of analysis blocks                */

    int fd = creat(file,0644);
    //int outputfd = fileno(ffoutput);
    wdat(fd, &temp_header);

    int byte_reverse = byte_order();


    /* Go through each frame, find fundamental frequency */
    int remaining_samples = num_samples;
    for(i = 0; i < numframes-2; i++){
        int length = framesize;
        if(remaining_samples < framesize){
            length = remaining_samples;
        }
        pitches[i] = (float)pitch_detect(&(buf[framesize*i]), length, samplerate);
        printf("%f\n", pitches[i]);


        // write(outputfd, &pitches[i], sizeof(float));

        remaining_samples -= length;
    }
    // fclose(ffoutput);

    /* If debugging is enabled, write output file with list of all frequencies*/
    #ifdef DEBUG

    FILE * pitch_output;
    pitch_output = fopen("pitch_output.out","w+");
    for (i = 0; i < numframes; i ++){
        fprintf(pitch_output,"%f ",pitches[i]);
        fprintf(pitch_output,"\n");
    }
    fclose(pitch_output);

    #endif

    for(i = 0; i < numframes; i++){
        if(byte_reverse){
            byteswap4((int*)pitches+i);
        }
        write(fd, &pitches[i], sizeof(float));
    }
    close(fd);
    // int testbuflength = numframes;
    // float * testbuf = (float *) malloc(testbuflength*sizeof(float));
    // memset(testbuf, (float)440, testbuflength*sizeof(float));
    // fwrite(testbuf, sizeof(float), testbuflength*sizeof(float), ffoutput);

    /* Write pitches to .ff file */
    // if(fwrite(pitches, sizeof(float), numframes*sizeof(float), ffoutput) < numframes*sizeof(float)){
    //     printf("Error in writing file\n");
    // }

    /* Close file, free memory */

    free(buf);
    free(pitches);

    return 0;
}
