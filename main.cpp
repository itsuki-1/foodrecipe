#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <utility>
#include <algorithm>
#include <tuple>
#include <cctype>
#include <sstream>
#include <cstring>

std::vector<std::tuple<std::string, std::vector<std::string>, std::string>> recipes;

void initialzeFood()
{
    // Add each recipe and its ingredients
    recipes.emplace_back("Classic Spaghetti Carbonara", std::vector<std::string>{"Spaghetti", "Pancetta", "Eggs", "Cheese", "Garlic", "Salt", "Black pepper", "Olive oil"}, "https://www.jamieoliver.com/recipes/pasta-recipes/gennaro-s-classic-spaghetti-carbonara/");
    recipes.emplace_back("Chicken Tikka Masala", std::vector<std::string>{"Chicken", "Yogurt", "Onion", "Tomatoes", "Cream", "Garlic", "Ginger", "Salt", "Oil"}, "https://www.indianhealthyrecipes.com/chicken-tikka-masala/");
    recipes.emplace_back("Beef Stir Fry", std::vector<std::string>{"Beef", "Peppers", "Onion", "Soy", "Oyster sauce", "Sesame oil", "Garlic", "Ginger", "Oil"}, "https://www.allrecipes.com/recipe/228823/quick-beef-stir-fry/");
    recipes.emplace_back("Shakshuka", std::vector<std::string>{"Eggs", "Onion", "Pepper", "Tomato sauce", "Cumin", "Paprika", "Salt and pepper to taste", "Olive oil"}, "https://downshiftology.com/recipes/shakshuka/");
    recipes.emplace_back("Greek Salad", std::vector<std::string>{"Tomatoes", "Cucumber", "Onion", "Cheese", "Kalamata olives", "Olive oil", "Red wine vinegar", "Salt", "Black pepper", "Oregano"}, "https://www.loveandlemons.com/greek-salad/");
    recipes.emplace_back("Mexican Tacos", std::vector<std::string>{"Beef", "Taco shells", "Onion", "Tomatoes", "Lettuce", "Cheese", "Taco seasoning", "Salt", "Sour cream"}, "https://damndelicious.net/2019/04/18/mexican-street-tacos/");
    recipes.emplace_back("Vegetable Curry", std::vector<std::string>{"Onion", "Garlic", "Ginger", "Carrot", "Peas", "Pepper", "Cauliflower", "Tomato", "Curry powder", "Coconut milk", "Salt", "Oil"}, "https://www.bbcgoodfood.com/recipes/vegetable-curry-crowd");
    recipes.emplace_back("French Onion Soup", std::vector<std::string>{"Onions", "Beef broth", "White wine", "Butter", "Thyme", "Salt", "Black pepper", "Baguette", "Cheese"}, "https://www.simplyrecipes.com/recipes/french_onion_soup/");
    recipes.emplace_back("Quiche Lorraine", std::vector<std::string>{"Crust", "Bacon", "Onion", "Eggs", "Cream", "Cheese", "Salt", "Black pepper"}, "https://natashaskitchen.com/quiche-lorraine/");
    recipes.emplace_back("Pad Thai", std::vector<std::string>{"Rice", "Noodle", "Shrimp", "Tofu", "Egg", "Bean sprouts", "Onions", "Peanuts", "Fish sauce", "Tamarind paste", "Sugar", "Lime", "Oil"}, "https://www.recipetineats.com/chicken-pad-thai/");
}

void printAll()
{
    if (recipes.empty())
    {
        std::cout << "No recipes available." << std::endl;
        return;
    }

    std::cout << "Available Recipes:" << std::endl;
    for (const auto& recipe : recipes)
    {
        const std::string& name = std::get<0>(recipe);
        const std::vector<std::string>& ingredients = std::get<1>(recipe);
        const std::string& url = std::get<2>(recipe);

        std::cout << "Recipe: " << name << std::endl;
        std::cout << "Ingredients:" << std::endl;
        for (const auto& ingredient : ingredients)
        {
            std::cout << "- " << ingredient << std::endl;
        }
        std::cout << std::endl;  // Add a blank line for better separation between recipes
    }
}

void toLower(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
}

