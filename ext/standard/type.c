/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2017 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Rasmus Lerdorf <rasmus@php.net>                              |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "php.h"
#include "php_incomplete_class.h"

/* {{{ proto string gettype(mixed var)
   Returns the type of the variable */
PHP_FUNCTION(gettype)
{
	zval *arg;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL_DEREF(arg)
	ZEND_PARSE_PARAMETERS_END();

	switch (Z_TYPE_P(arg)) {
		case IS_NULL:
			RETVAL_STRING("NULL");
			break;

		case IS_FALSE:
		case IS_TRUE:
			RETVAL_STRING("boolean");
			break;

		case IS_LONG:
			RETVAL_STRING("integer");
			break;

		case IS_DOUBLE:
			RETVAL_STRING("double");
			break;

		case IS_STRING:
			RETVAL_STRING("string");
			break;

		case IS_ARRAY:
			RETVAL_STRING("array");
			break;

		case IS_OBJECT:
			RETVAL_STRING("object");
			break;

		case IS_RESOURCE:
			{
				const char *type_name = zend_rsrc_list_get_rsrc_type(Z_RES_P(arg));

				if (type_name) {
					RETVAL_STRING("resource");
				} else {
					RETVAL_STRING("resource (closed)");
				}
				break;
			}

		default:
			RETVAL_STRING("unknown type");
	}
}
/* }}} */

/* {{{ proto bool settype(mixed var, string type)
   Set the type of the variable */
PHP_FUNCTION(settype)
{
	zval *var;
	char *type;
	size_t type_len = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL_DEREF(var)
		Z_PARAM_STRING(type, type_len)
	ZEND_PARSE_PARAMETERS_END();

	if (!strcasecmp(type, "integer")) {
		convert_to_long(var);
	} else if (!strcasecmp(type, "int")) {
		convert_to_long(var);
	} else if (!strcasecmp(type, "float")) {
		convert_to_double(var);
	} else if (!strcasecmp(type, "double")) { /* deprecated */
		convert_to_double(var);
	} else if (!strcasecmp(type, "string")) {
		convert_to_string(var);
	} else if (!strcasecmp(type, "array")) {
		convert_to_array(var);
	} else if (!strcasecmp(type, "object")) {
		convert_to_object(var);
	} else if (!strcasecmp(type, "bool")) {
		convert_to_boolean(var);
	} else if (!strcasecmp(type, "boolean")) {
		convert_to_boolean(var);
	} else if (!strcasecmp(type, "null")) {
		convert_to_null(var);
	} else if (!strcasecmp(type, "resource")) {
		php_error_docref(NULL, E_WARNING, "Cannot convert to resource type");
		RETURN_FALSE;
	} else {
		php_error_docref(NULL, E_WARNING, "Invalid type");
		RETURN_FALSE;
	}
	RETVAL_TRUE;
}
/* }}} */

/* {{{ proto int intval(mixed var [, int base])
   Get the integer value of a variable using the optional base for the conversion */
PHP_FUNCTION(intval)
{
	zval *num;
	zend_long base = 10;

	size_t strlen;
	char *strval;
	char *tmpval;
	int offset = 0;

	if (ZEND_NUM_ARGS() != 1 && ZEND_NUM_ARGS() != 2) {
		WRONG_PARAM_COUNT;
	}
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(num)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(base)
	ZEND_PARSE_PARAMETERS_END();

	if (Z_TYPE_P(num) != IS_STRING || base == 10) {
		RETVAL_LONG(zval_get_long(num));
		return;
	}
	
	strval = Z_STRVAL_P(num);
	strlen = Z_STRLEN_P(num);

	while (isspace(*strval) && strlen) {
		strval++;
		strlen--;
	}

	/* Length of 3+ covers "0b#" and "-0b" (which results in 0) */
	if (strlen > 2) {
		if (strval[0] == '-' || strval[0] == '+') {
			offset = 1;
		}

		if (strval[offset] == '0' && (strval[offset + 1] == 'b' || strval[offset + 1] == 'B')) {
			tmpval = emalloc(strlen - 2); /* Minus "0b" */

			/* Place the unary symbol at pos 0 if there was one */
			if (offset) {
				tmpval[0] = strval[0];
			}

			/* Copy the data from after "0b" to the end of the buffer */
			memcpy(tmpval + offset, strval + offset + 2, strlen - 2);
			RETVAL_LONG(ZEND_STRTOL(tmpval, NULL, 2));
			efree(tmpval);
			return;
		}
	}

	RETVAL_LONG(ZEND_STRTOL(strval, NULL, base));
}
/* }}} */

