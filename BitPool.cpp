// Copyright 2017 Sathyanesh Krishnan
// Licensed under the Apache License, Version 2.0
// http://www.apache.org/licenses/LICENSE-2.0
#include "BitPool.h"

///////////////////////// public /////////////////
BitPool::BitPool(const unsigned MaxElements)
{
    unsigned i=0;

    //Zero based index, four bytes storage can accommodate bit 0 to bit 31.
    unsigned ArraySize = FindMaskArrayIndex(MaxElements) + 1;
    mMaxElements = (ArraySize * mArrayElementBitSizei) - 1; //Zero based index

    mpBitMaskArray = new unsigned[ArraySize];
    for (i = 0; i < ArraySize; ++i)
    {
        *(mpBitMaskArray + i) = 0;
    }
}

BitPool::~BitPool()
{
    delete mpBitMaskArray;
    mpBitMaskArray = NULL;
}



///////////////////////// protected /////////////////
char BitPool::GetFlag(unsigned BitIndex)
{
    char flag = 0;

    if (BitIndex > mMaxElements)
    {
        // Error
        flag = -1;
    }
    else
    {
        // The array element the bit belongs 
        unsigned ArrayIndex = FindMaskArrayIndex(BitIndex);

        // Offset of the bit withing this array element. 
        unsigned BitOffset = BitIndex % mArrayElementBitSizei;
        unsigned Mask = 1 << BitOffset;

        //  lock
        {
            unsigned *pElement = (mpBitMaskArray + ArrayIndex);
            if (*pElement & Mask)
            {
                flag = 1;
            }
        }
        //  UnLock
    }

    return(flag);
}

///////////////////////// protected /////////////////
char BitPool::SetFlag(unsigned BitIndex, unsigned char flag)
{
    if (BitIndex > mMaxElements)
    {
        return(-1);
    }
    else
    {
        // The array element the bit belongs 
        unsigned ArrayIndex = FindMaskArrayIndex(BitIndex);

        // Offset of the bit withing this array element. 
        unsigned BitOffset = BitIndex % mArrayElementBitSizei;
        unsigned Mask = 1 << BitOffset;

        //  lock
        {
            unsigned *pElement = (mpBitMaskArray + ArrayIndex);
            if (flag)
            {
                // Set the flag
                *pElement = *pElement | Mask;
            }
            else
            {
                // Clear the flag
                *pElement = *pElement & (~Mask);
            }
        }
        //  UnLock
    }
    return(0);

}



///////////////////////// private /////////////////
unsigned  BitPool::FindMaskArrayIndex(unsigned BitIndex)
{
    //Zero based index, four bytes storage can accommodate bit 0 to bit 31.
    //return(BitMaskArraySize(BitIndex) - 1);
    unsigned Index = (BitIndex / mArrayElementBitSizei);
    return(Index);
}



char *BitPool::TestModulePrintBits(const unsigned val)
{
    static char Buff[sizeof(unsigned)* 8 + 1];
    char *cp;
    unsigned Mask = 1;
    unsigned i = 0;


    for (i = 0; i < sizeof(Buff); ++i)
    {
        Buff[i] = 0;
    }

    cp = Buff;
    for (i = 0; i < sizeof(unsigned)* 8; ++i)
    {
        *cp = '0';
        unsigned tmp = val & Mask;
        if (tmp)
        {
            *cp = '1';
        }
        Mask = Mask << 1;
        ++cp;
    }
    *cp = 0;

    return(Buff);
}


void BitPool::TestModulePrintBits2(const char *Buff)
{
    const char *cp = Buff;
    unsigned Mask = 1;
    unsigned i = 0;

    printf("\n");
    for (i = 1; *cp; ++i)
    {
        printf("%c", *cp);
        if (i % 8 == 0)
        {
            printf(", ");
        }
        else if (i % 4 == 0)
        {
            printf(" ");
        }
        ++cp;
    }
    printf(" \n");
}

