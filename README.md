Uppgift 2. Administrationssystem dörr - Godkänt kritierium - v.1.1

# Innehållsförteckning

- Beskrivning
- Kravspecifikation
- Programmet
- Filstruktur

## Beskrivning

Programmet "Administrationssystem dörr" är ett inpasseringssystem där besökaren scannar sitt kort. Användaren kan välja fyra menyval som är kopplade till olika funktioner. Eftersom många funktioner är liknande i både "main"- och "vg-file"-grenarna, läggs ett "*" till i avsnitt 'Filstruktur' för att visa att funktionen finns tillgänglig i båda grenarna.

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

## Programmet

Programmet startar i main() och visar en meny() med fyra alternativ: 1) fjärröppna en dörr, 2) visa alla kort och deras behörighet i systemet, 3) lägga till eller ta bort behörighet, 4) avsluta programmet eller 9) testa kortläsaren.

> ### choiceOneRemoteOpenDoor()

(1) - Fjärröppna en dörr startar funktionen 'choiceOneRemoteOpenDoor()'. Funktionen visar ett meddelande som indikerar att lampan är grön och pausar sedan programmet i 3 sekunder med hjälp av funktionen 'waitSeconds(seconds)'.

> ### choiceTwoListAllCards()

(2) - För att visa alla kort och deras behörighet i systemet kan användaren välja att starta funktionen 'choiceTwoListAllCards()'. Då kommer alla data från viewArrayData(arrData) att skrivas ut i terminalen.

viewArrayData() - läser in data och skriver ut datan i terminalen.

> ### choiceThreeAddRemoveAccess()

(3) - Om användaren väljer att lägga till eller ta bort behörighet startar funktionen 'choiceThreeAddRemoveAccess()'. Användaren får välja ett kortnummer med hjälp av funktionen 'GetInputInt()'. Kortinformation hämtas med hjälp av 'getCardInfo()'. Kortets behörigheter skrivs ut och användaren har möjlighet att lägga till eller ta bort behörigheter med hjälp av funktionen 'usePrompt()'. Funktionen 'validateModifyInput()' används för att kontrollera om användarens val skiljer sig från kortets nuvarande behörigheter. Om användaren har valt annorlunda, anropas funktionen 'updateDataToArray()' för att uppdatera kortets behörigheter. Om användaren har valt samma behörighet som kortets nuvarande behörighet, görs ingenting.

getCardInfo() - Funktionen hämtar kortinformation och skapar sedan en ny struct Card med initial data. För att hitta radnumret för kortet anropas funktionen findCardInArray(). Om kortet hittas, läses kortets data in i structen Card. Om kortet inte finns anropas istället funktionen appendNewCard() för att lägga till det nya kortet. Till slut returneras structen Card.

- findCardInArray() - Funktionen letar efter kortets radnummer. Om kortet hittas, läggs kortinformationen till i card och funktionen returnerar true. Om kortet inte hittas, returnerar funktionen false.

  - isAccessInArray() - Funktionen letar efter kortets behörighet. Om behörigheten hittas, läggs behörigheten till i card och funktionen returnerar true. Om behörigheten inte hittas, returnerar funktionen false.
  - getCardDateToArray() - läser in data från filen och lägger till den i en array

- appendNewCard() - Om kortet inte redan finns, lägger funktionen till det nya kortet. För att bestämma rätt textformatering, kontrollerar funktionen om filen har nått sitt slut (endOfFile). Sedan skapas en formaterad sträng med concatStrings() och skickas till funktionen addDataToArray() för att lägga till det nya kortnumret i filen.

- addDatatoArray() - Denna funktion lägger till en rad med data i en fil. Funktionen tar tre parametrar: en array, raden som ska läggas till och radnumret. Först ökar funktionen storleken på arrayen med "relloc", flyttar sedan datan i arrayen, lägger till den nya raden och ökar till sist storleken på arrayen med 1.

usePrompt() - Funktionen används för att läsa in användarens val.

validateModifyInput() - Funktionen validerar användarens val genom att jämföra det med kortets nuvarande behörigheter och returnerar en boolean som indikerar om användarens val skiljer sig från dessa behörigheter.

if (isModify)
updateDataToArray() - Funktionen loopar igenom arrayen för att hitta raden med det valda kortnumret. Därefter uppdateras behörigheten för det valda kortnumret med hjälp av funktionerna strncpy() och strlen().

> ### exit(EXIT_SUCCESS)

(4) - Kör funktionen exit(EXIT_SUCCESS) som avslutar programmet.

> ### choiceNineFakeScanCard()

(9) - Om användaren väljer att skanna ett falskt testkort, startar funktionen 'choiceNineFakeScanCard()'. Först visas ett meddelande som indikerar att lampan är släckt, och användaren ombeds att ange kortnumret med hjälp av GetInputInt(). Funktionen 'getFakeCardStatus()' används för att hämta kortets status. Om användaren anger ett giltigt kortnummer, visas ett meddelande som indikerar om lampan är grön eller röd beroende på om kortet har behörighet eller inte."

- GetInputInt() - läser in ett kortnummer från användaren.
- getFakeCardStatus() - Funktionen loopar igenom arrayen för att hitta raden med det valda kortnumret.  Om rätt rad hittas, så uppdateras kortbehörigheten med hjälp av isAccessInArray(). Därefter returneras cardAccess.

  - isAccessInArray() - returnerar true om kortet har behörighet, annars returneras false.

## Filstruktur

Det finns totalt 15 filer i projektet. Programmet är uppdelat i en ArrayData och följande struktur: Define.h, FileData, common, util, array, input, main & prompt.

### main

main.c

- void choiceNineFakeScanCard() *
- void choiceThreeAddRemoveAccess() *
- void choiceTwoListAllCards() *
- void choiceOneRemoteOpenDoor() *
- initialData()
- void menu() *
- void main() *

### struct

- FileData.h
  - Data - int id, char *access, char *date
  - ArrayData - Data *data, int size
  - Card - int row, bool isAccess, char \*date, bool endOfFile *

### common.c

- char *concatStrings(const char *str1, const char \*str2) *
- void pauseKeyboard() *
- void waitSeconds(int seconds) *
- void getCardDateToArray(Card *card, const char *date)
- char *getCurrentDate(char *format) *

### util.c

- bool findCardInArray(ArrayData *arrData, int cardNumber, Card *card)
- void appendNewCard(ArrayData *arrData, int cardNumber, Card *card)
- Card getCardInfo(int cardNumber, ArrayData *arrData)
- bool getFakeCardStatus(ArrayData arrData, int cardNumber)

### array.c

- bool isAccessInArray(ArrayData arrData, int i)
- void viewArrayData(ArrayData arrData)
- void updateDataToArray(ArrayData *arrData, int cardNumber, char *newAccess)
- void addDataToArray(ArrayData *arrData, Data newData, int row)

### input.c

- bool GetInputInt(char *prompt, int *value) *

### prompt.c

- void validateInput(char \*inputBuffer) *
- bool isInteger(char \*input) *
- bool isInRange(int num, int min, int max) *
- int usePrompt(const char \*prompt, int max) *
- bool validateModifyInput(int input, Card card, int cardNumber, char \*text)

### Define.c

- file
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
- prompt
  - PROMPT_MIN 1 * 
  - MENU_MAX 9 *
  - CHOICE_THREE_MAX 2 *
