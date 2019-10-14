#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>

enum frequency {
	ANNUAL = 1,
	SEMI = 2,
	QUARTER = 4,
	MONTHLY = 12
};

class stock
{
private:
	//Stock name and ticker
	std::string fullName, ticker;
	//Stock price, dividend yield, dividend annual payout, dividend payout per distribution
	double price, divYield, divAnnualPay, divPayPerDist;
	//Payout frequency
	frequency payFreq;

public:
	//Constructors
	//default
	stock();
	//full
	stock(std::string fullN, std::string tick, double price, double divY, double divAP, double divPPD, frequency freq);
	//minimum using yield
	stock(std::string tick, double price, double divY, frequency freq);
	//minimum using pay per distribution
	stock(std::string tick, double price, double divPPD, frequency freq);
	//Minimums with full stock name
	stock(std::string fullN, std::string tick, double price, double divY, frequency freq);
	stock(std::string fullN, std::string tick, double price, double divPPD, frequency freq);


	//Setters
	void set_Name(std::string fullN);
	void set_Tick(std::string tick);
	void set_Price(double price);
	void set_Yield(double yield);
	void set_Annual(double annual);
	void set_Distr(double distr);
	void set_Freq(frequency freq);

	//Getters
	std::string get_Name();
	std::string get_Tick();
	double get_Price();
	double get_Yield();
	double get_Annual();
	double get_Distr();
	frequency get_Freq();
	std::string get_All();

	/**
	Operators
	**/

	//No return operators

	//Calculates and adds annual payout
	void calculate_Annual();

	//Calculates and adds distribution
	void calculate_Distribution();

	//Calculates and adds annual yield
	void calculate_Yield();

	//Return operators

	//Checks if two stocks are the same
	bool equal(stock Other);

	//Compares two stocks, returns better value option
	stock compare(stock Other);

	//Compares two stocks, returns better value option
	//Given a cash value for purchasing
	stock compare(stock Other, double cash);
};

