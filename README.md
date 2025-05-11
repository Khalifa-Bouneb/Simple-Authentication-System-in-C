🔐 C++ Command-Line Authentication System

A secure, command-line-based authentication system implemented in C++ to demonstrate essential concepts in user authentication and session management. It supports user registration, login, and session handling with password hashing, file-based storage, and session expiry tracking. Designed for educational purposes, the project emphasizes secure coding practices and modularity.

🚀 Features

* ✅ **User Registration:** Create an account with a unique username and a strong password (min. 8 characters, including uppercase, lowercase, digits, and special characters).
* 🔒 **Secure Password Storage:** Passwords are hashed using a simplified SHA-256 implementation with a randomly generated salt.
* 🔐 **User Login:** Authenticates users by verifying hashed passwords and initiates a session upon successful login.
* ⏳ **Session Management:** Sessions are tracked with unique session IDs and automatically expire after 30 minutes of inactivity.
* 📂 **File-Based Storage:** User data (username, hashed password, salt) is stored in `users.txt` in a CSV-like format.
* 🛡️ **Input Validation:** Prevents CSV injection in usernames and ensures password complexity.
* ✨ **Password Masking:** Passwords are masked with asterisks (\*) during entry for security.
* 🚧 **Error Handling:** Robust handling of invalid inputs and file operations.

---

🛠️ Project Structure

Main Components:

* `SHA256`: Simplified class for password hashing.
* `Validator`: Ensures usernames and passwords meet security criteria.
* `PasswordHasher`: Generates salts and hashes passwords securely.
* `UserRepository`: Handles file-based storage and retrieval of user data.
* `Session`: Represents user sessions with creation and expiration tracking.
* `SessionManager`: Manages session lifecycle and expiry.
* `AuthService`: Orchestrates registration, login, and logout operations.

File Structure:

```
📂 ProjectRoot
 ├── src/
 │   ├── main.cpp
 │   ├── sha256.cpp
 │   ├── validator.cpp
 │   └── ...
 ├── users.txt
 └── README.md
```

---

⚙️ Prerequisites

* C++11 or later
* C++ compiler (e.g., `g++`, `clang++`)
* Standard C++ libraries

---

🚀 Getting Started

1. Clone the repository:

```bash
$ git clone https://github.com/Khalifa-Bouneb/Simple-Authentication-System-in-C
```

2. Navigate to the project directory:

```bash
$ cd cpp-auth-system
```

3. Compile the project:

```bash
$ g++ src/main.cpp -o auth-system
```

4. Run the program:

```bash
$ ./auth-system
```

---

📦 Usage

* **Register:** Create a new user account with a secure password.
* **Login:** Authenticate with your username and password.
* **Logout:** End the session safely.
* **Exit:** Terminate the program.

---

🔥 Security Considerations

* The SHA256 implementation is **simplified** and not suitable for production use. Use libraries like `OpenSSL` or `libsodium` for secure hashing.
* Passwords are stored as hashed strings but not **encrypted**. Consider encrypting the file or using a database.
* Session IDs are **timestamp-based** and not cryptographically secure. Implement random session IDs for enhanced security.
* Implement **rate limiting** and account lockout to mitigate brute-force attacks.

---

🚧 Limitations

* Simplified hashing mechanism.
* File-based storage (unsuitable for large-scale deployment).
* No password recovery or user deletion functionality.
* Session persistence is limited to runtime (sessions are not stored between runs).

---

🌱 Future Enhancements

* Integrate a secure hashing library (e.g., `OpenSSL`).
* Migrate to a database (e.g., `SQLite`) for user data storage.
* Implement password recovery and user deletion features.
* Encrypt sensitive data in `users.txt`.
* Enhance session management with persistent storage.
* Add rate limiting and account lockout mechanisms.

---

🤝 Contributing

Contributions are welcome! Open an issue or submit a pull request to discuss improvements or bug fixes.

---

📜 License

This project is licensed under the [MIT License](LICENSE).

---

🙏 Acknowledgments

Inspired by common authentication systems, this project was developed for educational purposes to learn and demonstrate secure coding practices in C++.
