//****************************************************
//* Name Vending Machine
//****************************************************
//* File: VendingMachine.cpp
//****************************************************
//* This is the program that manages vending machine
//* with unlimited amount of products and sales per day.
//* Note that one sale - one product!
//*    
//****************************************************
#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <ctype.h>
#include <algorithm> // Função "std::remove()", "std::sort()", Função "std::find()"
#include <mysql.h>
#pragma warning(disable : 4996)
using namespace std;

class Product {

private:

	int idProduct;
	string name;
	int quantity;
	double priceForUnit;
	string expirationDate;

public:

	Product() {}

	Product(int id, string n, int q, double p, string d) {
		idProduct = id;
		name = n;
		quantity = q;
		priceForUnit = p;
		expirationDate = d;
	}
	// Destrutor
	~Product() {}

	// Setters
	void setIdProduct(int id) {
		idProduct = id;
	}
	void setQuantity(int q) {
		quantity = q;
	}
	void setName(string n) {
		name = n;
	}
	void setPrice(double p) {
		priceForUnit = p;
	}
	void setExpDate(string d) {
		expirationDate = d;
	}

	// Getters
	int getIdProduct() {
		return idProduct;
	}
	string getName() {
		return name;
	}
	int getQuantity() {
		return quantity;
	}
	double getPriceForUnit() {
		return priceForUnit;
	}
	string getExpDate() {
		return expirationDate;
	}
	//other functions
	void printProduct() {
		cout << "Id:" << idProduct << " " << name << endl;
		cout << "Quantity: " << quantity << endl;
		cout << "Price for unit: " << priceForUnit << " euros" << endl;
		cout << "Expiration date: " << expirationDate << endl;
		cout << "" << endl;
	}

	bool deleteQuantity(int qnt) {
		if (quantity >= qnt) {
			quantity = quantity - qnt;
			return true;
		}
		return false;
	}

};

class Stock {

private:

	int idStock;
	int idVm;
	vector<int> idProducts;
	vector<int> productQnts;

public:

	Stock() {}

	Stock(int idS, int idV) {
		idStock = idS;
		idVm = idV;
	}

	~Stock() {}

	// Setters
	void setIdStock(int id) {
		idStock = id;
	}
	void setIdVm(int id) {
		idVm = id;
	}
	void setIdProducts(vector<int> ids) {
		idProducts = ids;
	}
	void setProductsQnts(vector<int> qnts) {
		productQnts = qnts;
	}

	// Getters
	int getIdStock() {
		return idStock;
	}
	int getIdVm() {
		return idVm;
	}
	vector<int> getIdProducts() {
		return idProducts;
	}
	vector<int> getProductsQnts() {
		return productQnts;
	}

	//Other functions
	void addProductId(int id) {
		idProducts.push_back(id);
	}
	void addProductQnt(int qnt) {
		productQnts.push_back(qnt);
	}

	void updateProductStock(int prodId, int qnt) {
		int size = idProducts.size();
		for (int i = 0; i < size; i++) {
			if (prodId == idProducts.at(i)) {
				cin.ignore();
				productQnts.at(i) = productQnts.at(i) + qnt;
				break;
			}
		}
	}

	void deleteProduct(int prodId) {
		int size = idProducts.size();
		for (int i = 0; i < size; i++) {
			if (prodId == idProducts.at(i)) {
				idProducts.erase(idProducts.begin() + i);
				productQnts.erase(productQnts.begin() + i);
				break;
			}
		}
	}
	//update for Sale
	void updateProductSale(int prodId, int qnt) {
		int size = idProducts.size();
		for (int i = 0; i < size; i++) {
			if (prodId == idProducts.at(i)) {
				cin.ignore();
				productQnts.at(i) = productQnts.at(i) - qnt;
				break;
			}
		}
	}
	void printStock() {

		for (int i = 0; i < idProducts.size(); i++) {
			cout << "Product Id:" << idProducts.at(i) << endl;
			cout << "Quantity: " << productQnts.at(i) << endl;
			cout << "" << endl;
		}
	}

};

class Sale {

private:

	int idSale;
	string dateSale;
	int idVm;
	int idProduct;
	int productQnt;

public:

	Sale() {}

	Sale(int id, int idVmach, string date, int idP, int qnt) {
		idSale = id;
		idVm = idVmach;
		dateSale = date;
		idProduct = idP;
		productQnt = qnt;
	}

	~Sale() {}

	// Setters
	void setIdSale(int id) {
		idSale = id;
	}
	void setDateSale(string d) {
		dateSale = d;
	}
	void setIdVm(int id) {
		idVm = id;
	}
	void setIdProduct(int id) {
		idProduct = id;
	}
	void setProductQnt(int qnt) {
		productQnt = qnt;
	}

	// Getters
	int getIdSale() {
		return idSale;
	}
	string getDateSale() {
		return dateSale;
	}
	int getIdVm() {
		return idVm;
	}
	int getIdProduct() {
		return idProduct;
	}
	int  getProductsQnt() {
		return productQnt;
	}
	//other functions
	void printSale(Product p) {
		cout << endl;
		cout << "Sale:" << idSale << endl;
		cout << "Date:" << dateSale << endl;
		cout << "Vending Machine:" << idVm << endl;
		cout << "Product id:" << idProduct << " name: " << p.getName() << endl;
		cout << "Quantity: " << productQnt << endl;
		cout << "Total price: " << p.getPriceForUnit()*productQnt << " euros" << endl;
		cout << endl;
	}

};

class VendingMachine {

private:

	int idVm;
	int idStockVendingMachine;
	string address;
	string provider;

public:

	VendingMachine() {}

	VendingMachine(int id, int stockId, string a, string p) {
		idVm = id;
		idStockVendingMachine = stockId;
		address = a;
		provider = p;
	}

	~VendingMachine() {}

