#include <iostream>
#include <unordered_map>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

bool is_in_vec(vector<string> types, string str) 
{
	return std::find(types.begin(), types.end(), str) != types.end() ? true : false;
}

class Symbol 
{
	// attributes of a Symbol
private: 
	string Name;
	string Type;
	string Scope;
public:
	Symbol() {}
	Symbol(string _name, string _data_type, string _scope):Name(_name), Type(_data_type), Scope(_scope) // Default Constructor
	{} 
	string GetName()const 
	{
		return Name;
	}
	string GetDataType()const 
	{
		return Type;
	}
	string GetScope()const
	{
		return Scope;
	}
	friend ostream& operator<<(ostream& output, const Symbol& sym) {
		output << "Name : " << sym.Name << " Type : " << sym.Type<<" Scope : " << sym.Scope;
		return output;
	}
	void change_attributes(vector<string> types) 
	{
		cout << "Name : ";
		cin >> Name;
		do
		{
		    cout << "Type : ";
			cin >> Type;
		} while (!is_in_vec(types, Type)); // check if the type is valid
		cout << "Scope : ";
		cin >> Scope;
	}
};

class SymbolTable {
private:
	unordered_map<string, Symbol> Table;
public:
	SymbolTable()// default constructor
	{
	}
	SymbolTable(const SymbolTable & T) //
	{
		this->Table = T.Table;
	}
	void operator=(const SymbolTable& T) // assignment operator
	{
		this->Table = T.Table;
	}
	// add key value to the table
	void operator+=(Symbol s) 
	{
		this->Table[s.GetName()] = s;
	}
	// remove key value from the table
	void operator-=(string s)
	{
		Table.erase(s);
	}
	bool symbol_exists(string s)
	{
		return this->Table[s].GetName() == "" ? false : true;
	}
	void print_symbol(string s) 
	{
		cout << Table[s] << endl;
	}
};

void LoadSymbol(SymbolTable &table, const string & fn, vector<string>types) 
{
	ifstream reader(fn);
	while(!reader.eof())
	{
		char temp_sym[100];
		char temp_type[100];
		char temp_scope[100];
		reader.getline(temp_sym, 100, '\n');
		reader.getline(temp_type, 100, '\n');
		reader.getline(temp_scope, 100, '\n');
		if (!is_in_vec(types, temp_type)) 
		{
			cout << temp_type  <<" IS INVALID TYPE!" << endl;
			continue;
		}
		Symbol temp(temp_sym, temp_type, temp_scope);
		table += temp;
	}
	reader.close();
}

void load_valid_types(vector<string> &types)
{
	ifstream reader("types.txt");
	while (!reader.eof()) 
	{
		char t[100];
		reader.getline(t, 100, '\n');
		types.push_back(t);
	}
	reader.close();
}
void menu() 
{
	cout << "--------------------------MENU----------------------------------" << endl;
	cout << "1  Insert " << endl;
	cout << "2  Remove " << endl;
	cout << "3  Does Symbol Exist " << endl;
	cout << "4  Print Symbol Attributes " << endl;
	cout << "5  Load Symbol Table from File" << endl;
	cout << "-1  Exit " << endl;
}

int main() 
{
	cout << "--------------------------SYMBOL TABLE----------------------------------" << endl;
	SymbolTable table;
	vector<string> types;
	string fn = "symbol.txt";
	load_valid_types(types);
	int  choice;
	Symbol temp;
	string symbol;
	do 
	{
		menu();
		cin >> choice;
		if (choice == -1)
			break;
		system("cls");
		switch (choice)
		{
		case 1: // Add/Insert symbol into the symbol table
			temp.change_attributes(types);
			if (table.symbol_exists(temp.GetName()))
			{
				cout << "Symbol Already Exists!" << endl;
				break;
			}
			table += temp;
			cout << "Symbol INSERTED !" << endl;
			break;
		case 2: // Remove Symbol from the Symbol table
			cout << "Symbol : ";
			cin >> symbol;
			table -= symbol;
			cout << "Symbol REMOVED !" << endl;
			break;
		case 3: // find if the symbol exists in the Symbol Table
			cout << "Symbol : ";
			cin >> symbol;
			if (table.symbol_exists(symbol)) 
			{
				cout << "THIS SYMBOL EXISTS !" << endl;
				cout << "Attributes" << endl;
				table.print_symbol(symbol);
			}
			else
			{
				cout << "THIS SYMBOL DOES NOT EXISTS !" << endl;
			}
			break;
		case 4: // lookup and print symbol
			cout << "Symbol : "; 
			cin >> symbol;
			table.print_symbol(symbol);
			break;
		case 5: // load symbol table from file // will insert from file
			LoadSymbol(table, fn, types);
			cout << "Loading from file DONE!" << endl;
			break;
		case -1:
			break;
		default:
			break;
		}
	} while (choice != -1);

	return 0;
}