#include "functions.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "round_shift_table.h"
#include "Sbox.h"
#include "round_shift_table.h"
static const char ALFABET [] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
using namespace std;

char * OpenAndReturnText(const char * file_name, int & length_tab ) {
    const int EXPECTED_SIZE_TEXT =100;
    fstream file;
    char temp_tab[EXPECTED_SIZE_TEXT];
    file.open(file_name);

    if(!file.is_open()) {
        cout << "can not open file " << endl;
        exit(EXIT_FAILURE);
    }
    else {
        while (file.get(temp_tab[length_tab]) && length_tab < EXPECTED_SIZE_TEXT-1)
        {
            ++length_tab;
        }
        file.clear();
        temp_tab[length_tab]='\0';
        char * plain_text= new char[length_tab+1];
        int i=0;
        while (temp_tab[i]!='\0') {
            plain_text[i]=temp_tab[i];
            ++i;
        }
        plain_text[i]='\0';
        return plain_text;
    }
}

void    Sign8ToBinary (char tab_8chars[], int *binary_tab_for_8chars) {
    int next_adrres_8bit_tab=0;
    for (int i=0; i<8; i++ ) {
        if(tab_8chars[i]==0)
            break;
        SignToBinary(tab_8chars[i],&binary_tab_for_8chars[next_adrres_8bit_tab]);
        next_adrres_8bit_tab+=8;
    }
}

void    SignToBinary (char sign, int *binary_s) {
    // zemieniam assci do naszego alfabetu
    if(sign==' ')
        sign=26;
    else
        sign-=65;

    for (int i=7 ; i>=0; i--) {
        if(sign==0)
            break;
        binary_s[i]=sign%2;
        sign =(sign-binary_s[i])/2;
    }
}

char    BinaryToSign (int Binary_sign[]) {
    char temp=0;
    int Position_tab =7;
    for (int power2=0; power2<=7; power2++) {
        temp+=Binary_sign[Position_tab]*pow(2,power2);
        --Position_tab;
    }
    return temp;
}

void    BinaryToText (int Binary_tab[],char resultant_tab[], const int length_resultant_text) {
    int Begin_8bit_tab=0;
    for (int i = 0; i < length_resultant_text ; ++i) {
        resultant_tab[i] = ALFABET[BinaryToSign(&Binary_tab[Begin_8bit_tab])];
        Begin_8bit_tab+=8;
    }
    resultant_tab[length_resultant_text+1] = '\0';

}

int ColumnNr (const int *tab_6bit){
    int temp=0;
    int power=0;
    for (int i=4; i>=1; i--) {
        temp += tab_6bit[i] * pow(2,power);
        ++power;
    }

    return temp;
}

int LineNr (const int *tab_6bit) { return (tab_6bit[0] * 2 + tab_6bit[5] * 1);}

void sboxExit(int *tab_48bit, int *exit_tab_32bit) {
    int next_tab_6bit = 0;
    int next_exittab_4bit = 0;
    int value_from_Sbox =0;
    for (const auto &nr_Sbox : s_box) {
        value_from_Sbox= nr_Sbox[LineNr(&tab_48bit[next_tab_6bit])][ColumnNr(&tab_48bit[next_tab_6bit])];
        for (int i=3 ; i>=0; i--) {
            exit_tab_32bit[next_exittab_4bit+i]=value_from_Sbox%2;
            value_from_Sbox =(value_from_Sbox-exit_tab_32bit[next_exittab_4bit+i])/2;
        }
        next_exittab_4bit+=4;
        next_tab_6bit+=6;
    }
}

int     ImproveLenghtTo8 (int lenght_text){
    int temp=0;
    if(lenght_text%8 != 0){
        temp=8;
        temp-=lenght_text%8;
    }
    return lenght_text + temp;
}

void separate_arrays (int length_tab, int* binary_tab, int* first_half_tab, int* second_half_tab) {
    int a=length_tab/2;

    for (int i=0;i<a;i++)
    {
        first_half_tab[i]=binary_tab[i];
        second_half_tab[i]=binary_tab[a+i];

    }
}

void create_key (int* key){

    srand((time(NULL)));

    int a=0; int b=1;
    for (int i=0; i<56; i++)
    {
        key[i]=rand()%(2);

    }
}

void separate_key(int* fhalf, int* shalf, int* key){

    int a=28;
    for (int i=0;i<a;i++)
    {
        fhalf[i]=key[i];
        shalf[i]=key[a+i];

    }
}


void PermutationWithExtension (int *right_half, int *extended_right_tab){
    for (int i = 0; i < 48 ; ++i)
        extended_right_tab[i]=right_half[recipe_for_expansion[i]];
}

void shift_key_bits(int round_number, int *half){
    int tmp[28];
    int i_tmp;

    for (int i=0;i<28;i++)
    {
        tmp[i]=half[i];
    }

    for (int i=0;i<28;i++)
    {

        i_tmp=i-round_shift_table[round_number];

        if (i_tmp==-1)
            i_tmp=27;

        if (i_tmp==-2)
            i_tmp=26;

        half[i_tmp]=tmp[i];

    }

}

void PermutationWithCompression (int *right_half ,int *left_half, int *compressed_tab){
    int temp_tab[56]{};
    for (int i = 0; i < 28 ; ++i)
       temp_tab[i]=left_half[i];
    for (int i = 0; i < 28 ; ++i)
        temp_tab[i+28]=right_half[i];
    for (int j = 0; j <48 ; ++j)
        compressed_tab[j]=temp_tab[recipe_for_compresion[j]];
}

void XOR (int *first_b,int *second_b){
    *first_b = (*first_b + *second_b) % 2;
}

void shift_key_bits_right(int round_number, int *half) {

    int tmp[28];
    int i_tmp;

    for (int i = 0; i < 28; i++) {
        tmp[i] = half[i];
    }

    for (int i = 0; i < 28; i++) {

        i_tmp = i + round_shift_table_right[round_number];

        if (i_tmp == 28)
            i_tmp = 0;



        if (i_tmp == 29)
            i_tmp = 1;

        half[i_tmp] = tmp[i];

    }
}