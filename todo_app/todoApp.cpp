#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Constants for our menu options
enum TodoMenuOptions
{
    ADD_TODO = 1,
    DELETE_TODO,
    SHOW_TODO,
    EXIT_APP
};

/**
 * @brief Clear the input buffer
 *
 */
void clearInputBuffer()
{
    cin.clear();
    cin.ignore();
}

/**
 * @brief Structure for todo elements
 *
 */
struct Todo
{
    int id;
    string todo;
};

/**
 * @brief Get the Todo input data from user using command line
 *
 * @return Provided todo text from user
 */
string getTodoInput()
{
    string userInput{""};
    cout << "Enter todo: ";
    getline(cin, userInput);
    return userInput;
}

/**
 * @brief Ask user for taking another input
 *
 * @return True or False for taking another input
 */
bool shouldTakeAnotherTodo()
{
    string userInput{""};
    cout << endl
         << "Add another todo (Y | N): ";
    cin >> userInput;

    return userInput == "y" || userInput == "Y";
}

/**
 * @brief Shows all the entered todos by the user
 *
 * @param todos - Dataobject where todos are getting stored
 */
void showAvailableTodos(const vector<Todo> &todos)
{
    cout << "==================================" << endl;
    cout << "Available todos" << endl;

    if (todos.empty())
    {
        cout << "No todo added" << endl;
    }
    else
    {
        for (auto &&todo : todos)
        {
            cout << "Todo " << todo.id << ": " << todo.todo << endl;
        }
    }
    cout << "==================================" << endl;
    cout << endl;
}

/**
 * @brief Get the selected option from menu by the user
 *
 * @return The selected option
 */
int getMenuSelectedOption()
{
    int selectedOption{0};
    while (selectedOption < ADD_TODO || selectedOption > EXIT_APP)
    {
        cout << "Available actions for todo app" << endl;
        cout << ADD_TODO << ". Add Todo" << endl;
        cout << DELETE_TODO << ". Delete Todo" << endl;
        cout << SHOW_TODO << ". Show Todos" << endl;
        cout << EXIT_APP << ". Exit app" << endl;
        cout << "Enter menu option : ";
        cin >> selectedOption;
    }
    return selectedOption;
}

/**
 * @brief Continuosly ask user after taking todo for another and add them into dataobject.
 *
 * @param todoCounter - Current todo entered by user so far
 * @param todos - Dataobject where todos are getting stored
 */
void askAndAddTodo(int *todoCounter, vector<Todo> &todos)
{
    while (true)
    {
        clearInputBuffer();
        string userInput = getTodoInput();

        if (!userInput.empty())
        {
            todos.push_back({id : *todoCounter, todo : userInput});
            ++(*todoCounter);
        }

        bool takeOtherTodo = shouldTakeAnotherTodo();
        if (!takeOtherTodo)
            break;
    }
}

/**
 * @brief Delete particular todo from todos dataobject if present
 *
 * @param todoId - id of todo to delete
 * @param todoText - Todo text
 * @param todos - Dataobject where todos are getting stored
 */
void deleteTodo(int todoId, string todoText, vector<Todo> &todos)
{
    bool isTodoFound{false};
    for (auto td = todos.begin(); td != todos.end(); ++td)
    {
        if (td->id == todoId || td->todo == todoText)
        {
            cout << "Todo deleted: " << td->todo << endl;
            todos.erase(td);
            isTodoFound = true;
            break;
        }
    }

    if (!isTodoFound)
        cout << "No todo deleted" << endl;
}

/**
 * @brief Takes input from user for deleting the todo
 *
 * @param todos - Dataobject where todos are getting stored
 */
void handleTodoDeleteAction(vector<Todo> &todos)
{
    string enteredDeleteTodoText{""};
    int enteredDeleteTodoId{-1};

    string enteredData{""};
    showAvailableTodos(todos);
    clearInputBuffer();
    cout << "Enter todo to delete: ";
    getline(cin, enteredData);

    try
    {
        enteredDeleteTodoId = stoi(enteredData);
    }
    catch (const std::invalid_argument &e)
    {
        enteredDeleteTodoText = enteredData;
        std::cerr << "Error: Invalid string for conversion to integer: " << enteredData << std::endl;
    }

    deleteTodo(enteredDeleteTodoId, enteredDeleteTodoText, todos);
}

int main()
{
    // Initialize the dataobject for storing the todos
    // Some examples are added for testing
    vector<Todo> todos{};

    bool takeUserInput{false};

    int todoCounter{1};

    cout << "Basic todo app" << endl;

    // Continuously show todo menu to user, take his input and do action accordingly
    while (true)
    {
        int selectedAction = getMenuSelectedOption();

        if (selectedAction == ADD_TODO)
            askAndAddTodo(&todoCounter, todos);

        if (selectedAction == DELETE_TODO)
        {
            handleTodoDeleteAction(todos);
        }

        if (selectedAction == SHOW_TODO)
            showAvailableTodos(todos);

        if (selectedAction == EXIT_APP)
            break;
    }

    return 0;
}