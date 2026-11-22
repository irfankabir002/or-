#!/bin/sh
# Run by `make check` from the build directory, where ./bonnie lives.
set -eu

out=$(./bonnie 'this file provides a **HUGE smile for the interphase**')

echo "$out" | grep -q '^tokens: 9$'          || { echo "expected 9 tokens"; exit 1; }
echo "$out" | grep -q '^conjunctions: 1$'    || { echo "expected 1 conjunction (for)"; exit 1; }
echo "$out" | grep -q 'interphase'           || { echo "missing interphase"; exit 1; }

out=$(echo "this and that or the other" | ./bonnie)
echo "$out" | grep -q '^conjunctions: 2$'    || { echo "expected 2 conjunctions"; exit 1; }

echo "ok"
