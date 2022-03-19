#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>


const double BASIC_PIZZA_PRICE = 70.00;
const int BASIC_PIZZA_SIZE = 40 * 50;
const int OLIVES_PRICE = 10;
const int MUSHROOMS_PRICE = 12;
const int TOMATOS_PRICE = 9;
const int PINEAPPLES_PRICE = 14;
const double TAX = 1.17;
const int DELIVERY_PRICE = 15;
const int REGULAR_DOUGH_PRICE = 0;
const int VEGAN_DOUGH_PRICE = 5;
const int WHOLE_WHEAT_DOUGH_PRICE = 3;
const int GLUTEN_FREE_DOUGH_PRICE = 4;

//Matan kamin 313312886

struct CurrentPizza
{
	int pizzaLength; //Will hold the pizza length
	int pizzaWidth; //Will hold the pizza Width
	double pizzaRatio; //Will hold the ratio between the user pizza to the basic one (40*40)
	double mushroomsAmount; //Will hold the amount of mushrooms on the pizza
	double specificPizzaPrice; //Will hold the user's pizza price without toppings
	double toppingPrice; //Will hold the user's topping price without toppings
	double totalPizzaPrice; //Will hold the full price of the user pizza
	char doughType; //Will hold the dough type
	int doughPrice; //Will hold the dough price by the user choice
	double olivesRatio; //Will hold the ratio of olives that the user want on his pizza
	double mushroomsRatio; //Will hold the ratio of mushrooms that the user want on his pizza
	double tomatosRatio; //Will hold the ratio of tomatos that the user want on his pizza
	double pineapplesRatio; //Will hold the ratio of pineapples that the user want on his pizza
	int olivesQuarters; //Will hold the amount of olives quarters
	int mushroomsQuarters; //Will hold the amount of mushrooms quarters
	int tomatoesQuarters; //Will hold the amount of tomatoes quarters
	int pineapplesQuarters; //Will hold the amount of pinapples quarters
	double totalToppingAmount; //Will hold the total amount of toppings on the current pizza.
	double specificPizzaDoughPrice; //Will hold the user pizza's dough price
	char quarterOne; //Will hold the char of quarter one by his topping
	char quarterTwo; //Will hold the char of quarter two by his topping
	char quarterThree; //Will hold the char of quarter three by his topping
	char quarterFour; //Will hold the char of quarter four by his topping
};

int idLength_check(int id); //Will check the length of the user id
int get_right_check_digit(int id); //Will get the right check digit
int valid_check_digit(int id, int rightDigit); //Will check if the user check-digit is fine
void print_menu(); //Will print the menu
int pizzas_amount_check(); //Will check how much pizzas the user want
int pizza_length(); //Will get valid pizza length
int pizza_width(); //Will get valid pizza width
int chosing_dough(char* pdoughType); //Will get the user wanted dough type
double topping_ratio(int toppingAmount); //Will convert the topping number to ratio
void topping_amount(int toppingKind, double* ptoppingAmount, double* ptopping_ratio); //Will get the ratio of each topping
int delivery_choose(); //Will handle the delivery
void change(int fullPayment); //Will handle the change
int quarters_per_topping(double toppingRatio); //Will return the amount of quarters for single topping
void topping_per_quarter(struct CurrentPizza* C); //Will update each quarter char by his topping kind
void print_pizza_row(int width, char dough, char top_left, char top_right); //Will print row of the pizza
void print_pizza(struct CurrentPizza C); //Will print the whole pizza
int next_available_quarter(struct CurrentPizza c);

