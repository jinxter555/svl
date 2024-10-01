#!/bin/bash
make $1
(cd ast; make $1) &
(cd ast; cd test_cc; make $1) &

