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


// Prototipi delle funzioni

/*
MENU GESTIONE FILE
*/

int menuGestioneFile(Libro *libri, int numLibri, int capLibri, Utente *utenti, int numUtenti, int capUtenti, Prestito *prestiti, int numPrestiti, int capPrestiti);
void salvaDatabaseSuFileBinario(Libro *libri, int numLibri, Utente *utenti, int numUtenti, Prestito *prestiti, int numPrestiti);
int caricaDatabaseDaFileBinario(Libro **libri, int *numLibri, int *capLibri, Utente **utenti, int *numUtenti, int *capUtenti, Prestito **prestiti, int *numPrestiti, int *capPrestiti);  // cap... è la capacità attuale
void esportaCatalogoInFormatoTesto(Libro *libri, int numLibri);
void esportaReportPrestitiInFormatoTesto(Prestito *prestiti, int numPrestiti, Libro *libri, int numLibri, Utente *utenti, int numUtenti);
void chiediSalvataggio(Libro *libri, int numLibri, Utente *utenti, int numUtenti, Prestito *prestiti, int numPrestiti);

/*
MENU GESTIONE STATISTICHE E REPORT
*/

void menuGestioneStatisticheReport(Libro *database_libri, Utente *database_utenti, Prestito *database_prestiti, int libri_inseriti,int utenti_inseriti, int prestiti_inseriti); 
void statisticheGenerali(Libro *database_libri, Utente *database_utenti, Prestito *database_prestiti, int libri_inseriti,int utenti_inseriti, int prestiti_inseriti);
int calcolaLibroPiuPrestato(Libro *database_libri, Prestito *database_prestiti, int libri_inseriti, int prestiti_inseriti, int *out_indice_libro, int *out_conteggio);
void visualizzaLibroPiuPrestato(Libro *database_libri, Prestito *database_prestiti, int libri_inseriti, int prestiti_inseriti);
void libriPerGenere(Libro* database_libri, int libri_inseriti);
void top5LibriPiuPrestati(Libro *database_libri, Prestito *database_prestiti, int libri_inseriti, int prestiti_inseriti);

/*
MENU GESTIONE UTENTI
*/
Utente* menuGestioneUtenti(Utente* database_utenti, int* utenti_inseriti, int* capacita_attuale_utenti);

// Inserimento utente
Utente* inserisci_nuovo_utente(Utente* database_utenti,int* utenti_inseriti,int* capacita_utenti_attuale);
int inserimento_dati_utenti(Utente* database_utenti,int* utenti_inseriti);
int inserimento_codice_utente(Utente* database_utenti,int* utenti_inseriti);
void inserimento_data_iscrizione(Utente* database_utenti,int* utenti_inseriti);
void inserimento_email(Utente* database_utenti,int* utenti_inseriti);

// Visualizzazione degli utenti
void visualizza_tutti_gli_utenti(Utente* database_utenti,int utenti_inseriti);
int stampa_ordine_alfabetico_nomi(Utente* database_utenti,int utenti_inseriti);
int stampa_ordine_alfabetico_cognomi(Utente* database_utenti,int utenti_inseriti);
int stampa_ordine_email(Utente* database_utenti,int utenti_inseriti);
int stampa_ordine_codice_utente(Utente* database_utenti,int utenti_inseriti);
int stampa_ordine_data_iscrizione(Utente* database_utenti,int utenti_inseriti);
void stampa_dati_utenti(Utente* database_utenti, int utenti_inseriti, int* indici_ordinati);

// Ricerca utente
void cerca_utente_per_codice(Utente* database_utenti,int utenti_inseriti);

/* 
MENU GESTIONE PRESTITI
*/

// Registrazione prestiti
Prestito* menuGestionePrestiti(Utente* database_utenti,Libro* database_libri, Prestito* database_prestiti,int* utenti_inseriti, int* libri_inseriti,int* prestiti_inseriti,int* capacita_attuale_prestiti);
Prestito* registra_prestito(Libro* database_libri,Utente* database_utenti,Prestito* database_prestiti,int* prestiti_inseriti,int* capacita_attuale_prestiti,int libri_inseriti,int utenti_inseriti);
void richiedi_libro_utente(Libro* database_libri,Utente* database_utenti,int* utenti_inseriti,int libri_inseriti,int*posizione_utente,int* posizione_libro);

// Richiesta libro
int richiesta_codice_ISBN(Libro* database_libri,int libri_inseriti,char ISBN[],int* posizione_libro);
int invalida_ISBN(char ISBN[18]);
int invalida_data(char data[11]);
void controlla_esistenza_libro(Libro* database_libri,int libri_inseriti,char ISBN[],int* posizione_libro);
int menu_codice_ISBN_non_valido();

// Richiesta utente
void richiesta_codice_utente(Utente* database_utenti, int utenti_inseriti, int* codice, int* posizione_utente);
void controlla_esistenza_utente(Utente* database_utenti,int utenti_inseriti,int codice,int* posizione_utente);
int menu_codice_utente_non_valido();

// Calcolo data di restituzione
void calcola_30_giorni_dopo(char data[]);
void estrapola_data_numerica(char data[],int* anno, int* mese, int* giorno);
int calcola_data_valore(int* anno,int* mese, int* giorno);
void costruisci_data_da_valore_data(int data_valore,int* anno, int* mese, int* giorno);
void costruisci_stringa_da_data(char data[],int anno,int mese,int giorno);

// Registrazione restituzioni
void registra_restituzione(Prestito* database_prestiti, Libro* database_libri,int prestiti_inseriti,int libri_inseriti);
int menu_codice_prestito_errato();

// Visualizzazione dei prestiti attivi
void visualizza_prestiti_attivi(Utente* database_utenti,Prestito* database_prestiti,Libro* database_libri,int libri_inseriti,int prestiti_inseriti,int utenti_inseriti);

// Visualizzazione storico dei prestiti
void visualizza_storico_prestiti_utente(Utente* database_utenti,Prestito* database_prestiti,int utenti_inseriti,int prestiti_inseriti);
void stampa_prestito(Prestito* database_prestiti,int indice_prestito_assoluto,int indice_prestito_nel_ciclo_specifico);

/*
MENU GESTIONE LIBRI
*/

void menuGestioneLibri(Libro **libri, int *ptrNumLibri, int *ptrCapLibri);
Libro* inserisciNuovoLibro(Libro *libri, int *ptrNumLibri, int *ptrCapLibri);
void visualizzaTuttiILibri(Libro *libri, int numLibri);
void cercaLibroPerISBN(Libro *libri,int numLibri);
int formatoCorrettoISBN(char *s);
void cercaLibriPerAutore(Libro *libri,int numLibri);
void libriDisponibiliPerPrestito(Libro *libri,int numLibri);
int menu_errore_inserimento_ISBN();

int main(){
    Libro *libri;
    Utente *utenti;
    Prestito *prestiti;
    
    // Inizializzazione delle variabili capacità massime a 5, poi duplicate dentro le funzioni con il realloc
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
                } else{
                    utenti = utente_temp;
                }
                break;
            case 'C':
                Prestito* prestito_temp; 
                prestito_temp = menuGestionePrestiti(utenti, libri, prestiti, ptrNumUtenti, ptrNumLibri, ptrNumPrestiti, ptrCapPrestiti);
                if (prestito_temp == NULL) {
                    flagUscita = 1;  // uscita di emergenza
                } else{
                    prestiti = prestito_temp;
                }
                break;
            case 'D':
                menuGestioneStatisticheReport(libri, utenti, prestiti, *ptrNumLibri, *ptrNumUtenti, *ptrNumPrestiti);  // qui ho aggiunto *
                break;
            case 'E':
                int flagGestioneFile = menuGestioneFile(libri, *ptrNumLibri, *ptrCapLibri, utenti, *ptrNumUtenti, *ptrCapUtenti, prestiti, *ptrNumPrestiti, *ptrCapPrestiti);
                if (flagGestioneFile == -1) { // Libero la memoria evitando la variabile che ha dato errore
                    flagUscita = 1;
                }
                break;
            case 'F': // l'utente ha scelto "Esci" dal menu principale
                chiediSalvataggio(libri, *ptrNumLibri, utenti, *ptrNumUtenti, prestiti, *ptrNumPrestiti);
                flagUscita = 1;
                break;
            default: 
                printf("Errore, inserisci un carattere corretto! \n");
            break;
        }
    }while(flagUscita == 0);

    free(libri);
    free(utenti);
    free(prestiti);
    return 0;
}

// === MENU GESTIONE FILE === //
int menuGestioneFile(Libro *libri, int numLibri, int capLibri, Utente *utenti, int numUtenti, int capUtenti, Prestito *prestiti, int numPrestiti, int capPrestiti){
    int scelta;
    do{
        printf("=== MENU GESTIONE FILE ===\n");
        printf("  1. Salva database su file binario\n");
        printf("  2. Carica database da file binario\n");
        printf("  3. Esporta catalogo in formato testo\n");
        printf("  4. Esporta report prestiti in formato testo\n");
        printf("  5. Torna al menù principale.\n");
        printf("  6. Esci.\n");
        printf("\nTua scelta: ");
        scanf("%d",&scelta);
        
        switch(scelta)
        {
            case 1:
            salvaDatabaseSuFileBinario(libri, numLibri, utenti, numUtenti, prestiti, numPrestiti);  
            break;
            
            case 2:
            int flagCaricaDatabase = caricaDatabaseDaFileBinario(&libri, &numLibri, &capLibri, &utenti, &numUtenti, &capUtenti, &prestiti, &numPrestiti, &capPrestiti);
            if (flagCaricaDatabase == -1) {
                return -1;
            }
            break;
            
            case 3:
            esportaCatalogoInFormatoTesto(libri, numLibri);
            break;
            
            case 4:
            esportaReportPrestitiInFormatoTesto(prestiti, numPrestiti, libri, numLibri, utenti, numUtenti);
            break;

            case 5:
            break;

            case 6:
            chiediSalvataggio(libri, numLibri, utenti, numUtenti, prestiti, numPrestiti);
            return -1;  // segnale di uscita dal programma

            default:
                printf("Errore nell'inserimento della scelta! Deve essere 1, 2, 3 o 4\n");
                printf("Riprova:\n");
                break;
        }

    }while(scelta!=5);
    return 0;
}