void main()
{
	int id; //Will hold th user ID number
	int rightDigit; //Will hold the right digit by the user id
	int deliveryChoice; //Will hold the user delivery price
	int pizzasAmount; //Will hold the amount of pizzas the the user want
	int pizzasCounter; //Will use us for iterate untill we reached to the user pizzas amount
	double totalOrderPrice = 0; //Will hold the cost of all the order (Without delivery and TAX)
	double fullPayment; //Will hold the cost of all the order with delivery and tax
	int userPayment = 0; //Will hold the amount of money the user entered
	int toppingNumber = 4; //will hold the number of different toppings options
	int toppingIndex; //counter for each different toppings
	double toppingAmount = 0; //Will hold the total amount of the topping om the current pizza


	struct CurrentPizza C;

	printf(" Welcome to MTA-Pizza!\n");
	printf("\n*****\n *** \n  *  \n");
	printf("\nPlease enter your ID number:\n");
	scanf("%d", &id);

	//Will check the id length
	id = idLength_check(id);

	//Will get the right check digit by the user ID
	rightDigit = get_right_check_digit(id);

	//Will the if the user id & check digit are fine
	id = valid_check_digit(id, rightDigit);

	//Will print the manu
	print_menu();

	//Will return the amount of pizzas that the user want
	pizzasAmount = pizzas_amount_check();


	//Will iterate by the number of pizzas the the user want
	for (pizzasCounter = 1, C.totalPizzaPrice = 0; pizzasCounter <= pizzasAmount; pizzasCounter++, totalOrderPrice = totalOrderPrice + C.totalPizzaPrice)
	{
		printf("\n*************************************************");
		printf("\nPizza #%d:\n", pizzasCounter);

		//Will return the current pizza lenght
		C.pizzaLength = pizza_length();

		//Will return the current pizza width
		C.pizzaWidth = pizza_width();

		//Will return the dough type & price
		C.doughPrice = chosing_dough(&C.doughType);

		//For reset the "Currentpizza" Struct values
		C.olivesRatio = 0;
		C.mushroomsRatio = 0;
		C.tomatosRatio = 0;
		C.pineapplesRatio = 0;
		C.olivesQuarters = 0;
		C.mushroomsQuarters = 0;
		C.tomatoesQuarters = 0;
		C.pineapplesQuarters = 0;
		C.quarterOne = ' ';
		C.quarterTwo = ' ';
		C.quarterThree = ' ';
		C.quarterFour = ' ';

		//For handle the toppings throught the pizza. Will iterate by the user wanted topping and return their amounts & number of quarters
		toppingAmount = 0;
		for (toppingIndex = 1; toppingIndex <= toppingNumber && toppingAmount < 1; toppingIndex++)
		{
			if (toppingIndex == 1)
			{
				topping_amount(toppingIndex, &toppingAmount, &C.olivesRatio);
				C.olivesQuarters = quarters_per_topping(C.olivesRatio);
			}
			else if (toppingIndex == 2 && toppingAmount < 1)
			{
				topping_amount(toppingIndex, &toppingAmount, &C.mushroomsRatio);
				C.mushroomsQuarters = quarters_per_topping(C.mushroomsRatio);
			}
			else if (toppingIndex == 3 && toppingAmount < 1)
			{
				topping_amount(toppingIndex, &toppingAmount, &C.tomatosRatio);
				C.tomatoesQuarters = quarters_per_topping(C.tomatosRatio);
			}
			else if (toppingIndex == 4 && toppingAmount < 1)
			{
				topping_amount(toppingIndex, &toppingAmount, &C.pineapplesRatio);
				C.pineapplesQuarters = quarters_per_topping(C.pineapplesRatio);
			}
		}

		//Will return the distribution of the topping throughout the pizza
		topping_per_quarter(&C);

		//Get the ratio between the user pizza to the basic one (40*40)
		C.pizzaRatio = (double)C.pizzaLength * C.pizzaWidth / BASIC_PIZZA_SIZE;

		//Get the user pizza price without toppings
		C.specificPizzaPrice = C.pizzaRatio * BASIC_PIZZA_PRICE;

		//Get the user total toppings price
		C.toppingPrice = ((C.olivesRatio * OLIVES_PRICE) + (C.mushroomsRatio * MUSHROOMS_PRICE) + (C.tomatosRatio * TOMATOS_PRICE) + (C.pineapplesRatio * PINEAPPLES_PRICE)) * C.pizzaRatio;

		//Get the user pizza's dough price
		C.specificPizzaDoughPrice = (C.pizzaRatio * C.doughPrice);

		//Get the user total pizza price (With toppings and dough prices)
		C.totalPizzaPrice = C.specificPizzaPrice + C.toppingPrice + C.specificPizzaDoughPrice;

		printf("\nPizza #%d details:\n*******************\nPizza size: %dx%d\nPizza price (without tax): %.2lf\n", pizzasCounter, C.pizzaLength, C.pizzaWidth, C.totalPizzaPrice);

		//Will print the whole pizza
		print_pizza(C);

	}

	//Get the price of the delivery (if there is one)
	deliveryChoice = delivery_choose();

	//Get the user total pizza price (With toppings and delivery)
	totalOrderPrice = totalOrderPrice + deliveryChoice;

	//Get the price of the whole order with delivery and TAX
	fullPayment = totalOrderPrice * TAX;

	printf("\nYour order details:\n*******************\nID number: %09d", id);
	printf("\nNumber of pizzas: %d\n", pizzasAmount);
	if (deliveryChoice > 0)
		printf("Delivery\n");
	else
		printf("Pick-up\n");

	printf("Total price: %.2lf", totalOrderPrice);
	printf("\nTotal price with tax (rounded down): %d\n", (int)fullPayment);

	//Will get the user payment & handle the change
	change((int)fullPayment);
}



