# Bank Clients Management System
This is a C++ Console Application developed for the basic management of bank client records. The project focuses on implementing the fundamental CRUD (Create, Read, Update, Delete) operations efficiently. All client data is permanently stored in a delimited text file (Clients.txt)

🎯 Key Features
List All Clients: View a paginated or complete list of all current clients and their details.

Add New Client: Input new client records with validation to ensure account numbers are unique.

Delete Client: Search for a client by account number and delete their record after user confirmation.

Update Client Info: Modify existing client details (Pin Code, Name, Phone, Balance).

Find Client: Retrieve and display the full details of a specific client using their account number.

Data Persistence: Data is stored in a text file (Clients.txt), ensuring records are maintained between program sessions.

🏗️ Scalability and Code Architecture
The program has been specifically designed with a modular and highly structured architecture to facilitate future expansion and maintainability.

Modular Design: Functions are clearly separated based on their tasks (e.g., file handling, string conversion, data reading, and display). This reduces coupling and makes the codebase easier to understand and debug.

Data Structure Focus: Utilizing a struct (sClient) to represent the client object and a vector to manage the in-memory client list provides an efficient and standard way to handle collections of data.

Future Expansion Ready: The current structure acts as a robust core for record management. It is highly scalable to support the addition of advanced financial operations in the future, such as:

Deposit Operations: Easily integrate a function to increase a client's balance.

Withdrawal Operations: Add a function to decrease a client's balance, including necessary checks for sufficient funds.

Transfer Feature: Implement a complex function combining both withdrawal and deposit logic between two accounts.

This design philosophy ensures that the core logic is solid, allowing new features to be added by extending the existing code rather than rewriting it.

⚙️ How the Program Works
Main Menu: The program starts by displaying a main menu, allowing the user to select the desired operation.

Data Loading: For operations that require accessing client data, the application loads all records from the Clients.txt file into a vector in memory.

Operation Execution: The selected operation (Add, Delete, Update, etc.) is performed on the data held in the memory vector.

Data Saving: After any modification, the updated client list is entirely saved back to the Clients.txt file, ensuring the permanent records are always synchronized with the latest changes.

This design philosophy ensures that the core logic is solid, allowing new features to be added by extending the existing code rather than rewriting it.