// Funzioni gestione file:
// funzione salva database su file binario
void salvaDatabaseSuFileBinario(Libro *libri, int numLibri, Utente *utenti, int numUtenti, Prestito *prestiti, int numPrestiti){
    FILE *fp;
    printf("\nAvvio salvataggio dati...\n");
    // Salvataggio LIBRI (libri.dat)
    fp = fopen("libri.dat","wb");
    if (fp == NULL){
        printf("Errore: impossibile aprire 'libri.dat' per la scrittura.\n");
        return;
    }else{
        // Scrivo il numero di elementi
        fwrite(&numLibri, sizeof(int), 1, fp);
        
        // Scrivo l'array completo se ci sono libri
        if (numLibri > 0) {
            if (fwrite(libri, sizeof(Libro), numLibri, fp) != numLibri) {
                printf("Attenzione: Errore durante la scrittura dei dati dei libri.\n");
            }
        }
        fclose(fp);
        printf("- Libri salvati correttamente (%d %s).\n", numLibri, (numLibri == 1) ? "elemento" : "elementi");
    }
    // Salvataggio UTENTI (utenti.dat)
    fp = fopen("utenti.dat","wb");
    if(fp == NULL){
        printf("Errore: impossibile aprire 'utenti.dat' per la scrittura.\n");
        return;
    }else{
        fwrite(&numUtenti, sizeof(int), 1, fp);
        
        if (numUtenti > 0) {
            if (fwrite(utenti, sizeof(Utente), numUtenti, fp) != numUtenti) {
                printf("Attenzione: Errore durante la scrittura dei dati degli utenti.\n");
            }
        }
        fclose(fp);
        printf("- Utenti salvati correttamente (%d %s).\n", numUtenti, (numUtenti == 1) ? "elemento" : "elementi");
    }
    // Salvataggio PRESTITI (prestiti.dat)
    fp = fopen("prestiti.dat","wb");
    if (fp == NULL) {
        printf("Errore critico: Impossibile aprire 'prestiti.dat' per la scrittura.\n");
        return;
    } else {
        fwrite(&numPrestiti, sizeof(int), 1, fp);
        
        if (numPrestiti > 0) {
            if (fwrite(prestiti, sizeof(Prestito), numPrestiti, fp) != numPrestiti) {
                printf("Attenzione: Errore durante la scrittura dei dati dei prestiti.\n");
            }
        }
        fclose(fp);
        printf("- Prestiti salvati correttamente (%d %s).\n", numPrestiti, (numPrestiti == 1) ? "elemento" : "elementi");
    }
    
    printf("Operazione di salvataggio conclusa.\n");
}    

// funzione carica database da file binario
int caricaDatabaseDaFileBinario(Libro **libri, int *numLibri, int *capLibri, Utente **utenti, int *numUtenti, int *capUtenti, Prestito **prestiti, int *numPrestiti, int *capPrestiti) {
    FILE *fp;
    int tempNum;

    printf("\n=== CARICAMENTO DATABASE ===\n");

    // --- CARICAMENTO LIBRI ---
    fp = fopen("libri.dat", "rb");
    if (fp == NULL) {
        printf("[!] File 'libri.dat' non trovato. Nessuna modifica ai libri.\n");
        return 0;
    } else {
        // Leggo il numero di elementi
        fread(&tempNum, sizeof(int), 1, fp);

        if (tempNum >= 0) {
            // nuova capacità, massimo fra tempNum e 5
            int nuovaCapacita = (tempNum > 5) ? tempNum : 5;
            
            // Alloco la nuova memoria
            Libro *tempLibri= (Libro*)malloc(nuovaCapacita * sizeof(Libro));

            if (tempLibri == NULL) {
                printf("Errore critico di allocazione memoria per i libri!\n");
                printf("Dati precedenti mantenuti.\n"); // perche non tocco *libri
                return -1;
            } else {
                // Leggo l'array intero
                fread(tempLibri, sizeof(Libro), tempNum, fp);
                // Scambio i puntatori
                free(*libri);      // Ora posso liberare il vecchio sicuro
                *libri = tempLibri;  // Assegno il nuovo
                *numLibri = tempNum;
                *capLibri = nuovaCapacita;
                printf("[OK] Caricati %d libri.\n", tempNum);
            }
        }
            fclose(fp);
    }

    // --- CARICAMENTO UTENTI ---
    fp = fopen("utenti.dat", "rb");
    if (fp == NULL) {
        printf("[!] File 'utenti.dat' non trovato. Nessuna modifica agli utenti.\n");
    } else {
        fread(&tempNum, sizeof(int), 1, fp);
        if (tempNum >= 0) {
            int nuovaCapacita = (tempNum > 5) ? tempNum : 5;
            Utente *tempUtenti = (Utente*)malloc(nuovaCapacita * sizeof(Utente));

            if (tempUtenti == NULL) {
                printf("Errore critico di allocazione memoria per gli utenti!\n");
                printf("Dati precedenti mantenuti.\n");
                return -1;
            } else {
                int letti = fread(tempUtenti, sizeof(Utente), tempNum, fp);
                if (letti == tempNum) {
                    free(*utenti);        // Libero il vecchio array
                    *utenti = tempUtenti; // Assegno il nuovo array
                    *numUtenti = tempNum;
                    *capUtenti = nuovaCapacita;
                    printf("[OK] Caricati %d utenti.\n", tempNum);
                } else {
                    // Errore lettura: Pulisco il temporaneo e non tocco i dati precedenti
                    printf("[Errore] Lettura file utenti incompleta o corrotta. Dati precedenti mantenuti.\n");
                    free(tempUtenti); 
                }
            }
        }
        fclose(fp);
    }

    // --- CARICAMENTO PRESTITI ---
    fp = fopen("prestiti.dat", "rb");
    if (fp == NULL) {
        printf("[!] File 'prestiti.dat' non trovato. Nessuna modifica ai prestiti.\n");
    } else {
        fread(&tempNum, sizeof(int), 1, fp);
        if (tempNum >= 0) {
            int nuovaCapacita = (tempNum > 5) ? tempNum : 5;
            Prestito *tempPrestiti = (Prestito*)malloc(nuovaCapacita * sizeof(Prestito));

            if (tempPrestiti == NULL) {
                printf("Errore critico di allocazione memoria per i prestiti!\n");
                printf("Dati precedenti mantenuti.\n");
                return -1;
            } else {
                int letti = fread(tempPrestiti, sizeof(Prestito), tempNum, fp);
                if (letti == tempNum) {
                    free(*prestiti);          // Libero il vecchio array
                    *prestiti = tempPrestiti; // Assegno il nuovo array
                    *numPrestiti = tempNum;
                    *capPrestiti = nuovaCapacita;
                    printf("[OK] Caricati %d prestiti.\n", tempNum);
                } else {
                    // Errore lettura, sono mantenuti i dati precedenti
                    printf("[Errore] Lettura file prestiti incompleta o corrotta. Dati precedenti mantenuti.\n");
                    free(tempPrestiti);
                }
            }
        }
        fclose(fp);
    }
    
    printf("Operazione di caricamento completata.\n");
    return 0;
}

// funzione esporta catalogo in formato testo
void esportaCatalogoInFormatoTesto(Libro *libri, int numLibri) {
    if (numLibri == 0) {
        printf("Nessun libro da esportare.\n");
        return;
    }

    FILE *fp = fopen("catalogo.txt", "w");
    if (fp == NULL) {
        printf("Errore: Impossibile creare il file 'catalogo.txt'.\n");
        return;
    }

    fprintf(fp, "=== CATALOGO LIBRI ===\n");
    // Intestazione opzionale (puoi rimuoverla se vuoi solo i dati grezzi)
    // fprintf(fp, "ISBN | Titolo | Autore | Anno | Copie | Genere\n"); 

    for (int i = 0; i < numLibri; i++) {
        fprintf(fp, "ISBN: %s | Titolo: %s | Autore: %s | Anno: %d | Copie: %d | Genere: %s\n",
                libri[i].codice_ISBN,
                libri[i].titolo,
                libri[i].autore,
                libri[i].anno_pubblicazione,
                libri[i].numero_copie,
                libri[i].genere);
    }

    fclose(fp);
    printf("\nCatalogo esportato con successo in 'catalogo.txt'!\n");
}

// funzione esporta report prestiti in formato testo
void esportaReportPrestitiInFormatoTesto(Prestito *prestiti, int numPrestiti, Libro *libri, int numLibri, Utente *utenti, int numUtenti) {
    if (numPrestiti == 0) {
        printf("Nessun prestito da esportare.\n");
        return;
    }

    FILE *fp = fopen("report_prestiti.txt", "w");
    if (fp == NULL) {
        printf("Errore: Impossibile creare il file 'report_prestiti.txt'.\n");
        return;
    }

    fprintf(fp, "=== REPORT PRESTITI ATTIVI ===\n");
    int prestitiAttiviTrovati = 0;

    for (int i = 0; i < numPrestiti; i++) {
        // Filtriamo solo i prestiti NON restituiti (restituito == 0)
        if (prestiti[i].restituito == 0) {
            prestitiAttiviTrovati++;

            // 1. Cerchiamo il Titolo del libro usando l'ISBN
            char titoloLibro[101] = "Titolo non trovato";
            for (int j = 0; j < numLibri; j++) {
                if (strcmp(prestiti[i].codice_ISBN_libro, libri[j].codice_ISBN) == 0) {
                    strcpy(titoloLibro, libri[j].titolo);
                    break;
                }
            }

            // 2. Cerchiamo Nome e Cognome utente usando il codice utente
            char nomeUtente[105] = "Utente sconosciuto"; // Abbastanza grande per nome + spazio + cognome
            for (int k = 0; k < numUtenti; k++) {
                if (prestiti[i].codice_utente == utenti[k].codice_utente) {
                    sprintf(nomeUtente, "%s %s", utenti[k].nome, utenti[k].cognome);
                    break;
                }
            }

            // 3. Scriviamo la riga nel file
            fprintf(fp, "ID Prestito: %d | ISBN: %s | Titolo: %s | ID Utente: %d | Nome: %s | Data Prestito: %s | Restituzione Prevista: %s\n",
                    prestiti[i].codice_prestito,
                    prestiti[i].codice_ISBN_libro,
                    titoloLibro,
                    prestiti[i].codice_utente,
                    nomeUtente,
                    prestiti[i].data_prestito,
                    prestiti[i].data_restituzione_prevista);
        }
    }

    if (prestitiAttiviTrovati == 0) {
        fprintf(fp, "Nessun prestito attivo al momento.\n");
    }

    fclose(fp);
    printf("\nReport esportato con successo in 'report_prestiti.txt' (%d prestiti attivi).\n", prestitiAttiviTrovati);
}

// Funzione chiedi salvataggio in uscita, poi richiama il main che libera la memoria e chiude il database
void chiediSalvataggio(Libro *libri, int numLibri, Utente *utenti, int numUtenti, Prestito *prestiti, int numPrestiti) {
    char risposta;
    
    printf("\n=== CHIUSURA PROGRAMMA ===\n");
    
    do {
        printf("Vuoi salvare le modifiche su file binario prima di uscire? (S/N): ");
        scanf(" %c", &risposta);
        
        risposta = toupper(risposta);

        if (risposta != 'S' && risposta != 'N') {
            printf("Errore: Inserimento non valido. Digita 'S' per salvare o 'N' per uscire senza salvare.\n");
        }

    } while (risposta != 'S' && risposta != 'N');

    if (risposta == 'S') {
        salvaDatabaseSuFileBinario(libri, numLibri, utenti, numUtenti, prestiti, numPrestiti);
    } else {
        printf("Uscita senza salvataggio...\n");
    }
}

