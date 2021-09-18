#ifndef PAY_METHODS
#define PAY_METHODS
#include <iostream>
#include <iomanip>

using namespace std;

enum class paymentMethods {
	CARD, CASH, PLUS_POINTS
};

/*string getStringPaymentMethod(paymentMethods payM) {
	if (payM == paymentMethods::CARD) return "card";
	if (payM == paymentMethods::CASH)return "cash";
	if (payM == paymentMethods::PLUS_POINTS) return "points";
	return "";
}
*/
#endif