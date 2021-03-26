#include <bits/stdc++.h> // This will be replaces with individual header files later
using namespace std;

typedef struct
{
    string buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

/*  This is like creating a new data type as MetaCommandResult
    MetaCommands are the ones that are not SQL commands, they start with a '.'
*/
typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->buffer = "";

    return input_buffer;
}

MetaCommandResult do_meta_command(InputBuffer *input_buffer)
{
    if (input_buffer->buffer == ".exit")
    {
        cout << "Thanks for using YourSQL, Hope to see you again soon!\n";
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
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

    /* Clear the input buffer before accepting input*/
    input_buffer->buffer = "";
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

        if (input_buffer->buffer.empty())
        {
            // The user entered just an empty string
            continue;
        }
        else
        {
            if (input_buffer->buffer[0] == '.')
            {
                switch (do_meta_command(input_buffer))
                {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    cout << "Unrecognized Command " << input_buffer->buffer << endl;
                    continue;
                }
            }
        }
    }
}