// === MENU GESTIONE STATISTICHE E REPORT === //
void menuGestioneStatisticheReport(Libro *database_libri, Utente *database_utenti, Prestito *database_prestiti, int libri_inseriti,int utenti_inseriti, int prestiti_inseriti){
    int scelta;
    do{
        // stampa menu gestione statistiche e report
        printf("=== MENU GESTIONE STATISTICHE E REPORT ===\n");
        printf("  1. Statistiche generali\n");
        printf("  2. Libri per genere\n");
        printf("  3. Top 5 libri più prestati\n");
        printf("  4. Torna al menù principale.\n");
        printf("\nTua scelta: ");
        scanf("%d",&scelta);
        
        switch(scelta)
        {
            case 1:
            statisticheGenerali(database_libri, database_utenti, database_prestiti, libri_inseriti, utenti_inseriti, prestiti_inseriti);  
            break;
            
            case 2:
            libriPerGenere(database_libri, libri_inseriti); 
            break;
            
            case 3:
            top5LibriPiuPrestati(database_libri, database_prestiti, libri_inseriti, prestiti_inseriti);
            break;
            
            case 4:
            break;

            default:
                printf("Errore nell'inserimento della scelta! Deve essere 1, 2, 3 o 4\n");
                printf("Riprova:\n");
                break;
        }

    } while(scelta!=4);
}

// === FUNZIONI GESTIONE STATISTICHE E REPORT === //
// statistiche generali
void statisticheGenerali(Libro *database_libri, Utente *database_utenti, Prestito *database_prestiti, int libri_inseriti,int utenti_inseriti, int prestiti_inseriti){
    int numCopieDisponibili = 0;
    int numPrestitiAttuali = 0;

    for(int i = 0; i < libri_inseriti; i++){
        numCopieDisponibili += database_libri[i].numero_copie;
    }
    
    for(int i = 0; i < prestiti_inseriti; i++){
        if(database_prestiti[i].restituito==0){
            numPrestitiAttuali++;
        }
    }
    
    printf("Numero totale di libri (ISBN unici) nel catalogo: %d \n",libri_inseriti);  // codice ISBN univoco per ogni libro (ma ci possono essere comunque piu copie)
    printf("Numero totale di copie disponibili: %d \n",numCopieDisponibili);
    printf("Numero totale di utenti registrati: %d \n",utenti_inseriti);
    printf("Numero totale di prestiti effettuati: %d\n",prestiti_inseriti);
    printf("Numero di prestiti attualmente attivi: %d \n",numPrestitiAttuali);
    visualizzaLibroPiuPrestato(database_libri, database_prestiti, libri_inseriti, prestiti_inseriti);
}

// funzione calcola libro piu prestato:
//  restituisce 0 se il libro è stato trovato, -1 altrimenti
int calcolaLibroPiuPrestato(Libro *database_libri, Prestito *database_prestiti, int libri_inseriti, int prestiti_inseriti, int *out_indice_libro, int *out_conteggio) {
    // Inizializzo i valori di output a uno stato di "non trovato"
    *out_indice_libro = -1;
    *out_conteggio = 0;

    if (prestiti_inseriti == 0) {
        return -1; // Segnala che non ci sono prestiti da analizzare
    }

    // definisco struct ausiliaria per associare il codice ISBN del libro al conteggio dei prestiti effettuati
    typedef struct {
        char codice_ISBN[18];
        int conteggio;
    } ConteggioISBN;

    // definisco array dinamico di puntatori alla struct ConteggioISBN, per cercare libro piu prestato
    ConteggioISBN *conteggi = (ConteggioISBN*)malloc(libri_inseriti * sizeof(ConteggioISBN));
    if (conteggi == NULL) {
        printf("Errore di allocazione memoria (allocazione dinamica conteggioISBN* conteggi).\n");
        return -1; // Segnala errore
    }
    int numConteggi = 0;

    // logica per il conteggio
    for (int i = 0; i < prestiti_inseriti; i++) {
        int trovato = 0;
        for (int j = 0; j < numConteggi; j++) {
            if (strcmp(database_prestiti[i].codice_ISBN_libro, conteggi[j].codice_ISBN) == 0) {
                conteggi[j].conteggio++;
                trovato = 1;
                break;
            }
        }
        // se non ho trovato il codice isbn fra la struct dei libri prestati, lo aggiungo con conteggio 1
        if (!trovato) {
            strcpy(conteggi[numConteggi].codice_ISBN, database_prestiti[i].codice_ISBN_libro);
            conteggi[numConteggi].conteggio = 1;
            numConteggi++;
        }
    }

    if (numConteggi == 0) {
        free(conteggi);
        return -1; // Nessun libro trovato tra i prestiti
    }

    int maxConteggio = 0;
    char isbnPiuPrestato[18] = "";

    // cerco maxConteggio = numero massimo di prestiti di un certo libro (l'indice lo trovo sotto)
    for (int i = 0; i < numConteggi; i++) {
        if (conteggi[i].conteggio > maxConteggio) {
            maxConteggio = conteggi[i].conteggio;
            strcpy(isbnPiuPrestato, conteggi[i].codice_ISBN);
        }
    }

    // cerco codice isbn del libro con maxCOnteggio (= numero massimo di prestiti)
    int indiceTrovato = -1;
    for (int i = 0; i < libri_inseriti; i++) {
        if (strcmp(isbnPiuPrestato, database_libri[i].codice_ISBN) == 0) {
            indiceTrovato = i;
            break;
        }
    }

    free(conteggi);

    // scrivo le variabili con i puntatori
    if (indiceTrovato != -1) {
        *out_indice_libro = indiceTrovato;
        *out_conteggio = maxConteggio;
        return 0; // Successo!
    }

    return -1; // Errore: libro non trovato nel database principale
}



 // funzione per stampare il libro più prestato
void visualizzaLibroPiuPrestato(Libro *database_libri, Prestito *database_prestiti, int libri_inseriti, int prestiti_inseriti) {
    // Dichiaro le variabili che conterranno i risultati(posizione del libro piu prestato, numero di prestiti effettuato)
    int indice_risultato;
    int conteggio_risultato;

    if (calcolaLibroPiuPrestato(database_libri, database_prestiti, libri_inseriti, prestiti_inseriti, &indice_risultato, &conteggio_risultato) == 0) { 
        // Se la funzione ha avuto successo
        
        // Controllo grammaticale: singolare vs plurale
        if (conteggio_risultato == 1) {
            printf("Il libro più prestato in assoluto è:\t'%s' (prestato 1 volta)\n", database_libri[indice_risultato].titolo);
        } else {
            printf("Il libro più prestato in assoluto è:\t'%s' (prestato %d volte)\n", database_libri[indice_risultato].titolo, conteggio_risultato);
        }

    } else { 
        // Se la funzione non ha trovato un libro
        printf("Nessun prestito registrato o libro trovato.\n");
    }
}


// funzione che visualizza il conteggio dei libri suddiviso per genere
void libriPerGenere(Libro* database_libri, int libri_inseriti){
    // Controllo preliminare
    if (libri_inseriti == 0) {
        printf("Nessun libro presente nel catalogo.\n");
        return;
    }

    // Definisco una struttura ausiliaria per associare un genere al suo conteggio(quello che verrà stampato).
    typedef struct {
        char genere[31]; // La dimensione deve corrispondere a quella nella struct Libro
        int conteggio;
    } ConteggioGenere;

    // Alloco memoria per un array che conterrà i conteggi.
    // Nel caso peggiore, ogni libro ha un genere diverso(quindi la dimensione è libri_inseriti * sizeof(ConteggioGenere)).
    ConteggioGenere *conteggi = (ConteggioGenere*)malloc(libri_inseriti * sizeof(ConteggioGenere));
    if (conteggi == NULL) {
        printf("Errore critico: impossibile allocare memoria per le statistiche dei generi.\n");
        return;
    }
    
    int generiUnici = 0; // Contatore per il numero di generi unici trovati finora.

    // Ciclo principale per scorrere tutti i libri e popolare la lista di conteggi.
    for (int i = 0; i < libri_inseriti; i++) {
        int trovato = 0;
        // Cerco se il genere del libro corrente è già stato registrato.
        for (int j = 0; j < generiUnici; j++) {
            if (strcmp(database_libri[i].genere, conteggi[j].genere) == 0) {
                // Se lo trovo, incremento il suo conteggio ed esco dal ciclo interno.
                conteggi[j].conteggio++;
                trovato = 1;
                break;
            }
        }

        if (!trovato) {     // Se, dopo aver controllato tutti i generi unici, non l'ho trovato
            // lo aggiungo come unico genere nella lista
            strcpy(conteggi[generiUnici].genere, database_libri[i].genere);
            conteggi[generiUnici].conteggio = 1; // ha conteggio 1 perche è il primo trovato con questo genere
            generiUnici++; // Incremento il numero di generi unici che stiamo tracciando.
        }
    }

    // Con tutti i conteggi, stampiamo i risultati
    printf("\n Conteggio libri per genere: \n \n");
    for (int i = 0; i < generiUnici; i++) {
        // Controllo grammaticale: singolare vs plurale
        if (conteggi[i].conteggio == 1) {
            printf("%s: 1 libro\n", conteggi[i].genere);
        } else {
            printf("%s: %d libri\n", conteggi[i].genere, conteggi[i].conteggio);
        }
    }

    // Libero la memoria dinamica che avevo allocato prima
    free(conteggi);
}


