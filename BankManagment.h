#pragma once


#include <string>
#include "json.hpp"

using json = nlohmann::json;


class BankManagment
{
	public:
		BankManagment();		
		void start();
		
	private:
		int accountNum;
  		json clients;  
		void initializeAccNumber();
		void createNewAccount();
		bool isValidAccount(const std::string& passport, const int& acNum);
		void transactions();
		void viewCustList();
		void updateInformation();
		void removeAccount();
		void checkDetails();
		void exit();	
};
