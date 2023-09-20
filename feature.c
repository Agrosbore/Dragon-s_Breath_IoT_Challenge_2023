/*
 * feature.c
 *
 *  Created on: Jul 28, 2023
 *      Author: My Laptop
 */
#include "feature.h"
#include <stdio.h>
#include <math.h>
#include "app.h"

int breath = 0;


float find_std(float a[], int n) {
  float sum1 = 0;
  float sum2 = 0;
  float tb1, tb2, std;
  for(int i = 0; i < n; i++) {
    sum1 += a[i];
  }
  tb1 = sum1 / n;
  for(int i = 0; i < n; i++) {
    sum2 += pow((a[i] - tb1), 2);
  }
  tb2 = sum2 / n;
  std = sqrt(tb2);
  return std;
}

int peak_finding(float data[], int data_length, int window_size, float minpeak, struct peak peaks[]) {
  int num_peaks = 0;

  int extended_length = data_length + 2*window_size;
  float *data_extended = (float*)malloc((2*window_size + data_length) * sizeof(float));
  memset(data_extended, 0, extended_length * sizeof(float));
  memcpy(data_extended + window_size, data, data_length * sizeof(float));


  int max_index[extended_length];
  float max_var[extended_length];
  float std_ = find_std(data, data_length);
  int count = 0;
  for(int i = window_size; i < extended_length - window_size; i++) {
    float check_value = -1.0;
    // Calculate left and right maximum values
    float max_left = 0.0;
    for(int j = i - window_size; j <= i; j++) {
      if(data_extended[j] > max_left) {
        max_left = data_extended[j];
      }
    }
    float max_right = 0.0;
    for(int j = i; j <= i + window_size; j++) {
      if(data_extended[j] > max_right) {
        max_right = data_extended[j];
      }
    }
    // Check if the value is a peak
    if(data_extended[i] > std_ + minpeak) {
      check_value = data_extended[i] - (max_left + max_right)/2.0;
    }
    // Add peak to list
    if(check_value >= 0.0) {
      max_index[count] = i - window_size;
      max_var[count] = data[i - window_size];
      count++;
    }
  }
  // Copy peaks to output struct
  num_peaks += count;
  for(int i = 0; i < count; i++) {
    peaks[i].index = max_index[i];
    peaks[i].value = max_var[i];
  }
  // dem la danh giau 1 phut
  // Breath: so nhip tho trong 1 phut
  //if (DEM == 28 ){
       //printf("\n dem = %d \n", DEM);
      // printf("\n NHIP THO MOT PHUT LA %d \n", breath);
      // return 0;
     //  }
   //   printf("NHIP THO LA %d\n", breath);

//   if (DEM >=16){
//       DEM = 0;
//   }
//   DEM = 0;
   free(data_extended);
   return breath;

}

double findRMS(double *myArray, int size_arr)
{
  double rms = 0;
  for(int i = 0;i< size_arr;i++)
  {
    rms+=pow(myArray[i],2);
  }
  rms= sqrt(rms/size_arr);
  return rms;
}
