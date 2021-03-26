#include <bits/stdc++.h> // This will be replaces with individual header files later
using namespace std;

typedef struct
{
    string buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->buffer = "";

    return input_buffer;
}

/* Clear the input buffer after accepting input*/
void clear_input_buffer(InputBuffer *input_buffer)
{
    input_buffer->buffer = "";
}

/* Cleans input string by deleting extra spaces and semicolon*/
void remove_trailing_spaces(InputBuffer *input_buffer)
{
    /*Removing spaces and semicolon from the end*/
    while (!input_buffer->buffer.empty() && (input_buffer->buffer.back() == ' ' || input_buffer->buffer.back() == ';'))
    {
        input_buffer->buffer.pop_back();
    }

    /*Removing extra spaces from the start*/
    for (int i = 0; i < input_buffer->buffer.length(); i++)
    {
        if (input_buffer->buffer[i] != ' ')
        {
            input_buffer->buffer.erase(0, i);
            break;
        }
    }
}

/* Reads input from the cmd*/
void read_input(InputBuffer *input_buffer)
{
    string line = "";
    while (getline(cin, line))
    {
        if (line == "")
        {
            continue;
        }
        else
        {
            input_buffer->buffer += ' ' + line;
            if (line.back() == ';')
            {
                break;
            }
        }
    }
    remove_trailing_spaces(input_buffer);
}

void print_prompt() { printf("db > "); }

int main(int argc, char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();
    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer == ".exit")
        {
            cout << "Thanks for using YourSQL, Hope to see you again soon!\n";
            exit(0);
        }
        else
        {
            cout << "Unrecognized Command " << input_buffer->buffer << endl;
        }
        clear_input_buffer(input_buffer);
    }
}