#include <iostream>
#include <sstream>
#include <string>

class Card {
public:
    Card(std::string cardHolderName)
        : Card(cardHolderName, 0, 0) {
    }

    Card(std::string cardHolderName, int euros, int cents) 
        :cardNumber(generateCardNumber()) {
        setEuroCents(cents);
        setEuros(euros);

        this->cardHolderName = cardHolderName;

        this->totalCreatedCount += 1;
        this->instanceCount += 1;
    }

    ~Card() {
        this->instanceCount -= 1;
    }

    static void resetState() {
        instanceCount = 0;
        totalCreatedCount = 0;
    }

    int getCardNumber() {
        return this->cardNumber;
    }

    std::string getCardHolderName() {
        return this->cardHolderName;
    }

    int getEuroCents() {
        return this->euroCents;
    }

    int getEuros() {
        return this->euros;
    }

    int getInstanceCount() {
        return this->instanceCount;
    }

    int getTotalCreatedCount() {
        return this->totalCreatedCount;
    }

    void setEuroCents(int newEuroCents) {
        if (newEuroCents < 0) {
            throw std::invalid_argument("Can not set euro cents to an integer smaller than 0.");
        }
        else if (99 < newEuroCents) {
            throw std::invalid_argument("Can not set euro cents to an integer larger than 99.");
        }

        this->euroCents = newEuroCents;
    }

    void setEuros(int newEuros) {
        if (newEuros < 0) {
            throw std::invalid_argument("Can not set euros to an integer larger than 99.");
        }

        this->euros = newEuros;
    }

    std::string toString() {
        std::stringstream ss;
        ss << "Card number: " << this->getCardNumber() << "\n";
        ss << "Card holder: " << this->getCardHolderName() << "\n";
        ss << "Balance: " << this->getEuros() << "." << this->getEuroCents() << "€\n";
        return ss.str();
    }


private:
    static int instanceCount;
    static int totalCreatedCount;

    std::string cardHolderName;
    const int cardNumber;
    int euroCents;
    int euros;

    int generateCardNumber() {
        return getTotalCreatedCount() + 1;
    }
};

int Card::instanceCount = 0;
int Card::totalCreatedCount = 0;

int main(int argc, char *argv[]) {
    return 0;
}
