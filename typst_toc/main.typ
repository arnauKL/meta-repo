// ------------------------- Configuració -------------------------

#set page(
  margin: 2.5cm,
  paper: "a4",
)

#show raw: set text(font: "Libertinus")

#set text(
  lang: "ca",
  hyphenate: true,
  size: 11pt,
  font: "FreeSerif",
)

#set par(
  first-line-indent: 1em,
  justify: true,
)


#let NOREF = text(red)[*??????*]

#let colorUdg = rgb("#001489")
// #set page(fill: rgb("444342"))
// #set text(fill: rgb("fdfdfd"))


// Per fer que les l geminades surtin millor amb New Computer Modern
//#show "l·l": it => [#text(font: "New Computer Modern Math")[l·l]]

// ------------------------- Portada -------------------------

#page(margin: 3cm)[

  // Barra lateral blava
  #place(
    horizon + center,
    dx: -25em,
    rect(fill: colorUdg, height: 130%, width: 20%),
  )

  // Logo de la uni
  #place(
    top + left,
    [
      #image("imatges/EPS.png", width: 50%)
      #text(14pt)[
        #smallcaps(
          [
            Grau en Enginyeria Biomèdica \
            Seguretat i Protecció de Dades
          ],
        )]

    ],
  )

  // Títol al centre
  #align(horizon + left)[
    #box(
      width: 80%,
      text(size: 32pt)[*DRM en Multimèdia i Continguts Digitals*],
    )
  ]

  // Noms i data
  #place(
    bottom + right,
    align(right)[

      _Professor:_ \ Antonio Bueno

      _Estudiant:_ \ Arnau K. Deprez \ #link("mailto:u1989064@campus.udg.edu", "u1989064")

      #v(1em)
      #datetime.today().display("[day] de Gener, [year]")
    ],
  )
]
#pagebreak()


#show link: it => underline[#emph(it.body)]

#box(
  // Índex
  inset: 2em,
  outline(),
)

- Razor o una empresa similar de ratolins posa DRM als seus ratolins El que fan
- algunes empreses com Nintendo pels USB-C, és drm?
- els cartutxos de les impresores -> DRM.
- Programari d'adobe funciona millor quan està crackejat perquè es pot fer
  servir offline.

#set page(
  header: align(right)[ #text(10pt)[_Treball de la Segona part: DRM_ ] ],
  numbering: "1",
)

// ------------------------- Document -------------------------


= Introducció

En les darreres dècades, la digitalització dels continguts multimèdia ha
transformat profundament la manera com es creen, es distribueixen i es
consumeixen obres audiovisuals, musicals i literàries. L'aparició de plataformes
de distribució digital i serveis de streaming ha facilitat un accés immediat i
global als continguts, però també ha incrementat els reptes relacionats amb la
protecció dels drets d'autor, la seguretat de la informació i el control de l'ús
no autoritzat. En aquest context, els sistemes de *Digital Rights Management*
(DRM) han esdevingut una eina clau per a la gestió i la protecció dels drets
sobre continguts digitals.

El DRM fa referència a un conjunt de tecnologies i mecanismes destinats a
controlar l'accés, la còpia i la distribució de continguts digitals. A través de
tècniques com el xifratge, la gestió de llicències i l'autenticació d'usuaris i
dispositius, aquests sistemes permeten als proveïdors de contingut definir com,
quan i en quines condicions es pot consumir una determinada obra. Tot i que el
DRM s'aplica en múltiples àmbits, el seu ús és especialment rellevant en el
sector multimèdia, on la còpia i la distribució no autoritzada poden
realitzar-se amb gran facilitat.