	// Setters
	void setIdVm(int id) {
		idVm = id;
	}
	void setIdStock(int id) {
		idStockVendingMachine = id;
	}
	void setAddress(string a) {
		address = a;
	}
	void setProvider(string p) {
		provider = p;
	}

	// Getters
	int getIdVm() {
		return idVm;
	}
	int getIdStock() {
		return idStockVendingMachine;
	}
	string getAddress() {
		return address;
	}
	string getProvider() {
		return provider;
	}
	//other functions
	void printVendingMachine() {
		cout << "Vending Machine: " << idVm << endl;
		cout << "Address: " << address << endl;
		cout << "Provider: " << provider << endl;
		cout << "" << endl;
	}

};

//***************************************************
//* Exception class
//****************************************************
class StocksHandler
{
private:
	int NLinha;
public:
	StocksHandler(int n);
	void Msg();
};

StocksHandler::StocksHandler(int n)
{
	NLinha = n;
}
void StocksHandler::Msg()
{
	cout << "There are not any stocks yet ..." << endl;
	cout << "Adding a new Vending machine is reccomended!" << endl;
	cout << "Error at the line: " << NLinha << "." << endl;
}

void Exit()
{
	cout << "Terminating the program..." << endl;
	system("pause");
}
void UnexpectedException()
{
	cout << "Unexpected exception..." << endl;
	system("pause");
}
//*************************************
//* Prototypes of the functions
//*************************************
string checkDate();
void showMenu();
void getOption(char*);
void processOption(char, vector<VendingMachine>*, vector<Product>*, vector<Stock> *, bool*);
void manageStorehouse(vector<Product>*);
bool findProduct(int, vector<Product>);
void addProduct(vector<Product>*);
void deleteProduct(vector<Product>*);
void updateProduct(vector<Product>*);
void manageVendingMachines(vector<VendingMachine>*, vector<Stock>*);
bool findVendingMachine(int, vector<VendingMachine>);
void addVm(vector<VendingMachine>*, vector<Stock>*);
void deleteVm(vector<VendingMachine>*, vector<Stock>*);
void updateVm(vector<VendingMachine>*);
void manageStock(vector<Stock>*, vector<Product>*, vector<VendingMachine>*);
bool enoughQuantity(vector<Product>, int, int);
bool enoughQuantityStock(Stock, int, int);
void addProductVm(vector<Stock> *, vector<Product>*, vector<VendingMachine>*);
void addQuantitiesVm(vector<Stock> *, vector<Product> *, vector<VendingMachine>*);
void deleteProductVm(vector<Stock> *, vector<VendingMachine>*);
bool findStock(int, vector<Stock>);
bool findProductAtStock(int, int, vector<Stock>);
void sellProductVm(vector<Stock> *, vector<VendingMachine> *);
void printStorehouse(vector<Product>);
bool initializesales(vector<Sale>*);
void printSales(vector<Product>);
void printVms(vector<VendingMachine>);
void printStockAtVm(vector<VendingMachine>, vector<Stock>);
bool validatePrice(string);
bool validateNumber(string);
bool exitProgram(bool);
void optionInvalid(char);
void endProgram();
void pause();

ostream& operator<<(ostream& os, Product& p)
{
	os << p.getIdProduct() << endl;
	os << p.getName() << endl;
	os << p.getQuantity() << endl;
	os << p.getPriceForUnit() << endl;
	os << p.getExpDate() << endl;
	os << endl;

	return os;
}

istream& operator>>(istream& is, Product& p)
{
	{ int id = 0; is >> id; p.setIdProduct(id); is.ignore(); }
	char letra = '\0';
	{
		const int MAXNOME = 40; char texto[MAXNOME];
		for (int cLetra = 0; cLetra < MAXNOME; cLetra++)
			texto[cLetra] = '\0';
		is.getline(texto, MAXNOME, '\n');
		p.setName(texto);
	}
	{ int quantity = 0; is >> quantity; p.setQuantity(quantity); is.ignore(); }
	{ double price = 0; is >> price; p.setPrice(price); is.ignore(); }
	letra = '\0';
	{
		const int MAXNOME = 40; char texto[MAXNOME];
		for (int cLetra = 0; cLetra < MAXNOME; cLetra++)
			texto[cLetra] = '\0';
		is.getline(texto, MAXNOME, '\n');
		p.setExpDate(texto);
	}

	is.ignore();
	return is;
}

void saveFile(vector<Product> products)
{
	string caminho = "", nomeFicheiro = "prods.txt";
	string nomeCompleto = caminho + nomeFicheiro;
	//cout << "File name: " << nomeCompleto.c_str() << "." << endl;

	// Criar o objeto e abrir o ficheiro
	//ofstream ficheiro4(nomeCompleto.c_str());
	ofstream ficheiro;
	ficheiro.open(nomeCompleto, ios::out); // | ios_base::binary
	// Modos de abertura: "ios::out" -> escrita

	if (!ficheiro) {
		//cout << "File has not been opened!" << endl;
		pause();
	}
	else {
		// 4. Escrever mensagem
		int nProdutos = products.size();
		//cout << "Number of products: " << nProdutos << "." << endl;
		if (nProdutos <= 0)
		{
			//cout << "There are not any products!" << endl;
			pause();
		}
		else
		{
			//cout << "-> Writing products: \n";
			for (int i = 0; i < nProdutos; i++)
				ficheiro << products[i];
			// 5. Fechar o ficheiro
			ficheiro.close();
			//cout << "Data has been saved with success!" << endl;

		}
	}
}

void readFile(vector<Product> *products)
{

	string caminho = "", nomeFicheiro = "prods.txt";
	string nomeCompleto = caminho + nomeFicheiro;
	//cout << "File name: " << nomeCompleto.c_str() << "." << endl;

	products->erase(products->begin(), products->end());

	//cout << "-> Reading products: \n";
	// 3. Criar o objeto e abrir o ficheiro
	//ofstream ficheiro4(nomeCompleto.c_str());
	ifstream ficheiroL;
	ficheiroL.open(nomeCompleto, ios::in); // | ios_base::binary

	if (ficheiroL.is_open()) {

		Product p;
		// 4. Leitura dos objetos

		while (ficheiroL >> p && !ficheiroL.eof())
		{
			products->push_back(p);

		}
		// 5. Fechar o ficheiro
		ficheiroL.close();
		cout << endl;
	}
}

