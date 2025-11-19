# Parziali_Lab_Programmazione
Reopsitory con i progetti per l'esame di laboratorio di programmazione, update
IMPORTANTE PER RICCARDO  (DOBBIAMO DISCUTERNE):
Il modo in cui è stata scritta menuGestioneLibri (Opzione 1) è corretto e robusto. Il modo in cui è stata scritta menuGestioneUtenti contiene un bug perché la modifica del puntatore database_utenti è solo locale e non si propaga al main.

Per uniformare il codice, la soluzione migliore e più sicura è applicare il modello del puntatore a puntatore (Opzione 1) a tutte le sezioni del codice (Utenti, Prestiti) che modificano dinamicamente la dimensione di un array. Sebbene l'Opzione 2 funzioni, è più soggetta a errori, poiché è facile dimenticare di riassegnare il valore di ritorno in una delle funzioni della catena di chiamate.
Discussione: occcorre passare come parametro delle funzioni un puntatore a puntatore per rendere il programma piu robusto? 
