# RICORDARSI: 
MENU in "Inserisci il codice dell'utente che stai cercando" (RICK)  
NON STAMPA I PRESTITI RESTITUITI (RICK)  
INSERIRE "AGGIUNGI COPIE" (futuro)  
Se Libri/Utenti/Prestiti == NULL Nella lettura del database, bisogna uscire                                     da tutto il programma (e fare i vari free) (RICK)   
Controllare bug visualizzazione utenti (RICK)

# PARTE DELLA DISCUSSIONE CON LE CHIAMATE DEI DOPPI PUNTATORI
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


# IDEE: 
Inserire aggiungi copie
Inserire richiesta all'avvio di caricamento di file

# ULTIMI TEST:
Test di salvataggio su file binario
Test di caricamento corretto dei dati
Verifica integrità dei dati dopo caricamento
