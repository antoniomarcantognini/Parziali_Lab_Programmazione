# RICORDARSI:  
- mettere indici ordinati fuori dalla funzione(RICK)
- menu codice utente da togliere e copiare dentro il codice in modo spartano
- rifai screen funzione cerca libro per isbn per report

Perché nel tuo caso la Soluzione 1 è obbligatoria per menuGestioneFile?
Perché quella funzione deve modificare TRE array contemporaneamente (libri, utenti, prestiti). In C puoi restituire (return) un solo valore alla volta. Quindi l'unico modo per modificare 3 puntatori è passarli tutti e tre come doppi puntatori (**).

# 

# IDEE: 
Inserire aggiungi copie
Inserire richiesta all'avvio di caricamento di file

# ULTIMI TEST:
Test di salvataggio su file binario
Test di caricamento corretto dei dati
Verifica integrità dei dati dopo caricamento
