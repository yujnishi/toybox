#!/bin/sh

set -vx

f=$1
test -e $f || exit 1

test -x $f && exec $f


hline="`head -1 $f`"
cmd=${hline###!}
test "$hline" = "$cmd" || exec $cmd $f

exec sh $f

exit 1

