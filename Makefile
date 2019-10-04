P=xmlconv

all: pulisci compila esegui

compila:
	gcc ${P}.c -Llib -lxml -o ${P}

pulisci:
	if [ -f ${P} ] ; then rm ${P} ; fi
	
	if [ -f ${P}.c~ ] ; then rm ${P}.c~ ; fi

esegui:
	./${P}
