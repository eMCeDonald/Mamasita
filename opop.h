#include <iostream>

using namespace std;

char key[64]; //to jest podstawa klucza, ktory zostanie wprowadzony, a nastepnie podzielony na 2 czesci po 56 bitow
char first[56]; //pierwsza "polowa"
char second[56]; //druga "polowa"

void reset(char tab[], char tab1, char tab2[]) //tutaj przypisuje wartosci i do kazdej komorki wszystkich tablic czyli klucz first second
{
    for (int i=0; i<64; i++)
    {
        tab[i]=i;
    }
    for (int i=0; i<56; i++)
    {
        tab1[i]=i;
        tab2[i]=i;
    }
}

// WG tego co znajduje siê na tej stronie:
// druga[j]=klucz[(63-(i*8))]
// przydzielamy konretne bity z klucza 64bitowego
// do dwoch czesci po 56 bitow
// wyglada to tak, ze zaczynamy od konkretnej liczby
// i schodzimy co 8 w dol przypisujac nastepne

void assign_first(char klucz[],char pierwsza[],char druga[])
{
    int licznik=0;
    int flaga=0;
    for (int j=0; j<56; j++)
    {
        flaga=0;
        for (int i=0; i<64; i++)
        {
            do
            {
                if (licznik<8)
                {
                    pierwsza[j]=klucz[(57-(i*8)];
                    druga[j]=klucz[(63-(i*8))]
                                      flaga=1;
                }
                else if (licznik >=8 && licznik < 17)
                {
                    pierwsza[j]=klucz[(58-(i*8)];
                    druga[j]=klucz[(62-(i*8))]
                                      flaga=1;
                }
                else if (licznik >=17 && licznik < 24)
                {
                    pierwsza[j]=klucz[(59-(i*8)];
                    druga[j]=klucz[(61-(i*8))]
                                      flaga=1;
                }
                else
                {
                    pierwsza[j]=klucz[(60-(i*8))];
                    druga[j]=klucz[(28-(i*8))]
                    flaga=1;
                }

            }   while (flaga==0);
            licznik++;
        }
    }
}

void control_show(char pierwsza[])
{
    for (int i=0;i<56;i++)
    {
        cout << first[i] << "   ";
    }
}


int main()
{
    reset(key,first,second);
    assign_first(key,first);
    control_show(first);
    return 0;
}
