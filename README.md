# Parziali_Lab_Programmazione
Reopsitory con i progetti per l'esame di laboratorio di programmazione, update


merge artigianale pronto per debug. non da problemi.
Prossime mosse: statistiche e report + scrittura su file e lets goooo
=======

IMPORTANTE PER RICCARDO  (DOBBIAMO DISCUTERNE):

Il modo in cui è stata scritta menuGestioneLibri (Opzione 1) è corretto e robusto. Il modo in cui è stata scritta menuGestioneUtenti contiene un bug perché la modifica del puntatore database_utenti è solo locale e non si propaga al main.

Per uniformare il codice, la soluzione migliore e più sicura è applicare il modello del puntatore a puntatore (Opzione 1) a tutte le sezioni del codice (Utenti, Prestiti) che modificano dinamicamente la dimensione di un array. Sebbene l'Opzione 2 funzioni, è più soggetta a errori, poiché è facile dimenticare di riassegnare il valore di ritorno in una delle funzioni della catena di chiamate.

Discussione: occcorre passare come parametro delle funzioni un puntatore a puntatore per rendere il programma piu robusto? 

Riga 666: a che serve quella funzione ? ins ?



# RICORDARSI: 
CONTROLLO Se non ci sono utenti da fare (ANTO)  
MENU in "Inserisci il codice dell'utente che stai cercando" (RICK)  
NON STAMPA I PRESTITI RESTITUITI (RICK)  
CONTROLLO Se non ci sono libri da fare (Statistiche e report) (ANTO)  
INSERIRE "AGGIUNGI COPIE" (futuro)  
Se Libri/Utenti/Prestiti == NULL Nella lettura del database, bisogna uscire                                     da tutto il programma (e fare i vari free) (RICK)  
CONTROLLO "return" in funzioni void (ANTO)  
Inserire CONTROLLO risposta 'S' e 'N' nella funzione ESCI (ANTO)  
Togliere **libri e lasciare *libri (ANTO) discussione per realloc (RICK)  

controlli chiesti dal professore:
1. Inserimento libro con ISBN valido
2. Inserimento libro con ISBN duplicato (deve fallire)
3. Ricerca libro esistente
4. Ricerca libro non esistente
5. Creazione prestito con libro disponibile
6. Creazione prestito con libro non disponibile (deve fallire)
7. Restituzione libro
8. Salvataggio e caricamento da file binario
9. Esportazione catalogo in formato testo
10. Statistiche con database vuoto
11. Statistiche con database popolato
12. Gestione array pieno

T06 e T07 e T11 screenshot da rifare, non ce il menu di scelta dopo l'inserimento sballato del codice isbn


// PARTE DELLA DISCUSSIONE CON LE CHIAMATE DEI DOPPI PUNTATORI
Riassunto delle modifiche essenziali
Menu File: Tutti i parametri array (libri, utenti, prestiti) devono diventare Libro **, Utente **, Prestito **. I parametri di conteggio/capacità (numLibri, capLibri) devono essere puntatori int *.
Menu Libri/Utenti: Il puntatore all'array principale deve essere ** (doppio puntatore) per permettere l'aggiornamento dopo realloc.
Chiamate Main: Usa l'operatore & (es. &libri) quando chiami i menu modificati.
Se applichi queste modifiche, il passaggio dei dati sarà coerente e la gestione della memoria dinamica (specialmente il ridimensionamento e il caricamento da file) funzionerà correttamente sul database principale nel main.

Non posso fare la stessa cosa con il puntatore singolo all'array (che punta al primo elemento) ?


La risposta breve è: No, non puoi, se all'interno della funzione esegui una realloc (o malloc).
Se usi un puntatore singolo (Libro *libri), il main non verrà mai a sapere che l'indirizzo della memoria è cambiato. Questo porterà il tuo programma a crashare non appena provi a usare quella memoria dopo la funzione.

Perché nel tuo caso la Soluzione 1 è obbligatoria per menuGestioneFile?
Perché quella funzione deve modificare TRE array contemporaneamente (libri, utenti, prestiti). In C puoi restituire (return) un solo valore alla volta. Quindi l'unico modo per modificare 3 puntatori è passarli tutti e tre come doppi puntatori (**).


# NUOVE COSE DA RICORDARE:
ANTO: controllare la funzione calcolaDatabaseBinario
ANTO: richiedere il salvataggio del file quando si esce (OBBLIGATORIO)
ANTO: Manca la scritta "Libro in assoluto più prestato"

# IDEE: 
Inserire aggiungi copie
Inserire richiesta all'avvio di caricamento di file
