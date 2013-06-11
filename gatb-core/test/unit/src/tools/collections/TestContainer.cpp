/*****************************************************************************
 *   GATB : Genome Assembly Tool Box                                         *
 *   Copyright (c) 2013                                                      *
 *                                                                           *
 *   GATB is free software; you can redistribute it and/or modify it under   *
 *   the CECILL version 2 License, that is compatible with the GNU General   *
 *   Public License                                                          *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 *   CECILL version 2 License for more details.                              *
 *****************************************************************************/

#include <CppunitCommon.hpp>

#include <gatb/tools/collections/impl/Bloom.hpp>

#include <gatb/tools/misc/api/Macros.hpp>

#include <gatb/tools/math/NativeInt64.hpp>
#include <gatb/tools/math/NativeInt128.hpp>
#include <gatb/tools/math/LargeInt.hpp>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <set>

using namespace std;
using namespace gatb::core::tools::collections;
using namespace gatb::core::tools::collections::impl;
using namespace gatb::core::tools::math;

/********************************************************************************/
namespace gatb  {  namespace tests  {
/********************************************************************************/

/********************************************************************************/

/** \brief Test class for operating system operations
 */
class TestContainer : public Test
{
    /********************************************************************************/
    CPPUNIT_TEST_SUITE_GATB (TestContainer);

        CPPUNIT_TEST_GATB (bloom_checkContains);

    CPPUNIT_TEST_SUITE_GATB_END();

public:
    /********************************************************************************/
    void setUp    ()  {  srand (time(NULL));  }
    void tearDown ()  {}

    /********************************************************************************/
    template<typename Item> void bloom_checkContains_aux (u_int64_t* values, size_t size)
    {
        u_int64_t maxvalue = values [size-1];

        Bloom<Item> bloom (1000*1000);

        for (size_t i=0; i<size; i++)
        {
            Item item (values[i]);
            bloom.insert (item);
        }

        size_t nbNotFound = 0;

        for (size_t i=0; i<maxvalue; i++)
        {
            /** We look into the table whether the current value really exist. */
            bool found = false;
            for (size_t j=0; j<size && !found; j++)  {  found = (i==values[j]); }

            if (!found)
            {
                nbNotFound++;

                /** We check true negatives. */
                CPPUNIT_ASSERT (bloom.contains(i) == false);
            }
        }

        /** We check we found the correct number of true negatives. */
        CPPUNIT_ASSERT (nbNotFound == (maxvalue - size + 1));
    }

    /** */
    void bloom_checkContains ()
    {
        u_int64_t values1[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
        u_int64_t values2[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
        u_int64_t values3[] = { 1, 10, 100, 1000, 10000, 100000};

        bloom_checkContains_aux<NativeInt64> (values1, ARRAY_SIZE(values1));
        bloom_checkContains_aux<NativeInt64> (values2, ARRAY_SIZE(values2));
        bloom_checkContains_aux<NativeInt64> (values3, ARRAY_SIZE(values3));

#ifdef INT128_FOUND
        bloom_checkContains_aux<NativeInt128> (values1, ARRAY_SIZE(values1));
        bloom_checkContains_aux<NativeInt128> (values2, ARRAY_SIZE(values2));
        bloom_checkContains_aux<NativeInt128> (values3, ARRAY_SIZE(values3));
#endif

        bloom_checkContains_aux<LargeInt<1> > (values1, ARRAY_SIZE(values1));
        bloom_checkContains_aux<LargeInt<1> > (values2, ARRAY_SIZE(values2));
        bloom_checkContains_aux<LargeInt<1> > (values3, ARRAY_SIZE(values3));

        bloom_checkContains_aux<LargeInt<2> > (values1, ARRAY_SIZE(values1));
        bloom_checkContains_aux<LargeInt<2> > (values2, ARRAY_SIZE(values2));
        bloom_checkContains_aux<LargeInt<2> > (values3, ARRAY_SIZE(values3));

        bloom_checkContains_aux<LargeInt<3> > (values1, ARRAY_SIZE(values1));
        bloom_checkContains_aux<LargeInt<3> > (values2, ARRAY_SIZE(values2));
        bloom_checkContains_aux<LargeInt<3> > (values3, ARRAY_SIZE(values3));

        bloom_checkContains_aux<LargeInt<4> > (values1, ARRAY_SIZE(values1));
        bloom_checkContains_aux<LargeInt<4> > (values2, ARRAY_SIZE(values2));
        bloom_checkContains_aux<LargeInt<4> > (values3, ARRAY_SIZE(values3));

        bloom_checkContains_aux<LargeInt<5> > (values1, ARRAY_SIZE(values1));
        bloom_checkContains_aux<LargeInt<5> > (values2, ARRAY_SIZE(values2));
        bloom_checkContains_aux<LargeInt<5> > (values3, ARRAY_SIZE(values3));
    }
};

/********************************************************************************/

CPPUNIT_TEST_SUITE_REGISTRATION (TestContainer);

/********************************************************************************/
} } /* end of namespaces. */
/********************************************************************************/