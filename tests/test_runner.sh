#!/bin/bash

# COLORS

BLACK='\033[0;30m'
RED='\033[0;31m'
GREEN='\033[0;32m'
BROWN='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
LGRAY='\033[0;37m'
DGRAY='\033[1;30m'
LRED='\033[1;31m'
LGREEN='\033[1;32m'
YELLOW='\033[1;33m'
LBLUE='\033[1;34m'
PINK='\033[1;35m'
LCYAN='\033[1;36m'
WHITE='\033[1;37m'
NC='\033[0m'

if [ "$#" -eq 0 ]
then
	echo "USAGE: sh test_runner.sh <ft_ssl_binary> [--more] [--clean]"
	echo "Fail format: [openssl|ft_ssl]"
	exit
fi

if ! [ -e "temp" ]
then
	mkdir ./temp
fi

for f in tests/test_*.sh
do
	echo -e $BLUE"Running $f: "$NC
	./$f $@
done

if [ "$3" == "--clean" ]
then
	rm -rf temp
	rm -f fails
fi
