//
//  user_types.hpp
//  rod-cut
//
//  Created by mndx on 26/10/2021.
//

#ifndef user_types_h
#define user_types_h

typedef struct optimum_cut_info {
    int cut_index;
    int max_rev;
} opt_cut_info;

typedef struct table_element {
    bool is_set;
    opt_cut_info optimum_cut_info;
} t_elem;

#endif /* user_types_h */