Malgrat els avantatges que ofereix en termes de protecció dels drets d'autor, el
DRM també genera controvèrsia. Les restriccions imposades als usuaris finals
poden afectar drets com la còpia privada, la interoperabilitat entre dispositius
o la preservació a llarg termini dels continguts digitals. A més, molts sistemes
DRM impliquen la recopilació d'informació sobre l'ús que fan els usuaris dels
continguts, fet que planteja qüestions rellevants en matèria de privacitat i
protecció de dades personals, especialment en el marc de la legislació europea
vigent.

Aquest treball té com a objectiu analitzar el funcionament dels sistemes DRM,
amb un enfocament especial en l'àmbit multimèdia i la seva relació amb la
seguretat i la protecció de dades. D'una banda, s'estudien els principis tècnics
i les tecnologies que sustenten aquests sistemes, així com les seves aplicacions
en plataformes de consum digital àmpliament utilitzades. D'altra banda, es
presenta una anàlisi crítica dels avantatges i limitacions del DRM, tenint en
compte tant la perspectiva dels proveïdors de contingut com la dels usuaris
finals.


#text(red)[
  Finalment, el treball inclou una part pràctica destinada a il·lustrar de
  manera aplicada alguns dels conceptes tractats al llarg de l'estudi. Aquesta
  part permet explorar, des d'un punt de vista experimental, com s'implementen
  o s'apliquen els mecanismes de protecció de drets digitals, així com
  reflexionar sobre la seva eficàcia i les seves implicacions en termes de
  seguretat i usabilitat.
]


// Objectius del treball

= Fonaments del DRM

== Definició formal de DRM

El _Digital Rights Management_ (DRM), o Gestió de Drets Digitals, es defineix
com un conjunt de tecnologies, protocols i sistemes de control d'accés que
s'utilitzen per protegir la propietat intel·lectual de les obres digitals. A
diferència de les mesures de seguretat tradicionals que busquen protegir la
confidencialitat de les dades durant el seu transport, el DRM té com a objectiu
mantenir el control sobre el contingut després que hagi estat lliurat a l'usuari
@adobe.

Des d'una perspectiva de seguretat de la informació, el DRM és una extensió del
model de control d'accés que vincula el contingut xifrat amb una llicència d'ús
específica, garantint que només els usuaris autoritzats puguin executar
determinades operacions (llegir, copiar, imprimir o visualitzar) sota condicions
predefinides.

L'eficàcia d'un sistema DRM es basa en la cooperació de tres parts.

- Control d'accés: És el mecanisme que impedeix la visualització o ús del
  contingut a qualsevol entitat que no disposi de les credencials adequades.
  Aquest control no acaba en el moment de l'obertura del fitxer, sinó que es
  manté de forma persistent durant tot el consum de l'obra.

- Autenticació d'usuaris i dispositius: El DRM modern no només autentica la
  identitat de l'usuari (mitjançant credencials de compte), sinó també la
  integritat del dispositiu o software de reproducció. S'utilitzen
  identificadors únics de hardware (HWID) i mòduls de desxifratge certificats
  per assegurar que l'entorn on es visualitza el contingut és "de confiança" i
  no permet captures o duplicacions.

- Gestió de llicències (_License Management_): És el component lògic que separa
  el contingut de les regles d'ús. Mentre que el contingut és un fitxer xifrat
  (normalment amb AES), la llicència és un objecte de dades separat que conté
  la clau de desxifratge i els metadades que defineixen els drets (p.ex:
  "vàlid fins a X" o "màxim 2 reproduccions").

== Arquitectura d'actors implicats

En un ecosistema DRM típic, la comunicació segueix un flux d'entitats
interconnectades per garantir la traçabilitat i la seguretat:

Proveïdor de contingut (Content Provider): És el propietari dels drets d'autor
(estudis de cinema, editorials, discogràfiques). La seva funció és proporcionar
el contingut original i definir les regles de negoci i restriccions que s'han
d'aplicar.

Distribuïdor (Distributor): Plataformes com Spotify, Netflix o Amazon. Són els
encarregats d'empaquetar el contingut original, xifrar-lo i distribuir-lo a
través de les seves xarxes (CDN). També gestionen la interfície de cara a
l'usuari i la passarel·la de pagament.

