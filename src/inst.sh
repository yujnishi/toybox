#!/bin/sh

eng=$1
own=
grp=
mode=
src=
dst=
shift

while [ $# -gt 0 ]
do
    own=$grp
    grp=$mode
    mode=$src
    src=$dst
    dst=$1
    shift
done

#echo "$# eng=$eng mode=$mode own=$own grp=$grp src=$src dst=$dst" >&2

if [ ! -e $src ]
then
    echo "No such file or directory: $src" >&2
    exit 1
fi

case ${eng:-file} in
file|cp)  eng=cat  ;;
env|set)  eng=rpe  ;;
exe|eval) eng=run  ;;
esac

ischown=true
test "$own$grp" = "--" -o "$own$grp" = "" -o "$own$grp" = "-" && ischown=false
test `whoami` != root && ischown=false

test "$own" = "-" && own=
own=${own:-`stat -c %U $src`}

test "$grp" = "-" && grp=
grp=${grp:-`stat -c %G $src`}

test "$mode" = "-" && mode=
mode=${mode:-`stat -c %a $src`}

$eng $src > $dst
chmod $mode $dst
test $ischown = true && chown $own:$grp $dst


