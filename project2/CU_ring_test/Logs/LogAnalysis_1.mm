bijan@bijan:~/hello-world/project2/CU_ring_test$ ./unittest 


     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/

Please enter the size of the ring buffer ( in powers of 2 ): 4			/* Initial values at startup*/
You entered: 4

Please enter a string for writing to the buffer:  abcde
You entered: abcde

And the number of characters for removal: 2
You entered: 2


Suite: Basic_Test_Suite1

  Test:  

===> init() function: ...passed
  Test:  

===> insert() function: ...

Previous Buffer Status:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 0    	Head: 0    	Entries: 0	

Buffer Contents Linear Queue (Tail to Head): ...
Buffer Contents Circular Queue: ..."----"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

!!!~~> Expected buffer overflow at location: ... 0

Tail: 0    	Head: 0    	Entries: 4	

Buffer Contents Linear Queue (Tail to Head): ...abcd
Buffer Contents Circular Queue: ..."abcd"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FAILED
    1. ring_test.c:164  - 0 == check_insert
  Test:  

===> read() function: ...
Tail: 2    	Head: 0    	Entries: 2	Data Out: ab 

Buffer Contents Linear Queue (Tail to Head): ...cd
Buffer Contents Circular Queue: ..."--cd"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> entries() function: ... 
Tail: 2    	Head: 0    	Entries: 2...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      3      1        0
             asserts     11     11     10      1      n/a

Elapsed time =    0.001 seconds
Continue? (Y)es, (N)o y
Do you wish to modify the buffer size? (Y)es, (N)o: y


     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/

Please enter the size of the ring buffer ( in powers of 2 ): 8
You entered: 8

Please enter a string for writing to the buffer:  ABCDEFGH
You entered: ABCDEFGH

And the number of characters for removal: 2
You entered: 2


Suite: Basic_Test_Suite1

  Test:  

===> init() function: ...passed
  Test:  

===> insert() function: ...

Previous Buffer Status:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 2    	Head: 0    	Entries: 2	

Buffer Contents Linear Queue (Tail to Head): ...cd
Buffer Contents Circular Queue: ..."--cd"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

!!!~~> Expected buffer overflow at location: ... 6

Tail: 6    	Head: 6    	Entries: 8	

Buffer Contents Linear Queue (Tail to Head): ...cdABCDEF
Buffer Contents Circular Queue: ..."ABCDEFcd"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FAILED
    1. ring_test.c:164  - 0 == check_insert
  Test:  

===> read() function: ...
Tail: 0    	Head: 6    	Entries: 6	Data Out: cd 

Buffer Contents Linear Queue (Tail to Head): ...ABCDEF
Buffer Contents Circular Queue: ..."ABCDEF--"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> entries() function: ... 
Tail: 0    	Head: 6    	Entries: 6...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      3      1        0
             asserts     13     13     12      1      n/a

Elapsed time =    0.000 seconds
Continue? (Y)es, (N)o y
Do you wish to modify the buffer size? (Y)es, (N)o: n


     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/

Please enter a string for writing to the buffer:  12345
You entered: 12345

And the number of characters for removal: 3
You entered: 3


Suite: Basic_Test_Suite1

  Test:  

===> init() function: ...passed
  Test:  

===> insert() function: ...

Previous Buffer Status:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 0    	Head: 6    	Entries: 6	

Buffer Contents Linear Queue (Tail to Head): ...ABCDEF
Buffer Contents Circular Queue: ..."ABCDEF--"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

!!!~~> Expected buffer overflow at location: ... 0

Tail: 0    	Head: 0    	Entries: 8	

Buffer Contents Linear Queue (Tail to Head): ...ABCDEF12
Buffer Contents Circular Queue: ..."ABCDEF12"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FAILED
    1. ring_test.c:164  - 0 == check_insert
  Test:  

===> read() function: ...
Tail: 3    	Head: 0    	Entries: 5	Data Out: ABC 

Buffer Contents Linear Queue (Tail to Head): ...DEF12
Buffer Contents Circular Queue: ..."---DEF12"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> entries() function: ... 
Tail: 3    	Head: 0    	Entries: 5...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      3      1        0
             asserts     10     10      9      1      n/a

Elapsed time =    0.001 seconds
Continue? (Y)es, (N)o y
Do you wish to modify the buffer size? (Y)es, (N)o: n


     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/

Please enter a string for writing to the buffer:  ecen pes
You entered: ecen pes

And the number of characters for removal: 3
You entered: 3


Suite: Basic_Test_Suite1

  Test:  

===> init() function: ...passed
  Test:  

===> insert() function: ...

Previous Buffer Status:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 3    	Head: 0    	Entries: 5	

Buffer Contents Linear Queue (Tail to Head): ...DEF12
Buffer Contents Circular Queue: ..."---DEF12"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

!!!~~> Expected buffer overflow at location: ... 3

Tail: 3    	Head: 3    	Entries: 8	

