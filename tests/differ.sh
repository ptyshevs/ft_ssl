#!/bin/bash

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

if ! [ `diff $2 $3 | wc -l` -eq "0" ]
then
	if [ "$4" == "--more" ]
	then
		echo -e $RED"Failed $1:"$NC >> fails
		echo "test case [plaintext]: [`cat $1`]" >> fails
		echo -e "output [${LCYAN}openssl${NC}|ft_ssl]: [${LCYAN}`cat $2`${NC}|`cat $3`]" >> fails
		echo "" >> fails
	fi
	echo -n -e $RED"X"$NC
else
	echo -n -e $GREEN"✓"$NC
fi