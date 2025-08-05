## Förberedelsefrågor
• Vad är skillnaden mellan en referens och en pekare?
    1. En pekare kan pekas om till en annan variabel, en referens kan bara referera till origialet
    2. En pekare kan vara Null
    3. Referenser har automatisk dereferncing.

• Vad innebär en adress när vi talar om pekare? Hur kommer vi åt den?
    En address är den virtuella adressen som den tilldelade variabeln har i ram.
    För att komma åt den behöver vi alltså avreferera den med *.

• Vad är skillnaden mellan en flytt och en kopiering?
    I en flytt tar ett nytt objekt över ägandet av variablerna i originalet. Originalobjektets pekare pekar efter en move på Null.  
    I en kopiering är när man skapar nya variabler med samma värde som originalobjektets variabler.

• Vad är skillnaderna mellan public, protected och private?
    - public:
        Vem som helst kan läsa och ändra på värdet
    - protected:
        Bara objekt av samma typ kan modifera värdet
    - private:
        Ingen kan läsa eller modifiera värdet.

## Reflektionsfrågor
• Varför behöver vi en destruktor?
    För att kunna bestämma vad som ska ske med objektets variabler innan det förstörs. 
    Mestadels för att undvika minnesläckor

• Vad händer om vi inte deklarerar en konstruktor eller destruktor?
    Om man inte deklarerar en konstruktor eller en destruktor så kommer kompilatorn att automatiskt skapa en.
    Den genererade konstruktorn kommer initialisera alla variabler med deras default värden. 
    Den genererade destruktorn kommer att kalla delete på alla variabler

• Vad innebär det att ett objekt dör?
    Att det förstörs eller att dess minne frigörs

• Varför behöver vi hantera minne? Vad kan hända med vårt program och dator om vi inte gör det?
    Om vi inte hanterar minne korrekt kan det leda till minnesläckor. Dessa sker när vi tilldelar minne men glömmer att frigöra det. Då cpp inte har en garbage colletor (som t.ex python har) så kommer programmet ta upp mer och mer minne tills vi tar slut.

• Varför har vi inre klasser?
    I en länkad lista har t.ex den inre klassen Node då det är ett objekt som enbart används av klassen LinkedList. Node är ett objekt som inte är tänkt att användas av någonannanstans än i LinkedList, därmed är det en inre klass

• Varför är inkapsling ett viktigt koncept?
    Innkapsling innebär att man skyddar och skärmar av kod från andra delar av programmet. Andra objekt och funktioner som interagerar med objektet ska alltså inte behöva bry sig om hur klassen faktiskt fungerar, bara hur man interagerar med det.
