#!/usr/bin/env perl

my @lst= ( '0' .. '9', 'A' .. 'Z', 'a' .. 'z' ) ;
my $xtra= '!#$%&()*+-;<=>?@^_`{|}~' ;

my $out ;

push @lst, $xtra =~ /(.)/g ;
my $str= join('', @lst) ;

$out= "static const char ascii85[]= \"$str\" ;\n" ;

my @xcode= ( ( 0) x128) ;

        foreach ( map { ord($_) } @lst ) { $xcode[$_]= $i ++ }

$out .= "static const unsigned char  dascii85[128]= { ". join(', ', @xcode ). " } ; \n" ;

my ($dest)= @ARGV ;
open my $fh, '>', $dest or die "error writing $dest" ;
print $fh $out

