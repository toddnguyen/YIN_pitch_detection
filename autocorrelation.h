#ifndef _AUTOCORRELATION_H
#define _AUTOCORRELATION_H

#include <sndfile.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <math.h>


float pitch_detect(int * frame, int length, int samplerate);

#endif /* _AUTOCORRELATION_H */
