#include <iostream>
#include "clsLoginScreen.h"
#include "Global.h"
#include "clsCurrency.h"

using namespace std;

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


