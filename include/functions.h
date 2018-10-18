#ifndef KRYPTO_1_FUNCTIONS_H
#define KRYPTO_1_FUNCTIONS_H

char    *OpenAndReturnText (const char * file_name, int & length_tab );
void    Sign8ToBinary (char tab_8chars[], int *binary_tab_for_8chars);
void    SignToBinary (char sign, int *binary_s);
char    BinaryToSign (int Binary_sign[]);
void    BinaryToText (int Binary_tab[],char resultant_tab[], int length_resultant_text);
int    LineNr (const int *tab_6bit);
int     ColumnNr (const int *tab_6bit);
void    sboxExit ( int * tab_48bit, int *exit_tab_32bit);
int     ImproveLenghtTo8 (int lenght_text);
void separate_arrays (int length_tab, int* binary_tab, int* first_half_tab, int* second_half_tab);
void create_key (int* key);
void separate_key(int* fhalf, int* shalf, int* key);
void PermutationWithExtension (int *right_half, int *extended_right_tab);
void shift_key_bits(int round_number, int *half);
void PermutationWithCompression (int *right_half ,int *left_half, int *compressed_tab);
void XOR (int *first_b,int *second_b);
#endif //KRYPTO_1_FUNCTIONS_H
