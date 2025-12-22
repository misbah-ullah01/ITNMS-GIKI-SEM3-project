#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class HistoryManager
{
private:
    stack<string> historyStack; // Stores actions for undo

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
    void displayHistory() const
    {
        if (historyStack.empty())
        {
            cout << "History is empty." << endl;
            return;
        }

        stack<string> tempStack = historyStack; // copy to preserve original
        cout << "Action History (most recent first):" << endl;
        while (!tempStack.empty())
        {
            cout << "- " << tempStack.top() << endl;
            tempStack.pop();
        }
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
