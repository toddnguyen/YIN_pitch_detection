# YIN_pitch_detection

## Synopsis

This project is an implementation of the YIN Method for Pitch detection, as described in the paper "YIN, a fundamental frequency estimator for speech and music," by Alain de Cheveigne and Hideki Kawahara (2002). This program is tuned to find pitch values for instruments.

This program does not follow the exact method in the paper. Step 5, parabolic interpolation is skipped due to the frequency range being fairly small compared to the sampling rate of the recordings. Step 6 is also omitted due to the large increase in computation time and the relatively small accuracy increase.

The pitchdetection program outputs a .ff file which can be read by the included pitchit program. The program also outputs a .out file which has frequencies for each window if the "DEBUG" Define is set to one. The .out file is a line separated value list which can be read in Excel or Matlab.

More information for this project is in the Nguyen_YIN_paper.pdf file, which is included in the repository.

## Motivation

This goal of this project is to find a fast and robust method for pitch detection to replace the Two-Way Mismatch method of pitch detection currently implemented in the SNDAN Audio Processing suite. I chose to do an autocorrelative method because of its high accuracy without smoothing. Autocorrelation methods also have relatively good accuracy with pitch detection, however the autocorrelation method has relatively low accuracy for voiced/unvoiced pitches. The YIN method is based on the autocorrelation method with six add on features in order to improve accuracy. According to the paper by de Cheveigne, the YIN method’s six add-ons improve the error rate from 17% to 0.5%.

## Installation

In order to compile this project, you will need to install the library "libsndfile," which can be found at http://www.mega-nerd.com/libsndfile/. Minor change might need to be made to the Makefile, including deleting the dependencies after the last comment.

## Included files:
pitchdetection.c/h: Main program
autocorrelation.c/h: Method for finding pitch of frame, outputs a frequency value.

header.h/c: Contains information for .ff files
byteorder.h/c: Code for reading endinanness of architecture and byte-swapping if necessary

Nguyen_YIN_paper.pdf: Paper detailing project, also has list of references.

Sample Files:
leonard_output.ff: Output from pitchdetection program, ready to be read in pitchit.
leonard.16.wav: Saxophone recording
tenor.wav: Tenor voice recording
