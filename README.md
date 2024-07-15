# 2cornot2c
It's a 101 C course for my students.
Sorry, only italian version so far.

## Introduzione

Il corso è fondamentalmente pratico, non è richiesto alcun prerequisito e nulla è dato per scontato.
Prima di iniziare è giusto ricordare che per svolgere i laboratori richiesti è necessaria la conoscenza di alcuni strumenti, in particolare:

* [git](https://git-scm.com/download/win)
* [vagrant](https://developer.hashicorp.com/vagrant/install?ajs_aid=e022a39f-7694-4bed-a4cd-f721f515b885&product_intent=vagrant#windows)

 I link forniti sopra portano alle versioni dei softare per architettura `amd64` in ambiente `windows`, questo a causa dell'assenza di macchine
 linux nei lab scolastici.
 _GIT_ e _VAGRANT_ ci serviranno per ottenere un ambiente di sviluppo identico per tutti e per un provisioning automatico; in altre parole git ci permetterà di condividere il codice dei laboratori e vagrant di condividere la stessa macchina virtuala (`ubuntu-22.04`) con l'ambiente di sviluppo preinstallato.

 ## Installare l'ambiente di sviluppo

I passi seguenti permettono di duplicare sulla tua macchina locale l'ambiente di sviluppo (codice e vm).
Nella directory radice del progetto (`2cornot2c`) troverai una directory `lab` con il codice c per tutti laboratori. 
Questa cartella `2cornot2c\lab` è montata automaticamente sul file system della macchina virtuale nella cartella `/lab`. 
Tutto quello che verrà modificato sulla macchina linux in `lab`(vm o macchina guest) verrà visto sulla macchina windows (host) in `2cornot2c\lab`. 

1) Clone il repository con il codice ed il Vagrantfile

 ```bash
git clone https://github.com/kinderp/2cornot2c.git
```

2) Entra dentro la directory root del repository
   
```bash
cd 2cornot2c
```

3) Avvia la macchina virtuale

```bash
vagrant up
```

4) Apri una sessione ssh sulla macchina appena avviata

```bash
vagrant ssh
```

## Laboratori

All'interno della cartella `/lab` nella macchian Linux troverai il codice su cui lavorare.
Ogni lab ha un numero ed un nome ad esso associato, ad esempio al primo laboratorio è assegnato il numero `0` ed il nome `intro`; questo significa che per questo lab esisterà una cartella `lab/0_intro` che conterrà tutto il codice del lab.
All'interno della cartella del laboratorio troverai dei file sorgente con estensione `.c` anche questi con un numero ed un nome; ad esempio il primo sorgente del lab `0_intro` è `0_hello.c`.
Ogni lab al suo interno contiene una cartella `bin` destinata ad ospitare i file eseguibili ottenuti al termine del processo di compilazione.

### Il processo di compilazione

I programmi sono scriti in un qualche linguaggio di programmazione, il programmatore scrive il codice sorgente sfruttando un particolare linguagggio. Il codice sorgente contiene tutte le istruzioni che il programma dovrà eseguire. Le istruzioni all'interno del codice sorgente scritte in un qualsiasi linguaggio di programmazione devono essere tradotte in una sequenza di bit (in altri termini nel linguaggio macchina) perchè la cpu è in grado di comprendere solo il linguaggio macchina, esclusivamente sequenze di bit e nient'altro. In sintesi si dice che il programma sorgente deve essere trasformato in in file eseguibile (file binario) che contiene le istruzioni (sequenze di bit) per la pecifica architettura del nostro processore.
Questo processo di trasformazione del sorgente in binario è detto processo di compilazione ed è svolto del compilatore. In realtà queto processo è articolato in vari step e non coinvolge solo il compilatore. Vediamo brevemente di studiarne le fasi.
Se non lo hai già fatto avvia la macchina virtuale con `vagrant up` ed al termine del boot avvia una sessione ssh con il comando `vagrant ssh`.
Una volta dentro nella tue home directory (utente vagrant) usa vim per creare un nuovo file in questo modo: `vim hello.c` e copia il codice mostrato sotto:

