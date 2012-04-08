#!/bin/sh
cd `dirname "$0"`
rm -f html/form_*.png html/formula.repository
doxygen Doxyfile
