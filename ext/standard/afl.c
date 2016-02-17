#include "php.h"
#include "php_afl.h"

#ifdef __AFL_HAVE_MANUAL_CONTROL
/* {{{ proto void afl_init(void)
Tell AFK this is a good place to fork */
PHP_FUNCTION(afl_init)
{
	__AFL_INIT();
}
/* }}} */
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