// Funzione visualizza i 5 libri con il maggior numero di prestiti (LOGICA OTTIMIZZATA)
void top5LibriPiuPrestati(Libro *database_libri, Prestito *database_prestiti, int libri_inseriti, int prestiti_inseriti) {
    // Controllo preliminare
    if (prestiti_inseriti == 0 || libri_inseriti == 0) {
        printf("Nessun prestito o libro registrato.\n");
        return;
    }

    // Creiamo una struttura temporanea per associare l'indice del libro al suo conteggio
    typedef struct {
        int indice_originale; // Indice del libro nell'array database_libri
        int conteggio;        // Quante volte è stato prestato
    } StatisticaLibro;

    // Alloco l'array di statistiche (un elemento per ogni libro esistente)
    StatisticaLibro *stats = (StatisticaLibro*)malloc(libri_inseriti * sizeof(StatisticaLibro));
    if (stats == NULL) {
        printf("Errore critico di allocazione memoria per le statistiche.\n");
        return;
    }

    // Inizializzo l'array
    for (int i = 0; i < libri_inseriti; i++) {
        stats[i].indice_originale = i;
        stats[i].conteggio = 0;
    }

    // Conto i prestiti (Scorro i prestiti e incremento il contatore del libro corrispondente)
    for (int i = 0; i < prestiti_inseriti; i++) {
        // Per ogni prestito, cerco a quale libro corrisponde l'ISBN
        for (int j = 0; j < libri_inseriti; j++) {
            if (strcmp(database_prestiti[i].codice_ISBN_libro, database_libri[j].codice_ISBN) == 0) {
                stats[j].conteggio++;
                break; // Libro trovato, passo al prossimo prestito
            }
        }
    }

    // Bubble Sort Decrescente basato sul campo 'conteggio'
    // Ordiniamo l'array 'stats' portando in alto i libri con più prestiti
    for (int i = 0; i < libri_inseriti - 1; i++) {
        for (int j = 0; j < libri_inseriti - i - 1; j++) {
            if (stats[j].conteggio < stats[j+1].conteggio) {
                // Scambio
                StatisticaLibro temp = stats[j];
                stats[j] = stats[j+1];
                stats[j+1] = temp;
            }
        }
    }

    // Stampa dei Top 5 (o meno se non ci sono abbastanza libri prestati)
    printf("\n=== TOP 5 LIBRI PIU' PRESTATI ===\n\n");
    
    int libri_stampati = 0;
    int max_da_stampare = (libri_inseriti < 5) ? libri_inseriti : 5; // Se ho meno di 5 libri, stampo quelli che ho

    for (int i = 0; i < max_da_stampare; i++) {
        // Stampiamo solo se il libro ha effettivamente dei prestiti
        if (stats[i].conteggio > 0) {
            // Recupero i dati reali dal database_libri usando l'indice originale salvato
            Libro *libroCorr = &database_libri[stats[i].indice_originale];
            
            printf("%d. Titolo: %s (prestato %d %s)\n", 
                   i + 1, 
                   libroCorr->titolo, 
                   stats[i].conteggio, 
                   (stats[i].conteggio == 1) ? "volta" : "volte"); // Controllo plurale/singolare
            
            printf("   Autore: %s\n", libroCorr->autore);
            printf("   ISBN:   %s\n", libroCorr->codice_ISBN);
            printf("   Genere: %s\n\n", libroCorr->genere);
            
            libri_stampati++;
        }
    }

    if (libri_stampati == 0) {
        printf("Nessun libro è stato ancora prestato.\n");
    }

    //Pulizia memoria
    free(stats);
}


// === MENU GESTIONE UTENTI ===
Utente* menuGestioneUtenti(Utente* database_utenti, int* utenti_inseriti, int* capacita_attuale_utenti){
    int scelta;
    do { 
        // Stampa menù gestione utenti
        printf("\n=== MENU GESTIONE UTENTI ===\n");
        printf("  1. Inserisci nuovo utente\n");
        printf("  2. Visualizza tutti gli utenti;\n");
        printf("  3. Cerca utente per codice\n");
        printf("  4. Torna al menù principale\n");
        printf("\nTua scelta: ");
        scanf("%d",&scelta);

        // Switch menù:
        if (*utenti_inseriti!=0 || scelta == 1 || scelta==4) {
            switch (scelta)
            {
            case 1:
                Utente* temp;
                temp = inserisci_nuovo_utente(database_utenti,utenti_inseriti,capacita_attuale_utenti);
                if (temp == NULL) {
                    printf("Errore di allocazione in memoria (riallocazione dinamica del database utenti)! Verrai reindirizzato al menù gestione utenti\n");
                } else {
                    database_utenti = temp;
                }
                break;
        
            case 2:
                visualizza_tutti_gli_utenti(database_utenti,*utenti_inseriti);
                break;

            case 3:
                cerca_utente_per_codice(database_utenti,*utenti_inseriti);
                break;

            case 4:
                break;

            default:
                printf("Errore nell'inserimento della scelta! Deve essere 1, 2, 3 o 4\n");
                printf("Riprova:\n");
                break;
            }
        } else {
            printf("Non ci sono utenti inseriti, dunque non è possibile fare alcuna azione diversa dalla 1! Riprova:\n");
        }
    } while (scelta != 4);
    return database_utenti;
}

/*
    == INSERIMENTO UTENTI ==
*/

Utente* inserisci_nuovo_utente(Utente *database_utenti, int *utenti_inseriti, int *capacita_utenti_attuale) {
// Assegnare a questa funzione una variabile Utente temporanea su cui caricare la riallocazione dinamica del database utenti.

    // Riallocazione dinamica
    if (*utenti_inseriti == *capacita_utenti_attuale) {
        database_utenti = realloc(database_utenti,sizeof(Utente)*2*(*capacita_utenti_attuale));
        if (database_utenti == NULL) { // Per risparmiare tempo, in caso di errore di allocazione esco subito dalla funzione
            return NULL;
        }
        *capacita_utenti_attuale = 2* *capacita_utenti_attuale;
    }
    
    // Inserimento dati del nuovo utente
    int exit_flag;
    exit_flag=inserimento_dati_utenti(database_utenti,utenti_inseriti);
    if (exit_flag == 0) {
        printf("\nUtente inserito correttamente!\n\n");
    }
    return database_utenti;
}

// funzione inserimento dati utente
int inserimento_dati_utenti(Utente* database_utenti,int* utenti_inseriti) {    

    // Inserimento codice utente
    int exit_flag;
    exit_flag = inserimento_codice_utente(database_utenti,utenti_inseriti);
    if (exit_flag == 1) { // Controllo uscita da inserimento dati
        return 1;
    }

    // Inserimento nome e cognome
    printf("  - Nome: ");
    scanf(" %50[^\n]",database_utenti[*(utenti_inseriti)].nome);
    printf("  - Cognome: ");
    scanf(" %50[^\n]",database_utenti[*(utenti_inseriti)].cognome);

    // Inserimento data
    inserimento_data_iscrizione(database_utenti,utenti_inseriti);

    // Inserimento e-mail
    inserimento_email(database_utenti,utenti_inseriti);
    
    (*utenti_inseriti)++;
    return 0; 
}

int inserimento_codice_utente(Utente* database_utenti, int* utenti_inseriti) {
    int flag_codice_utente;
    int temp;

    do { // Questo ciclo ricomincia se il codice non è univoco
        printf("Inserisci i dati dell'utente: \n");
        printf("  - Codice utente: ");
        do {
            scanf("%d",&temp);
            if(temp<=0) {
            printf("Il codice utente deve essere positivo! Riprova: ");
            }
        } while (temp<=0);
        int i=0;
        do { // Controllo del codice univoco
            flag_codice_utente=0;
            if (temp == database_utenti[i].codice_utente) {
                flag_codice_utente++;
                int scelta=0; // Se il codice è già esistente faccio scegliere all'utente se fare un altro inserimento o uscire dall'inserimento utenti.
                printf("\nIl codice utente inserito è già esistente!\n");
                printf("\nCosa vuoi fare?\n");
                printf("1. Inserire un altro utente;\n");
                printf("2. Uscire dall'inserimento utenti.\n");
                do { // Controllo inserimento scelta corretto
                    printf("\nLa tua scelta: \n");
                    scanf("%d",&scelta);
                    switch (scelta)
                    {
                    case 1:
                        break;
                    
                    case 2:
                        return 1;
                        break;

                    default:
                        printf("Devi inserire un numero tra 1 e 2!");
                        printf("Riprova:\n");
                        break; 
                    } 
                } while (scelta!=1);
            }
            i++;
        } while (flag_codice_utente == 0 && i < *(utenti_inseriti));
        i=0;
    } while (flag_codice_utente != 0);

    database_utenti[*(utenti_inseriti)].codice_utente = temp;
    return 0;
}

// funzione inserimento data di iscrizione
void inserimento_data_iscrizione(Utente* database_utenti, int* utenti_inseriti) {
    char data[11];
    
    do { // Controllo inserimento corretto
        printf("  - Data di iscrizione: ");
        scanf("%10s",data);

        // Avvertimento per inserimento errato
        if (invalida_data(data)) {
            printf("Il formato della data deve essere gg/mm/aaaa!\n");
            printf("Riprova:\n");
        }
    } while (invalida_data(data));

    // Copia nel database
    strcpy(database_utenti[*(utenti_inseriti)].data_iscrizione,data);
}

void inserimento_email(Utente* database_utenti,int* utenti_inseriti) {
    char email[81];
    
    do { // Controllo inserimento corretto
        printf("  - Email: ");
        scanf("%s",email);

        // Avvertimento per inserimento errato
        if (strchr(email,'@') == NULL) {
        printf("E' obbligatorio inserire una chiocciola (@)!\n");
        printf("Riprova:\n");
        }   

    } while (strchr(email,'@') == NULL);
    
    // Copia nel database
    strcpy(database_utenti[*(utenti_inseriti)].email,email);
}


/*
  == VISUALIZZAZIONE UTENTI ==
*/

void visualizza_tutti_gli_utenti(Utente* database_utenti,int utenti_inseriti) {
    
    int scelta = 0;
    
    do {
        // Stampa Menù visualizzazione utenti
        printf("== MENÙ VISUALIZZAZIONE UTENTI ==\n");
        printf("  1. Ordine - alfabetico (nomi - cognomi);\n");
        printf("  2. Ordine - alfabetico (cognomi - nomi);\n");
        printf("  3. Ordine - alfanumerico (email);\n");
        printf("  4. Ordine - numerico (codice utente);\n");
        printf("  5. Ordine - temporale (iscrizione);\n");
        printf("  6. Torna al menù gestione utenti.\n");    
        printf("\nLa tua scelta: ");
        scanf("%d", &scelta);

        // Switch menù
        switch (scelta)
        {
        case 1:
            stampa_ordine_alfabetico_nomi(database_utenti,utenti_inseriti);
            break;

        case 2:
            stampa_ordine_alfabetico_cognomi(database_utenti,utenti_inseriti);
            break;

        case 3:
            stampa_ordine_email(database_utenti,utenti_inseriti);
            break;

        case 4:
            stampa_ordine_codice_utente(database_utenti,utenti_inseriti);
            break;
    
        case 5:
            stampa_ordine_data_iscrizione(database_utenti,utenti_inseriti);
            break;
    
        case 6:
            break;

        default:
            printf("La tua scelta deve essere un numero tra 1 e 6 (compresi)! Riprova:\n");
            break;
        }

    } while (scelta != 6);
}


int stampa_ordine_alfabetico_nomi(Utente* database_utenti,int utenti_inseriti) {
    
    // Inizializzazione vettore degli indici
    int* indici_ordinati = malloc(utenti_inseriti*sizeof(int));
    if (indici_ordinati==NULL) {
        return 1;
    }
    for (int i=0;i<utenti_inseriti;i++) {
        indici_ordinati[i]=i;
    }

    // Creazione stringhe nome - cognome in lettere minuscole
    char (*nomi_cognomi)[102]=malloc(utenti_inseriti*sizeof(*nomi_cognomi));
    if (nomi_cognomi==NULL) {
        free(indici_ordinati);
        return 1;
    }
    for (int i=0;i<utenti_inseriti;i++) {
        strcpy(nomi_cognomi[i],database_utenti[i].nome);
        strcat(nomi_cognomi[i]," ");
        strcat(nomi_cognomi[i],database_utenti[i].cognome);
        for (int j=0;j<strlen(nomi_cognomi[i]);j++) {
            nomi_cognomi[i][j] = (char) tolower((unsigned char) nomi_cognomi[i][j]);
        }
    }

    // Ordinamento vettore degli indici
    for (int i=0;i<utenti_inseriti-1;i++) {
        for (int j=utenti_inseriti-1;j>i;j--) {
            if (strcmp(nomi_cognomi[indici_ordinati[i]],nomi_cognomi[indici_ordinati[j]])>0) {
                int temp;
                temp = indici_ordinati[i];
                indici_ordinati[i] = indici_ordinati[j];
                indici_ordinati[j] = temp;
            }
        }
    }

    // Stampa utenti
    stampa_dati_utenti(database_utenti,utenti_inseriti,indici_ordinati);

    // libero vettori indici dinamici
    free(indici_ordinati);
    free(nomi_cognomi);
    return 0;
}