Servidors de Llicències (Clearing House / License Server): Actuen com
l'intermediari de confiança. Reben les peticions dels dispositius dels usuaris,
validen el seu dret a accedir al contingut i generen les claus de desxifratge
dinàmiques que s'envien de forma segura al client.

Usuari final i el Client DRM: L'usuari consumeix el contingut a través d'un
programari o hardware específic que conté un CDM (Content Decryption Module).
Aquest mòdul és l'única peça del sistema que pot manipular les claus i el
contingut en clar, sovint protegit dins d'un entorn d'execució aïllat del
sistema operatiu per evitar manipulacions.

Autoritats de certificació (CA): En sistemes d'alt nivell (com el vídeo 4K),
existeixen entitats que certifiquen que un model de televisor o de processador
és segur. Sense aquest certificat digital, el servidor de llicències es pot
negar a enviar contingut d'alta qualitat al dispositiu.


= El DRM en el sector multimèdia

L'aplicació del DRM no és uniforme. Depèn del tipus de contingut, del valor
econòmic de l'obra i dels acords de llicència entre els propietaris dels drets i
plataformes de distribució

== Vídeo en Streaming: Situació actual

En els vídeos s'apliquen els sistemes de DRM més robustos fet que és la
industria que més tem la pirateria. Actualment, el mercat està dividit per tres
tecnologies principals que actuen com a estàndards @callaba@vimeo tot i que n'hi
ha moltes més.

La tecnologia més reconeguda és Google Widevine. Utilitzada per Netflix,
Disney+, Amazon Prime Video i Youtube. És la més estesa perquè és compatible amb
una gran varietat de sistemes operatius i navegadors diferents. Una de les
característiques que el fa atractiu és que presenta tres nivells diferents
d'encriptació (L3, L2 i L1) progressivament més restrictius que s'explica més
avall.

Una altra tecnologia estesa és Microsoft PlayReady, molt comú a Windows i Xbox
fet que està desenvolupat per aquestes plataformes. Ofereix més models de
monetització.

Finalment hi ha Apple FairPlay, que és el sistema tancat d'Apple per iTunes,
AppleTV+ i Safari. Com només ha de dedicar els seus eforços a assegurar-se
compatibilitat amb un nombre reduit de dispositius, és molt robust i ofereix
bona experiència a l'usuari (comparat amb altres tecnologies).

=== El concepte de Nivells de Seguretat (Widevine):
Un aspecte clau en la seguretat de dades és el nivell de confiança del hardware.
Widevine, per exemple, divideix els dispositius en:

- L1 (Màxima seguretat): El desxifratge es fa totalment dins del TEE (Trusted
  Execution Environment) del processador. És l'únic que permet reproduir
  contingut en 4K.

- L3 (Seguretat per software): El desxifratge es fa per software, el que el fa
  més vulnerable a captures de pantalla o rippeig. Per això, moltes
  plataformes limiten la resolució a 480p o 720p en dispositius L3 (com molts
  PCs amb Linux o mòbils xinesos de gamma baixa).


== Àudio

