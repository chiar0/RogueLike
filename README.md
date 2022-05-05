# RogueLike - PROGETTO 2021/2022
CONSEGNA E DISCUSSIONE

Il gruppo consegna:
  - Codice (sorgenti e binari)
  - File README
  - Screen recording che mostri l'esecuzione del gioco
  - Breve relazione (3/4 pagine) in cui si descrivono le principali scelte nell’implementazione del progetto e la suddivisione del lavoro tra i vari componenti del    gruppo

CONTENUTI DEL GIOCO

- Si richiede di implementare un gioco platform in grafica ASCII
- Sviluppato su più livelli
- A punteggio
- Il protagonista viene controllato da tastiera
![Cattura](https://user-images.githubusercontent.com/97366638/166899869-38740a1f-aa10-4d9a-a249-050341a05dd1.PNG)

SVOLGIMENTO DEL GIOCO

Requisiti minimi e obbligatori:
  - La mappa viene esplorata man mano dal giocatore
  - Non esistono traguardi
  - Il protagonista può tornare indietro nella mappa e trovare esattamente tutto come lo ha lasciato
  - Devono essere presenti diversi tipi di nemici e diversi tipi di artefatti
  - Per passare da una stanza all’altra è necessario prendere artefatti/sconfiggere nemici
  - È possibile trovare “poteri” per sbloccare passaggi che portano ad artefatti

IL PUNTEGGIO

- Il giocatore umano controlla il protagonista
- Il protagonista ha un punteggio vita e cuori; a 10 punti vita corrisponde un cuore
- Nel percorso il protagonista incontra nemici, artefatti e poteri:
  - I nemici tolgono cuori; diversi tipi di nemici tolgono diverse quantità di cuori
  - Gli artefatti aumentano la vita
  - I poteri sbloccano passaggi che portano ad artefatti, ripristinano vita se in precedenza si è stati colpiti da un nemico e/o aprono porte delle stanze
- I nemici sono controllati dal computer: si possono muovere e sparare, possono venire uccisi dal protagonista (es. sparando)
- La mappa ha una visuale dall’alto ed è divisa in stanze; le stanze hanno più ingressi/uscite (porte)
- Quando la vita del protagonista scende a 0 il gioco termina

IMPOSTAZIONE DEL PROGETTO

Vincoli:
  - La mappa deve avere una grafica ASCII, è possibile utilizzare solo le librerie curses/ncurses.h per gestire la grafica
  - Gli elementi delle stanze devono essere gestiti tramite strutture dati dinamiche (prevedendo, quindi, inserimento e rimozione)
- Il progetto deve essere realizzato usando le classi
- Il progetto è organizzato in più file
- Ad ogni classe corrispondono due file: NomeClasse.cpp e NomeClasse.hpp

ESEMPIO FILE

ESEMPIO DI FILE

NomeClasse.hpp

  class NomeClasse{
  
  protected:
  
  int field;
  
  ...
  
  public:
  
  ...
  
  void method();
  
  ...
  
  };
  
NomeClasse.cpp

  #include "NomeClasse.hpp"
  
  void NomeClasse::method(){
  
  // do something
  
  }
  
IN OGNI FILE IN CUI SI USA IL TIPO “NOMECLASSE” BISOGNA IMPORTARE NOMECLASSE.HPP
