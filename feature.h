/*
 * feature.h
 *
 *  Created on: Jul 28, 2023
 *      Author: My Laptop
 */

#ifndef FEATURE_H_
#define FEATURE_H_

#include "app.h"
#include "sl_sleeptimer.h"

struct peak {
  int index;
  float value;
};


float find_std(float a[], int n);
int peak_finding(float data[], int data_length, int window_size, float minpeak, struct peak peaks[]);
double findRMS(double *myArray, int size_arr);
#endif /* FEATURE_H_ */
