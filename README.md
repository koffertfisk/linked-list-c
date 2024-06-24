# Linked List C
A linked list implementation in C.

## Dependencies
- C compiler (`gcc` for instance)
- `CUnit` (in order to run unit tests)
- `valgrind` (in order to run memory tests)

## Building
To compile and run:
-  `make` to build linked list
-  `make test` to run unit test suite
-  `make linked_list` to build linked list
-  `make memtest` to memory test linked list
-  `make test_coverage` to produce code coverage reports for the linked list test package
-  `make clean` to remove compiled output files and directories

### Code Coverage Reports
To generate and view test coverage reports, call `make test_coverage` then navigate to `linked_list-lcov` and open `index.html` in your web browser of choice. 