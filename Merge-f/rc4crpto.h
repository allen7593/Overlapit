#ifndef RC4CRPTO_H
#define RC4CRPTO_H

#include <cstring>

class RC4Crpto
{
public:
    RC4Crpto(char [],char []);
    ~RC4Crpto();
    char* crypt();
private:
    static const int LENGTH=256;

    void init();

    char key[LENGTH];
    int s[LENGTH],t[LENGTH];
    char plainText[1024],*cipherText,newPlainT[1024];

    int newKey[LENGTH];

};

#endif // RC4CRPTO_H
