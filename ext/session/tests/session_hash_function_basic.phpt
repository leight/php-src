--TEST--
Test session.hash_function ini setting : basic functionality
--SKIPIF--
<?php include('skipif.inc'); ?>
--INI--
session.sid_length=32
session.sid_bits_per_character=4
--FILE--
<?php

ob_start();

echo "*** Testing session.hash_function : basic functionality ***\n";

var_dump(ini_set('session.hash_function', 'md5'));
var_dump(ini_set('session.hash_bits_per_character', '5'));
var_dump(session_start());
var_dump(!empty(session_id()), session_id());
var_dump(session_destroy());

var_dump(ini_set('session.hash_function', 'sha1'));
var_dump(ini_set('session.hash_bits_per_character', '6'));
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

Deprecated: ini_set(): session.hash_bits_per_character is deprecated. Please use session.sid_bits_per_character instead in %ssession_hash_function_basic.php on line %d
bool(false)
bool(true)
bool(true)
string(32) "%s"
bool(true)

Deprecated: ini_set(): session.hash_function is deprecated. Please use session.sid_length to control session id length in %ssession_hash_function_basic.php on line %d
bool(false)

Deprecated: ini_set(): session.hash_bits_per_character is deprecated. Please use session.sid_bits_per_character instead in %ssession_hash_function_basic.php on line %d
bool(false)
bool(true)
bool(true)
string(32) "%s"
bool(true)

Deprecated: ini_set(): session.hash_function is deprecated. Please use session.sid_length to control session id length in %ssession_hash_function_basic.php on line %d
bool(false)
bool(true)
bool(true)
string(32) "%s"
bool(true)
Done
