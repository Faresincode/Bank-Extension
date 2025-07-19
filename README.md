# Bank-Extension
A simple C++ console-based Bank Management System that supports client and user management, deposit/withdrawal transactions, and role-based access permissions using text file storage.
# 🏦 Bank Management System (C++ Console Application)

This is a fully functional **Bank Management System** written in C++. It allows users to manage clients, perform banking transactions, and handle user roles and permissions.

## 📂 Project Structure

- `Bank-Extension.cpp`: Main C++ source file containing the entire logic of the program.
- `Clients.txt`: Text file that stores all the client records.
- `Users.txt`: Text file that stores all system users and their permissions.

> 💡 **Note:** The system uses simple text files for data persistence.

---

## 🔐 Features

### 👤 Client Management

- **Add New Client**: Add a new client with account number, pin code, name, phone, and balance.
- **Delete Client**: Delete an existing client by their account number.
- **Update Client**: Edit a client's information.
- **Find Client**: Search and view client details using their account number.
- **List Clients**: View all clients in a formatted table.
- **Show Total Balances**: Display the total balance across all client accounts.

---

### 💰 Transactions

- **Deposit Money**: Add money to a specific client’s account.
- **Withdraw Money**: Withdraw money (with balance validation).
- **Show Total Balances**: Display balance summary of all clients.

---

### 👨‍💻 User Management

- **Add User**: Create new system users (admin or limited access).
- **Delete User**: Delete existing users (except the default `Admin`).
- **Update User**: Change password or permissions of a user.
- **Find User**: View user details.
- **List Users**: View all registered users and their permissions.

---

## 🔐 User Login System

Upon running the program, the system shows a **login screen**. Only users with valid credentials (from `Users.txt`) can access the system. The default Admin has full permissions.

---

## 🎯 Permissions & Roles

Users can be given **full access** or **specific permissions**, including:

- Show Client List
- Add New Client
- Delete Client
- Update Client
- Find Client
- Perform Transactions
- Manage Users

Permissions are stored in binary format using **bitwise flags** for efficient access control.

---

## ⚙️ How It Works

### Data Storage

- `Clients.txt` and `Users.txt` are simple text files storing records.
- Each line represents one record, with fields separated by `#//#`.

**Example (Client):**

admin#//#admin123#//#-1
> `-1` means full access.

## 🧪 How to Run

1. Open the project in any C++ compiler (e.g., Code::Blocks, Visual Studio, or terminal).
2. Make sure `Clients.txt` and `Users.txt` are in the same folder.
3. Compile and run `Bank-Extension.cpp`.

**Linux/macOS/Windows (Terminal):**
```bash
g++ Bank-Extension.cpp -o BankSystem
./BankSystem
📌 Notes
All data is saved automatically to .txt files.

You cannot delete or update the default Admin.

System uses system("cls") or system("pause>0") for screen clearing and pausing (might be platform-dependent).

Use text-based permissions or bitwise values.

🧑‍💻 Author
This project is for learning C++ file handling, struct management, and access control using enums, vectors, and conditions.

