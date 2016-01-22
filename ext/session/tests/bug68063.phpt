--TEST--
Bug #68063 (Empty session IDs do still start sessions)
--SKIPIF--
<?php include('skipif.inc'); ?>
--INI--
session.sid_length=32
session.use_strict_mode=0
--FILE--
<?php
// Empty session ID may happen by browser bugs

// Could also be set with a cookie like "PHPSESSID=; path=/"
session_id('');

// Start the session with empty string should result in new session ID
var_dump(session_start());

// Returns newly created session ID
var_dump(session_id());
?>
--EXPECTF--
bool(true)
string(32) "%s"
