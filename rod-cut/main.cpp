//
//  main.cpp
//  rod-cut
//
//  Created by mndx on 26/10/2021.
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "cut_rod.hpp"
#include "cut_rod_ref.hpp"
#include "user_types.hpp"

int main(int argc, char* argv[]) {

    int N = 100; //Total length of the rod
    int *A = new int[N]; //Cost array for the rod

    //Arrays to store solution
    bool *rod_cut_at = new bool[N+1];
    int *cut_counter = new int[N+1];

    //Initialize cost array with random numbers
    srand((unsigned) time(NULL));
    for(int i = 0; i < N; ++i) {
        A[i] = rand() % 4 + (5*i)/2;
    }

    //Get maximum revenue
    int max_rev = get_optimum_solution(N, A, rod_cut_at, cut_counter);

    //Print results
    printf("total length of rod n: %d\n", N);
    printf("total revenue: %d\n", max_rev);
    for(int i = 0; i < N + 1; ++i) {
        if(rod_cut_at[i] == true) {
            printf("rod cut at %i a total of %i times\n", i, cut_counter[i]);
        }
    }

    //Print reference solution
    print_cut_rod_sol(A, N);
    
    //Verify computation
    int total_rev = 0;
    for(int i = 1; i < N + 1; ++i) {
        if(rod_cut_at[i] == true) {
            total_rev = total_rev + cut_counter[i]*A[i-1];
        }
    }

    printf("total revenue verification: %i\n", total_rev);
    printf("done\n");

    return 0;
}
