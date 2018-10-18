//
// Created by user on 18.10.2018.
//

#ifndef FUNFEL_ROUND_SHIFT_TABLE_H
#define FUNFEL_ROUND_SHIFT_TABLE_H


const int round_shift_table[16]= {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,};
static const int recipe_for_expansion[]= {31,0,1,2,3,4,3,4,5,6,7,8,7,8,9,10,11,12,11,12,13,14,15,16,15,16,17,18,19,20,19,20,21,22,23,24,23,24,25,26,27,28,27,28,29,30,31,0};
static const int recipe_for_compresion[]= {13,16,10,23,0,4,2,27,14,5,20,9,22,18,11,3,25,8,15,6,26,19,12,1,40,51,30,36,46,54,29,39,50,44,32,47,43,48,38,55,33,52,45,41,49,35,28,31};
#endif //FUNFEL_ROUND_SHIFT_TABLE_H
