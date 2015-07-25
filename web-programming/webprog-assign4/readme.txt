Daniela Dorneanu 342C3

In folder se afla toate documentele din enuntul temei.

Fisierele modificate sunt 
- index.html - am adaugat la Who Starts and Human marker un tag cu valoarea "" asa cum era de altfel si la Game Type.
   Tot legat de fereastra de dialog pot sa adaug ca am observat ca spre deosebire de Chrome, 
   Firefox pastreaza intr-un cache ce optiune a fost aleasa ultima data in selecturi. 
   (desi am instalat pluginul de jonny cache).

- in custom.css am adaugat alte dimensiun pentru square.
- in dialog.cs am implementat functionalitatea ferestrei de dialog.
- in jquery.xo.js am implementat functionalitatea jocului.

Algorimul de mutare al computerului este urmatorul
- daca are 2 la rand va pune si 3-a mutare
- Atunci cand este in situatia de a pierde la urmatoarea mutare (human are se afla la un pas de victorie) va incerca 
puna markerul astfel incat sa-l impidice pe adversar sa castige.
- Alfel va incerca sa puna markerul in centrul tablei
- Altfel (daca centrul tablei e ocupat)
   - va incerca sa puna markerul pe o linie pe care adversarul nu are inca nici un marker.
   - altfel va incerca sa puna markerul pe o coloana pe care adversarul nu are nici un marker
