/*
 *	netconv.c
    Copyright (C) 2014, Richard Owen, rowen@ieee.org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*==========================================
 * 	Includes
 *==========================================*/
#include "netconv.h"
#include <endian.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*==========================================
 * 	Extern Globals
 *==========================================*/
/*==========================================
 * 	Static Globals
 *==========================================*/
/*==========================================
 * 	Static Prototypes
 *==========================================*/
/*==========================================
 * 	Functions
 *==========================================*/
/*
 * Function: netconv_hton
 * Description: converts a block of data from host byte order to network byte order. A format string is used to describe the type
 *  of data at each point in the block
 * Parameters:
 *  fmt_str: format string used for formatting the block of data. See netconv.h for details
 *  block: pointer to the base of the block of data to be converted
 * Returns:	Pointer to block if the operation succeed, NULL otherwise.
 * NB: The operation may fail if the format string is incorrectly formatted. This may result in block being corrupted
 */
void*	netconv_hton(const char* fmt_str, void* __restrict__ block)
{
	int err = 0;
	int i = 0;
	int fmt_len = strlen(fmt_str);
	int fmt_len_parsed = 0;
	int num_el = 0;
	int block_offset = 0;
	const char* prev = fmt_str;
	char* next = NULL;
	while (fmt_len_parsed < fmt_len)
	{
		num_el = strtol(fmt_str + fmt_len_parsed,&next,0);	//Parse the length of the next data block
		if (num_el == 0)					//Handle the case where the quantity is optional for fmt_str entries that have unity magnitude
		{									//If the value 1 is included, num_el will be set to 1 and next will point to the entry type
			num_el = 1;						//If the value is not included, num_el will be set to 0 and next will point to the entry type
		}
		else
		{
			fmt_len_parsed = (int)(next - prev);
			prev = next;
		}
		for (i = 0; i < num_el; i++)
		{
			switch(*next)
			{
			case	'b':
							//Do Nothing as there is no need to alter the byte order of an int8 as it is already atomic
							block_offset += sizeof(uint8_t);
							break;
			case	's':
							*((uint16_t*)(block + block_offset)) = htobe16(*((uint16_t*)(block + block_offset)));
							block_offset += sizeof(uint16_t);
							break;
			case	'i':
							*((uint32_t*)(block + block_offset)) = htobe32(*((uint32_t*)(block + block_offset)));
							block_offset += sizeof(uint32_t);
							break;
			case	'l':
							*((uint64_t*)(block + block_offset)) = htobe64(*((uint64_t*)(block + block_offset)));
							block_offset += sizeof(uint64_t);
							break;
			case	'\0':	err |= 1;
							fmt_len_parsed = fmt_len;//What the hell have you done?
							break;
			}
		}
		fmt_len_parsed += 1;
	}
	if (err)
		return NULL;
	else
		return block;
}
/*
 * Function: netconv_ntoh
 * Description: converts a block of data from network byte order to host byte order. A format string is used to describe the type
 *  of data at each point in the block
 * Parameters:
 *  fmt_str: format string used for formatting the block of data. See netconv.h for details
 *  block: pointer to the base of the block of data to be converted
 * Returns:	Pointer to block if the operation succeed, NULL otherwise.
 * NB: The operation may fail if the format string is incorrectly formatted. This may result in block being corrupted
 */
void*	netconv_ntoh(const char* fmt_str, void* __restrict__ block)
{
	int err = 0;
	int i = 0;
	int fmt_len = strlen(fmt_str);
	int fmt_len_parsed = 0;
	int num_el = 0;
	int block_offset = 0;
	char* next = NULL;
	const char* prev = fmt_str;
	while (fmt_len_parsed < fmt_len)
	{
		num_el = strtol(fmt_str + fmt_len_parsed,&next,0);	//Parse the length of the next data block
		if (num_el == 0)					//Handle the case where the quantity is optional for fmt_str entries that have unity magnitude
		{									//If the value 1 is included, num_el will be set to 1 and next will point to the entry type
			num_el = 1;						//If the value is not included, num_el will be set to 0 and next will point to the entry type
		}
		else
		{
			fmt_len_parsed = (int)(next - prev);			prev = next;
		}
		for (i = 0; i < num_el; i++)
		{
			switch(*next)
			{
			case	'b':
							//Do Nothing as there is no need to alter the byte order of an int8 as it is already atomic
							block_offset += sizeof(uint8_t);
							break;
			case	's':
							*((uint16_t*)(block + block_offset)) = be16toh(*((uint16_t*)(block + block_offset)));
							block_offset += sizeof(uint16_t);
							break;
			case	'i':
							*((uint32_t*)(block + block_offset)) = be32toh(*((uint32_t*)(block + block_offset)));
							block_offset += sizeof(uint32_t);
							break;
			case	'l':
							*((uint64_t*)(block + block_offset)) = be64toh(*((uint64_t*)(block + block_offset)));
							block_offset += sizeof(uint64_t);
							break;
			case	'\0':	err |= 1;
							fmt_len_parsed = fmt_len;//What the hell have you done?
							break;
			}
		}
		fmt_len_parsed += 1;
	}
	if (err)
		return NULL;
	else
		return block;
}
