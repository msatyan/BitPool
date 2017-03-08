// Copyright 2017 Sathyanesh Krishnan
// Licensed under the Apache License, Version 2.0
// http://www.apache.org/licenses/LICENSE-2.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BitPool.h"

class TestBitPool
{
public:
    TestBitPool()
    {
    };

    void AllTest()
    {
        TestFindMaskArrayIndex();
        TestPrintBits();
        TestGetSetFlag();
        printf("\n\n End \n\n");

    }

private:

    int TestGetSetFlag()
    {
        char            *TestName = "TestGetSetFlag";
        const unsigned  MaxArraySize = 5000;
        int             trace = 0;
        int             TestError = 0;
        unsigned        i = 0;
        int             j = 0;
        int             k = 0;
        char            TestArray[MaxArraySize];
        BitPool         objBitPool(MaxArraySize);

        printf("\n\n Testing %s...", TestName);

        for (k = 0; k < 2; ++k)
        {
            for (j = 2; j < 100; ++j)
            {
                if ( trace )
                    printf("\n\n ------------ %s: j=%d, k=%d------------\n", TestName, j, k);

                for (i = 0; i < MaxArraySize; ++i)
                {
                    TestArray[i] = 1;
                    if ( i%j  == 0 )
                    {
                        TestArray[i] = 0;
                    }

                    if (k == 0)
                    { 
                        // Flip the flag with this iteration
                        if (TestArray[i])
                            TestArray[i] = 0;
                        else
                            TestArray[i] = 1;
                    }


                    if (trace)
                    {
                        if (i % 40 == 0)
                        {
                            printf("\n");
                        }
                        else if (i % 4 == 0)
                        {
                            printf("  ");
                        }
                        printf("%d", TestArray[i]);
                    }

                    // Set Flag
                    char rc = objBitPool.SetFlag(i, TestArray[i]);
                    if (rc < 0)
                    {
                        printf("\n Error_1 (%s): i=%d, j=%d, k=%d", TestName, i, j, k);
                    }
                }

                // Get Flag and Verify
                for (i = 0; i < MaxArraySize; ++i)
                {
                    char flag = objBitPool.GetFlag(i);

                    if (flag != TestArray[i])
                    {
                        ++TestError;
                        printf("\n Error_2 (%s): i=%d, j=%d, k=%d", TestName, i, j, k);
                    }
                }
            }
        }
    


        if (TestError)
        {
            printf("\n FAILED: %s", TestName);
        }
        else
        {
            printf("\n PASSED: %s", TestName);
        }
        return(TestError);
    }


    int TestFindMaskArrayIndex()
    {
        char *TestName = "TestFindMaskArrayIndex";
        int TestError = 0;
        int i = 0;

        //BitIndex
        unsigned TestArray[] = { 0, 1, 15, 16, 31, 32, 63, 64, 127, 128 };
        unsigned    ExpVal[] = { 0, 0,  0,  0,  0,  1,  1,  2,   3,   4 };

        int         TestArraySize = sizeof(TestArray) / sizeof(unsigned);
        int         ExpValValArraySize = sizeof(ExpVal) / sizeof(unsigned);
        BitPool      objBitPool(100);

        //printf("\n\n Testing %s", TestName);

        if (ExpValValArraySize != TestArraySize)
        {
            printf("\n %s Failed, mismatch in ExpValValArraySize and TestArraySize size ", TestName);
        }

        for (i = 0; i < TestArraySize; ++i)
        {
            unsigned Val = TestArray[i];
            unsigned Exp = ExpVal[i];
            unsigned Act = objBitPool.FindMaskArrayIndex(Val);

            if (Exp != Act)
            {
                TestError = 1;
                printf("\n %s Exp=%d, Act=%d, Val=%d",
                    TestName, Exp, Act, Val);
            }
        }

        if (TestError)
        {
            printf("\n FAILED: %s", TestName);
        }
        else
        {
            printf("\n PASSED: %s", TestName);
        }
        return(TestError);
    }


    int TestPrintBits()
    {
        char *TestName = "TestPrintBits";
        int TestError = 0;
        unsigned i = 0;
        unsigned tmp = 0;
        unsigned val = 0;
        const unsigned all = ~0; // Toggle all the bits


        struct
        {
            char BitString[sizeof(unsigned)* 8 + 1];
            unsigned CompVal;
            unsigned Val;

        } TestVal1[] =
        {
            { "01111111111111111111111111111111", 4294967294, 1 },
            { "10111111111111111111111111111111", 4294967293, 2 },
            { "11011111111111111111111111111111", 4294967291, 4 },
            { "11101111111111111111111111111111", 4294967287, 8 },
            { "11110111111111111111111111111111", 4294967279, 16 },
            { "11111011111111111111111111111111", 4294967263, 32 },
            { "11111101111111111111111111111111", 4294967231, 64 },
            { "11111110111111111111111111111111", 4294967167, 128 },
            { "11111111011111111111111111111111", 4294967039, 256 },
            { "11111111101111111111111111111111", 4294966783, 512 },
            { "11111111110111111111111111111111", 4294966271, 1024 },
            { "11111111111011111111111111111111", 4294965247, 2048 },
            { "11111111111101111111111111111111", 4294963199, 4096 },
            { "11111111111110111111111111111111", 4294959103, 8192 },
            { "11111111111111011111111111111111", 4294950911, 16384 },
            { "11111111111111101111111111111111", 4294934527, 32768 },
            { "11111111111111110111111111111111", 4294901759, 65536 },
            { "11111111111111111011111111111111", 4294836223, 131072 },
            { "11111111111111111101111111111111", 4294705151, 262144 },
            { "11111111111111111110111111111111", 4294443007, 524288 },
            { "11111111111111111111011111111111", 4293918719, 1048576 },
            { "11111111111111111111101111111111", 4292870143, 2097152 },
            { "11111111111111111111110111111111", 4290772991, 4194304 },
            { "11111111111111111111111011111111", 4286578687, 8388608 },
            { "11111111111111111111111101111111", 4278190079, 16777216 },
            { "11111111111111111111111110111111", 4261412863, 33554432 },
            { "11111111111111111111111111011111", 4227858431, 67108864 },
            { "11111111111111111111111111101111", 4160749567, 134217728 },
            { "11111111111111111111111111110111", 4026531839, 268435456 },
            { "11111111111111111111111111111011", 3758096383, 536870912 },
            { "11111111111111111111111111111101", 3221225471, 1073741824 },
            { "11111111111111111111111111111110", 2147483647, 2147483648 },
            { NULL, NULL, NULL }
        };


        BitPool      objBitPool(100);

        for (i = 0; i < 32; ++i)
        {
            char *cp1 = NULL;
            char *cp2 = TestVal1[i].BitString;
            unsigned val = TestVal1[i].CompVal; 

            if (val != (all & (~TestVal1[i].Val)))
            {
                ++TestError;
                printf("\nVal and CompVal not matching for TestVal1[%d]", i);
            }

            cp1 = objBitPool.TestModulePrintBits(val);
            tmp = strcmp(cp1, cp2);
            if (tmp != 0)
            {
                ++TestError;
                printf("\n\n Error : %u  ", val);
                printf("\n Exp[%s]", cp2);
                printf("\n Act[%s]", cp1);
            }
        }


        if (TestError)
        {
            printf("\n FAILED: %s", TestName);
        }
        else
        {
            printf("\n PASSED: %s", TestName);
        }
        return(TestError);
    }

};


void AllBitPoolTests()
{

    TestBitPool ObjTestBitPool;

    ObjTestBitPool.AllTest();
}
