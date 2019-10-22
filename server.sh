#!/bin/bash
porta=9999
eseguibile="./xmlconv"

while true
do
	echo "Eseguo $eseguibile in porta $porta"
	nc.traditional -l -p $porta -c "$eseguibile"
done
