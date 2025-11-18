#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char codice_ISBN[18];
    char titolo[101];
    char autore[51];
    int anno_pubblicazione;
    int numero_copie;
    char genere[31];
} Libro;

typedef struct {
    int codice_utente;
    char nome[51];
    char cognome[51];
    char email[81];
    char data_iscrizione[11];
} Utente;

typedef struct {
    int codice_prestito;
    char codice_ISBN_libro[18];
    int codice_utente;
    char data_prestito[11];
    char data_restituzione_prevista[11];
    int restituito;
} Prestito;

// prototipi delle funzioni
void menuGestioneLibri(Libro **libri, int *ptrNumLibri, int *ptrCapLibri, int numLibri);   // numLibri è il valore del puntatore!!

Libro* inserisciNuovoLibro(Libro *libri, int *ptrNumLibri, int *ptrCapLibri);
void visualizzaTuttiILibri(Libro *libri, int numLibri);
void cercaLibroPerISBN(Libro *libri,int numLibri);
int formatoCorrettoISBN(char *s);
void cercaLibriPerAutore(Libro *libri,int numLibri);
void libriDisponibiliPerPrestito(Libro *libri,int numLibri);


void menuGestioneUtenti(void);
void menuGestionePrestiti(void);
void menuGestioneStatisticheReport(void);
void menuGestioneFile(void);



// funzione per il corretto inserimento dell'ISBN:
int formatoCorrettoISBN(char *s) {
    if (strlen(s) != 17) return 0; // 13 cifre + 4 trattini = 17 char

    // posizioni dei trattini
    int trattinoPos[4] = {3, 5, 10, 15};
    // controlla ogni carattere
    for (int i = 0; i < 17; ++i) {
        int isTrattinoPos = 0;
        for (int j = 0; j < 4; ++j) {
            if (i == trattinoPos[j]) { isTrattinoPos = 1; break; }
        }

        if (isTrattinoPos) {
            if (s[i] != '-') return 0;
        } else {
            if (!isdigit((unsigned char)s[i])) return 0;
        }
    }

    return 1;
}


// Funzione inserisciNuovoLibro     libri,*ptrNumLibri, *ptrCapLibri
Libro* inserisciNuovoLibro(Libro *libri,int *ptrNumLibri,int* ptrCapLibri){
    
    // riallocamento se necessario
    if(*ptrNumLibri == *ptrCapLibri){
        libri = realloc(libri, sizeof(Libro)*2*(*ptrCapLibri));
        if(libri == NULL){ // Per risparmiare tempo, in caso di errore di allocazione esco subito dalla funzione
            return NULL;
        }
        *ptrCapLibri = 2 * *ptrCapLibri;
    }
   
    int duplicato;
    char ISBN_temp[18];
    printf("\n=== INSERIMENTO NUOVO LIBRO ===\n");

    // controllo sul corretto formato ISBN
    do {
        duplicato=0;
        printf("Inserisci codice ISBN (formato XXX-X-XXXX-XXXX-X): \n");
        scanf("%17s", ISBN_temp);

    if (!formatoCorrettoISBN(ISBN_temp)) {
        printf("Formato ISBN NON valido. Riprova.\n");
        continue;
    }

    // controllo eventuali duplicati (il codice ISBN è univoco)
    //int duplicato = 0;
    for (int i = 0; i < *ptrNumLibri; i++) {
        if (!strcmp(libri[i].codice_ISBN, libri[*ptrNumLibri].codice_ISBN)) {
            printf("ISBN già presente nella libreria. Riprova.\n");
            duplicato=1;
            break;
        }
    }
    // ripeti finché non valido o duplicato
} while (!formatoCorrettoISBN(ISBN_temp) || duplicato == 1);

    strcpy(libri[*ptrNumLibri].codice_ISBN,ISBN_temp);

    // Input titolo
    printf("Inserisci titolo (max 100 caratteri): ");
    scanf(" %100[^\n]", libri[*ptrNumLibri].titolo); 
    
    // Input autore
    printf("Inserisci autore (max 50 caratteri): ");
    scanf(" %50[^\n]", libri[*ptrNumLibri].autore);  
    
    // Input anno pubblicazione
    int anno_tmp;
    int rc;
    do {
        printf("Inserisci anno pubblicazione: ");
        scanf("%d", &anno_tmp);
        /* controlli sul range */
        if (anno_tmp < 1800 || anno_tmp > 2025) {
            printf("Anno di pubblicazione non valido (deve essere tra 1800 e 2025). Riprova.\n");
            continue;
        }
        break;
    } while (1);
    libri[*ptrNumLibri].anno_pubblicazione = anno_tmp;

    // input numero di copie
    int copie_tmp;
    do {
        printf("Inserisci numero copie: ");
        scanf("%d", &copie_tmp);
        if (copie_tmp <= 0) {
            printf("Numero di copie non valido (deve essere > 0). Riprova.\n");
            continue;
        }
        break;
    } while (1);
    libri[*ptrNumLibri].numero_copie = copie_tmp;


    // Input genere
    printf("Inserisci genere (max 30 caratteri): ");
    scanf(" %30[^\n]", libri[*ptrNumLibri].genere);   // Nota lo spazio iniziale!
    
    // Incrementa il contatore al prossimo libro nell'array libri
    (*ptrNumLibri)++;

    printf("Libro inserito con successo!\n");
    return libri;
}

