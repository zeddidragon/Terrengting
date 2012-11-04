# TOD110  GRAFISKE METODER
## Øving6 uke 42-47 (Utlevert 18.10)
#### Høsten 2012 Sist oppdatert 18.12 (Oppgaven vil bli gradvis spesifisert)
## HØGSKOLEN I BERGEN AVDELING FOR  INGENIØRUTDANNING
### Formål

*    Scenegraf
*    Avanserte teknikker
*    Bidra til at alle i gruppen utvikler seg videre

### Krav til innleveringen

*    Øvingen utføres i grupper på inntil 3-4 medlemmer eller i stor-grupper (2 grupper).
*    Visning av kjøring tirsdag 28.11 3-4 t i klasserom - der alle er gruppemedlemmer er til stede.
*    Rapport/prosjektbeskrivelse, kildekode, (winzippet prosjekt), video av kjøring kanskje også med tale som forklarer prosjektet.

### Prosjektbeskrivelse 
    I tillegg til program skal det skrives 1-2 sider med prosjektbeskrivelse. Denne skal forklare
    programstrukturene,UML-klassediagram, objektdiagram, teknikker og metoder som har vært brukt og 
    videre en beskrivelse og hva de ulike klassene gjør. Forklaringene kan støttes av figurer.

### Innledning
    To og to grupper kan gjerne samarbeide om koden. Det gir her mulighet for å fordele stoffet 
    mellom dere.

### Oppgave
    Landskap med det meste av bestående av himmel med skyer, lys, fjell, mark, gress planter og 
    trær og vann.

*    Statisk skybox (Environment map)
     (GMTerrain har en skybox)
*    Reflection map (environment map)
*    Vann (dynamic reflection?)Trær  
    * 3D-modell av tre (kamera nært)
    * Imposters (Level of Detail, 3D-modell til FBO, 2D-tekstur(billboard))
      Ref: Gems3 (Se it,slearning)
*    Gress og blomster (bilboard, gjennomsiktighet relatert til avstand)
     Først tegnes opake, så transparente.                          
*    Shadow map (for 3D-modellene)
*    Bump map (detaljer for stein, bark i trær)
*    Partikkelsystem for å visualisere sommerfugler på en viss avstand
*    Vind (tidsfunskjon i vertex-shader som gir en animasjon av gress og blader på trær))
*    Fly i landskap med kamera langs en kurve.
     Modeller av trær blir lastet opp. For gress blir det enkle quads med tekstur.
     Vanntekstur kan dere finne på nettet.
