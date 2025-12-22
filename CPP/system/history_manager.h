#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <iostream>
#include "../ds/stack.h"
#include "../ds/array.h"
using namespace std;

class HistoryManager
{
private:
    Stack<string> historyStack; // Stores actions for undo

public:
    // Add an action to history
    void addAction(const string &action)
    {
        historyStack.push(action);
    }

    // Undo last action
    string undo()
    {
        if (historyStack.empty())
        {
            return "No actions to undo.";
        }
        string lastAction = historyStack.top();
        historyStack.pop();
        return lastAction;
    }

    // View last action without removing
    string peekLastAction() const
    {
        if (historyStack.empty())
        {
            return "No actions in history.";
        }
        return historyStack.top();
    }

    // Check if history is empty
    bool isEmpty() const
    {
        return historyStack.empty();
    }

    // Display all history
    void displayHistory()
    {
        if (historyStack.empty())
        {
            cout << "History is empty." << endl;
            return;
        }

        // Use a temporary array to preserve order
        DynamicArray<string> temp;
        while (!historyStack.empty())
        {
            temp.push_back(historyStack.top());
            historyStack.pop();
        }
        cout << "Action History (most recent first):" << endl;
        for (int i = 0; i < temp.size(); i++)
        {
            cout << "- " << temp[i] << endl;
            historyStack.push(temp[i]); // restore
        }
        // Restore in reverse order
        DynamicArray<string> reversed;
        for (int i = temp.size() - 1; i >= 0; i--)
            reversed.push_back(temp[i]);
        while (!historyStack.empty())
            historyStack.pop();
        for (int i = reversed.size() - 1; i >= 0; i--)
            historyStack.push(reversed[i]);
    }

    // Clear all history
    void clearHistory()
    {
        while (!historyStack.empty())
        {
            historyStack.pop();
        }
    }
};

#endif
