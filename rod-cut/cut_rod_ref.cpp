//
//  cut_rod_ref.cpp
//  rod-cut
//
//  Created by mndx on 26/10/2021.
//

#include <stdio.h>

#include "cut_rod_ref.hpp"

void ext_bu_cut_rod(int p[], int n, int r[], int s[]) {
    r[0] = 0;
    for(int j = 1; j <= n; ++j) {
        double q = -3e+8;
        for(int i = 1; i <= j; ++i) {
            if(q < p[i-1] + r[j-i]) {
                q = p[i-1] + r[j-i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
}


void print_cut_rod_sol(int p[], int n) {
    int *s = new int[n + 1];
    int *r = new int[n + 1];

    ext_bu_cut_rod(p, n, r, s);

    bool* r_ver = new bool[n + 1];
    int* cut_counter = new int[n + 1];

    for(int i = 0; i < n + 1; ++i) {
        r_ver[i] = false;
        cut_counter[i] = 0;
    }

    int m = n;
    printf("reference solution:\n");
    while(m > 0) {
        r_ver[s[m]] = true;
        cut_counter[s[m]]++;
        m = m - s[m];
    }

    for(int i = 0; i < n + 1; ++i) {
        if(r_ver[i] == true) {
            printf("rod cut at %i a total of %i times\n", i, cut_counter[i]);
        }
    }

    printf("optimum revenue: %i\n", r[n]);
}