int idLength_check(int id)
{
	while (id / 1000000000 > 0 || id <= 0)
	{
		printf("Invalid ID number! Try again.");
		printf("\nPlease enter your ID number:\n");
		scanf("%d", &id);
	}
	return id;
}

int get_right_check_digit(int id)
{
	int counter;
	int idWithoutCheckDigit = id / 10; //The id without the check digit
	int lastDigit;
	int sum = 0;
	int rightDigit; //The valid check digit.

	for (counter = 1; idWithoutCheckDigit > 0; counter++)
	{
		if (counter % 2 == 1)
		{
			lastDigit = idWithoutCheckDigit % 10;
			sum = sum + (lastDigit * 2) % 10 + (lastDigit * 2) / 10;
			idWithoutCheckDigit = idWithoutCheckDigit / 10;
		}
		else if (counter % 2 == 0)
		{
			lastDigit = idWithoutCheckDigit % 10;
			sum = sum + lastDigit;
			idWithoutCheckDigit = idWithoutCheckDigit / 10;
		}
	}
	rightDigit = 10 - (sum % 10);
	return rightDigit;
}

int valid_check_digit(int id, int rightDigit)
{
	int checkDigit = id % 10; //The user check-digit


	while (rightDigit != checkDigit)
	{
		printf("Invalid check digit! Try again.");
		printf("\nPlease enter your ID number:\n");
		scanf("%d", &id);
		id = idLength_check(id);
		rightDigit = get_right_check_digit(id);
		checkDigit = id % 10;
	}
	return id;
}

void print_menu()
{
	printf("\nOur menu:\n*********\nBasic pizza: %.2lf NIS for 40x50 size pizza\n\nToppings for basic size pizza:\nOlives: %d NIS\nMushrooms: %d NIS\nTomatoes: 9 NIS\nPineapple: 14 NIS\n\n", BASIC_PIZZA_PRICE, OLIVES_PRICE, MUSHROOMS_PRICE);
	printf("Dough type for basic size pizza:\nRegular: %d NIS\nVegan: %d NIS\nWhole wheat: %d NIS\nGluten free: %d NIS\n", REGULAR_DOUGH_PRICE, VEGAN_DOUGH_PRICE, WHOLE_WHEAT_DOUGH_PRICE, GLUTEN_FREE_DOUGH_PRICE);

}