void searchByName(const std::string& searchTerm)
{
    std::string lowerSearchTerm = searchTerm;
    toLower(lowerSearchTerm);
    std::vector<const std::tuple<std::string, std::vector<std::string>, std::string>*> foundRecipes;

    for (const auto& recipe : recipes)
    {
        std::string lowerRecipeName = std::get<0>(recipe);
        toLower(lowerRecipeName);

        if (lowerRecipeName.find(lowerSearchTerm) != std::string::npos)
        {
            foundRecipes.push_back(&recipe);
        }
    }

    if (!foundRecipes.empty())
    {
        std::cout << "Found " << foundRecipes.size() << " result(s):" << std::endl;
        for (size_t i = 0; i < foundRecipes.size(); ++i)
        {
            std::cout << i + 1 << ". " << std::get<0>(*foundRecipes[i]) << std::endl;
        }

        std::cout << "Enter the numbers of the recipes you want to open (separated by space), or 0 to exit: ";
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        int num;
        while (iss >> num)
        {
            if (num > 0 && num <= foundRecipes.size())
            {
                std::string url = std::get<2>(*foundRecipes[num - 1]);
                std::string command = "start " + url;
                system(command.c_str());
            }
        }
    }
    else
    {
        std::cout << "No recipes found with the name containing '" << searchTerm << "'." << std::endl;
    }
}

void searchByIngredient(const std::string& searchTerm)
{
    std::string lowerSearchTerm = searchTerm;
    toLower(lowerSearchTerm);
    std::vector<const std::tuple<std::string, std::vector<std::string>, std::string>*> foundRecipes;

    for (const auto& recipe : recipes)
    {
        const auto& ingredients = std::get<1>(recipe);
        for (const auto& ingredient : ingredients)
        {
            std::string lowerIngredient = ingredient;
            toLower(lowerIngredient);

            if (lowerIngredient.find(lowerSearchTerm) != std::string::npos)
            {
                foundRecipes.push_back(&recipe);
                break; // Avoid adding the same recipe multiple times
            }
        }
    }

    if (!foundRecipes.empty())
    {
        std::cout << "Found " << foundRecipes.size() << " result(s) containing '" << searchTerm << "':" << std::endl;
        for (size_t i = 0; i < foundRecipes.size(); ++i) {
            std::cout << i + 1 << ". " << std::get<0>(*foundRecipes[i]) << std::endl;
        }

        std::cout << "Enter the numbers of the recipes you want to open (separated by space), or 0 to exit: ";
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        int num;
        while (iss >> num)
        {
            if (num > 0 && num <= foundRecipes.size())
            {
                std::string url = std::get<2>(*foundRecipes[num - 1]);
                std::string command = "start " + url;
                system(command.c_str());
            }
        }
    }
    else
    {
        std::cout << "No recipes found with the ingredient '" << searchTerm << "'." << std::endl;
    }
}

void case2()
{
    std::string searchTerm;
    std::cout << "Enter the name of the food to search for: ";
    std::cin.ignore();
    std::getline(std::cin, searchTerm);
    searchByName(searchTerm);
}

void case3()
{
    std::string searchTerm;
    std::cout << "Enter an ingredient to search for: ";
    std::cin.ignore(100000, '\n'); // Clear the newline character left in the input buffer
    std::getline(std::cin, searchTerm);
    searchByIngredient(searchTerm);
}

int main()
{
    initialzeFood();
    Print:
    std::cout << "Welcome to the quick recipe search app" << '\n';
    std::cout << "======================================" << '\n';
    std::cout << "[1] Show all recipe" << '\n';
    std::cout << "[2] Search by food name" << '\n';
    std::cout << "[3] Search by food ingredients" << '\n';
    std::cout << "[4] Exit" << '\n';
    std::cout << "======================================" << '\n';
    std::cout << "Option (1 - 4): ";
    char option{};
    std::cin >> option;

    switch (option)
    {
    case '1':
        system("cls");
        printAll();
        goto Print;
        break;
    case '2':
        system("cls");
        case2();
        goto Print;
        break;
    case '3':
        system("cls");
        case3();
        goto Print;
        break;
    case '4':
        std::cout << "Bye";
        break;
    default:
        system("cls");
        std::cout << "Invalid Input" << '\n';
        goto Print;
    }
}