// funzione visualizzaTuttiILibri: libri, *ptrNumLibri
void visualizzaTuttiILibri(Libro *libri, int numLibri){
    /*if (numLibri <= 0) {
        printf("Nessun libro presente.\n");
        return;
    }*/
     // intestazione tabella
    printf("\n%-17s | %-30s | %-20s | %-6s | %-6s | %-15s\n", "ISBN", "Titolo", "Autore", "Anno", "Copie", "Genere");  // controlla formati
    printf("\n\n");

    // Riga per ogni libro (uso precisione per troncare senza overflow) // todo: da tabella a lista (+leggibile)
    for (int i = 0; i < numLibri; ++i) {
        printf("%-17.17s | %-30.30s | %-20.20s | %6d | %6d | %-15.15s\n",
               libri[i].codice_ISBN,
               libri[i].titolo,
               libri[i].autore,
               libri[i].anno_pubblicazione,
               libri[i].numero_copie,
               libri[i].genere);
    }
    printf("\n");
}

// funzione cerca libro per ISBN-> ritorna o l'indice o -1 attraverso una stampa libri,numLibri
void cercaLibroPerISBN(Libro *libri,int numLibri){
    if (numLibri <= 0) {
        printf("Nessun libro presente.\n");
        return;
    }

    int srcFlag = -1;
    char isbnInserito[18];
    do{
        // inserimento codice ISBN
        printf("Inserisci codice ISBN (formato XXX-X-XXXX-XXXX-X): \n");
        scanf("%17s", isbnInserito);
        if (!formatoCorrettoISBN(isbnInserito)) {
        printf("Formato ISBN NON valido. Riprova.\n");  // migliorare controllo qui!
        continue;
        }

        // ricerca isbn inserito:
        for(int i = 0; i < numLibri; i++){
            if(!strcmp(isbnInserito,libri[i].codice_ISBN)){
            srcFlag = i;
            break;
            }
        } 
    
    // stampo i risultati ottenuti
    if(srcFlag == -1){  // se l'isbn non è stato trovato, è possibile inserire un altro codice oppure tornare alla gestione libri
        int scelta;
        printf("\n Non è stato trovato nessun libro con il codice ISBN inserito!\n");
        printf("Cosa vuoi fare?\n");
        printf("\n  1. Inserire un altro codice ISBN da cercare;\n");
        printf("  2. Tornare al menù gestione libri.\n");
        printf("\nLa tua scelta: ");

        do{ // ciclo per la scelta del isbn
            //inserimento scelta:
            scanf("%d",&scelta);
            switch (scelta)
            {
            case 1:
                break;

            case 2:
                return;

            default:
                printf("La tua scelta deve essere 1 oppure 2! Riprova:\n");
                printf("\nLa tua scelta: ");
                break;
            }
        }while (scelta!=1 && scelta != 2);
    } else{   // se il libro viene trovato, ne vengono stampati i dati(indice srcFlag):
        printf("\nLibro trovato! \n");
        printf("Codice ISBN: %s\n",libri[srcFlag].codice_ISBN);
        printf("Titolo: %s\n",libri[srcFlag].titolo);
        printf("Autore: %s\n",libri[srcFlag].autore);
        printf("Anno di pubblicazione: %d\n",libri[srcFlag].anno_pubblicazione);
        printf("Numero di copie: %d\n", libri[srcFlag].numero_copie);
        printf("Genere: %s\n",libri[srcFlag].genere);
    }
    }while(srcFlag == -1 || !formatoCorrettoISBN(isbnInserito));
}

