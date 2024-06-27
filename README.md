### CROW - C++ - SQLite - Backend

Crow: https://crowcpp.org/master/
Crow-Github: https://github.com/CrowCpp/Crow


## Endpoints

### Add a Todo
- **POST** `/todos/{todo}`
  - **Tags**: `todobackend-application`
  - **Parameters**:
    - `todo` (Path, required, Type: string)
  - **Responses**:
    - `200 OK`: Return value (Type: string)

### Remove a Todo
- **DELETE** `/todos/{todo}`
  - **Tags**: `todobackend-application`
  - **Parameters**:
    - `todo` (Path, required, Type: string)
  - **Responses**:
    - `200 OK`: Return value (Type: string)

### Get all Todos
- **GET** `/todos/`
  - **Tags**: `todobackend-application`
  - **Responses**:
    - `200 OK`: Return value (Type: array of strings)
