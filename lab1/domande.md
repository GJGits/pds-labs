```cpp
Message buf[10];
Message *buff2 = new Message[10];
```

1. Che differenza c'è tra queste due costruzioni di un array di Message?

Nel primo caso l'array viene memorizzato nello stack e viene distrutto al termine dello scope nel quale viene dichiarato, nel secondo caso l'array viene memorizzato nell'heap ed è compito del programmatore distruggere l'oggetto.