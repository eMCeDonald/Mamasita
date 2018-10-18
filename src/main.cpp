#include <iostream>
#include "functions.h"
#include "round_shift_table.h"

#include <cstdlib>
#include <fstream>


using namespace std;

int main() {
// wczytywanie tekstu i zwrocenie go w tablicy wraz z dlugiscia
    const char * file_name= "../text.txt";
    int length_plain_text=0;
    char * plain_text=OpenAndReturnText(file_name,length_plain_text);
    cout << "wczytany tekst " << endl << plain_text << endl;
    cout << "ilosc liter  " << length_plain_text << endl;
    // zamiana tekstu na binarke do binarytab

    //do klucza ogor
    int first_half_key[27];
    int second_half_key[27];
    int key[56];

    const int length_binary_tab = 8*ImproveLenghtTo8(length_plain_text);
    int *Binary_tab=new int[length_binary_tab]{};
    int next_tab_64bit=0;
    int amount_64bit_tab=length_plain_text/8;
    int pack_8chars=0;
    int *first_b_half=new int[length_binary_tab/2];
    int *second_b_half=new int[length_binary_tab/2];

    for (int i=0; i<=amount_64bit_tab; i++) {
        Sign8ToBinary(&plain_text[pack_8chars],&Binary_tab[next_tab_64bit]);
        pack_8chars+=8;
        next_tab_64bit+=64;
    }
    //wyswietlanie zamiany na binarke
    for (int i=0; i<length_binary_tab; i++ ) {
        if (i%8==0)
            cout <<"|";
        cout << Binary_tab[i];
    }
    cout << endl;

    // Generowanie klucza igor
    create_key(key);
    //SHAROWANIE klucze xD
    separate_key(first_half_key,second_half_key,key);
    //dzielenia na pol
    separate_arrays(length_binary_tab,Binary_tab,first_b_half,second_b_half);



    //WYswietlenie kluca i polowy

    cout<< "caly klucz \n";
    for (int i=0;i<55;i++) {
        cout << key[i] << "|";
    }

        cout << " TO JEST PIERWSZA POLOWA:"<<endl;
    for (int i=0; i<27; i++)
    {
        cout << first_half_key[i]<<"|";
    }
    cout << endl << "TO JEST DRUGA POLOWA:"<<endl;
    for (int i=0; i<27; i++)
    {
        cout << second_half_key[i]<<"|";
    }



    //TEST


    for (int j = 0; j < 16 ; ++j) {
        shift_key_bits(j,first_half_key);
        shift_key_bits(j,second_half_key);
        int subkey[48]{};
        int extended_right_tab[48]{};
        int temp[32]{};
        for (int i = 0; i < 32; ++i)
            temp[i]=second_b_half[i];
        PermutationWithExtension(second_b_half,extended_right_tab);
        PermutationWithCompression(first_half_key,second_half_key,subkey);
        for (int k = 0; k < 48 ; ++k)
            XOR(&extended_right_tab[k],&subkey[k]);
        sboxExit(extended_right_tab,second_b_half);
        for (int l = 0; l <32 ; ++l)
            XOR(&second_b_half[l],&first_b_half[l]);
        for (int m = 0; m < 32 ; ++m)
            first_b_half[m]=temp[m];
    }






    delete [] plain_text;
    delete [] Binary_tab;
    delete [] first_b_half;
    delete [] second_b_half;
    return 0;
}