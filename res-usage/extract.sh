#!/bin/bash
echo 'ioparse started'
./ioparse $1
echo 'ioparse completed'

echo 'clearing headers in perfparsed'
sed -i -e 's/#           time             comm-pid                  counts unit events//g' perftrace-${1}.txt
sed -i '/^$/d' perftrace-${1}.txt
echo 'perfparsed started'
./perfparse $1
echo 'perfparsed completed'

echo 'raplparsed started'
./raplparse $1
echo 'raplparsed completed'