// funzione cerca libri per autore  libri,numLibri
void cercaLibriPerAutore(Libro *libri,int numLibri){
    if (libri == NULL || numLibri <= 0) {
        printf("Nessun libro presente.\n");
        return;
    }

    int srcFlag = -1;
    char autoreInserito[51];
    do{
        // inserimento codice autore:
        printf("Inserisci il nome dell'autore: \n");
        scanf(" %50[^\n]",autoreInserito);

        // ricerca nome autore
        for(int i = 0; i < numLibri; i++){
            if(!strcmp(libri[i].autore,autoreInserito)){
                srcFlag = i;
                printf("Libro trovato! \n");
                printf("Codice ISBN: %-17.17s\n",libri[srcFlag].codice_ISBN);
                printf("Titolo: %-30.30s\n",libri[srcFlag].titolo);
                printf("Autore: %-20.20s\n",libri[srcFlag].autore);
                printf("Anno di pubblicazione: %6d\n",libri[srcFlag].anno_pubblicazione);
                printf("Numero di copie: %6d\n", libri[srcFlag].numero_copie);
                printf("Genere: %-15.15s\n",libri[srcFlag].genere);
            }
        }
        if(srcFlag == -1){  // se l'autore non è stato trovato, è possibile inserire un altro codice oppure tornare alla gestione libri
        int scelta;
        printf("\n Non è stato trovato nessun libro con il nome dell'autore inserito!\n");
        printf("Cosa vuoi fare?\n");
        printf("\n  1. Inserire un altro nome dell'autore da cercare;\n");
        printf("  2. Tornare al menù gestione libri.\n");
        printf("\nLa tua scelta: ");

        do{ // ciclo per la scelta del autore
            //inserimento scelta:
            scanf("%d",&scelta);
            switch (scelta)
            {
            case 1:
                break;

            case 2:
                return;

            default:
                printf("La tua scelta deve essere 1 oppure 2! Riprova:\n");
                printf("\nLa tua scelta: ");
                break;
            }
        }while (scelta!=1 && scelta != 2);
    }
    }while(srcFlag == -1 );
}

// funzione libri disponibili per il prestito,visualizza solo libri con numero copie >0 e li ordina per il titolo: ordine alfabetico crescente
void libriDisponibiliPerPrestito(Libro *libri,int numLibri){
    // Controllo iniziale
    if (numLibri <= 0) {
        printf("Nessun libro presente.\n");
        return;
    }
    
    // ordino libri con num copie>0 in ordine crescente
    int numOrdinati = 0; // contatore che tiene traccia del numero di copie disponibili(per stamparle)
    for(int i = 0; i < numLibri; i++){
        for(int j = i; j < numLibri; j++){
            
            // ordino solo se entrambi i libri hanno numerocopie>0
            if(libri[i].numero_copie > 0 && libri[j].numero_copie > 0){  // vincolo richiesto
                
                // confronto dei titoli lower case con strcmp
                if(strcmp(libri[i].titolo,libri[j].titolo)>0){           // bubble sort
                    // scambio tutta la struct
                    Libro temp = libri[i];
                    libri[i] = libri[j];
                    libri[j] = temp;
                }
            }
        }
    }

    // stampo solo libri con copie > 0
    printf("\n%-17s | %-30s | %-20s | %-6s | %-6s | %-15s\n\n",
           "ISBN", "Titolo", "Autore", "Anno", "Copie", "Genere");

    for (int i = 0; i < numLibri; i++) {
        if (libri[i].numero_copie > 0) {
            printf("%-17s | %-30.30s | %-20.20s | %6d | %6d | %-15.15s\n",
                   libri[i].codice_ISBN,
                   libri[i].titolo,
                   libri[i].autore,
                   libri[i].anno_pubblicazione,
                   libri[i].numero_copie,
                   libri[i].genere);
        }
    }
}