A diferència del vídeo, la indústria musical ha relaxat el DRM en les vendes
directes (com els MP3 d'Amazon o Bandcamp, que no en porten), però l'ha blindat
en els models de subscripció (Spotify, Apple Music, Tidal).

El xifratge de flux (_streaming_). Per escoltar música amb Spotify, la música
arriba xifrada en petits paquets. L'aplicació té la clau per desxifrar-los en
temps real, però l'usuari no pot _veure_ el fitxer original.

Per contra, les cançons que l'usuari té _"descarregades"_ (entre comes) per
poder escoltar cançons sense internet, són guardades per Spotify en un fitxer
xifrat al disc dur. Si l'usuari deixés de pagar la subscripció, l'aplicació
_oblida_ la clau i el fitxer es torna inservible, tot i que segueixi ocupant
espai al dispositiu.

== Llibres electrònics (E-books): Jardins tancats

El mercat dels llibres digitals o _e-books_ és on la fragmentació del DRM és més
evident per a l'usuari final, creant el que s'anomena _vendor lock-in_
(dependència del proveïdor).

Amazon Kindle: Utilitza un format propietari (AZW o KFX) amb un DRM propi. Un
llibre comprat a Amazon només es pot llegir en un dispositiu Kindle o en la seva
app.

Adobe Digital Editions (ADE): És l'estàndard per a la resta de la indústria
(Kobo, Google Play Books, biblioteques públiques). Utilitza el format EPUB
protegit amb el DRM d'Adobe. Requereix que l'usuari creï un "ID d'Adobe" per
autoritzar el dispositiu, vinculant el llibre a una identitat digital i no al
fitxer en si.

A la part pràctica s'explora més profundament la part del DRM en llibres
digitals.


= Tecnologies utilitzades en DRM // Seccio4

// Xifratge de continguts (AES, RSA – a nivell conceptual)
// CDM: Content Decryption Module
// Claus de sessió
// Servidors de llicències
// Autenticació de dispositius
// Watermarking digital (marques d'aigua visibles i invisibles)

= DRM vs drets dels usuaris i protecció de dades

//Part crítica i molt valorada acadèmicament.

//Problemes del DRM:
//  Restricció del dret de còpia privada
//  Dependència de plataformes
//  Obsolescència del contingut
//Implicacions de privacitat:
//  Seguiment d'ús
//  Identificació de dispositius
//Relació amb:
//  RGPD
//  Drets digitals del consumidor
//Ampolla de dades. Perquè el DRM funcioni, el servidor ha de saber qui ets, quin dispositiu tens i què estàs mirant en tot moment. Això xoca directament amb el principi de minimització de dades del RGPD

== Limitacions habituals i impacte en l'usuari

Les restriccions imposades per aquestes tecnologies sovint entren en conflicte
amb la seguretat i la comoditat de l'usuari.

Per exemple, la majoria de sistemes DRM limiten el contingut a un màxim de 5 o 6
dispositius autoritzats simultàniament. Això genera problemes quan un usuari
renova el seu mòbil o ordinador i perd una "llicència" en un dispositiu vell que
ja no funciona.

Per altra banda, tot això es per quan es passa al món de les ones: l'Analog Hole
(El forat analògic) que ja s'ha esmenat a classe. Per molta seguretat que hi
hagi, si un so surt per un altaveu o una imatge per una pantalla, pot ser
gravada. El DRM intenta combatre-ho bloquejant les sortides de vídeo no xifrades
(com els cables VGA antics) i obligant a fer servir HDMI amb HDCP
(_High-bandwidth Digital Content Protection_).

Finalment també Dependència de servidors (Kill Switch): Si l'empresa que
gestiona el DRM fa fallida o decideix tancar el servei, l'usuari perd l'accés a
tot el que ha _"comprat"_. És la transició definitiva del concepte de
"propietat" al de "llicència d'ús temporal".
= Alternatives al DRM tradicional

//DRM “light”
//Watermarking com a alternativa
//Models basats en confiança
//Open Access i Creative Commons
//Comparació amb DRM fort

= Part pràctica

La part pràctica consistirà en analitzar com s'aplica el DRM en els llibres
digitals o _ebooks_.

He descarregat el llibre _The Adventures of Tom Sawyer_ (Les aventures de Tom
Sawyer), de Mark Twain en format `.epub` de la web del projecte Gutenberg #NOREF
.

Els arxius `.epub` no són altra cosa que arxius `.zip` amb l'extensió canviada.
Per veure el contingut que contenen es pot descomprimir l'arxiu com qualevol
altre arxiu comprimit i a dins descobrim tots els continguts del llibre en text
clar (`.xhtml`).

Per tal d'il·lustrar-ho, he descomprimit el llibre de Mark Twain i,
efectivament, tot el que hi trobem a dintre és una carpeta amb els estils,
capítols i imatges del llibre i una altra amb metadades (veure @treeEpub).

#figure(
  ```bash
  $ unzip tom-sawyer.epub
  $ tree
  .
  ├── META-INF
  │   └── container.xml
  ├── mimetype
  └── OEBPS
      ├── 0.css
      ├── 1.css
      ├── 5054904921574492985_74-h-0.htm.xhtml
      ├── ... # tots els capítols
      ├── 5054904921574492985_74-h-39.htm.xhtml
      ├── 5490705198151656392_01-017.jpg
      ├── ... # totes les imatges
      ├── 5490705198151656392_35-271.jpg
      ├── 5490705198151656392_bookcover.jpg
      ├── 5490705198151656392_cover.jpg
      ├── 5490705198151656392_dedication.jpg
      ├── 5490705198151656392_frontispiece.jpg
      ├── 5490705198151656392_spine.jpg
      ├── 5490705198151656392_titlepage.jpg
      ├── content.opf
      ├── pgepub.css
      ├── toc.ncx
      ├── toc.xhtml
      └── wrap0000.xhtml

  3 directories, 216 files
  ```,
  caption: [ Estructura de fitxers dintre de l'arxiu `.epub` descomprimit ],
)<treeEpub>

Aquests arxius es poden obrir amb qualevol editor de text per veure'n el
contingut (@capitol27).

#figure(
  box(
    image("imatges/capturaxml.png"),
    inset: 1em,
  ),
  caption: [ Capítol 27 en text pla. ],
)<capitol27>


