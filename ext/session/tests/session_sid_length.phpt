--TEST--
Test session.sid_length ini setting
--SKIPIF--
<?php include('skipif.inc'); ?>
--FILE--
<?php

$testLengths = [31, 32, 128, 129];
$testBits = [4, 5, 6];

ob_start();

echo "*** Testing session.sid_length ***\n";

foreach ($testBits as $bits) {
    ini_set('session.hash_bits_per_character', $bits);

    foreach ($testLengths as $length) {
        print "length=$length, bits=$bits\n";
        ini_set('session.sid_length', $length);

        var_dump(session_start());
        var_dump(!empty(session_id()), session_id());
        var_dump(session_destroy());
    }
}

echo "Done";
ob_end_flush();
?>
--EXPECTF--
*** Testing session.sid_length ***
length=31, bits=4

Warning: session_start(): The ini setting session.sid_length is out of range (should be between 32 and 128) - using 32 for now in %ssession_sid_length.php on line %d
bool(true)
bool(true)
string(32) "%s"
bool(true)
length=32, bits=4
bool(true)
bool(true)
string(32) "%s"
bool(true)
length=128, bits=4
bool(true)
bool(true)
string(128) "%s"
bool(true)
length=129, bits=4

Warning: session_start(): The ini setting session.sid_length is out of range (should be between 32 and 128) - using 32 for now in %ssession_sid_length.php on line %d
bool(true)
bool(true)
string(32) "%s"
bool(true)
length=31, bits=5

Warning: session_start(): The ini setting session.sid_length is out of range (should be between 32 and 128) - using 32 for now in %ssession_sid_length.php on line %d
bool(true)
bool(true)
string(32) "%s"
bool(true)
length=32, bits=5
bool(true)
bool(true)
string(32) "%s"
bool(true)
length=128, bits=5
bool(true)
bool(true)
string(128) "%s"
bool(true)
length=129, bits=5

Warning: session_start(): The ini setting session.sid_length is out of range (should be between 32 and 128) - using 32 for now in %ssession_sid_length.php on line %d
bool(true)
bool(true)
string(32) "%s"
bool(true)
length=31, bits=6

Warning: session_start(): The ini setting session.sid_length is out of range (should be between 32 and 128) - using 32 for now in %ssession_sid_length.php on line %d
bool(true)
bool(true)
string(32) "%s"
bool(true)
length=32, bits=6
bool(true)
bool(true)
string(32) "%s"
bool(true)
length=128, bits=6
bool(true)
bool(true)
string(128) "%s"
bool(true)
length=129, bits=6

Warning: session_start(): The ini setting session.sid_length is out of range (should be between 32 and 128) - using 32 for now in %ssession_sid_length.php on line %d
bool(true)
bool(true)
string(32) "%s"
bool(true)
Done