int stampa_ordine_alfabetico_cognomi(Utente* database_utenti,int utenti_inseriti) {
    
    // Inizializzazione vettore degli indici
    int* indici_ordinati = malloc(utenti_inseriti*sizeof(int));
    if (indici_ordinati == NULL) {
        return 1;
    }
    for (int i=0;i<utenti_inseriti;i++) {
        indici_ordinati[i]=i;
    }

    // Creazione stringhe nome - cognome in lettere minuscole
    char (*cognomi_nomi)[102]=malloc(utenti_inseriti*sizeof(*cognomi_nomi));
    if (cognomi_nomi==NULL) {
        free(indici_ordinati);
        return 1;
    }
    for (int i=0;i<utenti_inseriti;i++) {
        strcpy(cognomi_nomi[i],database_utenti[i].cognome);
        strcat(cognomi_nomi[i]," ");
        strcat(cognomi_nomi[i],database_utenti[i].nome);
        int lunghezza=strlen(cognomi_nomi[i]);
        for (int j=0;j<lunghezza;j++) {
            cognomi_nomi[i][j] = (char) tolower((unsigned char)cognomi_nomi[i][j]);
        }
    }

    // Ordinamento vettore degli indici
    for (int i=0;i<utenti_inseriti-1;i++) {
        for (int j=utenti_inseriti-1;j>i;j--) {
            if (strcmp(cognomi_nomi[indici_ordinati[i]],cognomi_nomi[indici_ordinati[j]])>0) {
                int temp;
                temp = indici_ordinati[i];
                indici_ordinati[i] = indici_ordinati[j];
                indici_ordinati[j] = temp;
            }
        }
    }

    // Stampa utenti
    stampa_dati_utenti(database_utenti,utenti_inseriti,indici_ordinati);

    free(indici_ordinati);
    free(cognomi_nomi);
    return 0;
}

int stampa_ordine_email(Utente* database_utenti,int utenti_inseriti) {
    
    // Inizializzazione vettore degli indici
    int* indici_ordinati = malloc(utenti_inseriti*sizeof(int));
    if (indici_ordinati==NULL) {
        return 1;
    }
    for (int i=0;i<utenti_inseriti;i++) {
        indici_ordinati[i]=i;
    }
    
    // Ordinamento vettore degli indici
    for (int i=0;i<utenti_inseriti-1;i++) {
        for (int j=utenti_inseriti-1;j>i;j--) {
            if (strcmp(database_utenti[indici_ordinati[i]].email,database_utenti[indici_ordinati[j]].email)>0) {
                int temp;
                temp = indici_ordinati[i];
                indici_ordinati[i] = indici_ordinati[j];
                indici_ordinati[j] = temp;
            }
        }
    }
    
    // Stampa utenti
    stampa_dati_utenti(database_utenti,utenti_inseriti,indici_ordinati);

    free(indici_ordinati);
    return 0;
}

int stampa_ordine_codice_utente(Utente* database_utenti,int utenti_inseriti) {
    
    // Inizializzazione vettore degli indici
    int* indici_ordinati = malloc(utenti_inseriti*sizeof(int));
    if (indici_ordinati==NULL) {
        return 1;
    }
    for (int i=0;i<utenti_inseriti;i++) {
        indici_ordinati[i]=i;
    }
    
    // Ordinamento vettore degli indici
    for (int i=0;i<utenti_inseriti-1;i++) {
        for (int j=utenti_inseriti-1;j>i;j--) {
            if (database_utenti[indici_ordinati[i]].codice_utente > database_utenti[indici_ordinati[j]].codice_utente) {
                int temp;
                temp = indici_ordinati[i];
                indici_ordinati[i] = indici_ordinati[j];
                indici_ordinati[j] = temp;
            }
        }
    }
    
    // Stampa dati utenti
    stampa_dati_utenti(database_utenti,utenti_inseriti,indici_ordinati);

    // libero vettori indici dinamici
    free(indici_ordinati);
    return 0;
}

int stampa_ordine_data_iscrizione(Utente* database_utenti,int utenti_inseriti) {
    
    // Inizializzazione vettore degli indici
    int* indici_ordinati = malloc(utenti_inseriti*sizeof(int));
    if (indici_ordinati==NULL) {
        return 1;
    }
    for (int i=0;i<utenti_inseriti;i++) {
        indici_ordinati[i]=i;
    }

    // Dichiarazione anno,mese,giorno
    int* giorno=malloc(utenti_inseriti*sizeof(int));
    if (giorno == NULL) {
        free(indici_ordinati);
        return 1;
    }
    int* anno=malloc(utenti_inseriti*sizeof(int));
    if (anno == NULL) {
        free(indici_ordinati);
        free(giorno);
        return 1;
    }
    int* mese=malloc(utenti_inseriti*sizeof(int));
    if (mese == NULL) {
        free(indici_ordinati);
        free(giorno);
        free(anno);
        return 1;
    }

    // Calcolo anno
    for (int i=0;i<utenti_inseriti;i++) {
        char temp[5];
        for (int j=0;j<4;j++) {
            temp[j] = database_utenti[i].data_iscrizione[6+j];
        }
        anno[i]=(temp[0]-'0')*1000;
        anno[i]+=(temp[1]-'0')*100;
        anno[i]+=(temp[2]-'0')*10;
        anno[i]+=(temp[3]-'0');
    }
    
    // Calcolo mese
    for (int i=0;i<utenti_inseriti;i++) {
        char temp[3];
        for (int j=0;j<2;j++) {
            temp[j] = database_utenti[i].data_iscrizione[3+j];
        }
        mese[i]=(temp[0]-'0')*10;
        mese[i]+=(temp[1]-'0');
    }

    // Calcolo giorno
    for (int i=0;i<utenti_inseriti;i++) {
        char temp[3];
        for (int j=0;j<2;j++) {
            temp[j] = database_utenti[i].data_iscrizione[j];
        }
        giorno[i]=(temp[0]-'0')*10;
        giorno[i]+=(temp[1]-'0');
    }

    int* valore_data=malloc(utenti_inseriti*sizeof(int));
    if (valore_data==NULL) {
        free(indici_ordinati);
        free(giorno);
        free(mese);
        free(anno);
        return 1;
    }
    for (int i=0;i<utenti_inseriti;i++) {
        valore_data[i]=anno[i]*10000 + mese[i]*100 + giorno[i]; 
    }
    
    // Ordinamento vettore degli indici
    for (int i=0;i<utenti_inseriti-1;i++) {
        for (int j=utenti_inseriti-1;j>i;j--) {
            if (valore_data[i]>valore_data[j]) {
                int temp;
                temp = indici_ordinati[i];
                indici_ordinati[i] = indici_ordinati[j];
                indici_ordinati[j] = temp;
            }
        }
    }
    
    // Stampa dati utenti
    stampa_dati_utenti(database_utenti,utenti_inseriti,indici_ordinati);

    // Liberazione memoria
    free(indici_ordinati);
    free(giorno);
    free(mese);
    free(anno);
    free(valore_data);
    return 0;
}

void stampa_dati_utenti(Utente* database_utenti, int utenti_inseriti, int* indici_ordinati) {
    for (int i=0;i<utenti_inseriti;i++) {
        printf("\nUtente %d:\n",i+1);
        printf("  Nome: %s\n",database_utenti[indici_ordinati[i]].nome);
        printf("  Cognome: %s\n",database_utenti[indici_ordinati[i]].cognome);
        printf("  Email: %s\n",database_utenti[indici_ordinati[i]].email);
        printf("  Codice utente: %d\n",database_utenti[indici_ordinati[i]].codice_utente);
        printf("  Data di iscrizione: %s\n",database_utenti[indici_ordinati[i]].data_iscrizione);
    }
}

/*
   == RICERCA UTENTI TRAMITE CODICE UTENTE == 
*/

void cerca_utente_per_codice(Utente* database_utenti,int utenti_inseriti) {

    int src_flag=-1;
    do {
        
        // Inserimento codice utente
        int codice_inserito;
        printf("Inserisci il codice utente: ");
        scanf("%d",&codice_inserito);

        // Ricerca codice utente
        for (int i=0;i<utenti_inseriti;i++) {
            if (database_utenti[i].codice_utente == codice_inserito) {
                src_flag=i;
                break;
            }
        }

        // Stampa dati utente	
        if (src_flag==-1) { // Se l'utente non è stato trovato, è possibile inserirne un altro oppure tornare alla gestione utenti
            int scelta;
            printf("\nNon è stato trovato alcun utente con il codice inserito!\n");
            printf("Cosa vuoi fare?\n");
            printf("\n  1. Inserire un altro codice utente;\n");
            printf("  2. Tornare al menù gestione utenti.\n");
            printf("\nLa tua scelta: ");
            do { // Ciclo per la scelta dell'utente
                
                // Inserimento scelta
                scanf("%d",&scelta);
                
                // Switch scelta utente
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
            } while (scelta != 1);
        } else { // Se l'utente viene trovato, vengono stampati i suoi dati.
            printf("Utente trovato!\n");
            printf("  Nome: %s\n",database_utenti[src_flag].nome);
            printf("  Cognome: %s\n",database_utenti[src_flag].cognome);
            printf("  Email: %s\n",database_utenti[src_flag].email);
            printf("  Codice utente: %d\n",database_utenti[src_flag].codice_utente);
            printf("  Data di iscrizione: %s\n",database_utenti[src_flag].data_iscrizione);
            printf("\nVerrai, ora, indirizzato al menù gestione utenti.\n");
        }
    } while (src_flag == -1);

}

