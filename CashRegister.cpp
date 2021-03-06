//File: CashRegister.cpp
//Date: 09/23/2018
//Usage:  This program will ask the user for input of items, price, quantity, and amount paid.
//***Making sure the right things are inputted are important***

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


string Uppercase(string string1) {
	for (int i = 0; i < string1.length(); i++) {
		string1[i] = toupper(string1[i]);
	}
	return string1;
}

int main()
{
	cout << "*** Enter \"done\" for the unit name when finished listing items ***\n";
	
	//TAX PROMPT (either items include tax already or fixed tax)
	float taxRate;
	cout << endl << "Tax Rate(%): ";
	cin >> taxRate;
	taxRate /= 100;
	//No Tax/ Tax included
	//taxRate = 0;


	bool done = false;
	while (!done) {
	//DEFINE EVERYTHING
		vector<string> unitName{};
		vector<float> unitPrice{}, totalUnitCost{};
		vector<unsigned int> unitQuantity{};
		float totalCost, amountPaid, totalTaxCost;
		unsigned int intChange, centChange, hundred, twenty, ten, five, one, quarter, dime, nickel, penny;
	
		//cin placeholders to push into vector
		string name; float price; unsigned int quantity;
		
		//I want time printed here; before prompting items

	//ITEM PROMPTS
		bool prompting = true;
		while (prompting) {
			cout << endl << "Unit name: ";
			cin >> name;
			name = Uppercase(name);
			if (name == "DONE") {
				prompting = false;
				break;
			}
			unitName.push_back(name);
			cout << "Price per " << name << ": ";
			cin >> price;
			unitPrice.push_back(price);
			cout << "Quantity purchased: ";
			cin >> quantity;
			unitQuantity.push_back(quantity);
		}

	//PURCHSE SUMMARY
		cout << endl << "$----- Cost Summary -----$" << endl
			<< left << setw(20) << "Item" << left << setw(11) << "Price" << left << setw(14) << "Quantity" << left << setw(10) << "Cost" << endl
			<< "--------------------------------------------------------" << endl;
	//PRINT TABLE
		//for some reason i cant use unitName.size() in the for loop parameters
		int items = unitName.size();
		int itemsSold = 0;

		for (int i = 0; i < items; i++) {
			totalUnitCost.push_back(unitPrice.at(i) * unitQuantity.at(i));
			cout << left << setw(20) << unitName.at(i) << "$" << left << setw(11) << unitPrice.at(i) << left << setw(15) << unitQuantity.at(i) << "$" << left << setw(10) << totalUnitCost.at(i) << endl;
		
			itemsSold += unitQuantity.at(i);
		}

		cout << "--------------------------------------------------------" << endl
			<< "Items sold: " << itemsSold << endl ;

	//INITIALIZE TOTAL COSTS
		totalCost = 0;
		for (int t = 0; t < items; t++) {
			totalCost += totalUnitCost.at(t);
		}
		totalTaxCost = totalCost + (taxRate * totalCost);

	//TAX
		cout << endl << "$----- Total Cost Before Tax -----$" << endl
			<< "$" << totalCost << endl;
		printf("Tax: $%.2f\n", totalCost * taxRate);	//<< "Tax: $" << totalCost * taxRate << endl;

	//COST + TAX
		cout << endl << "$----- Cost w/ Tax -----$" << endl
			<< "$";
		printf("%.2f\n", totalTaxCost);

	//AMOUNT PAID BY CUSTOMER
		cout << endl << "--------------------------------------------------------" << endl
			<< "Amount Paid($): ";
		cin >> amountPaid;

	//INITIALIZING CHANGE
		//x and y for readability
		float x = amountPaid - totalTaxCost;
		float y = floor(amountPaid - totalTaxCost);
		//Rounding depending on final change so i'm trying to account for it(because i worked with decimals instead of whole numbers)
		//at the end of a store day the total 1 cent overcharge and 1 cent giveaway in change should even out to 0 anyways.
		centChange = (((x - y) * 5 + 0.02) / 5) * 100;
		intChange = amountPaid - totalTaxCost;
		//cout << x << " " << y << endl << intChange << " " << centChange;

	//PRINT CHANGE
		cout << endl << "$----- Change -----$" << endl
			<< "$";
		printf("%.2f\n", amountPaid - totalTaxCost);

	//DETERMINE DENOMINATIONS
		//Try making it a for loop array thing(i'm too lazy)
		//ALSO Changes should end up as 0
		hundred = floor(intChange / 100);
		intChange %= 100;

		twenty = floor(intChange / 20);
		intChange %= 20;

		ten = floor(intChange / 10);
		intChange %= 10;

		five = floor(intChange / 5);
		intChange %= 5;

		one = intChange / 1;
		intChange %= 1;


		quarter = floor(centChange / 25);
		centChange %= 25;

		dime = floor(centChange / 10);
		centChange %= 10;

		nickel = floor(centChange / 5);
		centChange %= 5;
		//cout << intChange << " " << centChange << endl;
		penny = centChange / 1;
		centChange %= 1;

		//cout << intChange << " " << centChange;

	//PRINT DENOMINATIONS
		cout << endl << "--------------------------------------------------------" << endl
			<< "Denominations ..." << endl << endl
			<< left << setw(10) << "$100 Bills: " << right << setw(8) << hundred << endl
			<< left << setw(10) << "$20 Bills:" << right << setw(10) << twenty << endl
			<< left << setw(10) << "$10 Bills:" << right << setw(10) << ten << endl
			<< left << setw(10) << "$5 Bills:" << right << setw(10) << five << endl
			<< left << setw(10) << "$1 Bills:" << right << setw(10) << one << endl
			<< left << setw(10) << "Quarters:" << right << setw(10) << quarter << endl
			<< left << setw(10) << "Dimes:" << right << setw(10) << dime << endl
			<< left << setw(10) << "Nickels:" << right << setw(10) << nickel << endl
			<< left << setw(10) << "Pennies:" << right << setw(10) << penny << endl;

	//QUITING PROGRAM
		string response;
		cout << "\n\n\nNext customer? (y/n) : ";
		cin >> response;
		if (Uppercase(response) == "N") {
			done = true;
		}
	}
	return 0;
}