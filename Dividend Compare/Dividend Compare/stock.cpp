#include "stock.h"

stock::stock()
{
	fullName = "Default";
	ticker = "DFLT";
	price = 0;
	divYield = 0;
	divAnnualPay = 0;
	divPayPerDist = 0;
	payFreq = ANNUAL;
}

stock::stock(std::string fullN, std::string tick, double price, double divY, double divAP, double divPPD, frequency freq)
{
	fullName = fullN;
	ticker = tick;
	this->price = price;
	divYield = divY;
	divAnnualPay = divAP;
	divPayPerDist = divPPD;
	payFreq = freq;
}

stock::stock(std::string tick, double price, double divY, frequency freq)
{
	ticker = tick;
	this->price = price;
	divYield = divY;
	payFreq = freq;

	//unset values
	divAnnualPay = 0;
	divPayPerDist = 0;
	fullName = ticker;
}

stock::stock(std::string fullN, std::string tick, double price, double divY, frequency freq)
{
	fullName = fullN;
	ticker = tick;
	this->price = price;
	divYield = divY;
	payFreq = freq;

	//unset values
	divAnnualPay = 0;
	divPayPerDist = 0;
}

stock::stock(std::string tick, double price, double divPPD, frequency freq)
{
	ticker = tick;
	this->price = price;
	divPayPerDist = divPPD;
	payFreq = freq;

	//unset values
	fullName = ticker;
	divAnnualPay = 0;
	divYield = 0;
}

stock::stock(std::string fullN, std::string tick, double price, double divPPD, frequency freq)
{
	fullName = fullN;
	ticker = tick;
	this->price = price;
	divPayPerDist = divPPD;
	payFreq = freq;

	//unset values
	divAnnualPay = 0;
	divYield = 0;
}

void stock::set_Name(std::string fullN)
{
	fullName = fullN;
}

void stock::set_Tick(std::string tick)
{
	ticker = tick;
}

void stock::set_Price(double price)
{
	this->price = price;
}

void stock::set_Yield(double yield)
{
	divYield = yield;
}

void stock::set_Annual(double annual)
{
	divAnnualPay = annual;
}

void stock::set_Distr(double distr)
{
	divPayPerDist = distr;
}

void stock::set_Freq(frequency freq)
{
	payFreq = freq;
}

std::string stock::get_Name()
{
	return fullName;
}

std::string stock::get_Tick()
{
	return ticker;
}

double stock::get_Price()
{
	return price;
}

double stock::get_Yield()
{
	return divYield;
}

double stock::get_Annual()
{
	return divAnnualPay;
}

double stock::get_Distr()
{
	return divPayPerDist;
}

frequency stock::get_Freq()
{
	return payFreq;
}

std::string stock::get_All()
{
	std::string ret = fullName + " : " + ticker + "\n"
		+ "Price: " + std::to_string(price) + "\n"
		+ "Yield: " + std::to_string(divYield) + "%\n"
		+ "Annual Payout: " + std::to_string(divAnnualPay) + "\n"
		+ "Amount per distribution: " + std::to_string(divPayPerDist) + "\n"
		+ "Distribution Frequency: ";

	switch (payFreq)
	{
	case ANNUAL:
		ret += "Annual\n";
		break;
	case SEMI:
		ret += "Semi-annual\n";
		break;
	case QUARTER:
		ret += "Quarterly\n";
		break;
	case MONTHLY:
		ret += "Monthly\n";
		break;
	default:
		ret += "Unknown\n";
		break;
	}

	return ret;
}

void stock::calculate_Annual()
{
	//One must be set per constructor
	if (divYield != 0 && divPayPerDist == 0)
	{
		divAnnualPay = price * (divYield / 100);
	}
	else if (divYield == 0 && divPayPerDist != 0)
	{
		divAnnualPay = divPayPerDist * payFreq;
	}
	//If both are set, use distribution, usually more accurate
	else if (divYield != 0 && divPayPerDist != 0)
	{
		divAnnualPay = divPayPerDist * payFreq;
	}
	//If neither is set there is no dividend
	else
	{
		divAnnualPay = 0;
	}
}

void stock::calculate_Distribution()
{
	//Use yield if annual pay is set to 0, otherwise use annual pay
	(divAnnualPay == 0) ? divPayPerDist = (price * (divYield / 100)) / payFreq : divPayPerDist = divAnnualPay / payFreq;
}

void stock::calculate_Yield()
{
	//If Annual Pay is not 0 use to calculate yield %, if it is use Distribution pay
	(divAnnualPay != 0) ? divYield = (divAnnualPay / price) * 100 : divYield = ((divPayPerDist * payFreq) / price) * 100;
}

bool stock::equal(stock Other)
{
	//Returns true if same stock, false if not
	bool ret;

	bool name = (fullName._Equal(Other.get_Name()));
	bool tick = ticker._Equal(Other.get_Tick());

	return (name && tick) ? true : false;
}

stock stock::compare(stock Other)
{
	if (this->divAnnualPay >= Other.get_Annual() && this->price <= Other.get_Price())
	{
		return *this;
	}
	if (this->divYield >= Other.get_Yield() && this->price <= Other.get_Price())
	{
		return *this;
	}
	
	return Other;
}

stock stock::compare(stock Other, double cash)
{
	int s1, s2;
	double p1, p2;

	s1 = cash / this->price;
	s2 = cash / Other.get_Price;

	p1 = s1 * this->divAnnualPay;
	p2 = s2 * Other.get_Annual();

	return (p1 > p2) ? *this : Other;
}