// === MENU GESTIONE PRESTITI === //
Prestito* menuGestionePrestiti(Utente* database_utenti,Libro* database_libri, Prestito* database_prestiti,int* utenti_inseriti, int* libri_inseriti,int* prestiti_inseriti,int* capacita_attuale_prestiti){
    int scelta;
    do {        
        // Stampa Menù
        printf("\n== MENU' GESTIONE PRESTITI ==\n");
        printf("  1. Registra un nuovo prestito;\n");
        printf("  2. Registra la restituzione di un libro;\n");
        printf("  3. Visualizza tutti i prestiti attivi;\n");
        printf("  4. Visualizza lo storico dei prestiti di un utente;\n");
        printf("  5. Torna al menù principale.\n");
        printf("\nLa tua scelta: ");
        scanf("%d",&scelta);
        
        if (*prestiti_inseriti!=0 || scelta == 1) {
            switch (scelta)
            {
            case 1:
                Prestito* temp;
                temp = registra_prestito(database_libri,database_utenti,database_prestiti,prestiti_inseriti,capacita_attuale_prestiti,*libri_inseriti,*utenti_inseriti);
                if (temp == NULL) { // Controllo che l'eventuale riallocazione sia avvenuta con successo
                    printf("\nErrore di allocazione in memoria (riallocazione dinamica del database prestiti)! Verrai reindirizzato al menù gestione prestiti\n");
                } else {
                    database_prestiti = temp; // Se è avvenuta con successo, aggiorno tale puntatore.
                }
                break;
            
            case 2:
                registra_restituzione(database_prestiti,database_libri,*prestiti_inseriti,*libri_inseriti);
                break;
            
            case 3:
                visualizza_prestiti_attivi(database_utenti,database_prestiti,database_libri,*libri_inseriti,*prestiti_inseriti,*utenti_inseriti);
                break;
            
            case 4:
                visualizza_storico_prestiti_utente(database_utenti,database_prestiti,*utenti_inseriti,*prestiti_inseriti);
                break;
            
            case 5:
                break;
            
            default:
                printf("La scelta deve essere un numero tra 1 e 5 (compresi)! Riprova:\n");
                break;
            }
        } else {
            printf("Non sono presenti prestiti. Per questo motivo le uniche scelte ammesse sono 1 e 5. Riprova:\n");
        }
    } while (scelta != 5);
    return database_prestiti;
}

// Funzione registra prestito
Prestito* registra_prestito(Libro* database_libri,Utente* database_utenti,Prestito* database_prestiti,int* prestiti_inseriti,int* capacita_attuale_prestiti,int libri_inseriti,int utenti_inseriti) {

    // Richiesta libro e utente + controllo
    int flag_inserimento;
    int posizione_libro=-1;
    int posizione_utente=-1;
    richiedi_libro_utente(database_libri,database_utenti,&utenti_inseriti,libri_inseriti,&posizione_utente,&posizione_libro);
    if (posizione_utente == -1 || posizione_libro == -1) {     // Se una delle due posizioni risulta ancora -1, allora c'è stato un errore nella richiesta del libro oppure  
                                                                // una richiesta di uscita dall'inserimento prestiti (tutti sono opportunamente segnalati nelle varie funzioni)
        return database_prestiti;
    }

    // Riallocazione dinamica database_prestiti
    if (*capacita_attuale_prestiti==*prestiti_inseriti) {
        database_prestiti = realloc(database_prestiti,2* *capacita_attuale_prestiti*sizeof(Prestito));
        if (database_prestiti == NULL) {
            return NULL;
        }
        *capacita_attuale_prestiti = 2 * *capacita_attuale_prestiti;
    }
    
    // Inserimento codice ISBN e codice utente
    strcpy(database_prestiti[*prestiti_inseriti].codice_ISBN_libro,database_libri[posizione_libro].codice_ISBN);
    database_prestiti[*prestiti_inseriti].codice_utente = database_utenti[posizione_utente].codice_utente;

    // Diminuzione numero di copie
    database_libri[posizione_libro].numero_copie--;

    // Inserimento data_prestito
    char data[11];
    do {
        printf("\nInserisci la data del prestito: ");
        scanf("%10s",data);
        if (invalida_data(data)) {
            printf("Formato non valido! Formato corretto: gg/mm/aaaa. Riprova: \n");
        }
    } while(invalida_data(data));
    printf("\nPrestito inserito correttamente!\n");
    strcpy(database_prestiti[*prestiti_inseriti].data_prestito,data);

    // Calcolo data_restituzione_prevista
    calcola_30_giorni_dopo(data);
    strcpy(database_prestiti[*prestiti_inseriti].data_restituzione_prevista,data);

    // Restituito = 0
    database_prestiti[*prestiti_inseriti].restituito=0;

    // Generazione codice prestito
    database_prestiti[*prestiti_inseriti].codice_prestito=(*prestiti_inseriti)+1;
    (*prestiti_inseriti)++;

    return database_prestiti;
}

void richiedi_libro_utente(Libro* database_libri,Utente* database_utenti,int* utenti_inseriti,int libri_inseriti,int*posizione_utente,int* posizione_libro) {

    char ISBN[18];
    int codice=0;
    int exit_flag_ISBN;
    int exit_flag_codice_utente;
    
    // Richiesta codice ISBN
    exit_flag_ISBN=richiesta_codice_ISBN(database_libri,libri_inseriti,ISBN,posizione_libro);
    if (exit_flag_ISBN==-1) { // Se c'è errore nella richiesta del codice ISBN, posso (anzi devo) evitare di controllare il codice utente
        return;
    }

    // Richiesta codice utente
    richiesta_codice_utente(database_utenti,*utenti_inseriti,&codice,posizione_utente);
    return;
}


int invalida_ISBN(char ISBN[18]) {  // ritorna 1 se non è valido, 0 altrimenti
    if (strlen(ISBN)!=17) {
        return 1;
    }
    return  ISBN[0] < '0' || ISBN[0] > '9' ||
            ISBN[1] < '0' || ISBN[1] > '9' ||
            ISBN[2] < '0' || ISBN[2] > '9' ||
            ISBN[4] < '0' || ISBN[4] > '9' ||
            ISBN[6] < '0' || ISBN[6] > '9' ||
            ISBN[7] < '0' || ISBN[7] > '9' ||
            ISBN[8] < '0' || ISBN[8] > '9' ||
            ISBN[9] < '0' || ISBN[9] > '9' ||
            ISBN[11] < '0' || ISBN[11] > '9' ||
            ISBN[12] < '0' || ISBN[12] > '9' ||
            ISBN[13] < '0' || ISBN[13] > '9' ||
            ISBN[14] < '0' || ISBN[14] > '9' ||
            ISBN[16] < '0' || ISBN[16] > '9' ||
            ISBN[3] != '-' || ISBN[5] != '-' ||
            ISBN[10] != '-' || ISBN[15] != '-';
}


int invalida_data(char data[11]) {
    if (strlen(data)!=10) {
        return 1;
    }
    return  data[0] < '0' || data[0] > '9' ||
            data[1] < '0' || data[1] > '9' ||
            data[3] < '0' || data[3] > '9' ||
            data[4] < '0' || data[4] > '9' ||
            data[6] < '0' || data[6] > '9' ||
            data[7] < '0' || data[7] > '9' ||
            data[8] < '0' || data[8] > '9' ||
            data[9] < '0' || data[9] > '9' ||
            data[2] != '/' || data[5] != '/';
}


int menu_codice_ISBN_non_valido() {
    int scelta=0;
    printf("\nCosa vuoi fare ora?\n");
    printf("\n  1. Inserire un nuovo codice ISBN per il libro\n");
    printf("  2. Tornare al menù di gestione dei prestiti.\n");
    do {
        scanf("%d",&scelta);
        switch (scelta)
        {
        case 1:
            return 0;
        
        case 2:
            return -1;

        default:
            printf("\nLa scelta deve essere 1 oppure 2! Riprova: ");
            break;
        }
    } while(1);
}


void controlla_esistenza_libro(Libro* database_libri,int libri_inseriti,char ISBN[],int* posizione_libro) {
    for (int i=0;i<libri_inseriti;i++) {
        if (strcmp(ISBN,database_libri[i].codice_ISBN)==0) {
            printf("\nLibro trovato correttamente!\n");
            *posizione_libro=i;
            return;
        } 
    }
    printf("Non è stato trovato alcun libro con tale codice!");
    *posizione_libro=-1;
    return;
}


int richiesta_codice_ISBN(Libro* database_libri,int libri_inseriti,char ISBN[],int* posizione_libro) {
    do {
        printf("\nInserisci il codice ISBN del libro (XXX-X-XXXX-XXXX-X): ");
        scanf("%17s",ISBN);

        // Controllo inserimento ISBN
        if (invalida_ISBN(ISBN)) {
            printf("\nIl codice ISBN è stato inserito con formato errato! Formato corretto: XXX-X-XXXX-XXXX-X.\n");
        } else {
            // Calcolo posizione libro
            controlla_esistenza_libro(database_libri,libri_inseriti,ISBN,posizione_libro);
            if (*posizione_libro!=-1 && database_libri[*posizione_libro].numero_copie==0) { // Controllo che ci siano copie del libro
                printf("Copie del libro non disponibili!");
                *posizione_libro=-1; // Piuttosto che inventare una nuova variabile, faccio valere posizione_libro = -1 (come se il libro non fosse nel catalogo).
                                    // Ciò non dà problemi perché gli unici messaggi relativi a posizione_libro provengono da "controlla_esistenza_libro"
            }   
        }
        
        // Controllo se l'utente vuole ancora inserire un prestito
        if (invalida_ISBN(ISBN) || *posizione_libro == -1) {
            int exit_flag;
            exit_flag=menu_codice_ISBN_non_valido();
            if (exit_flag == -1) {
                return -1;
            }
        }
    
    } while (invalida_ISBN(ISBN) || *posizione_libro == -1);
    return 0;
}

void richiesta_codice_utente(Utente* database_utenti, int utenti_inseriti, int* codice, int* posizione_utente) {
    do {
        printf("\nInserisci il codice utente: ");
        scanf("%d",codice);

        // Controllo inserimento codice utente
        if (*codice<=0) {
            printf("\nIl codice utente deve essere positivo!\n");
        } else {
            // Calcolo posizione utente
            controlla_esistenza_utente(database_utenti,utenti_inseriti,*codice,posizione_utente);
        }

        // Controllo se l'utente vuole ancora inserire un prestito
        if (*codice<=0 || *posizione_utente == -1) {
            int exit_flag;
            exit_flag = menu_codice_utente_non_valido();
            if (exit_flag == -1) {
                return;
            }
        }

    } while (*posizione_utente == -1 || *codice <= 0);
}


void controlla_esistenza_utente(Utente* database_utenti,int utenti_inseriti,int codice,int* posizione_utente) {
    for (int i=0;i<utenti_inseriti;i++) {
        if (codice == database_utenti[i].codice_utente) {
            printf("\nUtente trovato correttamente!\n");
            *posizione_utente=i;
            return;
        } 
    }
    printf("Non è stato trovato alcun utente con tale codice!");
    *posizione_utente=-1;
}


int menu_codice_utente_non_valido() {
    int scelta=0;
    printf("\nCosa vuoi fare ora?\n");
    printf("\n  1. Inserire un nuovo codice utente\n");
    printf("  2. Tornare al menù di gestione dei prestiti.\n");
    printf("\nLa tua scelta: ");
    do {
        scanf("%d",&scelta);
        switch (scelta)
        {
        case 1:
            return 0;
        
        case 2:
            return -1;

        default:
            printf("\nLa scelta deve essere 1 oppure 2! Riprova: ");
            break;
        }
    } while(1);
}


