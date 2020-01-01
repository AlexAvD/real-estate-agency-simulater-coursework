#pragma once

#include "Date.h"
#include "Client.h"
#include "Preferences.h"

class Contract {
  private:
    Date date_;
    Date dedline_;
    
    std::string clientFullName_;
    std::string clientPassportData_;
    std::string typeOfService_;
    Preferences clientPreferences_;
    double commission_;
    
    
  

};