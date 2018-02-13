#!/bin/bash

BLACK='\033[0;30m'
RED='\033[0;31m'
GREEN='\033[0;32m'
BROWN='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
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

# STDIN piping

echo -n -e $GREEN"[stdin:\t\t"$NC
for f in tests/base64/stdin*
do
	openssl_location="temp/"$(basename $f)"_openssl"
	ft_ssl_location="temp/"$(basename $f)"_ft_ssl"

	touch $openssl_location
	touch $ft_ssl_location
	echo `cat $f` | openssl base64 > $openssl_location
	echo `cat $f` | $1 base64 > $ft_ssl_location
	./differ.sh $f $openssl_location $ft_ssl_location $2
done
echo -e "]"

# in_out

echo -n -e $GREEN"[in out:\t"$NC
for f in tests/base64/stdin*
do
	if [ $(basename "$f") != "stdin5_empty" ]
	then
		out_openssl_location="temp/"$(basename $f)"_openssl_in_out"
		out_ft_ssl_location="temp/"$(basename $f)"_ft_ssl_in_out"

		echo "test" | openssl base64 -in $f -out $out_openssl_location
		echo "test" | $1 base64 -i $f -o $out_ft_ssl_location
		if [ "$2" == "--more" ]
		then
			./differ.sh $f $out_openssl_location $out_ft_ssl_location $2
		elif [ "$3" == "--more" ]
		then
			./differ.sh $f $out_openssl_location $out_ft_ssl_location $3
		else
			./differ.sh $f $out_openssl_location $out_ft_ssl_location
		fi
	fi
done
echo -e "\t]"

# Decrypt

echo -n -e $GREEN"[decrypt:\t"$NC
for f in tests/base64/decr*
do
	openssl_location="temp/"$(basename $f)"_openssl_decr"
	ft_ssl_location="temp/"$(basename $f)"_ft_ssl_decr"

	touch $openssl_location
	openssl base64 -d -in $f -out $openssl_location
	$1 base64 -d -i $f > $ft_ssl_location
	./differ.sh $f $openssl_location $ft_ssl_location $2
done
echo -e "\t\t]"

if [ "$2" == "--more" -a -e "fails" ]
then
	cat fails
fi
