```cpp
Message buf[10];
Message *buff2 = new Message[10];
```

1. Che differenza c'è tra queste due costruzioni di un array di Message?

Nel primo caso l'array viene memorizzato nello stack e viene distrutto al termine dello scope nel quale viene dichiarato, nel secondo caso l'array viene memorizzato nell'heap ed è compito del programmatore distruggere l'oggetto.

2. Quale costruttore viene invocato?

Viene invocato in entrambi i casi il costruttore vuoto, non potrebbe essere altrimenti considerato il fatto che non si passano altri argomenti.

3. E' necessario fare la delete dei buffer ?

L'array buff1 viene distrutto automaticamente, mentre per buff2 è il programmatore a dover chiamare `delete [] buff2; `.

4. Cosa capita quando assegno un nuovo messaggio ad un elemento dell'array?

Viene chiamato l'operatore di assegnazione. I passaggi sono i seguenti:

- viene creato un oggetto di tipo `Message`, questo oggetto verrà utilizzato come se fosse un RValue, quindi un oggetto volatile.
- viene invocato l'operatore.
- l'oggetto generato con `Message(100)` viene distrutto.

5. Cosa capita se commento il costruttore di default?

Viene dato un errore di compilazione, il costruttore di default ci viene fornito in automatico dal compilatore se e solamente se non si hanno implementazioni di altri costruttori.

6. Se lo rendo privato?

Il costruttore viene dichiarato inaccessibile come può evidenziare l'intelliSense nella nostra IDE, analogamente se compilassimo.

```cpp
buff1[0] = Message(100);
```
Provare l'esempio precedente commentando gli operatori di assegnazione.

7. Compila?

L'intelliSense di VSCode fornisce un output significativo

> impossibile fare riferimento a funzione "Message::operator=(const Message &)" (dichiarato in modo implicito). È una funzione eliminata

8. E' tutto corretto?

Guardare la risposta precedente.

9. Disegnate su un foglio i blocchi di memoria allocati e simulate graficamente la copia.

Controllare immagine copia.jpg all'interno del repo.

10. C'è garanzia che due chiamate successive di queste funzioni diano valori monotoni crescenti? Perché?

La funzione `time()` fa riferimento ad un orologio per contare il tempo,  la funzione `clock()` invece conta il tempo come numero di tic del clock della cpu. Solo per la seconda funzione possiamo assumero un andamento monotono crescente in quanto un orologio può essere manomesso. Fatta questa premessa la funzione scelta è `clock()` ed i risultati evidenziano una netta superiorità dell'assegnazione per movimento che è circa due ordini di grandezza più veloce dell'assegnazione.

12. Come ottimizzare la riallocazione dell'array che contiene i messaggi man mano che cresce? Verificare quale operatore di Message viene utilizzato durante la copia tra il vecchio ed il nuovo array, misurate i tempi (testare sia operatore di assegnazione che di movimento).

In questo caso il movimento risulta più adatto, questo ci fa risparmiare in termini di memoria, se ne utilizza metà visto che non si duplica anche solo temporaneamente il contenuto, e fa risparmiare in termini di tempo come abbiamo già visto nella domanda 10. Nel codice il movimento è stato forzato tramite l'utilizzo di `std::move()`, se si vuole testare l'operatore basta convertire queste chiamate in assegnazioni normali tramite l'operatore `=` e poi decommentare la chiamata alla funzione di test chiamata `test_add()`.

13. Il metodo `get()` potrebbe presentarsi in vari modi alternativi. Ad esempio: 

```cpp

Message* get(long id); // 1
Message get(long id); // 2
Message & get(long id); // 3
std::optional<Message> get(long id); // 4
void get(int id, Message message); // 5
void get(int id, Message *message); // 6
void get(int id, Message **message); // 7
void get(int id, Message &message); // 8
void get(int id, const Message &message); // 9

```

