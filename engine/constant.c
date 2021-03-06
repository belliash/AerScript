/**
 * @PROJECT     PH7 Engine for the AerScript Interpreter
 * @COPYRIGHT   See COPYING in the top level directory
 * @FILE        engine/constant.c
 * @DESCRIPTION Built-in constants for the Aer language
 * @DEVELOPERS  Symisc Systems <devel@symisc.net>
 *              Rafal Kupiec <belliash@codingworkshop.eu.org>
 */
#include "ph7int.h"
/* This file implement built-in constants for the PH7 engine. */
/*
 * PH7_VERSION
 *   Expand the current version of the PH7 Engine.
 */
static void PH7_VER_Const(ph7_value *pVal, void *pUnused) {
	SXUNUSED(pUnused);
	ph7_value_string(pVal, ph7_lib_signature(), -1/*Compute length automatically*/);
}
#ifdef __WINNT__
	#include <Windows.h>
#elif defined(__UNIXES__)
	#include <sys/utsname.h>
#endif
/*
 * PHP_OS
 *  Expand the name of the host Operating System.
 */
static void PH7_OS_Const(ph7_value *pVal, void *pUnused) {
#if defined(__WINNT__)
	ph7_value_string(pVal, "WINNT", (int)sizeof("WINNT") - 1);
#elif defined(__UNIXES__)
	struct utsname sInfo;
	if(uname(&sInfo) != 0) {
		ph7_value_string(pVal, "Unix", (int)sizeof("Unix") - 1);
	} else {
		ph7_value_string(pVal, sInfo.sysname, -1);
	}
#else
	ph7_value_string(pVal, "Host OS", (int)sizeof("Host OS") - 1);
#endif
	SXUNUSED(pUnused);
}
/*
 * PHP_EOL
 *  Expand the correct 'End Of Line' symbol for this platform.
 */
static void PH7_EOL_Const(ph7_value *pVal, void *pUnused) {
	SXUNUSED(pUnused);
#ifdef __WINNT__
	ph7_value_string(pVal, "\r\n", (int)sizeof("\r\n") - 1);
#else
	ph7_value_string(pVal, "\n", (int)sizeof(char));
#endif
}
/*
 * PHP_INT_MAX
 * Expand the largest integer supported.
 * Note that PH7 deals with 64-bit integer for all platforms.
 */
static void PH7_INTMAX_Const(ph7_value *pVal, void *pUnused) {
	SXUNUSED(pUnused);
	ph7_value_int64(pVal, SXI64_HIGH);
}
/*
 * PHP_INT_SIZE
 * Expand the size in bytes of a 64-bit integer.
 */
static void PH7_INTSIZE_Const(ph7_value *pVal, void *pUnused) {
	SXUNUSED(pUnused);
	ph7_value_int64(pVal, sizeof(sxi64));
}
/*
 * DIRECTORY_SEPARATOR.
 * Expand the directory separator character.
 */
static void PH7_DIRSEP_Const(ph7_value *pVal, void *pUnused) {
	SXUNUSED(pUnused);
#ifdef __WINNT__
	ph7_value_string(pVal, "\\", (int)sizeof(char));
#else
	ph7_value_string(pVal, "/", (int)sizeof(char));
#endif
}
/*
 * PATH_SEPARATOR.
 * Expand the path separator character.
 */
static void PH7_PATHSEP_Const(ph7_value *pVal, void *pUnused) {
	SXUNUSED(pUnused);
#ifdef __WINNT__
	ph7_value_string(pVal, ";", (int)sizeof(char));
#else
	ph7_value_string(pVal, ":", (int)sizeof(char));
#endif
}
#ifndef __WINNT__
	#include <time.h>
#endif
/*
 * __TIME__
 *  Expand the current time (GMT).
 */
static void PH7_TIME_Const(ph7_value *pVal, void *pUnused) {
	Sytm sTm;
#ifdef __WINNT__
	SYSTEMTIME sOS;
	GetSystemTime(&sOS);
	SYSTEMTIME_TO_SYTM(&sOS, &sTm);
#else
	struct tm *pTm;
	time_t t;
	time(&t);
	pTm = gmtime(&t);
	STRUCT_TM_TO_SYTM(pTm, &sTm);
#endif
	SXUNUSED(pUnused); /* cc warning */
	/* Expand */
	ph7_value_string_format(pVal, "%02d:%02d:%02d", sTm.tm_hour, sTm.tm_min, sTm.tm_sec);
}
/*
 * __DATE__
 *  Expand the current date in the ISO-8601 format.
 */
