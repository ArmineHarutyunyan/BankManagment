#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "BankManagment.h"

	


	BankManagment::BankManagment()
		:clients(json::array()), 
		 accountNum(111)
	{
		std::ifstream ifs("Clients.json");
		if(ifs.is_open())
		{
			ifs >> clients;
			ifs.close();
		}
		else
			std::cout << "Unable to open file\n";

		initializeAccNumber();
	}

	void BankManagment::initializeAccNumber()
	{
		if(!clients.empty())
		{
			for(const auto& element : clients)
			{
				int currentValue = element["accountNumber"].get<int>();
				if(currentValue > accountNum)
				{
					accountNum = currentValue;
				}
			}
			++accountNum;	
		}	
	}

	void BankManagment::start() 
	{
		std::cout << std::setw(6) << "\nCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n";
		std::cout << std::setw(8) << "\n WELCOME TO THE MAIN MENU\n\n";
		std::cout << "1. Create new account\n" << "2. Update information of existing account\n";
		std::cout << "3. For transactions\n" << "4. Check the details of existing account\n";
		std::cout << "5. Removing existing account\n" << "6. View customer's list\n" << "7. Exit\n";
		std::cout << "\n Enter your choice:\n";
		int n{};
		std::cin >> n;
		switch(n)
		{
			case 1:
				createNewAccount();
				break;
			case 2:
				updateInformation();
				break;
			case 3:
				transactions();
				break;
			case 4:
				checkDetails();
				break;
			case 5:
				removeAccount();
				break;
			case 6:
				viewCustList();
				break;
			case 7:
				exit();
				break;
			default:
				std::cout << "Enter correct number please\n";
				
		}
	}

	void BankManagment::updateInformation()
	{
		std::cout << "Enter your account number and passport seriya please\n";
		int accountNum{};
		std::string passport{};
		std::cin >> accountNum >> passport;
		double amount;
		for(auto& element : clients)
		{
			if(element["accountNumber"].get<int>() == accountNum)
			{
				std::cout << "Enter amount you will add\n";
				std::cin >> amount;
				double d = element["amount"].get<double>();
				amount += d;
				element["amount"] = amount;
				break;
			}										
		 }
		 std::cout << "\n Now you have " << amount << " on your account\n";
		 start();
	}



	void BankManagment::createNewAccount()
	{
		std::cout << "Enter your name and lastname please\n";
		std::string fName{};
		std::string lName{};
		std::cin >> fName >> lName;
		std::cout << "Enter your passport seriya\n";
		std::string passport{};
		std::cin >> passport;
		std::cout << "Enter amount that you will keep on this account please\n";
		double amount{};
		std::cin >> amount;
		
		json client;
		client["name"] = fName;
		client["lastName"] = lName;
		client["passport"] = passport;
		client["accountNumber"] = accountNum++;
		client["amount"] = amount;
		clients.push_back(client);
		
		std::cout << "Your account successfully created. Your account number is  " << accountNum - 1 << "\n";
		start();
	}
	
	void BankManagment::removeAccount()
	{
		std::cout << "Enter your passport seriya please\n";
		std::string passport{};
		std::cin >> passport;
		for(json::iterator it = clients.begin(); it != clients.end(); ++it)
		{
			if((*it)["passport"].get<std::string>() == passport)
			{
				clients.erase(it);
			}
			break;
		}
		std::cout << "\nYour account successfully deleted\n";
		start();
	}

	bool BankManagment::isValidAccount(const std::string& passport, const int& acNum) const
	{
		for(const auto& element : clients)
		{
			if(element["accountNumber"].get<int>() == acNum && element["passport"].get<std::string>() == passport)
				return true;
		}
		return false;
	}

	void BankManagment::transactions()
	{
		std::cout << "Enter your account number and passport seriya please\n";
		int accountNum1{};
		std::string passport{};
		std::cin >> accountNum1 >> passport;
		if(isValidAccount(passport, accountNum1))
		{
			std::cout << "Enter amount and account number whom you will transfer\n";
			double amount;
			int accountNum2{};
			std::cin >> amount >> accountNum2;
			bool done = false;
			for(auto& element : clients)
			{
				if(element["accountNumber"].get<int>() == accountNum1 && element["amount"].get<double>() > amount)
				{
					double d = element["amount"].get<double>();
					d -= amount;
					element["amount"] = d;
					done = true;
					break;
				}
			}
			if(!done)
				std::cout << "You can't do this action\n";
			for(auto& element : clients)
			{
				if(element["accountNumber"].get<int>() == accountNum2 && done == true)
				{
					double d = element["amount"].get<double>();
					d += amount;
					element["amount"] = d;
					std::cout << "\n Your transfer successfully done\n";
					break;
				}
			}				
		}
		else
			std::cout << "Invalid account\n";
		start();
	}

	void BankManagment::viewCustList() 
	{
		std::cout << "\nCustomer's list\n";
		for(auto& element : clients)
		{
			std::cout << element["name"] << "\t" << element["lastName"] << "\t" << element["accountNumber"] << "\t" << element["amount"] << "\n";
		}
		start();
	}

	void BankManagment::checkDetails() 
	{
		std::cout << "Enter your account number and passport seriya please\n";
		int accountNum{};
		std::string passport{};
		std::cin >> accountNum >> passport;
		if(isValidAccount(passport, accountNum))
		{
			for(auto& element : clients)
			{
				if(element["passport"].get<std::string>() == passport)
				{
					std::cout << "You have " << element["amount"] << " on your account\n";
					break;
				}
			}
		}
		else
			std::cout << "Invalid account\n";
		start();
	}

	void BankManagment::exit()
	{
		std::ofstream ofs("Clients.json");
		if(ofs.is_open())
		{
			ofs << std::setw(4) << clients << "\n";
			ofs.close();
		}
	}