ostream& operator<<(ostream& os, VendingMachine& vm)
{
	os << vm.getIdVm() << endl;
	os << vm.getIdStock() << endl;
	os << vm.getAddress() << endl;
	os << vm.getProvider() << endl;
	os << endl;

	return os;
}

istream& operator>>(istream& is, VendingMachine& vm)
{
	{ int id = 0; is >> id; vm.setIdVm(id); is.ignore(); }
	{ int ids = 0; is >> ids; vm.setIdStock(ids); is.ignore(); }
	char letra = '\0';
	{
		const int MAXNOME = 40; char texto[MAXNOME];
		for (int cLetra = 0; cLetra < MAXNOME; cLetra++)
			texto[cLetra] = '\0';
		is.getline(texto, MAXNOME, '\n');
		vm.setAddress(texto);
	}
	letra = '\0';
	{
		const int MAXNOME = 40; char texto[MAXNOME];
		for (int cLetra = 0; cLetra < MAXNOME; cLetra++)
			texto[cLetra] = '\0';
		is.getline(texto, MAXNOME, '\n');
		vm.setProvider(texto);
	}
	is.ignore();
	return is;
}

void saveFile(vector<VendingMachine> vms)
{
	string caminho = "", nomeFicheiro = "vms.txt";
	string nomeCompleto = caminho + nomeFicheiro;
	//cout << "File name: " << nomeCompleto.c_str() << "." << endl;

	// Criar o objeto e abrir o ficheiro
	//ofstream ficheiro4(nomeCompleto.c_str());
	ofstream ficheiro;
	ficheiro.open(nomeCompleto, ios::out); // | ios_base::binary
	// Modos de abertura: "ios::out" -> escrita

	if (!ficheiro) {
		//cout << "File has not been opened!" << endl;
		pause();
	}
	else {
		// 4. Escrever mensagem
		int n = vms.size();
		//cout << "Number of Vending Machines: " << n << "." << endl;
		if (n <= 0)
		{
			//cout << "There are not any Vending Machines!" << endl;
			pause();
		}
		else
		{
			//cout << "-> Writing Vending Machines: \n";
			for (int i = 0; i < n; i++)
				ficheiro << vms[i];
			// 5. Fechar o ficheiro
			ficheiro.close();
			//cout << "Data has been saved with success!" << endl;

		}
	}
}

void readFile(vector<VendingMachine> *vms)
{

	string caminho = "", nomeFicheiro = "vms.txt";
	string nomeCompleto = caminho + nomeFicheiro;
	cout << "File name: " << nomeCompleto.c_str() << "." << endl;

	vms->erase(vms->begin(), vms->end());

	cout << "-> Reading Vending machines: \n";
	// 3. Criar o objeto e abrir o ficheiro
	//ofstream ficheiro4(nomeCompleto.c_str());
	ifstream ficheiroL;
	ficheiroL.open(nomeCompleto, ios::in); // | ios_base::binary

	if (ficheiroL.is_open()) {

		VendingMachine vm;
		// 4. Leitura dos objetos

		while (ficheiroL >> vm && !ficheiroL.eof())
		{
			vms->push_back(vm);

		}
		// 5. Fechar o ficheiro
		ficheiroL.close();
		cout << endl;
	}
}

ostream& operator<<(ostream& os, Stock& s)
{
	os << s.getIdStock() << endl;
	os << s.getIdVm() << endl;
	vector<int> idProducts = s.getIdProducts();
	int size = idProducts.size();
	os << size << endl;
	for (int i = 0; i < size; i++) {
		os << idProducts[i] << endl;
	}
	vector<int> qnts = s.getProductsQnts();
	int size1 = qnts.size();
	os << size1 << endl;
	for (int i = 0; i < size1; i++) {
		os << qnts[i] << endl;
	}
	os << endl;
	return os;
}

istream& operator>>(istream& is, Stock& s)
{
	{ int id = 0; is >> id; s.setIdStock(id); is.ignore(); }
	{
		int idvm = 0; is >> idvm; s.setIdVm(idvm); is.ignore();
	}
	int size = 0; is >> size; is.ignore();
	vector<int> idProducts;
	for (int i = 0; i < size; i++) {
		int id = 0; is >> id; idProducts.push_back(id); is.ignore();

	}
	s.setIdProducts(idProducts);
	size = 0; is >> size; is.ignore();
	vector<int> qnts;
	for (int i = 0; i < size; i++) {
		int qnt = 0; is >> qnt; qnts.push_back(qnt); is.ignore();

	}
	s.setProductsQnts(qnts);
	is.ignore();
	return is;
}

void saveFile(vector<Stock> stocks)
{
	string caminho = "", nomeFicheiro = "stocks.txt";
	string nomeCompleto = caminho + nomeFicheiro;
	//cout << "File name: " << nomeCompleto.c_str() << "." << endl;

	// Criar o objeto e abrir o ficheiro
	//ofstream ficheiro4(nomeCompleto.c_str());
	ofstream ficheiro;
	ficheiro.open(nomeCompleto, ios::out); // | ios_base::binary
	// Modos de abertura: "ios::out" -> escrita

	if (!ficheiro) {
		//cout << "File has not been opened!" << endl;
		pause();
	}
	else {
		// 4. Escrever mensagem
		int n = stocks.size();
		//cout << "Number of Stocks: " << n << "." << endl;
		if (n <= 0)
		{
			//cout << "There are not any Stock!" << endl;
			pause();
		}
		else
		{
			//cout << "-> Writing Stocks: \n";
			for (int i = 0; i < n; i++)
				ficheiro << stocks[i];
			// 5. Fechar o ficheiro
			ficheiro.close();
			//cout << "Data has been saved with success!" << endl;

		}
	}
}