Discutere per ciascuno di essi, pregi e difetti, indicando quali possono essere le varie problematiche che esso introduce.

| Method ID | Pros return | Cons return | Pros params | Cons param |
|   :----:  |   :----:    |   :----:    |   :----:    |   :----:   |
|     1     | restituisce un puntatore al messaggio ricercato, non è necessaria quindi una copia | restituire un puntatore in questo caso potrebbe essere un pericolo oltre che andare contro il design dell'app. Abbiamo `MessageStorage` che dovrebbe occuparsi degli accessi ai messaggi, in questo caso una modifica sul massaggio restituito va a sovrascrivere il messaggio contenuto nella struttura `messages`. Inoltre il puntatore potrebbe essere un `nullptr` con tutti i problemi annessi qualora si cercasse di accedervi in seguito | essendo `long` un tipo nativo non c'è miglior metodo per passare il messaggio | nessun contro | 
| 2 | in questo caso viene restituita una copia del messaggio, di conseguenza ogni modica effettuata dal chiamante non avrà ripercussioni sul messaggio presente nella struttura dati | I difetti di questo valore di ritorno sono due, il primo è che deve essere effettuata una copia del messaggio, il secondo è che se il messaggio non è presente si deve creare un messaggio vuoto da restituire | stessi pro del metodo 1| nessun contro |
| 3 | restituisce una reference all'oggetto. In termini di prestazioni equivale con il metodo 1, in questo caso però non si può avere `nullptr` | sostanzialmente stessi contro del metodo 1 | stessi pro del metodo 1 | nessun contro |
| 4 | Tipo aggiunto nella specifica `C++17` e già presente in altri linguaggia come `Java`. Sostanzialmente in questo caso si ha un wrapper dell'oggetto e il termine `optional` indica che il valore può essere presente o meno. Questo valore di ritorno ha il pro di non restituire l'originale oltre al fatto che riesce a rispecchiare in maniera naturale il tipo di contesto nel quale ci si trova, non è detto che l'id passato infatti corrisponda ad un messaggio | i contro di questo tipo di ritorno sono dal punto di vista prestazionale il fatto che è necessario effettuare una copia dell'oggetto, dal punto di vista del codice che richiede prevedere entrambi i casi cosa che però bisognerebbe comunque fare se si restituisse un puntatore. | stessi pro del metodo 1 | nessun contro |
5 | valore di ritorno più rapido in assoluto | per nulla adatto al contesto di una get | ok `long id` | pessima la scelta di `Message message`, non solo è necessario fare una copia del messaggio passato dal chiamante, dopo averci lavorato e presumibilmente aggiunto l'oggetto corrispondente a quell'id il chiamante si ritroverebbe con lo stesso valore iniziale |
| 6 | stesso del metodo 5 | stesso del metodo 5 | ok `long id` in questo caso il chiamante da un puntatore al messaggio che dovrà contenere quello cercato, al ritorno della funzione il chiamante si troverà con l'oggetto aggiornato | soluzione accettabile al parte il fatto che il puntatore potrebbe essere un `nullptr` e di conseguenza bisogna, nell'implementazione del metodo, tenere conto di questo caso |
7 | stesso del metodo 5 | stesso del metodo 5 | sostanzialmente il concetto è analogo al punto precedente con la differenza che qui si sta passando un array di messaggi | in questo caso non trovo utile passare un array di messaggi, complica inutilmente il codice oltre al fatto che se esiste un messaggio con questo array, allora esso sarà unico
8 | stesso del metodo 5 | stesso del metodo 5 | sostanzialmente stesso del punto 6 | nessun vero contro, in questo caso si passa una reference quindi non ci si preoccupa di `nullptr` |
9 | stesso del metodo 5 | stesso del metodo 5 | stessa cosa del metodo precedente, però in questo caso è leggermente ottimizzato grazie all'uso di `const` (il compilatore può tenerne conto e ottimizzare) | stesso del metodo precedente