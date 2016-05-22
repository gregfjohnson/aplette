/* data_iterator.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include "data.h"

void indexIterateInit(DataIterator *iter) {
    int i;
    if (iter->size == 0) {
        iter->complete = true;

    } else {
        iter->complete = false;

        if (iter->rank > 0) {
            for (i = 0; i < iter->rank; ++i) {
                iter->idx[i] = 0;
            }
        }
    }
}

bool indexIterate(DataIterator *iter) {
    bool iterated = false;
    int i;
    if (iter->complete) return false;

    if (iter->rank > 0) {
        for (i = 0; i < iter->rank; ++i) {
            if (iter->idx[i] < iter->dim[i] - 1) {
                ++iter->idx[i];
                iterated = true;
                break;

            } else {
                iter->idx[i] = 0;
            }
        }
    } else {
        // in the case of a scalar, iterate once.
        iterated = true;
        iter->complete = true;
    }

    return iterated;
}
