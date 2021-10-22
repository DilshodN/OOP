#include "../shared_ptr.h"

#include <vector>

#include <gtest/gtest.h>

struct Struct
{
    explicit Struct(int aVal) :
            mVal(aVal)
    {
        ++_mNbInstances;
    }
    ~Struct(void)
    {
        --_mNbInstances;
    }
    void incr(void)
    {
        ++mVal;
    }
    void decr(void)
    {
        --mVal;
    }

    int         mVal;
    static int _mNbInstances;
};

int Struct::_mNbInstances = 0;



TEST(SharedPTR, empty_ptr)
{
    // Create an empty (ie. NULL) SharedPTR
    SharedPTR<Struct> xPtr;

    EXPECT_EQ(false, xPtr);
    EXPECT_EQ(false, xPtr.unique());
    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());


    // Reset to NULL (ie. do nothing)
    xPtr.reset();

    EXPECT_EQ(false, xPtr);
    EXPECT_EQ(false, xPtr.unique());
    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());
}

TEST(SharedPTR, basic_ptr)
{
    {
        // Create a SharedPTR
        SharedPTR<Struct> xPtr(new Struct(123));

        EXPECT_EQ(true, xPtr);
        EXPECT_EQ(true, xPtr.unique());
        EXPECT_EQ(1,    xPtr.use_count());
        EXPECT_NE((void*)NULL, xPtr.get());

        if (xPtr)
        {
            EXPECT_EQ(123,  xPtr->mVal);
            EXPECT_EQ(1,    xPtr->_mNbInstances);
            EXPECT_EQ(1,    Struct::_mNbInstances);

            // call a function
            xPtr->incr();
            EXPECT_EQ(124,  xPtr->mVal);
            (*xPtr).incr();
            EXPECT_EQ(125,  (*xPtr).mVal);
            xPtr->decr();
            xPtr->decr();

            // Copy construct the SharedPTR
            SharedPTR<Struct> yPtr(xPtr);

            EXPECT_EQ(xPtr,  yPtr);
            EXPECT_EQ(true,  xPtr);
            EXPECT_EQ(false, xPtr.unique());
            EXPECT_EQ(2,     xPtr.use_count());
            EXPECT_NE((void*)NULL,  xPtr.get());
            EXPECT_EQ(123,   xPtr->mVal);
            EXPECT_EQ(1,     Struct::_mNbInstances);
            EXPECT_EQ(true,  yPtr);
            EXPECT_EQ(false, yPtr.unique());
            EXPECT_EQ(2,     yPtr.use_count());
            EXPECT_NE((void*)NULL,  yPtr.get());
            EXPECT_EQ(123,   yPtr->mVal);
            EXPECT_EQ(1,     Struct::_mNbInstances);

            if (yPtr)
            {
                // Assign the SharedPTR
                SharedPTR<Struct> zPtr;
                zPtr = xPtr;

                EXPECT_EQ(xPtr,  zPtr);
                EXPECT_EQ(true,  xPtr);
                EXPECT_EQ(false, xPtr.unique());
                EXPECT_EQ(3,     xPtr.use_count());
                EXPECT_NE((void*)NULL,  xPtr.get());
                EXPECT_EQ(123,   xPtr->mVal);
                EXPECT_EQ(1,     Struct::_mNbInstances);
                EXPECT_EQ(true,  yPtr);
                EXPECT_EQ(false, yPtr.unique());
                EXPECT_EQ(3,     yPtr.use_count());
                EXPECT_NE((void*)NULL,  yPtr.get());
                EXPECT_EQ(123,   yPtr->mVal);
                EXPECT_EQ(1,     Struct::_mNbInstances);
                EXPECT_EQ(true,  zPtr);
                EXPECT_EQ(false, zPtr.unique());
                EXPECT_EQ(3,     zPtr.use_count());
                EXPECT_NE((void*)NULL,  zPtr.get());
                EXPECT_EQ(123,   zPtr->mVal);
                EXPECT_EQ(1,     Struct::_mNbInstances);
            }

            EXPECT_EQ(true,  xPtr);
            EXPECT_EQ(false, xPtr.unique());
            EXPECT_EQ(2,     xPtr.use_count());
            EXPECT_NE((void*)NULL,  xPtr.get());
            EXPECT_EQ(123,   xPtr->mVal);
            EXPECT_EQ(1,     Struct::_mNbInstances);
        }
        else
        {
            GTEST_FATAL_FAILURE_("bool cast operator error");
        }

        EXPECT_EQ(true, xPtr);
        EXPECT_EQ(true, xPtr.unique());
        EXPECT_EQ(1,    xPtr.use_count());
        EXPECT_NE((void*)NULL, xPtr.get());
        EXPECT_EQ(123,  xPtr->mVal);
        EXPECT_EQ(1,    Struct::_mNbInstances);
    }

    EXPECT_EQ(0,     Struct::_mNbInstances);
}

