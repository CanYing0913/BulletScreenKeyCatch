/**
 * @file zalg.cpp
 * Code to create Z-array and use Z-algorithm for exact pattern matching.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "zalg.h"

/**
 * Returns the number of individual character comparisons used by the Z-algorithm
 * Also modifies the input (empty) zArray to store the Z-value at each position i<0
 *
 * @param S A std::string object which holds the String being analyzed.
 * @param Z An int* that points to a length |S| int[] which holds the zArray.
 *
 * @return An integer counting the number of character comparisons needed to make the Z-array.
 */
int create_zarray(std::string S, int* Z) {
  int charComps = 0; //the number of character comparisons needed to make the Z-array

  int l, r = 0;
  for(int index = 0; index < (int)S.length() - 1; index++){
    // Case 1: i+1>r, calculate Z_i+1 explicitly.
    if(index + 1 > r){
      int z;
      for(z = 0; z < (int)S.length() - index - 1; z++){
        if(S[z] != S[index + 1 + z]){
          break;
        }
      }
      Z[index + 1] = z;
      charComps += z + 1;
      if(z > 0){
        l = index + 1;
        r = index + z;
      }
    }
    // Case 2: i+1<=r, divide the task to 3 situations.
    else{
      int k = index + 1 - l;
      int Zk = Z[k];
      int Beta = r - index;
      // Case 2.a: Zk < Beta, Z_i+1 = Z_i.
      if(Zk < Beta){
        Z[index + 1] = Zk;
      }
      // Case 2.b: Zk = Beta, Z_i+1 = Z_i + count.
      else if(Zk == Beta){
        int extra;
        for(extra = 0; extra < (int)S.length() - r - 1; extra++){
          if(S[Beta + extra] != S[r + extra + 1]){
            break;
          }
        }
        Z[index + 1] = Zk + extra;
        charComps += extra + 1;
        if(extra > 0){
          l = index + 1;
          r = index + Z[index + 1];
        }
      }
      // Case 2.c: Zk > Beta, Z_i+1 = Beta.
      else
      {
        Z[index + 1] = Beta;
      }
    }
  }
  
  return charComps;
}

/**
 * Returns the index positions of all exact matches of P in T.
 * If no match is found, returns a vector with one value '[-1]'
 * NOTE: We want the exact matches *in T* not string S.
 *
 * Search the Text string (T) for the Pattern string (P)
 * For example, if P = 'AAA' and T = 'BAAAT', will return 1
 *
 * @param P A std::string object which holds the Pattern string.
 * @param T A std::string object which holds the Text string.
 *
 * @return An std::vector<int> array containing ALL index matches.
 */
std::vector<int> zalg_search(std::string P, std::string T) {
  std::vector<int> outList;
  
  // NOTE: You should change this function as necessary to complete the assignment.
  std::string S = P+"$"+T;
  
  int *zarr = new int[S.length()];

  int charComps = create_zarray(S, zarr);

  //std::cout << "charComps (search): " << charComps << std::endl;
  
  // Get index(s) from T instead of S
  for(int i = P.length() + 1; i < (int)S.length(); i++){
    if(zarr[i] >= (int)P.length()){
      outList.push_back(i - P.length() - 1);
    }
  }

  // No need to edit this line but you will need to add code to deal with the non-empty case
  if(outList.empty()){ // bool empty() const; returns if my dynamic array is empty.
    outList.push_back(-1); //push_back appends (adds) a value to the end of a dynamic array
  }

  delete[] zarr; // No memory leaks here!
  return outList;
}