void readFile(vector<Stock> *stocks)
{

	string caminho = "", nomeFicheiro = "stocks.txt";
	string nomeCompleto = caminho + nomeFicheiro;
	cout << "File name: " << nomeCompleto.c_str() << "." << endl;

	stocks->erase(stocks->begin(), stocks->end());

	cout << "-> Reading Stocks: \n";
	// 3. Criar o objeto e abrir o ficheiro
	//ofstream ficheiro4(nomeCompleto.c_str());
	ifstream ficheiroL;
	ficheiroL.open(nomeCompleto, ios::in); // | ios_base::binary

	if (ficheiroL.is_open()) {

		Stock s;
		// 4. Leitura dos objetos

		while (ficheiroL >> s && !ficheiroL.eof())
		{
			stocks->push_back(s);

		}
		// 5. Fechar o ficheiro
		ficheiroL.close();
		cout << endl;
	}
}

//*************************************
//*  Main function
//*************************************
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
int main()
{
	setlocale(LC_ALL, "Portuguese");

	char option = '\0';
	bool wantToExit = false;

	vector<VendingMachine> vendingMachines;
	vector<Product> products;// products at the storehouse
	vector<Stock> stocks;// products at vending machines

	// initialize vectors
	readFile(&vendingMachines);
	readFile(&products);
	readFile(&stocks);
	//get connection	
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "root", "vending_machine", 3306, NULL, 0);
	
	do {
		showMenu();
		getOption(&option);
		processOption(option,
			&vendingMachines,
			&products,
			&stocks,
			&wantToExit);
	} while (!wantToExit);
	endProgram();
	return 0;
}

void showMenu()
{
	system("cls");
	system("color A");
	cout << "**************************************************" << endl;
	cout << "*                                                *" << endl;
	cout << "*            Main menu                           *" << endl;
	cout << "*                                                *" << endl;
	cout << "*   A. Manage Storehouse                         *" << endl;
	cout << "*   B. Manage Vending Machines                   *" << endl;
	cout << "*   C. Manage Stock at the specific machine      *" << endl;
	cout << "*   D. Manage Sales                              *" << endl;
	cout << "*   E. Check Storehouse                          *" << endl;
	cout << "*   F. Check Vending Machines                    *" << endl;
	cout << "*   G. Check Stock at specific Vending Machine   *" << endl;
	cout << "*   H. Check Sales                               *" << endl;
	cout << "*   I. Exit the program.                         *" << endl;
	cout << "*                                                *" << endl;
	cout << "**************************************************" << endl;
}
void getOption(char *option)
{
	cout << "Choose option (A-I)? ";
	cin >> (*option);
	cin.ignore();

}
void processOption(char option,
	vector<VendingMachine> *vms,
	vector<Product> *products,
	vector<Stock> *stocks,
	bool *exit)
{
	switch (option)
	{
	case 'a': case 'A':
		manageStorehouse(products); saveFile((*products));
		break;
	case 'b': case 'B':
		manageVendingMachines(vms, stocks); saveFile((*vms));
		break;
	case 'c': case 'C':
		manageStock(stocks, products, vms); saveFile((*stocks)); saveFile((*products));
		break;
	case 'd': case 'D':
		sellProductVm(stocks, vms); saveFile((*stocks)); 
		break;
	case 'e': case 'E':
		printStorehouse((*products));
		break;
	case 'f': case 'F':
		printVms((*vms));
		break;
	case 'g': case 'G':
		printStockAtVm((*vms), (*stocks));
		break;
	case 'h': case 'H':
		printSales((*products));
		break;
	case 'i': case 'I':
		(*exit) = exitProgram((*exit));
		break;
	default:
		optionInvalid(option);
	}
}
void manageStorehouse(vector<Product> *products) {

	char option = '\0';
	system("cls");
	system("color A");
	cout << "*******************************************" << endl;
	cout << "*      Here you can change the stock at   *" << endl;
	cout << "*      the Storehouse!                    *" << endl;
	cout << "*                                         *" << endl;
	cout << "*      Choose an option:                  *" << endl;
	cout << "*   A. Add product                        *" << endl;
	cout << "*   B. Delete product                     *" << endl;
	cout << "*   C. Update product                     *" << endl;
	cout << "*   D. Cancel                             *" << endl;
	cout << "*                                         *" << endl;
	cout << "*******************************************" << endl;
	cin >> option;
	cin.ignore();
	switch (option)
	{
	case 'a': case 'A':
		addProduct(products);
		break;
	case 'b': case 'B':
		deleteProduct(products);
		break;
	case 'c': case 'C':
		updateProduct(products);
		break;
	case 'd': case 'D':
		return;
	default:
		optionInvalid(option);
	}
}
bool findProduct(int id, vector<Product> products) {

	for (vector<Product>::iterator it = products.begin(); it != products.end(); ++it) {
		if (id == (*it).getIdProduct()) {
			return true;
		}
	}
	return false;
}

