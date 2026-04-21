#include <iostream>
#include "solution.h"

int main() {
    // Basic tests similar to provided sample
    std::cout << "======== Constructor Test ========\n";
    std::vector<int> b1{10,20,30,40,50,60,70,80,90,97};
    SpeedCircularLinkedList<int, 97> l1(b1);
    l1.print();

    std::cout << "============ Size Test ============\n";
    std::vector<int> b2{10,30,40,50,53};
    SpeedCircularLinkedList<int, 53> l2(b2);
    std::cout << "size = " << l2.size() << '\n';

    std::cout << "============ Put Test ============\n";
    std::vector<int> b3{10,30,50,70,90,110,130,150,170,197};
    SpeedCircularLinkedList<int, 197> l3(b3);
    l3.put("19260817", 0); // expect bound=150
    l3.put("What a pity!", 1); // expect bound=150
    l3.put("ACM2025", 6); // expect bound=50
    l3.print();

    std::cout << "=========== Get Test =============\n";
    std::vector<int> b4{50,250,450,800,1000,1300,1350,1600,1850,2017};
    SpeedCircularLinkedList<std::string, 2017> l4(b4);
    l4.put("Butterworth", "07:50");
    l4.put("Ipoh", "09:37");
    l4.put("KL Sentral", "12:15");
    l4.put("Seremban", "13:38");
    l4.put("Gemas", "14:42");
    l4.put("Segamat", "14:57");
    std::cout << l4.get("KL Sentral") << '\n';
    std::cout << l4.get("Gemas") << '\n';
    std::cout << l4.get("Butterworth") << '\n';

    return 0;
}