```c
#include <stdio.h>

int main(void){
    printf("Hello World");
}
```
Salva il contenuto premendo la combinazione: `Esc` + `:wq`.
Compila il sorgente `hello.c` lanciando il seguente comando: `gcc -o hello hello.c`; `gcc` è il compilatore che useremo in questo corso, lo trovi già installato sulla vm. In questo caso l'opzione `-o` specifica il nome del file oggetto (il file binario eseguibile) che vogliamo creare; ovviamente dobbiamo specificare successivamente il sorgente da cui partire per la generazione dell'eseguibile (`hello.c`). Se tutto ha funzionato puoi lanciare il programma appena compilato in questo modo: `./hello`. Come avrai avuto modo di constatare il programma ha stampato a schermo la frase `Hello World`; per fare ciò il programmatore si è servito di un pezzo di codice già pronto (in sostenza la funzione `printf()`) per inforare il compilatore circa il corretto uso di questo pezzo di codice (la funzione `printf()`) è stata inserita nella prima riga del programma la direttiva al preprocessore `#include <stdio.h>`. Vedremo in dettaglio cosa vuol dire usare una funzione esterna e come includere con le direttive il suo prototipo, per adesso ci basta sapere che per stampare è stata usata una funzione già pronta ed è stato necessario informare il compilatore di questo.

<p align="center">
<img src="https://github.com/kinderp/2cornot2c/blob/main/images/processo_di_compilazione.png" align="center">
</p>

Nella figura di sopra è mostato l'intero processo di compilazione che come puoi vedere è composto da almeno quattro fasi, come puoi vedere i due parametri passati al compilatore con: `gcc -o hello hello.c` sono ripsettivamente il file di input del processo (`hello.c`) ed il file di output (`hello`) del processo.
Volendo è possibile richiedere al compilatore di fermarsi ad uno specifico step senza produrre l'output finale. Le quattro fasi del processo di compilazione sono rispettivamente:

* Preprocessamento (_Preprocessing_): il preprocessore (`cpp`) esegue tutte le sostituzione di testo richieste secondo le chiamate al preprocessore, il risultato è un file con estensione `.i` nel nostro caso quindi `hello.i`. Per bloccare il processo di compilazione alla fase di preprocessamento puoi eseguire questo comando: `gcc -E hello.c > hello.i`. Il file `hello.i` conterrà tutte le sostituzione effettuate dal preprocessore e come puoi vedere quindi ha molto più contenuto del file di partenza `hello.c`, spiegheremo le chiamate al preprocessore nei prossimi paragrafi.
* Compilazione (_Compilation_): il compilatore (`cc`) trasforma il contenuto testuale del file `hello.i` in codice c nel corrispettivo codice assembly (`hello.s`) specifico per l'architettura del processore
* Assemblaggio (_Assembly_): l'assemblatore (`as`) trasforma il codice assembl contenuto in `hello.s` nelle istruzioni macchina dell'architettura della cpu, il risultato è il file oggetto rilocabile `hello.o`
* Linkaggio (_Linking_): il linker (`ld`) ha il compito di aggreggare in un unico file oggetto (il file eseguibile) eventuali altri file oggetto di librerie esterne o del linguaggio. Nel nostro esempio il programmatore ha fatto uso di una funzione del linguaggio (`printf()`) quindi il linker aggregerà nel file eseguibile (`hello`) il file oggetto `hello.o` ed il file oggetto relativo al codice della funzione printf: `printf.o`
### Introduzione

Un programma c è di fatto una collezione di:

* Variabili
* Costanti 
* Funzioni
* Chiamate al preprocessore

Di seguito provvederemo a dare una definizione sommaria per ogni componente sopra citato, rimandiamo ai singoli paragrafi per una trattazione completa.

> [!IMPORTANT]
> Una **variabile** è una locazione di memoria a cui è stato associato un **identificatore** cioè un nome per referenziare nel codice quella cella di memoria
> Una variabile ha un **tipo**; il tipo associato ad una variabile definisce appunto che tipo di dato essa può contenere (un numero intero, un numero reale, un carattere etc.)
> in altre parole il tipo della variabile definisce il numero di byte occupati dalla locazione di memoria referenziata dall'identificatore
> Una variabile può cambiare il valore in essa contenuto durante il ciclo di vita del programma. L'operazione mediante la quale si assegna un valore iniziale ad una variabile è detto **inizializzazione**, l'operazione attraverso cui si associa un nuovo valore ad una variabile già inizializzata è detto **assegnamento**

