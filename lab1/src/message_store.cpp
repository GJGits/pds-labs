#include <utility>
#include "lib/message_store.h"

/**
 * Genera un buffer di messaggi inizialmente vuoti.
 * 
 * @param n Dimensione iniziale del buffer
 */

MessageStore::MessageStore(int n) : dim{n}, n{n}
{
    this->messages = new Message[n];
}

MessageStore::~MessageStore()
{
    delete[] messages;
    this->messages = nullptr;
}

/**
 * Inserisce un nuovo messaggio o sovrascrive quello precedente se ce n'è 
 * uno presente con lo stessto id.
 * 
 * @param m reference al messaggio m
 */

void MessageStore::add(Message &m)
{
    // impedisco che vengano aggiunti messaggi vuoti. I messaggi vuoti presenti nel buffer
    // saranno dovuti al fatto che il buffer deve essere un multiplo di n.
    if (m.getId() != -1)
    {
        // 1. Ho ancora spazio ed aggiungo il messaggio
        for (int i = 0; i < dim; i++)
        {
            if (this->messages[i].getId() == -1)
            {
                this->messages[i] = std::move(m);
                return;
            }
        }
        // 2. Il buffer e' pieno, rialloco ed aggiungo
        this->dim += this->n;
        Message *temp = new Message[this->dim];
        Message *vuoto = new Message[this->n];

        for (int i = 0; i < (this->dim); i++)
        {
            temp[i] = (i < this->n) ? std::move(vuoto[i]) : std::move(this->messages[i - this->n]);
        }

        delete[] this->messages;
        this->messages = new Message[this->dim];

        for (int i = 0; i < (this->dim); i++)
        {
            this->messages[i] = std::move(temp[i]);
        }

        delete[] temp;
        delete[] vuoto;
        this->add(m);
    }
}

/**
 * Resituisce il messaggio dato il suo id.
 * 
 * @param id id del messaggio da ricercare
 * @return messagio se trovato
 */
std::optional<Message> MessageStore::get(long id)
{
    for (int i = 0; i < this->dim; i++)
    {
        if (this->messages[i].getId() == id)
        {
            return std::optional<Message>{this->messages[i]};
        }
    }
    return std::nullopt;
}

/**
 * Rimuove il messaggio dato il suo id. La cella di memoria nel
 * buffer corrispondente a questa posizione viene resettata, ma
 * questa chiamata non genera un ricompattamento della struttura
 * dati.
 * 
 * @param id id del messaggio da ricercare.
 * @return true se il messaggio è stato trovato e correttamente eliminato,
 *         false altrimenti.
 */
bool MessageStore::remove(long id)
{
    for (int i = 0; i < this->dim; i++)
    {
        if (this->messages[i].getId() == id)
        {
            Message vuoto{};
            this->messages[i] = std::move(vuoto);
            return true;
        }
    }
    return false;
}

/**
 * Restituisce il numero di messaggi validi e di elementi vuoti ancora disponibili.
 * 
 * @return tupla contenente rispettivamente numero messaggi validi, numero celle vuote.
 */
std::tuple<int, int> MessageStore::stats()
{
    int valide = 0;
    for (int i = 0; i < this->dim; i++)
    {
        valide += this->messages[i].getId() != -1 ? 1 : 0;
    }
    return std::tuple<int, int>(valide, this->dim - valide);
}

/**
 * Compatta l'array eliminando le celle vuote e riporta l'array alla dimensione multiplo
 * di n minima in grado di contenere tutte le celle
 */
void MessageStore::compact()
{
    Message *temp = new Message[this->dim];
    for (int i = 0; i < this->dim; i++) {
        temp[i] = std::move(this->messages[i]);
    }
    int tempDim = this->dim;
    delete [] this->messages;
    this->messages = new Message[this->dim];
    this->dim = this->n;
    for (int i = 0; i < tempDim; i++) {
        this->add(temp[i]);
    }
    delete [] temp;
}

int MessageStore::getN()
{
    return this->n;
}

int MessageStore::getDim()
{
    return this->dim;
}
