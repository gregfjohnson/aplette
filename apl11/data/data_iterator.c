/* data_iterator.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include "data.h"

void indexIterateInit(DataIterator* iter)
{
    int i;
    if (iter->size == 0) {
        iter->complete = true;
    }
    else {
        iter->complete = false;

        if (iter->rank > 0) {
            for (i = 0; i < iter->rank - 1; ++i) {
                iter->idx[i] = 0;
            }
            iter->idx[iter->rank - 1] = -1;
        }
    }
}

bool indexIterate(DataIterator* iter)
{
    int i;
    bool result;
    if (iter->complete)
        return false;

    if (iter->rank == 0) {
        result = true;         // process scalar once
        iter->complete = true; // for next time through..
    }
    else {
        iter->complete = true; // unless proven otherwise..

        for (i = iter->rank - 1; i >= 0; --i) {
            if (iter->idx[i] < iter->dim[i] - 1) {
                ++iter->idx[i];
                iter->complete = false;
                break;
            }
            else {
                iter->idx[i] = 0;
            }
        }
        result = !iter->complete;
    }

    return result;
}

#ifdef UNIT_TEST
#include <stdio.h>

void prt(char* title, DataIterator* iter)
{
    fprintf(stderr, "%s (done %d):  ", title, iter->complete);
    for (int i = 0; i < iter->rank; ++i) {
        fprintf(stderr, "%4d", iter->idx[i]);
    }
    fprintf(stderr, "\n");
}

static void testScalar()
{
    DataIterator iter;
    iter.rank = 0;
    iter.size = 1;

    indexIterateInit(&iter);
    while (indexIterate(&iter)) {
        prt("testScalar", &iter);
    }
}

static void testVectorWithOneElement()
{
    DataIterator iter;
    iter.rank = 1;
    iter.dim[0] = 1;
    iter.size = 1;

    indexIterateInit(&iter);
    while (indexIterate(&iter)) {
        prt("testVectorWithOneElement", &iter);
    }
}

static void testVectorWithMultipleElements()
{
    DataIterator iter;
    iter.rank = 1;
    iter.dim[0] = 3;
    iter.size = 3;

    indexIterateInit(&iter);
    while (indexIterate(&iter)) {
        prt("testVectorWithMultipleElements", &iter);
    }
}

static void testThreeDimensionalArrayWithOneElement()
{
    DataIterator iter;
    iter.rank = 3;
    iter.dim[0] = 1;
    iter.dim[1] = 1;
    iter.dim[2] = 1;
    iter.size = 1;

    indexIterateInit(&iter);
    while (indexIterate(&iter)) {
        prt("testThreeDimensionalArrayWithOneElement", &iter);
    }
}

static void testThreeDimensionalArray()
{
    DataIterator iter;
    iter.rank = 3;
    iter.dim[0] = 2;
    iter.dim[1] = 3;
    iter.dim[2] = 4;
    iter.size = 24;

    indexIterateInit(&iter);
    while (indexIterate(&iter)) {
        prt("testThreeDimensionalArray", &iter);
    }
}

int main(int argc, char** argv)
{
    testScalar();
    testVectorWithOneElement();
    testVectorWithMultipleElements();
    testThreeDimensionalArray();
    testThreeDimensionalArrayWithOneElement();

    return 0;
}
#endif
