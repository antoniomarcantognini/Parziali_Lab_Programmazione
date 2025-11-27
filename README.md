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



RICORDARSI: Inserire menu uscita da inserimento libri (ANTO)
            Formattazione buggata su: cerca libri per autore (ANTO)
            CONTROLLO Se non ci sono utenti da fare (ANTO)
            MENU in "Inserisci il codice dell'utente che stai cercando" (RICK)
            NON STAMPA I PRESTITI RESTITUITI (RICK)
            CONTROLLO Se non ci sono libri da fare (Statistiche e report) (ANTO)
            INSERIRE L'if per la scrittura dei libri nella gestione statistiche e report (Anche 1 volte nei top 5 libri) (ANTO)
            INSERIRE "AGGIUNGI COPIE" (futuro)
            TOP 5 LIBRI con vettore di indici (ANTO)
            Se Libri/Utenti/Prestiti == NULL Nella lettura del database, bisogna uscire da tutto il programma (e fare i vari free) (RICK)
            TEST da riscrivere (ANTO)
            CONTROLLO "return" in funzioni void (ANTO)
            Inserire CONTROLLO risposta 'S' e 'N' nella funzione ESCI (ANTO)
            Togliere **libri e lasciare *libri (ANTO)


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
