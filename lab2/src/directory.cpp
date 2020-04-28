#include "lib/directory.h"

/**
 * elenca ricorsivamente File e Directory figli della directory 
 * corrente, indentati in modo appropriato.
 * 
 * @indent: numero di spazi
 */
const void Directory::ls(int indent)
{
}

/**
 * restituisce il tipo dell’istanza (Directory o File) codificato come intero ?
 * 
 * @return: tipo oggetto
 */
const int Directory::mType()
{
    return 0;
}

/**
 * restituisce uno smart pointer all’oggetto (Directory o File) 
 * di nome “name” contenuto nella directory corrente. Se inesistente, 
 * restituisce uno shared_ptr vuoto. I nomi speciali “​..​” e “​.” permettono 
 * di ottenere rispettivamente lo shared_ptr alla directory genitore di 
 * quella corrente, e quello all’istanza stessa.
 * 
 * @name: riferimento al nome dell'oggetto da cercare
 * 
 * @return: weak_ptr all'oggetto trovato, eventualmente vuoto se non si 
 *          riscontra nessun match
 */
std::weak_ptr<Base> Directory::get(const std::string &name)
{
    return std::shared_ptr<Base>();
}

/**
 * funziona come il metodo get(nome), facendo un dynamic_pointer_cast 
 * dal tipo Base al tipo Directory
 * 
 * @name: riferimento al nome dell'oggetto da cercare
 * 
 * @return: weak_ptr all'oggetto trovato, eventualmente vuoto se non si
 *          riscontra nessun match
 */
std::weak_ptr<Directory> Directory::getDir(const std::string &name)
{
    return std::shared_ptr<Directory>();
}

/**
 * funziona come il metodo get(nome), facendo un dynamic_pointer_cast 
 * dal tipo Base al tipo File
 * 
 * @name: riferimento al nome dell'oggetto da cercare
 * 
 * @return: weak_ptr all'oggetto trovato, eventualmente vuoto se non si
 *          riscontra nessun match
 */
std::weak_ptr<File> Directory::getFile(const std::string &name)
{
    return std::shared_ptr<File>();
}

/**
 * crea, se ancora non esiste, l’oggetto di tipo Directory e ne 
 * restituisce lo smart pointer.
 * 
 * @return: shared_ptr alla cartella root
 */
std::shared_ptr<Directory> Directory::getRoot()
{
    /*
    if (Directory::root.use_count() == 0)
        Directory::root = std::shared_ptr<Directory>(heap("/"));
    return root;
    */
    return std::shared_ptr<Directory>();
}

/**
 * crea un nuovo oggetto di tipo Directory, il cui nome è desunto dal parametro, 
 * e lo aggiunge alla cartella corrente. Se risulta già presente, nella cartella corrente, 
 * un oggetto con il nome indicato, restituisce uno smart pointer vuoto lo stesso vale
 * per i nomi riservati ‘.’ e ‘..’
 * 
 * @name: nome oggetto da creare
 * 
 * @return: shared_ptr all'oggetto appena creato
 */
std::shared_ptr<Directory> Directory::addDirectory(const std::string &name)
{
    /*
    std::shared_ptr<Directory> child = makeDir(name, this->self);
    this->children.insert(std::make_pair(name, child));
    return child;
    */
    return std::shared_ptr<Directory>();
}

/**
 * aggiunge alla Directory un nuovo oggetto di tipo File, ricevendone 
 * come parametri il nome e la dimensione in byte; l’aggiunta di un File con 
 * nome già presente nella cartella corrente non è permessa e fa restituire 
 * uno smart pointer vuoto lo stesso vale se si tenta di creare un file con 
 * uno dei nomi riservati ‘.’ e ‘..’.
 * 
 * @name: riferimento al nome del file da creare
 * @size: dimensione in byte del file
 * 
 * @return: shared_ptr all'oggetto appena creato
 */
std::shared_ptr<File> addFile(const std::string &nome, uintmax_t size)
{
    return std::shared_ptr<File>();
}

/**
 * rimuove dalla collezione di figli della directory corrente l’oggetto 
 * (Directory o File) di nome “nome”, se esiste, restituendo true. 
 * Se l’oggetto indicato non esiste o se si tenta di rimuovere “​..​” e “​.” 
 * viene restituito false.
 * 
 * @name: riferimento al nome dell'oggetto da eliminare
 * 
 * @return: boolean che indica se l'eliminazione e' andata a buon fine
 */
bool remove(const std::string &name)
{
    return false;
}

// todo: valutare se necessario
std::shared_ptr<Directory> Directory::makeDir(std::string name, std::weak_ptr<Directory> parent)
{
    Directory *d = new Directory(name);
    std::shared_ptr<Directory> dir(d);
    dir->self = dir;
    dir->parent = parent;
    return dir;
}