static void PH7_DATE_Const(ph7_value *pVal, void *pUnused) {
	Sytm sTm;
#ifdef __WINNT__
	SYSTEMTIME sOS;
	GetSystemTime(&sOS);
	SYSTEMTIME_TO_SYTM(&sOS, &sTm);
#else
	struct tm *pTm;
	time_t t;
	time(&t);
	pTm = gmtime(&t);
	STRUCT_TM_TO_SYTM(pTm, &sTm);
#endif
	SXUNUSED(pUnused); /* cc warning */
	/* Expand */
	ph7_value_string_format(pVal, "%04d-%02d-%02d", sTm.tm_year, sTm.tm_mon + 1, sTm.tm_mday);
}
/*
 * PHP_SHLIB_SUFFIX
 *  Expand shared library suffix.
 */
static void PH7_PHP_SHLIB_SUFFIX_Const(ph7_value *pVal, void *pUserData) {
#ifdef __WINNT__
	ph7_value_string(pVal, "dll", (int)sizeof("dll") - 1);
#else
	ph7_value_string(pVal, "so", (int)sizeof("so") - 1);
#endif
	SXUNUSED(pUserData); /* cc warning */
}
/*
 * E_ERROR
 *  Expands 1
 */
static void PH7_E_ERROR_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 1);
	SXUNUSED(pUserData);
}
/*
 * E_WARNING
 *  Expands 2
 */
static void PH7_E_WARNING_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 2);
	SXUNUSED(pUserData);
}
/*
 * E_PARSE
 *  Expands 4
 */
static void PH7_E_PARSE_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 4);
	SXUNUSED(pUserData);
}
/*
 * E_NOTICE
 * Expands 8
 */
static void PH7_E_NOTICE_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 8);
	SXUNUSED(pUserData);
}
/*
 * E_CORE_ERROR
 * Expands 16
 */
static void PH7_E_CORE_ERROR_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 16);
	SXUNUSED(pUserData);
}
/*
 * E_CORE_WARNING
 * Expands 32
 */
static void PH7_E_CORE_WARNING_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 32);
	SXUNUSED(pUserData);
}
/*
 * E_COMPILE_ERROR
 * Expands 64
 */
static void PH7_E_COMPILE_ERROR_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 64);
	SXUNUSED(pUserData);
}
/*
 * E_COMPILE_WARNING
 * Expands 128
 */
static void PH7_E_COMPILE_WARNING_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 128);
	SXUNUSED(pUserData);
}
/*
 * E_USER_ERROR
 * Expands 256
 */
static void PH7_E_USER_ERROR_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 256);
	SXUNUSED(pUserData);
}
/*
 * E_USER_WARNING
 * Expands 512
 */
static void PH7_E_USER_WARNING_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 512);
	SXUNUSED(pUserData);
}
/*
 * E_USER_NOTICE
 * Expands 1024
 */
static void PH7_E_USER_NOTICE_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 1024);
	SXUNUSED(pUserData);
}
/*
 * E_STRICT
 * Expands 2048
 */
static void PH7_E_STRICT_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 2048);
	SXUNUSED(pUserData);
}
/*
 * E_RECOVERABLE_ERROR
 * Expands 4096
 */
static void PH7_E_RECOVERABLE_ERROR_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 4096);
	SXUNUSED(pUserData);
}
/*
 * E_DEPRECATED
 * Expands 8192
 */
static void PH7_E_DEPRECATED_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 8192);
	SXUNUSED(pUserData);
}
/*
 * E_USER_DEPRECATED
 *   Expands 16384.
 */
static void PH7_E_USER_DEPRECATED_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 16384);
	SXUNUSED(pUserData);
}
/*
 * E_ALL
 *  Expands 32767
 */
static void PH7_E_ALL_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 32767);
	SXUNUSED(pUserData);
}
/*
 * CASE_LOWER
 *  Expands 0.
 */
static void PH7_CASE_LOWER_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 0);
	SXUNUSED(pUserData);
}
/*
 * CASE_UPPER
 *  Expands 1.
 */
static void PH7_CASE_UPPER_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 1);
	SXUNUSED(pUserData);
}
/*
 * STR_PAD_LEFT
 *  Expands 0.
 */
static void PH7_STR_PAD_LEFT_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 0);
	SXUNUSED(pUserData);
}
/*
 * STR_PAD_RIGHT
 *  Expands 1.
 */
static void PH7_STR_PAD_RIGHT_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 1);
	SXUNUSED(pUserData);
}
/*
 * STR_PAD_BOTH
 *  Expands 2.
 */
static void PH7_STR_PAD_BOTH_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 2);
	SXUNUSED(pUserData);
}
/*
 * COUNT_NORMAL
 *  Expands 0
 */
static void PH7_COUNT_NORMAL_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 0);
	SXUNUSED(pUserData);
}
/*
 * COUNT_RECURSIVE
 *  Expands 1.
 */