// menu A: GESTIONE LIBRI         libri, *ptrNumLibri, *ptrCapLibri, numLibri
void menuGestioneLibri(Libro **libri, int *ptrNumLibri, int *ptrCapLibri,int numLibri){
    int sceltaGestioneLibri = 0;
    do{
        printf("\n\n--Inserisci la tua scelta--\n\n"); 

        printf("1. Inserisci nuovo libro\n");
        printf("2. Visualizza tutti i libri\n");
        printf("3. Cerca libro per ISBN\n");
        printf("4. Cerca libri per autore\n");
        printf("5. Libri disponibili per prestito\n");
        printf("6. Torna al menu precedente\n");
        // Inserire "La tua scelta"

        scanf("%d",&sceltaGestioneLibri);

        switch (sceltaGestioneLibri)
        {
        case 1:
            Libro* temp;
            temp = inserisciNuovoLibro(*libri, ptrNumLibri, ptrCapLibri); 
            if (temp == NULL) {
                printf("Errore allocazione durante l'inserimento del libro. Memoria non modificata.\n");
                // menu principale
            } else {
                *libri = temp;
                // free(temp);     // AI mi dice di togliere questa riga, discuti con prince.
            }
            break;
        case 2: // passo l'indirizzo di memoria della struct dinamica libri
            visualizzaTuttiILibri(*libri, *ptrNumLibri);
            break;
        case 3:
            cercaLibroPerISBN(*libri,*ptrNumLibri);
            break;
        case 4:
            cercaLibriPerAutore(*libri,*ptrNumLibri);
            break;
        case 5:
            libriDisponibiliPerPrestito(*libri,*ptrNumLibri);
            break;
        case 6:
            return;
        default:
            printf("Errore, inserisci un valore corretto ! \n");
            break;
        }
    }while(sceltaGestioneLibri != 6); 
}

    int main(){
    // funzione menu principale:
    // dichiaro le variabili fuori dal do-while
        Libro *libri = NULL;
        Utente *utenti = NULL;
        Prestito *prestiti = NULL;
        
        int capacitaMaxLibri = 5;   // parto da 5 e poi la raddoppio mano a mano
        int* ptrCapLibri = &capacitaMaxLibri;
        
        int capacitaMaxUtenti = 0;
        int* ptrCapUtenti = &capacitaMaxUtenti;
        int capacitaMaxPrestiti = 0;
        int* ptrCapPrestiti = &capacitaMaxPrestiti;
        char scelta1;
        // int sceltaGestioneLibri = 0;
        
        int numLibri = 0;  // variabile che tiene conto del numero di libri inserito(nella funzione inserisci libro viene)
        int* ptrNumLibri = &numLibri;
        
        int numUtenti = 0;
        int numPrestiti = 0;

        // inizializzazione con malloc 
        libri = (Libro*)malloc(capacitaMaxLibri*sizeof(Libro));
        if (libri == NULL) {
            printf("Errore critico nell'allocazione della memoria per i libri!\n");
            return 1;  // esci, la memoria non puo essere allocata
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
        printf("=== GESTIONE BIBLIOTECA DIGITALE ===\n\n");
        printf("Inserisci la tua scelta: \n\n");
        
        printf("A. GESTIONE LIBRI\n");
        printf("B. GESTIONE UTENTI\n");
        printf("C. GESTIONE PRESTITI\n");
        printf("D. STATISTICHE E REPORT\n");
        printf("E. GESTIONE FILE \n");
        printf("F. ESCI \n");

        scanf(" %c",&scelta1);
        scelta1 = toupper(scelta1); // Rende la scelta non case-sensitive (A o a)

        switch (scelta1)
        {
        case 'A':
            // CHIAMATA ALLA FUNZIONE: Qui avviene il cambiamento.
            // Non passiamo il valore di 'libri' (l'indirizzo che contiene),
            // ma passiamo L'INDIRIZZO DELLA VARIABILE 'libri' STESSA.
            // Usiamo l'operatore '&' per ottenere l'indirizzo del puntatore.
            menuGestioneLibri(&libri, ptrNumLibri, ptrCapLibri, *ptrNumLibri);  // passo il valore del puntatore che ho incrementato nella funzione inserisci libro, permetendo alla funzione di modificarla
            break;
        /* case 'B':
            menuGestioneUtenti();
            break;
        case 'C':
            menuGestionePrestiti();
            break;
        case 'D':
            menuGestioneStatisticheReport();
            break;
        case 'E':
            menuGestioneFile();
            break;*/
        case 'F':
            break;
        default: 
            printf("Errore, inserisci un carattere corretto! \n");
            break;
        }
    }while(scelta1 != 'F');
    free(libri);
    free(utenti);
    free(prestiti);
    return 0;
    }