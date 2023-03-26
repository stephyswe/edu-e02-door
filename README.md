Uppgift 2. Administrationssystem dörr - Väl Godkänt kritierium ink. Fil - v.1.1

# Innehållsförteckning

- Beskrivning
- Kravspecifikation
- Programmet
- Filstruktur

## Beskrivning

Programmet "Administrationssystem dörr" är ett inpasseringssystem där besökaren scannar sitt kort. Besökaren kan välja fyra menyval som är kopplade till olika funktioner. Eftersom många funktioner är liknande i både "main"- och "vg-file"-grenarna, läggs ett "*" till i avsnitt 'Filstruktur' för att visa att funktionen finns tillgänglig i båda grenarna.


```
Admin menu
1. Remote open door
2. List all cards in system
3. Add/Remove access
4. Exit
9. FAKE CARD TEST SCAN
```

### 1: Remote open door

När man väljer denna ska systemet öppna dörren, “visas” genom GRÖN lampa enl nedan. Dörren ska vara öppen (grön lampa) i 3 sekunder

```
CURRENTLY LAMP IS:Green
```

### 2: List all cards in system

Lista ALLA kortnummer och skriv om dom har access eller INTE. (1212 har access, 1213 har nekats samt DATUM när dom lades till i systemet)

```
All cards in system
1212 Access Added to system: 2019-10-19
1213 Access Added to system: 2019-10-19
Press key to continue
```

### 3: Add/remove access

```
Enter cardnumber>1212
This card has access
Enter 1 for access, 2 for no access
```

Här ska kort eventuellt skapas ifall det inte redan finns

### 4: Exit

Avslutar programmet

### 9: Fake card test scanning

```
Please scan card to enter or X to back to admin mode
CURRENTLY LAMP IS: Off
```

```
Please scan card to enter or X to back to admin mode
CURRENTLY LAMP IS: Off
1212
CURRENTLY LAMP IS: Green/Red
```

Det finns alltså en lampa på kortenheten. Den kommer lysa

RÖTT: när man scannat ett kort som ej har access
GRÖNT: när man scannat ett kort som har access

Men vi fejkar med att skriva ut “CURRENTLY LAMP IS: Green” och Red

## Kravspecifikation

Att tänka på:

- inte krascha vid DÅLIG inmatning
- felhantering, snäll mot användaren
- systemet skall klara “OBEGRÄNSAT” antal kort (dynamisk minnesallokering – mallloc/realloc)

### Godkänt

    Använda buffer overflow (inmatning)
    - ...

    Använda stack overflow (flöde)
    - ...

    Dela upp i funktioner
    - ...

    inga globala variabler: samla "state" i struct
    - ...

    Hantera fel inmatning och inte kracha
    - ...

### Väl Godkänt

    Kort ska kunna SPARAS i FIL! Dvs efter omstart ska alla kort läsas upp och finnas kvar

    Branch med alternativ implementation: gör en version UTAN dynamisk minnesallokering (och ingen statisk array heller...men du ska ändå klara “oändligt” många kort !).  Dvs du får läsa upp EN I TAGET

    hela tiden från fil, mer info https://youtu.be/GqKZFzM9COA

    Bra kod, best practices etc

## Programmet

Programmet startar i main() och visar en menu() med fyra alternativ: 1) fjärröppna en dörr, 2) visa alla kort och deras behörighet i systemet, 3) lägga till eller ta bort behörighet, 4) avsluta programmet eller 9) testa kortläsaren.

> ### choiceOneRemoteOpenDoor()

(1) - Fjärröppna en dörr startar funktionen 'choiceOneRemoteOpenDoor()'. Funktionen visar ett meddelande som indikerar att lampan är grön och pausar sedan programmet i 3 sekunder med hjälp av funktionen 'waitSeconds(seconds)'.

> ### choiceTwoListAllCards()

(2) - Visa alla kort och behörighet i systemet startar funktionen 'choiceTwoListAllCards()'. Funktionen läser in alla kort och behörighet med viewFileData(FILE_DOOR) från filen 'door.txt' och skriver ut dem i terminalen. Slutligen anropas 'pauseKeyboard()' för att pausa programmet tills användaren trycker på en tangent.

