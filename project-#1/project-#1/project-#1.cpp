#include <iostream>
#include "clsLoginScreen.h"
#include "Global.h"
#include "clsCurrency.h"

using namespace std;

static void _PrintCurrecy(clsCurrency Currency)
{
    cout << "\nCurrency Card:\n";
    cout << "__________________________________\n";
    cout << "\nCourntry    : " << Currency.Country();
    cout << "\nCode        : " << Currency.CurrencyCode();
    cout << "\nName        : " << Currency.CurrencyName();
    cout << "\nRate(1$) =  : " << Currency.Rate();
    cout << "\n__________________________________\n";
}

int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
    
    system("Pause>0");
    return 0;
}