```c
int var_intera; // variabile non inizializzata
var_intera = 5; // assegnamento
int var_intera_inizializzata = 3; // variabile inizializzata
var_intera_inizializzata = 9; // assegnamento
```

> [!IMPORTANT]
> Per la **costante** valgono le stesse considerazioni fatte per le variabili con l'eccezione che per le costanti non è possibile assegnare un nuovo valore una volta che questa è stata inizializzata

```c
const double pi = 3.14; // costante pi greco
```

> [!IMPORTANT]
> Una funzione è una collezione di istruzioni che svolgono uno specifico compito; una funzione ha un nome (`sottrazione` nel nostro esempio), un valore di ritorno, dei parametri di input (`minuendo` e `sottraendo` nel codice d'esempio) ed un corpo che è delimitato da una parenti graffa aperta `{` ed una chiusa `}`

```c
int sottrazione(int minuendo, int sottraendo){
    return minuendo - sottraendo;
}
```

> [!IMPORTANT]
> Il preprocessore viene richiamato dal compilatore come primo step nel processo di generazione del file eseguibile che poi verrà avviato dall'utente. Il preprocessore ha il compito di effettuare delle semplici sostituzioni di testo; esistono diverse sostituzioni che il preprocessore può effettuare per contro nostro. L'insieme di queste operazioni sono dette chiamate al preprocessore.

#### 0_hello.c

Come da tradizione, il primo esempio di codice è il classico `Hello World`.
Il programma di sotto stampa a schermo una semplice frase: `Ciao Mondo` in inglese.

https://github.com/kinderp/2cornot2c/blob/18b60e866c1e0e22c59835fe953cbe3c534e7422/lab/0_intro/0_hello.c#L14-L19

Compila il sorgente con: `gcc -o 0_hello bin/0_hello` e poi esegui il programma con: `bin/0_hello`.
Riconosciamo subito una funzione: `main()` [16-19]. Questa è una funzione speciale, tutti i programmi C devono averne una in quanto rappresenta il punto di partenza per l'esecuzione di ogni programma. Sei libero di chiamare tutte le altre funzioni a tuo piacimento ma la funzione da cui parte l'esecuzione si deve chiamare `main()`. Come qualsiasi funzione `main()` ha un tipo di ritorno `int` e dei parametri in ingresso opzionali, in questo caso la funzione `main()` non si aspetta nessun parametro in ingresso dal chiamante (il sistema operativo) e per esprimere che questa non accetta alcun valore in ingresso si usa la parola riservata `void`.
Ti potrebbe capitare di vedere la funzione `main()` in queste versioni:

```c
main()
```

```c
void main()
```

La prima forma è tollerata da vecchia versioni del C (C90) quindi pre ANSI C ma non è accettata da quelle successive (C99, C11); la seconda potrebbe essere tollerata da alcuni compilatori ma se il tuo codice deve funzionare anche su altre macchine è meglio usare qualcosa che funziona sempre.

> [!IMPORTANT]
> Dichiarazione di funzione (o prototipo): il tipo di ritorno, i tipi dei parametri in ingresso ed il nome della funzione rappresentano il prototipo della funzione. Quando si fornisce il prototipo di una funzione si usa dire che si effettua la dichiarazione della funzione

> [!IMPORTANT]
> Definizione di funzione: quando si fornisce l'implementazione della funzione (il corpo) allora si dice che la funzione è definita. La definizione implica anche la dichiarazione

Riprendendo la funzione `sottrazione` usata precedentemente avremo rispettivamente: la definizione in basso

```c
int sottrazione(int minuendo, int sottraendo){
    return minuendo - sottraendo;
}
```

e la dichiarazione o prototipo di seguito:

```c
int sottrazione(int, int);
```

volendo è possibile fornire anche i nomi dei parametri in ingresso ma nulla cambia ai fini della dichiarazione.

> [!IMPORTANT]
> Il compilatore quando incontra una chiamata a funzione deve conoscerne almeno il prototipo per verificare che questa stia venendo usata correttamente (il corretto numero e tipo per i parametri di ingresso e che il valore di ritorno sia assegnato ad una variabile compatibile, dello stesso tipo).

La funzione `main()` fa usa di un'altra funzione: `printf()` che viene usata per stampare su schermo. Questa funzione è fornita (la sua implementazione) dal linguaggio C stesso, quindi non viene definita (non si fornisce l'implementazione nel nostro file). L'implementazione della `printf()` sarà fornita sotto forma di file oggetto `.o` che verrà assemblato dal linker con il nostro: `hello.o` all'interno del file eseguibile finale. Il compilatore ha però bisogno di conoscere almeno il prototipo della funzione `printf()` per verificarne l'uso corretto. Il prototipo della funzione `printf()` è fornito all'interno del file `stdio.h`; risulta necessario copiare il contenuto di questo file nel nostro esempio nelle righe precedenti a quella dove la funzione `printf()` è usata. Non c'è bisogno di copiare ed incollare il file `stdio.h` ma è possibile usare una direttiva del preprocessore `#include <stdio.h>` che sostuisce il contenuto del file `stdio.h` a partire dalla riga di codice dove è inserita.
Per verificare l'effettiva aggiunta del prototipo di `printf()` da parte del preprocessore puoi lanciare:

```bash
 gcc -E 0_hello.c |grep 'printf'
```
questo l'output sulla mia macchina

```bash
      1 extern int fprintf (FILE *__restrict __stream,
      2 extern int printf (const char *__restrict __format, ...);
      3 extern int sprintf (char *__restrict __s,
      4 extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
      5 extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
      6 extern int vsprintf (char *__restrict __s, const char *__restrict __format,
      7 extern int snprintf (char *__restrict __s, size_t __maxlen,
      8      __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));
      9 extern int vsnprintf (char *__restrict __s, size_t __maxlen,
     10      __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
     11 extern int vdprintf (int __fd, const char *__restrict __fmt,
     12      __attribute__ ((__format__ (__printf__, 2, 0)));
     13 extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     14      __attribute__ ((__format__ (__printf__, 2, 3)));
     15  printf("Hello World\n");
```

Alla riga 2 il prototipo di `printf()`.

Infine, terminata la propria computazione il nostro programma ritora 0 per informare il sistema operativo che ha terminato senza errori.

Riassumendo: 
* riga 14: inclusione del file d'intestazione `stdio.h` contente il prototipo della funzione `printf()`. Il prototipo serve al compilatore per verificare che il programmatore utilizzi correttamente la funzione, in questo caso la `printf()`
* riga 16-19: definizione della funzione `main()`
 
#### 1_funzioni.c

Le funzioni sono un blocco di codice, un insieme di istruzioni che vengono raggruppate e possono essere richiamata in qualsiasi momento all'interno di un programma. Per intenderci, se nel nostro programma calcoliamo più volte la media pesata dei nostri voti è consigliabile racchiudere tutte le istruzioni all'interno di una funzione e richiamarla ogni volta che ne abbiamo bisogno piuttosto che riscrivere più volte lo stesso identico codice in punti diversi. Le funzioni possono ritornare un valore come risultato della loro elaborazione (possono anche non ritornare nulla al chiamante) e possono ricevere in ingresso un certo numero di parameti.
Una funzione ha un'intestazione ed un corpo, usando sempre la solita funzione sottrazione vista in precedenza avremo:

```c
int sottrazione(int minuendo, int sottraendo){
    return minuendo - sottraendo;
}
```

la prima riga rappresenta l'intestazione della funzione (escluso la parentesi graffa), tutto il codice compreso da `{` e `}` è il corpo.
Quando viene fornita sia l'intestazione che il corpo (l'implementazione) si parla di definizione di funzione, se viene fornita solo l'intestazione (anche detta prototipo) si parla di dichiarazione di funzione.
Il prototipo della funzione `sottrazione` è dunque il seguente:

