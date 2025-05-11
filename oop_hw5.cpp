#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Product {
public:
    string name;
    string description;
    float price;
    int quantity;

    Product(string name, string description, float price, int quantity)
        : name(name), description(description), price(price), quantity(quantity) {
    }

    void changePrice(float newPrice) {
        price = newPrice;
    }

    void decreaseQuantity(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
        }
        else {
            cout << "���������� ������� ������ � ��������." << endl;
        }
    }

    void increaseQuantity(int amount) {
        quantity += amount;
    }
};

class Cart {
public:
    vector<pair<Product*, int>> items;

    void addProduct(Product* product, int quantity) {
        if (product->quantity >= quantity) {
            items.push_back({ product, quantity });
            product->decreaseQuantity(quantity);
        }
        else {
            cout << "���������� ������� ������ ��� ��������� � �����." << endl;
        }
    }

    void removeProduct(string productName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->first->name == productName) {
                it->first->increaseQuantity(it->second);
                items.erase(it);
                return;
            }
        }
        cout << "����� �� �������� � ������." << endl;
    }

    float calculateTotal() {
        float total = 0;
        for (const auto& item : items) {
            total += item.first->price * item.second;
        }
        return total;
    }

    void clearCart() {
        for (auto& item : items) {
            item.first->increaseQuantity(item.second);
        }
        items.clear();
    }
};

class Order {
public:
    string orderID;
    vector<pair<Product*, int>> items;
    float totalAmount;
    string status;

    Order(string orderID, vector<pair<Product*, int>> items, float totalAmount)
        : orderID(orderID), items(items), totalAmount(totalAmount), status("� �������") {
    }

    void changeStatus(string newStatus) {
        status = newStatus;
    }

    void showOrderInfo() {
        cout << "���������� #" << orderID << endl;
        cout << "������: " << status << endl;
        cout << "�������� ����: " << totalAmount << endl;
        cout << "������:" << endl;
        for (const auto& item : items) {
            cout << "- " << item.first->name << ": " << item.second << " ��." << endl;
        }
    }
};

class User {
public:
    string name;
    string email;
    Cart cart;
    vector<Order> orderHistory;

    User(string name, string email) : name(name), email(email) {}

    void addToCart(Product* product, int quantity) {
        cart.addProduct(product, quantity);
    }

    void placeOrder() {
        if (cart.items.empty()) {
            cout << "����� �������!" << endl;
            return;
        }
        string orderID = "ORD" + to_string(orderHistory.size() + 1);
        orderHistory.emplace_back(orderID, cart.items, cart.calculateTotal());
        cart.clearCart();
    }

    void viewOrders() {
        for (Order& order : orderHistory) {
			order.showOrderInfo();
        }
    }
};

int main() {

}