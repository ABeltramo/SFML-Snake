Snake
==========

Il progetto è stato compilato tramite VC++ 2010.
Per poter utilizzare il progetto &egrave; necessaria l'installazione di SFML versione 2.0 http://www.sfml-dev.org/
Per informazioni su come installare la libreria vedere la seguente pagina: http://www.sfml-dev.org/tutorials/2.0/
Quelle che seguono sono le classi che ho utilizzato per il progetto con un breve riassunto sul loro utilizzo.
Per una documentazione più esaustiva vedere nella cartella documentazione

Controller360.h
-------
	Questa classe consente di utilizzare il controller dell'xbox 360.
	E' possibile collegare al pc fino a 4 controller tutti controllabili tramite questa classe.	
	Utilizza le xinput di windows; per maggiori info: http://msdn.microsoft.com/en-us/library/windows/desktop/ee417001(v=vs.85).aspx

DatFileClass.h
-------	
	Questo oggetto consente di creare un file .DAT il quale contiene dei file.
	Ad esempio per il mio Snake avevo la necessit&agrave; di salvare le immagini del corpo, dello sfondo, il font per il testo in un unico file.

FruitClass.h
-------
	Ho chiamato frutti gli oggetti che vengono mangiati dallo Snake e gli consentono di aumentare il proprio punteggio.
	Questa classe consente di aggiungere, eliminare, disegnare i frutti nel campo di gioco.

SnakeClass.h
-------
	Questo &egrave; è l'oggetto principale del gioco.
	Definisce un campo di gioco, il serpente vero e proprio, come esso debba essere disegnato, i movimenti possibili fino a quando non muore.
	Il punteggio del serpente è gestito dall'oggetto stesso ed infine con una piccola modifica è possibile aggiungere ulteriori serpenti al gioco.

Licenza
-------
Copyright (C) 2012  Alessandro Beltramo <beltramo.ale@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.