viewFileData() - läser in data från filen 'door.txt' och skriver ut datan i terminalen.

pauseKeyboard() - pausar programmet tills användaren trycker på en tangent.

> ### choiceThreeAddRemoveAccess()

(3) - Om användaren väljer att lägga till eller ta bort behörighet startar funktionen 'choiceThreeAddRemoveAccess()'. Användaren får välja ett kortnummer med hjälp av funktionen 'GetInputInt()'. Kortinformation hämtas med hjälp av 'getCardInfo()'. Kortets behörigheter skrivs ut och användaren har möjlighet att lägga till eller ta bort behörigheter med hjälp av funktionen 'usePrompt()'. Funktionen 'validateModifyInput()' används för att kontrollera om användarens val skiljer sig från kortets nuvarande behörigheter. Om användaren har valt annorlunda, anropas funktionen 'updateDataToFile()' för att uppdatera kortets behörigheter i filen. Om användaren har valt samma behörighet som kortets nuvarande behörighet, görs ingenting.

getCardInfo() - Funktionen hämtar kortinformation från filen 'door.txt' med hjälp av useFile(FILE_DOOR). Därefter skapas en ny struct Card med initial data. Funktionen findCardInFile() anropas för att hitta radnumret för kortet i filen. Om kortet hittas i filen, läses kortets data in i structen Card. Om kortet inte finns anropas istället funktionen appendNewCard() för att lägga till det nya kortet i filen. Slutligen returneras structen Card.

- findCardInFile() - Funktionen letar efter kortets radnummer i filen. Om kortet hittas, läggs kortinformationen till i card och funktionen returnerar true. Om kortet inte hittas, returnerar funktionen false.
  - isAccessInFile() - returnerar true om kortet i filen har behörighet, annars returneras false.
  - getCardDateToFile() - läser in kortets datum från filen och returnerar det

- appendNewCard() - Om kortet inte redan finns i filen, lägger funktionen till det nya kortet. För att bestämma rätt textformatering, kontrollerar funktionen om filen har nått sitt slut (endOfFile). Därefter skapas en formaterad sträng med snprintf() och skickas till funktionen addDataToFile() för att lägga till det nya kortnumret i filen. Slutligen läggs dagens datum till i card.

- addDatatoFile() - Denna funktion lägger till en rad med data i filen. Tre parametrar skickas med: filen, raden som ska läggas till och radnumret. Funktionen läser in alla rader i filen med hjälp av readFile() och lägger till den nya raden på rätt plats med writeFile(). Slutligen frigörs minnet som allokerats för filen med freeLine().

  - readFile() - läser in data från filen och returnerar en struct fileAppendData med data från filen.
  - writeFile() - lägger till data till filen.
  - freeLines() - friar minnet för structen fileAppend.

usePrompt() - Funktionen används för att läsa in användarens val.

validateModifyInput() - Funktionen validerar användarens val mot kortets nuvarande behörigheter och returnerar en boolean som indikerar om de är olika.

if (isModify) 
updateDatatoFile() - Funktionen generateTempFileName() uppdaterar kortets behörigheter i filen genom att skapa en temporär fil med namnet 'temp.txt', kopiera innehållet från 'door.txt' till den temporära filen, modifiera den valda raden med copyAndModifyFile(), ersätta originalfilen med den temporära filen genom replaceOriginalFileWithTempFile() och döpa om den temporära filen till 'door.txt'.

- generateTempFileName() - genererar unikt namn för temporär fil baserat på datum och tid.
- copyAndModifyFile() - kopierar innehåll från 'door.txt' till temporär fil och modifierar den valda raden.
- replaceOriginalFileWithTempFile() - ersätter originalfilen med temporär fil och döper om den till 'door.txt'.

> ### exit(EXIT_SUCCESS)

(4) - Använd exit(EXIT_SUCCESS) för att avsluta programmet.

> ### choiceNineFakeScanCard()

