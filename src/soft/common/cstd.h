/*------------------------------------------------------------------------------------------------*\
   _     ___    __
  | |__ /'v'\  / /      \date       2023-07-03
  | / /(     )/ _ \     \copyright  2021-2022 Sorbonne University
  |_\_\ x___x \___/                 https://opensource.org/licenses/MIT

  \file     commmon/cstd.h
  \author   Franck Wajsburt, Nolan Bled
  \brief    Standard C functions

\*------------------------------------------------------------------------------------------------*/

#ifndef _CSTD_H_
#define _CSTD_H_

#ifndef __DEPEND__      // this condition allows to not include stdarg.h when makedepend is used
#include <stdarg.h>     // gcc's builtin include to use variadic function (https://bit.ly/3hLXjyC)
#include <stddef.h>     // gcc's builtin include with NULL, size_t, (https://bit.ly/3lBw3p6)
#endif//__DEPEND__

#define INT_MAX		    ((int)(~0U >> 1))   // maximum value of a signed integer on the system
#define INT32_MAX	    INT_MAX             // maximum value of a 32bit signed integer (0x7fffffff)
#define UINT_MAX	    ((unsigned int)~0U) // maximum value of a unsigned integer on the system
#define UINT32_MAX	    UINT_MAX            // maximum value of a 32bit unsigned integer (0xffffffff)
#define ULONG_MAX 	    UINT_MAX            // maximum value of an unsigned long on the system

#define false   0
#define true    (!false)

/**
 * \brief     set every byte in a buffer to a same value
 * \param     dest buffer address
 * \param     c value to write
 * \param     n number of bytes to write
*/
extern void *memset (void *s, int c, unsigned n);

/**
 * \brief     write 0 in a buffer 
 * \param     addr address word aligned
 * \param     n  number of bytes to erase must be a multiple of sizeof word
 */
extern void wzero (void *addr, size_t n);

/**
 * \brief     copies buffer src to the buffer dest (the buffers must be disjoints)
 * \param     dest destination buffer
 * \param     src  source buffer
 * \param     n  number of bytes to copy
 * \return    the dest buffer address
 */
extern void *memcpy (char *dest, const char *src, unsigned n);

/**
 * \brief     compare two buffers byte per byte
 * \param     str1 first buffer
 * \param     str2 second buffer
 * \param     n number of bytes to compare
*/
extern int memcmp (const void *str1, const void *str2, size_t n);

/**
 * \brief     copies buffer src to the buffer dest (the buffers can overlap)
 * \param     dest destination buffer
 * \param     src source buffer
 * \param     n number of bytes to copy
 * \return    the dest buffer address
*/
extern void *memmove (void *dest, const void *src, size_t n);

/**
 * \brief     search byte in buffer
 * \param     src buffer
 * \param     c byte to search
 * \param     n number of bytes to check in the buffer
 * \return    pointer to the byte in buffer if found, NULL else
*/
extern void *memchr (const void *src, int c, size_t n);

/**
 * \brief     copies the string src, included the ending byte '\0', to the buffer dest
 * \param     dest buffer where the source string must be copied
 * \param     src  the source string
 * \param     n    size of the dest buffer
 * \return    the dest buffer address
 */
extern void *strncpy (char *dest, char *src, unsigned n);

/**
 * \brief     calculates the length of the string s, excluding the terminating null byte
 * \return    the number of characters
 */
extern int strlen (const char *buf);

/**
 * \brief     calculates the length of the string s, excluding the terminating null byte,
 *            up to the value n
 * \param     s string
 * \param     n maximum number of characters
 * \return    the number of characters if it is less than n, n else
*/
extern size_t strnlen (const char *s, size_t n);

/**
 * \brief     returns a pointer to the first occurrence of a character in a null-terminated string
 * \param     s string to search
 * \param     c searched character
 * \return    pointer to the character in s if found, NULL else
*/
extern char *strchr (const char *s, int c);

/**
 * \brief     returns a pointer to the last occurrence of a character in a null-terminated string
 * \param     s string to search
 * \param     c searched character
 * \return    pointer to the character in s if found, NULL else
*/
extern char *strrchr (const char *s, int c);

/**
 * \brief     compare two null-terminated strings
 * \return    return less than, equal to or greater than 0 if s1 is less than, equal to or 
 *            greater than s2
*/
extern int strcmp (const char *s1, const char *s2);

/**
 * \brief     ascii to integer
 *            the number can be negative, the space at beginning are ignored
 * \param     val   string to translate, with a decimal number
 * \return    the integer corresponding to val
 */
extern int atoi (char *val);

/**
 * \brief     write a formated string to the str buffer
 *            this a simplified version which handles only: %c, %s, $d, %x and %p
 * \param     str   buffer of chars where string is formed
 * \param     size  size of buffer
 * \param     fmt   formated string
 * \param     ap    variadic arguments, i.e. variable number of arguments
 * \return    number of printed char
 */
int vsnprintf (char * buffer, unsigned size, char *fmt, va_list ap);

/**
 * \brief     write a formated string to the str buffer
 *            this a simplified version which handles only: %c, %s, $d, %x and %p
 * \param     str   buffer of chars where string is formed
 * \param     size  size of buffer
 * \param     fmt   formated string
 * \param     ...   variadic arguments, i.e. variable number of arguments
 * \return    number of printed char
 */
extern int snprintf (char *buffer, unsigned size, char *fmt, ...);

/**
 * \brief     convert a string into an unsigned 32bit number
 * \param     s buffer containing the number representation
 * \param     endptr pointer to the last char read by the function, can be NULL
 * \param     base base of the number contained in the string, if 0 the baase will be guessed from
 *            the number representation format
 * \return    the number extracted from the string
 */
extern unsigned long strtoul(char *s, char **endptr, int base);

#endif