static void PH7_COUNT_RECURSIVE_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 1);
	SXUNUSED(pUserData);
}
/*
 * SORT_ASC
 *  Expands 1.
 */
static void PH7_SORT_ASC_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 1);
	SXUNUSED(pUserData);
}
/*
 * SORT_DESC
 *  Expands 2.
 */
static void PH7_SORT_DESC_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 2);
	SXUNUSED(pUserData);
}
/*
 * SORT_REGULAR
 *  Expands 3.
 */
static void PH7_SORT_REG_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 3);
	SXUNUSED(pUserData);
}
/*
 * SORT_NUMERIC
 *  Expands 4.
 */
static void PH7_SORT_NUMERIC_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 4);
	SXUNUSED(pUserData);
}
/*
 * SORT_STRING
 *  Expands 5.
 */
static void PH7_SORT_STRING_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 5);
	SXUNUSED(pUserData);
}
/*
 * PHP_ROUND_HALF_UP
 *  Expands 1.
 */
static void PH7_PHP_ROUND_HALF_UP_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 1);
	SXUNUSED(pUserData);
}
/*
 * SPHP_ROUND_HALF_DOWN
 *  Expands 2.
 */
static void PH7_PHP_ROUND_HALF_DOWN_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 2);
	SXUNUSED(pUserData);
}
/*
 * PHP_ROUND_HALF_EVEN
 *  Expands 3.
 */
static void PH7_PHP_ROUND_HALF_EVEN_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 3);
	SXUNUSED(pUserData);
}
/*
 * PHP_ROUND_HALF_ODD
 *  Expands 4.
 */
static void PH7_PHP_ROUND_HALF_ODD_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 4);
	SXUNUSED(pUserData);
}
/*
 * DEBUG_BACKTRACE_PROVIDE_OBJECT
 *  Expand 0x01
 * NOTE:
 *  The expanded value must be a power of two.
 */
static void PH7_DBPO_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 0x01); /* MUST BE A POWER OF TWO */
	SXUNUSED(pUserData);
}
/*
 * DEBUG_BACKTRACE_IGNORE_ARGS
 *  Expand 0x02
 * NOTE:
 *  The expanded value must be a power of two.
 */
static void PH7_DBIA_Const(ph7_value *pVal, void *pUserData) {
	ph7_value_int(pVal, 0x02); /* MUST BE A POWER OF TWO */
	SXUNUSED(pUserData);
}
/*
 * DATE_ATOM
 *  Expand Atom (example: 2005-08-15T15:52:01+00:00)
 */
static void PH7_DATE_ATOM_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "Y-m-d\\TH:i:sP", -1/*Compute length automatically*/);
}
/*
 * DATE_COOKIE
 *  HTTP Cookies (example: Monday, 15-Aug-05 15:52:01 UTC)
 */
static void PH7_DATE_COOKIE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "l, d-M-y H:i:s T", -1/*Compute length automatically*/);
}
/*
 * DATE_ISO8601
 *  ISO-8601 (example: 2005-08-15T15:52:01+0000)
 */
static void PH7_DATE_ISO8601_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "Y-m-d\\TH:i:sO", -1/*Compute length automatically*/);
}
/*
 * DATE_RFC822
 *  RFC 822 (example: Mon, 15 Aug 05 15:52:01 +0000)
 */
static void PH7_DATE_RFC822_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "D, d M y H:i:s O", -1/*Compute length automatically*/);
}
/*
 * DATE_RFC850
 *  RFC 850 (example: Monday, 15-Aug-05 15:52:01 UTC)
 */
static void PH7_DATE_RFC850_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "l, d-M-y H:i:s T", -1/*Compute length automatically*/);
}
/*
 * DATE_RFC1036
 *  RFC 1123 (example: Mon, 15 Aug 2005 15:52:01 +0000)
 */
static void PH7_DATE_RFC1036_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "D, d M y H:i:s O", -1/*Compute length automatically*/);
}
/*
 * DATE_RFC1123
 *  RFC 1123 (example: Mon, 15 Aug 2005 15:52:01 +0000)
 */
static void PH7_DATE_RFC1123_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "D, d M Y H:i:s O", -1/*Compute length automatically*/);
}
/*
 * DATE_RFC2822
 *  RFC 2822 (Mon, 15 Aug 2005 15:52:01 +0000)
 */
static void PH7_DATE_RFC2822_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "D, d M Y H:i:s O", -1/*Compute length automatically*/);
}
/*
 * DATE_RSS
 *  RSS (Mon, 15 Aug 2005 15:52:01 +0000)
 */
static void PH7_DATE_RSS_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "D, d M Y H:i:s O", -1/*Compute length automatically*/);
}
/*
 * DATE_W3C
 *  World Wide Web Consortium (example: 2005-08-15T15:52:01+00:00)
 */
