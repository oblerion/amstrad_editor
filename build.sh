#!/bin/bash
DSRC="src/"

CC=clang++
CFLAGS=" -g -Wall"
EXEC="main"
DOBJ="obj/"

CC2=i686-w64-mingw32-g++
CFLAGS2=" -g -Wall -lm -static-libstdc++ -static-libgcc"
EXEC2="build/main.exe"
DOBJ2="build/obj/"


TCC="";
TCFLAGS=""
TINC="";
TEXEC="";
TLINK=" ";
TDOBJ="";

function init()
{
	TCC="$1";#compilo
	TINC="$2";#inlcude dir
	TCFLAGS="$3";#flag/ lib dir
	TEXEC="$4";#out exec
	TDOBJ="$5";#obj dir 
}
function comp(){
	local out;
	out="$TDOBJ${1:0:-4}.o"
	rm -f $out;
	echo rm -f $out;
	command $TCC -c $DSRC$1 $TINC -o $out;
	echo $TCC -c $DSRC$1 $TINC -o $out;
	TLINK="$TLINK $out";
}
function link(){
	command $TCC $TLINK $TCFLAGS "-o" $TEXEC; 
	echo $TCC $TLINK $TCFLAGS "-o" $TEXEC; 
}
if [ $# -eq 0 ];then 
# default
	init $CC " " "$CFLAGS" $EXEC $DOBJ;
	comp cfile.cpp;
	comp dirent2.cpp;
	comp main.cpp;
	link;
elif [ -n $1 ] && [ "$1" == "w" ];then
# w win32
	init $CC2 " " "$CFLAGS2" $EXEC2 $DOBJ2;
	comp cfile.cpp;
	comp dirent2.cpp;
	comp main.cpp;
	link;
elif [ -n $1 ] && [ "$1" == "we" ];then
	init $CC2 " " "$CFLAGS2" $EXEC2 $DOBJ2;
	comp cfile.cpp;
	comp dirent2.cpp;
	comp main.cpp;
	link;
	command wine $EXEC2; 

elif [ -n $1 ] && [ "$1" == "c" ];then
# c clear
	rm -f $TDOBJ*.o;
fi