int pizzas_amount_check()
{
	int pizzasAmount;

	printf("\nHow many pizzas would you like to order? ");
	scanf("%d", &pizzasAmount);

	while (pizzasAmount <= 0)
	{
		printf("Invalid choice! Try again.");
		printf("\n\nHow many pizzas would you like to order? ");
		scanf("%d", &pizzasAmount);
	}
	return pizzasAmount;
}

int pizza_length()
{
	int pizzaLength;

	printf("\nPlease enter your pizza's length (cm): ");
	scanf("%d", &pizzaLength);
	while (pizzaLength < 10 || pizzaLength > 40 || pizzaLength % 2 == 1)
	{
		printf("Invalid length! Try again.");
		printf("\nPlease enter your pizza's length (cm): ");
		scanf("%d", &pizzaLength);
	}
	return pizzaLength;
}

int pizza_width()
{
	int pizzaWidth;

	printf("Please enter your pizza's width (cm): ");
	scanf("%d", &pizzaWidth);
	while (pizzaWidth < 10 || pizzaWidth > 80 || pizzaWidth % 2 == 1)
	{
		printf("Invalid width! Try again.");
		printf("\nPlease enter your pizza's width (cm): ");
		scanf("%d", &pizzaWidth);
	}
	return pizzaWidth;
}

int chosing_dough(char* pdoughType)
{
	char doughType;
	int doughPrice;

	printf("\nPlease enter the pizza's dough type:\nr - for regular\nv - for vegan\nw - for whole wheat\nf - for gluten-free\n");
	scanf(" %c", &doughType);

	while (doughType != 'r' && doughType != 'v' && doughType != 'w' && doughType != 'f')
	{
		printf("Invalid choice! Try again.");
		printf("\n\nPlease enter the pizza's dough type:\nr - for regular\nv - for vegan\nw - for whole wheat\nf - for gluten-free\n");
		scanf(" %c", &doughType);
	}

	*pdoughType = doughType;

	switch (doughType)
	{
	case 'r':
		doughPrice = REGULAR_DOUGH_PRICE;
		break;
	case 'v':
		doughPrice = VEGAN_DOUGH_PRICE;
		break;
	case 'w':
		doughPrice = WHOLE_WHEAT_DOUGH_PRICE;
		break;
	case 'f':
		doughPrice = GLUTEN_FREE_DOUGH_PRICE;
		break;
	}
	return doughPrice;
}

