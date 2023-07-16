import json

def generate_cpp_header(json_data):
    header_name = json_data['name']
    header_description = json_data['description']
    classes = json_data['classes']
    functions = json_data['functions']

    header_content = f'// {header_name} - C++ Standard Library\n\n'
    header_content += f'/*\n{header_description}\n*/\n\n'

    for class_data in classes:
        class_name = class_data['name']
        class_description = class_data['description']
        constructors = class_data['constructors']
        member_functions = class_data['member_functions']

        header_content += f'class {class_name} {{\n'
        header_content += f'    // {class_description}\n'

        # Constructors
        header_content += '\n    // Constructors\n'
        for constructor in constructors:
            constructor_signature = constructor['signature']
            constructor_description = constructor['description']
            header_content += f'\n'
            header_content += f'    // {constructor_description}\n'
            header_content += f'    {constructor_signature};\n'

        # Member functions
        header_content += '\n    // Member functions\n'
        for member_function in member_functions:
            member_function_signature = member_function['signature']
            member_function_description = member_function['description']
            header_content += f'    {member_function_signature};  // {member_function_description}\n'

        header_content += '};\n\n'

    return header_content


# Example usage
json_content = """
{
  "name": "vector",
  "description": "The `<vector>` header provides the `std::vector` container class for dynamic arrays.",
  "classes": [
    {
      "name": "std::vector",
      "description": "The `std::vector` class is a container that encapsulates dynamic arrays.",
      "constructors": [
        {
          "signature": "vector()",
          "description": "Constructs an empty vector."
        },
        {
          "signature": "vector(size_t count)",
          "description": "Constructs a vector with a specified number of default-initialized elements."
        }
      ],
      "member_functions": [
        {
          "signature": "size() const",
          "description": "Returns the number of elements in the vector."
        },
        {
          "signature": "push_back(const T& value)",
          "description": "Appends a value to the end of the vector."
        }
      ]
    }
  ]
}
"""

json_data = json.loads(json_content)
cpp_header = generate_cpp_header(json_data)
print(cpp_header)
