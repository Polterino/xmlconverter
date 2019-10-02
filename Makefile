P=xmlconv

all: pulisci compila esegui

compila:
	gcc -o ${P} ${P}.c

pulisci:
	if [ -f ${P} ] ; then rm ${P} ; fi
	
	if [ -f ${P}.c~ ] ; then rm ${P}.c~ ; fi

esegui:
	./${P}
