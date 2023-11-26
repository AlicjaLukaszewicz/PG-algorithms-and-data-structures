#include <iostream>
using namespace std;
#define MAX 255

int BinarySearch(const int *array, int leftSide, int rightSide, int numberToBeFound) {
    if (rightSide >= leftSide) {
        int middle = leftSide + (rightSide - leftSide) / 2;
        if (array[middle] == numberToBeFound)
            return middle;
        if (array[middle] > numberToBeFound)
            return BinarySearch(array, leftSide, middle - 1, numberToBeFound);
        return BinarySearch(array, middle + 1, rightSide, numberToBeFound);
    }
    return -1;
}

void Partition(int numberToBeParted, int primeIndex, int numberIndex, const int *primesArray, int sequence[]) {
    static bool isChangeNeeded;

    numberToBeParted -= primesArray[primeIndex];
    sequence[numberIndex] = primesArray[primeIndex];
    numberIndex++;

    if (numberToBeParted < 0)
        return;
    if (numberToBeParted == 0) {
        //Wypisanie na ekran bieżącej sekwencji
        for (int i = 0; i < numberIndex; ++i) {
            cout << sequence[i];
            if (i+1 != numberIndex)
                cout << "+";
        }
        cout << endl;
        //Zliczanie sumy najmniejszej liczby pierwszej i szukanie jej pierwszego indeksu
        int tempValue = 0;
        int tempIndex = 0;
        bool hasPrimeChanged = false;
        for (int i = numberIndex-1; i >= 0; i--) {
            if (sequence[i] == primesArray[primeIndex]) {
                tempValue+=sequence[i];
                if (sequence[i-1] != primesArray[primeIndex]) {
                    tempIndex = i;
                    break;
                }
            }
        }
        //Przypisanie numeru pierwszej liczby pierwszej stojącej na lewo od tempIndex dla niepodzielnej sumy
        int tempPrimeIndex;
        if (tempIndex!=0) {
            tempPrimeIndex = BinarySearch(primesArray, 0, 10, sequence[tempIndex-1]);
            while (true) {
                if ((tempValue <= 4)||
                ((primeIndex==0)&&(tempValue-2*primesArray[primeIndex+1] < 0))||
                ((primeIndex!=0)&&(tempValue-primesArray[primeIndex+1]-primesArray[1] < 0))) {
                    if (primeIndex!=0) {
                        for (int i = numberIndex-1; i >= 0; i--) {
                            if (sequence[i] == primesArray[tempPrimeIndex]) {
                                tempValue+=sequence[i];
                                if (sequence[i-1] != primesArray[tempPrimeIndex]) {
                                    tempIndex = i;
                                    break;
                                }
                            }
                        }
                        primeIndex = tempPrimeIndex;
                        hasPrimeChanged = true;
                        if (tempValue-primesArray[primeIndex+1]-primesArray[1] < 0) {
                            tempPrimeIndex++;
                            if (primesArray[tempPrimeIndex] > sequence[0])
                                break;
                            continue;
                        } else
                            break;
                    } else {
                        primeIndex = tempPrimeIndex;
                        hasPrimeChanged = true;
                    }
                }
                break;
            }
        }
        int originalNumberIndex = numberIndex;
        //Jeżeli liczba pierwsza się nie zmieniła
        if (!hasPrimeChanged) {
            numberToBeParted = tempValue;
            numberIndex = tempIndex;
        } else {
            //Szukanie pierwszego elementu najmniejszej liczby pierwszej (po zmianach)
            for (int i = 0; i < numberIndex; ++i) {
                if (sequence[i] == primesArray[primeIndex]) {
                    numberIndex = i;
                    break;
                }
            }
            //Zliczanie elementów
            for (int i = numberIndex; i < originalNumberIndex; ++i) {
                numberToBeParted += sequence[i];
            }
        }
        primeIndex++;
        isChangeNeeded = true;
        if (primesArray[primeIndex] > sequence[0])
            return;
        Partition(numberToBeParted, primeIndex, numberIndex ,primesArray, sequence);
    } else {
        if (numberToBeParted%2==0) {
            if ((numberIndex == 1)||(isChangeNeeded)) {
                primeIndex = 0;
                isChangeNeeded = false;
            } else if (primeIndex-1 >=0 ) {
                primeIndex--;
            }
        }
        else {
            if ((numberIndex == 1)||(isChangeNeeded)) {
                primeIndex = 1;
                if (sequence[0] < primesArray[primeIndex])
                    return;
                isChangeNeeded = false;
            } else if (primeIndex-1 >=1 ) {
                primeIndex--;
            }
        }
        Partition(numberToBeParted, primeIndex, numberIndex,primesArray, sequence);
    }
}

void Sequence(int numberToBeParted, int biggestPrime, const int *primesArray, int numberOfPrimes) {
    int sequence[128];

    int primeIndex = BinarySearch(primesArray, 0, numberOfPrimes, biggestPrime);
    if (primeIndex == -1)
        return;
    Partition(numberToBeParted, primeIndex, 0, primesArray, sequence);
}

int main() {
    int numberOfPrimes = MAX;
    bool temp[MAX];

    for (int i = 2; i < MAX; ++i) {
        temp[i] = true;
    }
    for (int i = 2; i*i < MAX; ++i) {
        if (temp[i]) {
            for (int j = i*i; j < MAX; j+=i) {
                if (temp[j])
                    numberOfPrimes--;
                temp[j] = false;
            }
        }
    }
    int* primes = new int[numberOfPrimes];
    int i=0;
    for (int j = 2; j < MAX; ++j) {
        if (temp[j]) {
            primes[i] = j;
            i++;
        }
    }
    int s, n, p;
    cin >> s;
    for (int j = 0; j < s; ++j) {
        cin >> n;
        cin >> p;
        Sequence(n, p, primes, numberOfPrimes);
    }
    return 0;
} 