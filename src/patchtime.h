/*
 *    Patch Time.  C port of get_patch_week.
 *    Copyright (C) 2026  Nashway
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PATCHTIME_H
#define PATCHTIME_H

/*
 * Return the patch week number (1..5) for the given Gregorian date,
 * counting weeks from the first occurrence of `anchor` (ISO weekday,
 * 1 = Mon ... 7 = Sun) in the month.  Days in the partial first row
 * that come before that anchor belong to the previous month's last
 * patch week.  Mirrors patchtime.py's get_patch_week().
 *
 * Returns -1 on invalid input.
 */
int patchtime_week(int year, int month, int day, int anchor);

#endif /* PATCHTIME_H */
