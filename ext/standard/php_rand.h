/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2016 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Rasmus Lerdorf <rasmus@php.net>                             |
   |          Zeev Suraski <zeev@zend.com>                                |
   |          Pedro Melo <melo@ip.pt>                                     |
   |          Sterling Hughes <sterling@php.net>                          |
   |                                                                      |
   | Based on code from: Shawn Cokus <Cokus@math.washington.edu>          |
   +----------------------------------------------------------------------+
 */
/* $Id$ */

#ifndef PHP_RAND_H
#define	PHP_RAND_H

#include <stdlib.h>
#include "basic_functions.h"
#include "php_lcg.h"

/* MT Rand */
#define PHP_MT_RAND_MAX ((zend_long) (0xFFFFFFFF)) /* (1<<32) - 1 */

#ifdef PHP_WIN32
#define GENERATE_SEED() (((zend_long) (time(0) * GetCurrentProcessId())) ^ ((zend_long) (1000000.0 * php_combined_lcg())))
#else
#define GENERATE_SEED() (((zend_long) (time(0) * getpid())) ^ ((zend_long) (1000000.0 * php_combined_lcg())))
#endif

PHPAPI void php_mt_srand(uint32_t seed);
PHPAPI uint32_t php_mt_rand(void);
PHPAPI zend_long php_mt_rand_range(zend_long min, zend_long max);

#endif	/* PHP_RAND_H */
