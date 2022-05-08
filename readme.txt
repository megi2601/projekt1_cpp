kompilacja programu (do database.exe):
g++ -o database main.cpp database.cpp user_mode.cpp admin_mode.cpp

argumenty wywołania:
--help : wyświetla info o programie
--login <username> <password> : logowanie do bazy danych

Domyślna nazwa pliku z bazą danych: database.txt (do zmiany w main.cpp).
Jeśli nie ma takiego pliku w folderze albo jest pusty, program prosi o stworzenie pierwszego użytkownika-admina.