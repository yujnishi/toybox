#!/bin/perl

use strict;

sub getenv {
    my $e = shift;

    return $ENV{$e};
}

open(FH,$ARGV[0]);
while ( <FH> ) {
    s%=/(.*?)/=%&getenv($1)%eg;
    print;
}
close(FH);

exit(0);
