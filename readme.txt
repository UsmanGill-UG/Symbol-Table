User Manual:
Menu Base is provided:
	Pressing 1:  
	This will insert the symbol into the table 
	Pressing 2:  
	This will remove the symbol from the table
	Pressing 3: 
	Will check if the Symbol Exists
	Pressing 4:
	Prints Symbol Attributes 
	Pressing 5 : 
	Load Symbol Table from File
	Pressing -1:
	Ends the program

NOTE: You can fill symbol.txt file if you want to load symbol table from a file.
	Format to fill symbol.txt is symbol on one line then type on another line.

Implementation Details:

Symbol Class : To store attributes of a symbol
	Functions:
		string GetName()const							    : returns the name of the symbol
		string GetDataType()const						    : returns the type of the symbol
		friend ostream& operator<<(ostream& output, const Symbol& sym)  : prints symbol attributes
		void change_attributes(vector<string> types)			    : change attributes of the symbol
	
SymbolTable Class: unordered_map (hash map) is used in the Symbol Table	
	Functions:
		void operator+=(Symbol s)    : Adds a symbol into the symbol table
		void operator-=(string s)    : Removes a symbol from the symbol table
		bool symbol_exists(string s) : Checks if a symbol exists in the symbol table
		void print_symbol(string s)  : prints attributes a symbol

Valid Types of SPL are loaded from types.txt file, you can edit that to add more valid types.