void topping_amount(int toppingKind, double* ptoppingAmount, double* ptopping_ratio)
{
	int olivesAmount; //Will hold the user choice following the olives amount
	int mushroomsAmount; //Will hold the user choice following the mushrooms amount
	int tomatosAmount; //Will hold the user choice following the tomatos amount
	int pineapplesAmount; //Will hold the user choice following the pineapples amount


	switch (toppingKind)
	{
	case 1:
		printf("\nPlease choose the toppings:\n\n");
		printf("Olives (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
		scanf("%d", &olivesAmount);

		while (olivesAmount != 0 && olivesAmount != 1 && olivesAmount != 2 && olivesAmount != 3)
		{
			printf("Invalid choice! Try again.");
			printf("Olives (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
			scanf("%d", &olivesAmount);
			*ptoppingAmount = topping_ratio(olivesAmount) + *ptoppingAmount;
		}
		*ptopping_ratio = topping_ratio(olivesAmount);
		*ptoppingAmount = topping_ratio(olivesAmount) + *ptoppingAmount;
		break;
	case 2:
		if (*ptoppingAmount < 1)
		{
			printf("\nMushrooms (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
			scanf("%d", &mushroomsAmount);

			while (mushroomsAmount != 0 && mushroomsAmount != 1 && mushroomsAmount != 2 && mushroomsAmount != 3)
			{
				printf("Invalid choice! Try again.");
				printf("Mushrooms (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
				scanf("%d", &mushroomsAmount);
			}
			*ptoppingAmount = topping_ratio(mushroomsAmount) + *ptoppingAmount;

			while (*ptoppingAmount > 1)
			{
				*ptoppingAmount = *ptoppingAmount - topping_ratio(mushroomsAmount);
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				printf("\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
				scanf("%d", &mushroomsAmount);
				*ptoppingAmount = topping_ratio(mushroomsAmount) + *ptoppingAmount;
			}
			*ptopping_ratio = topping_ratio(mushroomsAmount);
		}
		break;

	case 3:
		if (*ptoppingAmount < 1)
		{
			printf("\nTomatos (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
			scanf("%d", &tomatosAmount);

			while (tomatosAmount != 0 && tomatosAmount != 1 && tomatosAmount != 2 && tomatosAmount != 3)
			{
				printf("Invalid choice! Try again.");
				printf("Tomatos (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
				scanf("%d", &tomatosAmount);
			}
			*ptoppingAmount = topping_ratio(tomatosAmount) + *ptoppingAmount;

			while (*ptoppingAmount > 1)
			{
				*ptoppingAmount = *ptoppingAmount - topping_ratio(tomatosAmount);
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				printf("\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
				scanf("%d", &tomatosAmount);
				*ptoppingAmount = topping_ratio(tomatosAmount) + *ptoppingAmount;
			}
			*ptopping_ratio = topping_ratio(tomatosAmount);
		}
		break;

	case 4:
		if (*ptoppingAmount < 1)
		{
			printf("\nPineapple (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
			scanf("%d", &pineapplesAmount);

			while (pineapplesAmount != 0 && pineapplesAmount != 1 && pineapplesAmount != 2 && pineapplesAmount != 3)
			{
				printf("Invalid choice! Try again.");
				printf("Pineapples (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
				scanf("%d", &pineapplesAmount);
			}
			*ptoppingAmount = topping_ratio(pineapplesAmount) + *ptoppingAmount;

			while (*ptoppingAmount > 1)
			{
				*ptoppingAmount = *ptoppingAmount - topping_ratio(pineapplesAmount);
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				printf("\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
				scanf("%d", &pineapplesAmount);
				*ptoppingAmount = topping_ratio(pineapplesAmount) + *ptoppingAmount;
			}
			*ptopping_ratio = topping_ratio(pineapplesAmount);
		}
		break;
	}
}

double topping_ratio(int toppingAmount)
{
	double toppingRatio = 0; //will hold the ratio of the topping throught the user's pizza 

	switch (toppingAmount)
	{
	case 0:
		toppingRatio = 0;
		break;
	case 1:
		toppingRatio = 1;
		break;
	case 2:
		toppingRatio = 0.5;
		break;
	case 3:
		toppingRatio = 0.25;
		break;
	}
	return toppingRatio;
}

int delivery_choose()
{
	int wantDelivery; //Will hold the user choice following the delivery options
	int deliveryCost; //Will hold the delivery cost (if relevant)

	printf("\n*************************************************\nDo you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
	scanf("%d", &wantDelivery);
	while (wantDelivery != 1 && wantDelivery != 0)
	{
		printf("Invalid choice! Try again.");
		printf("\nDo you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
		scanf("%d", &wantDelivery);

	}
	deliveryCost = wantDelivery * DELIVERY_PRICE;

	return deliveryCost; //Get the price of the delivery (if there is one)

}

void change(int fullPayment)
{
	int paymentLeft; //Will hold who much the user pay
	int change = 0; //Will hold the user change
	int userPayment = 0; //Will hold the amount of money the user entered


	for (paymentLeft = (int)fullPayment; paymentLeft > 0; paymentLeft = paymentLeft - userPayment)
	{
		printf("\nPlease enter your payment: ");
		scanf("%d", &userPayment);
		if (userPayment < paymentLeft)
			printf("\nYour remaining balance is: %d", paymentLeft - userPayment);
	}

	change = paymentLeft * -1;
	if (change > 0)
		printf("Your change is %d NIS using:", change);
	if (change / 10 > 0)
	{
		printf("\n%d coin(s) of ten", change / 10);
		change = change % 10;
	}
	if (change / 5 > 0)
	{
		printf("\n%d coin(s) of five", change / 5);
		change = change % 5;
	}
	if (change / 2 > 0)
	{
		printf("\n%d coin(s) of two", change / 2);
		change = change % 2;
	}
	if (change / 1 > 0)
	{
		printf("\n%d coin(s) of one", change / 1);
		change = change % 1;
	}
	printf("\nThank you for your order!");
}

int quarters_per_topping(double toppingRatio)
{
	int numberOfQuarters = 0;

	numberOfQuarters = (int)(4 * toppingRatio);

	return numberOfQuarters;
}

void topping_per_quarter(struct CurrentPizza* C)
{	//For handling olives quarters 
	if ((*C).olivesQuarters == 1)
		(*C).quarterOne = 'O';
	else if ((*C).olivesQuarters == 2)
		(*C).quarterOne = (*C).quarterTwo = 'O';
	else if ((*C).olivesQuarters == 4)
		(*C).quarterOne = (*C).quarterTwo = (*C).quarterThree = (*C).quarterFour = 'O';

	//For handling mushrooms quarters 
	if ((*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 0)
		(*C).quarterOne = 'M';
	else if ((*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 1)
		(*C).quarterTwo = 'M';
	else if ((*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 2)
		(*C).quarterThree = 'M';
	else if ((*C).mushroomsQuarters == 2 && (*C).olivesQuarters == 0)
		(*C).quarterOne = (*C).quarterTwo = 'M';
	else if ((*C).mushroomsQuarters == 2 && (*C).olivesQuarters == 1)
		(*C).quarterTwo = (*C).quarterThree = 'M';
	else if ((*C).mushroomsQuarters == 2 && (*C).olivesQuarters == 2)
		(*C).quarterThree = (*C).quarterFour = 'M';
	else if ((*C).mushroomsQuarters == 4)
		(*C).quarterOne = (*C).quarterTwo = (*C).quarterThree = (*C).quarterFour = 'M';

	//For handling tomatoes quarters 
	if ((*C).tomatoesQuarters == 1 && (*C).mushroomsQuarters == 0 && (*C).olivesQuarters == 0)
		(*C).quarterOne = 'T';
	else if ((*C).tomatoesQuarters == 1 && (*C).olivesQuarters == 1 && (*C).mushroomsQuarters == 0)
		(*C).quarterTwo = 'T';
	else if ((*C).tomatoesQuarters == 1 && (*C).olivesQuarters == 0 && (*C).mushroomsQuarters == 1)
		(*C).quarterTwo = 'T';
	else if ((*C).tomatoesQuarters == 1 && (*C).olivesQuarters == 1 && (*C).mushroomsQuarters == 1)
		(*C).quarterThree = 'T';
	else if ((*C).tomatoesQuarters == 1 && (*C).olivesQuarters == 1 && (*C).mushroomsQuarters == 2)
		(*C).quarterFour = 'T';
	else if ((*C).tomatoesQuarters == 1 && (*C).olivesQuarters == 2 && (*C).mushroomsQuarters == 1)
		(*C).quarterFour = 'T';
	else if ((*C).tomatoesQuarters == 2 && (*C).olivesQuarters == 1 && (*C).mushroomsQuarters == 0)
		(*C).quarterTwo = (*C).quarterThree = 'T';
	else if ((*C).tomatoesQuarters == 2 && (*C).olivesQuarters == 0 && (*C).mushroomsQuarters == 1)
		(*C).quarterTwo = (*C).quarterThree = 'T';
	else if ((*C).tomatoesQuarters == 2 && (*C).olivesQuarters == 1 && (*C).mushroomsQuarters == 1)
		(*C).quarterThree = (*C).quarterFour = 'T';
	else if ((*C).tomatoesQuarters == 2 && (*C).olivesQuarters == 2)
		(*C).quarterThree = (*C).quarterFour = 'T';
	else if ((*C).tomatoesQuarters == 2 && (*C).mushroomsQuarters == 2)
		(*C).quarterThree = (*C).quarterFour = 'T';
	else if ((*C).tomatoesQuarters == 4)
		(*C).quarterOne = (*C).quarterTwo = (*C).quarterThree = (*C).quarterFour = 'T';

	//For handling pineapples quarters 
	if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 0 && (*C).mushroomsQuarters == 0 && (*C).olivesQuarters == 0)
		(*C).quarterOne = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 1 && (*C).mushroomsQuarters == 0 && (*C).olivesQuarters == 0)
		(*C).quarterTwo = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 0 && (*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 0)
		(*C).quarterTwo = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 0 && (*C).mushroomsQuarters == 0 && (*C).olivesQuarters == 1)
		(*C).quarterTwo = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 1 && (*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 0)
		(*C).quarterThree = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 1 && (*C).mushroomsQuarters == 0 && (*C).olivesQuarters == 1)
		(*C).quarterThree = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 0 && (*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 1)
		(*C).quarterThree = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 1 && (*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 1)
		(*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 0 && (*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 2)
		(*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 1 && (*C).mushroomsQuarters == 0 && (*C).olivesQuarters == 2)
		(*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 0 && (*C).mushroomsQuarters == 2 && (*C).olivesQuarters == 1)
		(*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 1 && (*C).mushroomsQuarters == 2 && (*C).olivesQuarters == 0)
		(*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 2 && (*C).mushroomsQuarters == 1 && (*C).olivesQuarters == 0)
		(*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 1 && (*C).tomatoesQuarters == 2 && (*C).mushroomsQuarters == 0 && (*C).olivesQuarters == 1)
		(*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 2 && (*C).olivesQuarters == 2 && (*C).mushroomsQuarters == 0 && (*C).tomatoesQuarters == 0)
		(*C).quarterThree = (*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 2 && (*C).mushroomsQuarters == 2 && (*C).olivesQuarters == 0 && (*C).tomatoesQuarters == 0)
		(*C).quarterThree = (*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 2 && (*C).tomatoesQuarters == 2 && (*C).mushroomsQuarters == 0 && (*C).olivesQuarters == 0)
		(*C).quarterThree = (*C).quarterFour = 'P';
	else if ((*C).pineapplesQuarters == 4)
		(*C).quarterOne = (*C).quarterTwo = (*C).quarterThree = (*C).quarterFour = 'P';
}

void print_pizza(struct CurrentPizza C) {
	int half_length, row_loc = 0;

	for (row_loc = 0; row_loc < C.pizzaWidth; row_loc++) {
		printf("%c", C.doughType);
	}
	printf("\n");
	half_length = (C.pizzaLength - 2) / 2;
	for (row_loc = 0; row_loc < half_length; row_loc++) {
		print_pizza_row(C.pizzaWidth, C.doughType, C.quarterFour, C.quarterOne);
	}
	for (row_loc = 0; row_loc < half_length; row_loc++) {
		print_pizza_row(C.pizzaWidth, C.doughType, C.quarterThree, C.quarterTwo);
	}
	for (row_loc = 0; row_loc < C.pizzaWidth; row_loc++) {
		printf("%c", C.doughType);
	}
	printf("\n");
}

void print_pizza_row(int width, char dough, char top_left, char top_right) {
	int topping_length, i;
	topping_length = (width - 2) / 2;
	printf("%c", dough);
	for (i = 0; i < topping_length; i++) {
		printf("%c", top_left);
	}
	for (i = 0; i < topping_length; i++) {
		printf("%c", top_right);
	}
	printf("%c\n", dough);

}