/* {{{ proto float floatval(mixed var)
   Get the float value of a variable */
PHP_FUNCTION(floatval)
{
	zval *num;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL_DEREF(num)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_DOUBLE(zval_get_double(num));
}
/* }}} */

/* {{{ proto bool boolval(mixed var)
   Get the boolean value of a variable */
PHP_FUNCTION(boolval)
{
	zval *val;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL_DEREF(val)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(zend_is_true(val));
}
/* }}} */

/* {{{ proto string strval(mixed var)
   Get the string value of a variable */
PHP_FUNCTION(strval)
{
	zval *num;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(num)
	ZEND_PARSE_PARAMETERS_END();

	RETVAL_STR(zval_get_string(num));
}
/* }}} */

static inline void php_is_type(INTERNAL_FUNCTION_PARAMETERS, int type)
{
	zval *arg;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL_DEREF(arg)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

	if (Z_TYPE_P(arg) == type) {
		if (type == IS_RESOURCE) {
			const char *type_name = zend_rsrc_list_get_rsrc_type(Z_RES_P(arg));
			if (!type_name) {
				RETURN_FALSE;
			}
		}
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}


/* {{{ proto bool is_null(mixed var)
   Returns true if variable is null
   Warning: This function is special-cased by zend_compile.c and so is usually bypassed */
PHP_FUNCTION(is_null)
{
	php_is_type(INTERNAL_FUNCTION_PARAM_PASSTHRU, IS_NULL);
}
/* }}} */

/* {{{ proto bool is_resource(mixed var)
   Returns true if variable is a resource
   Warning: This function is special-cased by zend_compile.c and so is usually bypassed */
PHP_FUNCTION(is_resource)
{
	php_is_type(INTERNAL_FUNCTION_PARAM_PASSTHRU, IS_RESOURCE);
}
/* }}} */

/* {{{ proto bool is_bool(mixed var)
   Returns true if variable is a boolean
   Warning: This function is special-cased by zend_compile.c and so is usually bypassed */
PHP_FUNCTION(is_bool)
{
	zval *arg;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL_DEREF(arg)
	ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

	RETURN_BOOL(Z_TYPE_P(arg) == IS_FALSE || Z_TYPE_P(arg) == IS_TRUE);
}
/* }}} */

/* {{{ proto bool is_int(mixed var)
   Returns true if variable is an integer
   Warning: This function is special-cased by zend_compile.c and so is usually bypassed */
PHP_FUNCTION(is_int)
{
	php_is_type(INTERNAL_FUNCTION_PARAM_PASSTHRU, IS_LONG);
}
/* }}} */

/* {{{ proto bool is_float(mixed var)
   Returns true if variable is float point
   Warning: This function is special-cased by zend_compile.c and so is usually bypassed */
PHP_FUNCTION(is_float)
{
	php_is_type(INTERNAL_FUNCTION_PARAM_PASSTHRU, IS_DOUBLE);
}
/* }}} */

/* {{{ proto bool is_string(mixed var)
   Returns true if variable is a string
   Warning: This function is special-cased by zend_compile.c and so is usually bypassed */
PHP_FUNCTION(is_string)
{
	php_is_type(INTERNAL_FUNCTION_PARAM_PASSTHRU, IS_STRING);
}
/* }}} */

/* {{{ proto bool is_array(mixed var)
   Returns true if variable is an array
   Warning: This function is special-cased by zend_compile.c and so is usually bypassed */
PHP_FUNCTION(is_array)
{
	php_is_type(INTERNAL_FUNCTION_PARAM_PASSTHRU, IS_ARRAY);
}
/* }}} */

/* {{{ proto bool is_object(mixed var)
   Returns true if variable is an object
   Warning: This function is special-cased by zend_compile.c and so is usually bypassed */
PHP_FUNCTION(is_object)
{
	php_is_type(INTERNAL_FUNCTION_PARAM_PASSTHRU, IS_OBJECT);
}
/* }}} */

/* {{{ proto bool is_numeric(mixed value)
   Returns true if value is a number or a numeric string */
PHP_FUNCTION(is_numeric)
{
	zval *arg;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(arg)
	ZEND_PARSE_PARAMETERS_END();

	switch (Z_TYPE_P(arg)) {
		case IS_LONG:
		case IS_DOUBLE:
			RETURN_TRUE;
			break;

		case IS_STRING:
			if (is_numeric_string(Z_STRVAL_P(arg), Z_STRLEN_P(arg), NULL, NULL, 0)) {
				RETURN_TRUE;
			} else {
				RETURN_FALSE;
			}
			break;

		default:
			RETURN_FALSE;
			break;
	}
}
/* }}} */

/* {{{ proto bool is_scalar(mixed value)
   Returns true if value is a scalar */
PHP_FUNCTION(is_scalar)
{
	zval *arg;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(arg)
	ZEND_PARSE_PARAMETERS_END();

	switch (Z_TYPE_P(arg)) {
		case IS_FALSE:
		case IS_TRUE:
		case IS_DOUBLE:
		case IS_LONG:
		case IS_STRING:
			RETURN_TRUE;
			break;

		default:
			RETURN_FALSE;
			break;
	}
}
/* }}} */

/* {{{ proto bool is_callable(mixed var [, bool syntax_only [, string callable_name]])
   Returns true if var is callable. */
PHP_FUNCTION(is_callable)
{
	zval *var, *callable_name = NULL;
	zend_string *name;
	char *error;
	zend_bool retval;
	zend_bool syntax_only = 0;
	int check_flags = 0;

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_ZVAL_DEREF(var)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(syntax_only)
		Z_PARAM_ZVAL_DEREF_EX(callable_name, 0, 1)
	ZEND_PARSE_PARAMETERS_END();

	if (syntax_only) {
		check_flags |= IS_CALLABLE_CHECK_SYNTAX_ONLY;
	}
	if (ZEND_NUM_ARGS() > 2) {
		retval = zend_is_callable_ex(var, NULL, check_flags, &name, NULL, &error);
		zval_dtor(callable_name);
		//??? is it necessary to be consistent with old PHP ("\0" support)
		if (UNEXPECTED(ZSTR_LEN(name) != strlen(ZSTR_VAL(name)))) {
			ZVAL_STRINGL(callable_name, ZSTR_VAL(name), strlen(ZSTR_VAL(name)));
			zend_string_release(name);
		} else {
			ZVAL_STR(callable_name, name);
		}
	} else {
		retval = zend_is_callable_ex(var, NULL, check_flags, NULL, NULL, &error);
	}
	if (error) {
		/* ignore errors */
		efree(error);
	}

	RETURN_BOOL(retval);
}
/* }}} */

/* {{{ proto bool is_iterable(mixed var)
   Returns true if var is iterable (array or instance of Traversable). */
PHP_FUNCTION(is_iterable)
{
	zval *var;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL_DEREF(var)
	ZEND_PARSE_PARAMETERS_END();	
	
	RETURN_BOOL(zend_is_iterable(var));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