Buffer Contents Linear Queue (Tail to Head): ...DEF12ece
Buffer Contents Circular Queue: ..."eceDEF12"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FAILED
    1. ring_test.c:164  - 0 == check_insert
  Test:  

===> read() function: ...
Tail: 6    	Head: 3    	Entries: 5	Data Out: DEF 

Buffer Contents Linear Queue (Tail to Head): ...12ece
Buffer Contents Circular Queue: ..."ece---12"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> entries() function: ... 
Tail: 6    	Head: 3    	Entries: 5...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      3      1        0
             asserts     11     11     10      1      n/a

Elapsed time =    0.001 seconds
Continue? (Y)es, (N)o y
Do you wish to modify the buffer size? (Y)es, (N)o: y


     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/

Please enter the size of the ring buffer ( in powers of 2 ): 16
You entered: 16

Please enter a string for writing to the buffer:  qwertyuiop
You entered: qwertyuiop

And the number of characters for removal: 2
You entered: 2


Suite: Basic_Test_Suite1

  Test:  

===> init() function: ...passed
  Test:  

===> insert() function: ...

Previous Buffer Status:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 6    	Head: 3    	Entries: 5	

Buffer Contents Linear Queue (Tail to Head): ...12ece
Buffer Contents Circular Queue: ..."ece---12"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 14   	Head: 13   	Entries: 15	

Buffer Contents Linear Queue (Tail to Head): ...12eceqwertyuiop
Buffer Contents Circular Queue: ..."eceqwertyuiop-12"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> read() function: ...
Tail: 0    	Head: 13   	Entries: 13	Data Out: 12 

Buffer Contents Linear Queue (Tail to Head): ...eceqwertyuiop
Buffer Contents Circular Queue: ..."eceqwertyuiop---"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> entries() function: ... 
Tail: 0    	Head: 13   	Entries: 13...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      4      0        0
             asserts     16     16     16      0      n/a

Elapsed time =    0.001 seconds
Continue? (Y)es, (N)o y
Do you wish to modify the buffer size? (Y)es, (N)o: y


     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/

Please enter the size of the ring buffer ( in powers of 2 ): 16					// change length with the same ( just for verification)
You entered: 16

Please enter a string for writing to the buffer:  123456
You entered: 123456

And the number of characters for removal: 3
You entered: 3


Suite: Basic_Test_Suite1

  Test:  

===> init() function: ...passed
  Test:  e

===> insert() function: ...

Previous Buffer Status:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 0    	Head: 13   	Entries: 13	

Buffer Contents Linear Queue (Tail to Head): ...eceqwertyuiop
Buffer Contents Circular Queue: ..."eceqwertyuiop---"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

!!!~~> Expected buffer overflow at location: ... 0

Tail: 0    	Head: 0    	Entries: 16	

Buffer Contents Linear Queue (Tail to Head): ...eceqwertyuiop123
Buffer Contents Circular Queue: ..."eceqwertyuiop123"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FAILED
    1. ring_test.c:164  - 0 == check_insert
  Test:  

===> read() function: ...
Tail: 3    	Head: 0    	Entries: 13	Data Out: ece 

Buffer Contents Linear Queue (Tail to Head): ...qwertyuiop123
Buffer Contents Circular Queue: ..."---qwertyuiop123"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> entries() function: ... 
Tail: 3    	Head: 0    	Entries: 13...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      3      1        0
             asserts     11     11     10      1      n/a

Elapsed time =    0.001 seconds
Continue? (Y)es, (N)o y
Do you wish to modify the buffer size? (Y)es, (N)o: y


     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/

Please enter the size of the ring buffer ( in powers of 2 ): 32
You entered: 32

Please enter a string for writing to the buffer:  ABCDEFGHIJKLMNOP
You entered: ABCDEFGHIJKLMNOP

And the number of characters for removal: 3
You entered: 3


Suite: Basic_Test_Suite1

  Test:  

===> init() function: ...passed
  Test:  

===> insert() function: ...

Previous Buffer Status:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 3    	Head: 0    	Entries: 13	

Buffer Contents Linear Queue (Tail to Head): ...qwertyuiop123
Buffer Contents Circular Queue: ..."---qwertyuiop123"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Tail: 19   	Head: 16   	Entries: 29	

Buffer Contents Linear Queue (Tail to Head): ...qwertyuiop123ABCDEFGHIJKLMNOP
Buffer Contents Circular Queue: ..."ABCDEFGHIJKLMNOP---qwertyuiop123"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> read() function: ...
Tail: 22   	Head: 16   	Entries: 26	Data Out: qwe 

Buffer Contents Linear Queue (Tail to Head): ...rtyuiop123ABCDEFGHIJKLMNOP
Buffer Contents Circular Queue: ..."ABCDEFGHIJKLMNOP------rtyuiop123"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed
  Test:  

===> entries() function: ... 
Tail: 22   	Head: 16   	Entries: 26...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      4      4      4      0        0
             asserts     23     23     23      0      n/a

Elapsed time =    0.000 seconds
Continue? (Y)es, (N)o 
