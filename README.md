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


#previus main:
int main(){
    Libro *libri;
    Utente *utenti;
    Prestito *prestiti;
    
 Inizializzazione delle variabili capacità massime a 5, poi duplicate dentro le funzioni con il realloc
    int capacitaMaxLibri = 5;
    int* ptrCapLibri = &capacitaMaxLibri;
        
    int capacitaMaxUtenti = 5;
    int* ptrCapUtenti = &capacitaMaxUtenti;
    int capacitaMaxPrestiti = 5;
    int* ptrCapPrestiti = &capacitaMaxPrestiti;
    char scelta;
        
    int numLibri = 0;
    int* ptrNumLibri = &numLibri;

    int numUtenti = 0;
    int* ptrNumUtenti = &numUtenti;

    int numPrestiti = 0;
    int* ptrNumPrestiti = &numPrestiti;

    int flagUscita = 0;   // 0 continua, 1 esci

    
    // Inizializzazione dinamica con malloc 
    libri = (Libro*)malloc(capacitaMaxLibri*sizeof(Libro));
    if (libri == NULL) {
        printf("Errore critico nell'allocazione della memoria per i libri!\n");
        return 1;
    }
    utenti = (Utente*)malloc(capacitaMaxUtenti*sizeof(Utente));
    if (utenti == NULL) {
        printf("Errore critico nell'allocazione della memoria per gli utenti!\n");
        free(libri);
        return 1;
    }
    prestiti = (Prestito*)malloc(capacitaMaxPrestiti*sizeof(Prestito));
    if (prestiti == NULL) {
        printf("Errore critico nell'allocazione della memoria per i prestiti!\n");
        free(libri);
        free(utenti);
        return 1;
    }
    printf("Database inizializzato correttamente ! \n\n");

    do{
        printf("\n\n=== GESTIONE BIBLIOTECA DIGITALE ===\n\n");
        printf("Inserisci la tua scelta: \n\n");
        
        printf("A. GESTIONE LIBRI\n");
        printf("B. GESTIONE UTENTI\n");
        printf("C. GESTIONE PRESTITI\n");
        printf("D. STATISTICHE E REPORT\n");
        printf("E. GESTIONE FILE \n");
        printf("F. ESCI \n");

        scanf(" %c",&scelta);
        scelta = toupper(scelta);

        switch (scelta)
        {
            case 'A':
                menuGestioneLibri(&libri, ptrNumLibri, ptrCapLibri);
                break;
            case 'B':
                Utente* utente_temp;
                utente_temp = menuGestioneUtenti(utenti, ptrNumUtenti, ptrCapUtenti);
                if (utente_temp == NULL) {
                    flagUscita = 1;  // uscita di emergenza
                } 
                utenti = utente_temp;
                break;
            case 'C':
                Prestito* prestito_temp; 
                prestito_temp = menuGestionePrestiti(utenti, libri, prestiti, ptrNumUtenti, ptrNumLibri, ptrNumPrestiti, ptrCapPrestiti);
                if (prestito_temp == NULL) {
                    flagUscita = 1;  // uscita di emergenza
                }
                prestiti = prestito_temp;
                break;
            case 'D':
                menuGestioneStatisticheReport(libri, utenti, prestiti, *ptrNumLibri, *ptrNumUtenti, *ptrNumPrestiti);  // qui ho aggiunto *
                break;
            case 'E':
                int flagGestioneFile = menuGestioneFile(libri, *ptrNumLibri, *ptrCapLibri, utenti, *ptrNumUtenti, *ptrCapUtenti, prestiti, *ptrNumPrestiti, *ptrCapPrestiti);
                if (flagGestioneFile == -1) { // Libero la memoria evitando la variabile che ha dato errore
                    
                    if (libri == NULL) {
                        free(prestiti);
                        free(utenti);
                    } else {
                        free(libri);
                    if (prestiti == NULL) {
                        free(utenti);
                    } else {
                        free(prestiti);
                        }
                    }
                return 1;
            }
            break;
            case 'F':
                break;
            default: 
                printf("Errore, inserisci un carattere corretto! \n");
            break;
        }
    }while(flagUscita == 0);
