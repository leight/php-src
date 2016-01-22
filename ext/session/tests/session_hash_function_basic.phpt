--TEST--
Test session.hash_function ini setting : basic functionality
--SKIPIF--
<?php include('skipif.inc'); ?>
--INI--
session.sid_length=32
session.hash_bits_per_character=4
--FILE--
<?php

ob_start();

echo "*** Testing session.hash_function : basic functionality ***\n";

var_dump(ini_set('session.hash_function', 'md5'));
var_dump(session_start());
var_dump(!empty(session_id()), session_id());
var_dump(session_destroy());

var_dump(ini_set('session.hash_function', 'sha1'));
var_dump(session_start());
var_dump(!empty(session_id()), session_id());
var_dump(session_destroy());

var_dump(ini_set('session.hash_function', 'none')); // Should fail
var_dump(session_start());
var_dump(!empty(session_id()), session_id());
var_dump(session_destroy());


echo "Done";
ob_end_flush();
?>
--EXPECTF--
*** Testing session.hash_function : basic functionality ***
string(1) "0"
bool(true)
bool(true)
string(32) "%s"
bool(true)

Deprecated: ini_set(): session.hash_function is deprecated. Please use session.sid_length to control session id length in %ssession_hash_function_basic.php on line 12
bool(false)
bool(true)
bool(true)
string(32) "%s"
bool(true)

Deprecated: ini_set(): session.hash_function is deprecated. Please use session.sid_length to control session id length in %ssession_hash_function_basic.php on line 17
bool(false)
bool(true)
bool(true)
string(32) "%s"
bool(true)
Done