TEST(SharedPTR, reset_ptr)
{
    // Create an empty (ie. NULL) SharedPTR
    SharedPTR<Struct> xPtr;

    // Reset it with a new pointer
    xPtr.reset(new Struct(123));

    EXPECT_EQ(true, xPtr);
    EXPECT_EQ(true, xPtr.unique());
    EXPECT_EQ(1,    xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(123,  xPtr->mVal);
    EXPECT_EQ(1,    Struct::_mNbInstances);
    Struct* pX  = xPtr.get();

    // Reset it with another new pointer
    xPtr.reset(new Struct(234));

    EXPECT_EQ(true, xPtr);
    EXPECT_EQ(true, xPtr.unique());
    EXPECT_EQ(1,    xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(234,  xPtr->mVal);
    EXPECT_EQ(1,    Struct::_mNbInstances);
    EXPECT_NE(pX,   xPtr.get());

    // Copy-construct a new SharedPTR to the same object
    SharedPTR<Struct> yPtr(xPtr);

    EXPECT_EQ(xPtr,  yPtr);
    EXPECT_EQ(true,  xPtr);
    EXPECT_EQ(false, xPtr.unique());
    EXPECT_EQ(2,     xPtr.use_count());
    EXPECT_NE((void*)NULL,  xPtr.get());
    EXPECT_EQ(234,   xPtr->mVal);
    EXPECT_EQ(true,  yPtr);
    EXPECT_EQ(false, yPtr.unique());
    EXPECT_EQ(2,     yPtr.use_count());
    EXPECT_NE((void*)NULL,  yPtr.get());
    EXPECT_EQ(234,   yPtr->mVal);
    EXPECT_EQ(1,     Struct::_mNbInstances);

    // Reset to NULL
    yPtr.reset();

    EXPECT_EQ(false, yPtr.unique());
    EXPECT_EQ(0,     yPtr.use_count());
    EXPECT_EQ((void*)NULL,  yPtr.get());
    EXPECT_EQ(true,  xPtr);
    EXPECT_EQ(true,  xPtr.unique());
    EXPECT_EQ(1,     xPtr.use_count());
    EXPECT_NE((void*)NULL,  xPtr.get());
    EXPECT_EQ(234,   xPtr->mVal);
    EXPECT_EQ(1,     Struct::_mNbInstances);

    // Copy-construct a new SharedPTR to the same object
    SharedPTR<Struct> zPtr(xPtr);

    EXPECT_EQ(xPtr,  zPtr);
    EXPECT_EQ(true,  xPtr);
    EXPECT_EQ(false, xPtr.unique());
    EXPECT_EQ(2, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(234, xPtr->mVal);
    EXPECT_EQ(true, zPtr);
    EXPECT_EQ(false, zPtr.unique());
    EXPECT_EQ(2, zPtr.use_count());
    EXPECT_NE((void*)NULL, zPtr.get());
    EXPECT_EQ(234, zPtr->mVal);
    EXPECT_EQ(1, Struct::_mNbInstances);

    // Reset it with another new pointer : now xPtr and yPtr each manage a different instance
    zPtr.reset(new Struct(345));

    EXPECT_EQ(true, xPtr);
    EXPECT_EQ(true, xPtr.unique());
    EXPECT_EQ(1, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(234, xPtr->mVal);
    EXPECT_EQ(true, zPtr);
    EXPECT_EQ(true, zPtr.unique());
    EXPECT_EQ(1, zPtr.use_count());
    EXPECT_NE((void*)NULL, zPtr.get());
    EXPECT_EQ(345, zPtr->mVal);
    EXPECT_EQ(2, Struct::_mNbInstances);

    // Reset to NULL
    zPtr.reset();

    EXPECT_EQ(false, zPtr.unique());
    EXPECT_EQ(0,     zPtr.use_count());
    EXPECT_EQ((void*)NULL,  zPtr.get());
    EXPECT_EQ(true, xPtr);
    EXPECT_EQ(true, xPtr.unique());
    EXPECT_EQ(1, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(234, xPtr->mVal);
    EXPECT_EQ(1, Struct::_mNbInstances);

    // Reset to NULL
    xPtr.reset();

    EXPECT_EQ(false, xPtr.unique());
    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());
    EXPECT_EQ(0,     Struct::_mNbInstances);
}

TEST(SharedPTR, compare_ptr)
{
    // Create a SharedPTR
    SharedPTR<Struct> xPtr(new Struct(123));

    EXPECT_EQ(true, xPtr);
    EXPECT_EQ(true, xPtr.unique());
    EXPECT_EQ(1, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(123,xPtr->mVal);
    EXPECT_EQ(1, Struct::_mNbInstances);
    Struct* pX = xPtr.get();

    // Create another SharedPTR
    SharedPTR<Struct> yPtr(new Struct(234));

    EXPECT_EQ(true, xPtr);
    EXPECT_EQ(true, xPtr.unique());
    EXPECT_EQ(1, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(123,xPtr->mVal);
    EXPECT_EQ(2, Struct::_mNbInstances);

    EXPECT_EQ(true, yPtr);
    EXPECT_EQ(true, yPtr.unique());
    EXPECT_EQ(1, yPtr.use_count());
    EXPECT_NE((void*)NULL, yPtr.get());
    EXPECT_EQ(234, yPtr->mVal);
    Struct* pY = yPtr.get();

    // Copy a SharedPTR
    SharedPTR<Struct> zPtr = xPtr;
    Struct* pZ = zPtr.get();

    EXPECT_EQ(pX, pZ);
    EXPECT_EQ(xPtr, zPtr);
    EXPECT_EQ(zPtr, xPtr);
    EXPECT_GE(xPtr, zPtr);
    EXPECT_LE(xPtr, zPtr);
}

TEST(SharedPTR, std_container)
{
    // Create a SharedPTR
    SharedPTR<Struct> xPtr(new Struct(123));

    EXPECT_EQ(true, xPtr);
    EXPECT_EQ(true, xPtr.unique());
    EXPECT_EQ(1,    xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(123,  xPtr->mVal);
    EXPECT_EQ(1, Struct::_mNbInstances);
    Struct* pX = xPtr.get();

    {
        std::vector<SharedPTR<Struct> > PtrList;

        // Copy-it inside a container
        PtrList.push_back(xPtr);

        EXPECT_EQ(true,  xPtr);
        EXPECT_EQ(false, xPtr.unique());
        EXPECT_EQ(2,     xPtr.use_count());
        EXPECT_EQ(2,     PtrList.back().use_count());
        EXPECT_EQ(xPtr,  PtrList.back());
        EXPECT_EQ(pX,    PtrList.back().get());
        EXPECT_EQ(1, Struct::_mNbInstances);

        // And copy-it again
        PtrList.push_back(xPtr);

        EXPECT_EQ(true,  xPtr);
        EXPECT_EQ(false, xPtr.unique());
        EXPECT_EQ(3,     xPtr.use_count());
        EXPECT_EQ(3,     PtrList.back().use_count());
        EXPECT_EQ(xPtr,  PtrList.back());
        EXPECT_EQ(pX,    PtrList.back().get());
        EXPECT_EQ(1, Struct::_mNbInstances);

        // Remove the second pointer from the vector
        PtrList.pop_back();

        EXPECT_EQ(true,  xPtr);
        EXPECT_EQ(false, xPtr.unique());
        EXPECT_EQ(2,     xPtr.use_count());
        EXPECT_EQ(2,     PtrList.back().use_count());
        EXPECT_EQ(xPtr,  PtrList.back());
        EXPECT_EQ(pX,    PtrList.back().get());
        EXPECT_EQ(1, Struct::_mNbInstances);

        // Reset the original pointer, leaving 1 last pointer in the vector
        xPtr.reset();

        EXPECT_EQ(false, xPtr);
        EXPECT_EQ(1,     PtrList.back().use_count());
        EXPECT_EQ(pX,    PtrList.back().get());
        EXPECT_EQ(1, Struct::_mNbInstances);

    } // Destructor of the vector releases the last pointer thus destroying the object

    EXPECT_EQ(0, Struct::_mNbInstances);
}

TEST(SharedPTR, swap_ptr)
{
    // Create a SharedPTR
    SharedPTR<Struct> xPtr(new Struct(123));

    EXPECT_EQ(true, xPtr);
    EXPECT_EQ(true, xPtr.unique());
    EXPECT_EQ(1, xPtr.use_count());
    EXPECT_NE((void*)NULL, xPtr.get());
    EXPECT_EQ(123,xPtr->mVal);
    EXPECT_EQ(1, Struct::_mNbInstances);
    Struct* pX = xPtr.get();

    // Create another SharedPTR
    SharedPTR<Struct> yPtr(new Struct(234));

    EXPECT_EQ(true, yPtr);
    EXPECT_EQ(true, yPtr.unique());
    EXPECT_EQ(1, yPtr.use_count());
    EXPECT_NE((void*)NULL, yPtr.get());
    EXPECT_EQ(234, yPtr->mVal);
    EXPECT_EQ(2, Struct::_mNbInstances);
}