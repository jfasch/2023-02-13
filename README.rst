Development Workflow
====================

.. contents::
   :local:

Checkout and Initialization
---------------------------

.. code-block:: console

   $ cd ~                            # or wherever you like
   $ git clone https://github.com/jfasch/2023-02-13.git
   $ cd ~/2023-02-13
   $ git submodule init
   $ git submodule update

Build
-----

Create build directory for Intel architecture (``x86_64``)

.. code-block:: console

   $ mkdir ~/2023-02-13-x86_64      # or wherever you like
   $ cd ~/2023-02-13-x86_64
   $ cmake ~/2023-02-13
   $ make

Test

.. code-block:: console

   $ ./livehacking/hello 
   Hello World

.. code-block:: console

   $ ./exercises/exercises-suite 
   Running main() from /home/jfasch/tmp/2023-02-13/googletest/googletest/src/gtest_main.cc
   [==========] Running 1 test from 1 test suite.
   [----------] Global test environment set-up.
   [----------] 1 test from exercises_suite
   [ RUN      ] exercises_suite.fail
   /home/jfasch/tmp/2023-02-13/exercises/fail.cpp:5: Failure
   Failed
   [  FAILED  ] exercises_suite.fail (0 ms)
   [----------] 1 test from exercises_suite (0 ms total)
   
   [----------] Global test environment tear-down
   [==========] 1 test from 1 test suite ran. (0 ms total)
   [  PASSED  ] 0 tests.
   [  FAILED  ] 1 test, listed below:
   [  FAILED  ] exercises_suite.fail
   
    1 FAILED TEST