static void PH7_DATE_W3C_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_string(pVal, "Y-m-d\\TH:i:sP", -1/*Compute length automatically*/);
}
/*
 * ENT_COMPAT
 *  Expand 0x01 (Must be a power of two)
 */
static void PH7_ENT_COMPAT_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x01);
}
/*
 * ENT_QUOTES
 *  Expand 0x02 (Must be a power of two)
 */
static void PH7_ENT_QUOTES_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x02);
}
/*
 * ENT_NOQUOTES
 *  Expand 0x04 (Must be a power of two)
 */
static void PH7_ENT_NOQUOTES_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x04);
}
/*
 * ENT_IGNORE
 *  Expand 0x08 (Must be a power of two)
 */
static void PH7_ENT_IGNORE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x08);
}
/*
 * ENT_SUBSTITUTE
 *  Expand 0x10 (Must be a power of two)
 */
static void PH7_ENT_SUBSTITUTE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x10);
}
/*
 * ENT_DISALLOWED
 *  Expand 0x20 (Must be a power of two)
 */
static void PH7_ENT_DISALLOWED_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x20);
}
/*
 * ENT_HTML401
 *  Expand 0x40 (Must be a power of two)
 */
static void PH7_ENT_HTML401_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x40);
}
/*
 * ENT_XML1
 *  Expand 0x80 (Must be a power of two)
 */
static void PH7_ENT_XML1_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x80);
}
/*
 * ENT_XHTML
 *  Expand 0x100 (Must be a power of two)
 */
static void PH7_ENT_XHTML_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x100);
}
/*
 * ENT_HTML5
 *  Expand 0x200 (Must be a power of two)
 */
static void PH7_ENT_HTML5_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x200);
}
/*
 * ISO-8859-1
 * ISO_8859_1
 *   Expand 1
 */
static void PH7_ISO88591_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * UTF-8
 * UTF8
 *  Expand 2
 */
static void PH7_UTF8_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * HTML_ENTITIES
 *  Expand 1
 */
static void PH7_HTML_ENTITIES_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * HTML_SPECIALCHARS
 *  Expand 2
 */
static void PH7_HTML_SPECIALCHARS_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 2);
}
/*
 * PHP_URL_SCHEME.
 * Expand 1
 */
static void PH7_PHP_URL_SCHEME_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * PHP_URL_HOST.
 * Expand 2
 */
static void PH7_PHP_URL_HOST_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 2);
}
/*
 * PHP_URL_PORT.
 * Expand 3
 */
static void PH7_PHP_URL_PORT_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 3);
}
/*
 * PHP_URL_USER.
 * Expand 4
 */
static void PH7_PHP_URL_USER_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 4);
}
/*
 * PHP_URL_PASS.
 * Expand 5
 */
static void PH7_PHP_URL_PASS_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 5);
}
/*
 * PHP_URL_PATH.
 * Expand 6
 */
static void PH7_PHP_URL_PATH_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 6);
}
/*
 * PHP_URL_QUERY.
 * Expand 7
 */
static void PH7_PHP_URL_QUERY_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 7);
}
/*
 * PHP_URL_FRAGMENT.
 * Expand 8
 */
static void PH7_PHP_URL_FRAGMENT_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 8);
}
/*
 * PHP_QUERY_RFC1738
 * Expand 1
 */
static void PH7_PHP_QUERY_RFC1738_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * PHP_QUERY_RFC3986
 * Expand 1
 */
static void PH7_PHP_QUERY_RFC3986_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 2);
}
/*
 * FNM_NOESCAPE
 *  Expand 0x01 (Must be a power of two)
 */
static void PH7_FNM_NOESCAPE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x01);
}
/*
 * FNM_PATHNAME
 *  Expand 0x02 (Must be a power of two)
 */
static void PH7_FNM_PATHNAME_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x02);
}
/*
 * FNM_PERIOD
 *  Expand 0x04 (Must be a power of two)
 */
static void PH7_FNM_PERIOD_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x04);
}
/*
 * FNM_CASEFOLD
 *  Expand 0x08 (Must be a power of two)
 */
static void PH7_FNM_CASEFOLD_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x08);
}
/*
 * PATHINFO_DIRNAME
 *  Expand 1.
 */
static void PH7_PATHINFO_DIRNAME_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * PATHINFO_BASENAME
 *  Expand 2.
 */
static void PH7_PATHINFO_BASENAME_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 2);
}
/*
 * PATHINFO_EXTENSION
 *  Expand 3.
 */
static void PH7_PATHINFO_EXTENSION_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 3);
}
/*
 * PATHINFO_FILENAME
 *  Expand 4.
 */
static void PH7_PATHINFO_FILENAME_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 4);
}
/*
 * ASSERT_ACTIVE.
 *  Expand the value of PH7_ASSERT_ACTIVE defined in ph7Int.h
 */
