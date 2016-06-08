/* work_space.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef WORK_SPACE_H
#define WORK_SPACE_H

void wssave(int ffile);

void readErrorOnFailure(int fd, void *buf, size_t count);
void writeErrorOnFailure(int fd, void *buf, size_t count);

#endif
