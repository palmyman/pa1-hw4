pa1-hw4
=======

Programming in C - Homework 4 (Water dispenser)

Úkolem je realizovat program, který umožní výpočet obsazení vodních nádrží.

Předpokládáme, že vodovodní společnost spravuje zásobníky na vodu. Každý zásobník má tvar kvádru a je propojen vodovodním potrubím s ostatními zásobníky. Celkem je takto propojeno mnoho zásobníků, víte, že jich je nejvýše 200000. Propojovací potrubí má pro účely výpočtu nulový objem. Situace je znázorněna na obrázku:

Program dostane takto definovanou síť zásobníků. Následuje zadání objemu vody obsaženého v zásobnících. Program určí nadmořskou výšku, do které bude sahat hladina vody.

Vstupem programu je počet zásobníků N (celé číslo). Pak následuje popis jednotlivých zásobníků. Zásobník je popsán čtveřicí celých čísel Alt H W D, kde Alt je nadmořská výška dna zásobníku, H je výška zásobníku, W je šířka zásobníku a D je hloubka zásobníku. Všechny velikosti jsou udané v metrech. Taková čtveřice je zadaná pro každý zásobník, na vstupu je tedy N čtveřic. Po zadání zásobníků následuje sekvence dotazů. Na vstupu jsou celá čísla udávající objem vody v zásobníku (v metrech kubických). Zadávání dotazů končí s koncem vstupu (EOF).

Výstupem programu je nadmořská výška hladiny pro každý zadaný objem vody. Pokud je objem nulový, je odpovědí "Prazdne", pokud se voda do zásobníků nevejde, je odpovědí "Pretece". Formát odpovědí je zřejmý z ukázek níže.

Program musí kontrolovat správnost vstupních dat. Pokud je detekovaný nesprávný vstup, program zobrazí chybové hlášení a ukončí se. Za chybu je považováno:

* počet zásobníků N nečíselný, záporný, nulový nebo větší než 200000,
* nečíselné zadání nadmořské výšky Alt,
* nečíselné, nulové nebo záporné rozměry zásobníku H, W nebo D,
* nečíselné nebo záporné zadání objemu uložené vody.