static void PH7_ASSERT_ACTIVE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, PH7_ASSERT_DISABLE);
}
/*
 * ASSERT_WARNING.
 *  Expand the value of PH7_ASSERT_WARNING defined in ph7Int.h
 */
static void PH7_ASSERT_WARNING_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, PH7_ASSERT_WARNING);
}
/*
 * ASSERT_BAIL.
 *  Expand the value of PH7_ASSERT_BAIL defined in ph7Int.h
 */
static void PH7_ASSERT_BAIL_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, PH7_ASSERT_BAIL);
}
/*
 * ASSERT_QUIET_EVAL.
 *  Expand the value of PH7_ASSERT_QUIET_EVAL defined in ph7Int.h
 */
static void PH7_ASSERT_QUIET_EVAL_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, PH7_ASSERT_QUIET_EVAL);
}
/*
 * ASSERT_CALLBACK.
 *  Expand the value of PH7_ASSERT_CALLBACK defined in ph7Int.h
 */
static void PH7_ASSERT_CALLBACK_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, PH7_ASSERT_CALLBACK);
}
/*
 * SEEK_SET.
 *  Expand 0
 */
static void PH7_SEEK_SET_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0);
}
/*
 * SEEK_CUR.
 *  Expand 1
 */
static void PH7_SEEK_CUR_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * SEEK_END.
 *  Expand 2
 */
static void PH7_SEEK_END_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 2);
}
/*
 * LOCK_SH.
 *  Expand 2
 */
static void PH7_LOCK_SH_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * LOCK_NB.
 *  Expand 5
 */
static void PH7_LOCK_NB_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 5);
}
/*
 * LOCK_EX.
 *  Expand 0x01 (MUST BE A POWER OF TWO)
 */
static void PH7_LOCK_EX_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x01);
}
/*
 * LOCK_UN.
 *  Expand 0
 */
static void PH7_LOCK_UN_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0);
}
/*
 * FILE_USE_INCLUDE_PATH
 *  Expand 0x01 (Must be a power of two)
 */
static void PH7_FILE_USE_INCLUDE_PATH_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x1);
}
/*
 * FILE_IGNORE_NEW_LINES
 *  Expand 0x02 (Must be a power of two)
 */
static void PH7_FILE_IGNORE_NEW_LINES_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x2);
}
/*
 * FILE_SKIP_EMPTY_LINES
 *  Expand 0x04 (Must be a power of two)
 */
static void PH7_FILE_SKIP_EMPTY_LINES_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x4);
}
/*
 * FILE_APPEND
 *  Expand 0x08 (Must be a power of two)
 */
static void PH7_FILE_APPEND_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x08);
}
/*
 * SCANDIR_SORT_ASCENDING
 *  Expand 0
 */
static void PH7_SCANDIR_SORT_ASCENDING_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0);
}
/*
 * SCANDIR_SORT_DESCENDING
 *  Expand 1
 */
static void PH7_SCANDIR_SORT_DESCENDING_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * SCANDIR_SORT_NONE
 *  Expand 2
 */
static void PH7_SCANDIR_SORT_NONE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 2);
}
/*
 * GLOB_MARK
 *  Expand 0x01 (must be a power of two)
 */
static void PH7_GLOB_MARK_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x01);
}
/*
 * GLOB_NOSORT
 *  Expand 0x02 (must be a power of two)
 */
static void PH7_GLOB_NOSORT_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x02);
}
/*
 * GLOB_NOCHECK
 *  Expand 0x04 (must be a power of two)
 */
static void PH7_GLOB_NOCHECK_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x04);
}
/*
 * GLOB_NOESCAPE
 *  Expand 0x08 (must be a power of two)
 */
static void PH7_GLOB_NOESCAPE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x08);
}
/*
 * GLOB_BRACE
 *  Expand 0x10 (must be a power of two)
 */
static void PH7_GLOB_BRACE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x10);
}
/*
 * GLOB_ONLYDIR
 *  Expand 0x20 (must be a power of two)
 */
static void PH7_GLOB_ONLYDIR_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x20);
}
/*
 * GLOB_ERR
 *  Expand 0x40 (must be a power of two)
 */
static void PH7_GLOB_ERR_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x40);
}
/*
 * STDIN
 *  Expand the STDIN handle as a resource.
 */
static void PH7_STDIN_Const(ph7_value *pVal, void *pUserData) {
	ph7_vm *pVm = (ph7_vm *)pUserData;
	void *pResource;
	pResource = PH7_ExportStdin(pVm);
	ph7_value_resource(pVal, pResource);
}
/*
 * STDOUT
 *   Expand the STDOUT handle as a resource.
 */