void calcola_30_giorni_dopo(char data[]) {
    int anno;
    int mese;
    int giorno;
    int data_valore;
    estrapola_data_numerica(data,&anno,&mese,&giorno);
    data_valore=calcola_data_valore(&anno,&mese,&giorno);
    data_valore+=30;
    costruisci_data_da_valore_data(data_valore,&anno,&mese,&giorno);
    costruisci_stringa_da_data(data,anno,mese,giorno);
}


void estrapola_data_numerica(char data[],int* anno, int* mese, int* giorno) {
    *anno = (data[9]-'0') + 10*(data[8]-'0') + 100*(data[7]-'0') + 1000*(data[6]-'0');
    *mese = (data[4]-'0') + 10*(data[3]-'0');
    *giorno = (data[1]-'0') + 10*(data[0]-'0');
}


int calcola_data_valore(int* anno,int* mese, int* giorno) {
    int data_valore;
    int trentuno=0;
    int ventotto=0;
    for (int i=1; i<*mese; i++) {
        if(i==1 || i==3 || i==5 || i==7 || i==8 || i==10) {
        trentuno++;
        } else if (i==2) {
            ventotto++;
        }
    }    
    
    data_valore =   *anno*365                                                                                       // giorni per ogni anno passato
                    +(*anno-1)/4-(*anno-1)/100+(*anno-1)/400 + 1                                                    // anni bisestili passati (+1 per l'anno 0)
                    +(*mese-1)*30 + trentuno - (2-(((*anno%4)==0 && (*anno%100)!=0) || (*anno%400)==0))*ventotto    // giorni per mese passato
                    +*giorno;                                                                                       // giorni passati in questo mese
    return data_valore;
}

void costruisci_data_da_valore_data(int data_valore,int* anno, int* mese, int* giorno) {
    
    int valore_anno;
    int flag_non_bisestile;
    int giorni_da_inizio_anno;

    int anno_provvisorio = data_valore / 365 +1;

    // Aggiustamento anno
    do {
        anno_provvisorio--;
        valore_anno = anno_provvisorio*365+(anno_provvisorio-1)/4-(anno_provvisorio-1)/100+(anno_provvisorio-1)/400 +1; // L'ultimo +1 è necessario per considerare anche l'anno 0
        flag_non_bisestile = ((anno_provvisorio%4)!=0 || (anno_provvisorio%100)==0) && ((anno_provvisorio%400)!=0);
        giorni_da_inizio_anno = data_valore-valore_anno;
    } while (giorni_da_inizio_anno <= 0);
    *anno=anno_provvisorio;
    
    // Calcolo mese e giorno
    int giorni_dei_mesi[12] = {0,31,60-flag_non_bisestile,91-flag_non_bisestile,121-flag_non_bisestile,152-flag_non_bisestile,182-flag_non_bisestile,213-flag_non_bisestile,244-flag_non_bisestile,274-flag_non_bisestile,305-flag_non_bisestile,335-flag_non_bisestile};
    for (int i=1;i<12;i++) {
        if (giorni_da_inizio_anno<=giorni_dei_mesi[i]) {
            *mese = i;
            *giorno = giorni_da_inizio_anno - giorni_dei_mesi[i-1];
            return;
        }
    }
    *mese = 12;
    *giorno = giorni_da_inizio_anno-giorni_dei_mesi[11];
}


void costruisci_stringa_da_data(char data[],int anno,int mese,int giorno) {
    data[0] = giorno / 10 +'0';
    data[1] = giorno % 10 + '0';
    data[2] = '/';
    data[3] = (mese / 10) + '0';
    data[4] = mese % 10 + '0';
    data[5] = '/';
    data[6] = (anno / 1000) % 10 + '0';
    data[7] = (anno / 100) % 10 + '0';
    data[8] = (anno / 10) % 10 + '0';
    data[9] = (anno % 10) + '0';
    data[10] = '\0';
}

// funzione registra restituzione
void registra_restituzione(Prestito* database_prestiti,Libro* database_libri, int prestiti_inseriti, int libri_inseriti) {
    
    // Richiedi prestito
    int codice;
    printf("\nInserisci il codice del prestito da modificare:\n");
    do{ 
        printf("\nLa tua scelta: ");
        scanf("%d",&codice);
        if (codice<=0) {
            printf("\nIl codice del prestito deve essere un numero positivo!\n");
        } else if (codice>prestiti_inseriti) { // Questo controllo funziona perché il codice è sequenziale.
            printf("\nIl codice del prestito è inesistente!\n");
        }

        if (codice<=0 || codice>prestiti_inseriti) {
            int flag=menu_codice_prestito_errato();
            if (flag==1) {
                return;
            }
        }
    } while (codice<=0 || codice>prestiti_inseriti);

    // Controllo esistenza codice, assegnazjone restituito e aumento numero di copie.
    for (int i=0;i<prestiti_inseriti;i++) {
        if (codice == database_prestiti[i].codice_prestito) {   
            if(database_prestiti[i].restituito == 0) {
                database_prestiti[i].restituito=1;
                printf("Restituzione assegnata correttamente!");
                for (int j=0;j<libri_inseriti;j++) {
                    if (strcmp(database_libri[j].codice_ISBN,database_prestiti[i].codice_ISBN_libro)==0) {
                        database_libri[j].numero_copie++;
                        break;
                    }
                }
            } else {
                printf("Restituzione già assegnata.");
            }
            break;
        }
    }
    return;
}


int menu_codice_prestito_errato() {
    
    int scelta;
    printf("\nCosa vuoi fare?\n");
    printf("\n  1. Inserire un nuovo codice di prestito;\n");
    printf("  2. Tornare al menù gestione prestiti.");
    do {
        printf("\nLa tua scelta\n");
        scanf("%d",&scelta);
        switch (scelta) {
            
        case 1: 
            return 0;

        case 2:
            return 1;

        default:
            printf("\nLa scelta deve esserd 1 oppure 2! Riprova:\n");
            break;
        }
    } while (1);
    return 0;

}

// funzione visualizza prestiti attivi
void visualizza_prestiti_attivi(Utente* database_utenti,Prestito* database_prestiti,Libro* database_libri,int libri_inseriti,int prestiti_inseriti,int utenti_inseriti) {
    printf("\nEcco tutti i prestiti attivi al momento:\n");
    int numero_prestiti_attivi=0;
    for (int i=0;i<prestiti_inseriti;i++) { // Ciclo sui prestiti inseriti
        if (database_prestiti[i].restituito==0) {
            numero_prestiti_attivi++;
            printf("\nPrestito %d:\n",numero_prestiti_attivi);
            printf("\n  1. Codice prestito: %d\n",database_prestiti[i].codice_prestito);
            
            // Ricerca titolo e stampa
            char titolo[101];
            for (int j=0;j<libri_inseriti;j++) {
                if (strcmp(database_prestiti[i].codice_ISBN_libro,database_libri[j].codice_ISBN)==0) {
                    strcpy(titolo,database_libri[j].titolo);
                    break;
                }
            }
            printf("  2. Titolo del libro: %s\n",titolo);

            // Ricerca nome utente e stampa
            char nome[51];
            char cognome[51];
            for (int j=0;j<utenti_inseriti;j++) {
                if (database_prestiti[i].codice_utente == database_utenti[j].codice_utente) {
                    strcpy(nome,database_utenti[j].nome);
                    strcpy(cognome,database_utenti[j].cognome);
                    break;
                }
            }
            printf("  3. Nome utente: %s\n",nome);
            printf("  4. Cognome utente: %s\n",cognome);

            // Stampa data prestito e data restituzione
            printf("  5. Data prestito: %s\n",database_prestiti[i].data_prestito);
            printf("  6. Data di restituzione prevista: %s\n",database_prestiti[i].data_restituzione_prevista);
            printf("  7. Codice prestito: %d\n",database_prestiti[i].codice_prestito);
        }
    }
}

// funzione visualizza storico prestiti utente
void visualizza_storico_prestiti_utente(Utente* database_utenti,Prestito* database_prestiti,int utenti_inseriti,int prestiti_inseriti) {
    
    int codice;
    int flag=-1;
    printf("\nInserisci il codice dell'utente che stai cercando: ");
    
    // Ciclo while per controllo codice utente inserito
    do {
        int scelta;
        scanf("%d",&codice);
        if (codice<=0) {
            printf("\nIl codice deve essere positivo!\n");
            printf("Cosa vuoi fare?\n");
            printf("\n  1. Inserire un altro nome dell'autore da cercare;\n");
            printf("  2. Tornare al menù gestione libri.\n");
            printf("\nLa tua scelta: ");

            do{ // ciclo per la scelta dell'utente
                scanf("%d",&scelta);
                if (scelta == 1) break;
                if (scelta == 2) return;
                printf("La tua scelta deve essere 1 oppure 2! Riprova:\n");
            } while (1);
        } else {
            for (int i=0;i<utenti_inseriti;i++) {
                if (database_utenti[i].codice_utente == codice) {
                    flag = i;
                    printf("\nUtente trovato correttamente!\n");
                    break;
                }
            }
            if (flag == -1) {
                printf("Utente non trovato!\n");
                printf("Cosa vuoi fare?\n");
                printf("\n  1. Inserire un altro nome dell'autore da cercare;\n");
                printf("  2. Tornare al menù gestione libri.\n");
                printf("\nLa tua scelta: ");
    
                do{ // ciclo per la scelta dell'utente
                    scanf("%d",&scelta);
                    if (scelta == 1) break;
                    if (scelta == 2) return;
                    printf("La tua scelta deve essere 1 oppure 2! Riprova:\n");
                } while (1);
            }
        }
    } while (flag == -1);
    
    // Stampo i prestiti non restituiti, salvo le posizioni di quelli restituiti  
    int indice_prestito_non_restituito=-1;
    int indice_prestito_restituito=-1;
    int* posizioni_restituiti=malloc(5*sizeof(int));
    int capacita_posizioni_restituiti = 5;

    // Controllo allocazione dinamica
    if (posizioni_restituiti==NULL) {
        printf("\nErrore di allocazione in memoria (allocazione dinamica della variabile posizioni_restituiti)! Verrai reindirizzato al menù gestione prestiti.\n");
        return;
    }

    posizioni_restituiti[0]=-1;
    // Ciclo per scrittura prestiti non restituiti
    for (int i=0;i<prestiti_inseriti;i++) {
        if (database_prestiti[i].codice_utente == codice) {
            if (database_prestiti[i].restituito == 0) {
                if (++indice_prestito_non_restituito == 0) {
                    printf("\nPrestiti non restituiti:\n");
                }
                stampa_prestito(database_prestiti,i,indice_prestito_non_restituito);
            } else {
                if (capacita_posizioni_restituiti<=++indice_prestito_restituito) { // Eventuale riallocazione dinamica di posizioni_restituiti
                    posizioni_restituiti = realloc(posizioni_restituiti,2*capacita_posizioni_restituiti*sizeof(int));
                    if (posizioni_restituiti==NULL) {
                        printf("\nErrore di allocazione in memoria (riallocazione dinamica della variabile prestiti_restituiti)! Verrai reindirizzato al menù gestione prestiti.\n");
                        return;
                    }
                    capacita_posizioni_restituiti = 2*capacita_posizioni_restituiti;
                }
                posizioni_restituiti[indice_prestito_restituito]=i;
            }
        }
    }
    if (indice_prestito_non_restituito == -1) {
        printf("\nNon ci sono prestiti attivi per questo utente.\n");
    }

    // Stampa dei restituiti
    if (posizioni_restituiti[0]!=-1) {
        printf("\nPrestiti restituiti:\n");
        for (int i=0;i<=indice_prestito_restituito;i++) {
            stampa_prestito(database_prestiti,posizioni_restituiti[i],i);
        }
    } else {
        printf("\nNon ci sono prestiti restituiti.\n");
    }

    free(posizioni_restituiti);

    return;
}

