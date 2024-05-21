#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
struct ComicBook {
    std::string title;
    int price;
};

bool compareBooks(const ComicBook& book1, const ComicBook& book2) {
    if (book1.price == book2.price) {
        return book1.title < book2.title;
    }
    return book1.price < book2.price;
}

std::vector<ComicBook> purchaseComicBooks(int cash, const std::vector<ComicBook>& books) {
    std::vector<ComicBook> purchasedBooks;

    // Sort the comic books based on price and title
    std::vector<ComicBook> sortedBooks = books;
    std::sort(sortedBooks.begin(), sortedBooks.end(), compareBooks);

    // Determine the maximum number of comic book pairs Sheldon can purchase
    for (size_t i = 0; i + 1 < sortedBooks.size(); i += 2) {
        if (sortedBooks[i].price + sortedBooks[i + 1].price <= cash) {
            // Purchase the comic book pair
            purchasedBooks.push_back(sortedBooks[i]);
            purchasedBooks.push_back(sortedBooks[i + 1]);
            cash -= sortedBooks[i].price + sortedBooks[i + 1].price;
        } else {
            break;  // Stop when there's not enough cash to buy another pair
        }
    }

    return purchasedBooks;
}

int main() {
    std::string comicNames, comicPrices;
    int cash;

    // Input the names of each comic book
    std::cout << "Enter the names of each comic book (comma separated): ";
    std::getline(std::cin, comicNames);

    // Input the prices of each comic book
    std::cout << "Enter the prices of each comic book (comma separated): ";
    std::getline(std::cin, comicPrices);

    // Parse the input into vectors
    std::vector<std::string> names, prices;
    std::istringstream nameStream(comicNames), priceStream(comicPrices);
    std::string nameToken, priceToken;

    while (std::getline(nameStream, nameToken, ',')) {
        names.push_back(nameToken);
    }

    while (std::getline(priceStream, priceToken, ',')) {
        prices.push_back(priceToken);
    }

    // Convert prices to integers
    std::vector<ComicBook> comicBooks;
    for (size_t i = 0; i < names.size() && i < prices.size(); ++i) {
        comicBooks.push_back({names[i], std::stoi(prices[i])});
    }

    // Input the cash held by Sheldon
    std::cout << "Enter the cash held by Sheldon: ";
    std::cin >> cash;

    std::vector<ComicBook> purchasedBooks = purchaseComicBooks(cash, comicBooks);

    if (purchasedBooks.empty()) {
        std::cout << "NONE" << std::endl;
    } else {
        // Display the purchased comic books in the specified format
        for (size_t i = 0; i < purchasedBooks.size(); i += 2) {
            std::cout << purchasedBooks[i].title << " - " << purchasedBooks[i].price << std::endl;
            std::cout << purchasedBooks[i + 1].title << " - " << purchasedBooks[i + 1].price << std::endl;
        }
    }

    return 0;
}