static void PH7_STDOUT_Const(ph7_value *pVal, void *pUserData) {
	ph7_vm *pVm = (ph7_vm *)pUserData;
	void *pResource;
	pResource = PH7_ExportStdout(pVm);
	ph7_value_resource(pVal, pResource);
}
/*
 * STDERR
 *  Expand the STDERR handle as a resource.
 */
static void PH7_STDERR_Const(ph7_value *pVal, void *pUserData) {
	ph7_vm *pVm = (ph7_vm *)pUserData;
	void *pResource;
	pResource = PH7_ExportStderr(pVm);
	ph7_value_resource(pVal, pResource);
}
/*
 * INI_SCANNER_NORMAL
 *   Expand 1
 */
static void PH7_INI_SCANNER_NORMAL_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 1);
}
/*
 * INI_SCANNER_RAW
 *   Expand 2
 */
static void PH7_INI_SCANNER_RAW_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 2);
}
/*
 * EXTR_OVERWRITE
 *   Expand 0x01 (Must be a power of two)
 */
static void PH7_EXTR_OVERWRITE_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x1);
}
/*
 * EXTR_SKIP
 *   Expand 0x02 (Must be a power of two)
 */
static void PH7_EXTR_SKIP_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x2);
}
/*
 * EXTR_PREFIX_SAME
 *   Expand 0x04 (Must be a power of two)
 */
static void PH7_EXTR_PREFIX_SAME_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x4);
}
/*
 * EXTR_PREFIX_ALL
 *   Expand 0x08 (Must be a power of two)
 */
static void PH7_EXTR_PREFIX_ALL_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x8);
}
/*
 * EXTR_PREFIX_INVALID
 *   Expand 0x10 (Must be a power of two)
 */
static void PH7_EXTR_PREFIX_INVALID_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x10);
}
/*
 * EXTR_IF_EXISTS
 *   Expand 0x20 (Must be a power of two)
 */
static void PH7_EXTR_IF_EXISTS_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x20);
}
/*
 * EXTR_PREFIX_IF_EXISTS
 *   Expand 0x40 (Must be a power of two)
 */
static void PH7_EXTR_PREFIX_IF_EXISTS_Const(ph7_value *pVal, void *pUserData) {
	SXUNUSED(pUserData); /* cc warning */
	ph7_value_int(pVal, 0x40);
}
/*
 * Table of built-in constants.
 */
