# YIN_pitch_detection

## Synopsis

This project is an implementation of the YIN Method for Pitch detection, as described in the paper "YIN, a fundamental frequency estimator for speech and music," by Alain de Cheveigne and Hideki Kawahara (2002). This program is tuned to find pitch values for instruments within the range 0 - 5000Hz. 

This program does not follow the exact method in the paper. Step 5, parabolic interpolation is skipped due to the frequency range being fairly small compared to the sampling rate of the recordings.

The program outputs a .out file which has frequencies for each window.

## Motivation

The motivation of this project was to program a robust pitch detection algorithm for the SNDAN music analysis command line tool.

## Installation

In order to compile this project, you will need to install the library "libsndfile," which can be found at http://www.mega-nerd.com/libsndfile/.

## Log:
April 19, 2016: YIN Method steps 1-4 completed. 