- KOBO EPUB is a thing
- MOBI is its own propietary garbage + DRM protected

- Calibre cannot convert from


= Conclusions

//Valoració crítica del DRM
//Impacte real en la seguretat
//Futur del DRM
//Opinió personal raonada


Segurament al llarg del treball s'ha pogut intuir la meva posició al respecte
d'aquestes tecnologies.

#figure(
  box(
    image("imatges/jailbrokenKindle.jpeg", width: 50%),
    inset: 1em,
  ),
  caption: [Els meus gats _Sawyer_ i _Bolleke_ a la pantalla de bloqueig del
    meu kindle rootejat.],
)

Una que m'agrada molt i que trobo que és bona per il·lustrar els problemes defer
servir tecnologies d'aquest tipus és del co-fundador de Valve, Gabe Newell.

#NOREF



// ------------------------- Referències -------------------------

#pagebreak()

#bibliography("fonts.bib")

Electronic Frontier Foundation (EFF): Tenen una secció anomenada "Digital Rights
Management" on expliquen per què el DRM pot ser perillós per a la seguretat (per
exemple, si el servidor de llicències tanca, perds el que has comprat).

Cory Doctorow: És un autor i activista molt famós que ha escrit extensament
sobre per què el DRM no atura la pirateria però sí que perjudica l'usuari legal.

W3C (World Wide Web Consortium): Busca sobre l'estàndard EME (Encrypted Media
Extensions). Va ser molt polèmic quan el W3C el va acceptar com a part de
l'HTML5.


Articles acadèmics Webs oficials Legislació Llibres o whitepapers

= Lectures addicionals

- Llibre the pig and the box


#let data = yaml("fontsAdicionals.yaml")

#grid(
  row-gutter: 2em,
  column-gutter: 2em,
  columns: (auto, 5fr),
  ..data
    .referencies
    .map(
      entrada => (
        link(entrada.url, entrada.nom),
        [#entrada.descripcio #v(-1.5em) \
          Disponible a #link(entrada.url). Data de consulta:
          #entrada.data-consulta.
        ],
      ),
    )
    .flatten()
)
