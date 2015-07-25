Daniela Dorneanu 342 C3 
T1 - Programare Web

Cuprins:

1. Continutul arhivei
2. Mod de testare
3. Detalii de implementare

1. Continul arhivei:

   a) Fisierele de include
   - includes.inc.php;
   - constants.inc.php
   - interfaces.inc.php

   b) Clasele implementate - dupa specificatiile temei
   - excetions.class.php
   - Item.class.php;
   - ItemFactory.class.php
   - Collection.class.php;
   - CollectionFactory.class.php
   - SingletonDB.class.php

   c) Implementarea scriptului de testare
   - index.php;
   - script.php - scriptul care implementeaza actiunea formularului din index.php

   d) Baza de date folosita in scriptul de testare
   - tema_1.sql - ce contine o baza de date cu tabelele mele. Tebelele sunt realizate
   in vederea obtinerii unui site de licitatii. In index.php am afisat tabele obiecte
   si m-am folosit si de tabelele la care tabela obiecte are chesti straine;

   e) Testerul standard
   - tester.php
   - testerLib.inc.php

   f) Readme
   - readme.txt - acest fisier

2) Mod de testare

   a) Clasele Item, Collection si SingletonDB  respecta cerintele temei - am implementat toate
   metodele din interfete. La rularea testerului am primit 90 de puncte.
   b) Implementarea scriptului de testare
   - Default - itemsPerPage = 10. Aceasta valoare se poate schimba din script.php
   - Pentru a vedea mai multe pagini - selectari tipul de obiect - "automobile",
      in index.php

3) Detalii de implementare
   Implementarea este destul de standard - si am urmat exemplele din laborator;

   a)clasa Item
   - in contructor 
      - selectez tabela si arunc exceptii in caz ca tabela respectiva nu exista;
      - selectez o inregisrare din tabele cu id-ul cerut si o adaug la array-ul global de proprietati al tabelei;
   - metodele magice _get si _set
      - _get = verific daca proprietatea data exista in setul de proprietati globale 
      format in constructor. Daca da atunci returnez valoarea
      - _set = fac aceeasi verificare ca la get si apoi updatez in baza de date noua
      valoare a proprietatii;
   - populate - inserez noua inregistrare in baza de date;

   b)clasa Collection
   - in constructor
      - setez campurile primite ca parametru al constructurului ca valori ale atributelor locale
      - apelez functia refresh
   - in refresh
      - construiesc query-ul pe baza tuturor restrictiilor primite
      - adaug eventual orderBy
      - si setez itemsPerPage, respectiv startIndex
   - getNumberOfPages - returnez numerul de pagini
   - hasNext - verific daca in tebele mai exista inregistrari in baza de date dupa restrictiile specificate
   - next - returnez urmatoarea inregistrare;

   c) clasa SingletonDB - designPattern Singleton
   - connect - daca mai exista o conexiune deschisa - o returnez;
             - altfel returnez conexiunea existenta


multumesc,

Daniela
