# bin_PROGRAMS: build "bonnie" and install it into $(bindir) on `make install`.
bin_PROGRAMS = bonnie
bonnie_SOURCES = src/main.cpp
bonnie_CXXFLAGS = -std=c++17 -Wall -Wextra

# `make check` runs these; a non-zero exit status means failure.
TESTS = tests/basic.sh
EXTRA_DIST = tests/basic.sh README.md
