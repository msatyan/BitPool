// Copyright 2017 Sathyanesh Krishnan
// Licensed under the Apache License, Version 2.0
// http://www.apache.org/licenses/LICENSE-2.0

#include <stdio.h>
#include <stdlib.h>

#ifndef _INC_BITPOOL
#define _INC_BITPOOL

class BitPool
{
    friend class TestBitPool;
private:
    const unsigned mArrayElementBitSizei = sizeof(unsigned)*8;
    unsigned mMaxElements;
    unsigned *mpBitMaskArray;

public:
    BitPool(const unsigned MaxElements);
    ~BitPool();

protected:
    char GetFlag(unsigned BitIndex);
    char SetFlag(unsigned BitIndex, unsigned char flag);

private:
    unsigned  FindMaskArrayIndex(unsigned BitIndex);
    char *TestModulePrintBits(const unsigned val);
    void TestModulePrintBits2(const char *Buff);
};

#endif  // _INC_BITPOOL