void addProduct(vector<Product> *products) {

	string idP;
	cout << "Enter product id:" << endl;
	cin >> idP;// validate id
	for (int i = 0; i < idP.size(); i++) {
		if (!isdigit(idP.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int id = atoi(idP.c_str());

	if (!findProduct(id, (*products))) {
		string name;
		string qnt;
		string price;
		string expirationDate;
		cout << "Enter name:" << endl;
		cin >> name;
		cout << "Enter quantity:" << endl;
		cin >> qnt;
		for (int i = 0; i < qnt.size(); i++) {
			if (!isdigit(qnt.at(i))) {
				cout << "An integer number shall be inserted!" << endl;
				cin.ignore();
				pause();
				return;
			}
		}
		int q = atoi(qnt.c_str());
		cout << "Enter price: (use ',' for real numbers)" << endl;
		cin >> price;
		int count = 0;
		for (int i = 0; i < price.size(); i++) {
			if (isdigit(price.at(i)) || ispunct(price.at(i))) {
				count++;
			}
		}
		if (price.size() != count) {
			cout << "A number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}

		double p = atof(price.c_str());

		cout << "Enter expiration date DD-MM-YYYY:" << endl;
		cin >> expirationDate;
		// create a new Product
		Product product(id, name, q, p, expirationDate);
		//add Product to the Storehouse
		(*products).push_back(product);
		cout << "The product has been successfully added!" << endl;
		cin.ignore();
		pause();
	}
	else {
		cout << "The product is already exists!";
		cin.ignore();
		pause();
	}
}

void deleteProduct(vector<Product> *products) {

	string idP;
	cout << "Enter product id:" << endl;
	cin >> idP;// validate id
	for (int i = 0; i < idP.size(); i++) {
		if (!isdigit(idP.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int id = atoi(idP.c_str());

	if (findProduct(id, (*products))) {
		for (vector<Product>::iterator it = (*products).begin(); it != (*products).end(); ++it) {
			if (id == (*it).getIdProduct()) {
				(*products).erase(it);
				break;
			}
		}
		cout << "The product has been successfully deleted!" << endl;
		cin.ignore();
		pause();
	}
	else {
		cout << "There is no product with such Id!" << endl;
		cin.ignore();
		pause();
	}
}

void updateProduct(vector<Product> *products) {

	string idP;
	cout << "Enter product id:" << endl;
	cin >> idP;// validate id
	for (int i = 0; i < idP.size(); i++) {
		if (!isdigit(idP.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int id = atoi(idP.c_str());

	if (findProduct(id, (*products))) {
		for (vector<Product>::iterator it = (*products).begin(); it != (*products).end(); ++it) {
			if (id == (*it).getIdProduct()) {

				string name;
				string q;
				string priceP;
				string expirationDate;
				cout << "Enter name:" << endl;
				cin >> name;
				cout << "Enter quantity:" << endl;
				cin >> q;//validate qnt
				if (!validateNumber(q)) return;
				int qnt = atoi(q.c_str());
				cout << "Enter price for one piece of product:" << endl;
				cin >> priceP;
				if (!validatePrice(priceP)) return;
				double price = atof(priceP.c_str());
				cout << "Enter expiration date:" << endl;
				cin >> expirationDate;

				(*it).setName(name);
				(*it).setPrice(price);
				(*it).setQuantity(qnt);
				(*it).setExpDate(expirationDate);
				break;
			}
		}
		cout << "the product has been successfully updated!" << endl;
		cin.ignore();
		pause();
	}
	else {
		cout << "There is no product with such an Id!" << endl;
		cin.ignore();
		pause();
	}
}

void manageVendingMachines(vector<VendingMachine>* vms, vector<Stock>* stocks) {

	char option = '\0';
	system("cls");
	system("color A");
	cout << "****************************************" << endl;
	cout << "*      Choose an option:               *" << endl;
	cout << "*                                      *" << endl;
	cout << "*   A. Add Vending Machine             *" << endl;
	cout << "*   B. Delete Vending Machine          *" << endl;
	cout << "*   C. Update Vending Machine          *" << endl;
	cout << "*   D. Cancel                          *" << endl;
	cout << "*                                      *" << endl;
	cout << "****************************************" << endl;
	cin >> option;
	cin.ignore();
	switch (option)
	{
	case 'a': case 'A':
		addVm(vms, stocks);
		break;
	case 'b': case 'B':
		deleteVm(vms, stocks);
		break;
	case 'c': case 'C':
		updateVm(vms);
		break;
	case 'd': case 'D':
		return;
	default:
		optionInvalid(option);
	}
}

bool findVendingMachine(int id, vector<VendingMachine> vms) {

	for (vector<VendingMachine>::iterator it = vms.begin(); it != vms.end(); ++it) {
		if (id == (*it).getIdVm()) {
			return true;
		}
	}
	return false;
}

bool findStock(int id, vector<Stock> stocks) {

	for (vector<Stock>::iterator it = stocks.begin(); it != stocks.end(); ++it) {
		if (id == (*it).getIdStock()) {
			return true;
		}
	}
	return false;
}

void addVm(vector<VendingMachine>* vms, vector<Stock>* stocks) {

	string idP;
	cout << "Enter Vending Machine Id:" << endl;
	cin >> idP;// validate id
	for (int i = 0; i < idP.size(); i++) {
		if (!isdigit(idP.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int id = atoi(idP.c_str());

	if (!findVendingMachine(id, (*vms))) {
		string provider;
		int stockId;
		string address;
		string sId;
		cout << "Enter provider:" << endl;
		cin.ignore();
		getline(cin, provider);
		cout << "Enter address:" << endl;
		getline(cin, address);
		cout << "Enter Stock Id:" << endl;
		cin >> sId;//validate 

		if (!validateNumber(sId)) return;
		stockId = atoi(sId.c_str());

		if (!findStock(stockId, (*stocks))) {
			//create new stock
			Stock s(stockId, id);
			(*stocks).push_back(s);

			// create a new Vm
			VendingMachine vm(id, stockId, address, provider);
			//add Vm to the vector
			(*vms).push_back(vm);
			cout << "The vending Machine has been successfully added!" << endl;
			cin.ignore();
			pause();
		}
		else
		{
			cout << "The stock with such Id already exists!" << endl;
			cin.ignore();
			pause();
		}
	}
	else {
		cout << "The Vending Machine already exists!" << endl;
		cin.ignore();
		pause();
	}

}

void deleteVm(vector<VendingMachine>* vms, vector<Stock>* stocks) {

	string idP;
	cout << "Enter Vending Machine Id:" << endl;
	cin >> idP;// validate id
	for (int i = 0; i < idP.size(); i++) {
		if (!isdigit(idP.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int id = atoi(idP.c_str());

	if (findVendingMachine(id, (*vms))) {
		for (vector<VendingMachine>::iterator it = (*vms).begin(); it != (*vms).end(); ++it) {
			if (id == (*it).getIdVm()) {
				(*vms).erase(it);
				break;
			}
		}
		cout << "The vending Machine has been successfully deleted!" << endl;
		cin.ignore();
		pause();
	}
	else {
		cout << "There is no Vending machine with such Id!" << endl;
		cin.ignore();
		pause();
	}

}

void updateVm(vector<VendingMachine>* vms) {

	string idP;
	cout << "Enter Vending Machine Id:" << endl;
	cin >> idP;// validate id
	for (int i = 0; i < idP.size(); i++) {
		if (!isdigit(idP.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int id = atoi(idP.c_str());
	if (findVendingMachine(id, (*vms))) {

		for (vector<VendingMachine>::iterator it = (*vms).begin(); it != (*vms).end(); ++it) {
			if (id == (*it).getIdVm()) {

				string provider;
				int stockId;
				string address;
				string sId;
				cout << "Enter provider:" << endl;
				cin.ignore();
				getline(cin, provider);
				cout << "Enter address:" << endl;
				getline(cin, address);
				cout << "Enter Stock Id:" << endl;
				cin >> sId;//validate 
				if (!validateNumber(sId)) return;
				stockId = atoi(sId.c_str());

				(*it).setIdVm(id);
				(*it).setIdStock(stockId);
				(*it).setAddress(address);
				(*it).setProvider(provider);
				break;
			}
		}
		cout << "The vending Machine has been successfully updated!" << endl;
		cin.ignore();
		pause();
	}
	else {
		cout << "There is no Vending machine with such Id!" << endl;
		cin.ignore();
		pause();
	}

}

void manageStock(vector<Stock> *stocks, vector<Product> * products, vector<VendingMachine>* vms) {

	set_terminate(Exit);
	set_unexpected(UnexpectedException);

	try {

		if ((*stocks).size() == 0) throw (StocksHandler(__LINE__));

		char option = '\0';
		system("cls");
		system("color A");
		cout << "*******************************************" << endl;
		cout << "*      Here you can change the stock at   *" << endl;
		cout << "*      the specific Vending machine!      *" << endl;
		cout << "*                                         *" << endl;
		cout << "*      Note: to sell product              *" << endl;
		cout << "*             choose menu Manage Sales    *" << endl;
		cout << "*             in the Main menu.           *" << endl;
		cout << "*                                         *" << endl;
		cout << "*      Choose an option:                  *" << endl;
		cout << "*   A. Add new product                    *" << endl;
		cout << "*   B. Delete product                     *" << endl;
		cout << "*   C. Add quantities to the product      *" << endl;
		cout << "*   D. Cancel                             *" << endl;
		cout << "*                                         *" << endl;
		cout << "*******************************************" << endl;
		cin >> option;
		cin.ignore();
		switch (option)
		{
		case 'a': case 'A':
			addProductVm(stocks, products, vms);
			break;
		case 'b': case 'B':
			deleteProductVm(stocks, vms);
			break;
		case 'c': case 'C':
			addQuantitiesVm(stocks, products, vms);
			break;
		case 'd': case 'D':
			return;
		default:
			optionInvalid(option);
		}
	}
	catch (StocksHandler T) {
		T.Msg();
	}
}

void addProductVm(vector<Stock> *stocks, vector<Product> *products, vector<VendingMachine>* vms) {

	string id;
	cout << "Enter Vending Machine Id:" << endl;
	cin >> id;// validate id
	for (int i = 0; i < id.size(); i++) {
		if (!isdigit(id.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int idVm = atoi(id.c_str());

	if (findVendingMachine(idVm, (*vms))) {

		int stockId;
		for (vector<VendingMachine>::iterator it = (*vms).begin(); it != (*vms).end(); ++it) {
			if ((*it).getIdStock() == idVm) {
				stockId = (*it).getIdStock();
				break;
			}
		}

		int prodId;
		string pId;
		cout << "Enter product id (product must exist in the Storehouse):" << endl;
		cin >> pId;// validate id
		if (!validateNumber(pId)) return;
		prodId = atoi(pId.c_str());

		if (findProduct(prodId, (*products))) {
			if (!findProductAtStock(stockId, prodId, (*stocks))) {
				for (vector<Stock>::iterator it = (*stocks).begin(); it != (*stocks).end(); ++it) {
					if ((*it).getIdStock() == stockId) {
						int qnt;
						string q;
						cout << "Enter quantity (cant be more than at the Storehouse):" << endl;
						cin >> q;
						if (!validateNumber(q)) return;
						qnt = atoi(q.c_str());

						//validate qnt(compare with storehouse shall not be more)
						if (enoughQuantity((*products), prodId, qnt)) {
							//delete qnt from the Storehouse
							for (vector<Product>::iterator it = (*products).begin(); it != (*products).end(); ++it) {
								if ((*it).getIdProduct() == prodId) {
									(*it).deleteQuantity(qnt);
								}
							}
							(*it).addProductId(prodId);
							(*it).addProductQnt(qnt);
							cout << "The product has been successfully added!" << endl;
							break;
						}
						else
							cout << "Not enough quantity at the Storehouse!" << endl;
						break;
					}
				}
				cin.ignore();
				pause();
			}
			else {
				cout << "Product with such Id already exists at Vending Machine!" << endl;
				cin.ignore();
				pause();
			}
		}
		else
		{
			cout << "There is no product with such Id!" << endl;
			cin.ignore();
			pause();
		}
	}
	else {
		cout << "There is no Vending Machine with such Id!" << endl;
		cin.ignore();
		pause();
	}
}

bool enoughQuantity(vector<Product> products, int prodId, int qnt) {

	for (vector<Product>::iterator it = products.begin(); it != products.end(); ++it) {
		if ((*it).getIdProduct() == prodId) {
			if ((*it).getQuantity() >= qnt)
				return true;
			else return false;
		}
	}
	return false;
}

bool findProductAtStock(int stockId, int ProdId, vector<Stock> stocks) {

	for (vector<Stock>::iterator it = stocks.begin(); it != stocks.end(); ++it) {
		if (stockId == (*it).getIdStock()) {
			vector<int> products = (*it).getIdProducts();
			for (vector<int>::iterator itr = products.begin(); itr != products.end(); ++itr) {
				if (ProdId == (*itr)) {
					return true;
				}
			}
		}
	}
	return false;

}

void addQuantitiesVm(vector<Stock> *stocks, vector<Product> *products, vector<VendingMachine>* vms) {

	string idv;
	cout << "Enter Vending Machine Id:" << endl;
	cin >> idv;// validate id
	for (int i = 0; i < idv.size(); i++) {
		if (!isdigit(idv.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int idVm = atoi(idv.c_str());
	if (findVendingMachine(idVm, (*vms))) {

		int stockId;
		for (vector<VendingMachine>::iterator it = (*vms).begin(); it != (*vms).end(); ++it) {
			if ((*it).getIdStock() == idVm) {
				stockId = (*it).getIdStock();
				break;
			}
		}

		int prodId;
		string pId;
		cout << "Enter product id:" << endl;
		cin >> pId;// validate id
		if (!validateNumber(pId)) return;
		prodId = atoi(pId.c_str());

		if (findProductAtStock(stockId, prodId, (*stocks))) {

			for (vector<Stock>::iterator it = (*stocks).begin(); it != (*stocks).end(); ++it) {
				if ((*it).getIdStock() == stockId) {

					int qnt;
					string q;
					cout << "Enter quantity (there shall be enough quantity at the Storehouse):" << endl;
					cin >> q;
					if (!validateNumber(q)) return;
					qnt = atoi(q.c_str());

					if (enoughQuantity((*products), prodId, qnt)) {
						(*it).updateProductStock(prodId, qnt);
						for (vector<Product>::iterator it = (*products).begin(); it != (*products).end(); ++it) {
							if ((*it).getIdProduct() == prodId) {
								(*it).deleteQuantity(qnt);
							}
						}
						cout << "The product has been successfully updated!" << endl;
						pause();
						break;
					}
					else {
						cout << "There is not enough quantity at the Storehouse!" << endl;
						break;
						cin.ignore();
						pause();
					}
				}
			}
			pause();
		}
		else
		{
			cout << "There is no product with such Id!" << endl;
			cin.ignore();
			pause();
		}
	}
	else {
		cout << "There is no Vending Machine with such Id!" << endl;
		cin.ignore();
		pause();
	}

}

void deleteProductVm(vector<Stock> *stocks, vector<VendingMachine>* vms) {

	string idv;
	cout << "Enter Vending Machine Id:" << endl;
	cin >> idv;// validate id
	for (int i = 0; i < idv.size(); i++) {
		if (!isdigit(idv.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int idVm = atoi(idv.c_str());

	if (findVendingMachine(idVm, (*vms))) {

		int stockId;
		for (vector<VendingMachine>::iterator it = (*vms).begin(); it != (*vms).end(); ++it) {
			if ((*it).getIdStock() == idVm) {
				stockId = (*it).getIdStock();
				break;
			}
		}

		int prodId;
		string pId;
		cout << "Enter product id:" << endl;
		cin >> pId;// validate id
		if (!validateNumber(pId)) return;
		prodId = atoi(pId.c_str());

		if (findProductAtStock(stockId, prodId, (*stocks))) {

			for (vector<Stock>::iterator it = (*stocks).begin(); it != (*stocks).end(); ++it) {
				if ((*it).getIdStock() == stockId) {
					(*it).deleteProduct(prodId);
					break;
				}
			}
			cout << "The product has been successfully deleted!" << endl;
			cin.ignore();
			pause();
		}
		else
		{
			cout << "There is no product with such Id!" << endl;
			cin.ignore();
			pause();
		}
	}
	else {
		cout << "There is no Vending Machine with such Id!" << endl;
		cin.ignore();
		pause();
	}
}

string checkDate() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	std::string str(buffer);
	string shortdate = str.substr(0, 10);
	std::cout << shortdate << endl;
	return shortdate;
}

void sellProductVm(vector<Stock> *stocks, vector<VendingMachine>* vms) {

	string idv;
	cout << "Enter Vending Machine Id:" << endl;
	cin >> idv;// validate id
	for (int i = 0; i < idv.size(); i++) {
		if (!isdigit(idv.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return;
		}
	}
	int vmId = atoi(idv.c_str());

	if (findVendingMachine(vmId, (*vms))) {

		int stockId;
		for (vector<VendingMachine>::iterator it = (*vms).begin(); it != (*vms).end(); ++it) {
			if ((*it).getIdStock() == vmId) {
				stockId = (*it).getIdStock();
				break;
			}
		}

		int prodId;
		string pId;
		cout << "Enter product id:" << endl;
		cin >> pId;// validate id
		if (!validateNumber(pId)) return;
		prodId = atoi(pId.c_str());

		if (findProductAtStock(stockId, prodId, (*stocks))) {

			for (vector<Stock>::iterator it = (*stocks).begin(); it != (*stocks).end(); ++it) {
				if ((*it).getIdStock() == stockId) {

					int qnt;
					string q;
					cout << "Enter quantity to sell:" << endl;
					cin >> q;
					if (!validateNumber(q)) return;
					qnt = atoi(q.c_str());

					if (enoughQuantityStock((*it), prodId, qnt)) {
						(*it).updateProductSale(prodId, qnt);
											
						//insert sale´s data into database
						if (conn) {
							int qstate = 0;	
							string date = checkDate();
							string query = string("Insert into sales (id_vending_machine, date_sale,id_product, quantity) values (")
								.append(to_string(vmId)).append(", '")
								.append(date).append("', ")
								.append(to_string(prodId)).append(", ")
								.append(to_string(qnt)).append(")");
							const char* q = query.c_str();
							qstate = mysql_query(conn, q);
							if (qstate == 0) {
								cout << "Record Inserted into database" << endl;
								system("pause");
								
							}
							else {
								cout << "Insert Error" << mysql_error(conn) << endl;
								system("pause");
							}
						}

						cout << "The product has been successfully sold!" << endl;
						cin.ignore();
						pause();
						break;
					}
					else {
						cout << "Not enough quantity at the Stock!" << endl;
						cin.ignore();
						pause();
					}
				}
			}
		}
		else
		{
			cout << "There is no Product with such Id!" << endl;
			cin.ignore();
			pause();
		}
	}
	else {
		cout << "There is no Vending Machine with such Id!" << endl;
		cin.ignore();
		pause();
	}

}

bool enoughQuantityStock(Stock s, int prodId, int qnt) {

	vector<int>idproducts = s.getIdProducts();
	vector<int>qnts = s.getProductsQnts();
	int size = idproducts.size();
	for (int i = 0; i < size; i++) {
		if (idproducts.at(i) == prodId) {
			if (qnts.at(i) >= qnt)
				return true;
			else return false;
		}
	}
	return false;
}

void printStorehouse(vector<Product> products) {

	system("cls");
	system("color A");
	int i = 1;
	for (vector<Product>::iterator it = products.begin(); it != products.end(); ++it) {

		if (i % 5 == 0) {
			(*it).printProduct();
			system("pause");
			system("cls");
		}
		else {
			(*it).printProduct();
		}
		i++;
	}
	pause();
}

bool initializesales(vector<Sale>* sales) {

	if (conn) {
		cout << "Sales Records from database:" << endl;
		int qstate = mysql_query(conn, "SELECT * FROM sales");

		if (!qstate) {
			res = mysql_store_result(conn);

			while (row = mysql_fetch_row(res)) {
				int id = stoi(row[0]);
				int idVm = stoi(row[1]);
				int idProduct = stoi(row[3]);
				int	quantity = stoi(row[4]);
				Sale s(id, idVm, row[2], idProduct, quantity);
				(*sales).push_back(s);
			}
		int qstate = 0;
			return true;
		}
		else {
			cout << "Insert Error" << mysql_error(conn) << endl;
			system("pause");
			return false;
		}
	}
	else return false;
}

void printSales(vector<Product> products) {
	vector<Sale> sales;
	if (initializesales(&sales)) {
		system("cls");
		system("color A");
		if ((sales).size() != 0) {
			int i = 1;
			for (vector<Sale>::iterator it = (sales).begin(); it != (sales).end(); ++it) {

				int idProduct = (*it).getIdProduct();
				for (vector<Product>::iterator itr = products.begin(); itr != products.end(); ++itr) {

					if (idProduct == (*itr).getIdProduct()) {

						if (i % 5 == 0) {
							(*it).printSale((*itr));
							system("pause");
							system("cls");
						}
						else {
							(*it).printSale((*itr));
						}
						i++;
					}
				}
			}
			pause();
		}
	}
	else
	{
		cout << "There are not any sales yet!" << endl;
		pause();
	}
}

void printVms(vector<VendingMachine> vms) {

	system("cls");
	system("color A");
	int i = 1;
	for (vector<VendingMachine>::iterator it = vms.begin(); it != vms.end(); ++it) {

		if (i % 5 == 0) {
			(*it).printVendingMachine();
			system("pause");
			system("cls");
		}
		else {
			(*it).printVendingMachine();
		}
		i++;
	}
	pause();

}

void printStockAtVm(vector<VendingMachine> vms, vector<Stock> stocks) {

	system("cls");
	system("color A");
	int vmId;
	cout << "Enter Vending Machine id:" << endl;
	cin >> vmId;// validate id

	if (findVendingMachine(vmId, vms)) {
		int idStock;
		for (int i = 0; i < vms.size(); i++) {
			if (vms[i].getIdVm() == vmId) {
				idStock = vms[i].getIdStock();
				break;
			}
		}
		for (int j = 0; j < stocks.size(); j++) {

			if (stocks[j].getIdStock() == idStock) {
				cout << "Stock at the vending machine:" << endl;
				cout << "" << endl;
				stocks[j].printStock();
				pause();
				break;
			}
		}
		pause();
	}
	else {
		cout << "There is no Vending Machine with such Id!" << endl;
		cin.ignore();
		pause();
	}


}

bool validateNumber(string n) {
	for (int i = 0; i < n.size(); i++) {
		if (!isdigit(n.at(i))) {
			cout << "An integer number shall be inserted!" << endl;
			cin.ignore();
			pause();
			return false;
		}
	}
	return true;
}

bool validatePrice(string p) {
	int count = 0;
	for (int i = 0; i < p.size(); i++) {
		if (isdigit(p.at(i)) || ispunct(p.at(i))) {
			count++;
		}
	}
	if (p.size() != count) {
		cout << "A number shall be inserted!" << endl;
		cin.ignore();
		pause();
		return false;
	}
	return true;
}

bool exitProgram(bool wantToExit)
{
	cout << "Are you sure (Y/N)? ";
	char responce = '\0';
	cin >> responce;
	if (responce == 'y' || responce == 'Y')
		return true;
	else
		return false;

}

void optionInvalid(char option)
{
	cout << "\"" << option << "\"";
	cout << " is invalid option!\n" << endl;
	pause();

}

void endProgram()
{
	cout << "Thanks for using the program.";
	cout << endl;
	pause();
}
void pause()
{
	cout << "Press ENTER to continue ..." << endl;
	cin.get();
}