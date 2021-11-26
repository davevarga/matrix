# matrix
This is a module that allows you to use algebra functinos with matrices, such as substractio, multiplication, and even gauss eliminatino

Description in Hungarian:

Beolvasás:

A mátrixok beolvasása file-okból történik. A file első sorában a két szám a beolvasandó mátrix 
méretét képviseli, az első szám a sorok száma (n), a második pedig az oszlopok száma (k). A 
következő n sorban, soronként k darab valós szám található space-el elválasztva, ezek képviselik a 
mátrix tartalmát. A mátrix beolvasására szolgáló függvény paraméterként megkapja a file nevét, 
amiből a beolvasás történik, ott kinyitja kiolvas belőle pontosan egy mátrixot, majd bezárja. 
Visszatéritési értékként visszakült egy mátrixra mutató pointert ha sikeres a művelet, ellenkező 
esetben pedig a NULL pointert.
Beolvasás közben, a függvényen belül foglalódik le a tárhely ahova le lesznek mentve a mátrixbeli 
adatok. A Mátrix típusú változó három mezőből áll, a mátrix tartalma (.elm), ami egy kétdimenziós 
tömbre mutató pointer, illetve a mátrix méretét képviselő egész számok: a sorok száma (.nrw) és az 
oszlopok száma (.nlclmn).
Ezen kívü l rendelkezésünkre áll az is, hogy kiirassuk a fügvényeket az stdio termináljába, az mprintf() 
függvény keretein belül. Ez az eljárás paraméterként fogad egy Mátrix tipusú változót, mely 
tartalmát megjeleníti a terminálba, formatált módon, minden sor és oszlop között üres helyet 
hagyva.
Függvények használata: 

Sum(): 

A sum függvény paraméterként megkapja a két összeadandó mátrixot majd a függvény belsejében 
elemenként összeadja ezeket majd visszatéríti az eredmény mátrixot. Fontos hogy a paraméterként 
megkapott mátrixon nem végez módosítást. A függvény csak azonos méretű mátrixok között tudja 
értelmezni az összeadást, ezért erre a felhasználó különös tekintettel kell legyen mert nem kezel 
mérethibát. 

Sub(): 

Hasonlóan a sum() függvényhez, a sub() a paraméterként megkapott mátrixok között különbséget 
számol, pontosabban az elsőből kivonja a másodikat majd az eredmény mátrixot visszatéríti. 
Továbbra sem értelmezi a méreteltérést a mátrixok között.

Mult(): 

A mátrixok szorzására szolgáló függvény első paraméterében megkapott mátrix egy sorát 
elemenként összeszorozza a második mátrix egy oszlopával majd a mintermeket osszeadja. Az 
eredmény mátrix sor és oszlopszámát megkapja az első mátrix sorszámából és a második mátrix 
oszlopszámából. A felhasználónak vigyáznia kell hogy az első mátrix oszlopszáma azonos legyen a 
második mátrix oszlopszámával. 

Trans(): 

A működése se eléggé egyszerű. A főátló fölötti értékeket kicseréli a megfelelő főátló alattival A[i][j] 
<-> A[j][i]. A függvény a mátrix sorszámát és oszlopszámát is felcserélni. Az eredmény mátrixot 
visszatéríti visszatérítési értékként. Fontos hogy nem minden elemét cseréli ki a megadott módon 
hanem csak a főátló fölöttieket mert ha mindkét oldalon elvégezzük a cserét akkor visszaállítjuk a 
mátrixot (Egy mátrix tanszponáltjának a transzponáltja az önmaga a mátrix). 

Det():

Ez a fügvény arra a matematikai tulajdonságra épül hogy a determinánsokat fel lehet bontani egy 
oszlop vagy egy sor szerint több kisebb determinánsra. Megegyezés szerint az utolsó sor szerint 
bontja fel a következő módon: (-1)^(i+j) * aij * annak a mátrixnak a determinánsa amelyik nem 
tartalmazza az i-edik sort és a j-edik oszlopot. Az utóbbit ugyanez függvény számol ki rekurzív 
módszert alkalmazásával addig, amíg egy 1x1-es determinánst kapunk, melynek értéke önmaga. Így 
az egyetlen paraméterként kapott mátrixnak kiszámítja a determinánsát amit visszatérítési értéke 
továbbítja. Vigyázat mivel determinánst csak négyzetes mátrixokból lehet számolni. Ennek helyes 
használata is a felhasználó felelősége. 