void stampa_prestito(Prestito* database_prestiti,int indice_prestito_assoluto,int indice_prestito_nel_ciclo_specifico) {
    printf("\nPrestito: %d\n",indice_prestito_nel_ciclo_specifico+1);
    printf("  1. Codice prestito: %d\n",database_prestiti[indice_prestito_assoluto].codice_prestito);
    printf("  2. Codice ISBN del libro: %s\n",database_prestiti[indice_prestito_assoluto].codice_ISBN_libro);
    printf("  3. Codice utente: %d\n",database_prestiti[indice_prestito_assoluto].codice_utente);
    printf("  4. Data prestito: %s\n",database_prestiti[indice_prestito_assoluto].data_prestito);
    printf("  5. Data di restituzione prevista: %s\n",database_prestiti[indice_prestito_assoluto].data_restituzione_prevista);
} 


int menu_errore_inserimento_ISBN() {
    int scelta = 0;
    printf("\nCosa vuoi fare?\n");
    printf("  1. Inserire un nuovo codice ISBN\n");
    printf("  2. Annullare l'inserimento del libro e tornare al menu\n");
    printf("La tua scelta: ");
    
    do {
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                return 0; // Riprova
            case 2:
                return -1; // Annulla
            default:
                printf("Scelta non valida. Inserisci 1 o 2: ");
                break;
        }
    } while (1);
    return 0;
}
// Funzione inserisciNuovoLibro
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

    if (invalida_ISBN(ISBN_temp)) {  // se non è valido ritorna 1
        printf("Formato ISBN NON valido. Riprova.\n");
    }
    else{
        // controllo eventuali duplicati (il codice ISBN è univoco)
        for (int i = 0; i < *ptrNumLibri; i++) {
            if (!strcmp(ISBN_temp, libri[i].codice_ISBN)) {
                printf("ISBN già presente nella libreria. Riprova.\n");
                duplicato=1;
                break;
            }
        }
    }
    if (invalida_ISBN(ISBN_temp) || duplicato == 1) {
            int exit_flag;
            exit_flag = menu_errore_inserimento_ISBN();
            
            if (exit_flag == -1) {
                printf("\nInserimento annullato.\n");
                return libri; // Esce dalla funzione tornando al menu principale
            }
        }
    // ripeti finché non valido o duplicato
} while (invalida_ISBN(ISBN_temp) || duplicato == 1);

    strcpy(libri[*ptrNumLibri].codice_ISBN,ISBN_temp);

    // Input titolo
    printf("Inserisci titolo (max 100 caratteri): ");
    scanf(" %100[^\n]", libri[*ptrNumLibri].titolo); 
    
    // Input autore
    printf("Inserisci autore (max 50 caratteri): ");
    scanf(" %50[^\n]", libri[*ptrNumLibri].autore);  
    
    // Input anno pubblicazione
    int anno_tmp;
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
    scanf(" %30[^\n]", libri[*ptrNumLibri].genere);
    
    // Incremento il contatore al prossimo libro nell'array libri
    (*ptrNumLibri)++;

    printf("Libro inserito con successo!\n");
    return libri;
}


// funzione visualizzaTuttiILibri:
void visualizzaTuttiILibri(Libro *libri, int numLibri){
    if (numLibri <= 0) {
        printf("Nessun libro presente.\n");
        return;
    }
    
    printf("\n=== ELENCO COMPLETO DEI LIBRI NEL CATALOGO ===\n\n");

    // Scorre l'intero array di libri
    for (int i = 0; i < numLibri; ++i) {
        // Stampa le informazioni del libro corrente in formato verticale
        // L'uso di "%-25s" allinea le etichette per una migliore leggibilità
        printf("%-25s: %s\n", "ISBN", libri[i].codice_ISBN);
        printf("%-25s: %s\n", "Titolo", libri[i].titolo);
        printf("%-25s: %s\n", "Autore", libri[i].autore);
        printf("%-25s: %d\n", "Anno di Pubblicazione", libri[i].anno_pubblicazione);
        printf("%-25s: %d\n", "Numero di Copie", libri[i].numero_copie);
        printf("%-25s: %s\n", "Genere", libri[i].genere);

        if (i < numLibri - 1) {
            printf("\n\n");
        }
    }
    
    printf("\n");
}


// funzione cerca libro per ISBN-> ritorna o l'indice o -1 attraverso una stampa libri,numLibri
void cercaLibroPerISBN(Libro *libri,int numLibri){
    if (numLibri <= 0) {
        printf("Nessun libro presente.\n");
        return;
    }

    char isbnInserito[18];
    int indiceTrovato;
    do{
        indiceTrovato = -1;
        // inserimento codice ISBN
        printf("Inserisci codice ISBN (formato XXX-X-XXXX-XXXX-X): \n");
        scanf("%17s", isbnInserito);
        if (invalida_ISBN(isbnInserito)) {
        printf("Formato ISBN NON valido. Riprova.\n"); 
        }
        else{
            // ricerca isbn inserito:
            for(int i = 0; i < numLibri; i++){
                if(strcmp(isbnInserito,libri[i].codice_ISBN) == 0){
                    indiceTrovato = i;
                    break;  // trovato, interrompo il ciclo for
                }
            }
        
            if (indiceTrovato != -1) {
                // Libro trovato
                printf("\n=== LIBRO TROVATO ===\n");
                printf("Codice ISBN:                %s\n", libri[indiceTrovato].codice_ISBN);
                printf("Titolo:                     %s\n", libri[indiceTrovato].titolo);
                printf("Autore:                     %s\n", libri[indiceTrovato].autore);
                printf("Anno di pubblicazione:      %d\n", libri[indiceTrovato].anno_pubblicazione);
                printf("Numero di copie:            %d\n", libri[indiceTrovato].numero_copie);
                printf("Genere:                     %s\n", libri[indiceTrovato].genere);
                return;
            } else {
                printf("\nERRORE: Nessun libro trovato con questo codice ISBN.\n");
            }
        }
        // Se arriviamo qui, o il formato era sbagliato o il libro non c'era.
        int scelta = menu_errore_inserimento_ISBN();
        if (scelta == -1) {
            printf("\nRicerca annullata.\n");
            return; // L'utente ha scelto di uscire
        }
        // Se scelta è 0, il ciclo do-while ricomincia
    } while (1); // Il ciclo è controllato dai return interni
}


// funzione cerca libri per autore  libri,numLibri
void cercaLibriPerAutore(Libro *libri,int numLibri){
    if (numLibri <= 0) {
        printf("Nessun libro presente.\n");
        return;
    }

    int libriTrovati; // Flag per contare i libri trovati
    char autoreInserito[51];
    
    do{
        libriTrovati = 0; // Resetta il contatore ad ogni nuova ricerca
        // inserimento nome autore:
        printf("Inserisci il nome dell'autore: \n");
        scanf(" %50[^\n]",autoreInserito);

        // ricerca nome autore
        for(int i = 0; i < numLibri; i++){
            // Confronta il nome dell'autore (TODO: ignorando maiuscole/minuscole sarebbe un miglioramento)
            if(strcmp(libri[i].autore, autoreInserito) == 0){
                // Se questo è il PRIMO libro trovato, stampa l'intestazione
                if (libriTrovati == 0) {
                    printf("\n=== Libri trovati per l'autore: %s ===\n", autoreInserito);
                }
                
                // Stampa i dettagli del libro trovato
                printf("\n");
                printf("Titolo:                     %s\n", libri[i].titolo);
                printf("Codice ISBN:                %s\n", libri[i].codice_ISBN);
                printf("Anno di pubblicazione:      %d\n", libri[i].anno_pubblicazione);
                printf("Numero di copie:            %d\n", libri[i].numero_copie);
                printf("Genere:                     %s\n", libri[i].genere);

                libriTrovati++; // Incrementa il contatore dei libri trovati
            }
        }
        
        // Se, dopo aver controllato tutti i libri, il contatore è ancora 0
        if(libriTrovati == 0){
            int scelta;
            printf("\nNon è stato trovato nessun libro con il nome dell'autore inserito!\n");
            printf("Cosa vuoi fare?\n");
            printf("\n  1. Inserire un altro nome dell'autore da cercare;\n");
            printf("  2. Tornare al menù gestione libri.\n");
            printf("\nLa tua scelta: ");

            do{ // ciclo per la scelta dell'utente
                scanf("%d",&scelta);
                if (scelta == 1) break;
                if (scelta == 2) return;
                printf("La tua scelta deve essere 1 oppure 2! Riprova:\n");
            } while (1);
            
            if (scelta == 1) continue; // Continua con il ciclo do-while
        }

    } while(libriTrovati == 0); // Continua a chiedere un autore finché non ne trova almeno uno
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

    printf("\n=== LIBRI DISPONIBILI PER IL PRESTITO (Ordinati per Titolo) ===\n\n");
    
    int libriDisponibili = 0; // Contatore per i libri che rispettano il vincolo

    // Scorro i libri (ormai ordinati) per stamparli
    for (int i = 0; i < numLibri; i++) {
        // Applico il vincolo: stampo solo se le copie sono > 0
        if (libri[i].numero_copie > 0) {
            
            // Se questo non è il primo libro che stampo, aggiungiamo il doppio spazio
            if (libriDisponibili > 0) {
                printf("\n\n");
            }

            // Stampa le informazioni in formato verticale
            printf("%-25s: %s\n", "Titolo", libri[i].titolo);
            printf("%-25s: %s\n", "Autore", libri[i].autore);
            printf("%-25s: %s\n", "ISBN", libri[i].codice_ISBN);
            printf("%-25s: %d\n", "Copie Disponibili", libri[i].numero_copie);
            printf("%-25s: %s\n", "Genere", libri[i].genere);

            libriDisponibili++; // Incrementa il contatore dei libri validi
        }
    }
    
    //  Se dopo aver ciclato tutti i libri il contatore è ancora a 0,
    //    significa che nessun libro era disponibile.
    if (libriDisponibili == 0) {
        printf("Attualmente non ci sono libri disponibili per il prestito.\n");
    }

    printf("\n");
}


// === MENU GESTIONE LIBRO === //
void menuGestioneLibri(Libro **libri, int *ptrNumLibri, int *ptrCapLibri){
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
