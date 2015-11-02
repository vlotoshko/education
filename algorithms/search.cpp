#include "search.h"

int testBst(int argc, char *argv[]) {

    if (argc > 2) {
        std::string fileName = argv[2];

        std::ifstream file;
        file.open (fileName);
        BST< std::string, int > bst;

        std::string word;
        while (file >> word)
        {
//            std::cout << word << std::endl;
            bst.put(word, 0);
        }

//        std::cout << "size: " << bst.size() << std::endl;
//        std::cout << "count: " << bst.valSum() << std::endl;
//        std::cout << "min: " << bst.min() << std::endl;
//        std::cout << "max: " << bst.max() << std::endl;
////        std::string key;
////        std::cin >> key;
////        std::cout << "floor: " << bst.floor(key) << std::endl;
////        std::cout << "ceiling: " << bst.ceiling(key) << std::endl;
//        std::cout << "select: " << bst.select(1) << std::endl;
//        std::cout << "rank \"love\": " << bst.rank("memory") << std::endl;
//        bst.deleteNode("love");
//        std::cout << "rank \"love\": " << bst.rank("memory") << std::endl;
//        bst.put("love", 0);
//        bst.print();
//        std::cout << std::endl;
//        auto v = bst.keys("f", "r");

//        for (auto e : v) {
//            std::cout << e << " ";
//        }
//        std::cout << std::endl;
    }
    return 0;
}
