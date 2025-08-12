**14:**  
1. Den kommer att misslyckas då vi har stängt kopieringskonstruktorn, det kommer inte att kompilera. Detta är för att den högra delen av "=" uttrycket är ett "lvalue", alltså att det är ett namngivet objekt som har en plats i minnet.  
2. Den kommer att lyckas då den högra delen av "=" uttrycket (Expression{infix}) är ett ttemporärt object, alltså ett "rvalue". Kompilatorn kommer därmed använda sig av flyttkonstruktorn. 
