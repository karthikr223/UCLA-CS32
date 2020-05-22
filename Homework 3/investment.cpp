
class Investment {
public:
	Investment(string p_name, int p_price);
	virtual ~Investment();
	virtual string name() const;
	virtual bool fungible() const = 0;
	virtual int purchasePrice() const;
	virtual string description() const = 0;
private:
	string investment_name;
	int investment_price;
};

class Painting : public Investment {
public:
	Painting(string p_name, int p_price);
	virtual ~Painting();
	virtual bool fungible() const { return false; };
	virtual string description() const;
};

class Stock :public Investment {
public:
	Stock(string p_name, int p_price, string p_id);
	virtual ~Stock();
	virtual bool fungible() const { return true; };
	virtual string description() const;

private:
	string id;
};

class House :public Investment {
public:
	House(string p_name, int p_price);
	virtual ~House();
	virtual bool fungible() const { return false; };
	virtual string description() const;

};


Investment::Investment(string p_name, int p_price):investment_name(p_name), investment_price(p_price){}

Investment::~Investment() {}

string Investment::name() const {
	return investment_name;
}

int Investment::purchasePrice() const {
	return investment_price;
}

Painting::Painting(string p_name, int p_price):Investment(p_name, p_price){}

Painting::~Painting() {
	cout << "Destroying " << this->name() << ", a painting" << endl;
}

string Painting::description() const {
	return "painting";
}

Stock::Stock(string p_name, int p_price, string p_id):Investment(p_name, p_price), id(p_id){}

Stock::~Stock() {
	cout << "Destroying " << this->name() << ", a stock holding" << endl;
}

string Stock::description() const {
	return ("stock trading as " + id);
}

House::House(string p_name, int p_price) :Investment(p_name, p_price) {}

House::~House() {
	cout << "Destroying the house " << this->name();
}

string House::description() const {
	return "house";
}