(9) - Om användaren skannar ett falskt testkort startar 'choiceNineFakeScanCard()'. Ett meddelande visas först om att lampan är släckt, och användaren ombeds sedan att ange kortnumret med hjälp av GetInputInt(). Funktionen 'getFakeCardStatus()' hämtar kortets status från filen 'door.txt'. Efter att användaren har angett ett giltigt kortnummer, visas ett meddelande som indikerar om lampan är grön eller röd beroende på om kortet har behörighet eller inte.

- GetInputInt() - läser in kortnummer från användaren.
- getFakeCardStatus() - hämtar kortinformation från filen 'door.txt' och returnerar en boolean som indikerar om kortet har behörighet eller inte. Funktionen söker efter rätt rad i filen med hjälp av getCardNumber() och uppdaterar kortbehörigheten med isAccessInFile(). Funktionen returnerar cardAccess.

  - getCardNumber() - hämtar kortnumret från en rad i filen och returnerar det.
  - isAccessInFile() - returnerar en boolean som indikerar om kortet har behörighet eller inte.

## Filstruktur

Det finns totalt 15 filer i projektet. Programmet är uppdelat i en text fil 'door.txt' och följande struktur: Define.h, FileData, common, door.txt, file, input, main & prompt.

### main

door.txt

main.c

- void choiceNineFakeScanCard() *
- void choiceThreeAddRemoveAccess() *
- void choiceTwoListAllCards() *
- void choiceOneRemoteOpenDoor() *
- void menu() *
- void main() *

### struct

- FileData.h
  - FileData - FILE \*file_ptr, char file_row[256]
  - FileAppend - char \*\*lines, int row_insert
  - Card - int row, bool isAccess, char \*date, bool endOfFile *

### common.c

- char *concatStrings(const char *str1, const char \*str2) *
- void pauseKeyboard() *
- void waitSeconds(int seconds) *
- char *getCardDateToFile(const char *row)
- char *getCurrentDate(char *format) *
- int getCardNumber(char \*row)

### util.c

- bool findCardInFile(FileData fdata, int cardNumber, Card *card)
- void appendNewCard(FileData fdata, int cardNumber, Card \*card)
- Card getCardInfo(int cardNumber)
- bool getFakeCardStatus(int cardNumber)

### file.c

- void createFileWithEmptyRow(char \*filename)
- FileData useFile(char *fileName, char *mode)
- void viewFileData(char \*fileName)
- bool isAccessInFile(char \*row)
- void generateTempFileName(char \*tempFileName)
- void copyAndModifyFile(int rowNumber, char *newRow, char *tempFileName)
- void replaceOriginalFileWithTempFile(char \*tempFileName)
- void updateDataToFile(int rowNumber, char \*newRow)
- FileAppend readFile(char *file_path, int num_lines, int line_number, char *text)
- void writeFile(char *file_path, FileAppend fileAppend, int rowLine, char *text)
- void freeLines(FileAppend fileAppend)
- void addDataToFile(char *file_path, int rowLine, char *text)

### input.c

- bool GetInputInt(char *prompt, int *value) *

### prompt.c

- void validateInput(char \*inputBuffer) *
- bool isInteger(char \*input) *
- bool isInRange(int num, int min, int max) *
- int usePrompt(const char \*prompt, int max) *
- bool validateModifyInput(int input, Card card, int cardNumber, char \*text)

### Define.h

- file
  - FILE_DOOR "door.txt"
  - FILE_SIZE 1024
  - MAX_ROW_LENGTH 60 *
  - TEXT_NO_ACCESS "No access" *
  - TEXT_ACCESS "Access" *
  - TEXT_ADDED " Added to system"
- main
  - OPTION_REMOTE_OPEN_DOOR 1 *
  - OPTION_LIST_ALL_CARDS 2 *
  - OPTION_ADD_REMOVE_ACCESS 3 *
  - OPTOON_EXIT 4 *
  - OPTION_FAKE_SCAN_CARD 9 *
  - CLOCKS_PER_SEC 1000 *
