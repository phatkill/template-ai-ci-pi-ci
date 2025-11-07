    #include <iostream>
    #include <vector>
    #include <algorithm>

    struct Person {
        std::string name;
        int age;
    };

    // Custom comparison function
    bool comparePeople(const Person& p1, const Person& p2) {
        return p1.age < p2.age; // Sort by age in ascending order
    }

    int main() {
        std::vector<Person> people = {
            {"Alice", 30},
            {"Bob", 25},
            {"Charlie", 35}
        };

        // Using a custom comparison function
        std::sort(people.begin(), people.end(), comparePeople);

    // Using a lambda expression (more common in modern C++)
        // std::sort(people.begin(), people.end(), [](const Person& p1, const Person& p2) {
        //     return p1.name < p2.name; // Sort by name alphabetically
        // });

        for (const auto& p : people) {
            std::cout << p.name << " (" << p.age << ")\n";
        }
        return 0;
    }