```c
int sottrazione(int minuendo, int sottraendo);
```

Volendo è possibile omettere il nome dei parametri in ingresso lasciando solo il tipo, in questo modo:

```c
int sottrazione(minuendo, sottraendo);
```

Per il compilatore non cambia nulla ma può aiutare un altro programmatore a comprendere il significato e l'uso dei parametri in ingresso.
Di sotto è riportato un esempio completo che fa uso della funzione `sottrazione`, come è possibile vedere questa è richiamta all'interno del `main()` alla riga 8 fornendo in ingresso i due parametri previsti durante le definzione. Se avessimo fornio un numero diverso (sia inferiore che superiore) di parametri o di tipo diverso rispetto al tipo intero il compilatore ci avrebbe dato errore (o forse nel secondo caso no...?!?)

https://github.com/kinderp/2cornot2c/blob/849c8731e84196bab6b5a17aed9e983d045cb025/lab/0_intro/1_funzioni.c#L1-L14

Siccome la definzione della funzione `sottrazione` è stata fornita successivamente (riga 12-14) al punto in cui questa è richiamata (riga 8) per permettere al compilatore di controllare il corretto uso da parte del programmatore è stato necessario fornire prima della riga 8 il prototipo della funzione (riga 3). Commentando la riga 3 il compilatore darebbe errore o almeno rileverebbe un warning circa una dichiarazione implicita che non è in grado di verificare.
Come spiegato ampiamente in precedenza, facciamo uso anche della funzione `printf()` ed in questo caso per fornire il prototipo sfruttiamo la direttiva al preprocessore `#inclde <stdio.h>`

##### 2_variabili.c

Abbiamo precedentemente detto che una variabile è semplicemente una locazione di memoria a cui è associato un identificatore ed un tipo.
L'identificatore è un nome mnemonico che ci permette, all'interno del codice, di accedere al valore contenuto nella locazione di memoria corrispondente. Il tipo definisce lo spazio (in terminit di byte) che la locazione di memoria può contenere.
**Una variabile prima di essere usata deve esssere sempre dichiarata**. Come anticipato, l'operazione di dichiarazione consiste nell'allocare spazio di memoria per la variabile ed associargli l'identificatore; lo spazio riservato viene dedotta dal tipo della variabile.
I diversi tipi privisti del C hanno un numero di byte prefissati dipendenti dall'architettura; per esempio `int` di solito occupa 32 bit, `char` 8 bit etc.
Se ti può aiutare puoi pensare ad una variabile come ad una scatola, vedi immagine di sotto.

```c
int answer;
```