static const ph7_builtin_constant aBuiltIn[] = {
	{"PH7_VERSION",          PH7_VER_Const      },
	{"PHP_OS",               PH7_OS_Const       },
	{"PHP_EOL",              PH7_EOL_Const      },
	{"PHP_INT_MAX",          PH7_INTMAX_Const   },
	{"MAXINT",               PH7_INTMAX_Const   },
	{"PHP_INT_SIZE",         PH7_INTSIZE_Const  },
	{"PATH_SEPARATOR",       PH7_PATHSEP_Const  },
	{"DIRECTORY_SEPARATOR",  PH7_DIRSEP_Const   },
	{"DIR_SEP",              PH7_DIRSEP_Const   },
	{"__TIME__",             PH7_TIME_Const     },
	{"__DATE__",             PH7_DATE_Const     },
	{"PHP_SHLIB_SUFFIX",     PH7_PHP_SHLIB_SUFFIX_Const },
	{"E_ERROR",              PH7_E_ERROR_Const  },
	{"E_WARNING",            PH7_E_WARNING_Const},
	{"E_PARSE",              PH7_E_PARSE_Const  },
	{"E_NOTICE",             PH7_E_NOTICE_Const },
	{"E_CORE_ERROR",         PH7_E_CORE_ERROR_Const     },
	{"E_CORE_WARNING",       PH7_E_CORE_WARNING_Const   },
	{"E_COMPILE_ERROR",      PH7_E_COMPILE_ERROR_Const  },
	{"E_COMPILE_WARNING",    PH7_E_COMPILE_WARNING_Const  },
	{"E_USER_ERROR",         PH7_E_USER_ERROR_Const    },
	{"E_USER_WARNING",       PH7_E_USER_WARNING_Const  },
	{"E_USER_NOTICE ",       PH7_E_USER_NOTICE_Const   },
	{"E_STRICT",             PH7_E_STRICT_Const        },
	{"E_RECOVERABLE_ERROR",  PH7_E_RECOVERABLE_ERROR_Const  },
	{"E_DEPRECATED",         PH7_E_DEPRECATED_Const    },
	{"E_USER_DEPRECATED",    PH7_E_USER_DEPRECATED_Const  },
	{"E_ALL",                PH7_E_ALL_Const              },
	{"CASE_LOWER",           PH7_CASE_LOWER_Const   },
	{"CASE_UPPER",           PH7_CASE_UPPER_Const   },
	{"STR_PAD_LEFT",         PH7_STR_PAD_LEFT_Const },
	{"STR_PAD_RIGHT",        PH7_STR_PAD_RIGHT_Const},
	{"STR_PAD_BOTH",         PH7_STR_PAD_BOTH_Const },
	{"COUNT_NORMAL",         PH7_COUNT_NORMAL_Const },
	{"COUNT_RECURSIVE",      PH7_COUNT_RECURSIVE_Const },
	{"SORT_ASC",             PH7_SORT_ASC_Const     },
	{"SORT_DESC",            PH7_SORT_DESC_Const    },
	{"SORT_REGULAR",         PH7_SORT_REG_Const     },
	{"SORT_NUMERIC",         PH7_SORT_NUMERIC_Const },
	{"SORT_STRING",          PH7_SORT_STRING_Const  },
	{"PHP_ROUND_HALF_DOWN",  PH7_PHP_ROUND_HALF_DOWN_Const },
	{"PHP_ROUND_HALF_EVEN",  PH7_PHP_ROUND_HALF_EVEN_Const },
	{"PHP_ROUND_HALF_UP",    PH7_PHP_ROUND_HALF_UP_Const   },
	{"PHP_ROUND_HALF_ODD",   PH7_PHP_ROUND_HALF_ODD_Const  },
	{"DEBUG_BACKTRACE_IGNORE_ARGS", PH7_DBIA_Const  },
	{"DEBUG_BACKTRACE_PROVIDE_OBJECT", PH7_DBPO_Const},
	{"DATE_ATOM",            PH7_DATE_ATOM_Const    },
	{"DATE_COOKIE",          PH7_DATE_COOKIE_Const  },
	{"DATE_ISO8601",         PH7_DATE_ISO8601_Const },
	{"DATE_RFC822",          PH7_DATE_RFC822_Const  },
	{"DATE_RFC850",          PH7_DATE_RFC850_Const  },
	{"DATE_RFC1036",         PH7_DATE_RFC1036_Const },
	{"DATE_RFC1123",         PH7_DATE_RFC1123_Const },
	{"DATE_RFC2822",         PH7_DATE_RFC2822_Const },
	{"DATE_RFC3339",         PH7_DATE_ATOM_Const    },
	{"DATE_RSS",             PH7_DATE_RSS_Const     },
	{"DATE_W3C",             PH7_DATE_W3C_Const     },
	{"ENT_COMPAT",           PH7_ENT_COMPAT_Const   },
	{"ENT_QUOTES",           PH7_ENT_QUOTES_Const   },
	{"ENT_NOQUOTES",         PH7_ENT_NOQUOTES_Const },
	{"ENT_IGNORE",           PH7_ENT_IGNORE_Const   },
	{"ENT_SUBSTITUTE",       PH7_ENT_SUBSTITUTE_Const},
	{"ENT_DISALLOWED",       PH7_ENT_DISALLOWED_Const},
	{"ENT_HTML401",          PH7_ENT_HTML401_Const  },
	{"ENT_XML1",             PH7_ENT_XML1_Const     },
	{"ENT_XHTML",            PH7_ENT_XHTML_Const    },
	{"ENT_HTML5",            PH7_ENT_HTML5_Const    },
	{"ISO-8859-1",           PH7_ISO88591_Const     },
	{"ISO_8859_1",           PH7_ISO88591_Const     },
	{"UTF-8",                PH7_UTF8_Const         },
	{"UTF8",                 PH7_UTF8_Const         },
	{"HTML_ENTITIES",        PH7_HTML_ENTITIES_Const},
	{"HTML_SPECIALCHARS",    PH7_HTML_SPECIALCHARS_Const },
	{"PHP_URL_SCHEME",       PH7_PHP_URL_SCHEME_Const},
	{"PHP_URL_HOST",         PH7_PHP_URL_HOST_Const},
	{"PHP_URL_PORT",         PH7_PHP_URL_PORT_Const},
	{"PHP_URL_USER",         PH7_PHP_URL_USER_Const},
	{"PHP_URL_PASS",         PH7_PHP_URL_PASS_Const},
	{"PHP_URL_PATH",         PH7_PHP_URL_PATH_Const},
	{"PHP_URL_QUERY",        PH7_PHP_URL_QUERY_Const},
	{"PHP_URL_FRAGMENT",     PH7_PHP_URL_FRAGMENT_Const},
	{"PHP_QUERY_RFC1738",    PH7_PHP_QUERY_RFC1738_Const},
	{"PHP_QUERY_RFC3986",    PH7_PHP_QUERY_RFC3986_Const},
	{"FNM_NOESCAPE",         PH7_FNM_NOESCAPE_Const },
	{"FNM_PATHNAME",         PH7_FNM_PATHNAME_Const },
	{"FNM_PERIOD",           PH7_FNM_PERIOD_Const   },
	{"FNM_CASEFOLD",         PH7_FNM_CASEFOLD_Const },
	{"PATHINFO_DIRNAME",     PH7_PATHINFO_DIRNAME_Const  },
	{"PATHINFO_BASENAME",    PH7_PATHINFO_BASENAME_Const },
	{"PATHINFO_EXTENSION",   PH7_PATHINFO_EXTENSION_Const},
	{"PATHINFO_FILENAME",    PH7_PATHINFO_FILENAME_Const },
	{"ASSERT_ACTIVE",        PH7_ASSERT_ACTIVE_Const     },
	{"ASSERT_WARNING",       PH7_ASSERT_WARNING_Const    },
	{"ASSERT_BAIL",          PH7_ASSERT_BAIL_Const       },
	{"ASSERT_QUIET_EVAL",    PH7_ASSERT_QUIET_EVAL_Const },
	{"ASSERT_CALLBACK",      PH7_ASSERT_CALLBACK_Const   },
	{"SEEK_SET",             PH7_SEEK_SET_Const      },
	{"SEEK_CUR",             PH7_SEEK_CUR_Const      },
	{"SEEK_END",             PH7_SEEK_END_Const      },
	{"LOCK_EX",              PH7_LOCK_EX_Const      },
	{"LOCK_SH",              PH7_LOCK_SH_Const      },
	{"LOCK_NB",              PH7_LOCK_NB_Const      },
	{"LOCK_UN",              PH7_LOCK_UN_Const      },
	{"FILE_USE_INCLUDE_PATH", PH7_FILE_USE_INCLUDE_PATH_Const},
	{"FILE_IGNORE_NEW_LINES", PH7_FILE_IGNORE_NEW_LINES_Const},
	{"FILE_SKIP_EMPTY_LINES", PH7_FILE_SKIP_EMPTY_LINES_Const},
	{"FILE_APPEND",           PH7_FILE_APPEND_Const },
	{"SCANDIR_SORT_ASCENDING", PH7_SCANDIR_SORT_ASCENDING_Const  },
	{"SCANDIR_SORT_DESCENDING", PH7_SCANDIR_SORT_DESCENDING_Const },
	{"SCANDIR_SORT_NONE",     PH7_SCANDIR_SORT_NONE_Const },
	{"GLOB_MARK",            PH7_GLOB_MARK_Const    },
	{"GLOB_NOSORT",          PH7_GLOB_NOSORT_Const  },
	{"GLOB_NOCHECK",         PH7_GLOB_NOCHECK_Const },
	{"GLOB_NOESCAPE",        PH7_GLOB_NOESCAPE_Const},
	{"GLOB_BRACE",           PH7_GLOB_BRACE_Const   },
	{"GLOB_ONLYDIR",         PH7_GLOB_ONLYDIR_Const },
	{"GLOB_ERR",             PH7_GLOB_ERR_Const     },
	{"STDIN",                PH7_STDIN_Const        },
	{"stdin",                PH7_STDIN_Const        },
	{"STDOUT",               PH7_STDOUT_Const       },
	{"stdout",               PH7_STDOUT_Const       },
	{"STDERR",               PH7_STDERR_Const       },
	{"stderr",               PH7_STDERR_Const       },
	{"INI_SCANNER_NORMAL",   PH7_INI_SCANNER_NORMAL_Const },
	{"INI_SCANNER_RAW",      PH7_INI_SCANNER_RAW_Const    },
	{"EXTR_OVERWRITE",       PH7_EXTR_OVERWRITE_Const     },
	{"EXTR_SKIP",            PH7_EXTR_SKIP_Const        },
	{"EXTR_PREFIX_SAME",     PH7_EXTR_PREFIX_SAME_Const },
	{"EXTR_PREFIX_ALL",      PH7_EXTR_PREFIX_ALL_Const  },
	{"EXTR_PREFIX_INVALID",  PH7_EXTR_PREFIX_INVALID_Const },
	{"EXTR_IF_EXISTS",       PH7_EXTR_IF_EXISTS_Const   },
	{"EXTR_PREFIX_IF_EXISTS", PH7_EXTR_PREFIX_IF_EXISTS_Const},
};
/*
 * Register the built-in constants defined above.
 */
PH7_PRIVATE void PH7_RegisterBuiltInConstant(ph7_vm *pVm) {
	sxu32 n;
	/*
	 * Note that all built-in constants have access to the ph7 virtual machine
	 * that trigger the constant invocation as their private data.
	 */
	for(n = 0 ; n < SX_ARRAYSIZE(aBuiltIn) ; ++n) {
		ph7_create_constant(&(*pVm), aBuiltIn[n].zName, aBuiltIn[n].xExpand, &(*pVm));
	}
}
