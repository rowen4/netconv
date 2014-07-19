/*
 *	netconv.h
    Copyright (C) 2014, Richard Owen, rowen@ieee.org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef NETCONV_H_
#define NETCONV_H_
/*==========================================
 * 	Includes
 *==========================================*/
#include <stdint.h>
/*==========================================
 * 	Defaults
 *==========================================*/
/*==========================================
 * 	Types
 *==========================================*/
/*==========================================
 * 	Externals
 *==========================================*/
/*==========================================
 * 	Prototypes
 *==========================================*/
/*
 *	payload_fmt:	Format string for the payload. acceptable values are:
 *		b:		int8_t (byte)
 *		s:		int16_t (short)
 *		i:		int32_t(integer)
 *		l:		int64_t(integer)
 *		example: "4b4s2l" would be interpreted as four int8_t followed by four int_16t, followed by two int64_t
 *		Quantities prior to a type of unity magnitude are optional. Eg "4b1i" and "4bi" are equivalent
 */
void*	netconv_hton(const char* fmt_str, void* __restrict__ block);
void*	netconv_ntoh(const char* fmt_str, void* __restrict__ block);
#endif /* NETCONV_H_ */
