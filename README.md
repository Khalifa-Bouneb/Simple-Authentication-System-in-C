C++ Command-Line Authentication System
Overview
This project is a secure, command-line-based authentication system implemented in C++ to demonstrate key concepts in user authentication and session management. It allows users to register, log in, and log out, with features such as password hashing with salts, session tracking with automatic expiry, and file-based user storage. The system is designed for educational purposes, emphasizing secure coding practices and modularity.
Features

User Registration: Users can create an account with a unique username and a strong password. Passwords are validated to ensure they meet security requirements (minimum 8 characters, including uppercase, lowercase, digits, and special characters).
Secure Password Storage: Passwords are hashed using a simplified SHA-256 implementation (for demonstration) combined with a randomly generated salt to enhance security.
User Login: Authenticates users by comparing hashed passwords and creates a session upon successful login.
Session Management: Sessions are tracked with unique session IDs and automatically expire after 30 minutes of inactivity.
File-Based Storage: User data (username, hashed password, and salt) is stored in a text file (users.txt) using a CSV-like format.
Input Validation: Ensures usernames do not contain commas (to prevent CSV injection) and passwords meet complexity requirements.
Password Masking: Password input is masked with asterisks (*) for security during entry.
Error Handling: Robust handling of invalid inputs and file operations.

Project Structure

Main Components:
SHA256: A simplified class for hashing passwords (note: in production, use a cryptographically secure library like OpenSSL).
Validator: Validates usernames and passwords based on predefined rules.
PasswordHasher: Generates random salts and hashes passwords with salts.
UserRepository: Manages user data storage and retrieval from a file.
Session: Represents a user session with creation and expiration times.
SessionManager: Handles session creation, retrieval, and deletion.
AuthService: Orchestrates registration, login, and logout operations.


File:
users.txt: Stores user data in the format username,hashedPassword,salt.



Prerequisites

C++11 or later
A C++ compiler (e.g., g++, clang++)
Standard C++ libraries (included in the code)

Usage

Run the Program:
The program starts with a menu offering options to register, log in, or exit.
After logging in, the menu changes to offer logout or exit options.


Register:
Enter a unique username (no commas allowed).
Enter a password (at least 8 characters, with uppercase, lowercase, digits, and special characters).
The system will confirm successful registration or display an error if the username exists or input is invalid.


Login:
Enter your username and password.
On successful login, a session is created, and the menu updates.
If credentials are invalid, an error message is shown.


Logout:
Select the logout option to end the session.


Exit:
Choose the exit option to terminate the program.



Security Notes

The SHA256 implementation is simplified for educational purposes and not cryptographically secure. In a production environment, use established libraries like OpenSSL or libsodium for hashing.
Passwords are stored in plain text in users.txt (hashed but not encrypted). In a real system, consider encrypting the file or using a database with proper access controls.
Session IDs are basic (timestamp-based). For production, use cryptographically secure random IDs.
The system does not implement rate limiting or account lockout mechanisms, which are essential for preventing brute-force attacks in real applications.

Limitations

The hashing algorithm is a placeholder and not suitable for production use.
File-based storage (users.txt) is not optimized for concurrent access or large user bases.
No support for password recovery or user deletion.
Session IDs are not persisted across program restarts.

Future Improvements

Replace the simplified SHA256 with a secure hashing library (e.g., OpenSSL).
Implement a database (e.g., SQLite) for user storage.
Add password recovery and account management features.
Introduce rate limiting and account lockout for enhanced security.
Persist sessions across program restarts using file or database storage.
Encrypt sensitive data in users.txt.

Contributing
Contributions are welcome! Please submit a pull request or open an issue to discuss improvements or bug fixes.
License
This project is licensed under the MIT License. See the LICENSE file for details.
Acknowledgments
This project was created to learn and demonstrate secure authentication concepts in C++. It is inspired by real-world authentication systems but simplified for educational purposes.
