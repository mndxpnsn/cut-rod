//
//  cut_rod.cpp
//  rod-cut
//
//  Created by mndx on 26/10/2021.
//

#include "cut_rod.hpp"
#include "user_types.hpp"

int max(int a, int b) {
    int dum;
    if(a < b) { dum = b; }
    else { dum = a; }

    return dum;
}

opt_cut_info cut_rod(int n, int A[], t_elem **f_table) {

    if(n == 0) {
        f_table[n]->is_set = true;
        f_table[n]->optimum_cut_info.cut_index = 0;
        f_table[n]->optimum_cut_info.max_rev = 0;

        return f_table[n]->optimum_cut_info;
    }

    if(n == 1) {
        f_table[n]->is_set = true;
        f_table[n]->optimum_cut_info.cut_index = 1;
        f_table[n]->optimum_cut_info.max_rev = A[0];

        return f_table[n]->optimum_cut_info;
    }

    int cut_index = n;
    int val = A[n-1];

    for(int i = 1; i <= n - 1; ++i) {
        if(i <= (n - i)) {
            opt_cut_info dum1, dum2;
            if(f_table[i]->is_set) { dum1 = f_table[i]->optimum_cut_info; }
            else { dum1 = cut_rod(i, A, f_table); }
            if(f_table[n-i]->is_set) { dum2 = f_table[n-i]->optimum_cut_info; }
            else { dum2 = cut_rod(n-i, A, f_table); }

            int dum_int1 = dum1.max_rev;
            int dum_int2 = dum2.max_rev;
            int dum = max(dum_int1 + dum_int2, A[n-1]);

            if(val < dum) {
                val = dum;
                cut_index = i;
            }
        }
    }

    f_table[n]->is_set = true;
    f_table[n]->optimum_cut_info.cut_index = cut_index;
    f_table[n]->optimum_cut_info.max_rev = val;

    return f_table[n]->optimum_cut_info;
}

void delete_memo_table(t_elem **f_table, int n) {

    for(int i = 0; i < n + 1; ++i) {
        delete f_table[i];
    }

    delete [] f_table;
}

int get_optimum_solution(int n, int A[], bool *r, int *cut_counter) {

    //Initialize rod cutting tracker and memo table
    t_elem **f_table = new t_elem*[n+1];

    for(int i = 0; i < n + 1; ++i) {
        r[i] = false;
        f_table[i] = new t_elem;
        f_table[i]->is_set = false;
        cut_counter[i] = 0;
    }

    int NN = n;

    //Cut rod
    while(NN > 0) {
        opt_cut_info cut_info = cut_rod(NN, A, f_table);
        int cut_index = cut_info.cut_index;
        r[cut_index] = true;
        cut_counter[cut_index]++;
        NN = NN - cut_index;
    }

    //Check to see if cut is optimal
    for(int i = 0; i < n + 1; ++i) {
        if(r[i] == true) {
            opt_cut_info cut_info = cut_rod(i, A, f_table);
            int max_rev_loc = cut_info.max_rev;
            if(max_rev_loc != A[i-1]) {
                printf("error, cut not optimal\n");
            }
        }
    }

    //Get max revenue from memo table
    int max_rev = f_table[n]->optimum_cut_info.max_rev;

    delete_memo_table(f_table, n);

    return max_rev;
}
