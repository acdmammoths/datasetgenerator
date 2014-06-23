Dataset Generator
=================

A porting to C++11 and modern g++ of the IBM transactional dataset generator.

Copyright (c) 2014 Matteo Riondato <matteo@cs.brown.edu>

History
-------
Once upon a time (possibly on July 22 1997), the IBM Almaden group published a
synthetic transactional dataset generator. The workings of the generator were
described in 'R. Agrawal and R. Srikant. Fast algorithms for mining association
rules in large databases. In Proc. 20th Int. Conf. Very Large Data Bases, VLDB
’94, pages 487–499, 1994'. The original version could be downloaded from
http://www.almaden.ibm.com/cs/quest/syndata.html (that page no longer exists).

After a while (around 2002-2003), the IBM version could not be compiled with
"modern" g++ compilers anymore. Paolo Palmerini (<paolo.palmerini@cnuce.cnr.it>)
published a g++-compilable modified version of the generator on his
[website](http://miles.cnuce.cnr.it/~palmeri/datam/DCI/datasets.php). Paolo's
modifications can be found in the source code by looking for comments
highlighted by "// g++". 

As of June 2014 Paolo's version does not compile on current g++ (e.g., g++-4.9).
[Matteo Riondato](http://cs.brown.edu/~matteo) (<matteo@cs.brown.edu>) took up
the task to port the code to C++11 and make it compile with the current g++.

License
-------
The code published on Paolo Palmerini's website comes without any licensing
information and Matteo Riondato is not aware of the licensing of the original
IBM code. If you have information about this, please let Matteo know by writing
an email to <matteo@cs.brown.edu>. Assuming the code was in the public
domain, Matteo is licensing this code under the Apache License, Version 2.0. See
the [LICENSE](./LICENSE) file and the [NOTICE](./NOTICE) file. 

Install
-------
Just run "make" and the code will be compiled. It uses whatever "g++" is on your
system. You can specify your favourite version by modifying the Makefile. 

Running
-------
TODO: add information abount running
