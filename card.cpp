#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    static int getInstanceCount() {
        return instanceCount;
    }

    static int getTotalCreatedCount() {
        return totalCreatedCount;
    }

    static void resetState() {
        instanceCount = 0;
        totalCreatedCount = 0;
    }

    const std::string getCardHolderName() {
        return this->cardHolderName;
    }

    int getCardNumber() {
        return this->cardNumber;
    }

    int getEuroCents() {
        return this->euroCents;
    }

    int getEuros() {
        return this->euros;
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

class Tests {
public:
    Tests()
        : Tests(false) {
    }

    Tests(bool verboseOption)
        : verbose(verboseOption) {
        this->testFunctionVector.push_back(unitTest1);
        this->testFunctionVector.push_back(unitTest2);
        this->testFunctionVector.push_back(unitTest3);
        this->testFunctionVector.push_back(unitTest4);
        this->testFunctionVector.push_back(unitTest5);
    }

    bool runTests (std::ostream& oStrm) {
        int succeeded = 0, testCount;
        testCount = testFunctionVector.size();

        for(int i = 0; i < testCount ; i++){
            Card::resetState();

            if (testFunctionVector[i]()) {
                oStrm << "Test " << i + 1 << " passed\n";
                ++succeeded;
            }
            else {
                oStrm << "Test " << i + 1 << " failed\n";
            }

        }
        if (succeeded < testCount) {
            oStrm << "❌ Some tests failed (passed " << succeeded << "/" << testCount << ")\n";
            return false;
        }

        oStrm << "✓ All tests passed (passed " << succeeded << "/" << testCount << ")\n";
        return true;
    }

private:
    const bool verbose;

    std::vector<bool (*)()> testFunctionVector;

    static void check(bool& isSuccefulState, bool logicStatement) {
        isSuccefulState = isSuccefulState && logicStatement;
    }

    static bool unitTest1() {
        bool isSuccessful = true;

        Card card = Card("John Doe", 7, 89);

        check(
            isSuccessful,
            card.getCardHolderName() ==
            "John Doe"
        );

        check(
            isSuccessful,
            card.getCardNumber() == 1
        );

        check(
            isSuccessful,
            card.getEuroCents() == 89
        );

        check(
            isSuccessful,
            card.getEuros() == 7
        );

        check(
            isSuccessful,
            card.getInstanceCount() == 1
        );

        check(
            isSuccessful,
            card.getTotalCreatedCount() == 1
        );

        check(
            isSuccessful,
            card.toString() ==
            "Card number: 1\n"
            "Card holder: John Doe\n"
            "Balance: 7.89€\n"
        );

        return isSuccessful;
    }

    static bool unitTest2() {
        bool isSuccessful = true;

        Card card = Card("John Doe", 7, 89);

        try {
            card.setEuroCents(-1);
        }
        catch(...) {
        }
        check(
            isSuccessful,
            card.getEuroCents() == 89
        );

        try {
            card.setEuroCents(100);
        }
        catch(...) {
        }
        check(
            isSuccessful,
            card.getEuroCents() == 89
        );


        card.setEuroCents(50);
        check(
            isSuccessful,
            card.getEuroCents() == 50
        );

        try {
            card.setEuros(-1);
        }
        catch(...) {
        }
        check(
            isSuccessful,
            card.getEuros() == 7
        );

        card.setEuros(10);
        check(
            isSuccessful,
            card.getEuros() == 10
        );

        return isSuccessful;
    }

    static bool unitTest3() {
        bool isSuccessful = true;

        Card card = Card("John Doe", 7, 89);

        try {
            card.setEuroCents(-1);

            // Did not raise exception
            isSuccessful = false;
        }
        catch(const std::invalid_argument& e) {
            // Got an exception that was excepted, gets a pass
        }
        catch(...) {
            // Got an unexpected exception type
            isSuccessful = false;
        }

        try {
            card.setEuroCents(100);

            // Did not raise exception
            isSuccessful = false;
        }
        catch(const std::invalid_argument& e) {
            // Got an exception that was excepted, gets a pass
        }
        catch(...) {
            // Got an unexpected exception type
            isSuccessful = false;
        }

        try {
            card.setEuros(-1);

            // Did not raise exception
            isSuccessful = false;
        }
        catch(const std::invalid_argument& e) {
            // Got an exception that was excepted, gets a pass
        }
        catch(...) {
            // Got an unexpected exception type
            isSuccessful = false;
        }

        return isSuccessful;
    }

    static bool unitTest4() {
        bool isSuccessful = true;

        Card *card1 = new Card("John Doe");
        Card *card2 = new Card("Bob Doe");

        check(
            isSuccessful,
            card1->getCardNumber() == 1
        );

        check(
            isSuccessful,
            card2->getCardNumber() == 2
        );

        delete card2;

        Card *card3 = new Card("Matt Doe");

        check(
            isSuccessful,
            card3->getCardNumber() == 3
        );

        return isSuccessful;
    }

    static bool unitTest5() {
        bool isSuccessful = true;

        check(
            isSuccessful,
            Card::getInstanceCount() == 0
        );
        check(
            isSuccessful,
            Card::getTotalCreatedCount() == 0
        );

        Card *card1 = new Card("John Doe");

        check(
            isSuccessful,
            Card::getInstanceCount() == 1
        );
        check(
            isSuccessful,
            Card::getTotalCreatedCount() == 1
        );

        Card *card2 = new Card("Bob Doe");

        check(
            isSuccessful,
            Card::getInstanceCount() == 2
        );
        check(
            isSuccessful,
            Card::getTotalCreatedCount() == 2
        );

        delete card1;

        check(
            isSuccessful,
            Card::getInstanceCount() == 1
        );
        check(
            isSuccessful,
            Card::getTotalCreatedCount() == 2
        );

        Card *card3 = new Card("Matt Doe");

        check(
            isSuccessful,
            Card::getInstanceCount() == 2
        );
        check(
            isSuccessful,
            Card::getTotalCreatedCount() == 3
        );

        delete card2;
        delete card3;

        check(
            isSuccessful,
            Card::getInstanceCount() == 0
        );
        check(
            isSuccessful,
            Card::getTotalCreatedCount() == 3
        );

        return isSuccessful;
    }
};

int main(int argc, char *argv[]) {
    Tests testClass = Tests(true);

    testClass.runTests(std::cout);

    return 0;
}
