#include "rc4crpto.h"

RC4Crpto::RC4Crpto(char key[],char plainText[])
{
    cipherText = new char[1024];
    std::strcpy(this->plainText,plainText);
    std::strcpy(this->key,key);
}

RC4Crpto::~RC4Crpto()
{
    delete cipherText;
}
void RC4Crpto::init()
{
    for(int i=0;i<LENGTH;++i)		//init s box and t box
    {
            s[i]=i;
            t[i]=key[i%strlen(key)];
    }

    for(int i=0,j=0;i<LENGTH;++i)
    {
            int tmp;
            j=(j+s[i]+t[i])%LENGTH;
            tmp=s[i];
            s[i]=s[j];
            s[j]=tmp;
    }
}

char* RC4Crpto::crypt()
{
    init();
    int m=0,n=0,q;
    int i=0;
    for(;i<strlen(plainText);++i)
    {
        int tmp;
        m=(m+1)%LENGTH;
        n=(n+s[n])%LENGTH;
        tmp=s[m];
        s[m]=s[n];
        s[n]=tmp;

        q=(s[m]+s[n])%LENGTH;
        newKey[i]=s[q];
        cipherText[i]=plainText[i]^newKey[i];
    }
    cipherText[i]='\0';

    return cipherText;

}