![dichiarazione_variabile](https://github.com/kinderp/2cornot2c/blob/main/images/dichiarazione_variabile.png)

Una volta dichiarata la variabile è pronta ad ospitare un valore del tipo corrispondente a quello scelto nella dichiarazione; questa operazione è detta **assegnamento**

```c
int answer;   // dichiarazione di variabile, tipo intero
answer = 12;  // assegnamento del valore 12 alla variabile sopra dichiarata
```

![](https://github.com/kinderp/2cornot2c/blob/main/images/assegnamento_variabile.png)

E' possible associare un valore ad una variabile direttamente nella dichiarazione, questa operazione è detta **inizializzazione**

```c
int answer = 12; // dichiarazione con inizializzazione
```

E' possibile dichiarare più variabile nella stessa riga, purchè esse siano dello stesso tipo. In questo modo:

```c
int question, answer;
```

Oltre al tipo ed all'identificatore una variabile è caratterizzata dalla **visibilità** (`scope` in inglese) ed il **tempo di vita** (`lifetime` o `storage duration`)

> [!IMPORTANT]
> Visibilità: porzioni di codice nel programma in cui la variabile (il suo identificatore) è visibile e quindi è possibile fare riferimento alla variabile.

> [!IMPORTANT]
> Tempo di vita: porzione di tempo all'interno del ciclo di esecuzione del programma per cui alla variabile è associata una locazione di  memoria

Sulla base del tempo di vita e della visibilità possiamo classificare le variabile in due grandi categoria: **variabili globali** e **variabili locali**.

**Le variabili locali** sono definite all'interno delle funzioni e hanno una visibilità limitata: dal punto in cui sono dichiarate fino al termine del corpo della funzione (ti ricordo che il corpo è compreso tra `{` e `}`); il loro tempo di vita è anche limitato: la locazione di memoria ad esse associata è allocata quando la funzione viene invocata ed è liberata quando l'esecuzione dell'intero corpo della funzione termina.

**Le variabili globali** sono definite fuori dalle funzioni, di solito dopo le direttive `#include` nelle righe iniziali. 
Hanno visibilità globale appunto, cioè sono visibili a tutte le funzioni nel file in cui sono dichiarate (e potenzialmente anche alle funzioni in altri file ma questo lo vedremo in seguito); il loro tempo di vita coincide con quello globale di esecuzione del programma.

**Le variabili globali** se non inizializzate vengono poste a zero automaticamente, al contrario **le variabili locali** se non inizializzate contengono semplicemente un valore sporco ed assolutamente non prevedibile (il valore che era precedentemente contenuto nella locazione di memoria che è stata associata alla variabile).

Il programma di sotto fa uso di variabili globali e locali; semplicemente sono definite tre funzioni: _somma()_, _differenza()_ e _moltiplicazione()_. I due operandi su cui le funzioni devono lavorare (`primo` e `secondo`) vengono definite coeme variabili globali; essendo globali queste variabili sono visibili da tutte le funzioni nel file. 

```c
int primo, secondo; /* variabili globali */
```

Il risultato dell'operazione ed il tipo di operazione da svolgere sono definiti come variabili locali (dentro la funzione `main()`)

```c
int risultato; 	 // variabile locale
char operazione; // variabile locale
```

Queste due variabili sono visibili solo all'interno della funzione `main()` dono sono dichiarate e non dalle altre funzioni.

Inoltre, siccome facciamo uso della funzione `printf()` e `scanf()` dobbiamo includere con la direttiva al preprocessore (`#include<stdio.h`) i prototipi contenuti nel file header: `stdio.h`.

Le definizioni della funzioni `somma()`, `differenza()` e `moltiplicazione()` sono fornite dopo la loro effettiva chiamata nel `main()` e quindi per permettere al compilatore di controllare l'uso corretto di queste funzioni è stato necessario, prima del `main()`, fornire i prototipoi.

https://github.com/kinderp/2cornot2c/blob/8fcadf5f8a958f9b6194c4dac724d5a21ecef717/lab/0_intro/2_variabili.c#L1-L41

Riassumendo:

**Variabili globali**: 
* visibili in tutto il file da ogni funzione
* se non inizializzate ad un valore sono settate a zero automaticamente
* il loro ciclo di vita coincide con quello del programma, la memoria è allocata prima dell'esecuzione e deallocata al termine dell'esecuzione
  
**Variabili locali**:
* visibili solo nel blocco dove sono state dichiarate
* se non inizializzate settate ad un valore assolutamente casuale
* il loro ciclo di vita è limitato all'esecuzione del blocco dove sono dichiarate

L'uso di variabili globali per comunicare con le funzioni è scorretto ed è stato mostrato solo come esempio per introdurre le variabili globali. Meno uso facciamo delle variabili globali è meglio è.
Per comunicare con le funzioni, scambiare valori è sempre preferibile usare i parametri in ingresso ed i valori di ritorno, quindi le variabili locali.
Di sotto è riportato il codice corretto che elimina l'uso improprio delle variabili globali:

https://github.com/kinderp/2cornot2c/blob/9c77cc456006b9edb0dddea96eaf5860037e7b8c/lab/0_intro/3_variabili.c#L1-L47

come puoi vedere le variabili `primo` e `secondo` sono state dichiarate dentro la funzione `main()` e quindi sono locali, esattamente come `risultato` ed `operazione`. Solo `risultato` è inizializzato a zero, le altre variabili conterrrano all'inizio un valore casuale (le variabili locali non sono inizializzate automaticamente)

```c
int risultato = 0;
int primo, secondo;
char operazione;
```
















































































































