entutil
=======
Entropy measurement utility for Linux

Overview
========
This utility measures the Shannon entropy of its input file argument in 1-bit
(binary), 4-bit (nybble), and 8-bit (byte) units.

For more information on calculating Shannon entropy, see:
[Entropy (information theory)](http://en.wikipedia.org/wiki/Entropy_%28information_theory%29)

Build and Test
==============

Building
--------

To build, check out files on a Linux machine and type:

`make`

Testing
-------

Usage:

`entutil filespec`

Examples:

Measuring itself:
```
$ ./entutil ./entutil
0.678625 2.254717 3.749226
```

Measuring the dictionary:
```
$ ./entutil /usr/share/dict/words
1.000000 3.357988 4.418825
```

Measuring AES-encrypted data
```
$ openssl enc -in /var/log/syslog -out crypt.bin -e -aes-256-cbc -K 0123456789abcdef -iv fedcba9876543210 -md sha1 -S 00112233aabbccdd
$ ./entutil ./crypt.bin
0.999998 3.999744 7.989879
```

Measuring pseudo-random data
```
$ dd if=/dev/urandom of=urandom bs=4096 count=64
64+0 records in
64+0 records out
262144 bytes (262 kB) copied, 0.0650555 s, 4.0 MB/s
$ ./entutil ./urandom
1.000000 3.999991 7.999335
```

License
=======
Licensed under the WTFPL.  For details, see:
[WTF Public License](http://www.wtfpl.net/)
