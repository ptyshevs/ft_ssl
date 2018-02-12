#!/bin/bash

echo "All arguments are" $@

for f in tests/base64/simple*
do
	openssl_location="temp/"$(basename $f)"_openssl"
	ft_ssl_location="temp/"$(basename $f)"_ft_ssl"

	touch $openssl_location
	touch $ft_ssl_location
	echo `cat $f` | openssl base64 > $openssl_location
	echo `cat $f` | $1 base64 > $ft_ssl_location
done
