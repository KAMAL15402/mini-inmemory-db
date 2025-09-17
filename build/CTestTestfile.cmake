# CMake generated Testfile for 
# Source directory: /Users/kamalrawat/Desktop/Projects/inmemory-db
# Build directory: /Users/kamalrawat/Desktop/Projects/inmemory-db/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit_tests "/Users/kamalrawat/Desktop/Projects/inmemory-db/build/tests")
set_tests_properties(unit_tests PROPERTIES  _BACKTRACE_TRIPLES "/Users/kamalrawat/Desktop/Projects/inmemory-db/CMakeLists.txt;30;add_test;/Users/kamalrawat/Desktop/Projects/inmemory-db/CMakeLists.txt;0;")
subdirs("_deps/catch2-build")