Conj(): 

Egy módosított det() függvény amely nem veszi figyelembe az aij értékét csak (-1)^(i+j) * az a 
determináns amelyik nem tartalmazza az i-edik és a j-edik sort. Ez a függvény nem rekurzív mivel 
elemenként determinánst számol nem pedig conjugáltat, a det() függvényt felhasználva. A függvény 
csak négyzetes mátrixokat értelmez, amire a felhasználó különös tekintettel kell legyen. 

Inv(): 

Az elözőleg definiált det() függvény 0 értéke esetén kiír egy hibajelzést, mivel matematikailag ennek 
a mátrixnak nincs értelmezve inverz mátrix. Különben kiszámítja a mátrix transzponáltját, majd 
konjugáltját a trans() es conj() függvények segítségével. Az inverz mátrix 1/det() * conj() lessz 
egyenlő. A felhasználó felelősége hogy négyzetes mátrixot adjon át. 

GaussEliminacio(): 

Gauss mátrixokra alkalmazott matematikai algoritmusára épül melynek feladata egyenletrendszerek 
megoldása. Fontos hogy az utolsó oszlop a szabadtagok oszlopa amire különös figyelemmel kell 
lenni. A két fázisbók álló algoritmus első fázisa a főátló mentén vezéregyeseket alkot amelyek alatt 
csak 0-k találhatók amíg kifogy a sorokból vagy az oszlopokból. Ezt úgy valósítja meg hogy minden 
sort leosztunk a főátlón lévő értékkel, így 1-est alkotva (innen jön a vezéregyes) Ezek után 
megnézzük ha van 0-tól különböző érték a vezéreggyes alatt. Ha van akkor ezzel az értékkel 
megszorozzuk a vézéreggyes sorába lévő összes értéket és kivonjuk elemenként az adott sorból. (Pl: 
a vezereggyes az i sor j oszlopába található es találtunk egy x nullátol különböző értéket a j oszlop k 
sorában. Akkor az i sort beszorozzuk x-el és a k sor megfelelő eleméből kivonjuk ezt) Ha a ciklus azért 
ál meg mert elért az utolsó elötti oszlopig (azaz az utolsó ismeretlenes) az azt jelenti hogy van egy 
olyan sor ami csupa 0. Ha a szabadtag is 0 akkor ezt a sort elhanyagolhatjuk mert nem bír semmilyen 
információval ha viszont nem akkor azt jelenti hogy kaptunk egy tilos sort, azaz az egyenletrenszer 
nem megoldható. Abban az esetben amikor a főátló mentén 0-át találunk akkor megnézzük hogy ha 
az alatta lévő sorok közül van olyan az oszlopban amelyik különbözik 0-tól. Ha van akkor a két sort 
teljessen felválthatjuk anélkül hogy elrontanánk az eddigi alakításokat. Abban az esetben, viszont, ha 
nincs az oszlopindexet növeljük eggyel így eltolva a főátlót amin haladunk tovább. Ezt az oszlopot 
paraméter oszlopnak nevezzük. Folytatólagosan a második fázis a vezéregyesek felett alkot 0-àsokat. 
Hasonlóan az első fázishoz a második is 0-ázással foglalkozik, csak most a vezéreggyes fölötti részt 
nullázzuk lentről felfelé. 

Rang(): 

A Gauss elimináció algoritmusát felhasználva a vezéregyesek száma adja meg a mátrix rangját. 
Vigyázat hogy nem minden vezér egyes található a főátlón, és nem minden egyes vezéregyes. Tehát 
a vezéregyesek azok az egyesek amelyektől balra csak 0-ák találhatóak.
